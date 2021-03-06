/*!
 * \file      Commissioning.h
 *
 * \brief     End device commissioning parameters
 *
 * \copyright Revised BSD License, see section \ref LICENSE.
 *
 * \code
 *                ______                              _
 *               / _____)             _              | |
 *              ( (____  _____ ____ _| |_ _____  ____| |__
 *               \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 *               _____) ) ____| | | || |_| ____( (___| | | |
 *              (______/|_____)_|_|_| \__)_____)\____)_| |_|
 *              (C)2013-2017 Semtech
 *
 * \endcode
 *
 * \author    Miguel Luis ( Semtech )
 *
 * \author    Gregory Cristian ( Semtech )
*/
 /******************************************************************************
  * @file    commissioning.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    10-July-2018
  * @brief   End device commissioning parameters
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LORA_COMMISSIONING_H__
#define __LORA_COMMISSIONING_H__
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
/*!
 ******************************************************************************
 ********************************** WARNING ***********************************
 ******************************************************************************
  The crypto-element implementation supports both 1.0.x and 1.1.x LoRaWAN 
  versions of the specification.
  Thus it has been decided to use the 1.1.x keys and EUI name definitions.
  The below table shows the names equivalence between versions:
               +-------------------+-------------------------+
               |       1.0.x       |          1.1.x          |
               +===================+=========================+
               | LORAWAN_DEVICE_EUI| LORAWAN_DEVICE_EUI      |
               +-------------------+-------------------------+
               | LORAWAN_APP_EUI   | LORAWAN_JOIN_EUI        |
               +-------------------+-------------------------+
               | N/A               | LORAWAN_APP_KEY         |
               +-------------------+-------------------------+
               | LORAWAN_APP_KEY   | LORAWAN_NWK_KEY         |
               +-------------------+-------------------------+
               | LORAWAN_NWK_S_KEY | LORAWAN_F_NWK_S_INT_KEY |
               +-------------------+-------------------------+
               | LORAWAN_NWK_S_KEY | LORAWAN_S_NWK_S_INT_KEY |
               +-------------------+-------------------------+
               | LORAWAN_NWK_S_KEY | LORAWAN_NWK_S_ENC_KEY   |
               +-------------------+-------------------------+
               | LORAWAN_APP_S_KEY | LORAWAN_APP_S_KEY       |
               +-------------------+-------------------------+
 ******************************************************************************
 ******************************************************************************
 ******************************************************************************
 */
/*!
 * When set to 1 the application uses the Over-the-Air activation procedure
 * When set to 0 the application uses the Personalization activation procedure
 */
#define OVER_THE_AIR_ACTIVATION                     0
/*!
 * Indicates if the end-device is to be connected to a private or public network
 */
#define LORAWAN_PUBLIC_NETWORK                      true
      
/*!
 * When set to 1 DevEui is LORAWAN_DEVICE_EUI
 * When set to 0 DevEui is automatically generated by calling
 *         BoardGetUniqueId function
 */
#define STATIC_DEVICE_EUI                     1
   
/*!
 * IEEE Organizationally Unique Identifier ( OUI ) (big endian)
 * \remark This is unique to a company or organization
 */
#define IEEE_OUI                                           0x01, 0x01, 0x01   
/*!
 * Mote device IEEE EUI (big endian)
 *
 * \remark see STATIC_DEVICE_EUI comments
 */

#if defined (ICSPACE16)

#define LORAWAN_DEVICE_EUI                                  { 0x00, 0x26, 0x50, 0x98, 0x31, 0xE3, 0x15, 0xBC }

#elif defined (ICSPACE17)

#define LORAWAN_DEVICE_EUI                                  { 0x00, 0x48, 0x9C, 0x11, 0xF0, 0x99, 0x24, 0x6E }

#elif defined (ICSPACE18)

#define LORAWAN_DEVICE_EUI                                  { 0x00, 0x16, 0x5C, 0xD6, 0xA3, 0x85, 0xFC, 0x63 }

#elif defined (ICSPACE19)

#define LORAWAN_DEVICE_EUI                                  { 0x00, 0x50, 0xA9, 0x6A, 0xFE, 0xA9, 0x93, 0x74 }

#elif defined (ICSPACE20)

#define LORAWAN_DEVICE_EUI                                  { 0x00, 0x87, 0xFA, 0x6D, 0xB8, 0xEA, 0xAF, 0x57 }

#elif defined ICSPACE21

#define LORAWAN_DEVICE_EUI                                  { 0x00, 0xAB, 0xDF, 0x8A, 0x62, 0xF5, 0xC1, 0x81 }

#endif

/*!
 * App/Join server IEEE EUI (big endian)
 */

#define LORAWAN_JOIN_EUI                                   { 0x70, 0xB3, 0xD5, 0x7E, 0xD0, 0x02, 0x82, 0x4D }   // not changed usually


/*!
 * Application root key
 * WARNING: NOT USED FOR 1.0.x DEVICES
 */

#if defined (ICSPACE16)

#define LORAWAN_APP_KEY                                    { 0x4E, 0x5B, 0x37, 0xE1, 0x12, 0x23, 0xAC, 0x61, 0x8E, 0x0C, 0x3F, 0x95, 0x02, 0x0E, 0x8E, 0x92 }

#elif defined(ICSPACE17)

#define LORAWAN_APP_KEY                                    { 0xC0, 0x08, 0xD3, 0x1E, 0x02, 0x85, 0x0C, 0xFC, 0x47, 0x97, 0x83, 0x3A, 0xCB, 0xC3, 0x74, 0x8F }

#elif defined(ICSPACE18)

#define LORAWAN_APP_KEY                                    { 0x03, 0xBC, 0x8C, 0x09, 0x9F, 0xA2, 0x4F, 0x02, 0x93, 0x80, 0xB0, 0x6B, 0xF6, 0x39, 0x00, 0xDC }

#elif defined(ICSPACE19)

#define LORAWAN_APP_KEY                                    { 0x6A, 0x86, 0x33, 0xF2, 0xDD, 0x3B, 0x92, 0xCA, 0x60, 0xFB, 0x4F, 0xBE, 0x51, 0x21, 0xCB, 0x7A }

#elif defined(ICSPACE20)

#define LORAWAN_APP_KEY                                    { 0xC5, 0x9A, 0x51, 0x08, 0x66, 0x26, 0x85, 0x6B, 0x4C, 0x0D, 0x68, 0x4B, 0xF7, 0x81, 0x9A, 0x58 }

#elif defined(ICSPACE21)

#define LORAWAN_APP_KEY                                    { 0x70, 0xB3, 0xD5, 0x7E, 0xD0, 0x02, 0x82, 0x4D }


#endif

/*!
 * Network root key
 * WARNING: FOR 1.0.x DEVICES IT IS THE \ref LORAWAN_APP_KEY
 */
#define LORAWAN_NWK_KEY                                     LORAWAN_APP_KEY

#if( OVER_THE_AIR_ACTIVATION == 0 )
/*!
 * Current network ID
 */
#define LORAWAN_NETWORK_ID                                 ( uint32_t )0
/*!
 * When set to 1 DevAdd is LORAWAN_DEVICE_ADDRESS
 * When set to 0 DevAdd is automatically generated using
 *         a pseudo random generator seeded with a value derived from
 *         BoardUniqueId value
 */
#define STATIC_DEVICE_ADDRESS                     1
/*!
 * Device address on the network (big endian)
 *
 * \remark see STATIC_DEVICE_ADDRESS comments
 */
#define LORAWAN_DEVICE_ADDRESS                      ( uint32_t )0x26013D75
/*!
 * Forwarding Network session integrity key
 * WARNING: NWK_S_KEY FOR 1.0.x DEVICES
 */
#define LORAWAN_F_NWK_S_INT_KEY                            { 0xB5, 0x21, 0xC6, 0x23, 0xA8, 0x94, 0x80, 0x90, 0xAD, 0xC7, 0x19, 0x6F, 0x4B, 0x31, 0x4B, 0x3A }
/*!
 * Serving Network session integrity key
 * WARNING: NOT USED FOR 1.0.x DEVICES. MUST BE THE SAME AS \ref LORAWAN_F_NWK_S_INT_KEY
 */
#define LORAWAN_S_NWK_S_INT_KEY                            LORAWAN_F_NWK_S_INT_KEY
/*!
 * Network session encryption key
 * WARNING: NOT USED FOR 1.0.x DEVICES. MUST BE THE SAME AS \ref LORAWAN_F_NWK_S_INT_KEY
 */
#define LORAWAN_NWK_S_ENC_KEY                              LORAWAN_F_NWK_S_INT_KEY
/*!
 * Application session key
 */
#define LORAWAN_APP_S_KEY                                  { 0xCE, 0x27, 0xD7, 0xC6, 0x98, 0xE1, 0x8C, 0xE2, 0x4F, 0xAA, 0xB4, 0x62, 0xFF, 0xD4, 0xAF, 0x94 }
#endif /* OVER_THE_AIR_ACTIVATION == 0 */
#ifdef __cplusplus
}
#endif
#endif /* __LORA_COMMISSIONING_H__ */

