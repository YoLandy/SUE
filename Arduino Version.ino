#include <UTFT.h>
#include <TouchScreen.h>

extern uint8_t BigFont[];

const uint8_t YP = A1;// вывод Y+ должен быть подключен к аналоговому входу
const uint8_t XM = A2;// вывод X- должен быть подключен к аналоговому входу
const uint8_t YM = 7; // вывод Y-
const uint8_t XP = 6; // вывод X+

TouchScreen TS = TouchScreen(XP, YP, XM, YM, 300);// указываем пины подкулючения к тачу и сопротивление между пинами X Y
UTFT tft(TFT395UNO, A2,A1,A3,A4,A0);

byte servonum [9] = {0b10000000, 0b01000000, 0b00100000, 0b00010000, 0b00001000, 0b00000100, 0b00000010, 0b00000001, 0b00000000};//массив с указанием портов для сервоприводов

int dataPin = 0;  //идет в DS (14 пин на регистре) 
int clockPin = 0; //идет в SH_CP (11 пин на регистре)
int latchPin = 0; //идет в ST_CP (12 пин на регистре)
int low = 8; //это 8ая ячейка в servonum то есть на все выходы идет 0

const char NUMBERS[4][3] =
{
  {'#','0','*'},
  {'9','8','7'},
  {'6','5','4'},
  {'3','2','1'}
};//двойной массив, обозначающий цифру

const int ID[4][2] =
{
  {8,4},
  {7,3},
  {6,2},
  {5,1}
};//двойной массив, обозначающий букву

char b;// при нажатии на кнопку на кейборде записываем эту цифру как b
int pin = 0;//некоторые циклы while(pin == 0) когда просиходит нужное действие pin = 1 и выходим из цикла
int use = 0;//???
int digit;//зачем?
int NumOfCell_1;//индекс ячейки массива для первого пароля
int NumOfCell_2 = NumOfCell_1 + 1;//индекс ячейки массива для сравнительного мароля
int Cells [8] = {0, 0, 0, 0, 0, 0, 0, 0};//для того что бы определять используется ячейка шкафчика или нет (нет = 0, да = 1)
int PinCode [17] [4];//большой массив для всех всех всех паролей
int back;//переменная для того что бы отменять действия
int x;//координата х нажатия на экран
int y;//координата у нажатия на экран 
int p;//переменная что бы выходить из while в функции SchitivanieOfNaghatiya()
int r;//этой переменной обозначают нужный ряд массива
int s;//этой переменной обозначают нужную строку массива

int id;//буквенный индификатор 

int PulseTimeLock = 400;//время импульсоы для закрытия (перевод сервопривода на 0 град.)
int PulseTimeUp = 800;//время импульсов для открытия (перевод сервопривода на 0 град.)

String altb;//tft.print не выводит char по этому надо сначало перевести в стринг (стринг = стринг + чар)

void setup()
{
  //иницилизация и настройка экрана
  tft.InitLCD(0);
  tft.clrScr();
  tft.setFont(BigFont);
  tft.setColor(VGA_WHITE);
  
  //объявление пинов для сдвигового регистра
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT); 
  
  Serial.begin(9600);// открываем Serial порт(для отладки через ПК)
}

void ServoWrite(int x){ // подаем сигнал на нужный порт в регистре (Q0-Q7)
  digitalWrite(latchPin, LOW);//открываем регистр
  shiftOut(dataPin, clockPin, LSBFIRST, servonum[x]);//записывается последовательность 
  digitalWrite(latchPin, HIGH);//закрываем регистр
}

//функция которая закрывет замок
void CloseDoor(int x){
  for (int pos = 0; pos < 90; pos++){ 
	ServoWrite(x);
	delayMicroseconds(PulseTimeLock);
	ServoWrite(low);
	delay(25);
  }
}

//функция которая открывает замок
void OpenDoor(int x){
  for (int pos = 90; pos >= 0; pos--){  
	ServoWrite(x);
	delayMicroseconds(PulseTimeUp);
	ServoWrite(low);
	delay(25);
  }
}

//функция которая считывает х и у нажатия
void SchitivanieOfNaghatiya() // создаем функцию для чтения кнопок
{
  do{
	TSPoint data = TS.getPoint();
	pinMode(XM, OUTPUT);// переводит пины для вывода
	pinMode(YP, OUTPUT);
	if(data.z>0 && data.y < 770){
	  x = data.x;
	  y = data.y;
	  p = 1;
	}
	else if(data.z <= 0){//data.z - это глубина нажатия, если равно 0 то значит его нету
	  p = 0;
	}
  }while(p == 0);
  p = 0;
}

void EnterID() {   //записываем букву ячейки
  SchitivanieOfNaghatiya();
  
  r = (y-200)/142.0;//считываем, на какую часть было нажатие (определяем ряд массива)
  s = (x-250)/420.0;//определяем строку массива
  id = ID[r][s];
}

void EnterNum() { //записывавем цифру
  SchitivanieOfNaghatiya();
  
  r = (y-100)/180.0;//считываем, на какую часть было нажатие (определяем ряд массива)
  s = (x-250)/210.0;//определяем строку массива
  b = NUMBERS[r][s];
}

void Numpad(){
  tft.setColor(VGA_BLACK);
  
  for(int yy = 50; yy < 480; yy=yy+108){
    for(int xx = 10; xx < 320; xx=xx+155){
	  tft.fillRoundRect(xx, yy, xx+150, yy+100);
	}
  }//закрашиваем экран

  tft.setColor(VGA_WHITE);
  tft.print("1       2       3", CENTER, 100);
  tft.print("4       5       6", CENTER, 200);
  tft.print("7       8       9", CENTER, 300);
  tft.print("*       0       #", CENTER, 400);
  
  for(int yy = 70; yy < 480; yy=yy+105){
	for(int xx = 10; xx < 320; xx=xx+105){
	  tft.drawRoundRect(xx, yy, xx+90, yy+90);
	}
  }

}

void Keypad(){
  tft.clrScr();
  tft.print("Enter ID", CENTER, 10);
  tft.print("A0            A1", CENTER, 100);
  tft.print("B0            B1", CENTER, 200);
  tft.print("C0            C1", CENTER, 300);
  tft.print("D0            D1", CENTER, 400);
  
  int i = 0;
  
  for(int yy = 50; yy < 480; yy=yy+108){
	for(int xx = 10; xx < 320; xx=xx+155){
	  tft.drawRoundRect(xx, yy, xx+150, yy+100);
	  if(Cells[i] != 0){
		tft.fillRoundRect(xx, yy, xx+150, yy+100);
	  }
	  i=i+4;
	  Serial.println(i);
	}
	i=i-7;
  }
}

void EnterPin(int x) //записываем пароль
{
  String stars = "";
  pin = 0;
  EnterNum();
  altb = stars + b;
  tft.print(altb, CENTER, 40);
  delay(250);
  stars = stars + "*";
  tft.print(stars, CENTER, 40);
  PinCode [x] [0] = b;
  if(b == '#'){
	back = 1;
  }
  if(back != 1){
	for (int i = 1; i < 4; i++)
	{
		pin = 0;
		EnterNum();
		altb = stars + b;
		tft.print(altb, CENTER, 40);
		delay(250);
		stars = stars + "*";    
	  tft.print(stars, CENTER, 40);
	  PinCode [x] [i] = b;
	  delay(250);
	}
	delay(500);  
	tft.print("                    ", CENTER, 40);
  } 
}

void CheckPin() { //сравниваем два пароля (по одной цифре из каждого массива) 
  for (int i = 0; i < 4; i++) {
	char  a = PinCode [NumOfCell_1] [i];// Serial.println(a);
	char  b = PinCode [NumOfCell_2] [i];// Serial.println(b);
	if (a != b)
	{
	  pin = 0;
	  //Serial.print (i);
	  //Serial.println ("error");
	  break;
	}
	else
	{
	  //Serial.print (i);
	  //Serial.println ("true");
	  pin = 1; //!!!!!!!!!!!!!!!!!!!!!!!!!!!иногда применяется как тру/фолс 
	}
  }
}

void EnterPinTwice(char cell, int cellNum) {   //cell-буква cellNum-номер ячейки
  //Это все для установки пароля, то есть пользователь должен два раза подрят ввести придуманный пароль перед тем как дверь закроется
  tft.print("Create your pin", CENTER, 10);
  delay(500);
  Numpad();
  EnterPin(NumOfCell_1);//записываем основной
  //Serial.println("pin1");
  if(back != 1){
	tft.print("               ", RIGHT, 10);
	tft.print("Repeat your pin", CENTER, 10);
	EnterPin(NumOfCell_2);//записываем сравнительный
	//Serial.println ("pin2");
	if(back != 1){  
	  CheckPin();//сравниваем
	}
	else{
	  pin = 2;
	}

  }
  else{
	pin = 2;
  }
}

void CheckMainPin(int x) { //х - это индекс для массива использования, а так же номер сервопривода который надо открыть/закрыть
  //это уже главный этап, дверь откроется только тогда когда пользователь правильно введет придуманный ранее пароль 
  EnterPin(NumOfCell_2);//записываем в сравнительный массив
  //Serial.println ("pin3");
  if(back != 1){
	CheckPin();

	if (pin == 0) {
	  tft.print("                ", RIGHT, 10);
	  tft.print("WrongPin", CENTER, 10);
	  delay(500);
	}

	else {
	  tft.print("                    ", RIGHT, 10);
	  tft.print ("OpenDoor", CENTER, 10);
	  delay(500);
	  OpenDoor(x);
	  //Serial.print(x);

	  Cells[x] = 0;
	}
  }
}

void TheCellProgramm(char cell, int cellNum, int c)
 //сell как всегда буква, cellNum цифра, c-номер юзания
{
  int num_arr = c + c;//я заметил, что номер массива пароля ровно в два раза больше чем с

  NumOfCell_1 = num_arr;// следовательно сравнительный массив равен с+с+1
  use = Cells [c];

  if (use != 1) { //ветка для установки пароля (вот здесь и понадобился use) :)
  
	Cells [c] = 1;//метим эту ячейку как "в использовании"
	EnterPinTwice(cell, cellNum);
   
	if (pin == 0) {
	  tft.print("                  ", RIGHT, 10);
	  tft.print("Pin repeated wrong", CENTER, 10);//если пароль установили не верно все идет обратно
	  delay(500);
		
	  Cells [c] = 0;
	}
	
	else if(pin == 2){
	  Cells [c] = 0;
	}

	else if(pin == 1){
	  tft.print("               ", RIGHT, 10);
	  tft.print ("Password saved", CENTER, 10);
	  delay(500);

	  CloseDoor(c);//удивительно! номер юзания равен номеру замка(сервопривода)
	}
  }
  
  else {
	tft.print("Enter your saved pin", CENTER, 10);
	Numpad();
	CheckMainPin(c);// если юз = 1 то значит мы уже устанавливали пароль 
  }
}

void loop()
{
  pin = 0;//обнуляем
  back = 0;
  
  Keypad();
  EnterID();//вводим id
  //tft.clrScr();
  switch (id) {
	case 1:
		tft.print("A0", LEFT, 10);
		delay(1000);
		TheCellProgramm ('A', 0, 0);//A0
	
	break;
	
	case 2:
	
		tft.print("B0", LEFT, 10);
		delay(1000);
		TheCellProgramm ('B', 0, 1);//В0  
	
	break;
	
	case 3:
	
		tft.print("C0", LEFT, 10);
		delay(500);
		TheCellProgramm ('C', 0, 2);//C0
	
	break;
	
	case 4:
		tft.print("D0", LEFT, 10);
		delay(1000);
		TheCellProgramm ('D', 0, 3);//D0
	break;
	
	case 5:
	
		tft.print("A1", LEFT, 10);
		delay(1000);
		TheCellProgramm ('A', 1, 4);//А1
	
	break;
	
	case 6:
	
		tft.print("B1", LEFT, 10);
		delay(1000);
		TheCellProgramm ('B', 1, 5);//В1
	
	break;
	
	case 7:
	
		tft.print("C1", LEFT, 10);
		delay(500);
		TheCellProgramm ('C', 1, 6);//C1
	  
	break;
	
	case 8:
	  
		tft.print("D1", LEFT, 10);
		delay(1000);
		TheCellProgramm ('D', 1, 7);//D1
	
	break;
	}
}


