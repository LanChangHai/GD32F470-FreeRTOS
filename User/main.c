#include "gd32f4xx.h"
#include "Usart.h"
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "ff.h"
#include "drive.h"

TaskHandle_t StartTask_Handler;

extern sd_card_info_struct sd_cardinfo;                            /* information of SD card */

void LED_Init(void);
void CrateTask(void *pvParameters);
void task_led2(void *pvParameters);
void task_led4(void *pvParameters);

int main(void)
{
    /* configure systick */
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

    LED_Init();  // led��ʼ��

    xTaskCreate(CrateTask ,"CrateTask" , 128, NULL, 1, &StartTask_Handler);

    vTaskStartScheduler();          //�����������

    while(1)
    {
        ;
    }
    while (1) {
    }
}

void LED_Init(void)
{
    //LED2
    rcu_periph_clock_enable(RCU_GPIOD);
    gpio_mode_set(GPIOD,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_PIN_7);
    gpio_output_options_set(GPIOD,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_7);
    //LED4
    rcu_periph_clock_enable(RCU_GPIOA);
    gpio_mode_set(GPIOA,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_PIN_5);
    gpio_output_options_set(GPIOA,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_5);
}

void CrateTask(void *pvParameters){

    taskENTER_CRITICAL();

    xTaskCreate(task_led2 , "task_led2" ,50 ,NULL , 2 ,0);

    xTaskCreate(task_led4 , "task_led4" ,50 ,NULL , 2 ,0);

    vTaskDelete(StartTask_Handler);

    taskEXIT_CRITICAL();

}

void task_led2(void *pvParameters)
{
    FATFS fs;                         /* FatFs�ļ�ϵͳ���� */
    FIL fnew;                         /* �ļ����� */
    FRESULT res_sd;                /* �ļ�������� */
    UINT fnum;                        /* �ļ��ɹ���д���� */
    BYTE ReadBuffer[1024]= {0};       /* �������� */
    BYTE WriteBuffer[] =              /* д������*/
        "12345\r\n";

    printf("\r\n****** ����һ��SD�� �ļ�ϵͳʵ�� ******\r\n");

    //���ⲿSPI Flash�����ļ�ϵͳ���ļ�ϵͳ����ʱ���SPI�豸��ʼ��
    res_sd = f_mount(&fs,"0:",1);

    /*----------------------- ��ʽ������ ---------------------------*/
    /* ���û���ļ�ϵͳ�͸�ʽ�����������ļ�ϵͳ */
    if (res_sd == FR_NO_FILESYSTEM) {
        printf("��SD����û���ļ�ϵͳ���������и�ʽ��...\r\n");
        /* ��ʽ�� */
        res_sd=f_mkfs("0:",0,0,0);

        if (res_sd == FR_OK) {
            printf("��SD���ѳɹ���ʽ���ļ�ϵͳ��\r\n");
            /* ��ʽ������ȡ������ */
            res_sd = f_mount(NULL,"0:",1);
            /* ���¹��� */
            res_sd = f_mount(&fs,"0:",1);
        } else {
            printf("������ʽ��ʧ�ܡ�����\r\n");
            while (1);
        }
    } else if (res_sd!=FR_OK) {
        printf("����SD�������ļ�ϵͳʧ�ܡ�(%d)\r\n",res_sd);
        printf("��������ԭ��SD����ʼ�����ɹ���\r\n");
        while (1);
    } else {
        printf("���ļ�ϵͳ���سɹ������Խ��ж�д����\r\n");
    }

    /*--------------------- �ļ�ϵͳ���ԣ�д���� -----------------------*/
    /* ���ļ�������ļ��������򴴽��� */
    printf("\r\n****** ���������ļ�д�����... ******\r\n");
    res_sd=f_open(&fnew,"0:FatFs��д�����ļ�.txt",FA_CREATE_ALWAYS|FA_WRITE);
    if ( res_sd == FR_OK ) {
        printf("����/����FatFs��д�����ļ�.txt�ļ��ɹ������ļ�д�����ݡ�\r\n");
        /* ��ָ���洢������д�뵽�ļ��� */
        res_sd=f_write(&fnew,WriteBuffer,sizeof(WriteBuffer),&fnum);
        if (res_sd==FR_OK) {
            printf("���ļ�д��ɹ���д���ֽ����ݣ�%d\n",fnum);
            printf("�����ļ�д�������Ϊ��\r\n%s\r\n",WriteBuffer);
        } else {
            printf("�����ļ�д��ʧ�ܣ�(%d)\n",res_sd);
        }
        /* ���ٶ�д���ر��ļ� */
        f_close(&fnew);
    } else {
        printf("������/�����ļ�ʧ�ܡ�\r\n");
    }

    /*------------------ �ļ�ϵͳ���ԣ������� --------------------------*/
    printf("****** ���������ļ���ȡ����... ******\r\n");
    res_sd=f_open(&fnew,"0:FatFs��д�����ļ�.txt",FA_OPEN_EXISTING|FA_READ);
    if (res_sd == FR_OK) {
        printf("�����ļ��ɹ���\r\n");
        res_sd = f_read(&fnew, ReadBuffer, sizeof(ReadBuffer), &fnum);
        if (res_sd==FR_OK) {
            printf("���ļ���ȡ�ɹ�,�����ֽ����ݣ�%d\r\n",fnum);
            printf("����ȡ�õ��ļ�����Ϊ��\r\n%s \r\n", ReadBuffer);
        } else {
            printf("�����ļ���ȡʧ�ܣ�(%d)\n",res_sd);
        }
    } else {
        printf("�������ļ�ʧ�ܡ�\r\n");
    }
    /* ���ٶ�д���ر��ļ� */
    f_close(&fnew);

    /* ����ʹ���ļ�ϵͳ��ȡ�������ļ�ϵͳ */
    f_mount(NULL,"0:",1);

    /* ������ɣ�ͣ�� */
    while (1) {
    }
}

void task_led4(void *pvParameters)
{
    while(1)
    {
        gpio_bit_write(GPIOA, GPIO_PIN_5, SET);
        vTaskDelay(200);
        gpio_bit_write(GPIOA, GPIO_PIN_5, RESET);
        vTaskDelay(200);
    }
}
