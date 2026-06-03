/*
 * error.h
 * @author    : Fesih TAN
 * @date      : June 1, 2026
 * @brief     : Contains the type definitions and function prototypes for error handling in the RTOS project.
 */

#ifndef INC_ERROR_H_
#define INC_ERROR_H_

/**
 * Return type to be used for functions that require an error status returned.
 */
typedef int error_t;

/**
 *  Enum of error constants
 */
typedef enum
{
  ERR_OK = 0,
  ERR_FAIL = -1,
  ERR_TIMEOUT = -2,
  ERR_INVALID_PARAM = -3
}error_e;


#endif /* INC_ERROR_H_ */
