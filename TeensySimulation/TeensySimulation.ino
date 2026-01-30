#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#include <OneButton.h>

#include <Mice.h>
#include <BrainConfig.h>
#include <BodyConfig.h>

#include <BabyMouse.h>
#include <YoungMouse.h>
#include <YoungAdultMouse.h>
#include <AdultMouse.h>
#include <OldMouse.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };

const int ledPin = 13;

// Create an IntervalTimer object 
IntervalTimer myTimer;

#define PIN_INPUT1 3
#define PIN_INPUT2 5

// Setup a new OneButton on pin PIN_INPUT1,2.
OneButton button1(PIN_INPUT1, true);
OneButton button2(PIN_INPUT2, true);

Simulation mySimulation;


#if SIMULATION == 1
BabyMouse   BDavid ( &mySimulation );
YoungMouse  YDavid ( &mySimulation );
YoungAdultMouse   NDavid ( &mySimulation );
AdultMouse  ADavid ( &mySimulation );
OldMouse    ODavid ( &mySimulation );
#else
BabyMouse   BDavid ( NULL );
YoungMouse  YDavid ( NULL );
YoungAdultMouse    NDavid ( NULL );
AdultMouse  ADavid ( NULL );
OldMouse    ODavid ( NULL );
#endif

// Active mouse
//BabyMouse      *mice =  &BDavid;
//YoungMouse     *mice =  &YDavid;
AdultMouse     *mice =  &ADavid;
//OldMouse       *mice =  &ODavid;
//YoungAdultMouse  *mice =  &NDavid;

int ledState = LOW;

void click1() {
    Serial.println("log Button 1 click.");
#if SIMULATION == 1
  digitalWrite(ledPin, HIGH);   // set the LED on
	mice->WalkToGoal( );
  digitalWrite(ledPin, LOW);    // set the LED off
#else
	mice->objBody.start_motor_controllers();
	mice->WalkToGoal( );
	mice->objBody.reset_motor_controllers();
#endif
	//ssd1306_clearScreen();

} // click1

void click2() {
  Serial.println("log Button 2 click.");
	//ssd1306_clearScreen();
	//ssd1306_printFixedN(0,16,"RUNNING   ", STYLE_NORMAL, FONT_SIZE_2X);
#if SIMULATION == 1
	mice->RunToGoal( );
#else
	mice->objBody.start_motor_controllers();
	mice->RunToGoal( );
	mice->objBody.reset_motor_controllers();
#endif
	//ssd1306_clearScreen();

} // click2

void setup() {
    Serial.begin(19200);

    pinMode(ledPin, OUTPUT);

  // Wait for display
  delay(500);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(3000); // Pause for 2 seconds
  display.clearDisplay();
//  display.setTextSize(2); // Draw 2X-scale text
 // display.setTextColor(SSD1306_WHITE);
//  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  // Clear the buffer
  //display.clearDisplay();
  //testdrawrect();      // Draw rectangles (outlines)

  //OneButton  button1, button2;

  button1.attachClick(click1);
  button2.attachClick(click2);

	mice->miceReset();

  //myTimer.begin(&mice->objBody.BodyUpdates  , 150000);  // blinkLED to run every 0.15 seconds
  myTimer.begin(blinkLED  , 150000);  // blinkLED to run every 0.15 seconds
//  	  mice->objBody.BodyDisplay();

}

// functions called by IntervalTimer should be short, run as quickly as
// possible, and should avoid calling other functions if possible.
void blinkLED() {
  mice->objBody.BodyUpdates();  
  if (ledState == LOW) {
    ledState = HIGH;
  } else {
    ledState = LOW;
  }
  digitalWrite(ledPin, ledState);
}

void testdrawrect(void) {
  display.clearDisplay();

  for(int16_t i=0; i<display.height()/2; i+=2) {
    display.drawRect(i, i, display.width()-2*i, display.height()-2*i, SSD1306_WHITE);
    display.display(); // Update screen with each newly-drawn rectangle
    delay(1);
  }

  delay(2000);
}
void loop() {

  	  button1.tick();
  	  button2.tick();

  	  mice->objBody.BodyDisplay();
	
}

