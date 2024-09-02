#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_test2.h"

class test2 : public QMainWindow
{
    Q_OBJECT

public:
    test2(QWidget *parent = nullptr);
    ~test2();

private:
    Ui::test2Class ui;

    Q_INVOKABLE void producer(int i);
    Q_INVOKABLE void consumer();

private slots:
    void clicked_btn(bool clicked);
};
