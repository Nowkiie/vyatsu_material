#pragma once
#include "Dll1/Neyav.h"
#include <Windows.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <wchar.h>

using namespace std;

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define OnButtonChoooseClick           1
#define OnButtonClearClick             2
#define OnButtonBackClick              3
#define OnButtonMultiplyClick          4
#define OnButtonDivideClick            5
#define OnButtonOKClick                6
#define OnButtonOK2Click               7


const int N = 5;

const CHAR* ACCEPTED_CHARS = ("0123456789+-");

//Main
HWND Static; 
HWND ButtonChoose; //выбрать действие
HWND ButtonOk2;
HWND ButtonClear; //очитстить матрицу
HWND hEdit[10 * 10]; //матрица
HWND EditRes1; //матрица результатат
HWND EditRes2;
HWND EditVer;
HWND EditNum; //размер матрицы
HWND ButtonOK; //применить 
HWND StaticEr;

//Child
HWND Static1;
HWND Static2;
HWND ButtonBack;
HWND ButtonDivide;
HWND ButtonMultiply;

int a[6][6]; //матрица
int scal = 0; //число
int d[6]; // минимальное расстояние
int v[6]; // посещенные вершины
int co;
int temp, minindex ;
int begin_index = 0;

int number = 6; //число
int past = 0;
int con;

int f = 0; //действие

bool ff = true;






void Clear(HWND edit)
{
	SetWindowText(edit, L""); 
}


void MainWndAddWidjets(HWND hWnd)
{
	

	Static = CreateWindow(L"static", L"Enter top B:", WS_VISIBLE | WS_CHILD | ES_CENTER,
		-105, 300, 490, 20, hWnd, NULL, NULL, NULL);

	EditVer = CreateWindow(L"edit", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
		200, 300, 40, 20, hWnd, NULL, NULL, NULL);

	//ButtonOk2 = CreateWindow(L"button", L"OK", WS_CHILD | WS_VISIBLE,
		//250, 295, 75, 30, hWnd, (HMENU)OnButtonOK2Click, NULL, NULL);

	Static = CreateWindow(L"static", L"Enter initial data:", WS_VISIBLE | WS_CHILD | ES_CENTER,
		5, 80, 490, 20, hWnd, NULL, NULL, NULL);

	int k = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (i == j)
			{
				hEdit[k] = CreateWindow(L"edit", L"0", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER | ES_READONLY,
					i * 80 + 50, j * 30 + 100, 50, 20, hWnd, NULL, NULL, NULL);
				k++;
			}
			else if (i < j)
			{
				hEdit[k] = CreateWindow(L"edit", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER | ES_READONLY,
					i * 80 + 50, j * 30 + 100, 50, 20, hWnd, NULL, NULL, NULL);
				k++;
			}
			else
			{
				hEdit[k] = CreateWindow(L"edit", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
					i * 80 + 50, j * 30 + 100, 50, 20, hWnd, NULL, NULL, NULL);
				k++;
			}

		}
	}
	HEDIT_CREATER(hWnd);
	/*ButtonChoose = CreateWindow(L"button", L"Choose an action", WS_CHILD | WS_VISIBLE,
		175, 550, 150, 30, hWnd, (HMENU)OnButtonChoooseClick, NULL, NULL);


	ButtonClear = CreateWindow(L"button", L"Clear", WS_CHILD | WS_VISIBLE,
		175, 600, 150, 30, hWnd, (HMENU)OnButtonClearClick, NULL, NULL);*/

	Static = CreateWindow(L"static", L"Number of paths:", WS_VISIBLE | WS_CHILD | ES_CENTER,
		600, 5, 490, 20, hWnd, NULL, NULL, NULL);

	EditRes1 = CreateWindow(L"edit", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER |ES_READONLY,
		900, 5, 40, 20, hWnd, NULL, NULL, NULL);

	Static = CreateWindow(L"static", L"Shortest way:", WS_VISIBLE | WS_CHILD | ES_CENTER,
		600, 50, 490, 20, hWnd, NULL, NULL, NULL);

	EditRes2 = CreateWindow(L"edit", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_READONLY,
		900, 50, 40, 20, hWnd, NULL, NULL, NULL);

	


	Static = CreateWindow(L"static", L"Enter matrix size:", WS_VISIBLE | WS_CHILD | ES_CENTER,
		-105, 40, 490, 20, hWnd, NULL, NULL, NULL);

	EditNum = CreateWindow(L"edit", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
		200, 40, 40, 20, hWnd, NULL, NULL, NULL);

	ButtonOK = CreateWindow(L"button", L"OK", WS_CHILD | WS_VISIBLE,
		260, 35, 75, 30, hWnd, (HMENU)OnButtonOKClick, NULL, NULL);

	StaticEr = CreateWindow(L"static", NULL, WS_VISIBLE | WS_CHILD | ES_CENTER,
		200, 450, 690, 50, hWnd, NULL, NULL, NULL);


	

	
}

void MainWnd(HWND hWnd)
{
	

}

void MinWnd2(HWND hWnd)
{
	
}




void ChildWndAddWidjets(HWND hWnd)
{
	Static1 = CreateWindow(L"static", L"Choose an action:", WS_VISIBLE | WS_CHILD | ES_CENTER,
		5, 5, 240, 20, hWnd, NULL, NULL, NULL);

	ButtonBack = CreateWindow(L"button", L"Back", WS_CHILD | WS_VISIBLE,
		75, 170, 100, 30, hWnd, (HMENU)OnButtonBackClick, NULL, NULL);

	ButtonDivide = CreateWindow(L"button", L"Number of paths from A to B", WS_CHILD | WS_VISIBLE, 
		15, 80, 200, 30, hWnd, (HMENU)OnButtonDivideClick, NULL, NULL);

	ButtonMultiply = CreateWindow(L"button", L"Shortest way", WS_CHILD | WS_VISIBLE,
		15, 40, 200, 30, hWnd, (HMENU)OnButtonMultiplyClick, NULL, NULL);

	Static2 = CreateWindow(L"static", L"", WS_VISIBLE | WS_CHILD | ES_CENTER,
		5, 120, 240, 20, hWnd, NULL, NULL, NULL);
}

//void function(int(&mas)[6][6], int (&d)[6], int(&flag))
//{
//	
//
//	for (int i = 0; i < number; i++)
//	{
//		for (int j = 0; j < number; j++)
//		{
//			
//			if (flag == 2) //поиск минимального пути
//			{
//				int min;
//				for (int i = 0; i < 6; i++)
//				{
//					d[i] = 10000;
//					v[i] = 1;
//				}
//				d[begin_index] = 0;
//				// Шаг алгоритма
//				do {
//					minindex = 10000;
//					min = 10000;
//					for (int i = 0; i < 6; i++)
//					{ // Если вершину ещё не обошли и вес меньше min
//						if ((v[i] == 1) && (d[i] < min))
//						{ // Переприсваиваем значения
//							min = d[i];
//							minindex = i;
//						}
//					}
//					// Добавляем найденный минимальный вес
//					// к текущему весу вершины
//					// и сравниваем с текущим минимальным весом вершины
//					if (minindex != 10000)
//					{
//						for (int i = 0; i < 6; i++)
//						{
//							if (mas[minindex][i] > 0)
//							{
//								temp = min + mas[minindex][i];
//								if (temp < d[i])
//								{
//									d[i] = temp;
//								}
//							}
//						}
//						v[minindex] = 0;
//					}
//				} while (minindex < 10000);
//				
//			}
//			if (flag == 1)
//			{
//				if (mas[i][j] != 0 && i>1)
//				{
//					co = co + 1;
//				}
//			}
//		}
//	}
//}
