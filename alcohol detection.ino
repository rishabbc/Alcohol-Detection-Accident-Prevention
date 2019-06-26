#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd( 13, 12, 5, 4, 3, 2 );
SoftwareSerial serial_gps(8, 7);
SoftwareSerial gsmSerial(10,11);
TinyGPSPlus gps;

double latitude, longitude;
const int alcoholA0 = A0;
const int alcoholThres=40;
const int blow=150;   
int minutes = 0; 
int seconds = 5; 
double analogSensor;
String link;
String sms;
String alco;
void setup() 
{
  pinMode(alcoholA0, INPUT);
  analogWrite(6,30);
  lcd.begin(16, 2);
  Serial.begin(9600);
  serial_gps.begin(9600);
  delay(5000);
  lcd.print("WAITING FOR GPS");
}
void loop() 
{
  serial_gps.listen();
  while(serial_gps.available()) 
  
    gps.encode(serial_gps.read());
  
  if(gps.location.isUpdated()) 
  
    latitude = gps.location.lat();
    longitude = gps.location.lng();
    link = "http://www.google.com/maps/place/" + String(latitude,6) + "," + String(longitude,6) ;
    Serial.println(link);
    delay(5000);
    goto skip;
    skip1:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("LATITUDE : ");
    lcd.setCursor(0,1);
    lcd.print(latitude,6);
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("LONGITUDE : ");
    lcd.setCursor(0,1);
    lcd.print(longitude, 6);
    delay(3000);
    lcd.clear();
    skip:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("BREATH ALCOHOL");
    lcd.setCursor(0,1);
    lcd.print("DETECTION METER");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("BLOW FOR");
    lcd.setCursor(0,1);
    lcd.print("5 SECONDS");
    delay(3500);
    int analogSensor = analogRead(alcoholA0);
    alco=String(analogSensor)+" "+"ppm";
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("ALCOHOL METER:");
    lcd.setCursor(0,1);
    lcd.print(alco);
    delay(3000);
    if (analogSensor > alcoholThres)
    
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("ALCOHOL DETECTED");
      lcd.setCursor(0,1);
      lcd.print("SENDING MESSAGE");
      delay(1000);
      sms="Alcohol Detected\nAlcohol Meter:"+String(alco)+"\nLocation at:\n"+String(link);
      Serial.println(sms);
      delay(2500);
      alcoholDetected();
      alcoholDetected2();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("LOCATION SENT TO");
      delay(3000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("FAMILY MEMBERS");
      lcd.setCursor(0,1);
      lcd.print("PH NO:XXXXXXXXXX");
      delay(3000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("AND ");
      lcd.setCursor(0,1);
      lcd.print("PH NO:XXXXXXXXXX");
      delay(3000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("YOUR LOCATION IS");
      delay(3000);
      goto skip1;
     } 
     else
     
      delay(3000); 
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("NO ALCOHOL");
      lcd.setCursor(0,1);
      lcd.print("DETECTED");
      delay(3000);
      lcd.clear();
     }   
    
  
void alcoholDetected()
  
      delay(5000);
      gsmSerial.begin(9600);
      gsmSerial.println("AT+CMGF=1");
      delay(1000);
      gsmSerial.println("AT+CMGS=\"+91XXXXXXXXXX\"\r");
      delay(1000);
      Serial.println(sms);
      gsmSerial.println(sms);
      gsmSerial.println((char)26);
      Serial.println("gsm connected");
  
  void alcoholDetected2()
  
      delay(5000);
      gsmSerial.begin(9600);
      gsmSerial.println("AT+CMGS=\"+91XXXXXXXXXX\"\r");
      delay(1000);
      Serial.println(sms);
      gsmSerial.println(sms);
      delay(1000);
      gsmSerial.println((char)26);
      Serial.println("gsm connected");
  } 
