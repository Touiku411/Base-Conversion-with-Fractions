//1121645
#include <iostream>
#include <string>

using namespace std;

int charToValue(char c) {
	if (c >= '0' && c <= '9') 
		return c - '0';
	else if (c >= 'A' && c <= 'Z') 
		return c - 'A' + 10;
	else if (c >= 'a' && c <= 'z')
		return c - 'a' + 10;
	return -1;
}
long long convertIntegerToDecimal(string integerPart, int base_n) {
	long long decimaldigit = 0;
	long long power = 1;
	for (int i = integerPart.length() - 1; i >= 0; i--) {
		int value = charToValue(integerPart[i]);
		if (value == -1 || value >= base_n) {
			cout << "Error" << integerPart[i] << i <<"\n";
			return -1;
		}
		decimaldigit += value * power;
		power *= base_n;
	}
	return decimaldigit;
}
long long convertFractionalToDecimal(string franctionalPart, int base_m) {
	long long decimaldigit = 0.0;
	long long factor = 1 / base_m;
	for (int i = 0; i < franctionalPart.length() ; i++) {
		int value = charToValue(franctionalPart[i]);
		if (value == -1 || value >= base_m) {
			cout << "Error" << franctionalPart[i] <<  i <<"\n";
			return -1;
		}
		decimaldigit += value * factor;
		factor /= base_m;
	}
	return decimaldigit;
}
int main()
{
	string input;
	while (getline(cin, input)) {
		char sign = '+';
		string integerPart, fractionalPart;
		int base_n, base_m;

		size_t dotPos = input.find('.');
		size_t parenPos = input.find('(');
		size_t arrowPos = input.find("->");

		if (parenPos == string::npos) {
			cout << " Missing paren\n";
			continue;
		}
		if (arrowPos == string::npos) {
			cout << "Missing -> operation\n";
			continue;
		}
		//substr(pos, len)：从位置 pos 开始提取 len 个字符。﻿
		base_n = stoi(input.substr(parenPos + 1));

		size_t secondparenPos = input.find('(', arrowPos);
		base_m = stoi(input.substr(secondparenPos + 1));
		//檢查正負號
		int startIndex = 0;
		if (input[0] == '+' || input[0] == '-') {
			sign = input[0];
			startIndex = 1;
		}

		//提取整數、小數
		if (dotPos != string::npos) {
			integerPart = input.substr(startIndex, dotPos - startIndex);
			fractionalPart = input.substr(dotPos + 1, parenPos - dotPos - 1);
		}
		else {
			integerPart = input.substr(startIndex, dotPos - startIndex);
			fractionalPart = "0";
		}

		cout << convertIntegerToDecimal(integerPart, base_n);
		cout << "\n";
		cout << convertFractionalToDecimal(fractionalPart, base_m);

		//cout << sign << endl;
		//cout << integerPart << endl;
		//cout << fractionalPart << endl;
		//cout << base_n << endl;
		//cout << base_m << endl;
	}

	
}

