#include "mainwindow.h"

mainwindow::mainwindow(QWidget *parent) : QWidget(parent)
{
    lbl   = new QLabel("Sue_alfa_v.3.0.0");

    cb1   = new QCheckBox("Upper Register");
    cb2   = new QCheckBox("Inversion");

    line  = new QLineEdit;

    ok    = new QPushButton("ENTER");
    close = new QPushButton("Close");

    b1    = new QPushButton("1");
    b2    = new QPushButton("2");
    b3    = new QPushButton("3");

    b4    = new QPushButton("4");
    b5    = new QPushButton("5");
    b6    = new QPushButton("6");

    b7    = new QPushButton("7");
    b8    = new QPushButton("8");
    b9    = new QPushButton("9");

    b10   = new QPushButton("0");
    b11   = new QPushButton("*");
    b12   = new QPushButton("#");

    QVBoxLayout *LineLayout = new QVBoxLayout;
    LineLayout->addWidget(lbl);
    LineLayout->addWidget(line);


    QHBoxLayout *first = new QHBoxLayout;

    first->addWidget(b1);
    first->addWidget(b2);
    first->addWidget(b3);

    QHBoxLayout *second = new QHBoxLayout;

    second->addWidget(b4);
    second->addWidget(b5);
    second->addWidget(b6);

    QHBoxLayout *third = new QHBoxLayout;

    third->addWidget(b7);
    third->addWidget(b8);
    third->addWidget(b9);

    QHBoxLayout *forth = new QHBoxLayout;

    forth->addWidget(b11);
    forth->addWidget(b10);
    forth->addWidget(b12);

    QVBoxLayout *numpad = new QVBoxLayout;

    numpad->addLayout(first);
    numpad->addLayout(second);
    numpad->addLayout(third);
    numpad->addLayout(forth);

    QVBoxLayout *main = new QVBoxLayout;

    main->addLayout(LineLayout);
    main->addLayout(numpad);

    connect(b1,SIGNAL(clicked()),this,SLOT(setValue1()));
    connect(b2,SIGNAL(clicked()),this,SLOT(setValue2()));
    connect(b3,SIGNAL(clicked()),this,SLOT(setValue3()));
    connect(b4,SIGNAL(clicked()),this,SLOT(setValue4()));
    connect(b5,SIGNAL(clicked()),this,SLOT(setValue5()));
    connect(b6,SIGNAL(clicked()),this,SLOT(setValue6()));
    connect(b7,SIGNAL(clicked()),this,SLOT(setValue7()));
    connect(b8,SIGNAL(clicked()),this,SLOT(setValue8()));
    connect(b9,SIGNAL(clicked()),this,SLOT(setValue9()));
    connect(b10,SIGNAL(clicked()),this,SLOT(setValue0()));

    connect(b11,SIGNAL(clicked()),this,SLOT(DeleteLastSimbol()));
    connect(b12,SIGNAL(clicked()),this,SLOT(close()));

    setLayout(main);
    setWindowTitle("Sue_alfa_v.3.0.0");
}
