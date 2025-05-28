#include "stm32f407xx.h"
#include "string.h"

#define Button_Pressed ENABLE

void delay()
{
	for(uint32_t i = 0;i<500000/2;i++);
}

int main(void)
{
	// for handling of led

	GPIO_Handle_t GpioLed,GpioButton;

	//memset is a standard C library function used to set memory (RAM) to a specific value.
	//In embedded C (especially with STM32, drivers, etc.), we often use memset to initialize
	//a structure to zero before using it.

	memset(&GpioLed,0,sizeof(GpioLed));
	memset(&GpioButton,0,sizeof(GpioButton));

	GpioLed.pGPIOx = GPIOD;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOD,ENABLE);
	GPIO_Init(&GpioLed);

	// for handling of button

	//GPIO_Handle_t GpioButton;
	GpioButton.pGPIOx = GPIOD;
	GpioButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GpioButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	GpioButton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioButton.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PU;

	GPIO_PeriClockControl(GPIOA,ENABLE);
	GPIO_Init(&GpioButton);

	GPIO_IRQInterruptConfig(IRQ_NO_EXTI9_5,ENABLE);
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI9_5,NVIC_IRQ_PRI15);

	while(1);
	return 0;
}

// Button press → Interrupt triggered → Clear the interrupt → Toggle LED
void EXTI9_5_IRQHandler()
{
	delay();
	GPIO_IRQHandling(GPIO_PIN_NO_5);
	GPIO_ToggleOutputPin(GPIOD,GPIO_PIN_NO_12);
}





