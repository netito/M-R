  int num=0; 
  int mapeo=0;
  int cuadro = 0;
  int fila = 0;
  int cuadfil=0; 
  int flaj=0;
  int ruta=0;
  char tecla =0;
  int gris=0; 
  #include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,13,10,9,8);
#include <Keypad.h>
const byte ROWS = 4;// Four rows
const byte COLS = 2;// Three columns
// Connect keypad ROW1, ROW2, ROW3 and ROW4 to these Arduino pins.
byte rowPins[ROWS] = {7,6,5,4}; 
// Connect keypad COL1, COL2 to these Arduino pins.
byte colPins[COLS] = {3,2};//el pin 0 no se puede usar es el rx de upload 
char keys[ROWS][COLS]{
  {'1','2',},
  {'4','5',},
  {'7','8',},
  {'*','0'}
};
Keypad kpd = Keypad(makeKeymap(keys),rowPins, colPins, ROWS, COLS);
 
int numero;
int a;
int b;
int c;
int d= 1;
int e;
 void setup(){
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Micro-Ritmia");
  lcd.setCursor(0,1);
  lcd.print("V.1");
  delay(1500);
  lcd.clear();
  }
  int potPin = 0;
  int val = 0;
   //----------------------------------------------------------------------------
   void loop(){
     /*Serial.println("fgfgfg"); 
    delay(1000); */
    if(flaj==0){//anti grrrr
     Serial.write(23);//23 bpm
     delay(1);
     flaj=1;}
    tecla = kpd.getKey();
    if(tecla=='0'){//SYNQ
     callSynq();}
      if(tecla=='*'){//CMD e IDE 
     comandIde();} 
  if(tecla=='1'){//BPM 
 for (int cuebpm = 0; cuebpm <  10 ; cuebpm++) {
   Serial.write(12);  
  }
   int val = map(analogRead(potPin),0,1023,13,32);
    Serial.write(val);//envio al RX
     delay(1);  
   BPM();}
     if(ruta==1){//a BPM no a comandIde 
  BPM();}
   if(ruta==2){//a comandIde no a Bpm 
  comandIde();}  
    } 
    
    void BPM(){
    ruta=1;//refresh lcd
    int valLCD= analogRead(potPin);//sin map para usar la función
    lcd.display();
    //lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("BPM =           ");
    lcd.setCursor(6,0);
    float math=valLCD/2+12;//map hecho en casa
    int math2=math;
    lcd.print(math2);
    lcd.setCursor(0,1);
    lcd.print("                ");
    }  
    
    void  comandIde(){
    ruta=2;//LCD refresh
    lcd.display();
    //lcd.clear();//no usar borra todo
    lcd.setCursor(0,0);
    lcd.print("ALGORITMO = ");
    lcd.setCursor(12,0);

 tecla = kpd.waitForKey();//solo entra al comand una vez, cuando tecleo el cmd
 numero=tecla-48;//convertidor de char a numero
 a= numero;
 lcd.println(a);
 lcd.setCursor(13,0);
 //lcd.println("   ");//blank
 a=a*10;//que 12 sea 12 real
 tecla  = kpd.waitForKey();
 numero=tecla -48;
 b= numero;
 lcd.println(b);
 lcd.setCursor(14,0);
 lcd.println("  ");
 c=a+b;//c= número real (no char) de dos dígitos
  /*if(e!=c){//solo pase por callsynq 1 vez (al cambio de comand)
  e=c;
  d=1;}*/
   
    if(c==22){
    /*Serial.println("fgfgfg"); 
    delay(10000);*/
    lcd.setCursor(0,1);
    lcd.print("a 2:1357 50%2468");//41 
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(40);  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(1);//ide 
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(40);  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(3);//ide 
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(40);  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(5);//ide 
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(40);  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(7);//ide 
    delay(1);}
     for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(41);  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(2);//ide 
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(41);  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(4);//ide 
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(41);  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(6);//ide 
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(41);  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(8);//ide 
    delay(1);
    } 
    }

    if(c==15){
    lcd.setCursor(0,1);
    lcd.print("SYNQ!!!          ");//40
    Serial.write   (249);
    delay( 123 );//delay del rx synq
    int val = map(analogRead(potPin),0,1023,12,32);
    Serial.write(val);//envio al RX
    delay(1);
    } 

    if(c==12){//TX a 3 rx (1, 2 y 3) simultaneamente?  
    lcd.setCursor(0,1);
    lcd.print("a3:147,258,36   ");//40 y 46 
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(40 );//0% ch1  
    //Serial.print(40 ); 
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(1);//ide 
    delay(1);} 
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(47);//33% ch2  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(2);//ide ch 2
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(48);//66% ch3  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(3);//ide ch3
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(40);//0% ch4  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(4);//ide ch4
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(47 );//33%   
    //Serial.print(40 ); 
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(5); 
    delay(1);} 
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(48);//66% 
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(6); 
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(40);//0%  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(7); 
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(47);//33%  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(8); 
    delay(1);
     }
    }

    if(c==28){//TX a 3 rx (1, 2 y 3) simultaneamente?  
    lcd.setCursor(0,1);
    lcd.print("8 metr a CERO %");//40 y 46 
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(40 );//0% ch1  
    //Serial.print(40 ); 
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(1);//ide (ch1)
    delay(1);} 
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(40);//0% ch2  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(2);//ide ch 2
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(40);//0% ch3  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(3);//ide ch 3
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(40);//0% ch4  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(4);//ide ch 4
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(40 );//0% ch1  
    //Serial.print(40 ); 
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(5);//ide (ch1)
    delay(1);} 
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(40);//0% ch2  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(6);//ide ch 2
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(40);//0% ch3  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(7);//ide ch 3
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(40);//0% ch4  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(8);//ide ch 4
    delay(1);
    }
    }
   
    if(c==44){//TX a 4 rx (1, 2, 3, 4) simultaneamente?  
    lcd.setCursor(0,1);
    lcd.print("a 4:15,26,37,48"); 
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(40 );//0%   
    //Serial.print(40 ); 
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(1);//ide (ch1)
    delay(1);} 
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(49);//25%   
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(2);//ide ch 2 
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(45);//50% ch3  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(3);//ide ch 3
    delay(1);} 
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(50);//75% ch4  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(4);// 
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(40 );//0%   
    //Serial.print(40 ); 
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(5); 
    delay(1);} 
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(49);//25%   
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(6); 
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(45);//50% ch3  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(7); 
    delay(1);} 
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(50);//75% ch4  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(8); 
    delay(1);
    }
    }

    if(c==55){//TX a 5 rx (1, 2, 3, 4, 5) simultaneamente?  
    lcd.setCursor(0,1);
    lcd.print("a5:16,2,37,4,58 ");  
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(40 );//0%   
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(1);//ide (ch1)
    delay(1);} 
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(51);//20%   
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(2);//ide ch 2 
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(52);//40% ch3  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(3);//ide ch 3
    delay(1);} 
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(53);//60% ch4  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(4);// 
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(54);//80% ch5  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(5);// 
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(40);// 20%  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(6);//ide ch 3
    delay(1);} 
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(52);  //60%
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(7);  
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(54); //80%
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(8);// 
    delay(1);
    }
    }

    if(c==42){//TX a 6 rx (1, 2, 3, 4, 5, 6) simultaneamente?  
    lcd.setCursor(0,1);
    lcd.print("a6:17,4,2,58,3,6");  
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(40 );//0%   
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(1);//ide (ch1)
    delay(1);} 
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(55);//16.6%   
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(4);//ide ch 2 
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(47);//33% ch3  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(2);//ide ch 3
    delay(1);} 
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(56);//49.9% ch4  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(5);// 
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(48);//66% ch5  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(3);// 
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(57);//83.3% ch5  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(6);// 
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(40 );//0%   
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(7); 
    delay(1);} 
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(48);//66%
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(8); 
    delay(1);
    }
    
    }

    if(c==77){//TX a 6 rx (1, 2, 3, 4, 5, 6) simultaneamente?  
    lcd.setCursor(0,1);
    lcd.print("a7:18,234567    ");  
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(40 );//0%   
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(1);//ide (ch1)
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(58);//14.29%   
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(2);//ide ch 2 
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(59);//42.87%  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(3);//ide ch 3
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(60);//42.87% ch4  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(4);// 
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(61);//57.16% ch5  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(5);// 
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(62);//71.45% ch5  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(6);// 
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(63);//85.74% ch5  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(7);// 
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(40);//0% ch5  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(8);// 
    delay(1);
    }
    } 

    if(c==88){//TX a 6 rx (1, 2, 3, 4, 5, 6) simultaneamente?  
    lcd.setCursor(0,1);
    lcd.print("a 8:12345678    ");  
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(40 );//0%   
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(1);//ide (ch1)
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(64);//12.50%   
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(2);//ide ch 2 
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(49);//25%  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(3);// 
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(65);//37.50%  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(4);// 
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(41);//50%   
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(5);// 
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(66);//62.50% ch5  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(6);// 
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(50);//75% ch5  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(7);// 
    delay(1);}
    for (int txlup = 0; txlup < 200; txlup++) {
    Serial.write(67);//87.50% ch5  
    delay(1);//NO VARIAR ESTE VALOR
    Serial.write(8);// 
    delay(1);
    /*if(d==1){
    callSynq();}*/
    }
    }

    if(c==24){
    ruta=1;}//SALIDA a BPM ....synq
    } //llave del void comanIde  
    
    void  callSynq(){
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Sincronizando!!!");
    Serial.write   (249);
    delay( 123 );//delay del rx synq
    int val = map(analogRead(potPin),0,1023,12,32);//regreso al mismo bpm
    Serial.write(val);//envio al RX
    /*lcd.setCursor(0,0);
    lcd.println("fgfgfg");*/
    delay(1);
    d=0;
    }//llave del void callSynq  
      
   
  
   
   
