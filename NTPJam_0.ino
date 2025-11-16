/*
 * Contoh penggunaan library DMDESP
 * dengan NTP untuk Jam
 * email : bonny@grobak.net - www.grobak.net - www.elektronmart.com
 * 
 * v0 - small changes by Nicu FLORICA (niq_ro) -> 2x2 to one display
*/

#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include <DMDESP.h>   //  https://github.com/busel7/DMDESP/
#include <fonts/EMKotak5x7.h>
#include <fonts/EMSans8x16.h>
#include <fonts/Font_6x14niqro.h> // Original font file only contains numbers from 0-9. Used only to display time, font downloaded from https://www.youtube.com/watch?v=-WQuz01Ml80
                                  // File changed by niq_ro to be space instead ; and C instead : 

#define FontDefault EMKotak5x7
//#define FontBig EMSans8x16
#define FontBig Font_6x14

/*
#define pin_A 16   // D0
#define pin_B 12   // D6
#define pin_clk 14 // D5
#define pin_sclk 0 // D3
#define pin_r 13   // D7
#define pin_noe 15 // D8
*/

// DMDESP Setup
#define DISPLAYS_WIDE 1 // Kolom Panel
#define DISPLAYS_HIGH 1 // Baris Panel
DMDESP dmd(DISPLAYS_WIDE, DISPLAYS_HIGH);  // Jumlah Panel P10 yang digunakan (KOLOM,BARIS)

// WIFI Setup
#define ssid      "bbk2"          // Ubah sesuaikan
#define password  "internet2"     // Ubah sesuaikan

// NTP Client Setup
const long utcOffset = 3600 * 2; // Waktu WIB
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffset);

// Variabel
byte Hour;
byte Minut;
byte Det;

int x = 0;
int y = 0;
int tip = 1;

//----------------------------------------------------------------------
// SETUP

void setup() {

  // WIFI
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    //Serial.print ( "." );
  }

  // NTP
  timeClient.begin();  

  // DMDESP
  dmd.start(); // Jalankan library DMDESP
  dmd.setBrightness(2); // set the brighness (min.1..max.255)
  dmd.setFont(FontDefault); // Set font 
}


//----------------------------------------------------------------------
// LOOP

void loop() {

  timeClient.update();
  
  Hour = timeClient.getHours();
  Minut = timeClient.getMinutes();
  Det = timeClient.getSeconds();

 dmd.setFont(FontBig);
if (Hour/10 == 0) dmd.drawChar(x,y, ';'); // just for Font_6x14niqro.h ; is space and : is C
else
{
dmd.drawChar(x,y, ';');
dmd.drawChar(x,y, 48+Hour/10);
}

dmd.drawChar(x+7,y, ";');
dmd.drawChar(x+7,y, 48+Hour%10);

if (millis()/1000%2 == 1)
{
dmd.drawLine(x+15,y+2,x+15,y+3);
dmd.drawLine(x+15,y+7,x+15,y+8);
dmd.drawLine(x+15+tip%2,y+2,x+15+tip%2,y+3);
dmd.drawLine(x+15+tip%2,y+7,x+15+tip%2,y+8);
}

else
{
dmd.setFont(FontDefault);
dmd.drawText(13,2,";"); 
}

 dmd.setFont(FontBig);
dmd.drawChar(x+19,y, ';');  
dmd.drawChar(x+19,y, 48+Minut/10);

dmd.drawChar(x+26,y, ';'); 
dmd.drawChar(x+26,y, 48+Minut%10);
 
  dmd.loop();
}   // end main loop

