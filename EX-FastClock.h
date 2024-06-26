#include <Arduino.h>

// include the specific clock configuration
#include "config.h"

#include <EEPROM.h>

#ifdef TFT_DISPLAY
  #include <Adafruit_GFX.h>
  #include <MCUFRIEND_kbv.h>
  #include <TouchScreen.h>
  #include <SPI.h>
  
  // Define some colours for the display
  #define BLACK   0x0000
  //#define BLUE    0x001F
  #define RED     0xF800
  #define GREEN   0x07E0
  #define CYAN    0x07FF
  #define MAGENTA 0xF81F
  #define YELLOW  0xFFE0
  #define WHITE   0xFFFF

  #define MINPRESSURE 200
  #define MAXPRESSURE 1000
  
  // Define the operating buttons
  //Adafruit_GFX_Button btn1, btn2, btn3, btn4, btn5, btn6;
  Adafruit_GFX_Button key[6];
  
  int pixel_x, pixel_y;     //Touch_getXY() updates global vars
#endif

// 1 - SSD1306 OR 2 - SH1106
#ifdef OLED_DISPLAY
  #if OLED_DISPLAY == 1
    #include <SoftWire.h>
    #include <Adafruit_GFX.h>
    #include <Adafruit_SSD1306_SoftWire.h>
    // #include <Fonts/FreeSans9pt7b.h>
    // #include "fonts/Open_Sans_Regular_9.h"

    SoftWire i2c(OLED_SDA, OLED_SCL);
    Adafruit_SSD1306 oled(OLED_WIDTH, OLED_HEIGHT, &i2c, OLED_RESET);
  #endif

  #if OLED_DISPLAY == 2
    #include <FlexWire_v1.h>
    FlexWire flexWire = FlexWire(OLED_SDA, OLED_SCL);

    #include <Adafruit_GFX.h>
    #include <Adafruit_SH1106_FlexWire.h>
    
    Adafruit_SH1106 oled(OLED_RESET);
  #endif
#endif

// The following line governs the clock speeds available for selection
// Clockspeed of 1 = real time
// Clockspeed of 2 = half real time i.e. 1 min equiv. to 30 seconds
// Clockspeed of 4 = 1/4 real time i.e. 1 min equiv. to 15 seconds
// etc.
// These do not need to be changed but could be
byte clockSpeeds[] = {1, 2, 4, 6, 8, 12, 30};  //  Fast Clock Speeds

// The following line sets the default (startup) speed.
byte clockSpeed = 4;               //  Initial Fast Clock Speed Setting

// Global message buffers shared by Serial and Scrolling functions
#define BUF_SIZE  15
char message[BUF_SIZE];
char last_message[BUF_SIZE];

unsigned long currentMillis = 0;  //  Current Millis value for comparison
unsigned long lastMillis = 0;     //  Last Millis for comparison
unsigned long startTime = 0;      //  Milliseconds since 00:00.000 to Session Start Time
unsigned long runTime = 0;        //  Milliseconds since Session Start Time

// Constants
const int milPerSec = 1000;       //  Milliseconds per Second
unsigned long milPerMin = 60000;  //  Milliseconds per minute
unsigned long milPerHr = 3600000; //  Milliseconds per Hour

byte debounceDelay = 100;           //  the debounce time; increase if the output flickers
byte counter = 2;                  //  for program logic
bool pausePlay = false;            //  clock state - running or paused

byte HH;                           //  Integer Hours
byte MM;                           //  Integer Minutes
byte HD;                           //  number of full Days since conting
byte MH;                           //  number of full hours since conting
byte SM;                           //  number of full minutes since conting 

byte LastMinutes = 99;
byte ButtonPressed = 0;
byte ButtonPressedTFT = 0;
byte ButtonPressedMechanical = 0;

struct MyTime {
  byte hour;
  byte minute;
  byte speed;
};

MyTime PauseTime;

#define DEBOUNCE 100  // button debouncer, how many ms to debounce
#ifdef MECHANICAL_BUTTONS
  byte buttons[] = {2, 3, 4, 5, 6, 7};
  // This handy macro lets us determine how big the array up above is, by checking the size
  #define NUMBUTTONS sizeof(buttons)
#endif

// only load the wire library if we transmit to CS
#ifdef SEND_VIA_I2C
  #include <Wire.h>
#endif

#ifdef OLED_DISPLAY
  void printOledClock(char *Msg) {
    oled.cp437(true);
    oled.setTextSize(3);
    oled.setCursor(20, 13);
    oled.setTextColor(WHITE, BLACK);
    oled.print(Msg);
    oled.display();    
  }
#endif

#ifdef TFT_DISPLAY
  MCUFRIEND_kbv tft;  // set up a tft instance with the MCUFRIEND drivers
  TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
  
  // Load the special font for the clock display - 24 point wont load
  // This is a converted Arial Truetype font with characters 0 - 9 & :
  #include "Fonts/Arial48pt7b.h"
  #include "Fonts/Arial9pt7b.h"
  
  void showmsgXY(byte x, byte y, byte sz, char colour, char *msg)
  {
    tft.setFont();
    tft.setFont(&Arial9pt7b);
    tft.setCursor(x, y);
    tft.setTextColor(colour);
    tft.setTextSize(sz);
    tft.print(msg);
    delay(10);
  }
  
  void TFT_Begin()
  {
    tft.reset();   
    uint16_t ID = tft.readID();
  
    #ifdef DEBUG_PRINT
      Serial.print("TFT ID = 0x");
      Serial.println(ID, HEX);
      Serial.println("Calibrate for your Touch Panel");
    #endif
    
    if (ID == 0xD3D3) ID = 0x9486; // write-only shield
    tft.begin(ID);
    tft.setRotation(0);           //PORTRAIT
    tft.fillScreen(BLACK);
    showmsgXY(1, 15, 1, YELLOW, header);
    tft.drawFastHLine(0, 20, tft.width(), WHITE);
  }
  
  void DrawButtons() {
  
    tft.setFont();  // Set the default font
  
    #ifdef DEBUG_PRINT
      Serial.println("Defining Buttons");
    #endif

    #if START_PAUSED == true
      key[0].initButton(&tft,  40, 220, 70, 40, WHITE, GREEN, WHITE, "Start", 2);
    #else
      key[0].initButton(&tft,  40, 220, 70, 40, WHITE, CYAN, BLACK, "Pause", 2);
    #endif
    key[1].initButton(&tft,  120, 220, 70, 40, WHITE, RED, WHITE, "Save", 2);
    key[2].initButton(&tft,  200, 220, 70, 40, WHITE, CYAN, BLACK, "Reset", 2);
    key[3].initButton(&tft,  40, 270, 70, 40, WHITE, CYAN, BLACK, "T+", 2);
    key[4].initButton(&tft,  120, 270, 70, 40, WHITE, CYAN, BLACK, "T-", 2);
    key[5].initButton(&tft,  200, 270, 70, 40, WHITE, CYAN, BLACK, "Rate", 2); 
    
    for (byte x = 0; x < 6; x++) {
      key[x].drawButton(false);
      delay(10);    // Seem to need a slight pause
    }
    
  } 
  
  void printClock(char *Msg) {
    tft.setFont(&Arial48pt7b);
    tft.setTextColor(MAGENTA);
    tft.setTextSize(1);
    tft.fillRect(1, 30, 235, 90, BLACK);
    tft.setCursor(1,100);
    tft.print(Msg);
    // tft.drawFastHLine(0, 120, tft.width(), WHITE);
  }
    
  void printClockEx() {
    // prevent flickering
    tft.setFont(&Arial48pt7b);
    tft.setTextColor(MAGENTA);
    tft.setTextSize(1);
  
    if (message[0] != last_message[0]) {
      //tft.fillRect(1, 30, 50, 75, BLACK);
      tft.fillRect(1, 30, 104, 75, BLACK);
      tft.setCursor(1,100);
      tft.print(String(message[0]) + String(message[1]));
      last_message[0] = message[0];
      last_message[1] = message[1];
    } else {
      if (message[1] != last_message[1]) {
        tft.fillRect(54, 30, 50, 75, BLACK);
        tft.setCursor(54,100);
        tft.print(message[1]);
        last_message[1] = message[1];
      }
    }
    if (message[2] != last_message[2]) {
      tft.fillRect(107, 30, 25, 75, BLACK);
      tft.setCursor(107,100);
      tft.print(message[2]);
      last_message[2] = message[2];
    }
    if (message[3] != last_message[3]) {
      //tft.fillRect(135, 30, 50, 75, BLACK);
      tft.fillRect(135, 30, 104, 75, BLACK);
      tft.setCursor(135,100);
      tft.print(String(message[3]) + String(message[4]));
      last_message[3] = message[3];
      last_message[4] = message[4];
    } else {
      if (message[4] != last_message[4]) {
        tft.fillRect(188, 30, 50, 75, BLACK);
        tft.setCursor(188,100);
        tft.print(message[4]);
        last_message[4] = message[4];
      }
    }
  }
  
  void printText(char *Msg) {
    #ifdef DEBUG_PRINT
      Serial.println(Msg);
    #endif
    tft.fillRect(1, 170, 318, 30, BLACK);
    tft.setCursor(15, 170);
    tft.setFont();
    tft.setTextColor(YELLOW);
    tft.setTextSize(2);
    tft.print(Msg);
    delay(10);
  }
  
  bool Touch_getXY(void) {
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   //because TFT control pins
    digitalWrite(XM, HIGH);
    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
    if (pressed) {
      pixel_x = map(p.x, TS_LEFT, TS_RT, 0, tft.width()); //.kbv makes sense to me
      pixel_y = map(p.y, TS_TOP, TS_BOT, 0, tft.height());
    }
    return pressed;
  }
  
  void CheckButtons() {
    tft.setFont();
    bool down = Touch_getXY();
    for (uint8_t b = 0; b < 6; b++){
      key[b].press(down && key[b].contains(pixel_x, pixel_y));
      if (key[b].justReleased()) {
        key[b].drawButton();
      }
      if (key[b].justPressed()) {
        key[b].drawButton(true);
        ButtonPressedTFT = b + 1;
        delay(debounceDelay);
      }
    } // for
  }
#endif

#ifdef SEND_VIA_SERIAL
  void SendTime(byte hour, byte mins, byte speed) {
    int itime = (hour * 60) + mins;
    Serial.print(F("<JC "));
    Serial.print( itime);
    Serial.print(F(" "));
    Serial.print((int)speed);
    Serial.print(F(">\n"));
  }
#endif

#ifdef SEND_VIA_I2C
  void TransmitTime() {
    // send the data over I2C
    // send the time as <mmmm> as two bytes followed by clockspeed
    int timetosend = (HH * 60) + MM;
    byte TimeArray[2];
    TimeArray[0] = (timetosend >> 8);
    TimeArray[1] = timetosend & 0xFF;
    Wire.write(TimeArray, 2);
    Wire.write(clockSpeed);
  }
#endif

#ifdef MECHANICAL_BUTTONS 
  void check_switches()
  {
    static byte previousstate[NUMBUTTONS];
    static byte currentstate[NUMBUTTONS];
    static unsigned long lasttime[NUMBUTTONS];
    byte index;
    
    for (index = 0; index < NUMBUTTONS; index++) {
      if (millis() < lasttime[index]) {
         // we wrapped around, lets just try again
         lasttime[index] = millis();
      }
      if (millis() - lasttime[index] > DEBOUNCE) {
        currentstate[index] = digitalRead(buttons[index]);
        if (currentstate[index] == LOW) {
          currentstate[index] = digitalRead(buttons[index]); // check a 2nd time to be sure
          if (previousstate[index] != currentstate[index]) {
            if (currentstate[index] == LOW) {// check a 2nd time to be sure
              ButtonPressedMechanical = index + 1;
            }
          }
        }
        previousstate[index] = currentstate[index];
        lasttime[index] = millis();
      }    
    } //for
  }
#endif
