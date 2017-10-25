#include<stdlib.h>
#include<stdio.h>
#include<stdarg.h>
#include<string.h>
#include<stdint.h>

char* make_array(int64_t size)
{
	char* a = (char*)malloc(size * sizeof(char));
	return a;
}

void for_cod(int64_t size, char* a)
{
	int64_t temp = 255;
	for (int64_t st = 0; st < size; st++)
	{
		a[st] = temp;
		temp--;
	}
	for (int64_t i = 0; i < 1000; i++)
	{
		int64_t st = rand() % 255 - 0;
		int64_t st1 = rand() % 255 - 0;
		int64_t temp = a[st];
		a[st] = a[st1];
		a[st1] = temp;
	}
}
void for_decod(int64_t size, char* a, char* b)
{
	for (int64_t st = 0; st < size; st++)
	{
		b[(unsigned char)a[st]] = st;
	}
}

void print_array(int64_t size, int64_t* a)
{
	for (int64_t st = 0; st < size; st++)
	{
		printf("%lli ", a[st]);
	}
	printf("\n\n");
}
void free_array(uint64_t* a)
{
	free(a);
}

int main()
{
	srand(time(NULL));
	int64_t size = 256;
	char* a;
	char* b;
	a = make_array(size);
	b = make_array(size);
	for_cod(size, a);
	for_decod(size, a, b);
//	print_array(size, a);


	FILE *fp = NULL;
	fopen_s(&fp, "Windows Server 2012 R2 Key.txt", "rb");
	if (fp == NULL) {
		printf("Not opened\n");
		return 1;
	}
	char ptr[100];

	FILE *fe = NULL;
	fopen_s(&fe, "new.txt", "w+b");


	while (!feof(fp))
	{
		size_t len = fread(&ptr, 1, 100, fp);
		for (int64_t st = 0; st < len; st++)
		{
			ptr[st] = a[(unsigned char)ptr[st]];
			printf("%d to %d\n", ptr[st], a[(unsigned char)ptr[st]]);
		}
		fwrite(&ptr, 1, len, fe);
	}
	fclose(fp);
	fclose(fe);

	fopen_s(&fp, "new.txt", "rb");
	fopen_s(&fe, "new1.txt", "w+b");
	while (!feof(fp))
	{
		size_t len = fread(&ptr, 1, 100, fp);
		for (int64_t st = 0; st < len; st++)
		{
			ptr[st] = b[(unsigned char)ptr[st]];
			printf("%d dec %d\n", ptr[st], b[(unsigned char)ptr[st]]);
		}
		fwrite(&ptr, 1, len, fe);
	}
	fclose(fp);
	fclose(fe);
	free_array(a);
	free_array(b);
	system("pause");
	return 0;
}