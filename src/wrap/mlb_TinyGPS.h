#ifndef MLB_TINY_GPS_H_
#define MLB_TINY_GPS_H_

#include "base/mlb_config.h"

#include "base/mlb_common.h"
#include "mlb_arduino_util.h"

C_LINKAGE_BEGIN

/****************************************************************************************/

typedef struct MlbTinyGpsPlus
{
#ifdef ARDUINO_ARCH_SAMD
  char fill[216];
#else
  char fill[173];
#endif
} MlbTinyGpsPlus;

typedef struct MlbTinyGpsLocation 
{
#ifdef ARDUINO_ARCH_SAMD
  char fill[56];
#else
  char fill[34];
#endif
} MlbTinyGpsLocation;

typedef struct MlbTinyGpsDate 
{
#ifdef ARDUINO_ARCH_SAMD
  char fill[16];
#else
  char fill[14];
#endif
} MlbTinyGpsDate;

typedef struct MlbTinyGpsTime 
{
#ifdef ARDUINO_ARCH_SAMD
  char fill[16];
#else
  char fill[14];
#endif
} MlbTinyGpsTime;

void tgps_construct(MlbTinyGpsPlus *p);
void tgps_destruct(MlbTinyGpsPlus *p);

bool tgps_encode(MlbTinyGpsPlus *p, char c);

uint32_t tgps_failed_checksum(const MlbTinyGpsPlus *p);
uint32_t tgps_passed_checksum(const MlbTinyGpsPlus *p);

MlbTinyGpsLocation *tgps_location(MlbTinyGpsPlus *p);
bool tgps_loc_is_valid(const MlbTinyGpsLocation *p);
bool tgps_loc_is_updated(const MlbTinyGpsLocation *p);
uint32_t tgps_loc_age(const MlbTinyGpsLocation *p);
double tgps_loc_lat(MlbTinyGpsLocation *p);
double tgps_loc_lng(MlbTinyGpsLocation *p);

MlbTinyGpsDate *tgps_date(MlbTinyGpsPlus *p);
bool tgps_date_is_valid(const MlbTinyGpsDate *p);
bool tgps_date_is_updated(const MlbTinyGpsDate *p);
uint32_t tgps_date_age(const MlbTinyGpsDate *p);
uint32_t tgps_date_value(MlbTinyGpsDate *p);
uint16_t tgps_date_year(MlbTinyGpsDate *p);
uint8_t tgps_date_month(MlbTinyGpsDate *p);
uint8_t tgps_date_day(MlbTinyGpsDate *p);

MlbTinyGpsTime *tgps_time(MlbTinyGpsPlus *p);
bool tgps_time_is_valid(const MlbTinyGpsTime *p);
bool tgps_time_is_updated(const MlbTinyGpsTime *p);
uint32_t tgps_time_age(const MlbTinyGpsTime *p);
uint32_t tgps_time_value(MlbTinyGpsTime *p);
uint8_t tgps_time_hour(MlbTinyGpsTime *p);
uint8_t tgps_time_minute(MlbTinyGpsTime *p);
uint8_t tgps_time_second(MlbTinyGpsTime *p);
uint8_t tgps_time_centisecond(MlbTinyGpsTime *p);

/****************************************************************************************/

C_LINKAGE_END

#endif /* MLB_TINY_GPS_H_ */
