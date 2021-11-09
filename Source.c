#include <Windows.h>
#include <stdio.h>


int n;


VOID WINAPI StartFirstThreads(VOID);
VOID WINAPI StartSecondThreads(VOID);

VOID WINAPI ShowNumFirst(VOID);
VOID WINAPI ShowNumSecond(VOID);


DWORD WINAPI Fact(VOID);
DWORD WINAPI Fibn(VOID);



int main()
{
	system("chcp 1251");
	n = 100;
	HANDLE FirstEx = CreateThread(NULL, 0, StartFirstThreads, NULL, 0, 0);
	WaitForSingleObject(FirstEx, INFINITE);

	
	n = 10;

	
	HANDLE SecondEx = CreateThread(NULL, 0, StartSecondThreads, NULL, 0, 0);
	WaitForSingleObject(SecondEx, INFINITE);


	return 0;
}


VOID WINAPI StartFirstThreads(VOID)
{
	
	HANDLE hT[2];
	hT[0] = CreateThread(NULL, 0, ShowNumFirst, NULL, 0, 0);
	hT[1] = CreateThread(NULL, 0, ShowNumSecond, NULL, 0, 0);
	WaitForMultipleObjects(2, hT, TRUE, INFINITE);
}


VOID WINAPI StartSecondThreads(VOID)
{

	HANDLE hT[2];
	hT[0] = CreateThread(NULL, 0, Fact, NULL, 0, 0);
	hT[1] = CreateThread(NULL, 0, Fibn, NULL, 0, 0);
	WaitForMultipleObjects(2, hT, TRUE, INFINITE);
}


VOID WINAPI ShowNumFirst(VOID)
{
	for (int i = 0; i < n; i++)
	{
		printf("\nПоток 1 число %i", i);
	}
	ExitThread(0);
}

VOID WINAPI ShowNumSecond(VOID)
{
	for (int i = 0; i < n; i++)
	{
		printf("\nПоток 2 число %i", i);
	}
	ExitThread(0);
}

DWORD WINAPI Fact(VOID)
{
	DWORD Num = 1;
	if (n == 0)
	{
		printf("\nФакториал %i = %i", n, Num);
	}
	else
	{
		for (DWORD i = 1; i <= n; i++)
		{
			Num *= i;
			printf("\nФакториал %i = %i", i, Num);
		}
	}
	ExitThread(0);
}

DWORD WINAPI Fibn(VOID)
{
	DWORD a = 0;
	DWORD b = 1;
	DWORD c = a+b;
	for (DWORD i = 1; i <= n; i++)
	{
		if (i > 2)
		{
			a = b;
			b = c;
			c = a + b;
		}
		printf("\nФибоначчи %i = %i", i, c);
	}
	ExitThread(0);
}