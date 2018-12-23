#include <RtcDS3231.h>
#include <JQ6500_Serial.h>
#include <SoftwareSerial.h>
#include <Wire.h>

JQ6500_Serial mp3(2,3); //create an mp3 object
RTC_DS1307 rtc; //create an rtc object

void setup() {
  Serial.begin(57600);
  Serial.println("Audio Calendar by Uwe");
  
  pinMode(4, INPUT);
  pinMode(13, OUTPUT);

  // setup the mp3 module 
  mp3.begin(9600);
  mp3.reset();
  delay(500);
  mp3.setVolume(22);
  mp3.setLoopMode(MP3_LOOP_NONE);

  // setup rtc
  Wire.begin();
  rtc.begin();
  rtc.adjust(DateTime(__DATE__, __TIME__));
}

void loop() {
  DateTime now = rtc.now();
  if(mp3.getStatus() != MP3_STATUS_PLAYING) {
    Serial.print("playing track Number: ");
    Serial.println(now.day());

    mp3.playFileNumberInFolderNumber(now.month(), now.day());      
  }
  exit(0); 
}
