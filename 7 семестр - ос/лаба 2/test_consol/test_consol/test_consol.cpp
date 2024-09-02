// test_consol.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <thread>
#include <atomic>

int i = 0;
int j = 0;

// Общий ресурс
std::atomic<int> resource(0);

// Флаги доступа для продавца и потребителя
std::atomic<bool> seller_wants_access(false);
std::atomic<bool> buyer_wants_access(false);
std::atomic<int> turn(1);

int steck = 0;

// Потребитель
void consumer() {
    while (true) {
        if (steck != 0)
        {
            // Запрос доступа к ресурсу
            buyer_wants_access = true;
            while (seller_wants_access) {
                if (turn == 2) {
                    buyer_wants_access = false;
                    while (turn == 2) {
                        // Ждем, пока продавец закончит доступ
                    }
                    buyer_wants_access = true;
                }
            }

            // Получение ресурса
            std::cout << "Потребитель получил ресурс: " << resource << std::endl;
            resource = 0;

            // Закончить доступ
            turn = 2;
            buyer_wants_access = false;
            i++;
        }
        
        if (i == 4) break;
    }
}

// Продавец
void producer() {
    while (true) {
        // Запрос доступа к ресурсу
        seller_wants_access = true;
        while (buyer_wants_access) {
            if (turn == 1) {
                seller_wants_access = false;
                while (turn == 1) {
                    // Ждем, пока потребитель закончит доступ
                }
                seller_wants_access = true;
            }
        }

        // Производство ресурса
        
        int new_resource = rand() % 100 + 1;
        resource = new_resource;
        steck = 1;
        std::cout << "Продавец произвел ресурс: " << new_resource << std::endl;

        // Закончить доступ
        turn = 1;
        seller_wants_access = false;
        j++;
        if (j == 4) break;
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    srand(time(0));
    std::thread consumer_thread(consumer);
    std::thread producer_thread(producer);

    consumer_thread.join();
    producer_thread.join();

    return 0;
}

