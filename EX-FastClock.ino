/*
 * Fast Clock Version 3.0
 * Colin H Murdoch - December 2022
 * 
 * September 2023, Franziska Walter:
 * - cleaning and formatting Code
 * - add config Options
 * - remove unwanted CodeBlocks
 * - repair debug print
 * - prevent flickering
 * - multiple bugs,e.g Display Refresh at Reset, etc.
 * 
 * 
 * Modified December 2022
 * Amended to operate in conjuction with DCC-EX and pass clock time values over I2C
 * to allow time based operation of EXRAIL commands.
 * 
 * Based on the original Written by Jim Gifford June 2017
 * COPYRIGHT © 2017 Jim Gifford
 * http://www.hallettcovesouthern.com/ - The website for my Layout
 * http://halletcovesouthern.blogspot.com.au - The Construction & Activities Blog
 * 
 * Provided under a Creative Commons Attribution, Non-Commercial Share Alike,3.0 Unported License
 *
 * This version modified by Colin H Murdoch - March 2022
 * Modified to operate on an Arduino Uno with an McuFriend type TFT LCD Shield.
 *
 * Design Notes:
 *
 * This code is designed to use the Arduino Uno R3 with a 2.8" plug in shield TFT display.
 * On initialisation the clock is paused ready to set the start time. The start time can be adjusted
 * up and/or from the 06:00 preset with a preset fast clock ratio of 4:1.  The fast clock ratio can
 * be adjusted to 1, 2, 4, 6, 8, 12 or 30.  A reset function has been included. When ready to commence
 * operation the start/pause button is pressed.  the original buttons have been replaced with on-screen buttons
 * set up using the Adafruit_GFX graphics library.
 * 
 * The system can now use the EEPROM to hold the time value.  If Button 2 (Save) is prwssed, the clock is halted 
 * and the values are saved to EEPROM.  on restart the clock loads up this time.  This can be overwritten
 * * with the Reset button.
 * 
 * On screen buttons.
 * 
 * Button 1   - Start/Pause
 * Button 2   - Save
 * Button 3   - Reset
 * Button 4   - +Time
 * Button 5   - -Time
 * Button 6   - Rate
 *
 * 
 */

#include "EX-FastClock.h"

#ifndef SEND_VIA_SERIAL
 //#define DEBUG_PRINT  // should not use if serial send active
#endif

void TimeCheck() {
  HH = ((startTime + runTime) / milPerHr) ;
  if (HH >= 24) {
    HD = (HH / 24);
    HH = (HH - (24 * HD)); 
  }
  MM = ((startTime + runTime) % milPerHr) / milPerMin;
  if (MM > 59) {
    MH = (MM / 60);
    MM = (MM - ( 60 * MH)); 
  }
  message[0] = '0' + HH/10;
  message[1] = '0' + HH%10;
  message[2] = ':';
  message[3] = '0' + MM/10;
  message[4] = '0' + MM%10;
  message[5] = 0;
}

void CheckClockTime() {
  #ifdef DEBUG_PRINT
    // Serial.println("Clock Tick");
  #endif
  if (currentMillis - lastMillis >= milPerSec) {  // cycle every second  
    runTime = runTime + (clockSpeed * milPerSec);
    TimeCheck();
    lastMillis = currentMillis;
    if (MM != LastMinutes){
      LastMinutes = MM;
      #ifdef TFT_DISPLAY
        printClockEx();
      #endif
      #ifdef OLED_DISPLAY
        printOledClock(message);
      #endif
      #ifdef SEND_VIA_SERIAL
        SendTime(HH, MM, clockSpeed);
      #endif  
    }
  }
}

void PauseClock() {
  
  pausePlay = !pausePlay;

  #ifdef DEBUG_PRINT
    Serial.print("PausePlay = ");
    Serial.println(pausePlay);
  #endif

  #ifdef TFT_DISPLAY
    if (pausePlay == true) {
      showmsgXY(55, 160, 2, YELLOW, "PAUSED");
      tft.setFont();
      key[0].initButton(&tft,  40, 220, 70, 40, WHITE, GREEN, WHITE, "Start", 2);
      key[0].drawButton(false);
    } else {
      tft.setFont();
      tft.fillRect(1, 135, 235, 30, BLACK);
      key[0].initButton(&tft,  40, 220, 70, 40, WHITE, CYAN, BLACK, "Pause", 2);
      key[0].drawButton(false); 
    }
  #endif

  #ifdef OLED_DISPLAY
    oled.setCursor(30, 40);    
    if (pausePlay == true) {
      oled.setTextColor(WHITE, BLACK);
    } else {
      oled.setTextColor(BLACK, BLACK);
    }
    oled.setTextSize(2);
    oled.print("PAUSED");
    oled.display();
  #endif
}

void AdjustTime(byte OPT){
  // if runTime is > 2 minutes (120000 millis) adjust runTime if under 2 minutes startTime
  //  Increment by 15 Min "a press"
  
  switch (OPT) {
    case 1:
      if (runTime > 120000) {
        runTime = runTime + 900000;
      } else  {
        startTime = startTime + 900000;
      }
      break;
      
    case 2:
      if (runTime > 120000) {
        runTime = runTime - 900000;
      } else  {
        startTime = startTime - 900000;
      }
      break;
      
    default:
      break;
      
  }
  
  TimeCheck();
  #ifdef TFT_DISPLAY
    printClockEx();
  #endif
  #ifdef OLED_DISPLAY
    printOledClock(message);
  #endif
  
  #if ACTION_PAUSED
    if (!pausePlay) {
      PauseClock();
    }
  #endif
}

void displaySpeed(byte x) {
  clockSpeed = clockSpeeds[x];
  
  strcpy(message, "Speed = ");
  if (clockSpeed < 10) {
    message[8] = '0' + clockSpeed;
    message[9] = 0;
    message[10] = ' ';
  } else {
    message[8] = '0' + clockSpeed/10;
    message[9] = '0' + clockSpeed%10;
    message[10] = 0;
  }
  
  #ifdef TFT_DISPLAY
    tft.fillRect(10, 170, 240, 22, BLACK);
    showmsgXY(10, 190, 1, YELLOW, message);
  #endif
  #ifdef OLED_DISPLAY
    oled.setTextSize(1);
    oled.fillRect(0, 57, oled.width() - 1, 7, BLACK);
    oled.setCursor(0, 57);
    oled.setTextColor(WHITE, BLACK);
    oled.print(message);
    oled.display();
  #endif
}

void AlterRate() {
  
  if (counter < 6) {
    counter++;
  } else {
    counter = 0;
  }
  displaySpeed(counter); // Speed Display
  
  #if ACTION_PAUSED
    if (!pausePlay) {
      PauseClock();
    }
  #endif
  
  currentMillis = millis();
}

void ResetAll() {
  startTime = 21600000;              //  default start time 06:00  
  counter = 2;                       //  initial clock speed 4:1
  runTime = 0;                       //  Reset run time
  LastMinutes = 99;
  currentMillis = millis();
  lastMillis = currentMillis + milPerSec;
  
  displaySpeed(counter);            // Speed Display
  CheckClockTime();                 // display the time
  
  #if ACTION_PAUSED
    if (!pausePlay) {
      PauseClock();
    }
  #endif
}

void SaveTime() {
  #if ACTION_PAUSED
    if (!pausePlay) {
      PauseClock();
    }
  #endif
  
  PauseTime.hour = HH;
  PauseTime.minute = MM;
  PauseTime.speed = counter;

  int eeAddress = 0;
  EEPROM.put(eeAddress, PauseTime);
  
  #ifdef TFT_DISPLAY
    tft.fillRect(1, 135, 235, 30, BLACK);
    showmsgXY(55, 160, 2, YELLOW, "SAVED");
  #endif
}

void GetSavedTime() {
  int eeAddress = 0;
  EEPROM.get(eeAddress, PauseTime);

  // Check we have something valid from EEPROM
  if (PauseTime.hour > 0 && PauseTime.hour < 25) {
    // we have a valid time so calculate start point
    startTime = (PauseTime.hour * milPerHr) + (PauseTime.minute * milPerMin);
    counter = PauseTime.speed;
  } else {
    // not valid so set defaults.  Either first use or EEPROM corrupt
    startTime = 21600000;           //  default start time 06:00
    clockSpeed = 4;                 //  initial clock speed 4:1
  }

  lastMillis = millis();          //  first reference reading of arduino O/S
}

void PrintButton(){
  #ifdef DEBUG_PRINT
    Serial.print("Button :");
    Serial.println(ButtonPressed);
  #endif
}

void setup() {

  #if defined(SEND_VIA_SERIAL) || defined(DEBUG_PRINT)
    Serial.begin(115200);
  #endif

  #ifdef MECHANICAL_BUTTONS
    #ifdef DEBUG_PRINT
      Serial.println("Init Mechanical Buttons:");
    #endif
    for (unsigned int i = 0; i < NUMBUTTONS; i++) {
      pinMode(buttons[i], INPUT_PULLUP);
      #ifdef DEBUG_PRINT
        Serial.print("Pin ");
        Serial.println(buttons[i]);
      #endif
    }
  #endif
  
  #ifdef SEND_VIA_I2C       // only start the wire library if we transmit to CS
    #ifdef DEBUG_PRINT
      Serial.print("Starting Wire Library at address : ");
      Serial.println(I2CAddress);
    #endif
    Wire.begin(I2CAddress);
    Wire.onRequest(TransmitTime);
  #endif
  
  currentMillis = millis();
  GetSavedTime();                   // Read the EEPROM

  // 1 - SSD1306 OR 2 - SH1106
  #ifdef OLED_DISPLAY
    #if OLED_DISPLAY == 1
      if(!oled.begin(SSD1306_SWITCHCAPVCC, OLED_I2C)) {
        #ifdef DEBUG_PRINT
          Serial.println(F("OLED allocation failed"));
        #endif
        for(;;); // Don't proceed, loop forever
      }
    #endif
    #if OLED_DISPLAY == 2
      oled.begin(SH1106_SWITCHCAPVCC, OLED_I2C);
    #endif
    
    TimeCheck();
    
    // Clear the buffer
    oled.clearDisplay();
    oled.setCursor(0, 0);
    oled.setTextColor(WHITE);
    oled.setTextSize(1);
    oled.print(header);
    oled.drawLine(0, 10, oled.width()-1, 10, WHITE);
    oled.cp437(true);
    oled.setTextSize(3);
    oled.setCursor(20, 13);
    oled.setTextColor(WHITE, BLACK);
    oled.print(message);
    oled.drawLine(0, 37, oled.width()-1, 37, WHITE);
    oled.setCursor(0, 57);
    oled.setTextColor(WHITE, BLACK);
    oled.setTextSize(1);
    oled.print("Speed = 4");
    oled.display();
    displaySpeed(counter);
  #endif
  
  #ifdef TFT_DISPLAY
    TFT_Begin();
    DrawButtons();
    displaySpeed(counter);            //speed Display
    CheckClockTime();                 // display the time
    tft.drawFastHLine(0, 114, tft.width(), WHITE);
  #endif
  
  pausePlay = START_PAUSED;
  if (pausePlay){
    #ifdef TFT_DISPLAY
      showmsgXY(50, 160, 2, YELLOW, "PAUSED");
    #endif
  }
  
  #ifdef DEBUG_PRINT
    Serial.println("Setup Finished");
  #endif
}

void loop() {
  
  if (pausePlay == false) {
    CheckClockTime();                 // display the time
  }

  #ifdef TFT_DISPLAY
    CheckButtons();
  #endif
  #ifdef MECHANICAL_BUTTONS
    check_switches();
  #endif
  ButtonPressed = ButtonPressedTFT | ButtonPressedMechanical;
        
  switch (ButtonPressed) {
    case 1:
      PauseClock();
      PrintButton();
      break;
        
    case 2:
      SaveTime();
      PrintButton();
      break;
  
    case 3:
      ResetAll();
      PrintButton();
      break;
  
    case 4:
      AdjustTime(1); // add time
      PrintButton();
      break;
  
    case 5:
      AdjustTime(2); // deduct time
      PrintButton();
      break;
  
    case 6:
      AlterRate();
      PrintButton();
      break;

  }

  ButtonPressed = 0;
  ButtonPressedTFT = 0;
  ButtonPressedMechanical = 0;
  currentMillis = millis();
}
