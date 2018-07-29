/*
   This program tracks the amount of time that the input square wave 
   is high on pins d2, d3, d8, a0, and d4. 
*/

const byte LED = 13;
const byte digital2 = 2;
const byte digital3 = 3;
byte led_state = 0;
unsigned int microsecondsD2 = 0;
unsigned int microsecondsD3 = 0;
unsigned int microsecondsD8 = 0;
unsigned int microsecondsA0 = 0;
unsigned int microsecondsD4 = 0;
byte rising_edgeD2 = 0;
byte falling_edgeD2 = 0;
byte rising_edgeD3 = 0;
byte falling_edgeD3 = 0;
byte rising_edgeD8 = 0;
byte falling_edgeD8 = 0;
byte rising_edgeA0 = 0;
byte falling_edgeA0 = 0;
byte rising_edgeD4 = 0;
byte falling_edgeD4 = 0;


ISR(INT0_vect)
{
  // Pin D2 has changed states.
  if ((PIND & 0x04) == 0x04) // Testing if D2 is high
  {
    // Rising edge,
    rising_edgeD2 = TCNT0;
  }
  else
  {
    // Falling edge
    falling_edgeD2 = TCNT0;
    if (falling_edgeD2 > rising_edgeD2)
    {
      microsecondsD2 = (falling_edgeD2 - rising_edgeD2) / 2;
    }
    else
    {
      microsecondsD2 = ((255 - rising_edgeD2) + falling_edgeD2) / 2;
    }

  }
}


ISR(INT1_vect)
{
  // Pin D3 has changed states.
  if ((PIND & 0x08) == 0x08) // Testing if D3 is high
  {
    // Rising edge,
    rising_edgeD3 = TCNT0;
  }
  else
  {
    // Falling edge
    falling_edgeD3 = TCNT0;
    if (falling_edgeD3 > rising_edgeD3)
    {
      microsecondsD3 = (falling_edgeD3 - rising_edgeD3) / 2;
    }
    else
    {
      microsecondsD3 = ((255 - rising_edgeD3) + falling_edgeD3) / 2;
    }

  }
}


ISR(PCINT0_vect)
{
  // Pin D8 has changed states.
  if ((PINB & 0x01) == 0x01) // Testing if D8 is high
  {
    // Rising edge,
    rising_edgeD8 = TCNT0;
  }
  else
  {
    // Falling edge
    falling_edgeD8 = TCNT0;
    if (falling_edgeD8 > rising_edgeD8)
    {
      microsecondsD8 = (falling_edgeD8 - rising_edgeD8) / 2;
    }
    else
    {
      microsecondsD8 = ((255 - rising_edgeD8) + falling_edgeD8) / 2;
    }

  }
}


ISR(PCINT1_vect)
{
  // Pin A0 has changed states.
  if ((PINC & 0x01) == 0x01) // Testing if A0 is high
  {
    // Rising edge,
    rising_edgeA0 = TCNT0;
  }
  else
  {
    // Falling edge
    falling_edgeA0 = TCNT0;
    if (falling_edgeA0 > rising_edgeA0)
    {
      microsecondsA0 = (falling_edgeA0 - rising_edgeA0) / 2;
    }
    else
    {
      microsecondsA0 = ((255 - rising_edgeA0) + falling_edgeA0) / 2;
    }

  }
}


ISR(PCINT2_vect)
{
  // Pin D4 has changed states
  if ((PIND & 0x10) == 0x10) // Testing if D4 is high
  {
    // Rising edge,
    rising_edgeD4 = TCNT0;
  }
  else
  {
    // Falling edge
    falling_edgeD4 = TCNT0;
    if (falling_edgeD4 > rising_edgeD4)
    {
      microsecondsD4 = (falling_edgeD4 - rising_edgeD4) / 2;
    }
    else
    {
      microsecondsD4 = ((255 - rising_edgeD4) + falling_edgeD4) / 2;
    }

  }
}


void setup() {
  pinMode (LED, OUTPUT);  // so we can update the LED
  digitalWrite(LED, LOW);
  pinMode(digital2, INPUT);
  pinMode(digital3, INPUT);
  digitalWrite(digital2, HIGH); // internal pull-up resistor
  digitalWrite(digital3, HIGH); // internal pull-up resitor
  SREG |= B10000000; // enable the I-bit of status register.
  EICRA &= B11110000; // External interrupt control register.
  EICRA |= B00000101; // Setting bits so any logical change triggers interrupt.
  EIMSK |= B00000011; // Enable INT0 and INT1 ono Iterrupt mask register.
  PCICR |= B00000111; // Enable pin change interrupts 1, 2, and 3.
  PCMSK0 |= B00000001; // Enable D8 (PCINT0) for PCI0
  PCMSK1 |= B00000001; // Enable A0 for PCI1
  PCMSK2 |= B00010000; // Enable D4 for PCI2

  TCCR0A &= B00001100; // Timer 0 is in normal mode. TC0 Control Register A
  // Timer/Counter Control Register 0 B
  // The timer will increment every 4 microseconds.
  TCCR0B &= B11111000; // Clears CS02 bit. TC0 Control Register B
  TCCR0B |= B00000010; // Sets the precalar to 8
  // Serial.begin(115200); // For testing purposes only
}

void loop() {
  // Serial.println(microsecondsD2); // Time that the pulse is high on D2.
}

