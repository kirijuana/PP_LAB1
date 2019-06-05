

#include "stdafx.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <ctime> 

using namespace std;

int mas[16] = {};
int q = 0, w = 0;

void *proizv(void *param)
{
	int i, p = (*(int *)param) * 8;
	int *x; x = new int; *x = 1;
	cout << "Числа кратные " << q << " и " << w << ":\n";
	for (i = p; i < p + 8; i++)
	{
		if ((mas[i] % q) == 0 && (mas[i] % w) == 0)
		{
			cout << mas[i] << "\n";
			*x = *x * mas[i];
		}
			//if ((mas[i] % w) == 0)
			//{
			//	cout << mas[i] << "\n";
			//	*x = *x * mas[i];
			//}
	}
	return (void *)x;

}

int main()
{
	int x1 = 1;
	cout << "Введите q и w.\n";
	cin >> q >> w;	

		srand(time(NULL));
	
	
		for (int i = 0; i < 16; i++)
		{
			mas[i] = 1 + rand() % 16; // 0 ... 15
		}
		pthread_t thread[2]; int number[2];
		for (int i = 0; i<2; i++)
		{
			number[i] = i; //для передачи параметра потоку
			pthread_create(&thread[i], NULL, proizv, (void *)(number + i));
		}		int *x;
	for (int i = 0; i<2; i++)
	{ //ожидание завершения работы дочерних потоков
	  //и получение результата их вычислений
		pthread_join(thread[i], (void **)&x);
		x1 = x1 * *x;
	}
	fprintf(stdout, "Массиу: ");
	for (int i = 0; i < 16; i++)
	{
		fprintf(stdout, "%d ", mas[i]);
	}
	fprintf(stdout, "\n");
	fprintf(stdout, "Произведение = %d", x1);
	fprintf(stdout, "\n");

	system("pause");
	
}



