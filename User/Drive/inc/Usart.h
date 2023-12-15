//
// Created by 7invensun on 15/12/2023.
//

#ifndef GD32F470_FREERTOS_USART_H
#define GD32F470_FREERTOS_USART_H

#include "gd32f4xx_usart.h"
#include "gd32f4xx_gpio.h"

#define EVAL_COM USART0 //定义重定向的端口

/*
 *  uint32_t UsartPort 串口号
 *  uint32_t BaudRate 波特率
 *  uint32_t GpioPort 串口对应的Gpio组
 *  uint32_t GpioPin 串口对应的Gpio号,查阅数据手册必须有对应功能才可
 */
typedef struct
{
    uint32_t UsartPort;
    uint32_t BaudRate;
    uint32_t GpioTXPort;
    uint32_t GpioTXPin;
    uint32_t GpioRXPort;
    uint32_t GpioRXPin;
}UsartClass;

uint8_t UsartInit(UsartClass TypeOfInit);

#endif  // GD32F470_FREERTOS_USART_H
