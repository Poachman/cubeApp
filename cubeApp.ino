#include "config.h"
#include "cubeGFX.h"
#include "cubePattern.h"

#include "fading.h"
#include "planes.h"
#include "fallingPlanes.h"

#include <stdint.h>

fading* fadingPattern;
planes* planesPattern;
fallingPlanes* fallingPlanesPattern;

cubeGFX cube;

bool onlinePressed=false;
bool lastOnline=true;
SYSTEM_MODE(SEMI_AUTOMATIC);  //don't connect to the internet on boot
#define BUTTON D6 //press this button to connect to the internet
#define MODE D4

uint8_t PIXEL_RGB[NUM_STRIPS * NUM_LEDS_PER_STRIP * 3];

void setup() {
  randomSeed(analogRead(A0));
  Serial.begin(115200);
  delay(2000);
  pinMode(GAIN_CONTROL, OUTPUT);
    digitalWrite(GAIN_CONTROL, LOW);

  pinMode(D0,OUTPUT);  //PB7
  pinMode(D1,OUTPUT); //PB6
  pinMode(D2,OUTPUT);  //BP5
  pinMode(D3,OUTPUT);  //PB4
  pinMode(A2,OUTPUT);  //PA4
  pinMode(A3,OUTPUT); //PA5
  pinMode(A4,OUTPUT);  //BA6
  pinMode(A5,OUTPUT);  //PA7

  initCloudButton();

  pinMode(D7, OUTPUT);
  digitalWrite(D7, HIGH);

  fadingPattern = new fading();
  planesPattern = new planes();
  fallingPlanesPattern = new fallingPlanes();
}

uint8_t pixel = 0;

void loop() {
//   Serial.println("Loop-Start");
    fallingPlanesPattern->doFrame();

    checkCloudButton();
    show();
//  Serial.println("Loop-End");
}

//sets up the online/offline switch
void initCloudButton()
{
  //set the input mode for the 'connect to cloud' button
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(MODE, INPUT_PULLUP);
    if(!digitalRead(MODE))  //if the wifi button is held down on boot, do a hard reset.  At any other time, keep the firmware, but try to add new wifi creds
    {
        WiFi.on();
        WiFi.clearCredentials();
        System.factoryReset();
    }
    //a.k.a. onlinePressed is HIGH when the switch is set to 'online' and LOW when the switch is set to 'offline'
    onlinePressed=!digitalRead(BUTTON);
    if(onlinePressed)
        Particle.connect();
}

//checks to see if the 'online/offline' switch is switched
void checkCloudButton()
{
    //if the 'connect to cloud' button is pressed, try to connect to wifi.
    //otherwise, run the program
    //note -- how does this behave when there are no wifi credentials loaded on the spark?

    //onlinePressed is HIGH when the switch is _not_ connected and LOW when the switch is connected
    //a.k.a. onlinePressed is HIGH when the switch is set to 'online' and LOW when the switch is set to 'offline'
    onlinePressed=!digitalRead(BUTTON);

    if((onlinePressed)&&(!lastOnline))  //marked as 'online'
    {
        lastOnline=onlinePressed;
        Particle.connect();
    }

    else if((!onlinePressed)&&(lastOnline))  //marked as 'offline'
    {
        lastOnline=onlinePressed;
        Particle.disconnect();
    }

    lastOnline=onlinePressed;

    if(!digitalRead(MODE))
        WiFi.listen();
}

void show() {
    uint8_t *ptrA,*ptrB,*ptrC,*ptrD,*ptrE,*ptrF,*ptrG,*ptrH;
    uint8_t mask;
    uint8_t c=0,a=0,b=0,j=0;

    GPIOA->BSRRH=0xE0;    //set A3~A5 to low
    GPIOB->BSRRH=0xF0;    //set D0~D4 to low
    GPIOC->BSRRH=0x04;     //set A2 to low

    ptrA=&PIXEL_RGB[0];
    ptrB=ptrA+NUM_LEDS_PER_STRIP*3;
    ptrC=ptrB+NUM_LEDS_PER_STRIP*3;
    ptrD=ptrC+NUM_LEDS_PER_STRIP*3;
    ptrE=ptrD+NUM_LEDS_PER_STRIP*3;
    ptrF=ptrE+NUM_LEDS_PER_STRIP*3;
    ptrG=ptrF+NUM_LEDS_PER_STRIP*3;
    ptrH=ptrG+NUM_LEDS_PER_STRIP*3;

    delay(1);
    __disable_irq();

    uint16_t i=NUM_LEDS_PER_STRIP*3;   //3 BYTES = 1 PIXEL

    while(i) { // While bytes left... (3 bytes = 1 pixel)
      i--;
      mask = 0x80; // reset the mask
      j=0;
        // reset the 8-bit counter
      do {
        a=0;
        b=0;
        c=0;

//========Set D0~D4, i.e. B7~B4=======
        if ((*ptrA)&mask) b|=0x10;// if masked bit is high
    //    else "nop";
        b<<=1;
        if ((*ptrB)&mask) b|=0x10;// if masked bit is high
    //    else "nop";
        b<<=1;
        if ((*ptrC)&mask) b|=0x10;// if masked bit is high
    //    else "nop";
        b<<=1;
        if ((*ptrD)&mask) b|=0x10;// if masked bit is high
   //     else "nop";

//=========Set A2, i.g. C2==========
        if ((*ptrE)&mask) c|=0x04;// if masked bit is high
   //     else "nop";

        GPIOA->BSRRL=0xE0;    //set A3~A5 to high
        GPIOB->BSRRL=0xF0;    //set D0~D4 to high
        GPIOC->BSRRL=0x04;    //set A2 to high


//=========Set A3~A5, i.e. A5~A7========
        if ((*ptrF)&mask) a|=0x80;// if masked bit is high
        // else "nop";
        a>>=1;
        if ((*ptrG)&mask) a|=0x80;// if masked bit is high
   //     else "nop";
        a>>=1;
        if ((*ptrH)&mask) a|=0x80;// if masked bit is high

        a=(~a)&0xE0;
        b=(~b)&0xF0;
        c=(~c)&0x04;
        GPIOA->BSRRH=a;
        GPIOB->BSRRH=b;
        GPIOC->BSRRH=c;
        mask>>=1;
         asm volatile(
            "mov r0, r0" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            ::: "r0", "cc", "memory");
        GPIOA->BSRRH=0xE0;    //set all to low
        GPIOB->BSRRH=0xF0;    //set all to low
        GPIOC->BSRRH=0x04;    //set all to low
          // WS2812 spec             700ns HIGH
          // Adafruit on Arduino    (meas. 812ns)
          // This lib on Spark Core (meas. 792ns)
          /*
        if(j<7) {
          asm volatile(
            "mov r0, r0" "\n\t"
            ::: "r0", "cc", "memory");
        }
        */

      } while ( ++j < 8 ); // ...one color on a pixel done
      ptrA++;
      ptrB++;
      ptrC++;
      ptrD++;
      ptrE++;
      ptrF++;
      ptrG++;
      ptrH++;
    } // end while(i) ... no more pixels
    __enable_irq();
}
