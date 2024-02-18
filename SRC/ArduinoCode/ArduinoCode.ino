#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <Keypad_I2C.h>
#include <Keypad.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <EEPROM.h>

#define ONE_WIRE_BUS 13

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

Adafruit_PCD8544 display = Adafruit_PCD8544(12, 11, 10, 9, 8);

const byte pompa = 3;
const byte dmuchawa = 4;
int tzadana = 29;
int tpompa = 27;
int temperatura;
byte ekran = 0;
byte zmiana = 0;
byte uruchomiony=0;
byte wygaszanie=0;

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {0, 1, 2, 3};
byte colPins[COLS] = {4, 5, 6, 7};

int i2caddress = 0x20;

Keypad_I2C kpd = Keypad_I2C( makeKeymap(keys), rowPins, colPins, ROWS, COLS, i2caddress );

int odczytLiczba()
{
  return odczytCyfra() * 10 + odczytCyfra();
}

int odczytCyfra()
{
  switch (kpd.getKey())
  {
    case '0': return 0; break;
    case '1': return 1; break;
    case '2': return 2; break;
    case '3': return 3; break;
    case '4': return 4; break;
    case '5': return 5; break;
    case '6': return 6; break;
    case '7': return 7; break;
    case '8': return 8; break;
    case '9': return 9; break;
    default: odczytCyfra();
  }
}

void EkranStartowy()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(13, 0);
  display.print("Sterownik");
  display.println();
  display.print("pieca CO v4.20");
  display.println();
  display.println();
  display.print("A-Temperatury");
  display.println();
  display.print("B-Ekran Stanu");
  display.println();
  display.print("C-Ust. pompy");
  display.display();
}

void EkranTemperatury ()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  sensors.requestTemperatures();
  display.println("Temp. pieca:");
  display.print(temperatura);
  display.print(" C");
  display.println();
  display.println("Temp. zadana:");
  if (zmiana == 1)
  {
    display.print("Edycja");
    display.display();
    tzadana = odczytLiczba();
    EEPROM.put(100, tzadana);
    zmiana = 0;
  }
  EEPROM.get(100, tzadana);
  display.print(tzadana);
  display.print(" C");
  display.println();
  display.display();
}

void EkranStanu()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  display.print("Stan systemu: ");
  display.println();
  display.print("Pompa: ");
  if (digitalRead(pompa) == 0)
  {
    display.println("WYL");
    display.display();
  } else display.println("WL");
  display.print("Dmuchawa:");
  if (digitalRead(dmuchawa) == 0)
  {
    display.println("WYL");
    display.display();
  } else display.println("WL");
  display.display();
}

void EkranPompa()
{
  display.clearDisplay();
  display.setTextSize(0.8);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  display.println("Tem. wl. pompy");
  if (zmiana == 1)
  {
    display.print("Edycja");
    display.display();
    tpompa = odczytLiczba();
    EEPROM.put(0, tpompa);
    zmiana = 0;
  }
  EEPROM.get(0, tpompa);
  display.print(tpompa);
  display.print(" C");
  display.display();
}

void setup()
{
  display.begin();
  display.setContrast(60);
  EkranStartowy();
  Serial.begin(9600);
  sensors.begin();
  Wire.begin(); 
  kpd.begin();
  pinMode(pompa, OUTPUT);
  pinMode(dmuchawa, OUTPUT);
}

void loop() {
  temperatura=sensors.getTempCByIndex(0);
  char klawisz = kpd.getKey();
  
  switch (klawisz)
  {
    case 'A': ekran = 1; break;
    case 'B': ekran = 2; break;
    case 'C': ekran = 3; break;
    case '#': ekran = 4; break;
    default: NULL; break;
  }

  switch (ekran)
  {
    case 1: EkranTemperatury(); break;
    case 2: EkranStanu(); break;
    case 3: EkranPompa(); break;
    case 4: EkranStartowy(); break;
    default: NULL; break;
  }

  if (klawisz != NO_KEY) Serial.println(klawisz);

  if (klawisz == '*') zmiana = 1;
  
  if(klawisz == 'D') {
    wygaszanie=0;
    uruchomiony=0;
  }

  if(klawisz == '#') {
    sensors.requestTemperatures();
    int i = 0;
    float temperatureC = sensors.getTempCByIndex(i);
    Serial.print(" Temperatura: ");
    Serial.print(temperatureC);
    Serial.println(" °C");
  }

  if ((temperatura>=tzadana)||(wygaszanie==1)) digitalWrite(dmuchawa,LOW);
  else digitalWrite(dmuchawa,HIGH);
  
  if(temperatura>tpompa) {
    digitalWrite(pompa,HIGH);
    uruchomiony=1;
  } else digitalWrite(pompa,LOW);
  
  if((uruchomiony==1)&&(digitalRead(pompa)==0)) wygaszanie=1;

}