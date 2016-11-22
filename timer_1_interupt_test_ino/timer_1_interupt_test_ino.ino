#include <avr/io.h> // includes external libraries
#include <avr/interrupt.h>
volatile unsigned int asdf = 0; // makes asdf volatile and equals zero
volatile unsigned int count = 0; // makes count volatile and equals zero
void setup()
{
  Serial.begin(57600); 
  pinMode(9, INPUT);  // pin 9 becomes an input
  pinMode(8, OUTPUT); // pin 8 becomes an output
  cli();
  TCCR1A = 0; // clears register
  TCCR1B = 0; // clears register
  TCCR1B = (1 << CS12)| (0 << CS11)| (1 << CS10);//pre scaler
  TIMSK1 = (1 << OCIE1A); // enables the interrupt on match to register
  OCR1A = 625; // up to a very high number // compare register

  PCICR = (1 << PCIE0); // pin change interrupt control register
  PCMSK0 = (1 << PCINT1);
  sei(); // enables global interrupt
}
void loop()
{
  // do some crazy stuff while my LED keeps blinking
}
ISR(TIMER1_COMPA_vect)// interrupt routine on compare 
{
  // count = count + 1;
  count = (960)/count; //divisions * time / count
  count = 100000/count;
  Serial.println(count);
 // Serial.println(asdf);
  count = 0;
  //asdf = (16/count)/24;
  digitalWrite(8, !digitalRead(8)); // toggles between high and low
  TCNT1 = 0; // reset timer to zero
}
ISR(PCINT0_vect)
{
 // digitalWrite(8, !digitalRead(8));
  count = count + 1;
 // asdf = (40/24) * count;
}


