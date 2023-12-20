//
// Created by 7invensun on 15/12/2023.
//

#include "SdRam.h"

static void SDRamGPIOInit()
{
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOD);
    rcu_periph_clock_enable(RCU_GPIOE);
    rcu_periph_clock_enable(RCU_GPIOF);
    rcu_periph_clock_enable(RCU_GPIOG);

    gpio_af_set(GPIOC,GPIO_AF_12,GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3);
    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3);
    gpio_output_options_set(GPIOC,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3);

    gpio_af_set(GPIOD,GPIO_AF_12,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_14|GPIO_PIN_15);
    gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_14|GPIO_PIN_15);
    gpio_output_options_set(GPIOD,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_14|GPIO_PIN_15);

    gpio_af_set(GPIOE,GPIO_AF_12,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);
    gpio_mode_set(GPIOE, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);
    gpio_output_options_set(GPIOE,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);

    gpio_af_set(GPIOF,GPIO_AF_12,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);
    gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);
    gpio_output_options_set(GPIOF,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);

    gpio_af_set(GPIOG,GPIO_AF_12,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_8|GPIO_PIN_15);
    gpio_mode_set(GPIOG, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_8|GPIO_PIN_15);
    gpio_output_options_set(GPIOG,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_8|GPIO_PIN_15);
}

static void SDRAMInit_W9825G6KH()
{
    uint32_t timeout = SDRAM_TIMEOUT;
    uint32_t command_content = 0;
    exmc_sdram_parameter_struct SDRAM_Init_Struct;
    exmc_sdram_timing_parameter_struct SDRAM_Timing_Init_Struct;
    exmc_sdram_command_parameter_struct SDRAM_Command_Init_Struct;
    /* EXMC SDRAM 设备初始化序列 --------------------------------*/
    /* 第 1 步：配置 SDRAM 时序寄存器 --------------------------------*/
    /* LMRD：2 个时钟周期 */
    SDRAM_Timing_Init_Struct.load_mode_register_delay = 2;
    /* XSRD: min = 72ns */
    SDRAM_Timing_Init_Struct.exit_selfrefresh_delay = 9;
    /* RASD: min=42ns , max=100k (ns) */
    SDRAM_Timing_Init_Struct.row_address_select_delay = 5;
    /* ARFD: min=60ns *///Trc
    SDRAM_Timing_Init_Struct.auto_refresh_delay = 8;
    /* WRD: 2tck */
    SDRAM_Timing_Init_Struct.write_recovery_delay = 3;
    /* RPD:  min=15ns */
    SDRAM_Timing_Init_Struct.row_precharge_delay = 3;
    /* RCD:  min=15ns */
    SDRAM_Timing_Init_Struct.row_to_column_delay = 3;

    /* 第 2 步：配置 SDRAM 控制寄存器 ---------------------------------*/
    //bank0
    SDRAM_Init_Struct.sdram_device = EXMC_SDRAM_DEVICE0;
    //CAW:9
    SDRAM_Init_Struct.column_address_width = EXMC_SDRAM_COW_ADDRESS_9;
    //RAW:13
    SDRAM_Init_Struct.row_address_width = EXMC_SDRAM_ROW_ADDRESS_13;
    //SDW:16bit
    SDRAM_Init_Struct.data_width = EXMC_SDRAM_DATABUS_WIDTH_16B;
    //4bank
    SDRAM_Init_Struct.internal_bank_number = EXMC_SDRAM_4_INTER_BANK;
    //CL:3SDCLK
    SDRAM_Init_Struct.cas_latency = EXMC_CAS_LATENCY_3_SDCLK;
    //禁止写保护
    SDRAM_Init_Struct.write_protection = DISABLE;

    SDRAM_Init_Struct.sdclock_config = EXMC_SDCLK_PERIODS_2_HCLK;
    SDRAM_Init_Struct.burst_read_switch = ENABLE;
    SDRAM_Init_Struct.pipeline_read_delay = EXMC_PIPELINE_DELAY_2_HCLK;
    SDRAM_Init_Struct.timing = &SDRAM_Timing_Init_Struct;
    /* EXMC SDRAM bank 初始化 */
    exmc_sdram_init(&SDRAM_Init_Struct);

    /* step 3 : configure CKE high 命令---------------------------------------*/
    SDRAM_Command_Init_Struct.command = EXMC_SDRAM_CLOCK_ENABLE;
    SDRAM_Command_Init_Struct.bank_select = EXMC_SDRAM_DEVICE0_SELECT;
    SDRAM_Command_Init_Struct.auto_refresh_number = EXMC_SDRAM_AUTO_REFLESH_2_SDCLK;
    SDRAM_Command_Init_Struct.mode_register_content = 0;
    /* 等待 SDRAM 控制器准备就绪 */
    while ((exmc_flag_get(EXMC_SDRAM_DEVICE0, EXMC_SDRAM_FLAG_NREADY) != RESET) && (timeout > 0)) {
        timeout--;
    }
    /* 发送命令 */
    exmc_sdram_command_config(&SDRAM_Command_Init_Struct);

    /* step 4 : insert 10ms delay----------------------------------------------*/
    delay_1ms(10);

    /* step 5 : configure precharge all command----------------------------------*/
    SDRAM_Command_Init_Struct.command = EXMC_SDRAM_PRECHARGE_ALL;
    SDRAM_Command_Init_Struct.bank_select = EXMC_SDRAM_DEVICE0_SELECT;
    SDRAM_Command_Init_Struct.auto_refresh_number = EXMC_SDRAM_AUTO_REFLESH_2_SDCLK;
    SDRAM_Command_Init_Struct.mode_register_content = 0;
    /* wait until the SDRAM controller is ready */
    timeout = SDRAM_TIMEOUT;
    while ((exmc_flag_get(EXMC_SDRAM_DEVICE0, EXMC_SDRAM_FLAG_NREADY) != RESET) && (timeout > 0)) {
        timeout--;
    }
    /* send the command */
    exmc_sdram_command_config(&SDRAM_Command_Init_Struct);

    /* step 6 : configure Auto-Refresh command-----------------------------------*/
    SDRAM_Command_Init_Struct.command = EXMC_SDRAM_AUTO_REFRESH;
    SDRAM_Command_Init_Struct.bank_select = EXMC_SDRAM_DEVICE0_SELECT;
    SDRAM_Command_Init_Struct.auto_refresh_number = EXMC_SDRAM_AUTO_REFLESH_9_SDCLK;
    SDRAM_Command_Init_Struct.mode_register_content = 0;
    /* wait until the SDRAM controller is ready */
    timeout = SDRAM_TIMEOUT;
    while ((exmc_flag_get(EXMC_SDRAM_DEVICE0, EXMC_SDRAM_FLAG_NREADY) != RESET) && (timeout > 0)) {
        timeout--;
    }
    /* send the command */
    exmc_sdram_command_config(&SDRAM_Command_Init_Struct);

    /* step 7 : configure load mode register command-----------------------------*/
    /* program mode register */
    command_content = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1 | SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL |
                      SDRAM_MODEREG_CAS_LATENCY_3 | SDRAM_MODEREG_OPERATING_MODE_STANDARD |
                      SDRAM_MODEREG_WRITEBURST_MODE_SINGLE ;

    SDRAM_Command_Init_Struct.command = EXMC_SDRAM_LOAD_MODE_REGISTER;
    SDRAM_Command_Init_Struct.bank_select = EXMC_SDRAM_DEVICE0_SELECT;
    SDRAM_Command_Init_Struct.auto_refresh_number = EXMC_SDRAM_AUTO_REFLESH_2_SDCLK;
    SDRAM_Command_Init_Struct.mode_register_content = command_content;

    /* wait until the SDRAM controller is ready */
    timeout = SDRAM_TIMEOUT;
    while ((exmc_flag_get(EXMC_SDRAM_DEVICE0, EXMC_SDRAM_FLAG_NREADY) != RESET) && (timeout > 0)) {
        timeout--;
    }
    /* send the command */
    exmc_sdram_command_config(&SDRAM_Command_Init_Struct);

    /* step 8 : 设置自动刷新率计数器--------------------------------*/
    /* 64ms, 8192-cycle refresh, 64ms/8192=7.81us */
    /* SDCLK_Freq = SYS_Freq/2 */
    /* (7.81 us * SDCLK_Freq) - 20 */
    exmc_sdram_refresh_count_set(900);

    /* wait until the SDRAM controller is ready */
    timeout = SDRAM_TIMEOUT;
    while ((exmc_flag_get(EXMC_SDRAM_DEVICE0, EXMC_SDRAM_FLAG_NREADY) != RESET) && (timeout > 0)) {
        timeout--;
    }
}

void SDRamInit()
{
    rcu_periph_clock_enable(RCU_EXMC);
    SDRamGPIOInit();
    SDRAMInit_W9825G6KH();
}

/*!
    \brief      fill the buffer with specified value
    \param[in]  pbuffer: pointer on the buffer to fill
    \param[in]  buffersize: size of the buffer to fill
    \param[in]  value: value to fill on the buffer
    \param[out] none
    \retval     none
*/
void fill_buffer(uint8_t *pbuffer, uint16_t buffer_lengh, uint16_t offset)
{
    uint16_t index = 0;

    /* fill the buffer with specified values */
    for (index = 0; index < buffer_lengh; index++) {
        pbuffer[index] = index + offset;
    }
}

/*!
    \brief      write a byte buffer(data is 8 bits) to the EXMC SDRAM memory
    \param[in]  sdram_device: specify which a SDRAM memory block is written
    \param[in]  pbuffer: pointer to buffer
    \param[in]  writeaddr: SDRAM memory internal address from which the data will be written
    \param[in]  numbytetowrite: number of bytes to write
    \param[out] none
    \retval     none
*/
void sdram_writebuffer_8(uint32_t sdram_device, uint8_t *pbuffer, uint32_t writeaddr, uint32_t numbytetowrite)
{
    uint32_t temp_addr;

    /* select the base address according to EXMC_Bank */
    if (sdram_device == EXMC_SDRAM_DEVICE0) {
        temp_addr = SDRAM_DEVICE0_ADDR;
    } else {
        temp_addr = SDRAM_DEVICE1_ADDR;
    }

    /* while there is data to write */
    for (; numbytetowrite != 0; numbytetowrite--) {
        /* transfer data to the memory */
        *(uint8_t *)(temp_addr + writeaddr) = *pbuffer++;

        /* increment the address */
        writeaddr += 1;
    }
}

/*!
    \brief      read a block of 8-bit data from the EXMC SDRAM memory
    \param[in]  sdram_device: specify which a SDRAM memory block is written
    \param[in]  pbuffer: pointer to buffer
    \param[in]  readaddr: SDRAM memory internal address to read from
    \param[in]  numbytetoread: number of bytes to read
    \param[out] none
    \retval     none
*/
void sdram_readbuffer_8(uint32_t sdram_device, uint8_t *pbuffer, uint32_t readaddr, uint32_t numbytetoread)
{
    uint32_t temp_addr;

    /* select the base address according to EXMC_Bank */
    if (sdram_device == EXMC_SDRAM_DEVICE0) {
        temp_addr = SDRAM_DEVICE0_ADDR;
    } else {
        temp_addr = SDRAM_DEVICE1_ADDR;
    }

    /* while there is data to read */
    for (; numbytetoread != 0; numbytetoread--) {
        /* read a byte from the memory */
        *pbuffer++ = *(uint8_t *)(temp_addr + readaddr);

        /* increment the address */
        readaddr += 1;
    }
}

