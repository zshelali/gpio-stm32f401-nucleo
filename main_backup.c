
#include <stdint.h>
#include "stm32f401xe.h"

int main(void)
{
	//activation clock pour A et C
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;

	//declaration pins
	GPIO_TypeDef* PA5 = GPIOA;

	GPIO_TypeDef* PC13 = GPIOC;

	GPIO_TypeDef* PA1 = GPIOA;
	GPIO_TypeDef* PA0 = GPIOA;


	//mode sortie : 01
	PA5->MODER |= (1 << 10);

	//LED PA1 OUTPUT, OPEN DRAIN, LOW SPEED
	PA5->ODR |= (1 << 1);
	PA1->MODER |= (1 << 2);
	PA1->OTYPER |= (1 << 1);

	//BOUTON NOIR PA0 INPUT, PULL-UP
	PA0->MODER &= ~(1 << 0);
	PA0->PUPDR |= 1;





	//multiplicateur de vitesse
	uint32_t mult = 1;

	//timer pour remplacer sleep
		uint32_t timer = 800000;

	while(1){
		PA5->ODR |= 1 << 5; //allumer led
		if ((PC13->IDR & (1 << 13))){ //si bouton non presse
			mult = 1;
		}
		else {
			mult=2; //si bouton presse
		}
		while (timer > 0){
			timer-=4;
			if ((PC13->IDR & (1 << 13))){ //si bouton non presse
						mult = 1;
					}
			else {
						mult=2; //si bouton presse
					}

			if (!(PA0->IDR & 1)){
						PA1->ODR &= ~(1 << 1); //eteindre led rouge de l'exercice 2 // la valeur est inversee
					}
			else {
						PA1->ODR |= (1 << 1);
					}

		}
		timer = 800000/mult;

		// ODR bouton PA0 = 0 ==> presse

		if (!(PA0->IDR & 1)){
			PA1->ODR &= ~(1 << 1); //eteindre led rouge de l'exercice 2 // la valeur est inversee
		}
		else {
			PA1->ODR |= (1 << 1);
		}

		PA5->ODR &= ~(1 << 5); //eteindre led verte
		
		while (timer > 0){
			timer-=4;
			if ((PC13->IDR & (1 << 13))){ //si bouton non presse
						mult = 1;
					}
			else {
						mult=2; //si bouton presse
					}

			if (!(PA0->IDR & 1)){
						PA1->ODR &= ~(1 << 1); //eteindre led rouge de l'exercice 2 // la valeur est inversee
					}
					else {
						PA1->ODR |= (1 << 1);
			}

		}
		timer = 800000/mult;

	}
}





