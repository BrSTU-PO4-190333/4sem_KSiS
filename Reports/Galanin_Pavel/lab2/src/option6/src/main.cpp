#define _CRT_SECURE_NO_WARNINGS	// для VS включить старые функции

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

char* init(int* length, const char* static_string);		// конструктор
void del(char* str);									// деструктор
void print(char* str);									// печать строки
void print_time(double start_time, double end_time);	// печать времени
void func_cpp(char* str, int length);					// заменяет нечётные символы на +
void func_assembler(char* str, int length);				// заменяет нечётные символы на +
void test_change_str(void (*func)(char*, int), const char* title);	// тест изменения строки
void time_test(int iterations, void (*func)(char*, int), const char* title);	// тест по времени

int main()
{
	// Тесты изменения строки
	test_change_str(func_cpp, "C++");
	test_change_str(func_assembler, "Assembler");

	// Тесты по времени
	for (int i = 1; i < 1e8; i *= 10)
	{
		time_test(i, func_cpp, "C++");
		time_test(i, func_assembler, "Assembler");
	}

	return 0;
}

char* init(int* length, const char* static_string)
{
	*length = strlen(static_string);			// length = размер строки

	char* dynamic_string = new char[*length];	// выделили память для dynamic_string
	strcpy(dynamic_string, static_string);		// dynamic_string = static_string

	return dynamic_string;
}

void del(char* str)
{
	delete[] str;	// очистили строку
}

void print(char* str)
{
	printf("str = \"%s\"\n", str);	// напечатали строку
}

void print_time(double start_time, double end_time)
{
	double result = (end_time - start_time) / CLOCKS_PER_SEC;	// высчитали время
	printf("time\t%lf\n", result);								// напечатали время
}

void func_cpp(char* str, int length)
{
	for (int i = 0; i < length; i++)
	{
		if (i % 2 == 1)	// если i делится на 2 c остатком 1
		{
			str[i] = '+';
		}
	}
}

void func_assembler(char* my_string, int my_length)
{
	__asm
	{
		mov edi, my_string			// edi = my_string
		mov ecx, my_length			// ecx = my_length
		mov eax, 0					// eax = 0
	lo:								// 
		inc edi						// edi = edi + 1
		test eax, 1					// if (eax % 2 == 1) then zf = ? 
		jz ev						// goto ev
		mov byte ptr[edi - 1], '+'	// arr[edi - 1] = '+'
	ev:								//
		inc eax						// eax = eax + 1
		loop lo						// if (ecx != 0) then goto loop; ecx = ecx - 1
	}
}

void test_change_str(void (*func)(char*, int), const char* title)
{
	printf("Test change string on %s\n", title);
	char* str;									// переменная для динамической строки
	int length;									// переменная для размера строки

	str = init(&length, "Hello, World!");		// вернули строку, вернули размер строки конструктором
	print(str);									// напечатали строку
	func(str, length);							// функция заменяет нечётные символы на +
	print(str);									// напечатали строку
	del(str);									// очистили строку деструктором
	printf("\n");
}

void time_test(int iterations, void (*func)(char*, int), const char* title)
{
	
	char* str;			// переменная для динамической строки
	int length;			// переменная для длины строки
	double start_time;	// переменная времени старта
	double end_time;	// переменная времени финиша
	double time = 0;	//	переменная для полного времени после цикла
	for (int i = 0; i < iterations; i++)
	{
		int a = 1000000;							// начальная точка для рандома
		int b = 1000000000;							// конечная точка для рандома
		int number = rand() % (b - a + 1) + a;		// получаем рандомное число
		str = new char[9];							// выделили память под строку
		str = init(&length, _itoa(number, str, 10));// получили новую строку и длину

		start_time = clock();						// засекли время
		func(str, length);							// функция заменяет нечётные символы на +
		end_time = clock();							// засекли время
		time += (end_time - start_time);			// добавили время данного цикла

		del(str);									// очистили строку
	}

	printf(
		"%12d\t%24.12lf\t%s\n",
		iterations,
		time / CLOCKS_PER_SEC,
		title
	);

	FILE* file_pointer = fopen("data.csv", "a");	// открываем файл
	if (file_pointer == NULL)						// если файл не открылся
	{
		printf("File not open\n");
	}
	else											// если файл открылся
	{
		fprintf(
			file_pointer,
			"%d, %lf, %s\n",
			iterations,
			time / CLOCKS_PER_SEC,
			title
		);
		fclose(file_pointer);						// закрываем файл
	}
}