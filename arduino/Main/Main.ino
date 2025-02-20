/*
  8266 expander board project.
*/

#define DATAOUT  1
#define DATAIN   3
#define CLOCKLINE 0
#define STROBE    2

uint8_t shift(uint8_t out);


void setup() {
  pinMode(DATAOUT, OUTPUT);  
  
  pinMode(CLOCKLINE, OUTPUT);  
  digitalWrite(CLOCKLINE, LOW);
  
  pinMode(STROBE, OUTPUT);  
  digitalWrite(STROBE, LOW);
}


uint16_t i; // static storage for last read

void loop() {
  
  /*
  for (i = 1; i != 0; i <<= 1) {
    shift(i);
    delay(500);                      // Wait for two seconds (to demonstrate the active low LED)
  }
  */
  
  i = shift(i);
}


/*
 * Serial data exchange, we get 181kHz.
 * 
 */
uint16_t shift(uint16_t out) {
  
  uint16_t mask = 0x8000;
  uint16_t ret  = 0x0000;

  digitalWrite(STROBE, LOW);  // sample inputs 
  digitalWrite(STROBE, HIGH);
  
  while (mask) {
    if (out & mask) digitalWrite(DATAOUT, HIGH);
    else digitalWrite(DATAOUT, LOW);

    if (digitalRead(DATAIN) == HIGH) ret |= mask;
    
    digitalWrite(CLOCKLINE, HIGH); 
    digitalWrite(CLOCKLINE, LOW);
    mask >>= 1;
  }
  
  digitalWrite(STROBE, LOW);  
  digitalWrite(STROBE, HIGH); // latch outputs
  
  return ret;
}
