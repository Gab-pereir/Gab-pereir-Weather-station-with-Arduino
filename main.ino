//BIBLIOTECAS---------------------------------------------------------------



#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Wire.h>
#include <DHT_U.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>




//CONSTANTES----------------------------------------------------------------



#define DHTPIN 2 //PINO DIGITAL UTILIZADO PELO DHT22
#define DHTTYPE DHT22 //DEFINE O MODELO DO SENSOR (DHT22 / AM2302)
#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)
#define sensorPower 7
#define sensorPin 8


DHT dht(DHTPIN, DHTTYPE); //PASSA OS PARÂMETROS PARA A FUNÇÃO
LiquidCrystal_I2C lcd(0x27,16,2);
Adafruit_BMP280 bmp; 




//CONFIGURAÇÕES-------------------------------------------------------------


void setup() {

  //CONFIGURAÇÕES DO LCD
  lcd.init();
  lcd.clear();
  lcd.backlight();
  dht.begin();

  //CONFIGURAÇÃO DO SENSOR DE CHUVA
  pinMode(sensorPower, OUTPUT);
  digitalWrite(sensorPower, LOW);
  Serial.begin(9600);

  //CONFIGURAÇÃO DO BMP
  while ( !Serial ) delay(100);   
  Serial.println(F("BMP280 test"));
  unsigned status;
  
  status = bmp.begin(0x76);
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }

  
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     
                  Adafruit_BMP280::SAMPLING_X2,    
                  Adafruit_BMP280::SAMPLING_X16,   
                  Adafruit_BMP280::FILTER_X16,     
                  Adafruit_BMP280::STANDBY_MS_500);

}

//REPETIÇÃO-----------------------------------------------------------------

void loop() {
  
  delay(2000); 

  //DECLARAÇÃO DAS VARIÁVEIS
  float hum  = dht.readHumidity();   
  float temp = dht.readTemperature();
  float pre = bmp.readPressure();
  float alt = bmp.readAltitude(1013.25);

  lcd.clear();

  
    //CHECAR ESTADO DOS SENSORES
    if (isnan(hum) || isnan(temp)) {
    lcd.setCursor(0, 0);
    lcd.print("Erro");
  } else {

    //IMPRESSÃO DOS DADOS DE TEMPERATURA
    lcd.setCursor(2, 0);  
    lcd.print("Temperatura:");
    lcd.setCursor(5, 1);
    lcd.print(temp);    
    lcd.print((char)223); 
    lcd.print("C");
    delay (2000);
    lcd.clear();

    //IMPRESSÃO DOS DADOS DE UMIDADE
    lcd.setCursor(4, 0); 
    lcd.print("Umidade:");
    lcd.setCursor(5, 1);
    lcd.print(hum);     
    lcd.print("%");
    delay (2000);
    lcd.clear();

    //IMPRESSÃO DOS DADOS DE PRESSÃO
    lcd.setCursor(4, 0); 
    lcd.print("Pressao:");
    lcd.setCursor(2, 1);
    lcd.print(pre);      
    lcd.print(" Pa");
    delay (2000);
    lcd.clear();

    //IMPRESSÃO DOS DADOS DE ALTITUDE
    lcd.setCursor(4, 0); 
    lcd.print("Altitude:");
    lcd.setCursor(4, 1);
    lcd.print(alt);      
    lcd.print(" m");
    delay (2000);
    lcd.clear();
  }
}
