/*
 * Project Name:
     SPI_Ethernet;
 * Copyright:
     (c) Mikroelektronika, 2013.
 * Revision History:
     20101129:
       - initial release (SZ)
 * description  :
 *      this code shows how to use the Spi_Ethernet mini library :
 *              the board will reply to ARP & ICMP echo requests
 *              the board will reply to UDP requests on any port :
 *                      returns the request in upper char with a header made of remote host IP & port number
 *              the board will reply to HTTP requests on port 80, GET method with pathnames :
 *                      /               will return the HTML main page
 *                      /s              will return board status as text string
 *                      /t0 ... /t7     will toggle P1.b0 to P1.b7 bit and return HTML main page
 *                      all other requests return also HTML main page
 *
 * target devices :
 *      any 8051 with integrated SPI and more than 8 Kb ROM memory
 *
 *      the INT and WOL signals from the ENC are not used
 *
 * Test configuration:
     MCU:             C8051F040
                      http://www.silabs.com/Support%20Documents/TechnicalDocs/C8051F04x.pdf
     Dev.Board:       BIG8051  ac:Ethernet
                      http://www.mikroe.com/big8051/
     Oscillator:      External oscillator 25MHz
     Ext. Modules:    -
     SW:              mikroC PRO for 8051
                      http://www.mikroe.com/mikroc/8051/
 * NOTES:
     - External power supply should be used due to Serial Ethernet Board power consumption.
     - SW10(1,3,5-ON)
     - SW13(5,7-ON)
 */

// duplex config flags
#define Spi_Ethernet_HALFDUPLEX     0x00                                        // half duplex
#define Spi_Ethernet_FULLDUPLEX     0x01                                        // full duplex

// mE ehternet NIC pinout
sfr sbit SPI_Ethernet_RST at P2_6_bit;
sfr sbit SPI_Ethernet_CS  at P2_4_bit;
// end ethernet NIC definitions

/************************************************************
 * ROM constant strings
 */
const code unsigned char httpHeader[] = "HTTP/1.1 200 OK\nContent-type: " ;     // HTTP header
const code unsigned char httpMimeTypeHTML[] = "text/html\n\n" ;                 // HTML MIME type
const code unsigned char httpMimeTypeScript[] = "text/plain\n\n" ;              // TEXT MIME type
idata unsigned char httpMethod[] = "GET /";
/*
 * web page, splited into 2 parts :
 * when coming short of ROM, fragmented data is handled more efficiently by linker
 *
 * this HTML page calls the boards to get its status, and builds itself with javascript
 */
const code char    *indexPage =                   // Change the IP address of the page to be refreshed
"<meta http-equiv=\"refresh\" content=\"3;url=http://192.168.20.60\">\
<HTML><HEAD></HEAD><BODY>\
<h1>8051 + ENC28J60 Mini Web Server</h1>\
<a href=/>Reload</a>\
<script src=/s></script>\
<table><tr>" ;


const   char    *indexPage2 =  "<td>\
<table border=1 style=\"font-size:20px ;font-family: terminal ;\">\
<tr><th colspan=3>P1</th></tr>\
<script>\
var str,i;\
str=\"\";\
for(i=0;i<8;i++)\
{str+=\"<tr><td bgcolor=yellow>LED #\"+i+\"</td>\";\
if(P1&(1<<i)){str+=\"<td bgcolor=red>ON\";}\
else {str+=\"<td bgcolor=#cccccc>OFF\";}\
str+=\"</td><td><a href=/t\"+i+\">Toggle</a></td></tr>\";}\
document.write(str) ;\
</script>\
</table></td></tr></table>\
This is HTTP request #<script>document.write(REQ)</script></BODY></HTML>\
" ;

/***********************************
 * RAM variables
 */
idata unsigned char   myMacAddr[6] = {0x00, 0x14, 0xA5, 0x76, 0x19, 0x3f} ;     // my MAC address
idata unsigned char   myIpAddr[4]  = {192, 168, 20, 60} ;                       // my IP address
idata unsigned char   getRequest[15] ;                                          // HTTP request buffer
idata unsigned char   dyna[29] ;                                                // buffer for dynamic response
idata unsigned long   httpCounter = 0 ;                                         // counter of HTTP requests

/*******************************************
 * functions
 */

/*
 * put the constant string pointed to by s to the ENC transmit buffer.
 */
/*unsigned int    putConstString(const code char *s)
        {
        unsigned int ctr = 0 ;

        while(*s)
                {
                Spi_Ethernet_putByte(*s++) ;
                ctr++ ;
                }
        return(ctr) ;
        }*/
/*
 * it will be much faster to use library Spi_Ethernet_putConstString routine
 * instead of putConstString routine above. However, the code will be a little
 * bit bigger. User should choose between size and speed and pick the implementation that
 * suites him best. If you choose to go with the putConstString definition above
 * the #define line below should be commented out.
 *
 */
#define putConstString  SPI_Ethernet_putConstString

/*
 * put the string pointed to by s to the ENC transmit buffer
 */
/*unsigned int    putString(char *s)
        {
        unsigned int ctr = 0 ;

        while(*s)
                {
                Spi_Ethernet_putByte(*s++) ;

                ctr++ ;
                }
        return(ctr) ;
        }*/
/*
 * it will be much faster to use library Spi_Ethernet_putString routine
 * instead of putString routine above. However, the code will be a little
 * bit bigger. User should choose between size and speed and pick the implementation that
 * suites him best. If you choose to go with the putString definition above
 * the #define line below should be commented out.
 *
 */
#define putString  SPI_Ethernet_putString

/*
 * this function is called by the library
 * the user accesses to the HTTP request by successive calls to Spi_Ethernet_getByte()
 * the user puts data in the transmit buffer by successive calls to Spi_Ethernet_putByte()
 * the function must return the length in bytes of the HTTP reply, or 0 if nothing to transmit
 *
 * if you don't need to reply to HTTP requests,
 * just define this function with a return(0) as single statement
 *
 */
unsigned int SPI_Ethernet_UserTCP(unsigned char *remoteHost, unsigned int remotePort, unsigned int localPort, unsigned int reqLength, char *canClose)
        {
        idata unsigned int    len;                                              // my reply length

        if(localPort != 80)                                                     // I listen only to web request on port 80
                {
                return(0) ;
                }

        // get 10 first bytes only of the request, the rest does not matter here
        for(len = 0 ; len < 10 ; len++)
                {
                getRequest[len] = SPI_Ethernet_getByte() ;
                }
        getRequest[len] = 0 ;

        len = 0;

        if(memcmp(getRequest, httpMethod, 5))                                   // only GET method is supported here
                {
                return(0) ;
                }

        httpCounter++ ;                                                         // one more request done

        if(getRequest[5] == 's')                                                // if request path name starts with s, store dynamic data in transmit buffer
                {
                // the text string replied by this request can be interpreted as javascript statements
                // by browsers

                len = putConstString(httpHeader) ;                              // HTTP header
                len += putConstString(httpMimeTypeScript) ;                     // with text MIME type

                // add P1 value (buttons) to reply
                len += putConstString("var P1=") ;
                WordToStr(P1, dyna) ;
                len += putString(dyna) ;
                len += putConstString(";") ;

                // add P3 value (LEDs) to reply
                len += putConstString("var P3=") ;
                WordToStr(P3, dyna) ;
                len += putString(dyna) ;
                len += putConstString(";") ;

                // add HTTP requests counter to reply
                WordToStr(httpCounter, dyna) ;
                len += putConstString("var REQ=") ;
                len += putString(dyna) ;
                len += putConstString(";") ;
                }
        else if(getRequest[5] == 't')                                           // if request path name starts with t, toggle P1 (LED) bit number that comes after
                {
                unsigned char   bitMask = 0 ;                                   // for bit mask

                if(isdigit(getRequest[6]))                                      // if 0 <= bit number <= 9, bits 8 & 9 does not exist but does not matter
                        {
                        bitMask = getRequest[6] - '0' ;                         // convert ASCII to integer
                        bitMask = 1 << bitMask ;                                // create bit mask
                        P1 ^= bitMask ;                                         // toggle P1 with xor operator
                        }
                }

        if(len == 0)                                                            // what do to by default
                {
                len =  putConstString(httpHeader) ;                             // HTTP header
                len += putConstString(httpMimeTypeHTML) ;                       // with HTML MIME type
                len += putConstString(indexPage) ;                              // HTML page first part
                len += putConstString(indexPage2) ;                             // HTML page second part
                }

        return(len) ;                                                           // return to the library with the number of bytes to transmit
        }

/*
 * this function is called by the library
 * the user accesses to the UDP request by successive calls to Spi_Ethernet_getByte()
 * the user puts data in the transmit buffer by successive calls to Spi_Ethernet_putByte()
 * the function must return the length in bytes of the UDP reply, or 0 if nothing to transmit
 *
 * if you don't need to reply to UDP requests,
 * just define this function with a return(0) as single statement
 *
 */
unsigned int SPI_Ethernet_UserUDP(unsigned char *remoteHost, unsigned int remotePort, unsigned int destPort, unsigned int reqLength)
        {
        idata unsigned int    len ;                                             // my reply length

        // reply is made of the remote host IP address in human readable format
        ByteToStr(remoteHost[0], dyna) ;                                        // first IP address byte
        dyna[3] = '.' ;
        ByteToStr(remoteHost[1], dyna + 4) ;                                    // second
        dyna[7] = '.' ;
        ByteToStr(remoteHost[2], dyna + 8) ;                                    // third
        dyna[11] = '.' ;
        ByteToStr(remoteHost[3], dyna + 12) ;                                   // fourth

        dyna[15] = ':' ;                                                        // add separator

        // then remote host port number
        WordToStr(remotePort, dyna + 16) ;
        dyna[21] = '[' ;
        WordToStr(destPort, dyna + 22) ;
        dyna[27] = ']' ;
        dyna[28] = 0 ;

        // the total length of the request is the length of the dynamic string plus the text of the request
        len = 28 + reqLength;

        // puts the dynamic string into the transmit buffer
        SPI_Ethernet_putBytes(dyna, 28) ;

        // then puts the request string converted into upper char into the transmit buffer
        while(reqLength--)
                {
                SPI_Ethernet_putByte(toupper(SPI_Ethernet_getByte())) ;
                }

        return(len) ;           // back to the library with the length of the UDP reply
        }

unsigned int i;

/*
 * main entry
 */
void  main() {

  WDTCN    = 0xDE;                                                              // Sequence for
  WDTCN    = 0xAD;                                                              // disabling the watchdog timer



  OSCICN = 0x83;                                                                // Configure internal oscillator for
                                                                                // its highest frequency (24.5 MHz)
  RSTSRC = 0x04;                                                                // Enable missing clock detector


// Consult datasheet for more details about starting External oscillator
 // Step 1. Enable the external oscillator.
   OSCXCN = 0x60;                                                               // External Oscillator is an external
                                                                                // crystal (no divide by 2 stage)
   OSCXCN |= 7;


   // Step 2. Wait at least 1 ms.
   Delay_ms(5);

   // Step 3. Poll for XTLVLD => ‘1’.
   while ((OSCXCN & 0x80) != 0x80);


   // Step 4. Switch the system clock to the external oscillator.
   CLKSEL = 0x01;
//

   XBR0 = 0x02;
   XBR1 = 0x00;                                                                 // Don't Route /SYSCLK to a port pin
   XBR2 = 0x40;                                                                 // Enable crossbar and weak pull-ups




        P0MDOUT |= 0b00000101;                                                  // P0.2(MOSI) and P0.0(SCK) pin as push-pull outputs
        P1MDOUT  = 0xFF;                                                        // Configure PORT1 pins as push-pull outputs
        P2MDOUT |= 0b01010000;                                                  // Configure P2.4(CS), P2.6(RST) pins as push-pull outputs

        SPI1_Init(100000);                                                      // Init SPI module
        /*
         * starts ENC28J60 with :
         * reset bit on P0_4
         * CS bit on P0_5
         * my MAC & IP address
         * full duplex
         */
        SPI_Ethernet_Init(myMacAddr, myIpAddr, Spi_Ethernet_FULLDUPLEX) ;       // Full duplex, CRC + MAC Unicast + MAC Broadcast filtering

        while(1)                                                                // Do forever
                {
                /*
                 * if necessary, test the return value to get error code
                 */
                SPI_Ethernet_doPacket() ;                                       // Process incoming Ethernet packets

                /*
                 * add your stuff here if needed
                 * Spi_Ethernet_doPacket() must be called as often as possible
                 * otherwise packets could be lost
                 */
                }
        }