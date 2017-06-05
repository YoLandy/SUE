#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QMessageBox>
#include <QString>

class mainwindow : public QWidget
{
    Q_OBJECT

public:
    mainwindow(QWidget *parent);
private:
    int PinCode[2][4];
    int num = 0;
    int Pin = 0;
    char pin[4];

    QString  str = "";

    QLabel      *lbl;
    QLineEdit   *line;

    QCheckBox   *cb1;
    QCheckBox   *cb2;

    QPushButton *ok;
    QPushButton *close;

    QPushButton *b1;
    QPushButton *b2;
    QPushButton *b3;
    QPushButton *b4;
    QPushButton *b5;
    QPushButton *b6;
    QPushButton *b7;
    QPushButton *b8;
    QPushButton *b9;
    QPushButton *b10;
    QPushButton *b11;
    QPushButton *b12;

    void Inting(char a){
        int c = a - '0';
        this->PinCode [Pin] [num] = c;
        if(num == 4){
            str = "";
            num = 0;
            Pin++;
        }
        pin[num] = a;
        str=str+ pin [num];
        num++;
        line->setText(str);
    }

public slots:

    void setValue1(){
       Inting('1');
    }
    void setValue2(){
       Inting('2');
    }
    void setValue3(){
       Inting('3');
    }
    void setValue4(){
       Inting('4');
    }
    void setValue5(){
       Inting('5');
    }
    void setValue6(){
       Inting('6');
    }
    void setValue7(){
       Inting('7');
    }
    void setValue8(){
       Inting('8');
    }
    void setValue9(){
       Inting('9');
    }
    void setValue0(){
       Inting('0');
    }
    void DeleteLastSimbol(){
        if(num!=0){
            num=num-1;
            str = "";
            for(int i=0; i<num; i++){
                str = str+pin[i];
            }
            line->setText(str);
        }
    }

};

#endif // MAINWINDOW_H
