///*
// * GEOFENCE.c
// *
// * Created: 5.11.2016 22:04:58
// *  Author: Tomy2
// * Modified by Medad Newman 27/12/19
// */ 

// 
#include "geofence.h"
#include <stdio.h>




/*
 * dummy function to force the compiler to compile all the polygons
 * to see their memory footprint. MUST NEVER BE CALLED!
 */
void doit(void){
	EU863870_1F[1] = 1;
	EU863870_2F[1] = 1;
	EU863870_3F[1] = 1;
	EU863870_4F[1] = 1;
	EU863870_5F[1] = 1;

	
	AU915928_1F[1] =1;
	AU915928_2F[1] = 1;
	AU915928_3F[1] = 1;

	US902928_1F[1] = 1;
	US902928_2F[1] = 1;

	KR920923_1F[1] = 1;
	IN865867_1F[1] = 1;
	
	AS920923_2F[1] = 1;
	AS920923_1F[1] = 1;

	CN470510_1F[1] = 1;
	
	AS923925_4F[1] = 1;
	AS923925_3F[1] = 1;
	AS923925_2F[1] = 1;
	AS923925_1F[1] = 1;

}



// Strategy: check if GPS coordinate is in any of the polygons. If so, look up what transmit frequency it uses.

/*
	Adapted version of pointInPolygon() function from:	http://alienryderflex.com/polygon/
	
	Returns '0' if the point is outside of the polygon and '1' if it's inside.
	
	Expects input DEGREES * 100000 for latitude and longitude. Eg 4961070 for 49.61070 N.
	The reason is to make sure all calculations fit inside int32_t.
	
	However, this function is not very accurate due to rounding within the computation.
*/
int32_t pointInPolygon(int32_t polyCorners, int32_t * polygon, int32_t latitude, int32_t longitude)
{
	int32_t i;
	int32_t j = polyCorners * 2 - 2;
	int32_t oddNodes = 0;

	for(i = 0; i < polyCorners * 2; i += 2)
	{
		if((polygon[i + 1] < latitude && polygon[j + 1] >= latitude
			|| polygon[j + 1] < latitude && polygon[i + 1] >= latitude)
			&& (polygon[i] <= longitude || polygon[j] <= longitude))
		{
			oddNodes ^= (polygon[i] + (latitude - polygon[i + 1])
			/ (polygon[j + 1] - polygon[i + 1]) * (polygon[j] - polygon[i]) < longitude);
		}

		j = i;
	}

	return oddNodes;
}


/*
	Adapted version of pointInPolygon() function from:	http://alienryderflex.com/polygon/
	
	Returns '0' if the point is outside of the polygon and '1' if it's inside.
	
	Uses FLOAT input for better accuracy.
*/
int32_t pointInPolygonF(int32_t polyCorners, float * polygon, float latitude, float longitude)
{
	int32_t i;
	int32_t j = polyCorners * 2 - 2;
	int32_t oddNodes = 0;

	for(i = 0; i < polyCorners * 2; i += 2)
	{
		if((polygon[i + 1] < latitude && polygon[j + 1] >= latitude
		|| polygon[j + 1] < latitude && polygon[i + 1] >= latitude)
		&& (polygon[i] <= longitude || polygon[j] <= longitude))
		{
			oddNodes ^= (polygon[i] + (latitude - polygon[i + 1])
			/ (polygon[j + 1] - polygon[i + 1]) * (polygon[j] - polygon[i]) < longitude);
		}

		j = i;
	}

	return oddNodes;
}



///*
//	Changes GEOFENCE_LoRA_frequency and GEOFENCE_no_tx global variables based on the input coordinates.
//	TODO: documentation must be updated for LoRa frequencies
//	FREQUENCIES:
//						EU863870    = 0x01,
//						AU915928    = 0x02,
//						US902928    = 0x03,
//						KR920923    = 0x04,
//						IN865867    = 0x05,
//						AS920923		= 0x06,
//						CN470510		= 0x07,
//						AS923925		= 0x08,
//	Expected input FLOAT for latitude and longitude as in GPS_UBX_latitude_Float and GPS_UBX_longitude_Float.
//*/
void GEOFENCE_position(float latitude, float longitude)
{


	if     (pointInPolygonF(sizeof(EU863870_1F)/2, EU863870_1F, latitude, longitude) == 1)  {GEOFENCE_no_tx = 0; GEOFENCE_LoRa_frequency = EU863870;}
	else if(pointInPolygonF(sizeof(EU863870_2F)/2, EU863870_2F, latitude, longitude) == 1)  {GEOFENCE_no_tx = 0; GEOFENCE_LoRa_frequency = EU863870;}
	else if(pointInPolygonF(sizeof(EU863870_3F)/2, EU863870_3F, latitude, longitude) == 1)	{GEOFENCE_no_tx = 0; GEOFENCE_LoRa_frequency = EU863870;}
	else if(pointInPolygonF(sizeof(EU863870_4F)/2, EU863870_4F, latitude, longitude) == 1)	{GEOFENCE_no_tx = 0; GEOFENCE_LoRa_frequency = EU863870;}
	

	else if(pointInPolygonF((int32_t)sizeof(US902928_1F)/2, US902928_1F, latitude, longitude) == 1)	{GEOFENCE_no_tx = 0; GEOFENCE_LoRa_frequency = US902928;}
	else if(pointInPolygonF((int32_t)sizeof(US902928_2F)/2, US902928_2F, latitude, longitude) == 1)	{GEOFENCE_no_tx = 0; GEOFENCE_LoRa_frequency = US902928;}

  //else if(pointInPolygonF(sizeof(IN865867_1F)/2, IN865867_1F, latitude, longitude) == 1)	{GEOFENCE_no_tx = 0; GEOFENCE_LoRa_frequency = IN865867;}

	
	else if(pointInPolygonF(sizeof(KR920923_1F)/2, KR920923_1F, latitude, longitude) == 1)	{GEOFENCE_no_tx = 0; GEOFENCE_LoRa_frequency = KR920923;}
	
  else if(pointInPolygonF((int32_t)sizeof(AU915928_1F)/2, AU915928_1F, latitude, longitude) == 1)	{GEOFENCE_no_tx = 0; GEOFENCE_LoRa_frequency = AU915928;}
	
	// there is something wrong with the AU915928_2F polygons. it was detecting a point in INDIA
  else if(pointInPolygonF((int32_t)sizeof(AU915928_2F)/2, AU915928_2F, latitude, longitude) == 1)	{GEOFENCE_no_tx = 0; GEOFENCE_LoRa_frequency = AU915928;}
	
  else if(pointInPolygonF((int32_t)sizeof(AU915928_3F)/2, AU915928_3F, latitude, longitude) == 1)	{GEOFENCE_no_tx = 0; GEOFENCE_LoRa_frequency = AU915928;}
	
	

	else if(pointInPolygonF(sizeof(AS920923_1F)/2, AS920923_1F, latitude, longitude) == 1)	{GEOFENCE_no_tx = 0; GEOFENCE_LoRa_frequency = AS920923;}
	else if(pointInPolygonF(sizeof(AS920923_2F)/2, AS920923_2F, latitude, longitude) == 1)	{GEOFENCE_no_tx = 0; GEOFENCE_LoRa_frequency = AS920923;}
	
	


  else if(pointInPolygonF(sizeof(CN470510_1F)/2, CN470510_1F, latitude, longitude) == 1)	{GEOFENCE_no_tx = 0; GEOFENCE_LoRa_frequency = CN470510;}
	

  else if(pointInPolygonF(sizeof(AS923925_1F)/2, AS923925_1F, latitude, longitude) == 1)	{GEOFENCE_no_tx = 0; GEOFENCE_LoRa_frequency = AS923925;}
  else if(pointInPolygonF(sizeof(AS923925_2F)/2, AS923925_2F, latitude, longitude) == 1)	{GEOFENCE_no_tx = 0; GEOFENCE_LoRa_frequency = AS923925;}
  else if(pointInPolygonF(sizeof(AS923925_3F)/2, AS923925_3F, latitude, longitude) == 1)	{GEOFENCE_no_tx = 0; GEOFENCE_LoRa_frequency = AS923925;}
  else if(pointInPolygonF(sizeof(AS923925_4F)/2, AS923925_4F, latitude, longitude) == 1)	{GEOFENCE_no_tx = 0; GEOFENCE_LoRa_frequency = AS923925;}

	
	// Over the sea or areas where there is no frequency declared, transmit on EU frequencies!!

	else {GEOFENCE_no_tx = 0; GEOFENCE_LoRa_frequency = EU863870;}
}
	
	


