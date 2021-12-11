#include <VirtualWire.h>  
#define TRIG 11 //pin that sends ultrasounds (1° transmitter)
#define ECHO 12 // pin that receives return signals (1° transmitter)
 #define TRIG2 6 // pin that sends ultrasounds (2° transmitter)
 #define ECHO2 5 // pin that receives return signals (2° transmitter)
  
const int TX_DIO_Pin = 2; 

void setup() { 
  initialize_transmitter();
  Serial.begin(9600); // Serial monitoring 
  pinMode(TRIG, OUTPUT); // Initializing Trigger Output and Echo Input 
  pinMode(ECHO, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  pinMode (TRIG2, OUTPUT);
  pinMode (ECHO2, INPUT);
  pinMode (13, OUTPUT);
  } 
  
  void loop() { 

    digitalWrite(TRIG, LOW); // 
    delayMicroseconds(2); 
    
    digitalWrite(TRIG, HIGH); //
    delayMicroseconds(20); 
    
    digitalWrite(TRIG, LOW); // 
   int distance = pulseIn(ECHO, HIGH)/ 58.0; // values ​​the distance (1° transmitter)
  Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println("cm");
      digitalWrite(13, HIGH);  
        digitalWrite(13, LOW); 
        delay(20);                   

    digitalWrite(TRIG2, LOW); // 
    delayMicroseconds(2); 
    
    digitalWrite(TRIG2, HIGH); // 
    delayMicroseconds(20); 
    
    digitalWrite(TRIG2, LOW); // 
   int distance2 = pulseIn(ECHO2, HIGH)/ 58.0; // values ​​the distance (2° transmitter)
  Serial.print("Distance 2: ");
    Serial.print(distance2);
    Serial.println("cm");
      digitalWrite(13, HIGH);  
  if (distance < distance2) {
    transmit_integer(distance);// send the distance of 1° transmitter
  }
  else {
    transmit_integer(distance2);// send the distance of 2° transmitter
  }
        digitalWrite(13, LOW); 
        delay(20);  
        
}


/* DO NO EDIT BELOW */
    
    void initialize_transmitter() {
      /* Initialises the DIO pin used to send data to the Tx module */
      vw_set_tx_pin(TX_DIO_Pin);
      /* Set the transmit logic level (LOW = transmit for this version of module)*/ 
      vw_set_ptt_inverted(true); 
      
      /* Transmit at 2000 bits per second */
      vw_setup(2000);    // Bits per sec
    }
    
    void transmit_integer(unsigned int Data) {
      /* The transmit buffer that will hold the data to be 
         transmitted. */
      byte TxBuffer[2];
      /* ...and store it as high and low bytes in the transmit 
         buffer */
      TxBuffer[0] = Data >> 8;
      TxBuffer[1] = Data;
      
      /* Send the data (2 bytes) */
      vw_send((byte *)TxBuffer, 2);
      /* Wait until the data has been sent */
      vw_wait_tx();
    }
    
 
