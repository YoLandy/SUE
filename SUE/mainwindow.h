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
#include <QThread>
#include <mmapGpio.h>

class Sleeper: public QThread
{
    public:
        static void msleep(int ms)
        {
            QThread::msleep(ms);
        }
};

class mainwindow : public QWidget
{
	Q_OBJECT

public:
	mainwindow(QWidget *parent);
private:
	int PinCode[17][4];
	int num = 0;
	int Pin = 0;
	char pin[4];
	int cells[8] = {0,0,0,0,0,0,0,0};
	int check;
	int id;
	int reset = 0;
	int inter = 0;

    mmapGpio  *rpiGpio;

	QString  str = "";

	QLabel      *lbl;
	QLabel      *Info;

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

	QPushButton *A0;
	QPushButton *B0;
	QPushButton *C0;
	QPushButton *D0;
	QPushButton *A1;
	QPushButton *B1;
	QPushButton *C1;
	QPushButton *D1;

	void SetEnable(int i){
		A0->setEnabled(i);
		B0->setEnabled(i);
		C0->setEnabled(i);
		D0->setEnabled(i);
		A1->setEnabled(i);
		B1->setEnabled(i);
		C1->setEnabled(i);
		D1->setEnabled(i);
	}

	void CheckPin() { //сравниваем два пароля (по одной цифре из каждого массива) 
		for (int i = 0; i < 4; i++) {
            int  a = PinCode [Pin-1] [i];// Serial.println(a);
			int  b = PinCode [Pin] [i];// Serial.println(b);
			if (a != b)
			{
				check = 0;
				//Serial.print (i);
				//Serial.println ("error");
				break;
			}
			
			else
			{
				//Serial.print (i);
				//Serial.println ("true");
				check = 1; //!!!!!!!!!!!!!!!!!!!!!!!!!!!иногда применяется как тру/фолс
			}
		}
	}

	void OpenDoor(){
		for(int i=0; i<90; i++){
			rpiGpio->writePinHigh(14);
            Sleeper::msleep(800);
			rpiGpio->writePinLow(14);
            Sleeper::msleep(800);
		}		
	}
	void CloseDoor(){
		for(int i=0; i<90; i++){
			rpiGpio->writePinHigh(14);
            Sleeper::msleep(400);
			rpiGpio->writePinLow(14);
            Sleeper::msleep(400);
		}	
	}

	void Inting(char a){
		int c = a - '0';

        rpiGpio->writePinHigh(4);

        if(num == 3){
			b12->setEnabled(1);
		}
		else{
			b12->setEnabled(0);
        }

        if(num == 3 && Pin % 2 == 0){
             if(a != 'r'){
                this->PinCode [Pin] [num] = c;
             }
             CheckPin();
             if(check == 1){
                 Info->clear();
                 Info->setText("Repeated True");
                 b12->setEnabled(1);
             }
             else{
                 Info->clear();
                 Info->setText("Repeated Wrong");
                 b12->setEnabled(0);
                 cells[id] = 0;
             }
         }

        if(cells[id] == 0 ){
            if(a != 'r'){
                this->PinCode [Pin] [num] = c;
            }

			if (inter == 1 && Pin % 2 == 1){
				num++;
				pin[num] = a;
				str=str + pin [num];
				line->setText(str);

				Info->clear();
				Info->setText("Confirm Password");

				line->clear();
				line->setText("");

				Pin++;
				reset = 1;
				inter = 0;
				num = 0;
				str = "";
			}

            if(inter == 1 && Pin % 2 == 0){
                num++;
                pin[num] = a;
                str=str + pin [num];
                line->setText(str);

				Info->clear();
				Info->setText("Enter ID");
				SetEnable(1);

                cells[id] = 1;
                reset = 1;
                inter = 0;
                num = 0;
                str = "";
			}
		}	

		else{
            if(a != 'r'){
                this->PinCode [Pin+1] [num] = c;
            }

            Info->clear();
			Info->setText("Enter Your Saved Pin");

			if (num == 3)
			{
                Pin++;
                CheckPin();
                if (check == 1)
				{
					Info->clear();
					Info->setText("Open Door");
                    cells[id] = 0;
                    reset = 1;
                    inter = 0;
                    num = 0;
                    str = "";
				}
				else{
                    Info->clear();
                    Info->setText("Wrong Pin");
                    reset = 1;
                    inter = 0;
                    num = 0;
                    str = "";
				}
			}
		}
		if(reset == 0){
			pin[num] = a;
			str=str + pin[num];
			num++;
		}
		else{
            num=0;
			str = "";
			reset = 0;
		}
		line->setText(str);
	}

	void Incilisation(int i){
		Pin = i*2-1;
		id = i;

		A0->setEnabled(0);
		B0->setEnabled(0);
		C0->setEnabled(0);
		D0->setEnabled(0);
		A1->setEnabled(0);
		B1->setEnabled(0);
		C1->setEnabled(0);
		D1->setEnabled(0);
	}

public slots:

	void setID1(){
		Incilisation(1);
	}
	void setID2(){
		Incilisation(2);
	}
	void setID3(){
		Incilisation(3);
	}
	void setID4(){
		Incilisation(4);
	}
	void setID5(){
		Incilisation(5);
	}
	void setID6(){
		Incilisation(6);
	}
	void setID7(){
		Incilisation(7);
	}
	void setID8(){
		Incilisation(8);
	}

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
			Info->clear();
			Info->setText("Enter PIN");
			line->setText(str);
		}
	}
	void Enter(){
		inter = 1;
		Inting('r');
	}

};

#endif // MAINWINDOW_H
