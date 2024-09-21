© Real-Time Farm Monitoring System - 2024 RUSL

Guide for Connecting Components to ESP32:
1.DHT11 Sensor (Temperature & Humidity)
	DHT Pin: Connect the data pin of the DHT11 sensor to GPIO2 of the ESP32.
	VCC: Connect the VCC pin of the DHT11 sensor to the 3.3V pin of the ESP32.
	GND: Connect the ground pin of the DHT11 sensor to any GND pin of the ESP32.

2.Soil Moisture Sensors
	Soil Moisture Sensor 1: Connect the analog output pin to GPIO34 (SOIL_PIN1).
	Soil Moisture Sensor 2: Connect the analog output pin to GPIO35 (SOIL_PIN2).
	VCC: Connect the VCC pin of both sensors to the 3.3V pin of the ESP32.
	GND: Connect the ground pin of both sensors to any GND pin of the ESP32.

3.Relays
	Relay 1 (Water Pump): Connect the signal pin to GPIO12 (RELAY_1_PIN).
	Relay 2 (Humidity Controller): Connect the signal pin to GPIO13 (RELAY_2_PIN).
	Relay 3 (Temperature Controller): Connect the signal pin to GPIO14 (RELAY_3_PIN).
	VCC: Connect the VCC pin of all relays to the 3.3V pin of the ESP32.
	GND: Connect the ground pin of all relays to any GND pin of the ESP32.

4.LED Indicators
	Water Level - Low Indicator: Connect an LED to GPIO19.
	Water Level - Normal Indicator: Connect an LED to GPIO18.
	Humidity - High Indicator: Connect an LED to GPIO5.
	Humidity - Low Indicator: Connect an LED to GPIO4.
	Temperature - High Indicator: Connect an LED to GPIO22.
	Temperature - Low Indicator: Connect an LED to GPIO15.

For each LED:
- Connect the positive leg (anode) to the respective GPIO pin.
- Connect the negative leg (cathode) to the GND via a 220Ω resistor.

Power Supply:
The ESP32 board typically requires a 5V power supply but will run on USB power. Ensure that the power supply is adequate for the relays, which may need an external power source depending on their current requirements. The sensors and ESP32 should be powered from the board’s 3.3V pin.

