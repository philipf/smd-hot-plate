// Date: 2023/02/26
// Purpose: Sketch to control the temperature of a hot plate to follow a given solder melting profile

// Define the value of the series resistor (in ohms)
#define SERIES_RESISTOR 100000

// Define the nominal resistance of the thermistor at room temperature (in ohms)
#define NOMINAL_RESISTANCE 100000

// Define the temperature at which the thermistor's nominal resistance is specified (in Celsius)
#define NOMINAL_TEMPERATURE 25

// Define the beta coefficient of the thermistor
#define BETA_COEFFICIENT 3950

// Define the analog pin to which the thermistor is connected
#define THERMISTOR_PIN A0

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(4, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(4, LOW);
  Serial.begin(57600);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(4, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);   

  // Print the temperature to the serial monitor
  float probe1 = readTemperature(THERMISTOR_PIN);
  Serial.println(probe1);

  digitalWrite(4, LOW);
  digitalWrite(LED_BUILTIN, LOW);    
  delay(250);                        
}

float readTemperature(int pin)
{
  int rawValue;
  float resistance;
  float steinhart;
 
  rawValue = analogRead(THERMISTOR_PIN);
  // Convert the raw value to resistance using the series resistor
  resistance = SERIES_RESISTOR / ((1023.0 / rawValue) - 1);

  // Calculate the temperature using the Steinhart-Hart equation
  steinhart = resistance / NOMINAL_RESISTANCE;        // (R/Ro)
  steinhart = log(steinhart);                         // ln(R/Ro)
  steinhart /= BETA_COEFFICIENT;                      // 1/B * ln(R/Ro)
  steinhart += 1.0 / (NOMINAL_TEMPERATURE + 273.15);  // + (1/To)
  steinhart = 1.0 / steinhart;                        // Invert
  steinhart -= 273.15;                                // Convert to Celsius

  return steinhart;
}
