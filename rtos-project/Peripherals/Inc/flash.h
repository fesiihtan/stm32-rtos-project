/*
 * @outhor    : Fesih TAN
 * @date      : May 26, 2026 
 * @brief     : Provides function prototypes for configuring the internal flash memory of the MCU.
 * 
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#include "mcu.h"

/**
 * @brief  Configures the flash memory wait states based on the provided HCLK frequency.
 * @param  hclk: The frequency of the HCLK in Hz.
 */
void flash_config_wait_states(uint8_t hclk);



#endif /* INC_FLASH_H_ */
