#include<tm4c123gh6pm.h>
#include "tm4c123gh6pm.h"	// Header file accesses registers in TMC123 microcontroller

void PWMsig(void);
void wait(void)
{
/*	unsigned long volatile time;
	time = 727240*200/91;  // 0.1sec
  while(time){
    time--;
  }*/
   TIMER0_TAMATCHR_R=0x1E84800; // Match register value loaded for 2 sec delay
   TIMER0_CTL_R=0x1; //Timer enabled
}

int main(void)
{
    TIMER0_CFG_R=0x0; //Configuration Register
    TIMER0_TAMR_R=0x1; //Setting One-Shot mode
    TIMER0_TAR_R=0x0; //Setting count-up mode
    //Match Value given for 2 sec delay
    GPIO_PORTF_DIR_R=0x0;//PF0 configured as input
    GPIO_PORTF_DEN_R=0x1;//PF configured as digital io
	
    int x, mask=0x1;
  
   	SYSCTL_RCGC0_R=0x00100000;
        GPIO_PORTB_AFSEL_R=0x00010000; //enable alternate function (pwm) on PB6
        GPIO_PORTB_PCTL_R=0x100;//assign the PWM signals to the PB6(pin 1)
        PWM0_CTL_R=0x00000000;
        PWM0_0_GENA_R=0x8C;
        PWM0_0_GENB_R=0x80C;//for count-down mode with immediate updates
        PWM0_0_LOAD_R=0x18F;//period loaded for a 25-KHz frequency
        PWM0_0_CMPA_R=0x12B;//pulse width of the MnPWM0 pin for 25% duty cycle
        PWM0_0_CMPB_R=0x63;//pulse width of the MnPWM0 pin for 75% duty cycle

	while(1)
	{
	    x=GPIO_PORTF_DATA_R&mask;
	    if(x==1)
	        PWMsig();//Start sun shade motor (PWM output)
	    else
	        PWM0_ENABLE_R=0x0;//disable PWM output
			wait();
	}
	
	return 0;
}

void PWMsig(void)
{

    PWM0_CTL_R=0x1;//Start the timer in PWM generator
    PWM0_ENABLE_R=0x3;//Enable PWM outputs
}



