#include "test2.h"
#include <thread>
#include <chrono>
#include <qimage.h>

// Общий ресурс
std::atomic<int> resource(0);

// Флаги доступа для продавца и потребителя
std::atomic<bool> seller_wants_access(false);
std::atomic<bool> buyer_wants_access(false);
std::atomic<int> turn(1);

std::vector <int> resours;

static unsigned int timeout{ 2000 }, timeout2{ 2000 };

int steck = 0;
std::thread* t1;
std::thread* t2;

int i = 0;
int j = 0;

bool end = false;

test2::test2(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.pushButton, &QPushButton::clicked,
        this, &test2::clicked_btn);

    QImage img;
    img.load("resource/earth.ico");
    //ui.label->setPixmap(QPixmap::fromImage(img));

    connect(ui.horizontalSlider, &QSlider::valueChanged,
        this, [](int value)
        {
            auto value_u = static_cast<unsigned int>(value);
            unsigned int time = 300 + 2700 * value_u / 100;
            timeout = time;
        });

    connect(ui.horizontalSlider_2, &QSlider::valueChanged,
        this, [](int value)
        {
            auto value_u = static_cast<unsigned int>(value);
            unsigned int time = 300 + 2700 * value_u / 100;
            timeout2 = time;
        });

    connect(ui.pushButton_2, &QPushButton::clicked,
        this, [](bool clicked)
        {
            end = true;
        });
}

void test2::producer(int i)
{
    QString s = "make resource " + QString::number(resource)+'\n';
    resours.push_back(resource);
    ui.plainTextEdit->insertPlainText(s);

    
    for (int count = 0; count < resours.size(); count++)
    {
        QImage img;
        img.load("resource/earth.ico");
        switch (count)
        {
        case 0:
        {
            ui.label->setText(QString::number(resours[0]));
            break;
        }
        case 1:
        {
            ui.label_2->setText(QString::number(resours[1]));
            break;
        }
        case 2:
        {
            ui.label_3->setText(QString::number(resours[2]));
            break;
        }
        case 3:
        {
            ui.label_4->setText(QString::number(resours[3]));
            break;
        }
        case 4:
        {
            ui.label_5->setText(QString::number(resours[4]));
            break;
        }
        case 5:
        {
            ui.label_6->setText(QString::number(resours[5]));
            break;
        }
        case 6:
        {
            ui.label_7->setText(QString::number(resours[6]));
            break;
        }
        case 7:
        {
            ui.label_8->setText(QString::number(resours[7]));
            break;
        }
        case 8:
        {
            ui.label_9->setText(QString::number(resours[8]));
            break;
        }
        default:
            break;
        }
        //ui.label_2->setPixmap(QPixmap::fromImage(img));
    }
    
        
      
    
        
    
}

void test2::consumer()
{
    ui.label->clear();
    ui.label_2->clear();
    ui.label_3->clear();
    ui.label_4->clear();
    ui.label_5->clear();
    ui.label_6->clear();
    ui.label_7->clear();
    ui.label_8->clear();
    ui.label_9->clear();
    QString s = "get resource " + QString::number(resours[resours.size()-1]) + '\n';
    resours.pop_back();

    for (int count = 0; count < resours.size(); count++)
    {
        switch (count)
        {
        case 0:
        {
            ui.label->setText(QString::number(resours[0]));
            break;
        }
        case 1:
        {
            ui.label_2->setText(QString::number(resours[1]));
            break;
        }
        case 2:
        {
            ui.label_3->setText(QString::number(resours[2]));
            break;
        }
        case 3:
        {
            ui.label_4->setText(QString::number(resours[3]));
            break;
        }
        case 4:
        {
            ui.label_5->setText(QString::number(resours[4]));
            break;
        }
        case 5:
        {
            ui.label_6->setText(QString::number(resours[5]));
            break;
        }
        case 6:
        {
            ui.label_7->setText(QString::number(resours[6]));
            break;
        }
        case 7:
        {
            ui.label_8->setText(QString::number(resours[7]));
            break;
        }
        case 8:
        {
            ui.label_9->setText(QString::number(resours[8]));
            break;
        }
        default:
            break;
        }
    }
    ui.plainTextEdit->insertPlainText(s);

    
}

void modify(test2* form)
{
    while (true)
    {
        if (!resours.empty())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(timeout2));
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
            int i = 0;
            
            // Получение ресурса
            QMetaObject::invokeMethod(form, "consumer", Qt::BlockingQueuedConnection);
            resource = 0;

            // Закончить доступ
            turn = 2;
            buyer_wants_access = false;
            i++;
            steck--;
        }
        if (end) break;
    }
}

void modify2(test2* form)
{
   while (true)
   {
       if (resours.size() != 9)
       {
           std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
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
           QMetaObject::invokeMethod(form, "producer", Qt::BlockingQueuedConnection, Q_ARG(int, i));
           

           // Закончить доступ
           turn = 1;
           seller_wants_access = false;
           j++;
       }
       if (end) break;
      // if (j == 9) break;
    }
}

void test2::clicked_btn(bool clicked)
{
    t1 = new std::thread{modify, this};
    t2 = new std::thread{modify2, this};
}



test2::~test2()
{}
