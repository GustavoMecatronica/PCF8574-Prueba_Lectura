/*****************************************************************************/
// C�digo para realizar la lectura del integrado PCF8574AP, esto para encontrar
// la m�xima frecuencia a la cu�l el IC es capaz de leer una se�al.
// Desarrollado por: Gustavo Trejo -Agosto de 2021
/*****************************************************************************/
#INCLUDE<16F887.h>
#FUSES XT,PUT,NOPROTECT,BROWNOUT,NOLVP,WDT
#USE delay(internal=8000000)
#USE I2C(MASTER, SDA=PIN_C4, SLOW, SCL=PIN_C3, NOFORCE_SW)
#use standard_io(c)

#BYTE PORTA=5;
#BYTE PORTB=6;

#DEFINE btn PORTA,0
/***************************Variables globales********************************/
unsigned int data=0;
int16 count;

void main(){
set_tris_b(0);
set_tris_a(0b01111111);
output_low(PIN_A7);
setup_wdt(WDT_2304MS); //config del watchdog cada 2.304 segundos
while(!bit_test(btn)){
   delay_ms(200);
   output_toggle(PIN_A7);
   restart_wdt();
}
while(true){
   
   output_low(PIN_A7);
   delay_ms(1000);
   output_high(PIN_A7);
   count=0;
   restart_wdt();
   while(count<=1990){
      i2c_start();
      i2c_write(0x71);
      data=i2c_read(1);
      i2c_stop();
      PORTB=data;
      delay_ms(1);
      count++;
      restart_wdt();
   }
}
}
