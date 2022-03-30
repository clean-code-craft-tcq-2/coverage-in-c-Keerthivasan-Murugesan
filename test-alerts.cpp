#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("Infers the breach type according to limits") {
	REQUIRE(inferBreach(15, 0, 30) == NORMAL);
	REQUIRE(inferBreach(35, 20, 30) == TOO_HIGH);
	REQUIRE(inferBreach(18, 20, 30) == TOO_LOW);
}

TEST_CASE("Checks if the value is below given limit") {
	REQUIRE(checkIfValueIsBelowLimit(25,30) == true);
	REQUIRE(checkIfValueIsBelowLimit(37,30) == false);
}

TEST_CASE("Checks if the value is above given limit") {
	REQUIRE(checkIfValueIsAboveLimit(25,30) == false);
	REQUIRE(checkIfValueIsAboveLimit(37,30) == true);
}

TEST_CASE("Checks if the values is within given limits") {
	REQUIRE(checkIfValueIsWithinLimits(25,0,30) == true);
	REQUIRE(checkIfValueIsWithinLimits(37,0,30) == false);
}

TEST_CASE("Check the value and alert for Passive Cooling") {
	BatteryCharacter batteryCharacter;
	batteryCharacter.coolingType = PASSIVE_COOLING;
	checkAndAlert(TO_CONTROLLER, batteryCharacter, 15);
	REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 15) == NORMAL);

	checkAndAlert(TO_EMAIL, batteryCharacter, -10);
	REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -10) == TOO_LOW);

	checkAndAlert(TO_CONTROLLER, batteryCharacter, 40);
	REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 40) == TOO_HIGH);
}

TEST_CASE("Check the value and alert for High Active Cooling") {
	BatteryCharacter batteryCharacter;
	batteryCharacter.coolingType = HI_ACTIVE_COOLING;
	checkAndAlert(TO_CONTROLLER, batteryCharacter, 15);
	REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 15) == NORMAL);

	checkAndAlert(TO_EMAIL, batteryCharacter, -10);
	REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, -10) == TOO_LOW);

	checkAndAlert(TO_CONTROLLER, batteryCharacter, 50);
	REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 50) == TOO_HIGH);
}

TEST_CASE("Check the value and alert for Medium Active Cooling") {
	BatteryCharacter batteryCharacter;
	batteryCharacter.coolingType = MED_ACTIVE_COOLING;
	checkAndAlert(TO_CONTROLLER, batteryCharacter, 15);
	REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 15) == NORMAL);

	checkAndAlert(TO_EMAIL, batteryCharacter, -10);
	REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -10) == TOO_LOW);

	checkAndAlert(TO_CONTROLLER, batteryCharacter, 50);
	REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 50) == TOO_HIGH);
}
