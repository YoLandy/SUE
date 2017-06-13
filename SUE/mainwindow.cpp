#include "mainwindow.h"


mainwindow::mainwindow(QWidget *parent) : QWidget(parent)
{
    lbl     = new QLabel("Sue_alfa_v.3.0.0");
    Info    = new QLabel("Enter Pin");
    //ConfirmLbl = new QLabel("Confirm Password");

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
    b11   = new QPushButton("Del");
    b12   = new QPushButton("Enter");


    b1->setFixedSize(50,50);
    b2->setFixedSize(50,50);
    b3->setFixedSize(50,50);
    b4->setFixedSize(50,50);
    b5->setFixedSize(50,50);
    b6->setFixedSize(50,50);
    b7->setFixedSize(50,50);
    b8->setFixedSize(50,50);
    b9->setFixedSize(50,50);
    b10->setFixedSize(50,50);
    b11->setFixedSize(50,50);
    b12->setFixedSize(50,50);

    A0   = new QPushButton("A0");
    B0   = new QPushButton("B0");
    C0   = new QPushButton("C0");
    D0   = new QPushButton("DO");
    A1   = new QPushButton("A1");
    B1   = new QPushButton("B1");
    C1   = new QPushButton("C1");
    D1   = new QPushButton("D1");    

    A0->setFixedSize(30,22);
    B0->setFixedSize(30,22);
    C0->setFixedSize(30,22);
    D0->setFixedSize(30,22);
    A1->setFixedSize(30,22);
    B1->setFixedSize(30,22);
    C1->setFixedSize(30,22);
    D1->setFixedSize(30,22);

    QVBoxLayout *IDPAD1HALF = new QVBoxLayout;

    IDPAD1HALF->addWidget(A0);
    IDPAD1HALF->addWidget(B0);
    IDPAD1HALF->addWidget(C0);
    IDPAD1HALF->addWidget(D0);


    QVBoxLayout *IDPAD2HALF = new QVBoxLayout;

    IDPAD1HALF->addWidget(A1);
    IDPAD1HALF->addWidget(B1);
    IDPAD1HALF->addWidget(C1);
    IDPAD1HALF->addWidget(D1);

    QVBoxLayout *LineLayout = new QVBoxLayout;

    LineLayout->addWidget(lbl);
    LineLayout->addWidget(Info);
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

    QHBoxLayout *HALFPADS= new QHBoxLayout;

    HALFPADS->addLayout(IDPAD1HALF);
    HALFPADS->addLayout(numpad);

    QHBoxLayout *ALLPADS=new QHBoxLayout;

    ALLPADS->addLayout(HALFPADS);
    ALLPADS->addLayout(IDPAD2HALF);

    QVBoxLayout *main = new QVBoxLayout;

    main->addLayout(LineLayout);
    main->addLayout(ALLPADS);

    connect(A0,SIGNAL(clicked()),this,SLOT(setID1()));
    connect(B0,SIGNAL(clicked()),this,SLOT(setID2()));
    connect(C0,SIGNAL(clicked()),this,SLOT(setID3()));
    connect(D0,SIGNAL(clicked()),this,SLOT(setID4()));
    connect(A1,SIGNAL(clicked()),this,SLOT(setID5()));
    connect(B1,SIGNAL(clicked()),this,SLOT(setID6()));
    connect(C1,SIGNAL(clicked()),this,SLOT(setID7()));
    connect(D1,SIGNAL(clicked()),this,SLOT(setID8()));

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
    connect(b12,SIGNAL(clicked()),this,SLOT(Enter()));

    setLayout(main);
    setWindowTitle("Sue_alfa_v.3.0.0");
}
