/*****************************************************************************/
// Código para un simple generador de señal de onda cuadrada, para probar
// el PCF8574AP, el objetivo es subir y bajar la frecuencia de una señal para
// verificar cuál es la frecuancia máxima que el expansor es capaz de leer
// Desarrollado por: Gustavo Trejo -Agosto de 2021
/*****************************************************************************/
#INCLUDE<16F887.h>
#FUSES XT,PUT,NOPROTECT,BROWNOUT,NOLVP,NOWDT
#USE delay(internal=8000000)
#USE RS232(baud=9600,xmit=PIN_C6,rcv=PIN_C7, BITS=8)
#use standard_io(c)

#BYTE PORTA=5;


#DEFINE out PORTA,0
/***************************Variables globales********************************/
char data=0;
unsigned int16 delay=0; //mitad del periodo en us
/***************************Interrupciones************************************/
#int_RDA
void RDA_isr(){
   data=getc();
   if(data=='+')
      delay=delay+100;
   else if(data=='-')
      delay=delay-100;
      
   printf("%lu\n",delay);
}
void main(){
set_tris_a(0b11111110);
bit_clear(out);

ENABLE_INTERRUPTS(GLOBAL);
ENABLE_INTERRUPTS(int_RDA);

delay=2000;

while(true){

   bit_set(out);
   delay_us(delay);
   bit_clear(out);
   delay_us(delay);
  
}
}
