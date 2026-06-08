/*
 * iwdg.h
 *
 *  Created on: Jun 7, 2026
 *      Author: Fesih TAN
 *      @brief: Provides the interface for the Independent Watchdog (IWDG) peripheral
 */

#ifndef INC_IWDG_H_
#define INC_IWDG_H_

#include "mcu.h"

/**
 * Independet Watchdog key definitions
 */
#define IWDG_KEY_ENABLE                 (0x0000CCCCU)
#define IWDG_KEY_WR_ACCESS_ENABLE       (0x00005555U)
#define IWDG_KEY_RELOAD                 (0x0000AAAAU)

/**
 * IWDG timeout in ms - adjust as necessary
 */
#define IWDG_TIMEOUT                    ((uint16_t)4000) // 4000 ms or 4 seconds  

/**
 * Enumeration for the IWDG prescalers
 */
typedef enum
{
    IWDG_PRESCALER_4   = 0x00,
    IWDG_PRESCALER_8   = 0x01,
    IWDG_PRESCALER_16  = 0x02,
    IWDG_PRESCALER_32  = 0x03,
    IWDG_PRESCALER_64  = 0x04,
    IWDG_PRESCALER_128 = 0x05,
    IWDG_PRESCALER_256 = 0x06
} iwdg_prescaler_e;

/**
 *  Starts the IWDG
 */
static inline void iwdg_enable(void)
{
    IWDG->KR = IWDG_KEY_ENABLE;
}

/**
 * Enables write access to the IWDG registers
 */
static inline void iwdg_enable_write_access(void)
{
    IWDG->KR = IWDG_KEY_WR_ACCESS_ENABLE;
}

/**
 * Resets the IWDG with the value previously set in the reload register
 */
static inline void iwdg_reset(void)
{
    IWDG->KR = IWDG_KEY_RELOAD;
}

/**
 * Initializes the Independent Watchdog for 4 second timeouts
 */
void iwdg_init(void);

#endif /* INC_IWDG_H_ */
