/*
 * Tokenizer.cpp
 *
 *  Created on: 31 paź 2015
 *      Author: plysiu
 */

#include "Tokenizer.h"
namespace RemoteControl {
Tokenizer::Tokenizer(std::string str) :
		input(str) {
	state = TokenizerState::Init;
}
/**
 */
bool Tokenizer::isSign(char character) {
	return character == '+' || character == '-';
}
/**
 */
bool Tokenizer::isSignal(char character) {
	return character == 'S';
}
/**
 */
bool Tokenizer::isInHexRange(char character) {
	return (character >= '0' && character <= '9')
			|| (character >= 'A' && character <= 'F') || (character >= 'a' && character <= 'f');
}

Token Tokenizer::next() {

	char character;
	while (true) {
		if (!queue.empty()) {
			Token token = queue.front();
			queue.pop_front();
			return token;
		}
		if (input.empty() && buffer.empty()) {
			return {TokenType::End};
		}
		//mały myk żeby wyrzucał to co zbuforowane
		if (input.empty() && !buffer.empty()) {
			Token token { TokenType::Value };
			std::swap(token.value, buffer);
			return token;
		}
		//magiczne przesunięcie xD
		character = input.at(0);
		input.erase(input.begin());
		switch (state) {
		case TokenizerState::Init:
			if (isSignal(character)) {
				state = TokenizerState::Signal;
				return {TokenType::Signal};
			}
			continue;
		case TokenizerState::Signal:
			if (isInHexRange(character)) {
				state = TokenizerState::SignalId;
				buffer += character;
			}
			continue;

		case TokenizerState::SignalId:

			if (isSign(character)) {
				state = TokenizerState::Sign;
				Token sign { TokenType::Sign };
				sign.value += character;
				queue.push_back(sign);
				Token token { TokenType::SignalId };
				std::swap(token.value, buffer);
				return token;
			}
			if (isInHexRange(character)) {
				state = TokenizerState::SignalId;
				buffer += character;
			}
			continue;

		case TokenizerState::Value:
			if (isSignal(character)) {
				state = TokenizerState::Signal;
				queue.push_back( { TokenType::Signal });
				Token token { TokenType::Value };
				std::swap(token.value, buffer);
				return token;
			}

			if (isInHexRange(character)) {
				state = TokenizerState::Value;
				buffer += character;
			}
			continue;
		case TokenizerState::Sign:
			if (isInHexRange(character)) {
				state = TokenizerState::Value;
				buffer += character;
			}
			continue;

		}
		return {TokenType::Error};
	}
}

}

