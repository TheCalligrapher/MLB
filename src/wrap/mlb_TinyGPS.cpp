#include "mlb_TinyGps.h"
#include "impl/mlb_wrapper.h"

#include <TinyGPS++.h>

//char a[sizeof(TinyGPSPlus)];
//char (*b)[sizeof(MlbTinyGpsPlus)] = &a;
mlb_static_assert(sizeof(MlbTinyGpsPlus) == sizeof(TinyGPSPlus));
mlb_static_assert(sizeof(MlbTinyGpsLocation) == sizeof(TinyGPSLocation));
mlb_static_assert(sizeof(MlbTinyGpsDate) == sizeof(TinyGPSDate));
mlb_static_assert(sizeof(MlbTinyGpsTime) == sizeof(TinyGPSTime));

void tgps_construct(MlbTinyGpsPlus *p)
{
  assert(p != nullptr);
  new (p) TinyGPSPlus();
}

void tgps_destruct(MlbTinyGpsPlus *p)
{
  assert(p != nullptr);
  TinyGPSPlus *d = reinterpret_cast<TinyGPSPlus *>(p);
  d->~TinyGPSPlus();
}

#define MLB_CPP_WRAPPER_C_STRUCT MlbTinyGpsPlus
#define MLB_CPP_WRAPPER_CPP_CLASS TinyGPSPlus

  MLB_CPP_WRAPPER_DEF(bool, tgps_encode, encode, char, c);
  MLB_CPP_WRAPPER_CONST_DEF(uint32_t, tgps_failed_checksum, failedChecksum);
  MLB_CPP_WRAPPER_CONST_DEF(uint32_t, tgps_passed_checksum, passedChecksum);

#undef MLB_CPP_WRAPPER_C_STRUCT
#undef MLB_CPP_WRAPPER_CPP_CLASS

/****************************************************************************************/

MlbTinyGpsLocation *tgps_location(MlbTinyGpsPlus *p)
{
  assert(p != nullptr);
  TinyGPSPlus *d = reinterpret_cast<TinyGPSPlus *>(p);
  return reinterpret_cast<MlbTinyGpsLocation *>(&d->location);
}

#define MLB_CPP_WRAPPER_C_STRUCT MlbTinyGpsLocation
#define MLB_CPP_WRAPPER_CPP_CLASS TinyGPSLocation

  MLB_CPP_WRAPPER_CONST_DEF(bool, tgps_loc_is_valid, isValid)
  MLB_CPP_WRAPPER_CONST_DEF(bool, tgps_loc_is_updated, isUpdated)
  MLB_CPP_WRAPPER_CONST_DEF(uint32_t, tgps_loc_age, age)
  MLB_CPP_WRAPPER_DEF(double, tgps_loc_lat, lat)
  MLB_CPP_WRAPPER_DEF(double, tgps_loc_lng, lng)

#undef MLB_CPP_WRAPPER_C_STRUCT
#undef MLB_CPP_WRAPPER_CPP_CLASS

/****************************************************************************************/

MlbTinyGpsDate *tgps_date(MlbTinyGpsPlus *p)
{
  assert(p != nullptr);
  TinyGPSPlus *d = reinterpret_cast<TinyGPSPlus *>(p);
  return reinterpret_cast<MlbTinyGpsDate *>(&d->date);
}

#define MLB_CPP_WRAPPER_C_STRUCT MlbTinyGpsDate
#define MLB_CPP_WRAPPER_CPP_CLASS TinyGPSDate

  MLB_CPP_WRAPPER_CONST_DEF(bool, tgps_date_is_valid, isValid)
  MLB_CPP_WRAPPER_CONST_DEF(bool, tgps_date_is_updated, isUpdated)
  MLB_CPP_WRAPPER_CONST_DEF(uint32_t, tgps_date_age, age)
  MLB_CPP_WRAPPER_DEF(uint32_t, tgps_date_value, value)
  MLB_CPP_WRAPPER_DEF(uint16_t, tgps_date_year, year)
  MLB_CPP_WRAPPER_DEF(uint8_t, tgps_date_month, month)
  MLB_CPP_WRAPPER_DEF(uint8_t, tgps_date_day, day)

#undef MLB_CPP_WRAPPER_C_STRUCT
#undef MLB_CPP_WRAPPER_CPP_CLASS

/****************************************************************************************/

MlbTinyGpsTime *tgps_time(MlbTinyGpsPlus *p)
{
  assert(p != nullptr);
  TinyGPSPlus *d = reinterpret_cast<TinyGPSPlus *>(p);
  return reinterpret_cast<MlbTinyGpsTime *>(&d->time);
}

#define MLB_CPP_WRAPPER_C_STRUCT MlbTinyGpsTime
#define MLB_CPP_WRAPPER_CPP_CLASS TinyGPSTime

  MLB_CPP_WRAPPER_CONST_DEF(bool, tgps_time_is_valid, isValid)
  MLB_CPP_WRAPPER_CONST_DEF(bool, tgps_time_is_updated, isUpdated)
  MLB_CPP_WRAPPER_CONST_DEF(uint32_t, tgps_time_age, age)
  MLB_CPP_WRAPPER_DEF(uint32_t, tgps_time_value, value)
  
  MLB_CPP_WRAPPER_DEF(uint8_t, tgps_time_hour, hour)
  MLB_CPP_WRAPPER_DEF(uint8_t, tgps_time_minute, minute)
  MLB_CPP_WRAPPER_DEF(uint8_t, tgps_time_second, second)
  MLB_CPP_WRAPPER_DEF(uint8_t, tgps_time_centisecond, centisecond)

#undef MLB_CPP_WRAPPER_C_STRUCT
#undef MLB_CPP_WRAPPER_CPP_CLASS
