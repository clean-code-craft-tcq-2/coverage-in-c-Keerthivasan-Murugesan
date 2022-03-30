#pragma once

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
bool checkIfValueIsBelowLimit(double value, double limit);
bool checkIfValueIsAboveLimit(double value, double limit);
bool checkIfValueIsWithinLimits(double value, double lowerLimit, double upperLimit);
void inferLowBreach(double value, double lowerLimit, BreachType *valueBreachType);
void inferHighBreach(double value, double upperLimit, BreachType *valueBreachType);
void inferNoBreach(double value, double lowerLimit, double upperLimit, BreachType *valueBreachType);
