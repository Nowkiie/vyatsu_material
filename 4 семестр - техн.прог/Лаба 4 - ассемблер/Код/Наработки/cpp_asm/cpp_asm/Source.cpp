#include <iostream>

using namespace std;

extern "C" void sum(int &mas, int &n, int num);

void main()
{
	int num, n;
	//cout << "Enter number: ";
	//cin >> n;
	cout << "Enter size of matrix: ";
	cin >> num;
	int *mas = new int[num];
	cout << "Enter elements array"<<endl;
	for (int i = 0; i < num; i++)
	{
		cout << "Enter mas[" << i << "]= ";
		cin >> mas[i];
	}
	sum(*mas , n, num);
	for (int i = 0; i < num; i++)
	{
		cout << "Enter mas[" << i << "]= "<<mas[i]<<endl;
	}
	cout << n << "\n";
}