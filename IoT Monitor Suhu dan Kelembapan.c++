#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int ledRed = 19;
int ledBlue = 18;
int ledWhite = 17;
int pinBuz = 16;

DHT dht(12, DHT22);
void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);

  if(!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println(F("Failed to start SSD1306 OLED"));
    while(1);
  }

  dht.begin();

  pinMode(ledRed, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledWhite, OUTPUT);

  ledcAttachPin(pinBuz, 0);
}

void loop() {
  float suhu_c = dht.readTemperature();
  float kelembapan = dht.readHumidity();

  float suhu_k = dht.readTemperature() + 273.15;
  float suhu_f = 1.8*dht.readTemperature() + 32;

  if (suhu_c <= 15 && kelembapan <=10){
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(WHITE);
    oled.setCursor(0, 2);

    tone(pinBuz, 1000);
    delay(200);
    tone(pinBuz, 800);
    delay(200);

    digitalWrite(ledRed, LOW);
    digitalWrite(ledBlue, LOW);
    digitalWrite(ledWhite, HIGH);

    oled.print("Celcius : ");
    oled.println(suhu_c);
    oled.print("Kelvin : ");
    oled.println(suhu_k);
    oled.print("Fahrenheit : ");
    oled.println(suhu_f);
    oled.display();

  }else if(suhu_c >= 16 && suhu_c <= 27 && kelembapan >= 11 && kelembapan <=50){
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(WHITE);
    oled.setCursor(0, 2);

    noTone(pinBuz);

    digitalWrite(ledRed, LOW);
    digitalWrite(ledBlue, HIGH);
    digitalWrite(ledWhite, LOW);

    oled.print("Celcius : ");
    oled.println(suhu_c);
    oled.print("Kelvin : ");
    oled.println(suhu_k);
    oled.print("Fahrenheit : ");
    oled.println(suhu_f);
    oled.display();

  }else if(suhu_c > 27 && kelembapan >= 51){
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(WHITE);
    oled.setCursor(0, 2);

    tone(pinBuz, 800);

    digitalWrite(ledRed, HIGH);
    digitalWrite(ledBlue, LOW);
    digitalWrite(ledWhite, LOW);

    oled.print("Celcius : ");
    oled.println(suhu_c);
    oled.print("Kelvin : ");
    oled.println(suhu_k);
    oled.print("Fahrenheit : ");
    oled.println(suhu_f);
    oled.display();
  }else{
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(WHITE);
    oled.setCursor(0, 2);

    noTone(pinBuz);

    digitalWrite(ledRed, LOW);
    digitalWrite(ledBlue, LOW);
    digitalWrite(ledWhite, LOW);

    oled.print("menyala abangkuu!!!");
    oled.display();
  }

  delay(1000);
}
