/*
 * Project name:
     Sound (Demonstration of using Sound Library)
 * Copyright:
     (c) Mikroelektronika, 2009.
 * Revision History:
     20071210:
       - initial release;
 * Description:
     This project is a simple demonstration of how to use Sound Library 
     for playing tones on a piezo speaker. Pressing buttons P1.7 .. P1.3
     generates commands for playing sounds and melodies.      
 * Test configuration:
     MCU:             AT89S8253
                      http://www.atmel.com/dyn/resources/prod_documents/doc3286.pdf
     Dev.Board:       Easy8051v6
                      http://www.mikroe.com/easy8051/
     Oscillator:      External Clock 10.0000 MHz
     Ext. Modules:    Piezo speaker on P0.3 pin
                      http://www.mikroe.com/add-on-boards/audio-voice/easybuzz/
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - Put button jumper into GND (J6) position and pull-up PORT1 (SW2).
*/

// Sound connections
sbit Sound_Play_Pin at P0_3_bit;
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
  P1 = 255;                     // Configure PORT1 as input
  Sound_Init();                 // Initialize sound pin
  
  Sound_Play(2000, 1000);       // Play starting sound, 2kHz, 1 second

  while (1) {                   // endless loop
  
    if (!(P1_7_bit))            // If P1.7 is pressed play Tone1
      Tone1();                  // 
    while (!(P1_7_bit)) ;       // Wait for button to be released

    if (!(P1_6_bit))            // If P1.6 is pressed play Tone2
      Tone2();                  //
    while (!(P1_6_bit)) ;       // Wait for button to be released

    if (!(P1_5_bit))            // If P1.5 is pressed play Tone3
      Tone3();                  //
    while (!(P1_5_bit)) ;       // Wait for button to be released

    if (!(P1_4_bit))            // If P1.4 is pressed play Melody2
      Melody2();                //
    while (!(P1_4_bit)) ;       // Wait for button to be released

    if (!(P1_3_bit))            // If P1.3 is pressed play Melody
      Melody();                 //
    while (!(P1_3_bit)) ;       // Wait for button to be released
  }
}