#include "test.h"

#include <iostream>
#include <thread>
#include <chrono>
#include "boost/interprocess/sync/interprocess_semaphore.hpp"
#include <qpushbutton.h>
#include <qtextedit.h>

boost::interprocess::interprocess_semaphore sem_1(0); 
boost::interprocess::interprocess_semaphore sem_2(0); 

int x_o = 0;
int y_o = 0;
int z_o = 0;
int j = 0;

std::thread* t1;
std::thread* t2;

static unsigned int timeout{ 2000 }, timeout2{ 2000 };

test::test(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.start_btn, &QPushButton::clicked,
        this, &test::clicked_btnStart);
    
    ui.horizontalSlider->setValue(25);
    ui.horizontalSlider_2->setValue(25);

    ui.label_3->setText(QString::number(ui.horizontalSlider->value()));

    ui.label_4->setText(QString::number(ui.horizontalSlider_2->value()));

    connect(ui.horizontalSlider, &QSlider::valueChanged,
        this, &test::changed_slider);
    
    connect(ui.horizontalSlider_2, &QSlider::valueChanged,
        this, &test::changed_slider2);
}

void test::changed_slider(int value)
{
    ui.label_3->setText(QString::number(ui.horizontalSlider->value()));
    auto value_u = static_cast<unsigned int>(value);
    unsigned int time = 300 + 2700 * value_u / 100;
    timeout = time;
}

void test::changed_slider2(int value)
{
    ui.label_4->setText(QString::number(ui.horizontalSlider_2->value()));
    auto value_u = static_cast<unsigned int>(value);
    unsigned int time = 300 + 2700 * value_u / 100;
    timeout2 = time;
}



void test::calculateFunc(int i)
{
    x = x_o;
    z = z_o;
    int count_elem = x + z;
    int count_row = count_elem / 4;
    int g = 0;

    for (int str = 0; str <= count_row; str++)
    {
        for (int row = 0; row <= 4; row++)
        {
            QString text_intoEdit = "edt" + QString::number(g);
            QTextEdit* edt = new QTextEdit();
            edt->setText(text_intoEdit);
            ui.gridLayout->addWidget(edt, str, row);
            g++;
        }
        
    }
   
    ui.edit_t1->insertPlainText(QString::number(i) + '\n');
    
    
    
   
}

void test::calculateFunc_2()
{
    y = y_o;
    int count_elem = y;
    int count_row = count_elem / 4;
    int g = 0;

    for (int str = 0; str <= count_row; str++)
    {
        for (int row = 0; row <= 4; row++)
        {
            QString text_intoEdit = "btn" + QString::number(g);
            QPushButton* btn = new QPushButton();
            btn->setText(text_intoEdit);
            ui.gridLayout_2->addWidget(btn, str, row);
            g++;
        }

    }
    ui.edit_t1->insertPlainText("this 2\n");
    
}



void modify(test* form)
{
    

    for (int i=1; i<=10; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
        x_o = i;
        y_o = 3 * i - 1;
        z_o = 2 * i - 1;
       QMetaObject::invokeMethod(form, "calculateFunc", Qt::BlockingQueuedConnection, Q_ARG(int, i));
       sem_2.post();
       sem_1.wait();
    }      
   
}

void modify_2(test* form)
{
    while (true)
    {
       
        sem_2.wait();
        std::this_thread::sleep_for(std::chrono::milliseconds(timeout2));
        QMetaObject::invokeMethod(form, "calculateFunc_2", Qt::BlockingQueuedConnection);
        j++;
        sem_1.post();
        if (j == 10)
        {
            break;
        }
    }
    
    
}

void test::clicked_btnStart(bool clicked)
{
    while (ui.gridLayout->count())
    {
        QWidget* widget = ui.gridLayout->itemAt(0)->widget();
        if (widget)
        {
            ui.gridLayout->removeWidget(widget);
            delete widget;
        }
    }

    while (ui.gridLayout_2->count())
    {
        QWidget* widget = ui.gridLayout_2->itemAt(0)->widget();
        if (widget)
        {
            ui.gridLayout_2->removeWidget(widget);
            delete widget;
        }
    }

    t1 = new std::thread{modify, this };
    t2 = new std::thread{modify_2, this };

}

test::~test()
{}
