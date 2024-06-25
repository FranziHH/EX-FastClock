// Use Multiple Configs
#define USE_CONFIG 6

#if USE_CONFIG == 1

  //#define MECHANICAL_BUTTONS
  #define TFT_DISPLAY
  
  // 1 - SSD1306 OR 2 - SH1106
  // #define OLED_DISPLAY 1
  #ifdef OLED_DISPLAY  
    #define OLED_I2C 0x3C
    #define OLED_SDA A2
    #define OLED_SCL A3
    #define OLED_WIDTH 128
    #define OLED_HEIGHT 64
    #define OLED_RESET -1
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
  
  // Calibration for GTIN/EAN 4251102612806
  // 24.08.2023 eBay: https://www.ebay.de/itm/354531855596
  // Title: 2,4" TFT Touch-Display Shield für Arduino UNO R3 Mega2560 DIY-Elektronik Stift
  // const int XP = 6,XM=A2,YP=A1,YM=7; //240x320 ID=0x9341
  // const int TS_LEFT=198,TS_RT=915,TS_TOP=183,TS_BOT=916;
  
  // 001-ESP32
  const int XP=8,XM=A2,YP=A3,YM=9; //240x320 ID=0x9341
  const int TS_LEFT=122,TS_RT=929,TS_TOP=87,TS_BOT=900;
#endif

#if USE_CONFIG == 2

  // #define MECHANICAL_BUTTONS
  #define TFT_DISPLAY
  
  // 1 - SSD1306 OR 2 - SH1106
  // #define OLED_DISPLAY 1
  #ifdef OLED_DISPLAY
    #define OLED_DISPLAY_I2C 0x3C
    #define OLED_DISPLAY_SDA A2
    #define OLED_DISPLAY_SCA A3
    #define OLED_WIDTH 128
    #define OLED_HEIGHT 64
    #define OLED_RESET -1
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
  
  // Calibration for GTIN/EAN 4251102612806
  // 24.08.2023 eBay: https://www.ebay.de/itm/354531855596
  // Title: 2,4" TFT Touch-Display Shield für Arduino UNO R3 Mega2560 DIY-Elektronik Stift
  // const int XP=6,XM=A2,YP=A1,YM=7; //240x320 ID=0x9341
  // const int TS_LEFT=197,TS_RT=929,TS_TOP=172,TS_BOT=924;

  // 002-MEGA
  const int XP=6,XM=A2,YP=A1,YM=7; //240x320 ID=0x9341
  const int TS_LEFT=201,TS_RT=923,TS_TOP=169,TS_BOT=919;
#endif

#if USE_CONFIG == 3

  // #define MECHANICAL_BUTTONS
  #define TFT_DISPLAY
  
  // 1 - SSD1306 OR 2 - SH1106
  // #define OLED_DISPLAY 1
  #ifdef OLED_DISPLAY
    #define OLED_DISPLAY_I2C 0x3C
    #define OLED_DISPLAY_SDA A2
    #define OLED_DISPLAY_SCA A3
    #define OLED_WIDTH 128
    #define OLED_HEIGHT 64
    #define OLED_RESET -1
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
  
  // Calibration for GTIN/EAN 4251102612806
  // 24.08.2023 eBay: https://www.ebay.de/itm/354531855596
  // Title: 2,4" TFT Touch-Display Shield für Arduino UNO R3 Mega2560 DIY-Elektronik Stift
  // const int XP=6,XM=A2,YP=A1,YM=7; //240x320 ID=0x9341
  // const int TS_LEFT=197,TS_RT=929,TS_TOP=172,TS_BOT=924;

  // 003-MEGA
  const int XP=6,XM=A2,YP=A1,YM=7; //240x320 ID=0x9341
  const int TS_LEFT=186,TS_RT=938,TS_TOP=162,TS_BOT=928;
#endif

#if USE_CONFIG == 4

  // #define MECHANICAL_BUTTONS
  #define TFT_DISPLAY
  
  // 1 - SSD1306 OR 2 - SH1106
  // #define OLED_DISPLAY 1
  #ifdef OLED_DISPLAY
    #define OLED_DISPLAY_I2C 0x3C
    #define OLED_DISPLAY_SDA A2
    #define OLED_DISPLAY_SCA A3
    #define OLED_WIDTH 128
    #define OLED_HEIGHT 64
    #define OLED_RESET -1
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
  
  // Calibration for GTIN/EAN 4251102612806
  // 24.08.2023 eBay: https://www.ebay.de/itm/354531855596
  // Title: 2,4" TFT Touch-Display Shield für Arduino UNO R3 Mega2560 DIY-Elektronik Stift
  // const int XP=6,XM=A2,YP=A1,YM=7; //240x320 ID=0x9341
  // const int TS_LEFT=197,TS_RT=929,TS_TOP=172,TS_BOT=924;

  // 005
  const int XP=8,XM=A2,YP=A3,YM=9; //240x320 ID=0x9325
  const int TS_LEFT=86,TS_RT=988,TS_TOP=177,TS_BOT=948;
#endif

#if USE_CONFIG == 5

  #define MECHANICAL_BUTTONS
  // #define TFT_DISPLAY

  // 1 - SSD1306 OR 2 - SH1106
  #define OLED_DISPLAY 1
  #ifdef OLED_DISPLAY
    #define OLED_I2C 0x3C
    #define OLED_SDA A2
    #define OLED_SCL A3
    #define OLED_WIDTH 128
    #define OLED_HEIGHT 64
    #define OLED_RESET -1
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
  
  // Calibration for GTIN/EAN 4251102612806
  // 24.08.2023 eBay: https://www.ebay.de/itm/354531855596
  // Title: 2,4" TFT Touch-Display Shield für Arduino UNO R3 Mega2560 DIY-Elektronik Stift
  const int XP = 6,XM=A2,YP=A1,YM=7; //240x320 ID=0x9341
  const int TS_LEFT=198,TS_RT=915,TS_TOP=183,TS_BOT=916;
#endif

#if USE_CONFIG == 6

  #define MECHANICAL_BUTTONS
  // #define TFT_DISPLAY

  // 1 - SSD1306 OR 2 - SH1106
  #define OLED_DISPLAY 2
  #ifdef OLED_DISPLAY
    #define OLED_I2C 0x3C
    #define OLED_SDA A2
    #define OLED_SCL A3
    #define OLED_WIDTH 128
    #define OLED_HEIGHT 64
    #define OLED_RESET -1
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
  
  // Calibration for GTIN/EAN 4251102612806
  // 24.08.2023 eBay: https://www.ebay.de/itm/354531855596
  // Title: 2,4" TFT Touch-Display Shield für Arduino UNO R3 Mega2560 DIY-Elektronik Stift
  const int XP = 6,XM=A2,YP=A1,YM=7; //240x320 ID=0x9341
  const int TS_LEFT=198,TS_RT=915,TS_TOP=183,TS_BOT=916;
#endif
