//BIBLIOTECAS --------------------------------------------------------------



#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Wire.h>
#include <DHT_U.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>



//DEFINIÇÃO ----------------------------------------------------------------



#define DHTPIN 2 //PINO DIGITAL UTILIZADO PELO DHT22
#define DHTTYPE DHT22 //DEFINE O MODELO DO SENSOR (DHT22 / AM2302)
#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)



//CONSTANTES ----------------------------------------------------------------

int pin2 = 4; // Alterando para a pinagem desejada
int pin1 = 3; // Alterando para a pinagem desejada
unsigned long duracao1;
unsigned long duracao2;
unsigned long tempoInicial;
unsigned long tempoAmostragem_ms = 3000;
unsigned long ocupacaoPulsoBaixo1 = 0;
unsigned long ocupacaoPulsoBaixo2 = 0;
float razao1 = 0;
float razao2 = 0;
float concentracao1 = 0;
float concentracao2 = 0;
int rLed = A1; // Laranja
int bLed = A2; // Azul
int oLed = A3; // Vermelho


DHT dht(DHTPIN, DHTTYPE); //PASSA OS PARÂMETROS PARA A FUNÇÃO
LiquidCrystal_I2C lcd(0x27,16,2);
Adafruit_BMP280 bmp; 


//CONFIGURAÇÕES-------------------------------------------------------------


void setup() {


  Serial.begin(9600);
  pinMode(4, INPUT); // Pin2 como 4
  pinMode(3, INPUT); // Pin1 como 3
  pinMode(oLed, OUTPUT);
  pinMode(bLed, OUTPUT);
  pinMode(rLed, OUTPUT);

  tempoInicial = millis();

  //CONFIGURAÇÕES DO LCD
  lcd.init();
  lcd.clear();
  lcd.backlight();
  dht.begin();


  //CONFIGURAÇÃO DO BMP
  while ( !Serial ) delay(100);   
  Serial.println(F("BMP280 test"));
  unsigned status;
  
  status = bmp.begin(0x76);
 
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     
                  Adafruit_BMP280::SAMPLING_X2,    
                  Adafruit_BMP280::SAMPLING_X16,   
                  Adafruit_BMP280::FILTER_X16,     
                  Adafruit_BMP280::STANDBY_MS_500);

}

//REPETIÇÃO-----------------------------------------------------------------

void loop() {

   duracao1 = pulseIn(pin1, LOW);
  duracao2 = pulseIn(pin2, LOW);
  ocupacaoPulsoBaixo1 = ocupacaoPulsoBaixo1 + duracao1;
  ocupacaoPulsoBaixo2 = ocupacaoPulsoBaixo2 + duracao2;

  if ((millis() - tempoInicial) > tempoAmostragem_ms) {
    razao1 = ocupacaoPulsoBaixo1 / (tempoAmostragem_ms * 10.0);
    concentracao1 = 1.1 * pow(razao1, 3) - 3.8 * pow(razao1, 2) + 520 * razao1 + 0.62;

    razao2 = ocupacaoPulsoBaixo2 / (tempoAmostragem_ms * 10.0);
    concentracao2 = 1.1 * pow(razao2, 3) - 3.8 * pow(razao2, 2) + 520 * razao2 + 0.62;

    int qualidadeAr;
  
  //DECLARAÇÃO DAS VARIÁVEIS LOCAIS
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

     if (concentracao1 < 1000) {
      qualidadeAr = 1; // BOM
      digitalWrite(oLed, LOW);
      digitalWrite(bLed, HIGH);
      digitalWrite(rLed, LOW);
    } else if (concentracao1 >= 1000 && concentracao1 < 10000) {
      qualidadeAr = 2; // MÉDIO
      digitalWrite(oLed, HIGH);
      digitalWrite(bLed, LOW);
      digitalWrite(rLed, LOW);
    } else if (concentracao1 >= 10000) {
      qualidadeAr = 3; // PÉSSIMO
      digitalWrite(oLed, LOW);
      digitalWrite(bLed, LOW);
      digitalWrite(rLed, HIGH);
    }

    // Exibir a qualidade do ar no LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Qualidade do Ar:");

    lcd.setCursor(0, 1);
    switch (qualidadeAr) {
      case 1:
        lcd.setCursor(6,1);
        lcd.print("Bom");
        break;
      case 2:
        lcd.setCursor(4,1);
        lcd.print("Mediano");
        break;
      case 3:
        lcd.setCursor(2,1);
        lcd.print("Ruim");        
        break;

        ocupacaoPulsoBaixo1 = 0;
    ocupacaoPulsoBaixo2 = 0;
    tempoInicial = millis();
    }
  }
 }
}




