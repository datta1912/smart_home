#include <DHT.h>
#include <LiquidCrystal_I2C.h>


#define DHTPIN 2	// DHT11 sensor pin #define DHTTYPE DHT11	// DHT11 sensor type DHT dht(DHTPIN, DHTTYPE);

#define MQ2PIN A0	// MQ-2 gas sensor pin

#define FLAMEPIN 3		// Flame sensor pin pin #define LEDPIN 4	// LED pin
#define BUZZERPIN 13	// Buzzer pin


LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address of the LCD module and the number of columns and rows


void setup() {
Serial.begin(9600);	// start serial communication dht.begin();	// start DHT11 sensor
pinMode(MQ2PIN, INPUT);// initialize MQ-2 gas sensor pin as input pinMode(FLAMEPIN, INPUT);// initialize flame sensor pin as input pinMode(LEDPIN, OUTPUT);// initialize LED pin as output pinMode(BUZZERPIN, OUTPUT);// initialize Buzzer pin as output

lcd.init();	// initialize LCD lcd.backlight();		// turn on the backlight
}


void loop() {
float temperature = dht.readTemperature(); // read temperature float humidity = dht.readHumidity(); // read humidity
int gas = analogRead(MQ2PIN); // read MQ-2 gas sensor value bool flame = digitalRead(FLAMEPIN); // read flame sensor value

Serial.print("Temperature: "); Serial.print(temperature); Serial.print(" °C, Humidity: ");

Serial.print(humidity); Serial.print("%,Gas: "); Serial.print(gas); Serial.print(", Flame: "); Serial.println(flame);

lcd.setCursor(0,0);	// set cursor to the first column of the first row lcd.print("Temp: ");		// print "Temp: "
lcd.print(temperature); // print the temperature lcd.print(" C");	// print " C"

lcd.setCursor(0,1);		// set cursor to the first column of the second row lcd.print("Gas:");	// print "Gas: "
lcd.print(gas);	// print the gas level lcd.print(" Flame:"); // print " Flame: " lcd.print(flame);		// print the flame detection

if (temperature > 45) { // check if temperature is too high digitalWrite(LEDPIN, HIGH); // turn on the LED
tone(BUZZERPIN, 1000, 1000); // make a sound with the buzzer for 1 second
}
else if (gas > 200 || flame == LOW) { // check if gas or flame is detected digitalWrite(LEDPIN, HIGH); // turn on the LED
tone(BUZZERPIN, 2000, 1000); // make a different sound with the buzzer for 1 second
}
else {

digitalWrite(LEDPIN, LOW); // turn off the LED noTone(BUZZERPIN); // stop the buzzer sound
}


delay(100); // wait for 2 seconds
}