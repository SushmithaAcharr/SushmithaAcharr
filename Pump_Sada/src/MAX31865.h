#ifndef _MAX31865_H
#define _MAX31865_H

/*
  Author:     Nima Askari
  WebSite:    http://www.github.com/NimaLTD
  Instagram:  http://instagram.com/github.NimaLTD
  Youtube:    https://www.youtube.com/channel/UCUhY7qY1klJm1d2kulr9ckw

  Version:    1.0.0


  Reversion History:

  (1.0.0)
  First Release.

*/

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#define _MAX31865_USE_FREERTOS  1

#define _MAX31865_RREF      430.0f
#define _MAX31865_RNOMINAL  100.0f

//#########################################################################################################################

//#########################################################################################################################
void  Max31865_init(uint8_t  numwires, uint8_t filterHz);
bool  Max31865_readTempC(float *readTemp);
bool  Max31865_readTempF(float *readTemp);
float Max31865_Filter(float newInput, float lastOutput, float efectiveFactor);
//#########################################################################################################################
#ifdef __cplusplus
}
#endif



#endif
