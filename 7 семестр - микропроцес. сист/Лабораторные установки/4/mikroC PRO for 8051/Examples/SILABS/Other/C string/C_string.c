/*
 * Project name:
     C_string
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20071210:
       - initial release;
 * Description:
     This program demonstrates usage of standard C string library routines. 
     Compile and run the code through software simulator.
 * Test configuration:
     MCU:             C8051F040
                      http://www.silabs.com/Support%20Documents/TechnicalDocs/C8051F04x.pdf
     Dev.Board:       BIG8051
                      http://www.mikroe.com/big8051/
     Oscillator:      Internal oscillator 24.5000 MHz
     Ext. Modules:    -
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     None.
 */

char *res;
int result;

void main(){
  char txt[] = "mikroElektronika";
  char txt_sub[10] = "mikr";
  

  /* memchr */
  res =  memchr(txt, 'e', 16);
  res =  memchr(txt, 'e', 5);

  /* memcmp */
  result =  memcmp(txt, txt_sub, 16);      // 111
  result =  memcmp(txt, txt_sub, 4);       // 0

  /* memcpy */
  res = memcpy(txt+4, txt_sub, 4);
  res = memcpy(txt+10, txt_sub, 2);

  /* memmove */
  res = memmove(txt+5, txt_sub, 4);
  res = memmove(txt+11, txt_sub, 2);

  /* memset */
  memset(txt_sub+5,'a',2);

  /* strcat */
  txt_sub[3] = 0;
  strcat(txt_sub,"_test");

  /* strchr */
  res =  strchr(txt_sub, 't');

  /* strcmp */
  result = strcmp(txt,txt_sub);            // 19

  /* strcpy */
  res = strcpy(txt, txt_sub);

  /* strlen - Returns length of given (null-terminated) string */
  result = strlen(txt);                    // 8

  /* strncat */
  txt[3] = 0;
  txt_sub[4] = 0;
  res = strncat(txt,txt_sub,8);
  txt[3] = 0;
  res = strncat(txt,txt_sub,2);

  /* strncpy */
  txt_sub[4] = 0;
  res = strncpy(txt,txt_sub,8);

  /* strspn */
  result = strspn(txt,txt_sub);            // 4

  /* strcspn */
  result = strcspn(txt_sub,txt);           // 0
  result = strcspn(txt_sub,"dxc");         // 4
  result = strcspn(txt_sub,"dxk");         // 2

  /* strncmp */
  txt[4] = 'r';
  result =  strncmp(txt_sub,txt,3);        // 0
  result =  strncmp(txt_sub,txt,6);        // -114

  /* strpbrk */
  res =  strpbrk(txt_sub,txt);

  /* strrchr */
  txt_sub[3] = 'k';
  res =  strrchr(txt_sub,'p');             // 0
  res =  strrchr(txt_sub,'k');

  /* strstr */
  txt_sub[3] = 0;
  res =  strstr(txt,txt_sub);
  txt[2] = 'P';
  res =  strstr(txt_sub,txt);              // 0
}