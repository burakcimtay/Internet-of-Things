#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#ifndef UNIT_TEST
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <SPI.h>
#endif
BlynkTimer timer;
IRsend irsend(D1);             // IR Ledimizin bağlı olduğu digital pin (D1)

#define BLYNK_PRINT Serial

#define ac_kapa 0xE0E040BF// Kumandadan tespit ettiğimiz kod
#define kanal_yukari 0x80BF53AC
#define kanal_asagi 0x80BF4BB4
#define ses_ac 0x80BF837C
#define ses_kis 0x80BF9966

char auth[] = "Your Blynk Token";

// Kendi WiFi Bilgilerini buraya yaz
char ssid[] = "WiFi Name";
char pass[] = "Password";

int blynk_V1;    
int blynk_V2;
int blynk_V3;
int blynk_V4;
int blynk_V5;
      
void setup()
{
  irsend.begin();
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(100L, butonpressed);
  Blynk.connect();
}
BLYNK_WRITE(V1)
{
  blynk_V1 = param.asInt();
  if (blynk_V1 == 1)
  {
    butonpressed ();
  }
  else
  {
    blynk_V1=LOW;
  }
}

BLYNK_WRITE(V2)
{
  blynk_V2 = param.asInt();
  if (blynk_V2 == 1)
  {
    butonpressed ();
  }
  else
  {
    blynk_V2=LOW;
  }
}

BLYNK_WRITE(V3)
{
  blynk_V3 = param.asInt();
  if (blynk_V3 == 1)
  {
    butonpressed ();
  }
  else
  {
    blynk_V3=LOW;
  }
}

BLYNK_WRITE(V4)
{
  blynk_V4 = param.asInt();
  if (blynk_V4 == 1)
  {
    butonpressed ();
  }
  else
  {
    blynk_V4=LOW;
  }
}


BLYNK_WRITE(V5)
{
  blynk_V5 = param.asInt();
  if (blynk_V5 == 1)
  {
    butonpressed ();
  }
  else
  {
    blynk_V5=LOW;
  }
}

void butonpressed ()
{
  if (blynk_V1)
  {
    irsend.sendSAMSUNG(ac_kapa, 32);        // Kumanda tipini ve bitini ayarladık
    delay(10);
    timer.setTimeout(500L, []() {  
        Blynk.virtualWrite(V1, LOW);  // Blynk serverinde V1'i 0 yap
      });  // END Timer Function

    blynk_V1=LOW;
    
  }
  if (blynk_V2)
  {
    irsend.sendNEC(kanal_yukari, 32);        // Kumanda tipini ve bitini ayarladık
    delay(10);
    timer.setTimeout(500L, []() {  
        Blynk.virtualWrite(V2, LOW);  // Blynk serverinde V2'i 0 yap
      });  // END Timer Function

    blynk_V2=LOW;
    
  }

  if (blynk_V3)
  {
    irsend.sendNEC(kanal_asagi, 32);        // Kumanda tipini ve bitini ayarladık
    delay(10);
    timer.setTimeout(500L, []() {  
        Blynk.virtualWrite(V3, LOW);  // Blynk serverinde V3'i 0 yap
      });  // END Timer Function

    blynk_V3=LOW;
    
  }

  if (blynk_V4)
  {
    irsend.sendNEC(ses_ac, 32);        // Kumanda tipini ve bitini ayarladık
    delay(10);
    timer.setTimeout(500L, []() {  
        Blynk.virtualWrite(V4, LOW);  // Blynk serverinde V4'i 0 yap
      });  // END Timer Function

    blynk_V4=LOW;
    
  }

  if (blynk_V5)
  {
    irsend.sendNEC(ses_kis, 32);        // Kumanda tipini ve bitini ayarladık
    delay(10);
    timer.setTimeout(500L, []() {  
        Blynk.virtualWrite(V5, LOW);  // Blynk serverinde V5'i 0 yap
      });  // END Timer Function

    blynk_V5=LOW;
    
  }
}
void loop()
{
  Blynk.run();
  timer.run();
}
