#include <iostream>
#include <conio.h>

using namespace std;
struct Node   
{
    int a;
    int Size;
    char* mas;
    Node* prev;
    Node* next;
};
Node* head = nullptr; 
Node* tail = nullptr; 
int Count = 0; 


void AddToHead()  
{
    using namespace std;
    setlocale(LC_ALL, "rus"); 

    Node* newNode = (Node*)malloc(sizeof(Node));  
    cout << "������� ���-�� ��������� ������: ";
    while (!(cin >> newNode->Size) || (cin.peek() != '\n') || newNode->Size < 1 || newNode->Size > 80)
    {
        cin.clear();
        while (cin.get() != '\n');
        cout << "������������ ����, ������� ����� ���� int �� 1 �� 80!" << endl;
        cout << "������� ���-�� ��������� �������: ";
    }
    newNode->mas = (char*)malloc(newNode->Size *sizeof(char));  //�������� ������ ��� ������
    cout << "������� ������: " << endl; 
    cin >> newNode->mas;
    cout << "������� ����� �����: "; 
    while (!(cin >> newNode->a) || (cin.peek() != '\n'))
    {
        cin.clear();
        while (cin.get() != '\n');
        cout << "������������ ����, ������� ����� ���� int!" << endl;
        cout << "������� ����� �����: ";
    }
    if (newNode != nullptr)
    {
        if (head == nullptr)
        {
            head = tail = newNode;
            //head->next = tail;
            tail->next = nullptr;
            head->prev = nullptr;
            Count++;
        }
        else
        {
            newNode->next = head;
            newNode->prev = nullptr;
            head->prev = newNode;
            head = newNode;
            Count++;
        }
    }

    cout << "������� �������� � ������" << endl;
   // cout << "������� ����� ������, ����� ����������"<<endl;
}

void AddToTail() 
{
    using namespace std;
    setlocale(LC_ALL, "rus"); 
    Node* newNode = (Node*)malloc(sizeof(Node));   
    cout << "������� ���-�� ��������� ������: ";
    while (!(cin >> newNode->Size) || (cin.peek() != '\n') || newNode->Size < 1 || newNode->Size > 80) 
    {
        cin.clear();
        while (cin.get() != '\n');
        cout << "������������ ����, ������� ����� ���� int �� 1 �� 80!" << endl;
        cout << "������� ���-�� ��������� �������: ";
    }
    newNode->mas = (char*)malloc(newNode->Size * sizeof(char));
    cout << "������� ������: " << endl;
    cin >> newNode->mas;
    cout << "������� ����� �����: "; 
    while (!(cin >> newNode->a) || (cin.peek() != '\n'))
    {
        cin.clear();
        while (cin.get() != '\n');
        cout << "������������ ����, ������� ����� ���� int!" << endl;
        cout << "������� ����� �����: ";
    }
    if (newNode != nullptr)
    {
        if (tail == nullptr)
        {
            head = tail = newNode;
            head->next = tail;
            tail->next = nullptr;
            tail->prev = head;
            Count++;
        }
        else
        {
            newNode->next = nullptr;
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
            Count++;
        }
    }
    cout << "������� �������� � �����" << endl;
   // cout << "������� ����� ������, ����� ����������" << endl;
}

void DeleteFromHead()  
{
    using namespace std;
    setlocale(LC_ALL, "rus"); 

    if (head == NULL)
    {
        cout << "������� �����" << endl;
    }
    else
    {
        if (Count == 1)
        {
           // delete[]head->mas;
             free(head->mas);
            free (head);
            head = tail = nullptr;
            Count--;
            cout << "����� ������ �������" << endl;
        }
        else
        {
            Node* temp = head;
            head = head->next;
            free (temp->mas);
            //delete[]temp->mas; //���������� ������ ������������� �������
            temp->prev = nullptr;
            temp->next = nullptr;
            temp->mas = nullptr;
            free(temp); //���������� ������
            temp = nullptr;
            Count--;
            cout << "����� ������ ������� " << endl;
        }
    }
   // cout << "������� ����� ������, ����� ����������" << endl;
}

void DeleteFromTail()  
{
    if (tail == NULL)
    {
        cout << "������� �����" << endl;
    }
    else
    {
        if (Count == 1)
        {
           // delete []head->mas;
            free(head->mas);
            free(head);
            head = tail = nullptr;
            Count--;
            cout << "����� ��������� �������" << endl;
        }
        else
        {
            Node* temp = tail;
            tail = tail->prev;
            free(temp->mas);
           // delete []temp->mas; //���������� ������ ������������� �������
            temp->next = nullptr;
            temp->prev = nullptr;
            free(temp);    //���������� ������
            Count--;
            cout << "����� ��������� �������" << endl;
        }
    }
   // cout << "������� ����� ������, ����� ����������" << endl;
}

void Show() 
{
    using namespace std;
    setlocale(LC_ALL, "rus"); 

    if (head == NULL)
    {
        cout << "������� �����" << endl;
    }
    else
    {
        Node* temp = head;
        int j = 0;
        do
        {
            cout << "������� " << j << ": ";
            for (int i = 0; i < temp->Size; i++)
            {
                cout <<temp->mas[i];
            }
            cout << " a=" << temp->a;
            cout << endl;
            temp = temp->next;
            j++;
        } while (temp != NULL);
    }
}

void Clear() 
{

    using namespace std;
    setlocale(LC_ALL, "rus"); //��������� ������� ��������

    Node* temp;
    if (head == nullptr)
    {
        cout << "������� �����" << endl;
    }
    else
    {
        while (head != nullptr)
        {
            temp = head;
            head = head->next;
           // delete[] temp->mas;
            temp->next = nullptr;
            free(temp); //���������� ������
            Count--;
        }
        if (head == nullptr)
        {
            tail = nullptr;
            cout << "������� �������" << endl;
        }
    }
}

void PrintMenu() //����
{
    using namespace std;
    setlocale(LC_ALL, "rus"); //��������� ������� ��������
    system("cls");

    cout << "1 - �������� � ������" << endl;
    cout << "2 - �������� � �����" << endl;
    cout << "3 - ������� ������ �������" << endl;
    cout << "4 - ������� ��������� �������" << endl;
   // cout << "5 - ��������" << endl;
  //  cout << "�������� �������� ����" << endl;
    cout << "ESC.�����" << endl;
    cout << endl;
}

int main()
{
    setlocale(LC_ALL, "rus"); //��������� ������� ��������

    char ch;
    do
    {
        PrintMenu();
        ch = _getch(); //������� ������� �������
        switch (ch)
        {
        case 49:
        {
           // PrintMenu();
            AddToHead();
            break;
            //break;
        }
        case 50:
        {
            //PrintMenu();
            AddToTail();
            break;
        }
        case 51:
        {
            // PrintMenu();
            DeleteFromHead();
            break;
        }
        case 52:
        {
            //PrintMenu();
            DeleteFromTail();
            break;
        }
      //  case 53:
       // {
        //    //PrintMenu();
        //    Clear();
        //    break;
       // }
        case 54:
        {
            //PrintMenu();
            Show();
            break;
        }
        case 27:
        {
            break;
        }
        default:
            //PrintMenu();
            cerr << "������������ ����� ������" << endl;
        }
        Show();
        cout << endl;
        cout << "������� ����� ������, ����� ����������" << endl;
        ch = _getch(); //������� ������� �������
    } while (ch != 27);


    return 0;
}