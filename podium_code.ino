#include "Nextion.h"
#include <Servo.h>
Servo myservo; 


// Declare a text object [page id:0,component id:2, component name: "textNumber"].
//NexText textNumber = NexText(0, 2, "textNumber");

// Declare a button object [page id:0,component id:3, component name: "buttonPlus"].
NexDSButton buttonup = NexDSButton(2, 6, "up");
NexDSButton buttondown = NexDSButton(2, 7, "down");
NexDSButton buttoninc = NexDSButton(3, 6, "inc");
NexDSButton buttondec = NexDSButton(3, 7, "dec");
NexButton buttonhdmi = NexButton(4, 3, "b1");
NexDSButton buttonunlock = NexDSButton(5, 3, "b1");
NexButton buttoncpu = NexButton(6, 3, "cppu");
//NexDSButton bt0 = NexDSButton(0, 1, "bt0");

// Declare a button object [page id:0,component id:4, component name: "buttonMinus"].
//NexButton buttonMinus = NexButton(0, 4, "buttonMinus");


char buffer[10] = {0};


/*
   Register object textNumber, buttonPlus, buttonMinus, to the touch event list.
*/
NexTouch *nex_listen_list[] =
{
  //&textNumber,
  &buttonup,
  &buttondown,
  &buttoninc,
  &buttondec,
  &buttonhdmi,
  &buttonunlock,
  &buttoncpu,
  NULL
};



/*
   Button0 component pop callback function.
   In this example,the value of the text component will plus one every time when button0 is released.
*/
/*void buttonPlusPushCallback(void *ptr)
{
  dbSerialPrintln("buttonPlusPushCallback");

  if (number < 100) number += 1;

  memset(buffer, 0, sizeof(buffer)); // clear buffer
  itoa(number, buffer, 10);
  textNumber.setText(buffer);
}*/
void buttonupPushCallback(void *ptr){Serial.println("BUTTON PRESSED-UP");
digitalWrite(10,LOW);
digitalWrite(11,HIGH);
    }
void buttondownPushCallback(void *ptr){Serial.println("BUTTON PRESSED-DOWN"); 
digitalWrite(11,LOW);
digitalWrite(10,HIGH);
   }
void buttonincPushCallback(void *ptr){Serial.println("BUTTON PRESSED-INC");
digitalWrite(12,LOW);
digitalWrite(13,HIGH);
   }
void buttondecPushCallback(void *ptr){Serial.println("BUTTON PRESSED-DEC");
digitalWrite(13,LOW);
digitalWrite(12,HIGH);
   }
void buttonupPopCallback(void *ptr){Serial.println("BUTTON RELEASED-UP");
digitalWrite(10,HIGH);
digitalWrite(11,HIGH);
    }
void buttondownPopCallback(void *ptr){Serial.println("BUTTON RELEASED-DOWN");
digitalWrite(10,HIGH);
digitalWrite(11,HIGH);
    }
void buttonincPopCallback(void *ptr){Serial.println("BUTTON RELEASED-INC");
digitalWrite(12,HIGH);
digitalWrite(13,HIGH);
   }
void buttondecPopCallback(void *ptr){Serial.println("BUTTON RELEASED-DEC");
digitalWrite(12,HIGH);
digitalWrite(13,HIGH);
   }
void buttonhdmiPushCallback(void *ptr){Serial.println("BUTTON PRESSED-HDMI");
digitalWrite(7,LOW);
delay(100);
digitalWrite(7,HIGH); 
   } 
void buttonunlockPushCallback(void *ptr){Serial.println("BUTTON PRESSED-UNLOCK"); 
digitalWrite(8,HIGH);

   }
void buttonunlockPopCallback(void *ptr){Serial.println("BUTTON RELEASED-UNLOCK"); 
digitalWrite(8,LOW);
   }
void buttoncpuPushCallback(void *ptr){Serial.println("BUTTON PRESSED-CPU"); 
myservo.write(0);
delay(1000);
myservo.write(180);

 }

/*
   Button1 component push callback function.
   In this example,the value of the text component will minus one every time when button1 is pressed.
*/
/*void buttonMinusPushCallback(void *ptr)
{
  dbSerialPrintln("buttonMinusPushCallback");

  if (number > 0) number -= 1;
  
  memset(buffer, 0, sizeof(buffer));  // clear buffer
  itoa(number, buffer, 10);
  textNumber.setText(buffer);
}*/

void setup(void)
{myservo.attach(9);
myservo.write(180);
delay(1000);
  /* Set the baudrate which is for debug and communicate with Nextion screen. */
  nexInit();
  
  Serial.begin(9600);

  Serial.println("Start");
  for(int x=7;x<14;x++){
    Serial.println(x);
  pinMode(x,OUTPUT);
  if(x==8){
  digitalWrite(x,LOW);
    
  }
  else{
    
    digitalWrite(x,HIGH);
    }
  }
  /* Register the pop event callback function of the current button0 component. */
  //buttonPlus.attachPush(buttonPlusPushCallback);

  /* Register the pop event callback function of the current button1 component. */
  //buttonMinus.attachPush(buttonMinusPushCallback);
  buttonup.attachPush(buttonupPushCallback);
  buttondown.attachPush(buttondownPushCallback);
  buttoninc.attachPush(buttonincPushCallback);
  buttondec.attachPush(buttondecPushCallback);
  buttonhdmi.attachPush(buttonhdmiPushCallback);
  buttonunlock.attachPush(buttonunlockPushCallback);
  buttoncpu.attachPush(buttoncpuPushCallback);
  buttonup.attachPop(buttonupPopCallback);
  buttondown.attachPop(buttondownPopCallback);
  buttoninc.attachPop(buttonincPopCallback);
  buttondec.attachPop(buttondecPopCallback);
  buttonunlock.attachPop(buttonunlockPopCallback);


  dbSerialPrintln("Setup done");
}

void loop(void)
{
  nexLoop(nex_listen_list);
}
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
