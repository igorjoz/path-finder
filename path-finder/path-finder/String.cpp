#include "String.h"


String::String() :
	string(new char[1]),
	length(0) {
	string[0] = '\0';
}


String::String(const String& string) {
	this->copy(string);
}


String::String(const char* cString) {
	this->copy(cString);
}


String::String(int number) {
	length = 0;

	int temp = number;

	while (temp > 0) {
		temp /= 10;
		length++;
	}

	string = new char[length + 1];

	for (int i = length - 1; i >= 0; i--) {
		string[i] = number % 10 + '0';
		number /= 10;
	}

	string[length] = '\0';
}


String::String(String&& string) noexcept :
	string(string.string),
	length(string.length) {
	string.string = nullptr;
	string.length = 0;
}


String::~String() {
	delete[] string;
}


void String::trimWhitespace() {
	trimPrecedingWhitespace();
	trimTrailingWhitespace();
}


void String::trimPrecedingWhitespace() {
	int whitespaceCount = 0;

	for (int i = 0; i < length; i++) {
		if (string[i] == ' ' or string[i] == '\t' or string[i] == '\n' or string[i] == '\r') {
			whitespaceCount++;
		}
		else {
			break;
		}
	}

	if (whitespaceCount > 0) {
		length -= whitespaceCount;

		char* temp = new char[length + 1];
		strcpy_s(temp, length + 1, string + whitespaceCount);

		delete[] string;
		string = temp;
	}
}


void String::trimTrailingWhitespace() {
	int whitespaceCount = 0;

	for (int i = length - 1; i >= 0; i--) {
		if (string[i] == ' ' or string[i] == '\t' or string[i] == '\n' or string[i] == '\r') {
			whitespaceCount++;
		}
		else {
			break;
		}
	}

	if (whitespaceCount > 0) {
		length -= whitespaceCount;

		char* temp = new char[length + 1];
		strncpy_s(temp, length + 1, string, length);
		temp[length] = '\0';

		delete[] string;
		string = temp;
	}
}


bool String::hasCharacter(char character) const {
	return hasCharacter(character, 0);
}


bool String::hasCharacter(char character, int startIndex) const {
	for (int i = startIndex; i < length; i++) {
		if (string[i] == character) {
			return true;
		}
	}

	return false;
}


int String::countCharacter(char character) const {
	return countCharacter(character, 0);
}


int String::countCharacter(char character, int startIndex) const {
	int count = 0;

	for (int i = startIndex; i < length; i++) {
		if (string[i] == character) {
			count++;
		}
	}

	return count;
}


String String::substring(int startIndex) const {
	return substring(startIndex, length - 1);
}


String String::substring(int startIndex, int endIndex) const {
	if (startIndex < 0 or startIndex >= length or endIndex < 0 or endIndex >= length) {
		return String();
	}

	int substringLength = endIndex - startIndex + 1;

	char* substring = new char[substringLength + 1];
	strncpy_s(substring, substringLength + 1, string + startIndex, substringLength);
	substring[substringLength] = '\0';

	return String(substring);
}


int String::findCharacter(char character) const {
	return findCharacter(character, 0);
}


int String::findCharacter(char character, int startIndex) const {
	for (int i = startIndex; i < length; i++) {
		if (string[i] == character) {
			return i;
		}
	}

	return -1;
}


int String::findSubstring(const String& substring) const {
	return findSubstring(substring, 0);
}


int String::findSubstring(const String& substring, int startIndex) const {
	if (substring.length > length - startIndex or substring.length == 0 or startIndex < 0 or startIndex >= length) {
		return -1;
	}

	for (int i = startIndex; i < length; i++) {
		if (string[i] == substring.string[0]) {
			bool found = true;

			for (int j = 1; j < substring.length; j++) {
				if (string[i + j] != substring.string[j]) {
					found = false;
					break;
				}
			}

			if (found) {
				return i;
			}
		}
	}

	return -1;
}


int String::findSubstring(const String& substring, int startIndex, int endIndex) const {
	if (substring.length > length - startIndex or substring.length == 0 or startIndex < 0 or startIndex >= length) {
		return -1;
	}

	if (endIndex > length - 1) {
		endIndex = length - 1;
	}


	for (int i = startIndex; i < length and i <= endIndex; i++) {
		if (string[i] == substring.string[0]) {
			bool found = true;

			for (int j = 1; j < substring.length; j++) {
				if (string[i + j] != substring.string[j]) {
					found = false;
					break;
				}
			}

			if (found) {
				return i;
			}
		}
	}

	return -1;
}


bool String::isNumber() const {
	for (int i = 0; i < length; i++) {
		if (string[i] < '0' or string[i] > '9') {
			return false;
		}
	}

	return true;
}


bool String::isEmpty() const {
	return length == 0;
}


int String::parseToInt() {
	return atoi(string);
}


String& String::operator=(const String& string) {
	if (this != &string) {
		delete[] this->string;

		this->copy(string);
	}

	return *this;
}


String& String::operator=(const char* cString) {
	delete[] this->string;

	this->copy(cString);

	return *this;
}


String& String::operator=(int number) {
	delete[] this->string;

	this->copy(number);

	return *this;
}


String& String::operator=(String&& string) noexcept {
	if (this != &string) {
		delete[] this->string;
		this->string = string.string;
		this->length = string.length;
		string.string = nullptr;
		string.length = 0;
	}

	return *this;
}


String& String::operator+=(const String& string) {
	length += string.length;

	char* temp = new char[length + 1];
	strcpy_s(temp, length + 1, this->string);
	strcat_s(temp, length + 1, string.string);

	delete[] this->string;
	this->string = temp;

	return *this;
}


String& String::operator+=(const char* cString) {
	length += strlen(cString);

	char* temp = new char[length + 1];
	strcpy_s(temp, length + 1, this->string);
	strcat_s(temp, length + 1, cString);

	delete[] this->string;
	this->string = temp;

	return *this;
}


String& String::operator+=(const char character) {
	length++;

	char* temp = new char[length + 1];
	strcpy_s(temp, length + 1, this->string);
	temp[length - 1] = character;
	temp[length] = '\0';

	delete[] this->string;
	this->string = temp;

	return *this;
}


//String& String::operator+=(const int number) {
//	char* cString = new char[11];
//	_itoa_s(number, cString, 11, 10);
//
//	length += strlen(cString);
//
//	char* temp = new char[length + 1];
//	strcpy_s(temp, length + 1, this->string);
//	strcat_s(temp, length + 1, cString);
//
//	delete[] this->string;
//	this->string = temp;
//
//	return *this;
//}


String String::operator+(const String& string) {
	String temp(*this);
	temp += string;

	return temp;
}


String String::operator+(const char* cString) {
	String temp(*this);
	temp += cString;

	return temp;
}


//bool String::operator==(const String& string) const {
//	return strcmp(this->string, string.string) == 0;
//}

bool String::operator==(const String& other) const {
	if (length != other.length) {
		return false;
	}

	for (int i = 0; i < length; i++) {
		if (string[i] != other.string[i]) {
			return false;
		}
	}

	return true;
}


bool String::operator==(const String& string) {
	return strcmp(this->string, string.string) == 0;
}

bool String::operator==(const char* cString) const {
	return strcmp(this->string, cString) == 0;
}


bool String::operator!=(const String& string) {
	return strcmp(this->string, string.string) != 0;
}


bool String::operator!=(const char* cString) {
	return strcmp(this->string, cString) != 0;
}


bool String::operator<(const String& other) const {
	return strcmp(string, other.string) < 0;
}


char& String::operator[](int index) {
	return string[index];
}


int String::getLength() const {
	return length;
}


const char* String::getCString() const {
	return string;
}


std::ostream& operator<<(std::ostream& os, const String& string) {
	os << string.string;

	return os;
}


std::istream& operator>>(std::istream& is, String& string) {
	char buffer[1024];
	is >> buffer;

	string = buffer;

	return is;
}


void String::copy(const String& string) {
	length = string.length;

	this->string = new char[length + 1];
	strcpy_s(this->string, length + 1, string.string);
}


void String::copy(const char* cString) {
	length = strlen(cString);

	this->string = new char[length + 1];
	strcpy_s(this->string, length + 1, cString);
}


void String::clear() const {
	delete[] string;
}
