# CoalFurnaceController

#### Repository structure:
\PPT - the catalog contains the presentation of the project in its final version, i.e., supplemented with conclusions after completion of work,
\SCH - complete project with PROTELA or EAGLE (without backup files) but with all necessary libraries (please check correctness!!!) additionally, there should be JPG or PDF files with schematics and views of the printed circuit board layers for quick preview without the need to open the entire project.
\SRC - if a microcontroller was used for the project, this directory should contain the source code, along with test programs in compilable and final versions.
\DOC -
\SPR - the directory contains all necessary documentation files for the project, i.e., report sources (.doc or html), JPG, PDF, etc., including the source materials used for algorithm development.
\PDF - The directory should contain the entire documentation for all active digital circuits.

##### Sprzęt:
Arduino UNO R3
Płytka stykowa 30
Kabel USB B
Klawiatura membranowa samoprzylepna 4x4 - 16 klawiszy
Czujnik temperatury (żółty data) # DS18B20
Diody x 2
Rezystory (dać między masą a danymi) 2x 330 Om , 1x 4,6kOm
Pin Expander - Pcf8574 - magistrala I2C
84 48 Nokia 5110 3310 wyświetlacz (pcd8544)

##### Elementy do Fusion360 a biblioteki:
Bazowa               - Arduino uno
Bazowa               - 2 diody
Bazowa               - 3 rezystory
Bazowa               - czujnik temperatury DS18B20
Micro-Philips      - pin expander pcf8574
LPH 7366            - 84 48 Nokia 5110 3310 wyświetlacz (pcd8544)
keypad_4x4_raw - Klawiatura membranowa samoprzylepna 4x4 

##### Teoria:
https://www.elektroda.pl/rtvforum/topic3668747.html
https://forbot.pl/blog/kurs-elektroniki-prawa-ohma-i-kirchhoffa-id3986

##### Podłączenia:
Pcf8574 http://akademia.nettigo.pl/starter_kit_030/
Klawiatury https://forbot.pl/blog/kurs-arduino-ii-klawiatura-wlasny-system-alarmowy-id18341
Czujnik temperatury ![[sonda-czujnik-temperatury-dallas-ds18b20-5metrow-1wire.jpg]]

##### Informacje do schematu:
Project scanner i2c - sprawdzanie portów ADRES 0x20
vss-supply ground
vdd-supply voltage
(5-1,7) / 0,01 = 330 Om tj. zasilanie układu - V diody / zakres działania diody 0,005 do 0,02 = wartość rezystora

##### Skrócony opis działania:
Diody symbolizują dmuchawe i pompę
Uruchamianie jest automatyczne, nie ma przycisku start
Dmuchawa rozgrzewa piec do temperatury zadanej, po przekroczeniu temp zadanej uruchamiana jest pompka która rozprowadza ciepło na grzejniki, wtedy też uruchomiony zmienia się z 0->1. Wtedy też dmuchawa się wyłącza (idzie w LOW)

Przykład tzadana to 50, t pompa 40, dmuchawa grzeje do 50 i sie wylacza
gdy nagrzeje do 40 wlacza sie pompa i rozprowadza cieplo, (ustawia stan uruchomiony na 1)

A - EkranTemperatury
B - EkranStanu
C - EkranPompa
D - reset
"*"- system w trybie edycji
