/* YourDuinoStarter Example: DS1307 Real Time Clock
 - WHAT IT DOES: Set and/or Run DS1307 Real Time Clock
 - SEE the comments after "//" on each line below
 - CONNECTIONS:
   Function  Arduino Pin  Mega Pin
   -         Gnd          Gnd
   +         +5V          +5V
   SDA       Analog A4    20
   SCL       Analog A5    21
 - V1.02 04/26/2015
   Questions: terry@yourduino.com */

/*-----( Import needed libraries )-----*/
#include <Wire.h>
#include <LCD.h> 
#include <LiquidCrystal_I2C.h> 
#include "RTClib.h"
#include <Keypad.h>
#include <SCoop.h>
String show_s(int a,int b,int c,int d);
void menu();
char set_time();
char input_show(int x);
char set_time_year();
char set_time_month();
char set_time_day();
char set_time_hour();
char set_time_minute();
char set_time_second();

char set_clock();
//void set_clock_year();
//void set_clock_month();
//void set_clock_day();
char set_clock_hour();
char set_clock_minute();
char set_clock_second();
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7); // 0x27 is the I2C bus address for an unmodified backpack 
void formatPrint(  int hour, int minute, int second){
     lcd.noBlink();
     lcd.setCursor (4,1); // go to start of 2nd line 
     if(hour<10){
      lcd.print(0);
      lcd.setCursor (5,1); // go to start of 2nd line 
      lcd.print(hour);
     }else
      lcd.print(hour);
     lcd.setCursor(6,1);
     lcd.print(":");
     lcd.setCursor(7,1);
     if(minute<10){
      lcd.print(0);
      lcd.setCursor (8,1); // go to start of 2nd line 
      lcd.print(minute);
     }else
      lcd.print(minute);
       lcd.setCursor(9,1);
       lcd.print(":");
       lcd.setCursor(10,1);
     if(second<10){
      lcd.print(0);
      lcd.setCursor(11,1); // go to start of 2nd line 
      lcd.print(second);
     }else
      lcd.print(second);
}

//String time_list[] = ["Year","Month","Day","Hour","Minute","Second"];
char y[4];  //存储year的数值
int i=0;//循环计数
/**初始时间**/
int py; //year
int pmo; //month
int pd;  //day
int ph;   //hour
int pmi;  //minute
int ps;  //second
/**闹钟时间**/
//int cy = 2015; //year
//int cmo = 5; //month
//int cd = 21;  //day
int ch = 00;   //hour
int cmi = 00;  //minute
int cs = 00;  //second
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
int menu_flag = 0;
int show_flag = 1;    //1是显示，-1是不显示
int switch_flag = 1;    //1是开，-1是关



const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'0','1','2','3'},
  {'4','5','6','7'},
  {'8','9','A','B'},
  {'C','D','E','F'}
};
byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9}; //connect to the column pinouts of the keypad
//initializes an instance of the Keypad class
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

/*-----( Declare objects )-----*/
RTC_DS1307 rtc;    // Create a RealTimeClock object
defineTask(Task1) 
void Task1::setup() { 
  Serial.begin(9600);
  pinMode(10,OUTPUT);
  } 
void Task1::loop() { 

  char key = keypad.getKey();
  if (key == 'F'){
    show_flag = -show_flag;
    menu();
    show_flag = 1;
  }else if(key == 'C'){
    switch_flag = -switch_flag;
    noTone(10); 
  }else if(key == 'D'){
    show_flag = -show_flag;
      lcd.clear();
      lcd.noBlink();
      lcd.setCursor(3,0);
      lcd.print("Alarm Clock"); 
      formatPrint(ch, cmi, cs);
      if(keypad.waitForKey())
        show_flag = -show_flag;
    }

   DateTime nowClock = rtc.now();  // Read data from the RTC Chip

   if(nowClock.hour() == ch && nowClock.minute() == cmi && nowClock.second() == cs && switch_flag == 1)
    {    
             tone(10, 31); 
             key = keypad.getKey();  
             if(key == 'C'){
                switch_flag = -switch_flag;
                noTone(10); 
              }     
    }
}

void setup()   /****** SETUP: RUNS ONCE ******/
{
  Serial.begin(9600); // Set up for Serial Monitor to be able to see this work
  /*----( These lines allow code to work also on Arduino DUE )----- */


  // Put these "//" in front of the line you do NOT want to use
  // following line sets the RTC to the date & time this sketch was compiled
//     rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // May 21, 2015 at 6pm you would call: (use 24 hour time)
  #ifdef AVR
  Wire.begin();
#else
  Wire1.begin(); // Shield I2C pins connect to alt I2C bus on Arduino Due
#endif

  rtc.begin(); // Start the RTC library code
  rtc.adjust(DateTime(2015, 5, 21, 18, 0, 0));
  lcd.begin (16,2); // for 16 x 2 LCD module 
  lcd.setBacklightPin(3,POSITIVE); 
  lcd.setBacklight(HIGH); 
  mySCoop.start(); 
}


void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{ 
  switch(show_flag){
    case 1:{
              DateTime now = rtc.now();  // Read data from the RTC Chip
              //lcd.home (); // set cursor to 0,0   
              lcd.noBlink();
              lcd.setCursor(1,0);
              lcd.print(show_s(now.year(),now.month(),now.day(),1)+' ' +daysOfTheWeek[now.dayOfTheWeek()]); 
              lcd.setCursor (4,1); // go to start of 2nd line 
              if(switch_flag == 1)
                  lcd.print(String(show_s(now.hour(),now.minute(),now.second(),0)+"   o")); 
              else
                  lcd.print(String(show_s(now.hour(),now.minute(),now.second(),0)+"   x"));   
              break;
      }
      case -1:{
              break;
        }
  }
  
  yield();  //本函数必须放在主线的loop循环体中 

}//--(end main loop )---

//显示日期和时间的字符拼合及补零函数
String show_s(int a,int b,int c,int d){
 String s1,s2,s3;
  if(a<10)
    s1 = String('0'+String(a));
  else
    s1 = String(a);
  if(b<10)
    s2 = String('0'+String(b));
  else
    s2 = String(b);
  if(c<10)
    s3 = String('0'+String(c));
  else
    s3 = String(c);
  if(d==1)
    return String(s1+'/'+s2+'/'+s3);
  else
    return String(s1+':'+s2+':'+s3);
  }


//菜单函数
void menu(){
  rmenu:
  char m1,m2;
  lcd.clear();
  lcd.noBlink();
  lcd.setCursor(0,0);
  lcd.print("1.Set_Time"); 
  lcd.setCursor (0,1); // go to start of 2nd line 
  lcd.print("2.Set_Clock"); 
    int f = keypad.waitForKey();
    switch(f){
      case '1':lcd.clear();
               lcd.home();
               lcd.print("<<<<Set_Time>>>>"); 
               m1 = set_time();
               if(m1 == '#')
                   goto rmenu;
               break;

      case '2':lcd.clear();
               lcd.home();
               lcd.print("<<<<Set_Clock>>>>"); 
               m2 = set_clock();
               if(m2 == '#')
                   goto rmenu;
               break;
      default: show_flag = -show_flag; 
               break;
      }
  lcd.clear();
 
  
  }

/**---设置初始时间---**/
char set_time(){
 char t1,t2,t3,t4,t5,t6;
 styear:
  t1 = set_time_year();
  if(t1 == '#')
    return '#';
  Serial.println(py);
 stmonth:
  t2 = set_time_month();
  if(t2 == '#')
    goto styear;
  Serial.println(pmo);
 stday:
  t3 = set_time_day();
  if(t3 == '#')
    goto stmonth;
  Serial.println(pd);
 sthour:
  t4 = set_time_hour();
  if(t4 == '#')
    goto stday;
  Serial.println(ph);
 stminute:
  t5 = set_time_minute();
  if(t5 == '#')
    goto sthour;
  Serial.println(pmi);
  t6 = set_time_second();
  if(t6 == '#')
    goto stminute;
  Serial.println(ps);
  rtc.adjust(DateTime(py, pmo, pd, ph, pmi, ps));
  lcd.clear();
  lcd.setCursor (1,0);
  lcd.print("Press any key!"); 
  lcd.setCursor (3,1);
  lcd.print("Success!"); 
  keypad.waitForKey();
  show_flag = -show_flag;
}

char set_time_year(){
   char k1;
   lcd.clear();
   lcd.home();
   lcd.print("<<<<Set_Time>>>>"); 
   lcd.setCursor (2,1);
   lcd.blink(); 
   lcd.print("Year:"); 
   for(i=0;i<4;i++){
     tYear:
     y[i] = input_show(i+7);
     Serial.println(y[i]);
     if(y[i]=='*')
        i = i-2;
     else if(y[i]=='#')
        return '#';
     if(i == 3)
        while(1){
          k1 = keypad.waitForKey();
          if( k1 == 'B'){  //确定
              py = (int(y[0])-48)*1000+(int(y[1])-48)*100+(int(y[2])-48)*10+(int(y[3])-48);
              break;
          }else if( k1 == 'A'){//取消
              lcd.setCursor(i+7,1);
              lcd.print(" ");
              lcd.setCursor(i+7,1);
              goto tYear;
          }
        }
   }
  }

char set_time_month(){
   char k1;
   lcd.clear();
   lcd.home();
   lcd.print("<<<<Set_Time>>>>"); 
   lcd.setCursor (1,1);
   lcd.blink(); 
   lcd.print("Month:"); 
   for(i=0;i<2;i++){
    tMonth:
     y[i] = input_show(i+7);
     if(y[i]=='*')
        i = i-2;
     else if(y[i]=='#')
        return '#';
     if(i == 1){
        while(1){
          k1 = keypad.waitForKey();
          if( k1 == 'B'){  //确定
              pmo = (int(y[0])-48)*10+(int(y[1])-48);
              break;
          }else if( k1 == 'A'){//取消
              lcd.setCursor(i+7,1);
              lcd.print(" ");
              lcd.setCursor(i+7,1);
              goto tMonth;
          }
        }
   }  
  }
    if(pmo > 12 || pmo < 1){
     Serial.print("error");
     lcd.clear();
     lcd.setCursor (5,1);
     lcd.print("ERROR!");
     keypad.waitForKey();
     set_time_month();
     }  
}

char set_time_day(){
   char k1;
   lcd.clear();
   lcd.home();
   lcd.print("<<<<Set_Time>>>>"); 
   lcd.setCursor (3,1);
   lcd.blink(); 
   lcd.print("Day:"); 
   for(i=0;i<2;i++){
    tDay:
     y[i] = input_show(i+7);
     if(y[i]=='*')
        i = i-2;
     else if(y[i]=='#')
        return '#';
     if(i == 1){
        while(1){
          k1 = keypad.waitForKey();
          if( k1 == 'B'){  //确定
              pd = (int(y[0])-48)*10+(int(y[1])-48);
              break;
          }else if( k1 == 'A'){//取消
              lcd.setCursor(i+7,1);
              lcd.print(" ");
              lcd.setCursor(i+7,1);
              goto tDay;
          }
        }
   }  
  }
    if(pd > 31 || pd < 1){
     Serial.print("error");
     lcd.clear();
     lcd.setCursor (5,1);
     lcd.print("ERROR!");
     keypad.waitForKey();
     set_time_day();
     }  
}

char set_time_hour(){
   char k1;
   lcd.clear();
   lcd.home();
   lcd.print("<<<<Set_Time>>>>"); 
   lcd.setCursor (2,1);
   lcd.blink(); 
   lcd.print("Hour:"); 
   for(i=0;i<2;i++){
    tHour:
     y[i] = input_show(i+7);
     if(y[i]=='*')
        i = i-2;
     else if(y[i]=='#')
        return '#';
     if(i == 1){
        while(1){
          k1 = keypad.waitForKey();
          if( k1 == 'B'){  //确定
              ph = (int(y[0])-48)*10+(int(y[1])-48);
              break;
          }else if( k1 == 'A'){//取消
              lcd.setCursor(i+7,1);
              lcd.print(" ");
              lcd.setCursor(i+7,1);
              goto tHour;
          }
        }
   }  
  }
    if(ph > 24 || ph < 0){
     Serial.print("error");
     lcd.clear();
     lcd.setCursor (5,1);
     lcd.print("ERROR!");
     keypad.waitForKey();
     set_time_hour();
     }  
}

char set_time_minute(){
   char k1;
   lcd.clear();
   lcd.home();
   lcd.print("<<<<Set_Time>>>>"); 
   lcd.setCursor (0,1);
   lcd.blink(); 
   lcd.print("Minute:"); 
   for(i=0;i<2;i++){
    tMinute:
     y[i] = input_show(i+7);
     if(y[i]=='*')
        i = i-2;
     else if(y[i]=='#')
        return '#';
     if(i == 1){
        while(1){
          k1 = keypad.waitForKey();
          if( k1 == 'B'){  //确定
              pmi = (int(y[0])-48)*10+(int(y[1])-48);
              break;
          }else if( k1 == 'A'){//取消
              lcd.setCursor(i+7,1);
              lcd.print(" ");
              lcd.setCursor(i+7,1);
              goto tMinute;
          }
        }
   }  
  }
    if(pmi > 60 || pmi < 0){
     Serial.print("error");
     lcd.clear();
     lcd.setCursor (5,1);
     lcd.print("ERROR!");
     keypad.waitForKey();
     set_time_minute();
     }  
}

char set_time_second(){
   char k1;
   lcd.clear();
   lcd.home();
   lcd.print("<<<<Set_Time>>>>"); 
   lcd.setCursor (0,1);
   lcd.blink(); 
   lcd.print("Second:"); 
   for(i=0;i<2;i++){
    tSecond:
     y[i] = input_show(i+7);
     if(y[i]=='*')
        i = i-2;
     else if(y[i]=='#')
        return '#';
     if(i == 1){
        while(1){
          k1 = keypad.waitForKey();
          if( k1 == 'B'){  //确定
              ps = (int(y[0])-48)*10+(int(y[1])-48);
              break;
          }else if( k1 == 'A'){//取消
              lcd.setCursor(i+7,1);
              lcd.print(" ");
              lcd.setCursor(i+7,1);
              goto tSecond;
          }
        }
   }  
  }
    if(ps > 60 || ps < 0){
     Serial.print("error");
     lcd.clear();
     lcd.setCursor (5,1);
     lcd.print("ERROR!");
     keypad.waitForKey();
     set_time_second();
     }  
}
/**---设置初始时间结束---**/


/**---设置闹钟时间---**/
char set_clock(){
char c1,c2,c3;
schour:
  c1 = set_clock_hour();
  if(c1 == '#')
    return '#';
  Serial.println(ch);
scminute:
  c2 = set_clock_minute();
  if(c2 == '#')
    goto schour;
  Serial.println(cmi);
  c3 = set_clock_second();
  if(c3 == '#')
    goto scminute;
  Serial.println(cs);
  lcd.clear();
  lcd.setCursor (1,0);
  lcd.print("Press any key!"); 
  lcd.setCursor (3,1);
  lcd.print("Success!"); 
  keypad.waitForKey();
  show_flag = -show_flag;
}

char set_clock_hour(){
   char k1;
   lcd.clear();
   lcd.home();
   lcd.print("<<<<Set_Clock>>>"); 
   lcd.setCursor (2,1);
   lcd.blink(); 
   lcd.print("Hour:"); 
   for(i=0;i<2;i++){
    cHour:
     y[i] = input_show(i+7);
     if(y[i]=='*')
        i = i-2;
     else if(y[i]=='#')
        return '#';
     if(i == 1){
        while(1){
          k1 = keypad.waitForKey();
          if( k1 == 'B'){  //确定
              ch = (int(y[0])-48)*10+(int(y[1])-48);
              break;
          }else if( k1 == 'A'){//取消
              lcd.setCursor(i+7,1);
              lcd.print(" ");
              lcd.setCursor(i+7,1);
              goto cHour;
          }
        }
   }  
  }
    if(ch > 24 || ch < 0){
     Serial.print("error");
     lcd.clear();
     lcd.setCursor (5,1);
     lcd.print("ERROR!");
     keypad.waitForKey();
     set_clock_hour();
     }  
}

char set_clock_minute(){
   char k1;
   lcd.clear();
   lcd.home();
   lcd.print("<<<<Set_Clock>>>"); 
   lcd.setCursor (0,1);
   lcd.blink(); 
   lcd.print("Minute:"); 
   for(i=0;i<2;i++){
    cMinute:
     y[i] = input_show(i+7);
     if(y[i]=='*')
        i = i-2;
     else if(y[i]=='#')
        return '#';
     if(i == 1){
        while(1){
          k1 = keypad.waitForKey();
          if( k1 == 'B'){  //确定
              cmi = (int(y[0])-48)*10+(int(y[1])-48);
              break;
          }else if( k1 == 'A'){//取消
              lcd.setCursor(i+7,1);
              lcd.print(" ");
              lcd.setCursor(i+7,1);
              goto cMinute;
          }
        }
   }  
  }
    if(cmi > 60 || cmi < 0){
     Serial.print("error");
     lcd.clear();
     lcd.setCursor (5,1);
     lcd.print("ERROR!");
     keypad.waitForKey();
     set_clock_minute();
     }  
}

char set_clock_second(){
   char k1;
   lcd.clear();
   lcd.home();
   lcd.print("<<<<Set_Clock>>>"); 
   lcd.setCursor (0,1);
   lcd.blink(); 
   lcd.print("Second:"); 
   for(i=0;i<2;i++){
    cSecond:
     y[i] = input_show(i+7);
     if(y[i]=='*')
        i = i-2;
     else if(y[i]=='#')
        return '#';
     if(i == 1){
        while(1){
          k1 = keypad.waitForKey();
          if( k1 == 'B'){  //确定
              cs = (int(y[0])-48)*10+(int(y[1])-48);
              break;
          }else if( k1 == 'A'){//取消
              lcd.setCursor(i+7,1);
              lcd.print(" ");
              lcd.setCursor(i+7,1);
              goto cSecond;
          }
        }
   }  
  }
    if(cs > 60 || cs < 0){
     Serial.print("error");
     lcd.clear();
     lcd.setCursor (5,1);
     lcd.print("ERROR!");
     keypad.waitForKey();
     set_clock_second();
     }  
}
/**---设置闹钟时间结束---**/






char input_show(int x){
   char k = keypad.waitForKey();
   if(k == 'A'){  //"取消"
        if(x-1>6){
          lcd.setCursor(x-1,1);
          lcd.print(" ");
          lcd.setCursor(x-1,1);
          return '*';
        }else{ 
            return '#';
        }
    }else if( k >= '0' && k <= '9'){
         lcd.setCursor(x,1);
         lcd.print(k);
        Serial.println(i);
         return k;
    }else{
      i = i-1;
      Serial.println(i);
      }
  }
