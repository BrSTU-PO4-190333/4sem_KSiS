#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

void c_string_swap(char* a, char* b);
void asm_string_swap(char* a, char* b);
int get_number_digit(int number);
char* generate_word();
void test(const char title[], void (*func)(char*, char*), int iter);

int main()
{
	printf("|%-16s|%-10s|%-10s|\n", "iterations", "time", "title");
	for (int i = 1; i < 1e8; i *= 10)
	{
		printf("|%-16s|%-10s|%-10s|\n", " ", " ", " ");
		test("C/C++", c_string_swap, i);
		test("Assembler", asm_string_swap, i);
	}
	return 0;
}

void c_string_swap(char* a, char* b)
{
	char* temp = a;
	a = b;
	b = temp;
}

void asm_string_swap(char* a, char* b)
{
	__asm
	{
		mov eax, a
		mov ebx, b
		xchg eax, b
		xchg ebx, a
	}
}

int get_number_digit(int number)
{
	int i = 0;
	while (number > 0)
	{
		number /= 10;
		++i;
	}
	return i;
}

char* generate_word()
{
	int a = 1e3;
	int b = 1e12;
	int number = rand() % (b - a + 1) + a;

	int word_length = get_number_digit(number);
	char* word = new char[word_length];

	_itoa(number, word, 10);

	return word;
}

void test(const char title[], void (*func)(char*, char*), int iterations)
{
	double time = 0.0;
	for (int i = 0; i < iterations; i++)
	{
		char* s1 = generate_word();
		char* s2 = generate_word();
		char* s3 = generate_word();
		char* s4 = generate_word();

		time_t start_time = clock();
		func(s1, s3);
		func(s2, s4);
		time_t end_time = clock();
		time += (double)(end_time - start_time) / CLOCKS_PER_SEC;

		delete[] s4;
		delete[] s3;
		delete[] s2;
		delete[] s1;
	}
	printf("|%-16d|%-10.4lf|%-10s|\n", iterations, time, title);
}
