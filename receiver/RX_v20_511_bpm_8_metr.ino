// Advanced Microcontroller-based Audio Workshop
//
// http://www.pjrc.com/store/audio_tutorial_kit.html
// https://hackaday.io/project/8292-microcontroller-audio-workshop-had-supercon-2015
// 
// Part 2-3: Playing Samples

// WAV files converted to code by wav2sketch
#include "AudioSampleLa.h"       //audios en RAM  
#include "AudioSampleC.h"         
#include "AudioSampleE.h"         
#include "AudioSampleG.h"          
#include "AudioSampleTi.h"
#include "AudioSampleTd.h"
#include "AudioSampleTf.h"
#include "AudioSampleBell2w.h"  


///////////////////////////////////
// copy the Design Tool code here
///////////////////////////////////
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlayMemory          playMem6;       //xy=62,714.3889255523682
AudioPlayMemory          playMem7;       //xy=62,781.944561958313
AudioPlayMemory          playMem4;       //xy=64.01042175292969,544.0000019073486
AudioPlayMemory          playMem2;       //xy=64.76040649414062,415.75000858306885
AudioPlayMemory          playMem3;       //xy=65.01041412353516,465.5000057220459
AudioPlayMemory          playMem5;       //xy=65.87152099609375,649.8055791854858
AudioPlaySdWav           playSdWav2;     //xy=69,841.1944789886475
AudioPlayMemory          playMem1;       //xy=82.51041412353516,358.5000114440918
AudioMixer4              mixer1; //xy=304.51038360595703,458.75002098083496
AudioMixer4              mixer2;         //xy=313.7881774902344,575.0277996063232
AudioMixer4              mixer3;         //xy=463.73260498046875,502.94455337524414
AudioFilterBiquad        biquad2;        //xy=594.4560737609863,564.4560375213623
AudioFilterBiquad        biquad1;        //xy=629.3187217712402,465.1519842147827
AudioMixer4              mixer4;         //xy=772.2338829040527,527.7893180847168
AudioOutputI2S           i2s2; //xy=924.5937881469727,527.3889789581299
AudioConnection          patchCord1(playMem6, 0, mixer2, 1);
AudioConnection          patchCord2(playMem7, 0, mixer2, 2);
AudioConnection          patchCord3(playMem4, 0, mixer1, 3);
AudioConnection          patchCord4(playMem2, 0, mixer1, 1);
AudioConnection          patchCord5(playMem3, 0, mixer1, 2);
AudioConnection          patchCord6(playMem5, 0, mixer2, 0);
AudioConnection          patchCord7(playSdWav2, 0, mixer2, 3);
AudioConnection          patchCord8(playMem1, 0, mixer1, 0);
AudioConnection          patchCord9(mixer1, 0, mixer3, 0);
AudioConnection          patchCord10(mixer2, 0, mixer3, 1);
AudioConnection          patchCord11(mixer3, biquad1);
AudioConnection          patchCord12(mixer3, 0, mixer4, 1);
AudioConnection          patchCord13(mixer3, biquad2);
AudioConnection          patchCord14(biquad2, 0, mixer4, 2);
AudioConnection          patchCord15(biquad1, 0, mixer4, 0);
AudioConnection          patchCord16(mixer4, 0, i2s2, 0);
AudioConnection          patchCord17(mixer4, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=805.5659942626953,655.8889055252075
// GUItool: end automatically generated code
 
  //unsigned long currentMillis = millis();//aqui se incrementa el currentmilis  
  //int lock=0;
  int mapeo=1;
  int accel=0;
  int flagbpm=0;
  int flagcmd=0;
  int cmdactual=0;
  unsigned long subd=0;
  int comadnum=0;
  int incomingByte;
  int incomingBy;
  float tz=0;
   int aa= 0; 
  unsigned long delai= 0;//tiene q ser uns long
  unsigned long delai2= 0;//para q entre BPM en el G, tpo 1
  unsigned long milisinicio=0;
  unsigned long currentMillis2=0;
  int led = 13; 
  int cc=0; 
  int compas=1;
#define HWSERIAL Serial1
// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14
int boton = 2;
int mapi  =0;
void setup() {
   HWSERIAL.begin(9600);
  AudioMemory(10);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
   SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
 if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  delay(1000);
   mixer1.gain(0, 0.6); //metr La, mixer1, los 4 canales 0-3
  mixer1.gain(1, 0.6); //metr c
  mixer1.gain(2, 0.6); //metr e
   mixer1.gain(3,0.6);  //metr g
 
  mixer2.gain(0, 0.4); //metr La Clásico tpo fuerte
   mixer2.gain(1,0.7);   //metr La Clásico tpo intermedio
  mixer2.gain(2,1.0);   //metr La Clásico tpo débil
   mixer2.gain(3,0.4);   //SD Card
  mixer3.gain(0,0.8);   // mtr maschine
  mixer3.gain(1,0.9);   // mtr clásicos (mazel)
  biquad1.setLowpass(0, 800, 0.54);
   biquad1.setLowpass(1, 800, 1.3);
   biquad1.setLowpass(2,  800, 0.54);
   biquad1.setLowpass(3,  800, 1.3);
  biquad2.setHighpass(0, 3000, 0.54);
   biquad2.setHighpass(1, 3000, 1.3);
   biquad2.setHighpass(2,  3000, 0.54);
   biquad2.setHighpass(3,  3000, 1.3);
     mixer4.gain(0,1.0);   // lowpass filter
    mixer4.gain(1,0.8 );   // mtr directo sin process
     mixer4.gain(2,1.2);   // highpass filter
 //attachInterrupt(digitalPinToInterrupt(2),idenTif,HIGH);
      pinMode(boton, INPUT);//si no se instala boton genera crackeos por capcitancia
   pinMode(led, OUTPUT); 
 }//llave del void
 
 int ide=1;
 int i=0;
 int flag=0; 
  
 //-----------000000000000-----------------
 void loop() {
   while(HWSERIAL.available()>0){
  incomingByte = HWSERIAL.read();}
  delay(.8);
    mapeo = map(incomingByte,12,32,60,511);//mapeo=BPM, aqui nace el bpm, solo del 12 al 32 se vuelven bpm ok
            //Serial.println (incomingByte);
     if(incomingByte ==0 || incomingByte ==254||incomingByte ==255||incomingByte ==250){ //a 233 bpm (numeros raros)
      //Serial.println (incomingByte); 
   mapeo =223;} //quita el grrrr del tx upload 223 bpm 
   if(incomingByte>=12&&incomingByte<=20){//contratiempo solo entre 15 y 146 BPM!!!
    mixer2.gain(1,0.9);}
    else   
    {mixer2.gain(1,0.0);}
    if(incomingByte==-42||incomingByte==-25){// filtro
       mapeo=223;}
       //Serial.println (incomingByte);
    if(incomingByte>=1&&incomingByte<=11){ //filtro ide no a bpm 
      mapeo=mapi;}  
      if(incomingByte>=40&&incomingByte<=248){ // Rango de comAnd (filtro cmd no a bpm) 
      mapeo=mapi;  
    comadnum=incomingByte;}//en renglón 234  checa IDE y en renglón 373 envia a subrutina cmd
      //Serial.println (comadnum);}
    mapi=mapeo;//devuelve mapi el valor 
    if( incomingByte == 249) {  //a subrutina sync
   //mapeo=mapeo;
   syncMe();}
   
 //--------------00000000000000---------
 //  I D E
  // PROGRAMAR IDE ojo pierde el sync
  if(digitalRead (boton)==1){ 
    delay( 300);//debounce
    if(ide ==1){ //decir canal (ide)
     playSdWav2.play("1.WAV");}
    if(ide ==2){  
     playSdWav2.play("2.WAV");}
    if(ide ==3){  
     playSdWav2.play("3.WAV");}
    if(ide ==4){  
     playSdWav2.play("4.WAV");}
    if(ide ==5){  
     playSdWav2.play("5.WAV");}
    if(ide ==6){  
     playSdWav2.play("6.WAV");}
     if(ide ==7){ 
     playSdWav2.play("7.WAV");}
     if(ide ==8){  
     playSdWav2.play("8.WAV");}
     if(ide ==9){  
     playSdWav2.play("9.WAV");}
     if(ide ==10){  
     playSdWav2.play("10.WAV");}
     if(ide ==11){  
     playSdWav2.play("11.WAV");}
     if(ide ==12){  
     playSdWav2.play("12.WAV");}
     if(ide ==13){  
     playSdWav2.play("13.WAV");}
     if(ide ==14){  
     playSdWav2.play("14.WAV");}
     if(ide ==15){  
     playSdWav2.play("15.WAV");}
     if(ide ==16){  
     playSdWav2.play("16.WAV");}
     if(ide ==17){  
     playSdWav2.play("17.WAV");
     }} 
    
     //----------- programar nuevo ide-----------
     if(digitalRead (boton)==1){ 
      delay( 1000);  
     if(digitalRead (boton)==1){
     playSdWav2.play("1.WAV");
     delay(1000);
      if(digitalRead (boton)==0){ //fijar nuevo ide
      ide=1;}} 
      if(digitalRead (boton)==1){
     playSdWav2.play("2.WAV");
     delay(1000);
      if(digitalRead (boton)==0){ //fijar nuevo ide
      ide=2;}}
       if(digitalRead (boton)==1){
     playSdWav2.play("3.WAV");
     delay(1000);
      if(digitalRead (boton)==0){ //fijar nuevo ide
      ide=3;}}
       if(digitalRead (boton)==1){
       playSdWav2.play("4.WAV");
     delay(1000);
      if(digitalRead (boton)==0){ //fijar nuevo ide
      ide=4;}}
      if(digitalRead (boton)==1){
       playSdWav2.play("5.WAV");
     delay(1000);
      if(digitalRead (boton)==0){ //fijar nuevo ide
      ide=5;}}
      if(digitalRead (boton)==1){
       playSdWav2.play("6.WAV");
     delay(1000);
      if(digitalRead (boton)==0){ //fijar nuevo ide
      ide=6;}}
      if(digitalRead (boton)==1){
       playSdWav2.play("7.WAV");
     delay(1000);
      if(digitalRead (boton)==0){ //fijar nuevo ide
      ide=7;}}
      if(digitalRead (boton)==1){
       playSdWav2.play("8.WAV");
     delay(1000);
      if(digitalRead (boton)==0){ //fijar nuevo ide
      ide=8;}}
      }  
     //Serial.println(tz);   
  //-------------0000000000------------ 
 int minuto=60000;
  mapeo=mapeo*2;//doble p que coincida con a-g-e-g
  delai=minuto/mapeo; //ej delai=60 bpm=500ms (60000/120=500=1/2 seg)
    if(flagbpm==0){//cambiar bpm en 1er nota d mtrnmo
  delai2=delai;}// ojo cambiar bpm en el tx en tpo3 + o - 
   if(incomingByte - ide ==0){//IDE solo entra a cmd al aparecer # de ide (canal),el# d cmd le antecedio al ide
   comAnd();}//IDE
     //---------------------------------------------------------------
    //Sección de ejecución de comandos
    //0%  
   if(cmdactual==1&&flagbpm==0){//actualizar tz pa estar en synq e nuevo bpm (en vez de cc)
    tz=0;}//40;flagbpm es p cambiar bpm solo en 1er nota d metr despues d el La flagbpm se pone en 1
    //50%  
    if(cmdactual==2&&flagbpm==0){
    tz=delai2*1;}//algorit 41
    //0 - 50%  c/4 compases
    if(cmdactual==3&&flagbpm==0){//algorit 42
    if(compas==2 || compas==10){  
    tz=delai*1;
    }
    if(compas==6 || compas==14){ 
    tz=0;
    }}
    //(50%) 
    if(cmdactual==4&&flagbpm==0){
    tz=delai2*1;}//algorit 45  
    //(0%) 
    if(cmdactual==5&&flagbpm==0){
    tz=0;}//algorit 46
    //(33%)canal 2  
    if(cmdactual==6&&flagbpm==0){
    tz=delai*2/3;}//algorit 47, 2o. trescillo;*2/3=66.66 xq c/metr es x2 x el contratiempo  
    //(66%)canal 3  
    if(cmdactual==7&&flagbpm==0){
    tz=delai*2/3*2;}//algorit 48, 3er trescillo 
     //(25%) 
    if(cmdactual==8&&flagbpm==0){
    tz=delai/2;;}//algorit 49
    //(75%) 
    if(cmdactual==9&&flagbpm==0){
    tz=delai/2*3;}//algorit 50 
    //Serial.println (tz);
    //( 2/5) 
    if(cmdactual==10&&flagbpm==0){
    tz=delai*2/5;}//algorit 51  
    //( 3/5) 
    if(cmdactual==11&&flagbpm==0){
    tz=delai*2/5*2;}//algorit 52 
    //( 4/5) 
    if(cmdactual==12&&flagbpm==0){
    tz=delai*2/5*3;}//algorit 53 
    //( 5/5) 
    if(cmdactual==13&&flagbpm==0){
    tz=delai*2/5*4;}//algorit 54  
    //( 2/6) 
    if(cmdactual==14&&flagbpm==0){
    tz=delai*2/6;}//algorit 55 
    //( 4/6) 
    if(cmdactual==15&&flagbpm==0){
    tz=delai*2/6*3;}//algorit 56 
    //( 6/6) 
    if(cmdactual==16&&flagbpm==0){
    tz=delai*2/6*5;}//algorit 57
    //( 2/7) 
    if(cmdactual==17&&flagbpm==0){
    tz=delai*2/7;}//algorit 58
    //( 3/7) 
    if(cmdactual==18&&flagbpm==0){
    tz=delai*2/7*2;}//algorit 59
    //( 4/7) 
    if(cmdactual==19&&flagbpm==0){
    tz=delai*2/7*3;}//algorit 60
     //( 5/7) 
    if(cmdactual==20&&flagbpm==0){
    tz=delai*2/7*4;}//algorit 61    
     //( 6/7) 
    if(cmdactual==21&&flagbpm==0){
    tz=delai*2/7*5;}//algorit 62   
     //( 7/7) 
    if(cmdactual==22&&flagbpm==0){
    tz=delai*2/7*6;}//algorit 63      
      //( 2/8) 
    if(cmdactual==23&&flagbpm==0){
    tz=delai*2/8;}//algorit 64    
       //( 4/8) 
    if(cmdactual==24&&flagbpm==0){
    tz=delai*2/8*3;}//algorit 65    
       //( 6/8) 
    if(cmdactual==25&&flagbpm==0){
    tz=delai*2/8*5;}//algorit 66 
         //(8/8) 
    if(cmdactual==26&&flagbpm==0){
    tz=delai*2/8*7;}//algorit 67 
        
//-------------000000000000000------------ 
  unsigned long currentMillis = millis();//aqui se crea el currentMillis no se incrementa
  currentMillis2=currentMillis;
  if (currentMillis  == delai  + milisinicio + tz +accel){ //se incrementa el currentMillis
      //if (var >= 80 && var <= 110) ejemplo d dos valores posibles AND
       //Serial.println (delai);
      //Serial.println("fff 5555555555ffffffffgggggggggggggggg");
      digitalWrite(led, HIGH); 
       playMem5.play(AudioSampleBell2w);
       delay(5 );//retardo p que suenen al mismo tpo
       playMem1.play(AudioSampleLa );  //La
      int knob = analogRead(A2);//volumen
      float vol = (float)knob / 1280.0;
      sgtl5000_1.volume(vol);
      delay(1);//anti doble ataque
    
     if(compas==4){       //contador de 4 compases
     playSdWav2.play("4.WAV");}
     if(compas==8){      
     playSdWav2.play("8.WAV");}
     if(compas==12){      
     playSdWav2.play("12.WAV");}
      if(compas==16){      
     playSdWav2.play("16.WAV");
     compas=0;}
      compas++;
      //Serial.println(compas); 
      flagbpm=1;  
       } 
    unsigned long b = delai2  *2;
   if (currentMillis  == b + milisinicio +tz +accel){
   digitalWrite(led, LOW); 
   //playMem6.play(AudioSampleTi);  //.5
   int knob = analogRead(A2);
   float vol = (float)knob / 1280.0;
   sgtl5000_1.volume(vol);
   delay(1);
   }
    unsigned long c = delai2  *3;
   if (currentMillis  == c + milisinicio +tz +accel ){
    playMem2.play(AudioSampleG);  //sol
    playMem7.play(AudioSampleTd);
    digitalWrite(led, HIGH);
    int knob = analogRead(A2);
   float vol = (float)knob / 1280.0;
   sgtl5000_1.volume(vol); 
    delay(1);
    }
    unsigned long d = delai2  *4;
   if (currentMillis  == d + milisinicio +tz+accel ){
    //playMem6.play(AudioSampleTi);  //.5
    digitalWrite(led, LOW);
    int knob = analogRead(A2);
   float vol = (float)knob / 1280.0;
   sgtl5000_1.volume(vol); 
     delay(1);
    }
    unsigned long e = delai2  *5;
   if (currentMillis  == e + milisinicio +tz+accel ){
    playMem3.play(AudioSampleE);  //mi
    playMem7.play(AudioSampleTd);
    digitalWrite(led, HIGH);
    int knob = analogRead(A2);
   float vol = (float)knob / 1280.0;
   sgtl5000_1.volume(vol); 
    delay(1);
    }
    unsigned long f = delai2 *6;
   if (currentMillis  == f + milisinicio + tz +accel ){
    //playMem6.play(AudioSampleTi);  //.5
    digitalWrite(led, LOW);
    int knob = analogRead(A2);
   float vol = (float)knob / 1280.0;
   sgtl5000_1.volume(vol); 
     delay(1);
    } 
    unsigned long g = delai2 *7;
    if (currentMillis  == g + milisinicio + tz +accel ){
    playMem4.play(AudioSampleG);  //sol
    playMem7.play(AudioSampleTd);
    //digitalWrite(led, HIGH);
    int knob = analogRead(A2);
   float vol = (float)knob / 1280.0;
   sgtl5000_1.volume(vol); 
     delay(1);
     } 
     unsigned long h = delai2 *8;
    if (currentMillis  == h + milisinicio + tz +accel){//OJO no lleva tz   
    //playMem6.play(AudioSampleTi);  //.5
    digitalWrite(led, LOW);
    int knob = analogRead(A2);
   float vol = (float)knob / 1280.0;
   sgtl5000_1.volume(vol); 
    delay( 1);
     flagbpm=0;
     //if (cc >0){comAnd();}
    //Serial.println(milisinicio);
     milisinicio = currentMillis - tz; }   //a nota la sin aumentar tz x eso el -
    
     //Serial.println(cc);
   if(currentMillis >  milisinicio + h + tz  ){//tope d seguridad 
    milisinicio=currentMillis - tz;} //a la
   }
   void syncMe(){ //anacruza inicio
      delay( 200 );
      milisinicio=currentMillis2;
      flagbpm=0; 
      compas=15;
       }
    void comAnd(){
      /*comadnum==40, cmdactual=1:0%
        comadnum==41, cmdactual=2:50%
        comadnum==42, cmdactual=3:0-50% c/4compases (sin uso)
        comadnum==43, up down volumen c/x compases (sin uso)
        comadnum==44, up down pm c/x compases (no sirve)
        comadnum==45, cmdactual=4: 50%   
        comadnum==46, cmdactual=5:(0%) 1er trescillo  
        comadnum==47, cmdactual=6:(33%)2o. trescillo   
        comadnum==48, cmdactual=7:(66%)3er. trescillo   
        comadnum==49, cmdactual=8:25%, 2o 16avo  
        comadnum==50, cmdactual=9:75%  4o 16avo
        comadnum==51, cmdactual=10:2/5 20%
        comadnum==52, cmdactual=11:3/5 40%
        comadnum==53, cmdactual=12:4/5 60%
        comadnum==54, cmdactual=13:5/5 80%
        comadnum==55, cmdactual=14:2/6 16.66%
        comadnum==56, cmdactual=15:4/6 49.98%
        comadnum==57, cmdactual=16:6/6 83.30%
        comadnum==58, cmdactual=17:2/7 14.29%
        comadnum==59, cmdactual=18:3/7 28.58%
        comadnum==60, cmdactual=19:4/7 42.87%
        comadnum==61, cmdactual=20:5/7 57.16%
        comadnum==62, cmdactual=21:6/7 71.45%
        comadnum==63, cmdactual=22:7/7 85.74%
        comadnum==64, cmdactual=23:2/8 12.50%
        comadnum==65, cmdactual=24:4/8 37.50%
        comadnum==66, cmdactual=25:6/8 62.50%
        comadnum==67, cmdactual=26:8/8 87.50%
        */
      //subd a 1 (0%)
      if (comadnum==40 ){//# de comand//refresh c/mismo No. de cmd
       cmdactual=1;
       } 
      //subd a 2 (50%)  
      if (comadnum==41){//# de comand//refresh c/mismo No. de cmd
      cmdactual=2;
      }
      //subd 0 - 50%  c/4 compases  
      if (comadnum==42){//# de comand//refresh c/mismo No. de cmd
       cmdactual=3; 
       //Serial.println(compas); 
       }  
       //up down volumen c/x compases  
      if (comadnum==43){//# de comand//refresh c/mismo No. de cmd
      if(compas==2){//entra en el c1
      mixer3.gain(0,0.8);   // mtr maschine
      mixer3.gain(1,1.0);   // mtr clásicos (mazel)    
      }
      if(compas==1 ){ //silencio en el 16
      mixer3.gain(0,0.0);   // mtr maschine
      mixer3.gain(1,0.0);   // mtr clásicos (mazel)    
      }}
      //up down BPM c/x compases  
      if (comadnum==44){//# de comand//refresh c/mismo No. de cmd
      if(compas==2||compas==3||compas==4||compas==6||compas==9||compas==13||compas==16){//entra en el c 1
      accel=delai*2;
      tz=accel;
       //Serial.println(mapeo);  
       }}
       //(50%) canal 2  
      if (comadnum==45){ 
      cmdactual=4;}
       //(0%) 1er trescillo 
      if (comadnum==46){  
      cmdactual=5;}
       //( 33%) 2o. trescillo  
      if (comadnum==47){  
      cmdactual=6;}
       //(66%) 3er trescillo   
      if (comadnum==48){  
      cmdactual=7;}
      //(25%)   
      if (comadnum==49){  
      cmdactual=8;}
      //(75%)   
      if (comadnum==50){  
      cmdactual=9;}
      //(20%, 2/5)   
      if (comadnum==51){ 
      cmdactual=10;}
      //(40%, 3/5)   
      if (comadnum==52){ 
      cmdactual=11;} 
       //(60%, 4/5)   
      if (comadnum==53){ 
      cmdactual=12;}   
       //(80%, 5/5)   
      if (comadnum==54){ 
      cmdactual=13;} 
       //(2/6)   
      if (comadnum==55){ 
      cmdactual=14;}  
       //(4/6)   
      if (comadnum==56){ 
      cmdactual=15;}
      //(6/6)   
      if (comadnum==57){ 
      cmdactual=16;}  
       //(2/7)   
      if (comadnum==58){ 
      cmdactual=17;}  
      //(3/7)   
      if (comadnum==59){ 
      cmdactual=18;}  
       //(4/7)   
      if (comadnum==60){ 
      cmdactual=19;} 
       //(5/7)   
      if (comadnum==61){ 
      cmdactual=20;}
      //(6/7)   
      if (comadnum==62){ 
      cmdactual=21;}    
        //(7/7)   
      if (comadnum==63){ 
      cmdactual=22;}   
        //(2/8)   
      if (comadnum==64){ 
      cmdactual=23;}  
       //(4/8)   
      if (comadnum==65){ 
      cmdactual=24;} 
      //(6/8)   
      if (comadnum==66){ 
      cmdactual=25;}
      //(8/8)   
      if (comadnum==67){ 
      cmdactual=26;}   
      }//llave del void 
       

         
        
      
  
