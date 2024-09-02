#include <iostream>
#include <Windows.h>
#include <thread>
//#include <semaphore.h>
#include <chrono>



HANDLE h_Sem1;
HANDLE h_Sem2;
HANDLE h_Sem3;

using namespace std;

void first()
{
	Sleep(500);
	WaitForSingleObject(h_Sem1, INFINITY);
	cout << "1 -ый курит " << endl;
	this_thread::sleep_for(chrono::milliseconds(100));
	ReleaseSemaphore(h_Sem1, 1, NULL);
	
}

void second()
{
	Sleep(500);
	WaitForSingleObject(h_Sem2, INFINITY);
	cout << "2 -ой курит" << endl;
	this_thread::sleep_for(chrono::milliseconds(100));
	ReleaseSemaphore(h_Sem2, 1, NULL);
}

void three()
{
	Sleep(500);
	WaitForSingleObject(h_Sem3, INFINITY);
	cout << "3 -ий курит" << endl;
	this_thread::sleep_for(chrono::milliseconds(100));
	ReleaseSemaphore(h_Sem3, 1, NULL);
}

int main()
{
	setlocale(LC_ALL, "ru");
	std::thread t1(first);
	std::thread t2(second);
	std::thread t3(three);

	

	h_Sem1 = CreateSemaphore(NULL, -1, 1, NULL);
	h_Sem2 = CreateSemaphore(NULL, -1, 1, NULL);
	h_Sem3 = CreateSemaphore(NULL, -1, 1, NULL);

	/*mtx1.lock();
	mtx2.lock();
	mtx3.lock();*/
	/*ReleaseSemaphore(h_Sem1, 1, NULL);
	ReleaseSemaphore(h_Sem2, 1, NULL);
	ReleaseSemaphore(h_Sem3, 1, NULL);*/

	
	
	while (1)
	{
		

		int d = 1 + rand() % 3;
		//cout << d << endl;
		switch (d)
		{
		case 1:
			t1.detach();
			cout << "На столе: бумага, спички" << endl;
			ReleaseSemaphore(h_Sem1, 1, NULL);
			this_thread::sleep_for(chrono::milliseconds(500));
			WaitForSingleObject(h_Sem1, INFINITY);
			t1 = thread(first);
		break;
		case 2:
			t2.detach();
			cout << "На столе: табак, спички" << endl;
			ReleaseSemaphore(h_Sem2, 1, NULL);
			this_thread::sleep_for(chrono::milliseconds(500));
			WaitForSingleObject(h_Sem2, INFINITY);
			t2 = thread(second);
		break;
		case 3:
			t3.detach();
			cout << "На столе: табак, бумага" << endl;
			ReleaseSemaphore(h_Sem3, 1, NULL);
			this_thread::sleep_for(chrono::milliseconds(500));
			WaitForSingleObject(h_Sem3, INFINITY);
			t3 = thread(three);
		break;
		default:
			break;
		}

		Sleep(1000);
	}

	return 0;
}