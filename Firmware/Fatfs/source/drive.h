//
// Created by 7invensun on 2023/12/27.
//

#ifndef GD32F470_FREERTOS_DRIVE_H
#define GD32F470_FREERTOS_DRIVE_H

#include "sdcard.h"
#include "gd32f4xx.h"
#include <stdio.h>

void nvic_config(void);
sd_error_enum sd_io_init(void);
void card_info_get(void);

#endif  // GD32F470_FREERTOS_DRIVE_H
