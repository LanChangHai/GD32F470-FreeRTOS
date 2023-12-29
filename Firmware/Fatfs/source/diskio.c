/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */

/* Definitions of physical drive number for each drive */
#define DEV_SDCARD		0	/* Example: Map Ramdisk to physical drive 0 */
extern sd_card_info_struct sd_cardinfo;
/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = STA_NOINIT;
	switch (pdrv) {
	    case DEV_SDCARD :
        {
            stat = RES_OK;
            break;
        }
	}
	return stat;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
    DSTATUS status = STA_NOINIT;
    sd_error_enum result;
    nvic_config();
	switch (pdrv) {
	    case DEV_SDCARD :
        {
            result = sd_io_init();
            //card_info_get();
            if(SD_OK == result)
            {
                status &= ~STA_NOINIT;
            }
            break;
        }
	}
	return status;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
    DRESULT result = RES_PARERR;
    sd_error_enum sd_error;
	switch (pdrv) {
        case DEV_SDCARD :{
            if ((DWORD)buff&3) {
                result = RES_OK;
                DWORD scratch[512 / 4];
                while (count--) {
                    sd_error = sd_block_read(scratch, sector*BLOCKSIZE, BLOCKSIZE);
                    if (sd_error != SD_OK) {
                        result = RES_ERROR;
                        break;
                    }
                    memcpy(buff, scratch, 512);
                    sector++;
                    buff += 512;
                }
            }else
            {
                sd_error = sd_multiblocks_read((uint32_t *)buff, sector*BLOCKSIZE, BLOCKSIZE,(uint32_t)count);
                if(sd_error != SD_OK)
                {
                    result = RES_ERROR;
                }
                else
                {
                    result = RES_OK;
                }
            }
            break;
        }
	}
	return result;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
    DRESULT result = RES_PARERR;
    sd_error_enum sd_error;
	switch (pdrv) {
        case DEV_SDCARD:
        {
            if ((DWORD)buff&3) {
                result = RES_OK;
                DWORD scratch[512 / 4];
                while (count--) {
                    memcpy(scratch,buff,512);
                    sd_error = sd_block_write(scratch,sector*BLOCKSIZE,BLOCKSIZE);
                    if (sd_error != SD_OK) {
                        result = RES_ERROR;
                        break;
                    }
                    sector++;
                    buff += 512;
                }
            }else
            {
                sd_error = sd_multiblocks_write((uint32_t *)buff, sector*BLOCKSIZE, BLOCKSIZE,(uint32_t)count);
                if(sd_error != SD_OK)
                {
                    result = RES_ERROR;
                }
                else
                {
                    result = RES_OK;
                }
            }
            break;
        }
	}
	return result;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
    uint32_t capacity;
    DRESULT result = RES_PARERR;
    switch (pdrv) {
        case DEV_SDCARD: {
            switch (cmd) {
                case GET_SECTOR_SIZE:
                    *(WORD *)buff = BLOCKSIZE;
                    break;
                case GET_BLOCK_SIZE:
                    *(DWORD *)buff = sd_cardinfo.card_blocksize;
                    break;
                case GET_SECTOR_COUNT:
                    capacity = sd_card_capacity_get();
                    *(DWORD *)buff = capacity * 1024 / sd_cardinfo.card_blocksize;
                    break;
                case CTRL_SYNC:
                    break;
            }
            result = RES_OK;
            break;
        }
        default:break;
    }
    return result;
}
