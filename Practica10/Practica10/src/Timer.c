#include <avr/interrupt.h>
#include <inttypes.h>
#include <avr/io.h>
/*	Definir el macro que calcula los ticks en base a al parametro de frecuencia (f). */
#define TICKS(f) (.001/(1/(f/64)))-1    /*Definida para 1ms*/
static volatile uint8_t SecFlag = 0;

struct note{
	uint16_t freq;
	uint16_t delay;
};

void Timer0_Ini ( void ){
	/* 	Permanece igual, ocasionando una interrupción cada 1 ms en modo CTC. */
	double freq = 16000000;
	TCNT0 = 0;							/*Clear Timer*/
	TCCR0A = 2<<WGM00;					/*CTC*/
	TCCR0B = 3<<CS00;					/*PS:64*/
	OCR0A = TICKS(freq);				/*Valor a comparar*/
	TIFR0 = 1<<OCF0A;					/*Limpiamos la bandera de interrupción*/
	TIMSK0 = 1<<OCIE0A;					/*Habilitamos la interrupción de comapración de A*/
	sei();
}

ISR(TIMER0_COMPA_vect){ 
	static uint16_t mSecCnt;		/* 	Código para actualizar bandera de segundos */
	mSecCnt++; 						/* Incrementa contador de milisegundos */
	if( mSecCnt==1000 ){
		mSecCnt=0;
		SecFlag++; 					/* Bandera de Segundos */
	}
	/*	Agregar las instrucciones necesarias para reproducir
		la siguiente nota en el arreglo dependiendo de la duración, 
		e insertar los silencios entre cada nota. */
}

void Timer2_Freq_Gen(uint8_t ticks){
	/* 	Si "ticks" es mayor que 0 entonces, inicializa y habilita el Generador 
		de Frecuencia del Timer2 con el tope dado por "ticks".
		De lo contrario se requiere deshabilitar el Generador, generando de 
		esta forma el silencio (0 lógico). */
}

void Timer2_Play(const struct note song[], unsigned int len)
{
	/*	Función que establece las condiciones necesarias para que
		el generador recorra el arreglo de notas. */
}

void Timer2_Volume(uint8_t direction){
	/* 	Ajusta el ciclo de trabajo para incrementar o decrementar  el volumen
	   	de las notas que se estan generando. */
}