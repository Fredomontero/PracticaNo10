#include <avr/interrupt.h>
#include <inttypes.h>
#include <avr/io.h>

/*función AutoBaudRate*/
void UART0_AutoBaudRate(void){
	UCSR0A = 1<<U2X0;							/*Doble velocidad*/
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);				/*Habilitamos receptor y transmisor*/
	UCSR0C= (3<<UCSZ00);						/*Estableecemos el formato*/
	TCCR0A = 0x00;								/*Timer 0: Modo normal*/
	TCCR0B = 2<<CS00;							/*Preescalador: 8*/
	while(PINE&(1<<PE0));
	TCNT0 = 0;
	while(!(PINE&(1<<PE0))){
	}
	TCCR0B = 0x00;
	UBRR0 = TCNT0-1;
}

/*Función que retorna el byte recibido por el puerto serie UART0*/
uint8_t UART0_getchar(void){
	while(!(UCSR0A&(1<<UDRE0)))
	return UDRE0;
}