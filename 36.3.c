#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<stdarg.h>

#define MAXSURNAME 11 //max length for surname

typedef struct
{
    char surname[MAXSURNAME];
    int age;
} the_employees_t;

enum commands {
    Exit,
    Enter_date,
    Edit_date,
    Delete_date,
    Find_date,
    Print_date
};

the_employees_t* read_from_file(uint64_t* size_array)
{
    the_employees_t* a;
    FILE *f = NULL;
    f = fopen("employees.txt", "rb");
    if (f == NULL)
    {
        printf("Not opened\n");
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    size_t size_f = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (size_f % sizeof(the_employees_t) != 0)
    {
        return NULL;
    }
    *size_array = (size_f / sizeof(the_employees_t));
    a = (the_employees_t*)malloc(sizeof(the_employees_t)*(*size_array));
    fread(a, sizeof(the_employees_t), *size_array, f);
    fclose(f);
    return a;
}

the_employees_t* write_to_file(the_employees_t* a, uint64_t* size_array)
{
    FILE *f = NULL;
    f = fopen("employees.txt", "w+b");
    if (f == NULL)
    {
        printf("Not opened\n");
        return NULL;
    }
    fwrite(a, sizeof(the_employees_t), *size_array, f);
    fclose(f);
    return a;
}

the_employees_t* enter_date(the_employees_t* a, uint64_t* size_array) {
    if (a == NULL) {
        (*size_array) = 1;
        a = (the_employees_t*)malloc(sizeof(the_employees_t)*(*size_array));
    }
    else
    {
        (*size_array)++;
        a = realloc(a, sizeof(the_employees_t)*(*size_array));
    }
        printf("Enter surname\n");
        scanf("%s", a[(*size_array)-1].surname);
        printf("Enter age\n");
        scanf("%d", &a[(*size_array)-1].age);
//		fwrite(&a[i], 1, sizeof(the_employees_t), f);
    return a;
}


void* print_struct(the_employees_t* a, uint64_t* size_array)
{
    for (int index = 0; index < *size_array; index++)
    {
        printf("Surname is  %s, age is %d\n", a[index].surname, a[index].age);
    }
}

void* edit_employees(the_employees_t* a, uint64_t* size_array)
{
    int position = -1;
    printf("Enter number of position for edit");
    scanf("%d", &position);
    printf("Enter surname\n");
    scanf("%s", a[position].surname);
    printf("Enter color\n");
    scanf("%d", &a[position].age);
}

void* find_surname(the_employees_t* a, uint64_t* size_array)
{
    char surname_for_find[MAXSURNAME];
    fgets(surname_for_find, MAXSURNAME, stdin);
    for (int index = 0; index < *size_array; index++)
    {
        if (strcmp(a[index].surname, surname_for_find) == 0)
        {
            printf("Surname %s, age is %d", a[index].surname, a[index].age);
        }
    }
}

int main()
{

    the_employees_t* a = NULL;
    uint64_t size_array = 0;
    a = read_from_file(&size_array);
    //    int counter = 0;
    uint64_t input = 0;
    do {
        printf("Press 0 for exit\n");
        printf("Press 1 for enter data\n");
        printf("Press 2 for edit data\n");
        printf("Press 3 for delete data\n");
        printf("Press 4 for find data\n");
        printf("Press 5 for print data\n");
        scanf("%lu", &input);
        switch (input) {
            case Enter_date:
                a = enter_date(a, &size_array);
                break;
            case Edit_date:
                edit_employees(a, &size_array);
                break;
            case Delete_date:

                break;
            case Find_date:
                find_surname(a, &size_array);
                break;
            case Print_date:
                printf("Base yours employees:\n");
                print_struct(a, &size_array);
                break;
            default:
                printf("Repeat your choice");
                break;
        }
    } while (input != Exit);
    write_to_file(a, &size_array);
    return 0;
}