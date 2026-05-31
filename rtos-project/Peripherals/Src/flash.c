/*
 * flash.c
 * @author    : Fesih TAN
 * @date      : May 26, 2026
 * @brief     : Provides function implementations for configuring the internal flash memory of the MCU.
 */

#include "flash.h"


void flash_config_wait_states(uint8_t hclk)
{
    // Reset the Flash Access Control Register to the default value after reset
    FLASH->ACR &= ~(FLASH_ACR_LATENCY | FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN
                    | FLASH_ACR_ICRST | FLASH_ACR_DCRST);

    FLASH->ACR |= (FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN); // Enable prefetch, instruction cache and data cache

    // Calculate the number of wait states based on the HCLK frequency
    uint32_t latency = (hclk - 1) / 30; // Round up to the nearest integer (30 MHz per wait state)

    // Set the FLASH_ACR_LATENCY based on the latency calculated
    FLASH->ACR |= (latency << FLASH_ACR_LATENCY_Pos);

}



