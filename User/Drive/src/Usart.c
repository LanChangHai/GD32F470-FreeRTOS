//
// Created by 7invensun on 15/12/2023.
//

#include "Usart.h"

int _write (int fd, char *pBuffer, int size)
{
    for (int i = 0; i < size; i++)
    {
        while(RESET == usart_flag_get(EVAL_COM, USART_FLAG_TBE));//等待上一次串口数据发送完成
        usart_data_transmit(EVAL_COM,pBuffer[i]);//串口发送数据
    }
    return size;
}

uint8_t UsartInit(UsartClass TypeOfInit)
{
    switch (TypeOfInit.GpioTXPort) {
        case GPIOA:
            rcu_periph_clock_enable(RCU_GPIOA);
            break;
        case GPIOB:
            rcu_periph_clock_enable(RCU_GPIOB);
            break;
        case GPIOC:
            rcu_periph_clock_enable(RCU_GPIOC);
            break;
        case GPIOD:
            rcu_periph_clock_enable(RCU_GPIOD);
            break;
        case GPIOE:
            rcu_periph_clock_enable(RCU_GPIOE);
            break;
        case GPIOF:
            rcu_periph_clock_enable(RCU_GPIOF);
            break;
        case GPIOG:
            rcu_periph_clock_enable(RCU_GPIOG);
            break;
        case GPIOH:
            rcu_periph_clock_enable(RCU_GPIOH);
            break;
        case GPIOI:
            rcu_periph_clock_enable(RCU_GPIOI);
            break;
    }
    switch (TypeOfInit.GpioRXPort) {
        case GPIOA:
            rcu_periph_clock_enable(RCU_GPIOA);
            break;
        case GPIOB:
            rcu_periph_clock_enable(RCU_GPIOB);
            break;
        case GPIOC:
            rcu_periph_clock_enable(RCU_GPIOC);
            break;
        case GPIOD:
            rcu_periph_clock_enable(RCU_GPIOD);
            break;
        case GPIOE:
            rcu_periph_clock_enable(RCU_GPIOE);
            break;
        case GPIOF:
            rcu_periph_clock_enable(RCU_GPIOF);
            break;
        case GPIOG:
            rcu_periph_clock_enable(RCU_GPIOG);
            break;
        case GPIOH:
            rcu_periph_clock_enable(RCU_GPIOH);
            break;
        case GPIOI:
            rcu_periph_clock_enable(RCU_GPIOI);
            break;
    }
    switch (TypeOfInit.UsartPort) {
        case USART0:
            rcu_periph_clock_enable(RCU_USART0);
            gpio_af_set(TypeOfInit.GpioTXPort, GPIO_AF_7, TypeOfInit.GpioTXPin);
            gpio_af_set(TypeOfInit.GpioRXPort, GPIO_AF_7, TypeOfInit.GpioRXPin);
            break;
        case USART1:
            rcu_periph_clock_enable(RCU_USART1);
            gpio_af_set(TypeOfInit.GpioTXPort, GPIO_AF_7, TypeOfInit.GpioTXPin);
            gpio_af_set(TypeOfInit.GpioRXPort, GPIO_AF_7, TypeOfInit.GpioRXPin);
            break;
        case USART2:
            rcu_periph_clock_enable(RCU_USART2);
            gpio_af_set(TypeOfInit.GpioTXPort, GPIO_AF_7, TypeOfInit.GpioTXPin);
            gpio_af_set(TypeOfInit.GpioRXPort, GPIO_AF_7, TypeOfInit.GpioRXPin);
            break;
        case UART3:
            rcu_periph_clock_enable(RCU_UART3);
            gpio_af_set(TypeOfInit.GpioTXPort, GPIO_AF_8, TypeOfInit.GpioTXPin);
            gpio_af_set(TypeOfInit.GpioRXPort, GPIO_AF_8, TypeOfInit.GpioRXPin);
            break;
        case UART4:
            rcu_periph_clock_enable(RCU_UART4);
            gpio_af_set(TypeOfInit.GpioTXPort, GPIO_AF_8, TypeOfInit.GpioTXPin);
            gpio_af_set(TypeOfInit.GpioRXPort, GPIO_AF_8, TypeOfInit.GpioRXPin);
            break;
        case USART5:
            rcu_periph_clock_enable(RCU_USART5);
            gpio_af_set(TypeOfInit.GpioTXPort, GPIO_AF_8, TypeOfInit.GpioTXPin);
            gpio_af_set(TypeOfInit.GpioRXPort, GPIO_AF_8, TypeOfInit.GpioRXPin);
            break;
        case UART6:
            rcu_periph_clock_enable(RCU_UART6);
            gpio_af_set(TypeOfInit.GpioTXPort, GPIO_AF_8, TypeOfInit.GpioTXPin);
            gpio_af_set(TypeOfInit.GpioRXPort, GPIO_AF_8, TypeOfInit.GpioRXPin);
            break;
        case UART7:
            rcu_periph_clock_enable(RCU_UART7);
            gpio_af_set(TypeOfInit.GpioTXPort, GPIO_AF_8, TypeOfInit.GpioTXPin);
            gpio_af_set(TypeOfInit.GpioRXPort, GPIO_AF_8, TypeOfInit.GpioRXPin);
            break;
    }

    gpio_mode_set(TypeOfInit.GpioTXPort, GPIO_MODE_AF, GPIO_PUPD_PULLUP, TypeOfInit.GpioTXPin);
    gpio_output_options_set(TypeOfInit.GpioTXPort, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, TypeOfInit.GpioTXPin);
    gpio_mode_set(TypeOfInit.GpioRXPort, GPIO_MODE_AF, GPIO_PUPD_PULLUP, TypeOfInit.GpioRXPin);
    gpio_output_options_set(TypeOfInit.GpioRXPort, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, TypeOfInit.GpioRXPin);

    usart_deinit(TypeOfInit.UsartPort);
    usart_baudrate_set(TypeOfInit.UsartPort, TypeOfInit.BaudRate);
    usart_receive_config(TypeOfInit.UsartPort, USART_RECEIVE_ENABLE);
    usart_transmit_config(TypeOfInit.UsartPort, USART_TRANSMIT_ENABLE);
    usart_enable(TypeOfInit.UsartPort);

    return 0;
}



