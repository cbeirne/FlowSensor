//Combination of codes from Adafruit, Sparkfun, Dr. Greg Gerbi, and personal customization

//clock 30 sec off

//built in libraries
#include <SD.h>   //SD card module
#include <SPI.h>
#include <RTClib.h> //Clock

//output data file name
char fname[] = "mmddhhnn.csv";

//input pins
const int CS = 10; //Set SS/CS pin for mega
#define FLOWSENSORPIN 2

//Global Variables                          
float T36C = 0;  
int PhotoResV = analogRead(A2); //photoresistor
const float circuitVoltage = 5.0;
int ThermV = analogRead(A0); //Thermsitor
float resistor1 = 10000.0;
volatile uint16_t pulses = 0;
volatile uint8_t lastflowpinstate;
volatile uint32_t lastflowratetimer = 0;
volatile float flowrate;
float lf = lastflowratetimer;

//declarations
File myFile;
RTC_PCF8523 rtc;

//Flow Sensor Timer 
void useInterrupt(boolean v) {  
  if (v) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK0 &= ~_BV(OCIE0A);
  }
}

SIGNAL(TIMER0_COMPA_vect) {
  uint8_t x = digitalRead(FLOWSENSORPIN);
  
  

  if (x == lastflowpinstate) {
    lastflowratetimer++;
    return; // nothing changed!
  }
  
  if (x == HIGH) {
    //low to high transition!
    pulses++;
  }
  lastflowpinstate = x;
  flowrate = 1000.0;
  flowrate /= lastflowratetimer;  // rotations per second
  lastflowratetimer = 0;
}

void setup() {
  Serial.begin(9600);
  pinMode(CS, OUTPUT);
    if (!SD.begin(CS)){
      Serial.println("Initialization failed");    //SD module initialization
    }
  if (! rtc.begin()) {
      Serial.println("Couldn't find RTC");    //Clock module initialization
      Serial.flush();
      while (1) delay (10);
    }
   
   pinMode(FLOWSENSORPIN, INPUT);
   digitalWrite(FLOWSENSORPIN, HIGH);
   lastflowpinstate = digitalRead(FLOWSENSORPIN);
   useInterrupt(true);


  makefname();
  Serial.print("fname: ");    //Write to SD card module initialization
  Serial.println(fname);
  myFile = SD.open(fname, FILE_WRITE);
  //Column titles
  Serial.println("year,month,day,hour,minute,second,Flow,Temperature,Light,LVoltage");
  myFile.println("year,month,day,hour,minute,second,Flow,Temperature,Light,LVoltage");
}

void loop() {
 
  float photo = PhotoResistance(resistor1); //Resistance
  //float Flow = flowrate
  float PVoltage = VP();
  float Flow = FlowCali(flowrate);    //Calibrated flowrate (l/s)
  DateTime now = rtc.now();
  delay(500);
  float Resistance = ThermResistance(resistor1); //Obtain resistance from resistor 
  float T36 = GetTemp (Resistance);  //Celsius 
  float T36C = TempCali(T36);
  
  SerialPrint(now, T36C, Flow, photo, PVoltage);
  FilePrint(now, T36C, Flow, photo, PVoltage);
  
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
 
  delay(1000);                              //measurement every 1 second
}
