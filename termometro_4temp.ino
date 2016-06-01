#define UNO       //anti crash wachdog reset only works with Uno (optiboot) bootloader, comment out the line if using delianuova

#include <LiquidCrystal.h>
/* Corrispondenza pin LCD <-> pin digitali di Arduino */
#define RS  12
#define EN  11
#define D7  5 
#define D6  4
#define D5  3
#define D4  2
/* Numero del pin analogico sul quale è collegato l'LM35  */
#define LM35_pin0 0
#define LM35_pin1 1
#define LM35_pin2 2
#define LM35_pin3 3
/* Definizioni globali */
float vref = 1.1;                        // Vref dell'ADC (quell'interno è di 1,1V)
int tempSoglia = 20;
LiquidCrystal lcd( RS, EN, D7, D6, D5, D4 ); // 'lcd' è una variabile di tipo LiquidCrystal */
/* Impostazione dell'hardware */
void setup()
{
  analogReference( INTERNAL );  // per l'ADC usiamo il Vref interno da 1,1V (migliore precisione)
  analogRead( LM35_pin0 );       // Prima lettura "a vuoto" (serve per l'assestamento dell'ADC)
  analogRead( LM35_pin1 );       // Prima lettura "a vuoto" (serve per l'assestamento dell'ADC)
  analogRead( LM35_pin2 );       // Prima lettura "a vuoto" (serve per l'assestamento dell'ADC)
  analogRead( LM35_pin3 );       // Prima lettura "a vuoto" (serve per l'assestamento dell'ADC)
  lcd.begin( 4, 20 );           // Impostazione per l' LCD (2x16)
}
void loop()
{
  
  #ifdef UNO
  wdt_reset();
  #endif

  float temp0 = readTemp(LM35_pin0);  // legge il valore della temperatura e la memorizza nella var. temp.
  delay(100);
  float temp1 = readTemp(LM35_pin1);  // legge il valore della temperatura e la memorizza nella var. temp.
  delay(100);
  float temp2 = readTemp(LM35_pin2);  // legge il valore della temperatura e la memorizza nella var. temp.
  delay(100);
  float temp3 = readTemp(LM35_pin3);  // legge il valore della temperatura e la memorizza nella var. temp.
 
  char _buffer[10]; ;
 
  lcd.clear();               // Pulisce lo schermo
  lcd.setCursor( 0, 0 );     // Va in posizione di home: colonna 1, riga 1
  lcd.print( "SALA:      ");
  dtostrf(temp0, 2, 1, _buffer);
  lcd.print( _buffer );         // Stampa solo la parte intera della temp.
  lcd.print( ' ' );          // Stampa uno spazio
  lcd.print( (char) 223 );   // Stampa '°'
  lcd.print( 'C' );
  
  lcd.setCursor( 0, 1 );     // Va in posizione di home: colonna 1, riga 2
  lcd.print( "CORRIDOIO: ");
  dtostrf(temp1, 2, 1, _buffer);
  lcd.print( _buffer );         // Stampa solo la parte intera della temp.
  lcd.print( ' ' );          // Stampa uno spazio
  lcd.print( (char) 223 );   // Stampa '°'
  lcd.print( 'C' );
  
  lcd.setCursor( 0, 2 );     // Va in posizione di home: colonna 1, riga 3
  lcd.print( "BAGNO:     ");
  dtostrf(temp2, 2, 1, _buffer);
  lcd.print( _buffer );         // Stampa solo la parte intera della temp.
  lcd.print( ' ' );          // Stampa uno spazio
  lcd.print( (char) 223 );   // Stampa '°'
  lcd.print( 'C' );  

  lcd.setCursor( 0, 3 );     // Va in posizione di home: colonna 1, riga 3
  lcd.print( "MANDATA:   ");
  dtostrf(temp3, 2, 1, _buffer);
  lcd.print( _buffer );         // Stampa solo la parte intera della temp.
  lcd.print( ' ' );          // Stampa uno spazio
  lcd.print( (char) 223 );   // Stampa '°'
  lcd.print( 'C' );  
    
  delay(5000);  
}
/* Legge la temperatura */
float readTemp(int pin_to_read)
{
  float temp = 0.0;       // valore convertito in temperatura (°C)
  int val = 0;            // valore quantizzato dall'ADC [0..1023]
  int nread = 10;          // numero di letture (da 5 a 8)
  float somma = 0.0;      // somma delle letture
  for (int i=0; i<nread; i++)
  {
    val = analogRead( pin_to_read );              // legge il dato della tensione sul pin 'LM35_pin'
    temp = ( 100.0 *  vref * val ) / 1024.0;   // lo converte in °C
    somma += temp;                             // aggiunge alla somma delle temperature lette  
  }  
  return ( somma / nread );                     // ne calcola il valore medio
}

