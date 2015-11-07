/*
 Shift Register weather display prototype
 for 74HC595 shift register

 This sketch turns reads serial input and uses it to set the pins
 of a 74HC595 shift register.

 Hardware:
 * x2 74HC595 shift register attached to pins 8, 11, and 12 on the Arduino.
 * x2 seven segment LEDs attached to each of the outputs of the shift register.
 * x1 HMSOFT 10 BLE chip on breakout board deisgned by Ken Rother in 2014

 Created 2014
 by Andrew Sowers
 
 */

//Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 8;
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 12;
////Pin connected to Data in (DS) of 74HC595
const int dataPin = 11;

const int green = 4;
const int blue  = 5;
const int red   = 6;

#include <SoftwareSerial.h>


void changeOutput(int output){
    Serial.print("read: ");
    Serial.println(output);
    //registerWrite(digit, HIGH);

    /*
    if (Serial.available()){
      mySerial.write(Serial.read());
    }
    */
    int buffer[2]={0,0};
    for (int i=0;output > 0;i++)
    {
      int digit = output%10;
      output /= 10;
      //print digit
      buffer[i]=digit;
    }
    for(int i=1;i>=0;i--){
       registerWrite(buffer[i],HIGH);
    }
}

SoftwareSerial mySerial(3, 2); // RX, TX
void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin,  OUTPUT);  
  pinMode(clockPin, OUTPUT);
  pinMode(green,    OUTPUT);
  pinMode(blue,     OUTPUT);
  pinMode(red,      OUTPUT);
  
  Serial.begin(9600);
  Serial.println("reset");
  registerWrite(0, HIGH);
  registerWrite(0, HIGH);
  mySerial.begin(9600);
  
}

void loop() {
  
  
    mySerial.write("AT+CON0017EA92D391");
    
    boolean newFlag = false;
    boolean negFlag = false;
    boolean hotFlag = false;
    int output = 0;
    if(Serial.available())
      newFlag = true;
    
    for(int i=0;Serial.available();i++){
      
      int digit = Serial.read();
      if(digit==45){
        negFlag = true;
        newFlag = false;
        //return;
      }else if(digit==43){
        hotFlag = true;
        newFlag = false;
        //return;
      }else{
        digit=digit-48;
        if(hotFlag==true||negFlag==true){
          if(i==2){
            output=output+digit;
          }if(i==1){
            output=output+digit*10;
          }
        }else{
          if(i==1){
            output=output+digit;
          }if(i==0){
            output = output + digit*10;
          }    
        }
      }
    }

    if(negFlag==true){
      // turn LED blue
      //output = output*-1;
      digitalWrite(red,LOW);
      digitalWrite(green,LOW);
      digitalWrite(blue,HIGH);
      changeOutput(output);
    }else if(hotFlag==true){
      //turn LED red
      //output = output+100;
      digitalWrite(green,LOW);
      digitalWrite(blue,LOW);
      digitalWrite(red,HIGH);
      changeOutput(output);
    }else if(newFlag==true){
      //turn LED green
      digitalWrite(red,LOW);
      digitalWrite(blue,LOW);
      digitalWrite(green,HIGH);
      changeOutput(output);     
    }else{
     Serial.println("no change"); 
    }

    mySerial.write("AT+REST");
    delay(1000);
}



// This method sends bits to the shift register:

void registerWrite(int digit, int whichState) {
// the bits you want to send
  byte bitsToSend = 0;

  // turn off the output so the pins don't light up
  // while you're shifting bits:
  digitalWrite(latchPin, LOW);
  // turn on the next highest bit in bitsToSend:
  if (digit==0){
    bitWrite(bitsToSend, 1, whichState);
    bitWrite(bitsToSend, 2,whichState);
    bitWrite(bitsToSend, 4,whichState);
    bitWrite(bitsToSend, 5,whichState);
    bitWrite(bitsToSend, 6,whichState);
    bitWrite(bitsToSend, 7,whichState);
  }else if(digit==1){
    bitWrite(bitsToSend, 4, whichState);
    bitWrite(bitsToSend, 6, whichState);
  }else if(digit==2){
    bitWrite(bitsToSend, 2, whichState);
    bitWrite(bitsToSend, 3, whichState);
    bitWrite(bitsToSend, 4, whichState);
    bitWrite(bitsToSend, 5, whichState);
    bitWrite(bitsToSend, 7, whichState);
  }else if(digit==3){
    bitWrite(bitsToSend, 2, whichState);
    bitWrite(bitsToSend, 3, whichState);
    bitWrite(bitsToSend, 4, whichState);
    bitWrite(bitsToSend, 6, whichState);
    bitWrite(bitsToSend, 7, whichState);
  }else if(digit==4){
    bitWrite(bitsToSend, 1, whichState);
    bitWrite(bitsToSend, 3, whichState);
    bitWrite(bitsToSend, 4, whichState);
    bitWrite(bitsToSend, 6, whichState);
  }else if(digit==5){
    bitWrite(bitsToSend, 1, whichState);
    bitWrite(bitsToSend, 2, whichState);
    bitWrite(bitsToSend, 3, whichState);
    bitWrite(bitsToSend, 6, whichState);
    bitWrite(bitsToSend, 7, whichState);
  }else if(digit==6){
    bitWrite(bitsToSend, 1, whichState);
    bitWrite(bitsToSend, 2, whichState);
    bitWrite(bitsToSend, 3, whichState);
    bitWrite(bitsToSend, 5, whichState);
    bitWrite(bitsToSend, 6, whichState);
    bitWrite(bitsToSend, 7, whichState);
  }else if(digit==7){
    bitWrite(bitsToSend, 2, whichState);
    bitWrite(bitsToSend, 4, whichState);
    bitWrite(bitsToSend, 6, whichState);
  }else if(digit==8){
    bitWrite(bitsToSend, 1, whichState);
    bitWrite(bitsToSend, 2, whichState);
    bitWrite(bitsToSend, 3, whichState);
    bitWrite(bitsToSend, 4, whichState);
    bitWrite(bitsToSend, 5, whichState);
    bitWrite(bitsToSend, 6, whichState);
    bitWrite(bitsToSend, 7, whichState);
  }else if(digit==9){
    bitWrite(bitsToSend, 1, whichState);
    bitWrite(bitsToSend, 2, whichState);
    bitWrite(bitsToSend, 3, whichState);
    bitWrite(bitsToSend, 4, whichState);
    bitWrite(bitsToSend, 6, whichState);
    bitWrite(bitsToSend, 7, whichState);
  }
  // shift the bits out:
  shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend);

    // turn on the output so the LEDs can light up:
  digitalWrite(latchPin, HIGH);

}
