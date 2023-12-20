#include "gd32f4xx.h"
#include "systick.h"
#include "Usart.h"
#include <assert.h>
#include <stdio.h>
#include "SdRam.h"

/* SDRAM */
#define BUFFER_SIZE                ((uint32_t)0x0400)
#define WRITE_READ_ADDR            ((uint32_t)0x0000)
uint32_t writereadstatus = 0;
uint8_t txbuffer[BUFFER_SIZE];
uint8_t rxbuffer[BUFFER_SIZE];

int main(void)
{
    /* configure systick */
    systick_config();
    SDRamInit();
    UsartClass Debug={
        .UsartPort = USART0,
        .BaudRate = 115200U,
        .GpioTXPort = GPIOA,
        .GpioRXPort = GPIOA,
        .GpioTXPin = GPIO_PIN_9,
        .GpioRXPin = GPIO_PIN_10
    };
    UsartInit(Debug);
    setvbuf(stdout, NULL, _IONBF, 0);

   printf("\r\nSDRAM initialized!");
    delay_1ms(1000);

    //* fill txbuffer *//*
    fill_buffer(txbuffer, BUFFER_SIZE, 0x0000);

    //* write data to SDRAM *//*
    sdram_writebuffer_8(EXMC_SDRAM_DEVICE0, txbuffer, WRITE_READ_ADDR, BUFFER_SIZE);

    printf("\r\nSDRAM write data completed!");
    delay_1ms(1000);

    //* read data from SDRAM *//*
    sdram_readbuffer_8(EXMC_SDRAM_DEVICE0, rxbuffer, WRITE_READ_ADDR, BUFFER_SIZE);

    printf("\r\nSDRAM read data completed!");
    delay_1ms(1000);

    printf("\r\nCheck the data!");
    delay_1ms(1000);

    //* compare two buffers *//*
    for(int i = 0; i < BUFFER_SIZE; i++) {
        if(rxbuffer[i] != txbuffer[i]) {
            writereadstatus ++;
            break;
        }
    }

    if(writereadstatus) {
        printf("\r\nSDRAM test failed!");

        //* failure, light on LED3 *//*
    } else {
        printf("\r\nSDRAM test successed!");
        delay_1ms(1000);
        printf("\r\nThe data is:\r\n");
        delay_1ms(1000);
        for(int i = 0; i < BUFFER_SIZE; i++) {
            printf("%6x", rxbuffer[i]);
            if(((i + 1) % 16) == 0) {
                printf("\r\n");
            }
        }
        //* success, light on LED1 *//*
    }

    while (1);
}
