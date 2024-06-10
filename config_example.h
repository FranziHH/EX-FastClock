// Use Multiple Configs
#define USE_CONFIG 1

#if USE_CONFIG == 1

  //#define MECHANICAL_BUTTONS
  #define TFT_DISPLAY
  
  //#define OLED_DISPLAY
  #ifdef OLED_DISPLAY
    #define OLED_I2C 0x3C
    #define OLED_SDA A2
    #define OLED_SCL A3
  #endif
  
  // TimeModus at Boot: default: PAUSE = true
  #define START_PAUSED false
  // Pause on each Action e.g. Change Time, Rate, etc defalt: true
  #define ACTION_PAUSED false
  
  // If we are sending data to the DCC-EX CS via I2C then we need to define an I2C Address
  // and set a flag for inclusion. If not using I2C then comment out next two lines
  #define I2CAddress 0x55 // default I2C address
  #define SEND_VIA_I2C true
  
  // If we are sending the data to the CS via Serial then uncomment the following line
  //#define SEND_VIA_SERIAL true
  
  // Set this following string to the header you require.  This is displayed at the top of the screen
  #define HDDR_SIZE  25
  char header[HDDR_SIZE] = {"   DCC-EX / EX-FastClock"}; // Add Your Location/Name Here
  
  // ALL Touch panels and wiring is DIFFERENT.  The touch screen needs to be calibrated
  // See the README files for how to run the calibration routine and
  // copy-paste results from TouchScreen_Calibr_native.ino into the lines below.
  
  const int XP=8,XM=A2,YP=A3,YM=9; //240x320 ID=0x9341
  const int TS_LEFT=122,TS_RT=929,TS_TOP=87,TS_BOT=900;
#endif

#if USE_CONFIG == 2

  #define MECHANICAL_BUTTONS
  // #define TFT_DISPLAY
  
  #define OLED_DISPLAY
  #ifdef OLED_DISPLAY
    #define OLED_I2C 0x3C
    #define OLED_SDA A2
    #define OLED_SCL A3
  #endif
  
  // TimeModus at Boot: default: PAUSE = true
  #define START_PAUSED false
  // Pause on each Action e.g. Change Time, Rate, etc defalt: true
  #define ACTION_PAUSED false
  
  // If we are sending data to the DCC-EX CS via I2C then we need to define an I2C Address
  // and set a flag for inclusion. If not using I2C then comment out next two lines
  #define I2CAddress 0x55 // default I2C address
  #define SEND_VIA_I2C true
  
  // If we are sending the data to the CS via Serial then uncomment the following line
  //#define SEND_VIA_SERIAL true
  
  // Set this following string to the header you require.  This is displayed at the top of the screen
  #define HDDR_SIZE  25
  char header[HDDR_SIZE] = {"DCC-EX / EX-FastClock"}; // Add Your Location/Name Here
  
  // ALL Touch panels and wiring is DIFFERENT.  The touch screen needs to be calibrated
  // See the README files for how to run the calibration routine and
  // copy-paste results from TouchScreen_Calibr_native.ino into the lines below.
  // const int XP = 6,XM=A2,YP=A1,YM=7; //240x320 ID=0x9341
  // const int TS_LEFT=198,TS_RT=915,TS_TOP=183,TS_BOT=916;
#endif
