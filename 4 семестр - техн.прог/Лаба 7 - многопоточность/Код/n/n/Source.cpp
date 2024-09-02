#include <iostream>
#include <Windows.h>
#include <thread>
//#include <semaphore.h>
#include <chrono>



HANDLE h_Sem1;
HANDLE h_Sem2;
HANDLE h_Sem3;
int l;

using namespace std;

void first()
{
	if (l == 1) {
		Sleep(1000);
		WaitForSingleObject(h_Sem1, INFINITY);
		cout << "1 -ый курит " << endl;
		this_thread::sleep_for(chrono::milliseconds(100));
		ReleaseSemaphore(h_Sem1, 1, NULL);
	}

}

void second()
{
	if (l == 2) {
		Sleep(1000);
		WaitForSingleObject(h_Sem2, INFINITY);
		cout << "2 -ой курит" << endl;
		this_thread::sleep_for(chrono::milliseconds(100));
		ReleaseSemaphore(h_Sem2, 1, NULL);
	}
}

void three()
{
	if (l == 3) {
		Sleep(1000);
		WaitForSingleObject(h_Sem3, INFINITY);
		cout << "3 -ий курит" << endl;
		this_thread::sleep_for(chrono::milliseconds(100));
		ReleaseSemaphore(h_Sem3, 1, NULL);
	}
}

int main()
{

	setlocale(LC_ALL, "ru");
	cin.get();
	h_Sem1 = CreateSemaphore(NULL, 0, 1, NULL);
	h_Sem2 = CreateSemaphore(NULL, 0, 1, NULL);
	h_Sem3 = CreateSemaphore(NULL, 0, 1, NULL);

	std::thread t1(first);
	std::thread t2(second);
	std::thread t3(three);


	Sleep(300);
	while (1)
	{
		int d = 1 + rand() % 3;
		//cout « d « endl;
		switch (d)
		{
		case 1:
			if (l != 1) {
				l = 1;
				Sleep(300);
				t1.detach();
				cout << "На столе: бумага, спички" << endl;
				ReleaseSemaphore(h_Sem1, 1, NULL);
				this_thread::sleep_for(chrono::milliseconds(100));
				WaitForSingleObject(h_Sem1, INFINITY);
				t1 = thread(first);
			}
			break;
		case 2:
			if (l != 2) {
				l = 2;
				Sleep(300);
				t2.detach();
				cout << "На столе: табак, спички" << endl;
				ReleaseSemaphore(h_Sem2, 1, NULL);
				this_thread::sleep_for(chrono::milliseconds(100));
				WaitForSingleObject(h_Sem2, INFINITY);
				t2 = thread(second);
			}
			break;
		case 3:
			if (l != 3) {
				l = 3;
				Sleep(300);
				t3.detach();
				cout << "На столе: табак, бумага" << endl;
				ReleaseSemaphore(h_Sem3, 1, NULL);
				this_thread::sleep_for(chrono::milliseconds(100));
				WaitForSingleObject(h_Sem3, INFINITY);

				t3 = thread(three);
			}
			break;
		default:
			break;
		}

		Sleep(1000);
	}

	return 0;
}