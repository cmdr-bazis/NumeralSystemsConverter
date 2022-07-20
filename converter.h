#pragma once
#ifndef CONVERTER_H_
#define CONVERTER_H_
#include <string>
#include <vector>
#include <iostream>

using namespace std;

string alphabet = "0123456789abcdefghijklmnopqrstuvwxyz";

class converter {
public:
	string firstNumber;
	int firstNumeralSystem;
	int secondNumeralSystem;
	bool solution = 0; //this defines will be your program with or without solution
private:
	char convertToString(int ten) { //function using for converting console information to numbers we can work with
		for (int i = 0; i < alphabet.length(); i++) {
			if (ten == i) {
				return alphabet[i];
			}
		}
	}
	int findMaxInt(string firstNumber) { //function using for some methods for finding max integer number
		int max = 0;
		for (int i = 0; i < firstNumber.length(); i++) {
			for (int j = 0; j < alphabet.length(); j++) {
				if (firstNumber[i] == alphabet[j]) {
					if (j > max) {
						max = j;
					}
				}
			}
		}
		return max;
	}
	string convertToDecimal(string firstNumber, int firstNumeralSystem, bool solution) {
		int decimal = 0;
		string stringDecimal;
		if ((firstNumeralSystem >= 2) and (firstNumeralSystem <= 36) and (firstNumeralSystem > findMaxInt(firstNumber))) {
			int wrongNumberCount = 0;
			bool minus = 0;
			if (firstNumber[0] == '-') {
				firstNumber.erase(0, 1);
				minus = true;
			}
			for (int i = 0; i < firstNumber.length(); i++) {
				wrongNumberCount = 0;
				for (int j = 0; j < alphabet.length(); j++) {
					if (firstNumber[i] == alphabet[j]) {
						decimal = decimal + j * pow(firstNumeralSystem, firstNumber.length() - 1 - i);
						if (solution == 1) {
							cout << j << "*" << firstNumeralSystem << "^" << firstNumber.length() - 1 - i;
						}
						break;
					}
					else {
						wrongNumberCount++;
						if (wrongNumberCount == alphabet.length()) {
							stringDecimal = " (error) ";
							return stringDecimal;
						}
					}
				}
				if ((i < firstNumber.length() - 1) and (solution == 1)) {
					cout << " + ";
				}
			}
			if (solution == 1) {
				cout << " = " << decimal << endl;
			}
			stringDecimal = to_string(decimal);
			if (minus) {
				stringDecimal.insert(0, "-");
			}
			return stringDecimal;
		}
		else {
			stringDecimal = " (error) ";
			return stringDecimal;
		}
	}
	string convertToAny(string stringDecimal, int secondNumeralSystem, bool solution) { //function for converting to any numeral systems from decimal
		vector <int> arr;
		string finalNumber;
		string sign;
		bool minus = false;
		int ten = 0;
		if ((stringDecimal == " (error) ") or (secondNumeralSystem < 2) or (secondNumeralSystem > 36)) {
			finalNumber = " (error) ";
			return finalNumber;
		}
		else {
			if (stringDecimal[0] == '-') {
				minus = true;
				stringDecimal.erase(0, 1);
				ten = stoi(stringDecimal);
			}
			ten = stoi(stringDecimal);
			while (ten > 0) {
				if (solution) {
					cout << sign << ten << " / " << secondNumeralSystem << " = " << sign << ten / secondNumeralSystem;
					cout << " (" << sign << convertToString(ten % secondNumeralSystem) << ") " << endl;
				}
				arr.push_back(ten % secondNumeralSystem);
				ten = ten / secondNumeralSystem;
			}
			cout << "answer: ";
			if (minus) {
				finalNumber += "-";
			}
			for (int i = 0; i < arr.size(); i++) {
				finalNumber = finalNumber + convertToString(arr[arr.size() - i - 1]);
			}
			return finalNumber;
		}
	}
	string convertToFractDecimal(string firstNumber, int firstNumeralSystem, bool solution) { //function using for convert fraction numbers to decimal system
		string stringFractDecimal;
		int count = firstNumber.length() - firstNumber.find('.') - 1;
		if ((firstNumeralSystem >= 2) and (firstNumeralSystem <= 36) and (firstNumeralSystem > findMaxInt(firstNumber)) and (count <= 6)) {
			double decimal = 0;
			bool minus = false;
			int wrongNumberCount = 0;
			double numberOfSignsToDot = 0;
			double numberOfMemorizedSigns = 0;
			if (firstNumber[0] == '-') {
				firstNumber.erase(0,1);
				minus = true;
			}
			for (int i = 0; i < firstNumber.length(); i++) {
				if (firstNumber[i] == '.') {
					numberOfSignsToDot = i;
				}
			}
			for (double i = 0; firstNumber[i] != '.'; i++) {
				wrongNumberCount = 0;
				for (double j = 0; j < alphabet.length(); j++) {
					if (firstNumber[i] == alphabet[j]) {
						decimal = decimal + j * pow(firstNumeralSystem, numberOfSignsToDot - 1.0 - i);
						if (solution == 1) {
							cout << j << "*" << firstNumeralSystem << "^" << numberOfSignsToDot - 1.0 - i;
						}
						break;
					}
					else {
						wrongNumberCount++;
						if (wrongNumberCount == alphabet.length()) {
							stringFractDecimal = " (error) ";
							return stringFractDecimal;
						}
					}
				}
				if ((i < firstNumber.length() - 1) and (solution == 1)) {
					cout << " + ";
				}
				numberOfMemorizedSigns = i;
			}
			numberOfMemorizedSigns++;
			for (double k = numberOfMemorizedSigns + 1; k < firstNumber.length(); k++) {
				wrongNumberCount = 0;
				for (double j = 0; j < alphabet.length(); j++) {
					if (firstNumber[k] == alphabet[j]) {
						decimal = decimal + j * pow(firstNumeralSystem, numberOfMemorizedSigns - k);
						if (solution == 1) {
							cout << j << " * " << firstNumeralSystem << "^" << numberOfMemorizedSigns - k;
						}
						break;
					}
					else {
						wrongNumberCount++;
						if (wrongNumberCount == alphabet.length()) {
							stringFractDecimal = " (error) ";
							return stringFractDecimal;
						}
					}
				}
				if ((k < firstNumber.length() - 1) and (solution == 1)) {
					cout << " + ";
				}
			}
			stringFractDecimal = to_string(decimal);
			if (minus) {
				stringFractDecimal.insert(0, "-");
			}
			return stringFractDecimal;
		}
		else {
			stringFractDecimal = " (error) ";
			return stringFractDecimal;
		}
	}
	string convertToFractAny(string stringFractDecimal, int secondNumeralSystem, bool solution) { //function using for convert fractional decimal numbers to any other numeral systems
		string finalNumber;
		if ((secondNumeralSystem >= 2) and (secondNumeralSystem <= 36) and (stringFractDecimal != " (error) ")) {
			double fractDecimal;
			bool minus = false;
			if (stringFractDecimal[0] == '-') {
				minus = true;
				stringFractDecimal.erase(0, 1);
			}
			int numberBeforeDot = stoi(stringFractDecimal);
			string numberAfterDot = stringFractDecimal;
			string signsToFinal;
			vector<int> arr;
			int num;
			while (numberBeforeDot > 0) {
				arr.push_back(numberBeforeDot % secondNumeralSystem);
				numberBeforeDot = numberBeforeDot / secondNumeralSystem;
			}
			for (int i = 0; i < arr.size(); i++) {
				finalNumber += convertToString(arr[arr.size() - 1 - i]);
			}
			finalNumber += ".";
			for (int i = 0; i < 6; i++) {
				while (numberAfterDot[0] != '.') {
					numberAfterDot.erase(0, 1);
				}
				numberAfterDot.insert(0, "0");
				fractDecimal = stod(numberAfterDot);
				fractDecimal = fractDecimal * secondNumeralSystem;
				numberAfterDot = to_string(fractDecimal);
				while (numberAfterDot[0] != '.') {
					signsToFinal += numberAfterDot[0];
					numberAfterDot.erase(0, 1);
				}
				finalNumber += convertToString(stoi(signsToFinal));
				signsToFinal = "";
			}
			if (minus) {
				finalNumber.insert(0, "-");
			}
			return finalNumber;
		}
		else {
			finalNumber = " (error) ";
			return finalNumber;
		}
	}
public:
	string convert() { //this function you use to convert any number to any numeral system you want
		bool fract = 0;
		if (firstNumeralSystem == secondNumeralSystem) {
			return firstNumber;
		}
		for (int i = 0; i < firstNumber.length(); i++) {
			if (firstNumber[i] == '.') {
				fract = true;
			}
		}
		if (!fract) {
			if ((firstNumeralSystem != 10) and (secondNumeralSystem == 10)) {
				string decimal = convertToDecimal(firstNumber, firstNumeralSystem, solution);
				return decimal;
			}
			else if ((firstNumeralSystem == 10) and (secondNumeralSystem != 10)) {
				string any = convertToAny(firstNumber, secondNumeralSystem, solution);
				return any;
			}
			else {
				string decimal = convertToDecimal(firstNumber, firstNumeralSystem, solution);
				string any = convertToAny(decimal, secondNumeralSystem, solution);
				return any;
			}
		}
		else {
			if ((firstNumeralSystem != 10) and (secondNumeralSystem == 10)) {
				string decimal = convertToFractDecimal(firstNumber, firstNumeralSystem, solution);
				return decimal;
			}
			else if ((firstNumeralSystem == 10) and (secondNumeralSystem != 10)) {
				string any = convertToFractAny(firstNumber, secondNumeralSystem, solution);
				return any;
			}
			else {
				string decimal = convertToFractDecimal(firstNumber, firstNumeralSystem, solution);
				string any = convertToFractAny(decimal, secondNumeralSystem, solution);
				return any;
			}
		}
	}
};
#endif

