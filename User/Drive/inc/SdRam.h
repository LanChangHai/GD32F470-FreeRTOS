//
// Created by 7invensun on 15/12/2023.
//

#ifndef GD32F470_FREERTOS_SDRAM_H
#define GD32F470_FREERTOS_SDRAM_H

#include "gd32f4xx_exmc.h"
#include "systick.h"

/* Define mode register content */
/* Burst Length */
#define SDRAM_MODEREG_BURST_LENGTH_1 ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2 ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4 ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8 ((uint16_t)0x0003)

/* Burst Type */
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED ((uint16_t)0x0008)

/* CAS Latency */
#define SDRAM_MODEREG_CAS_LATENCY_2 ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3 ((uint16_t)0x0030)

/* Write Mode */
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE ((uint16_t)0x0200)

#define SDRAM_MODEREG_OPERATING_MODE_STANDARD ((uint16_t)0x0000)

#define SDRAM_TIMEOUT ((uint32_t)0x0000FFFF)

#define SDRAM_DEVICE0_ADDR                         ((uint32_t)0xC0000000)
#define SDRAM_DEVICE1_ADDR                         ((uint32_t)0xD0000000)



void SDRamInit();
void fill_buffer(uint8_t *pbuffer, uint16_t buffer_lengh, uint16_t offset);
void sdram_writebuffer_8(uint32_t sdram_device, uint8_t *pbuffer, uint32_t writeaddr, uint32_t numbytetowrite);
void sdram_readbuffer_8(uint32_t sdram_device, uint8_t *pbuffer, uint32_t readaddr, uint32_t numbytetoread);

#endif  // GD32F470_FREERTOS_SDRAM_H
