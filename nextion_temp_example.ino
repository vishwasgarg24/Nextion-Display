 #include <SimpleDHT.h>

// for DHT22, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT22 = 4;
SimpleDHT22 dht22(pinDHT22);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // start working...

  
  // read without samples.
  // @remark We use read2 to get a float data, such as 10.1*C
  //    if user doesn't care about the accurate data, use read to get a byte data, such as 10*C.
  float temperature = 0;
  float humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht22.read2(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
   delay(2000);
    return;
  }
  
  
   Serial.print("voltage1.val=");              //We print the variable we want to cahnge on the screen
  Serial.print((int)temperature);                        //Print the value we want to be displayed
  Serial.write(0xff);                         //Always add 3 full bytes after...       
  Serial.write(0xff);
  Serial.write(0xff);
  delay(500);
  Serial.print("n0.val="); 
  Serial.print((int)humidity);
  Serial.write(0xff);                         //Always add 3 full bytes after...       
  Serial.write(0xff);
  Serial.write(0xff);
  delay(500);
  
  
  

}
