// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _RemoteControl_H_
#define _RemoteControl_H_
#include "Arduino.h"
#include "Tokenizer.h"

namespace RemoteControl {

enum class Identifier
	:unsigned char {
		BEGIN = 'B', SIGNAL = 'S', END = 'E'
};

enum class IdentifiersRange
	:unsigned char {
		DIGITAL_BEGINNING = 0,
	DIGITAL_END = 127,
	ANALOG_BEGINNING = 128,
	ANALOG_END = 255
};

enum class ValuesRange
	:int {
		MIN = -127, CENTER = 0, MAX = 127

};

struct Signal {
	uint8_t id;
	int8_t value;
};

int8_t convertAnalogValue(int val, int min, int center, int max);
int8_t convertDigitalValue(bool val);

std::string transformSignalToString(Signal signal);
std::vector<Signal> transformTokensToSignal(std::vector<Token> tokens);
}
//Do not add code below this line
#endif /* _RemoteControl_H_ */
