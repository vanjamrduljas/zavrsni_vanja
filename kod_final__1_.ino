

//definiramo varijable

//vrijeme
#define select 51
#define Right 50
#define Start 52

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  
byte pos,actPos;
char timer_vrijeme[4]={'0','0','0','0'};
unsigned long time1=0,time2=0; 
bool mask=0,toggle=0;

// rezultat domaci
#define aPin 2        
#define bPin 3  
#define cPin 4  
#define dPin 5  
#define ePin 6  
#define fPin 7  
#define gPin 8  

#define c1Pin 9  
#define c2Pin 10
#define c3Pin 11 
#define c4Pin 12 

#define bt_up     A0
#define bt_down   A1




//rezultat gosti
#define aPin2 23        
#define bPin2 25  
#define cPin2 22  
#define dPin2 24  
#define ePin2 26  
#define fPin2 27  
#define gPin2 28  

#define c1Pin2 29  
#define c2Pin2 31 
#define c3Pin2 33 
#define c4Pin2 30 

#define bt_up2     A7
#define bt_down2   A6



long Counter=0;
long Counter_gosti=0;

int flag1=0, flag2=0, timer=0;
int flag1_gosti=0, flag2_gosti=0, timer_gosti=0;

int Common = 1; 
int On, Off, Off_C; 
int DTime = 4; 

int Common_gosti = 1; 
int On_gosti, Off_gosti, Off_C_gosti; 
int DTime_gosti = 4; 


void setup(){ 

  //vrijeme
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("     Vrijeme:     ");
  lcd.setCursor(5,1);
  lcd.print("00:00      ");
  pinMode(select,INPUT_PULLUP);
  pinMode(Right,INPUT_PULLUP);
  pinMode(Start,INPUT_PULLUP);
  
  time1=millis();
  time2=millis();
 
 
 //rezultat domaći
 pinMode(bt_up,    INPUT_PULLUP);
 pinMode(bt_down,  INPUT_PULLUP);
 

 pinMode(aPin, OUTPUT);
 pinMode(bPin, OUTPUT);
 pinMode(cPin, OUTPUT);
 pinMode(dPin, OUTPUT);
 pinMode(ePin, OUTPUT); 
 pinMode(fPin, OUTPUT);
 pinMode(gPin, OUTPUT);

 pinMode(c1Pin, OUTPUT);
 pinMode(c2Pin, OUTPUT);
 pinMode(c3Pin, OUTPUT);
 pinMode(c4Pin, OUTPUT);




  pinMode(bt_up2,    INPUT_PULLUP);
 pinMode(bt_down2,  INPUT_PULLUP);
 

 pinMode(aPin2, OUTPUT);
 pinMode(bPin2, OUTPUT);
 pinMode(cPin2, OUTPUT);
 pinMode(dPin2, OUTPUT);
 pinMode(ePin2, OUTPUT); 
 pinMode(fPin2, OUTPUT);
 pinMode(gPin2, OUTPUT);

 pinMode(c1Pin2, OUTPUT);
 pinMode(c2Pin2, OUTPUT);
 pinMode(c3Pin2, OUTPUT);
 pinMode(c4Pin2, OUTPUT);

 if(Common==1){On=0, Off=1, Off_C=0;} 
      else{On=1, Off=0, Off_C=1;} 

 if(Common==1){On_gosti=0, Off_gosti=1, Off_C_gosti=0;} 
       else{On_gosti=1, Off_gosti=0, Off_C_gosti=1;} 


}

void loop(){  
//vrijeme
if((unsigned long)millis()-time1>200&&pos>0)
  {
    if(toggle)
    {
      toggle=0;
      actPos=pos;
      if(actPos>2)actPos++;
      lcd.setCursor(4+actPos,1);
      lcd.print(' ');
    }else
    {
      toggle=1;
      disp();  
    }
    time1=millis();
  }else if(pos==0)disp();

  
  if((unsigned long)millis()-time2>1000&&mask==1)
  {
    disp();
    if(timer_vrijeme[0]=='0'&&timer_vrijeme[1]=='0'&&timer_vrijeme[2]=='0'&&timer_vrijeme[3]=='0')
    {
      
      mask=0;
      lcd.setCursor(4,1);
      lcd.print("Finished");
      delay(500);
      lcd.setCursor(4,1);
      lcd.print("            ");
      delay(500);
      lcd.setCursor(4,1);
      lcd.print("Finished");
      delay(500);
      lcd.setCursor(4,1);
      lcd.print("            ");
      delay(500);
      disp();
    }else timer_vrijeme[3]--;
    if(timer_vrijeme[3]<'0')
    {
      timer_vrijeme[3]='9';
      timer_vrijeme[2]--;
    }
    if(timer_vrijeme[2]<'0')
    {
      timer_vrijeme[2]='5';
      timer_vrijeme[1]--;
    }
    if(timer_vrijeme[1]<'0')
    {
      timer_vrijeme[1]='9';
      timer_vrijeme[0]--;
    }
    time2=millis();
  }
  //Provjera koji je gumb stisnut
  if(digitalRead(Right)==LOW)
  {
    while(digitalRead(Right)==LOW);
    pos++;
    if(pos>4)pos=0;
  }else if(digitalRead(Start)==LOW)
  {
    while(digitalRead(Start)==LOW);
    mask=mask^1;
    
  }else if(digitalRead(select)==LOW)
  {
    while(digitalRead(select)==LOW);
    if(pos>0)
    {
      
      timer_vrijeme[pos-1]=timer_vrijeme[pos-1]+1;
      if(timer_vrijeme[0]>'5')timer_vrijeme[0]='0';
      if(timer_vrijeme[2]>'5')timer_vrijeme[2]='0';
      if(timer_vrijeme[pos-1]>'9')timer_vrijeme[pos-1]='0';
    }
  }


// rezultat domaći
if(digitalRead (bt_up) == 0){ 
if(flag1==0){ flag1=1;

Counter = Counter+1;
if(Counter>9999){Counter=0;} 
 }
}else{flag1=0;}

if(digitalRead (bt_down) == 0){ 
if(flag2==0){ flag2=1;

Counter = Counter-1;
if(Counter<0){Counter=9999;} 
 }  
}else{flag2=0;}



//gosti
if(digitalRead (bt_up2) == 0){ 
if(flag1_gosti==0){ flag1_gosti=1;

Counter_gosti = Counter_gosti+1;
if(Counter_gosti>9999){Counter_gosti=0;} 
 }
}else{flag1_gosti=0;}

if(digitalRead (bt_down2) == 0){ 
if(flag2_gosti==0){ flag2_gosti=1;

Counter_gosti = Counter_gosti-1;
if(Counter_gosti<0){Counter_gosti=9999;} 
 }  
}else{flag2_gosti=0;}



//domaći
showNumber((Counter/1000)%10);
digitalWrite(c1Pin, Common);
delay(DTime);
digitalWrite(c1Pin, Off_C);

showNumber((Counter/100)%10);
digitalWrite(c2Pin, Common);
delay(DTime);
digitalWrite(c2Pin, Off_C);

showNumber((Counter/10)%10);
digitalWrite(c3Pin, Common);
delay(DTime);
digitalWrite(c3Pin, Off_C);

showNumber(Counter%10);
digitalWrite(c4Pin, Common);
delay(DTime);
digitalWrite(c4Pin, Off_C);




//gosti
showNumber_gosti((Counter_gosti/1000)%10);
digitalWrite(c1Pin2, Common_gosti);
delay(DTime_gosti);
digitalWrite(c1Pin2, Off_C_gosti);

showNumber_gosti((Counter_gosti/100)%10);
digitalWrite(c2Pin2, Common_gosti);
delay(DTime_gosti);
digitalWrite(c2Pin2, Off_C_gosti);

showNumber_gosti((Counter_gosti/10)%10);
digitalWrite(c3Pin2, Common_gosti);
delay(DTime_gosti);
digitalWrite(c3Pin2, Off_C_gosti);

showNumber_gosti(Counter_gosti%10);
digitalWrite(c4Pin2, Common_gosti);
delay(DTime_gosti);
digitalWrite(c4Pin2, Off_C_gosti);


}

//vrijeme
void disp()
{
  lcd.setCursor(5,1);
  lcd.print(timer_vrijeme[0]);
  lcd.setCursor(6,1);
  lcd.print(timer_vrijeme[1]);
  lcd.setCursor(7,1);
  lcd.print(':');
  lcd.setCursor(8,1);
  lcd.print(timer_vrijeme[2]);
  lcd.setCursor(9,1);
  lcd.print(timer_vrijeme[3]);
}

//domaći-prikaz
void showNumber(int x){
  
   switch(x){
     case 1: one();   break;
     case 2: two();   break;
     case 3: three(); break;
     case 4: four();  break;
     case 5: five();  break;
     case 6: six();   break;
     case 7: seven(); break;
     case 8: eight(); break;
     case 9: nine();  break;
     default: zero(); break;
   }
}

void one(){
  digitalWrite( aPin, Off);     
  digitalWrite( bPin, On);  
  digitalWrite( cPin, On);  
  digitalWrite( dPin, Off); 
  digitalWrite( ePin, Off); 
  digitalWrite( fPin, Off);
  digitalWrite( gPin, Off);
}

void two(){
  digitalWrite( aPin, On);  
  digitalWrite( bPin, On);  
  digitalWrite( cPin, Off); 
  digitalWrite( dPin, On);     
  digitalWrite( ePin, On);  
  digitalWrite( fPin, Off);
  digitalWrite( gPin, On);
}

void three(){
  digitalWrite( aPin, On);  
  digitalWrite( bPin, On);  
  digitalWrite( cPin, On);  
  digitalWrite( dPin, On);  
  digitalWrite( ePin, Off); 
  digitalWrite( fPin, Off); 
  digitalWrite( gPin, On);
}

void four(){
  digitalWrite( aPin, Off); 
  digitalWrite( bPin, On);  
  digitalWrite( cPin, On);  
  digitalWrite( dPin, Off); 
  digitalWrite( ePin, Off); 
  digitalWrite( fPin, On);
  digitalWrite( gPin, On);
}

void five(){
  digitalWrite( aPin, On);  
  digitalWrite( bPin, Off); 
  digitalWrite( cPin, On);  
  digitalWrite( dPin, On);  
  digitalWrite( ePin, Off); 
  digitalWrite( fPin, On);  
  digitalWrite( gPin, On);
}

void six(){
  digitalWrite( aPin, On);  
  digitalWrite( bPin, Off); 
  digitalWrite( cPin, On);  
  digitalWrite( dPin, On);  
  digitalWrite( ePin, On);  
  digitalWrite( fPin, On);
  digitalWrite( gPin, On);
}

void seven(){
  digitalWrite( aPin, On);  
  digitalWrite( bPin, On);  
  digitalWrite( cPin, On);  
  digitalWrite( dPin, Off); 
  digitalWrite( ePin, Off); 
  digitalWrite( fPin, Off);
  digitalWrite( gPin, Off);
}

void eight(){
  digitalWrite( aPin, On); 
  digitalWrite( bPin, On); 
  digitalWrite( cPin, On); 
  digitalWrite( dPin, On); 
  digitalWrite( ePin, On); 
  digitalWrite( fPin, On); 
  digitalWrite( gPin, On); 
}

void nine(){
  digitalWrite( aPin, On);  
  digitalWrite( bPin, On);  
  digitalWrite( cPin, On);  
  digitalWrite( dPin, On);  
  digitalWrite( ePin, Off); 
  digitalWrite( fPin, On); 
  digitalWrite( gPin, On);
}

void zero(){                 
  digitalWrite( aPin, On); 
  digitalWrite( bPin, On); 
  digitalWrite( cPin, On); 
  digitalWrite( dPin, On); 
  digitalWrite( ePin, On); 
  digitalWrite( fPin, On); 
  digitalWrite( gPin, Off);   
}


//gosti-prikaz
void showNumber_gosti(int x){
  
   switch(x){
     case 1: one_gosti();   break;
     case 2: two_gosti();   break;
     case 3: three_gosti(); break;
     case 4: four_gosti();  break;
     case 5: five_gosti();  break;
     case 6: six_gosti();   break;
     case 7: seven_gosti(); break;
     case 8: eight_gosti(); break;
     case 9: nine_gosti();  break;
     default: zero_gosti(); break;
   }
}

void one_gosti(){
  digitalWrite( aPin2, Off);  
  digitalWrite( bPin2, On);  
  digitalWrite( cPin2, On);  
  digitalWrite( dPin2, Off); 
  digitalWrite( ePin2, Off); 
  digitalWrite( fPin2, Off);
  digitalWrite( gPin2, Off);
}

void two_gosti(){
  digitalWrite( aPin2, On);  
  digitalWrite( bPin2, On);  
  digitalWrite( cPin2, Off); 
  digitalWrite( dPin2, On);     
  digitalWrite( ePin2, On);  
  digitalWrite( fPin2, Off);
  digitalWrite( gPin2, On);
}

void three_gosti(){
  digitalWrite( aPin2, On);  
  digitalWrite( bPin2, On);  
  digitalWrite( cPin2, On); 
  digitalWrite( dPin2, On);  
  digitalWrite( ePin2, Off); 
  digitalWrite( fPin2, Off); 
  digitalWrite( gPin2, On);
}

void four_gosti(){
  digitalWrite( aPin2, Off); 
  digitalWrite( bPin2, On);  
  digitalWrite( cPin2, On);  
  digitalWrite( dPin2, Off); 
  digitalWrite( ePin2, Off); 
  digitalWrite( fPin2, On);
  digitalWrite( gPin2, On);
}

void five_gosti(){
  digitalWrite( aPin2, On);  
  digitalWrite( bPin2, Off);
  digitalWrite( cPin2, On);  
  digitalWrite( dPin2, On);  
  digitalWrite( ePin2, Off); 
  digitalWrite( fPin2, On);  
  digitalWrite( gPin2, On);
}

void six_gosti(){
  digitalWrite( aPin2, On);  
  digitalWrite( bPin2, Off); 
  digitalWrite( cPin2, On);  
  digitalWrite( dPin2, On);  
  digitalWrite( ePin2, On);  
  digitalWrite( fPin2, On);
  digitalWrite( gPin2, On);
}

void seven_gosti(){
  digitalWrite( aPin2, On);  
  digitalWrite( bPin2, On);  
  digitalWrite( cPin2, On);  
  digitalWrite( dPin2, Off); 
  digitalWrite( ePin2, Off); 
  digitalWrite( fPin2, Off);
  digitalWrite( gPin2, Off);
}

void eight_gosti(){
  digitalWrite( aPin2, On); 
  digitalWrite( bPin2, On); 
  digitalWrite( cPin2, On); 
  digitalWrite( dPin2, On); 
  digitalWrite( ePin2, On); 
  digitalWrite( fPin2, On); 
  digitalWrite( gPin2, On); 
}

void nine_gosti(){
  digitalWrite( aPin2, On);  
  digitalWrite( bPin2, On);  
  digitalWrite( cPin2, On);  
  digitalWrite( dPin2, On);  
  digitalWrite( ePin2, Off); 
  digitalWrite( fPin2, On); 
  digitalWrite( gPin2, On);
}

void zero_gosti(){                 
  digitalWrite( aPin2, On); 
  digitalWrite( bPin2, On); 
  digitalWrite( cPin2, On); 
  digitalWrite( dPin2, On); 
  digitalWrite( ePin2, On); 
  digitalWrite( fPin2, On); 
  digitalWrite( gPin2, Off);   
}
