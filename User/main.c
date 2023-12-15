#include "gd32f4xx.h"
#include "systick.h"
#include "Usart.h"
#include <assert.h>
#include <stdio.h>
int main(void)
{
    /* configure systick */
    systick_config();
    UsartClass Debug={
        .UsartPort = USART0,
        .BaudRate = 115200U,
        .GpioTXPort = GPIOA,
        .GpioRXPort = GPIOA,
        .GpioTXPin = GPIO_PIN_9,
        .GpioRXPin = GPIO_PIN_10
    };
    setvbuf(stdout, NULL, _IONBF, 0);







    while (1);
}
