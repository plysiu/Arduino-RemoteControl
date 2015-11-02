#include "RemoteControl.h"

namespace RemoteControl {
int8_t convertAnalogValue(int val, int min, int center, int max) {
	if (val > center) {
		return (int8_t) ValuesRange::MAX * (val - center) / (max - center);
	}
	if (val < center) {
		return (int8_t) ValuesRange::MIN * (center - val) / (center - min);
	}
	return 0;
}

int8_t convertDigitalValue(bool val) {
	return (val == true) ? (int8_t) ValuesRange::MAX : (int8_t) ValuesRange::MIN;
}
std::string transformSignalToString(RemoteControl::Signal signal) {
	std::string str = "S";
	char buffer[3];
	itoa(signal.id, buffer, 16);
	str += buffer;
	if (signal.value < 0) {
		str += '-';
	} else {
		str += '+';
	}
	itoa(signal.value, buffer, 16);
	str += buffer;
	return str;
}

std::vector<Signal> transformTokensToSignal(std::vector<Token> tokens) {
	uint8_t id;
	int8_t value;
	bool sign = false;

	int x = 0;
	std::vector<Signal> signals;
	for (unsigned int i = 0; i < tokens.size(); i++) {

		if (tokens[i].type == TokenType::SignalId) {
			x++;
			id = strtoul(tokens[i].value.c_str(), NULL, 16);
		}
		if (tokens[i].type == TokenType::Value) {
			x++;
			value = strtoul(tokens[i].value.c_str(), NULL, 16);
		}
		if (tokens[i].type == TokenType::Sign) {

			x++;

			if (tokens[i].value.c_str() == "-") {
				Serial.print(tokens[i].value.c_str());
				sign = true;

			}
		}

		if (x == 3) {

			if (sign == true) {
				value = value * -1;
			}

			signals.push_back( { id, value });
			x = 0;
			value = 0;
			sign = false;
		}

	}
	return signals;
}
}

