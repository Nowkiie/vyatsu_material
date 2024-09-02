#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_test.h"



class test : public QMainWindow
{
    Q_OBJECT

public:
    test(QWidget *parent = nullptr);
    ~test();
    

private:
    Ui::testClass ui;

    Q_INVOKABLE void calculateFunc(int i);
    Q_INVOKABLE void calculateFunc_2();
   // Q_INVOKABLE void DrawWidget();

    int x = 0;
    int z = 0;
    int y = 0;

    long long ms_1;
    long long ms_2;

    

private slots:
    void clicked_btnStart(bool clicked);
    void changed_slider(int value);
    void changed_slider2(int value);
};
