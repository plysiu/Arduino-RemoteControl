/*
 * Tokenizer.h
 *
 *  Created on: 31 paź 2015
 *      Author: plysiu
 */

#ifndef TOKENIZER_H_
#define TOKENIZER_H_
#include "StandardCplusplus.h"
#include <string>
#include <list>
namespace RemoteControl{
enum class TokenizerState {
  Init, Signal, SignalId,Sign, Value,
};
enum class TokenType {
  Signal,SignalId,  Sign,Value, Error, End
};


struct Token {
	TokenType type;
	std::string value;
};

class Tokenizer {
	TokenizerState state;
	std::string input;
	std::string buffer;
	std::list<Token> queue;
public:
	Tokenizer(std::string str);
	bool isSignal(char character);
	bool isSign(char character);
	bool isInHexRange(char character);
	Token next();
};

}
#endif /* TOKENIZER_H_ */
