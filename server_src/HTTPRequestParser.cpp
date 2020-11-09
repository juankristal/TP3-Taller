#include "HTTPRequestParser.h"
#include <iostream>

HTTPRequestParser::HTTPRequestParser(std::string &text):
	text(text){}

std::string HTTPRequestParser::getCommand(){
	return this->text.substr(0, this->text.find(' '));
}

std::string HTTPRequestParser::getResource(){
	size_t first_space_pos = this->text.find(' ') + 1;
	size_t second_space_pos = this->text.find(' ', first_space_pos);
	size_t size = second_space_pos - first_space_pos;
	return this->text.substr(this->text.find('/'), size);
}

std::string HTTPRequestParser::getBody(){
	size_t pos = this->text.find("\n\n");
	if (pos == std::string::npos) return "";
	return this->text.substr(pos);
}

std::string HTTPRequestParser::getFirstLine(){
	return this->text.substr(0, this->text.find("\n"));
}

HTTPRequestParser::~HTTPRequestParser(){}
