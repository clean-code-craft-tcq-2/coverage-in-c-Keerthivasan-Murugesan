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

typedef struct {
	CoolingType coolingType;
	int lowerLimit;
	int upperLimit;
}CoolingTypeLimitsPair;

typedef struct {
	BreachType breachType;
	const char* alertStatement;
}breachTypeAlertStatementPair;

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC, void (*fpAlertMethod) (const char*));

bool checkIfValueIsBelowLimit(double value, double limit);
bool checkIfValueIsAboveLimit(double value, double limit);
bool checkIfValueIsWithinLimits(double value, double lowerLimit, double upperLimit);
void inferLowBreach(double value, double lowerLimit, BreachType *valueBreachType);
void inferHighBreach(double value, double upperLimit, BreachType *valueBreachType);
void inferNoBreach(double value, double lowerLimit, double upperLimit, BreachType *valueBreachType);
bool checkIfCoolingTypeMatches(CoolingType coolingType, int index);
void sendToController(BreachType breachType, void (*fpAlertMethod) (const char*));
void sendAlertEmail(int matchingIndex, int index, const char* recepient, void (*fpAlertPrint) (const char*));
bool checkIfBreachTypeMatches(BreachType breachType, int index);
void sendToEmail(BreachType breachType, void (*fpAlertMethod) (const char*));
void print(const char* printStatement);
