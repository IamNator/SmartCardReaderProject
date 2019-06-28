

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

//#ifndef F_CPU 1000000UL
#define FOSC 1000000
#define BAUD FOSC/372
#define SMUBRR FOSC/16/BAUD-1

void UART_init(uint16_t ubrr);
void UART_transmit(uint8_t data);
uint8_t UART_receive(void);
//void Parallel_transiver(unsigned char data);
//void SPI_send(unsigned char data);
//unsigned char SPI_receive(void);
uint16_t Binary_to_array(uint16_t binary, uint8_t array_size);
void load_array(uint8_t  arrayONE[], uint8_t * arrayTWO[], uint8_t array_size);


int main(void)
{
	UART_init(SMUBRR);
	uint8_t data_array[8];

	while(1)
	{
			uint8_t data;
			
					data = (UART_receive());
						       
					 uint16_t i=0;
						        
			            for(i=0; i<=(7); i++)
			            {
			                if(data & (1<<i)){
			                    data_array[i] = 1;
			                }else if (!(data & (1<<i))){
			                    data_array[i] = 0;
			                };
			            }
	}	
	return 0;
}



void UART_init(uint16_t ubrr)
{   
	/*set UART baud rate*/
	UBRR0H = (ubrr>>8);
	UBRR0L = (ubrr);

	/*enable tx and rx pin*/
	UCSR0B |= ((1<<RXEN0)|(1<<TXEN0));

	/*Set frame format: 8bits, 2stop_bits*/
	UCSR0C |= (1<<USBS0)|(3<<UCSZ00);

	/*enable parity error*/
	UCSR0A |= (1<<UPE0);
}

void UART_transmit(uint8_t data)
{
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}


uint8_t UART_receive(void)
{
	while (!(UCSR0A & (1<<RXC0)));
  return UDR0;
}

//SPI_send(unsigned char data)
//{ 
///}

