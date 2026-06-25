#pragma once
#include<iostream>
#include<cstdlib>
#include<string>
#include<vector>


using namespace std;

namespace MyLib {



	int ReadNumber() {
		int number;

		cout << "enter a number\n";
		cin >> number;

		while (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits < std::streamsize>::max(), '\n');

			cout << "invalid input , please enter a number \n";
			cin >> number;

		}

		return number;

	}



	void PrintHi() {

		cout << "hi";
	}

	int GenerateRandomNumber(int from, int to) {

		return rand() % (to - from + 1) + from;
	}


	int ReadPositiveNumber(string message) {

		int number;

		do {
			cout << message << endl;
			cin >> number;

		} while (number < 0);

		return number;
	}

	int ReadNumberInRange(string message, int from, int to) {
		int number;

		do {
			cout << message << endl;
			cin >> number;

			if (number < from || number > to)
				cout << "invalid input try again, ";

		} while (number < from || number > to);
		return number;

	}

	string ReadString(string message) {
		string text;
		cout << message << endl;
		getline(cin >> ws, text);
		cout << endl;
		return text;
	}


	void ReadArray(int arr[], int& length) {

		length = ReadPositiveNumber("enter the array size");


		for (int i = 0; i < length; i++) {
			cout << "element [" << i + 1 << "] : ";
			cin >> arr[i];
		}


		cout << endl;



	}

	void PrintArray(int arr[], int length) {

		cout << "size is " << length << endl;;
		cout << "[ ";
		for (int i = 0; i < length; i++) {
			cout << arr[i] << " ";
		}
		cout << "]\n";
	}

	void FillArrayRandomly(int arr[], int length) {



		for (int i = 0; i < length; i++) {
			arr[i] = GenerateRandomNumber(1, 100);
		}

	}

	int GetMaxInArray(int arr[], int length) {
		int max = arr[0];
		for (int i = 1; i < length; i++) {
			if (arr[i] > max)
				max = arr[i];
		}
		return max;
	}

	int GetMinInArray(int arr[100], int length) {
		int min = arr[0];

		for (int i = 1; i < length; i++) {
			if (arr[i] < min)
				min = arr[i];
		}
		return min;
	}

	char ReadChar(string message) {
		cout << message << "\n";
		char c;
		cin >> c;
		return c;
	}

	vector<string> SplitString(string text, string delim) {
		int pos;
		string word;
		vector<string> words;

		while ((pos = text.find(delim)) != string::npos) {

			word = text.substr(0, pos);
			words.push_back(word);
			text.erase(0, pos + delim.size());

		}

		if (text != "")
			words.push_back(text);

		return words;

	}


}

