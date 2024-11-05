#include <stdint.h>
#include "stm32f401xe.h"

int main(void)
{
	//activation clock pour A et C
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;

	/*
     ============= declaration et initialisation des pins et des variables =============
     * PA5 : LED verte clignotante (GPIOA)
     * PC13 : Bouton user bleu (GPIOC)
     * PA1 : LED de la Breadboard (GPIOA)
     * PA0 : Bouton de la Breadboard (GPIOA)
     */
    
	GPIO_TypeDef* PA5 = GPIOA;
	GPIO_TypeDef* PC13 = GPIOC;
	GPIO_TypeDef* PA1 = GPIOA;
	GPIO_TypeDef* PA0 = GPIOA;
    
    
    //---- LED PA1 OUTPUT, MISE A 0 ----
    PA5->MODER |= (1 << 10);
    PA5->ODR |= (1 << 1);
    
    //---- LED PA1 OUTPUT, OPEN DRAIN, LOW SPEED ----
    PA1->MODER |= (1 << 2);
    PA1->OTYPER |= (1 << 1);

    //---- BOUTON NOIR PA0 INPUT, PULL-UP ----
    PA0->MODER &= ~(1 << 0);
    PA0->PUPDR |= 1;


    //multiplicateur de vitesse
    uint32_t mult = 1;

    //initialisation du timer pour remplacer sleep
    uint32_t timer = 800000;

    /*
     ======================================================================================
     */
    
    

	

	while(1){
        //allumer la LED
		PA5->ODR |= 1 << 5;
        //vérification de la pression du bouton user PC13
		if ((PC13->IDR & (1 << 13))){ /*si bouton non presse, mult reste à 1
			mult = 1;                   on pourrait retirer cette comparaison
		}                               mais le code fonctionne avec */
		else {
			mult=2; //si bouton user est presse, mult passe à 2
		}
		while (timer > 0){
            //on decremente le timer par 4 afin de garder environ 1Hz
			timer-=4;
            /*
             On effectue une verification du bouton  a chaque iteration
             pendant le temps d ecoulement du timer
             afin de garder une certaine fluidite lorsqu on presse le bouton
             */
			if ((PC13->IDR & (1 << 13))){
						mult = 1;
					}
			else {
						mult=2;
					}

            /*
             Si le bouton de la Breadboard PA0 est presse, on allume la LED de la Breadboard PA1
             Sinon on l eteint
             
             la valeur du bouton fonctionne comme suit :
             
             OUTPUT bouton PA0 = 0 ==> bouton presse
                               = 1 ==> bouton relache
             
             */
            
			if (!(PA0->IDR & 1)){
						PA1->ODR &= ~(1 << 1);
					}
			else {
						PA1->ODR |= (1 << 1);
					}
		}
            
        //eteindre led verte apres que le timer soit ecoule
        PA5->ODR &= ~(1 << 5);
            
        /*on reinitialise le timer divise par mult
         qui vaut :
         * 1 quand le bouton n est pas presse
         * 2 quand le bouton est presse, afin de multiplier la vitesse
            du clignotement par deux
         */
            
		timer = 800000/mult;
        
		
        
        
        //autre verification pour le bouton.
		if (!(PA0->IDR & 1)){
			PA1->ODR &= ~(1 << 1); //eteindre led rouge de l exercice 2 // la valeur est inversee
		}
		else {
			PA1->ODR |= (1 << 1);
		}
        
		//nouveau timer avec verification des deux boutons pour assurer la fluidite pour l utilisateur lorsqu il en presse un
		while (timer > 0){
			timer-=4;
			if ((PC13->IDR & (1 << 13))){
						mult = 1;
					}
			else {
						mult=2;
					}

			if (!(PA0->IDR & 1)){
						PA1->ODR &= ~(1 << 1);
					}
					else {
						PA1->ODR |= (1 << 1);
			}
		}
        //reinitialisation du timer
		timer = 800000/mult;

	}
}





