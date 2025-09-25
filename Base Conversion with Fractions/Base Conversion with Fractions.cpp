//1121645
#include <iostream>
#include <string>
#include <numeric>
#include <unordered_map>

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

char valueToChar(int value) {
	if (value >= 0 && value <= 9)
		return value + '0';
	else if (value >= 10 && value <= 35)
		return (value - 10) + 'A';
	return '?';
}
//n ->10(整數)
long long N_to_Decimal_Integer(string integerPart, int base_n) {
	long long decimaldigit = 0;
	long long power = 1;
	for (int i = integerPart.length() - 1; i >= 0; i--) {
		int value = charToValue(integerPart[i]);
		if (value == -1 || value >= base_n) {
			cout << "位置" << i << integerPart[i] << "Error" << "\n";
			return -1;
		}
		decimaldigit += value * power;
		power *= base_n;
	}
	return decimaldigit;
}


pair<long long,long long> N_to_Decimal_Fractional(string franctionalPart, int base_n) {
	long long fenzi = 0;
	long long fenmu = 1;
	for (char c : franctionalPart) {
		if (charToValue(c) >= base_n || charToValue(c) == -1) {
			cout << "錯誤\n";
			return { -1,-1 };
		}
		fenzi = fenzi * base_n + charToValue(c);
		fenmu *= base_n;
	}
	long long g = gcd(fenzi, fenmu);
	fenmu /= g;
	fenzi /= g;
	return { fenzi,fenmu };
}
//10-> m(整數)
string Decimal_to_M_Integer(long long IntegerDecimal, int base_m) {
	if (IntegerDecimal == 0)
		return "0";

	string result = "";
	bool isNegative = false;

	if (IntegerDecimal < 0) {
		isNegative = true;
		IntegerDecimal = -IntegerDecimal;
	}
	while (IntegerDecimal > 0) {
		int remainder = IntegerDecimal % base_m;
		result = valueToChar(remainder) + result;
		IntegerDecimal /= base_m;
	}
	if (isNegative) {
		result = "-" + result;
	}

	return result;
}

//10->m
string Decimal_to_M_Fraction(long long fenzi, long long fenmu,int base_m) {
	if (fenzi == 0)return "0";

	unordered_map<long long, int> seen;
	int pos = 0;
	string result = "";

	while (fenzi != 0) {
		if (seen.count(fenzi)) {
			//是循環小數
			int cyclestart = seen[fenzi];
			string noneRepeat = result.substr(0, cyclestart);
			string Repeat = result.substr(cyclestart);
			return noneRepeat + "[" + Repeat + "]";
		}
		seen[fenzi] = pos++;
		fenzi *= base_m;
		int digit = fenzi / fenmu;

		result += valueToChar(digit);//小數部分
		fenzi = fenzi % fenmu;
	}
	return result;
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
			integerPart = input.substr(startIndex, parenPos - startIndex);
			fractionalPart = "0";
		}
		//->decimal
		long long IntegerDecimal =  N_to_Decimal_Integer(integerPart, base_n);
		auto fraction =  N_to_Decimal_Fractional(fractionalPart, base_n);
		
		//to base_m
		string IntegerM = Decimal_to_M_Integer(IntegerDecimal, base_m);
		long long fenzi = fraction.first;
		long long fenmu = fraction.second;
		string FractionM = Decimal_to_M_Fraction(fenzi,fenmu,base_m);


		if (sign == '-') {
			IntegerM = "-" + IntegerM;
		}
		if (IntegerM == "-0" && FractionM == "0") {
			IntegerM = "0";
		}
		if (FractionM == "0") {
			cout << IntegerM << "(" << base_m << ")" << endl;
		}
		else {
			cout << IntegerM << "." << FractionM << "(" << base_m << ")" << endl;
		}
	}

	
}

