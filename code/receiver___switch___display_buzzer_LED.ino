/* 
PIN  DESCRIPTION      ARDUINO PIN
1    GND              GND
2    RX DATA          D2
3    RX DATA          N/A
4    VCC (5V)         VCC
*/

#include <VirtualWire.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <hd44780.h>                       // main hd44780 header
#include <hd44780ioClass/hd44780_I2Cexp.h> // i2c expander i/o class header

hd44780_I2Cexp lcd; // declare lcd object: auto locate & auto config expander chip

const int RX_DIO_Pin = 2; // pin receiver
int received;
int switchPin = 13; // pin of a slide switch
int switchState = 0;  // read slide switch status
const int buzzer = 11;
const int ledPin = 7;

// LCD geometry
const int LCD_COLS = 16;
const int LCD_ROWS = 2;

byte c=255;

long duration;
int distance;

void setup() {
    Serial.begin(9600);
    pinMode(switchPin, INPUT_PULLUP); //initialize the slide switch as input
    initialize_receiver(); // initialize the receiver
    pinMode(A0, OUTPUT); // initialize the display
    digitalWrite(A0, HIGH);
    lcd.begin(LCD_COLS, LCD_ROWS);
    lcd.home ();
    pinMode(buzzer, OUTPUT);
    pinMode(ledPin, OUTPUT);
}

/* Main program */
void loop() {
   switchState = digitalRead(switchPin);

  if (switchState == HIGH ) //

  {
     lcd.display();
  received = receive_integer();
  if(received != -1) 
   {
   lcd.clear();
    lcd.print("Distance:");
  lcd.setCursor(0, 1);
 lcd.print(received);
 lcd.setCursor(3, 1);
  lcd.print("cm");
  Serial.print("Distance = ");
  Serial.print(received);
  Serial.println(" cm"); 
  if (received>50) {
tone(buzzer,1000,200);//plays a note on pin 12 at a frequency of 1000Hz
digitalWrite(ledPin, HIGH);
delay(200);                        //waits 2 seconds
noTone(buzzer);                //doesn't play
 digitalWrite(ledPin, LOW);
delay(200);
  }
  else if (received<=50 && received>35) {
tone(buzzer,1200,200);//plays a note on pin 12 at a frequency of 1200Hz
digitalWrite(ledPin, HIGH);
delay(100);                        //waits 2 seconds
noTone(buzzer);                //doesn't play
 digitalWrite(ledPin, LOW);
delay(100);
  }
 else if (received<=35) {
tone(buzzer,1500,200);//plays a note on pin 12 at a frequency of 1500Hz
digitalWrite(ledPin, HIGH);
delay(50);                        //waits 2 seconds
noTone(buzzer);                //doesn't play
 digitalWrite(ledPin, LOW);
delay(50);
  }
delay(200);
  
  }}
else if (switchState == LOW ){
  Serial.println();
  lcd.noDisplay();
}
}
/* DO NOT EDIT BELOW */

void initialize_receiver() {
  /* Initialises the DIO pin used to receive data from the Rx module */
  vw_set_rx_pin(RX_DIO_Pin);  
  /* Receive at 2000 bits per second */
  vw_setup(2000);
  /* Enable the receiver */
  vw_rx_start();  
}

int receive_integer() {
 /* Set the receive buffer size to 2 bytes */
  uint8_t Buffer_Size = 2;
  
  /* Holds the recived data */
  unsigned int Data;
  
  /* The receive buffer */
  uint8_t RxBuffer[Buffer_Size];

  /* Has a message been received? */
  if (vw_get_message(RxBuffer, &Buffer_Size)) // Non-blocking
  {

      /* Store the received high and low byte data */
      Data = RxBuffer[0] << 8 | RxBuffer[1];
 
      return Data;
  }
  return -1;
}
