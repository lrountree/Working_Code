
int RXLED = 17;
void setup() {
  pinMode(RXLED, OUTPUT);

  Serial.begin(9600); // Serial monitor
  Serial.println("Initialize the serial monitor");

  Serial1.begin(9600); // UART
  Serial1.println("Initialize UART Pins");
 
}

void loop() {
  Serial.println("Hello World, from smon");
  Serial1.println("Hello, from UART");

  digitalWrite(RXLED, LOW); // Turns on RX LED
  TXLED0; // Turn TX LED off via macro
  delay(1000); // Wait one second

  digitalWrite(RXLED, HIGH);
  TXLED1;
  delay(1000);

}
