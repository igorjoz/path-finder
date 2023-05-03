#pragma once


#include <iostream>
#include <cstring>


class String
{
private:
	char* string;
	int length;

	void copy(const String& string);
	void copy(const char* cString);
	void clear() const;

public:
	String();
	String(const String& string);
	String(const char* cString);
	String(int number);
	String(String&& string) noexcept;

	~String();

	void trimWhitespace();
	void trimPrecedingWhitespace();
	void trimTrailingWhitespace();

	bool hasCharacter(char character) const;
	bool hasCharacter(char character, int startIndex) const;

	int countCharacter(char character) const;
	int countCharacter(char character, int startIndex) const;

	String substring(int startIndex) const;
	String substring(int startIndex, int endIndex) const;

	int findCharacter(char character) const;
	int findCharacter(char character, int startIndex) const;
	int findSubstring(const String& substring) const;
	int findSubstring(const String& substring, int startIndex) const;
	int findSubstring(const String& substring, int startIndex, int endIndex) const;

	bool isNumber() const;
	bool isEmpty() const;
	int parseToInt();

	void reverse();

	String& operator=(const String& string);
	String& operator=(const char* cString);
	String& operator=(const int number);
	String& operator=(String&& string) noexcept;

	String& operator+=(const String& string);
	String& operator+=(const char* cString);
	String& operator+=(const char character);
	//String& operator+=(const int number);

	String operator+(const String& string);
	String operator+(const char* cString);

	bool operator==(const String& string) const;
	bool operator==(const String& string);
	bool operator==(const char* cString) const;
	bool operator==(const char* cString);

	bool operator!=(const String& string);
	bool operator!=(String& string);
	bool operator!=(const String& string) const;
	bool operator!=(const char* cString);

	bool operator<(const String& other) const;

	char& operator[](int index);

	int getLength() const;
	const char* getCString() const;

	/*friend bool operator==(const String& lhs, const String& rhs) {
		return lhs.operator==(rhs);
	}*/

	friend std::ostream& operator<<(std::ostream& os, const String& string);

	friend std::istream& operator>>(std::istream& is, String& string);
};

