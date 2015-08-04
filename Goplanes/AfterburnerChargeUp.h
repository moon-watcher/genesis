#ifndef AFTERBURNER_CHARGEUP_INCLUDE_H
#define AFTERBURNER_CHARGEUP_INCLUDE_H

#include <genesis.h>

#include "ObjectStruct.h"

u16 AfterburnerChargeUpCreate();
void AfterburnerChargeUpUpdate(ObjectStruct* AfterburnerChargeUpObject);
void AfterburnerChargeUpDestroy(ObjectStruct* AfterburnerChargeUpObject);
void AfterburnerChargeUpDraw(ObjectStruct* AfterburnerChargeUpObject);

#endif
