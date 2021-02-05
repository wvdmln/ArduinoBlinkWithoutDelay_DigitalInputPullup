/*
  Blink without Delay + "Schakelaar" die "Lampje" stuurt

  LED_BUILTIN gaat aan voor 5s, daarna uit voor 5 s, herhalend.
  Schakelaar bedient INPUT 2 (wordt hier gebruikt met de ingebouwde pullup-weerstand)
  Wanneer de schakelaar (INPUT 2) bediend wordt, willen we dat het lampje brandt (OUTPUT 12)

  In tegenstelling tot de sketch die gebruik maakt van de delay-functie reageert "Lampje" nu wel ogenblikkelijk op het signaal van de schakelaar.
  
  
*/
#define LED_BUILTIN 13
#define Lampje 12
#define Schakelaar 2

// Variabele die kan wijzigen:
int ledState = LOW;             

// Gebruik "unsigned long" voor de variable die de waarde van Millis moet bijhouden (aantal ms dat verstreken is sinds de opstart)
// Een integer variabele zou heel snel een overflow genereren (groot getal)

unsigned long previousMillis = 0;        // laatste keer dat de LED was geupdated

// constants kunnen niet wijzigen:
const long interval = 5000;           // knipperinterval (milliseconden)


// de setup-functie runt 1 keer na reset of power-on
void setup() {
  //start de seriële connectie (monitorfunctie)
  Serial.begin(9600);
  // set inputs/outputs
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(Lampje, OUTPUT);
  pinMode(Schakelaar, INPUT_PULLUP);
}

// de loop-function runt telkens opnieuw
void loop() {
  
    // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(LED_BUILTIN, ledState);
  }
  //lees de status van de schakelaar in een variabele
  int sensorVal = digitalRead(2);
  //print de waarde in de seriële monitor (0 of 1)
  Serial.println(sensorVal);

    if (sensorVal == HIGH) {
    digitalWrite(Lampje, LOW); // Pullup-ingang werkt omgekeerd >> HIGH > LOW
  } else {
    digitalWrite(Lampje, HIGH);
  }
}
