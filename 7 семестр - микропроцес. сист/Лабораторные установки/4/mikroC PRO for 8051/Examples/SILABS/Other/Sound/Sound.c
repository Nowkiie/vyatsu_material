/*
 * Project name:
     Sound (Demonstration of using Sound Library)
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20071210:
       - initial release;
 * Description:
     This project is a simple demonstration of how to use Sound Library 
     for playing tones on a piezo speaker.
 * Test configuration:
     MCU:             C8051F040
                      http://www.silabs.com/Support%20Documents/TechnicalDocs/C8051F04x.pdf
     Dev.Board:       BIG8051
                      http://www.mikroe.com/big8051/
     Oscillator:      Internal oscillator 24.5000 MHz
     Ext. Modules:    Piezo speaker on P0.3 pin
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     None.
*/

// Sound connections
sbit Sound_Play_Pin at P2_7_bit;
// End Sound connections


void Tone1() {
  Sound_Play(659, 250);   // Frequency = 659Hz, duration = 250ms
}

void Tone2() {
  Sound_Play(698, 250);   // Frequency = 698Hz, duration = 250ms
}

void Tone3() {
  Sound_Play(784, 250);   // Frequency = 784Hz, duration = 250ms
}

void Melody() {           // Plays the melody "Yellow house"
  Tone1(); Tone2(); Tone3(); Tone3();
  Tone1(); Tone2(); Tone3(); Tone3();
  Tone1(); Tone2(); Tone3();
  Tone1(); Tone2(); Tone3(); Tone3();
  Tone1(); Tone2(); Tone3();
  Tone3(); Tone3(); Tone2(); Tone2(); Tone1();
}

void ToneA() {
  Sound_Play( 880, 50);
}
void ToneC() {
  Sound_Play(1046, 50);
}
void ToneE() {
  Sound_Play(1318, 50);
}

void Melody2() {
  unsigned short i;
  for (i = 9; i > 0; i--) {
    ToneA(); ToneC(); ToneE();
  }
}

void main() {
  WDTCN    = 0xDE;                // Sequence for
  WDTCN    = 0xAD;                //   disabling the watchdog timer
  OSCICN   = 0x83;                // Enable internal oscillator (24.5MHz divided by 1)
  RSTSRC = 0x04;                      // Enable missing clock detector


 // Consult datasheet for more details about starting External oscillator
 // Step 1. Enable the external oscillator.
  OSCXCN = 0x60;                     // External Oscillator is an external
                                      // crystal (no divide by 2 stage)
  OSCXCN |= 7;

  // Step 2. Wait at least 1 ms.
  Delay_ms(5);

  // Step 3. Poll for XTLVLD => ‘1’.
  while ((OSCXCN & 0x80) != 0x80);


  // Step 4. Switch the system clock to the external oscillator.
  CLKSEL = 0x01;//

  XBR2      = 0x40;
  P2MDOUT  = 0xFF;    // Configure PORT0 pins as push-pull outputs

  Sound_Init();            // Initialize sound pin
  
  Sound_Play(2000, 1000);  // Play starting sound, 2kHz, 1 second
  Delay_ms(1000);

  Tone1();                 //  play Tone1
  Delay_ms(1000);

  Tone2();                 //  play Tone2
  Delay_ms(1000);

  Tone3();                 //  play Tone3
  Delay_ms(1000);

  Melody2();               //  play Melody2
  Delay_ms(1000);

  Melody();                //  play Melody
  Delay_ms(1000);
}