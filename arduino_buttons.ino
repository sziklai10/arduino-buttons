#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SPI.h>    
#include <OSCMessage.h>

EthernetUDP Udp;

//the Arduino's IP
IPAddress ip(192,168,0,19); //must be unique! First three numbers must be the same as the destination machine (subnet)
//destination IP
IPAddress outIp(192,168,0,12); //check the destination machine //164,11,214,124
const unsigned int outPort = 7500; //destination port
byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x12 }; // you can find this written on the board of some Arduino Ethernets or shields

const int ledPin = 2;
const int buttonPin = 4;
const int button1Pin = 5;
const int button2Pin = 6;
int buttonState = 0;
int button1State = 0;
int button2State = 0;

void setup (){

   Serial.begin(9600);

   Ethernet.begin(mac,ip);
    Udp.begin(8888);
    
   pinMode(ledPin, OUTPUT);
   pinMode(buttonPin, INPUT);
   pinMode(button1Pin, INPUT);
   pinMode(button2Pin, INPUT);
   
}

void loop (){

  buttonState = digitalRead(buttonPin);

  if (buttonState ==LOW) {

    digitalWrite(ledPin, LOW);
    Serial.println("LED ON +++++");
  }
  else {
    digitalWrite(ledPin, HIGH);
    Serial.println("LED OFF ---");
  }
  
  button1State = digitalRead(button1Pin);
    if (button1State == LOW) {

    digitalWrite(ledPin, LOW);
    Serial.println("LED ON +++++");
  }
  else {
    digitalWrite(ledPin, HIGH);
    Serial.println("LED OFF ---");
  }
  
   button2State = digitalRead(button2Pin);
    if (button2State == LOW) {

    digitalWrite(ledPin, LOW);
    Serial.println("LED ON +++++");
  }
  else {
    digitalWrite(ledPin, HIGH);
    Serial.println("LED OFF ---");
  }

  OSCMessage msg("/analogue");
  msg.add(buttonState);
  msg.add(button1State);
  msg.add(button2State);

  Udp.beginPacket(outIp, outPort);
  msg.send(Udp); // send the bytes to the SLIP stream
  Udp.endPacket(); // mark the end of the OSC Packet
  msg.empty(); // free space occupied by message
  
  delay(3000);
}
