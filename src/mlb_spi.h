#ifndef MLB_SPI_H_
#define MLB_SPI_H_

#include "base/mlb_config.h"

#include "base/mlb_common.h"
#include "mlb_arduino_util.h"

C_LINKAGE_BEGIN

/****************************************************************************************/

typedef struct MlbSpi MlbSpi;

MlbSpi *mlb_spi(void);

void mlb_spi_begin(void);

/****************************************************************************************/

C_LINKAGE_END

#endif /* MLB_SPI_H_ */
