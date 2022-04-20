/*
 * Copyright (C) 2016 iot-lab
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     tests
 * @{
 *
 * @file
 * @brief       Idle application
 *
 * @author      Alexandre Abadie <alexandre.abadie@inria.fr>
 *
 * @}
 */

#ifdef MODULE_PERIPH_EEPROM
#include "periph/eeprom.h"
#endif

int main(void)
{
#ifdef MODULE_PERIPH_EEPROM
    eeprom_erase();
#endif
    return 0;
}
