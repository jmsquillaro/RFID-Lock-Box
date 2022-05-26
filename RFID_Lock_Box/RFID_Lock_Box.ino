#include <SPI.h> 
#include <RFID.h>
#include <ESP32Servo.h>
#include "config.h"

//Code created by Joseph M. Squillaro for University of Pennsylvania ESE 190 Final Project

#define BUZZER_PIN 13

AdafruitIO_Feed *authorizedUIDs = io.feed("authorizedUIDs");

RFID rfid(23, HIGH);       //D23:pin of tag reader SDA. D[HIGH]:pin of tag reader RST 
unsigned char status; 
unsigned char str[MAX_LEN]; //MAX_LEN is 16: size of the array 

const String defaultAccessUID = {"2125801539"};
String accessGranted [1] = {};  //RFID serial numbers to grant access to
int accessGrantedSize = 1;                                //The number of serial numbers

Servo lockServo;                //Servo for locking mechanism
int lockPos = 360;               //Locked position limit
int unlockPos = 90;             //Unlocked position limit
boolean locked = true;

void setup() {
  Serial.begin(9600);     //Serial monitor is only required to get tag ID numbers and for troubleshooting
  SPI.begin();            //Start SPI communication with reader

  //WIFI Setup
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  authorizedUIDs-> onMessage(handleMessage);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  authorizedUIDs->get();
  Serial.println();
  //End WIFI Setup

// Cannot get last value from feed, so it is currently hardcoded
//  handleMessage(authorizedUIDs->lastValue());
  
  rfid.init();            //RFID initialization 
  lockServo.attach(12);
  lockServo.write(lockPos);         //Move servo into locked position
  Serial.println("Place card/tag near reader...");
}

void handleMessage(AdafruitIO_Data *data) {
   String newData;
   Serial.print("Receiving Data: "); 
   Serial.println(data->toString());
   newData = data->toString();
   accessGranted [1] = {newData};
}

void loop() {
  io.run();
  
  if (rfid.findCard(PICC_REQIDL, str) == MI_OK)   //Wait for a tag to be placed near the reader
  { 
    Serial.println("Card found"); 
    String temp = "";                             //Temporary variable to store the read RFID number
    if (rfid.anticoll(str) == MI_OK)              //Anti-collision detection, read tag serial number 
    { 
      Serial.print("The card's ID number is : "); 
      for (int i = 0; i < 4; i++)                 //Record and display the tag serial number 
      { 
        temp = temp + (0x0F & (str[i] >> 4)); 
        temp = temp + (0x0F & str[i]); 
      } 
      Serial.println (temp);
      checkAccess (temp);     //Check if the identified tag is an allowed to open tag
    } 
    rfid.selectTag(str); //Lock card to prevent a redundant read, removing the line will make the sketch read cards continually
  }
  rfid.halt();
}

void checkAccess (String temp)    //Function to check if an identified tag is registered to allow access
{
  boolean granted = false;
  for (int i=0; i <= (accessGrantedSize-1); i++)    //Runs through all tag ID numbers registered in the array
  {
    if((defaultAccessUID == temp) || (accessGranted[i] == temp))            //If a tag is found then open/close the lock
    {
      Serial.println ("Access Granted");
      granted = true;
      if (locked == true)         //If the lock is closed then open it
      {
          lockServo.write(unlockPos);
          locked = false;
          tone(BUZZER_PIN, 330, 500);
          delay(250);
          tone(BUZZER_PIN, 360, 500);
          delay(250);
          noTone(BUZZER_PIN);
      }
      else if (locked == false)   //If the lock is open then close it
      {
          lockServo.write(lockPos);
          locked = true;
          tone(BUZZER_PIN, 330, 500);
          delay(250);
          tone(BUZZER_PIN, 311, 500);
          delay(250);
          noTone(BUZZER_PIN);
      }
    }
  }
  if (granted == false)     //If the tag is not found
  {
    Serial.println ("Access Denied");
    tone(BUZZER_PIN, 300, 1500);
    noTone(BUZZER_PIN);
  }
}
