/**
  ******************************************************************************
  * @file    bsp.c
  * @author  MCD Application Team
  * @brief   manages the sensors on the application
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdlib.h>
#include "hw.h"
#include "timeServer.h"
#include "bsp.h"
#include "ms5607.h"
#include "ublox.h"
#include "main.h"




// Battery levels
uint16_t battery_level16 = 0;

// Battery/Solar voltage
uint32_t VCC_ADC = 0;



/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BATTERY_ADC_CHANNEL             ADC_CHANNEL_5
/*!
 * Generic definition
 */
#ifndef SUCCESS
#define SUCCESS                                     1
#endif

#ifndef FAIL
#define FAIL                                        0
#endif

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


void BSP_sensor_Read( sensor_t *sensor_data)
{
	TVL1(PRINTF("READING SENSOR AND GPS\n\r");)

  /* USER CODE BEGIN 5 */
	#if SENSOR_ENABLED
	MS5607_get_temp_pressure();
	#endif
  
	#if GPS_ENABLED
	get_location_fix(GPS_LOCATION_FIX_TIMEOUT);
	#endif
	
	battery_level16 = (uint16_t) BSP_GetBatteryLevel16();

	
	PRINTF("================================================================\r\n");
	PRINTF("SENSOR AND GPS VALUES");
	PRINTF("\r\n"); 
	PRINTF("================================================================\r\n");

	PRINTF("Temperature degrees C: "); 
	PRINTF("%lf", TEMPERATURE_Value); 
	PRINTF("\r\n"); 
	PRINTF("Pressure mBar: "); 
	PRINTF("%lf", PRESSURE_Value); 
	PRINTF("\r\n");
	PRINTF("Longitude: "); 
	PRINTF("%lf ", GPS_UBX_longitude_Float); 
	PRINTF("Latitude: "); 
	PRINTF("%lf ", GPS_UBX_latitude_Float); 
	PRINTF("altitude: "); 
	PRINTF("%ld", GPSaltitude	); 
	PRINTF("\r\n");
	PRINTF("Solar voltage: "); 
	PRINTF("%ld", battery_level16	); 
	PRINTF("\r\n");
	PRINTF("================================================================\r\n");


	
	
  sensor_data->humidity    = 34; // hard coded dummy value
  sensor_data->temperature = TEMPERATURE_Value;
  sensor_data->pressure    = PRESSURE_Value;
	sensor_data->altitudeGps = GPSaltitude;
	sensor_data->latitude    = GPS_UBX_latitude_Float;
	sensor_data->longitude   = GPS_UBX_longitude_Float;
	sensor_data->battery_level16 = battery_level16;

  /* USER CODE END 5 */
}

void  BSP_sensor_Init( void  )
{
	PRINTF("SELFTEST: Initialisng ms5607\n\r");
	#if SENSOR_ENABLED
  /* Initialize sensors */	
		ms5607_Init();
	#endif
	
	 #if GPS_ENABLED
	 PRINTF("SELFTEST: Initialising GPS\n\r");

	 //GPS SETUP
	 setup_GPS();
	#endif

}


/**
  * @brief It measures the battery voltage by returning the value in mV
  * @param none
  * @retval uint16_t The battery voltage value in mV
  */
uint16_t BSP_GetBatteryLevel16( void )
{

  uint16_t batteryLevel = 0;
  uint16_t measuredLevel = 0;
  uint16_t nVrefIntLevel = 0;
  float batteryVoltage = 0;
  float nVddValue = 0;
  

  measuredLevel = HW_AdcReadChannel( BATTERY_ADC_CHANNEL ); 
  nVrefIntLevel = HW_AdcReadChannel( ADC_CHANNEL_VREFINT ); 
	
	
  nVddValue = (( (uint32_t) VDDA_VREFINT_CAL * (*VREFINT_CAL ) )/ nVrefIntLevel);
  
  batteryVoltage =  ((( (float)(measuredLevel) * nVddValue/*3300*/) / 4096) * RESITOR_DIVIDER);
  
  batteryLevel = (uint16_t)(batteryVoltage / 1.0);
  
  return batteryLevel;
}

/** @brief Write in STM32 internal EEPROM 
  * @param dest_addr EEPROM address (range 0x08080000 - 0x080817FF)
  * @param data uint32_t data
  * @retval none
  */
void WriteInternalEepromBuffer(uint32_t dest_addr, uint32_t data)
{
  HAL_FLASH_Unlock();
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR );
  

  HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, dest_addr, data);
  
  HAL_FLASH_Lock();
}

/**
  * @brief Check Frame Counter value saved in EEPROM
  * @param none
  * @retval BC_ChargeStatusTypeDef Battery charging status
  */
uint8_t EepromFrameCounterValidation(void)
{
  uint8_t retval = 0;
  /* DevEui validation */
  if((*(uint64_t*)FRAME_COUNTER_EEPROM_ADDRESS) == 0)
  {
    retval |= FRAME_COUNTER_EEPROM_ID;
  }
  return retval;
}


/**
  * @brief  Load Frame counter from STM32 internal EEPROM
  * @param  Pointer to frame count
  * @retval None
  */
void LoadFrameCounter(uint32_t* fcnt)
{
#if SAVE_FRAME_COUNTER_IN_INTERNAL_EEPROM
  
  if(EepromFrameCounterValidation() != 0)
  {
    return;
  }
  memcpy(fcnt, (void*)FRAME_COUNTER_EEPROM_ADDRESS, FRAME_COUNTER_EEPROM_LEN);

#endif //SAVE_FRAME_COUNTER_IN_INTERNAL_EEPROM
}


uint8_t EepromMcuWriteBuffer( uint16_t addr, uint8_t *buffer, uint16_t size )
{
    uint8_t status = FAIL;

    assert_param( ( DATA_EEPROM_BASE + addr ) >= DATA_EEPROM_BASE );
    assert_param( buffer != NULL );
    assert_param( size < ( DATA_EEPROM_BANK2_END - DATA_EEPROM_BASE ) );

    if( HAL_FLASHEx_DATAEEPROM_Unlock( ) == HAL_OK )
    {
        for( uint16_t i = 0; i < size; i++ )
        {
            if( HAL_FLASHEx_DATAEEPROM_Program( FLASH_TYPEPROGRAMDATA_BYTE,
                                                ( DATA_EEPROM_BASE + addr + i ),
                                                  buffer[i] ) != HAL_OK )
            {
                // Failed to write EEPROM
                break;
            }
        }
        status = SUCCESS;
    }

    HAL_FLASHEx_DATAEEPROM_Lock( );
    return status;
}

uint8_t EepromMcuReadBuffer( uint16_t addr, uint8_t *buffer, uint16_t size )
{
    assert_param( ( DATA_EEPROM_BASE + addr ) >= DATA_EEPROM_BASE );
    assert_param( buffer != NULL );
    assert_param( size < ( DATA_EEPROM_BANK2_END - DATA_EEPROM_BASE ) );

    memcpy1( buffer, ( uint8_t* )( DATA_EEPROM_BASE + addr ), size );
    return SUCCESS;
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
