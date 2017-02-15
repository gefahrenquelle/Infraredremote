/******************************************************************************/
/*   (C) Copyright HTL - HOLLABRUNN  2009-2009 All rights reserved. AUSTRIA   */ 
/*                                                                            */ 
/* File Name:   Detect.c                                                      */
/* Autor: 		Josef Reisinger                                               */
/* Version: 	V1.00                                                         */
/* Date: 		11/30/2009                                                    */
/* Description: Erkennen von Flanken, Ausagabe eine HEX Zahl                  */
/******************************************************************************/
/* History: 	V1.00  creation										          */
/******************************************************************************/
#include <ARMV10_STD.h>

/*---------------------------Prototypes ---------------------------------------*/

/*-----------------------------  Bit Banding Alias Adesses -------------------*/
#define NEC_in  *((volatile unsigned long *)(BITBAND_PERI(GPIOA_IDR,9)))	// PA9


/******************************************************************************/
/*            U N T E R P R O G R A M M:    init_leds_switches                */
/*                                                                            */
/* Aufgabe:   Initialisiert Portleitungen für LED / Schalterplatine           */
/* Input:                                                                     */
/* return:	                                                                  */
/******************************************************************************/
void nec_init(void) {
int temp;

RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;       // enable clock for GPIOA (APB2 Peripheral clock enable register)

// Schalter auf Led /Schalterplatine
temp = GPIOA->CRH;
temp &= ~(0x0F00);		// PA9 Konfigurationsbit löschen
temp |= (0x04UL << 8);	// PA9 als Floating Input definieren
GPIOA->CRH = temp;
} 

/******************************************************************************/
/*                                MAIN function                               */
/******************************************************************************/
int main (void) {

char zahl;
int column,row,bit;

nec_init();
lcd_init();

lcd_clear();

zahl = '0';
column = 0;
row = 0;
bit = 0;


	 do {			 //*Warte auf fallend Flanke
	 } while (NEC_in ==1);
	 do {			 //*Warte auf steigend Flanke
	 } while (NEC_in ==0);

	do { 
	  do {	  		
		}while (NEC_in == 1);			 //*Warte auf fallend Flanke
//	  zahl='1';
//	  lcd_set_cursor(1,column);
//	  column++;
//	  lcd_put_char (zahl);

	  do {			 //*Warte auf steigend Flanke
		} while (NEC_in ==0);
	  wait_ms (1);
	  if (NEC_in == 0)
	  {
	  	zahl = '1';
	  }
	  else
	  {
	  	zahl = '0';
	  }
	  if (column == 15)
	  {
	  	row++;
		column = 0;
	  }
	  lcd_set_cursor(row,column);
	  column++;
	  lcd_put_char (zahl);
	  zahl = '9';
	  bit++;
	  } while (bit <= 31);
}
