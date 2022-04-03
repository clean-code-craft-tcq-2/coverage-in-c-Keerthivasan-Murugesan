#include "typewise-alert.h"
#include <stdio.h>

bool checkIfValueIsBelowLimit(double value, double limit) {
	return (value < limit) ? true : false;
}

bool checkIfValueIsAboveLimit(double value, double limit) {
	return (value > limit) ? true : false;
}

bool checkIfValueIsWithinLimits(double value, double lowerLimit, double upperLimit) {
	return (value > lowerLimit && value < upperLimit) ? true : false;
}

void inferLowBreach(double value, double lowerLimit, BreachType *valueBreachType) {
	bool breachStatus;
	breachStatus = checkIfValueIsBelowLimit(value, lowerLimit);
	if (breachStatus) *valueBreachType = TOO_LOW;
}

void inferHighBreach(double value, double upperLimit, BreachType *valueBreachType) {
	bool breachStatus;
	breachStatus = checkIfValueIsAboveLimit(value, upperLimit);
	if (breachStatus) *valueBreachType = TOO_HIGH;
}

void inferNoBreach(double value, double lowerLimit, double upperLimit, BreachType *valueBreachType) {
	bool breachStatus;
	breachStatus = checkIfValueIsWithinLimits(value, lowerLimit, upperLimit);
	if (breachStatus) *valueBreachType = NORMAL;
}

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {

  	BreachType valueBreachType;
	inferLowBreach(value, lowerLimit, &valueBreachType);
	inferHighBreach(value, upperLimit, &valueBreachType);
	inferNoBreach(value, lowerLimit, upperLimit, &valueBreachType);
	return valueBreachType;
}

CoolingTypeLimitsPair CoolingTypeLimitsPairs[] = {
{PASSIVE_COOLING,0,35},
{HI_ACTIVE_COOLING,0,45},
{MED_ACTIVE_COOLING,0,40},
};

bool checkIfCoolingTypeMatches(CoolingType coolingType, int index) {
	return (coolingType == CoolingTypeLimitsPairs[index].coolingType) ? true : false;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
  int lowerLimit = 0;
  int upperLimit = 0;
  int matchfound, numberOfCoolingTypes=3;

	for(int i=0;i<numberOfCoolingTypes;i++){
		matchfound = checkIfCoolingTypeMatches(coolingType, i);
		if(matchfound){
			lowerLimit = CoolingTypeLimitsPairs[i].lowerLimit;
			upperLimit = CoolingTypeLimitsPairs[i].upperLimit;
		}
	}
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType, void (*fpAlertPrint) (const char*)) {
	char breachTypeString[10];
	char header[5] = "feed";

	sprintf(breachTypeString,"%d",breachType);
	strcat(header, breachTypeString);
  fpAlertPrint(header);
}

breachTypeAlertStatementPair breachTypeAlertStatementPairs[] = {
	{TOO_LOW, "Hi, the temperature is too low"},
	{TOO_HIGH, "Hi, the temperature is too high"},
	{NORMAL, "h"},
}; 

bool checkIfBreachTypeMatches(BreachType breachType, int index) {
	return (breachType == breachTypeAlertStatementPairs[index].breachType) ? true : false;
}

void print(const char* printStatement) {
	printf("%s \n", printStatement);
}

void sendAlertEmail(int matchingIndex, int index, const char* recepient, void (*fpAlertPrint) (const char*)) {
		// No alert for NORMAL breach type (index=2)
		if(matchingIndex && (index != 2)){
			fpAlertPrint(recepient);
			fpAlertPrint(breachTypeAlertStatementPairs[index].alertStatement);
		}
}

void sendToEmail(BreachType breachType, void (*fpAlertPrint) (const char*)) {
  	const char* recepient = "a.b@c.com";
	int matchfound, numberOfBreachTypes = 3;

	for(int i=0; i<numberOfBreachTypes; i++){
		matchfound = checkIfBreachTypeMatches(breachType, i);
		sendAlertEmail(matchfound, i, recepient, fpAlertPrint);
  }
}
