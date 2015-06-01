///////////////////////////////////////////
// LED CLOCK version 1
// Created by Chris Dalke
///////////////////////////////////////////

///////////////////////////////////////////
//Init
///////////////////////////////////////////

//Setup Shift Register Pins
int latchPin = 4;
int clckPin = 2;
int dataPin = 3;

//Delay in between display of lines
int displayDelay = 1000;
//1000 = 1s
//anything <5: display all lines at once (overheats!)

//Initialize internal display handling variables
int currentDisplayRow = 0;
byte data = 0;
byte data1 = 0;
byte data2 = 0;

//Variables for current time hour and minute.
//This uses the spark API to sync the correct time
int currenttime_h;
int currenttime_m;

///////////////////////////////////////////
// Setup
///////////////////////////////////////////

void setup() {
    //Start Serial for debugging purposes	
    Serial.begin(9600);
      
    //set shift register pins to output because they are addressed in the main loop
    pinMode(latchPin, OUTPUT);
    pinMode(clckPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    
    //Set proper time zone for spark time library
    Time.zone(-4);
}

///////////////////////////////////////////
// Update
///////////////////////////////////////////

void loop() {
  /*
  if the minute is between:
  0-4: hour
  5-9: five past
  10-14: ten past
  15-24: quarter past 
  25-39: half past
  40 - 44: quarter to
  45-49: quarter to
  50-54: ten to
  55-59: five to
  
  */
  
  //Get current time hour and minute
  currenttime_h = Time.hourFormat12();
  currenttime_m = Time.minute();
  
  if (currenttime_m >= 0 && currenttime_m <=4){
        DisplayHour(currenttime_h);
  }
   if (currenttime_m >= 5 && currenttime_m <=9){
  FlashWord(String("fivepast"));
  FlashWord(String("past"));
        DisplayHour(currenttime_h);
  }
   if (currenttime_m >= 10 && currenttime_m <=14){
  FlashWord(String("tenpast"));
  FlashWord(String("past"));
        DisplayHour(currenttime_h);
  }
   if (currenttime_m >= 15 && currenttime_m <=24){
  FlashWord(String("quarterpast"));
  FlashWord(String("past"));
        DisplayHour(currenttime_h);
  }
   if (currenttime_m >= 25 && currenttime_m <=39){
  FlashWord(String("halfpast"));
  FlashWord(String("past"));
        DisplayHour(currenttime_h);
  }
   if (currenttime_m >= 40 && currenttime_m <=44){
  FlashWord(String("quarterpast"));
  FlashWord(String("to"));
        DisplayHour(currenttime_h+1);
  }
   if (currenttime_m >= 45 && currenttime_m <=49){
  FlashWord(String("quarterpast"));
  FlashWord(String("to"));
        DisplayHour(currenttime_h+1);
  }
   if (currenttime_m >= 50 && currenttime_m <=54){
  FlashWord(String("tenpast"));
  FlashWord(String("to"));
        DisplayHour(currenttime_h+1);
  }
   if (currenttime_m >= 55 && currenttime_m <=59){
  FlashWord(String("fivepast"));
  FlashWord(String("to"));
        DisplayHour(currenttime_h+1);
  } 
  
}

void DisplayHour(int hour){
    if (hour > 12){hour = 1;}
    if (hour < 1){hour = 12;}
  if (hour == 1){FlashWord(String("one"));}
  if (hour == 2){FlashWord(String("two"));}
  if (hour == 3){FlashWord(String("three"));}
  if (hour == 4){FlashWord(String("four"));}
  if (hour == 5){FlashWord(String("five"));}
  if (hour == 6){FlashWord(String("six"));}
  if (hour == 7){FlashWord(String("seven"));}
  if (hour == 8){FlashWord(String("eight"));}
  if (hour == 9){FlashWord(String("nine"));}
  if (hour == 10){FlashWord(String("ten"));}
  if (hour == 11){FlashWord(String("eleven"));}
  if (hour == 12){FlashWord(String("twelve"));}
}

void FlashWord(String wordname){
    int tempRowId = 0;
    int tempdata = 0b00000000;
    if (wordname == "halfpast"){tempRowId=9;tempdata=0b11110000;}
    if (wordname == "fivepast"){tempRowId=9;tempdata=0b10000111;}
    
    if (wordname == "quarterpast"){tempRowId=8;tempdata=0b10000000;}
    if (wordname == "tenpast"){tempRowId=7;tempdata=0b11111000;}
    if (wordname == "past"){tempRowId=7;tempdata=0b00001111;}
    if (wordname == "to"){tempRowId=6;tempdata=0b11111100;}
    if (wordname == "three"){tempRowId=6;tempdata=0b00000111;}
    if (wordname == "eight"){tempRowId=5;tempdata=0b11100000;}
    if (wordname == "two"){tempRowId=5;tempdata=0b10001111;}
    if (wordname == "four"){tempRowId=4;tempdata=0b11110000;}
    if (wordname == "five"){tempRowId=4;tempdata=0b00001111;}
    if (wordname == "nine"){tempRowId=2;tempdata=0b11100001;}
    if (wordname == "ten"){tempRowId=2;tempdata=0b00011111;}
    
    if (wordname == "one"){tempRowId=1;tempdata=0b11111000;}
    if (wordname == "eleven"){tempRowId=1;tempdata=0b00000011;}
    if (wordname == "seven"){tempRowId=3;tempdata=0b00000111;}
    if (wordname == "six"){tempRowId=3;tempdata=0b11111000;}
    if (wordname == "hi"){tempRowId=0;tempdata=0b11111100;}
    if (wordname == "twelve"){tempRowId=0;tempdata=0b00000011;}
    
    FlashDisplayRow(tempRowId,tempdata);
    //delay(1000);
}

void FlashDisplayRow(byte RowID,byte data_stuff){
  
  digitalWrite(latchPin, 0);
  data2 = 0b00000000; //what 
  data1 = 0b00000000;
  //bits: xxxx_____x;
  //^^these control lower half
  
  if (RowID == 0){
      data2 = 0b00000000;
      data1 = 0b00000010;
  }
  if (RowID == 1){
      data2 = 0b00000000;
      data1 = 0b00000100;
  }
  if (RowID == 2){
      data2 = 0b00000000;
      data1 = 0b00001000;
  }
  if (RowID == 3){
      data2 = 0b00000000;
      data1 = 0b00010000;
  }
  if (RowID == 4){
      data2 = 0b00000000;
      data1 = 0b00100000;
  }
  if (RowID == 5){
      data2 = 0b00000010;
      data1 = 0b00000000;
  }
  if (RowID == 6){
      data2 = 0b00000100;
      data1 = 0b00000000;
  }
  if (RowID == 7){
      data2 = 0b00001000;
      data1 = 0b00000000;
  }
  if (RowID == 8){
      data2 = 0b00010000;
      data1 = 0b00000000;
  }
  if (RowID == 9){
      data2 = 0b00100000;
      data1 = 0b00000000;
  }
  
  shiftOut(dataPin, clckPin, MSBFIRST, data2); 
  shiftOut(dataPin, clckPin, MSBFIRST, data1); 
  
  shiftOut(dataPin, clckPin, MSBFIRST, data_stuff); 
  digitalWrite(latchPin, 1);
  delay(displayDelay);
  
}

