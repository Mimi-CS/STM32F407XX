#include "stm32f407xx.h"

#define Button_Pressed ENABLE

void delay()
{
	for(uint32_t i = 0;i<500000/2;i++);
}

int main(void)
{
	// for handling of led

	GPIO_Handle_t GpioLed;
	GpioLed.pGPIOx = GPIOD;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOD,ENABLE);
	GPIO_Init(&GpioLed);

	// for handling of button

	GPIO_Handle_t GpioButton;
	GpioLed.pGPIOx = GPIOA;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOA,ENABLE);
	GPIO_Init(&GpioButton);
	while(1)
	{
		if(GPIO_ReadFromInputPin(GPIOA,GPIO_PIN_NO_0) == Button_Pressed)
		{
			delay();
			GPIO_ToggleOutputPin(GPIOD,GPIO_PIN_NO_12);

		}
	}
	return 0;
}





