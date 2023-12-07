#ifndef SAMPLES_H
#define SAMPLES_H
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>


using namespace std;

string get_str() {
	string str;
	cin >> ws;
	getline(std::cin, str);
	cerr << str << '\n';
	return str;
}
template <typename T>
T get_correct_value(T min, T max) {
	T value;
	cin >> value;
	cerr << value << '\n';
	while (cin.fail() || cin.peek() != '\n' || value < min || value > max) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Введите ещё раз: ";
		cin >> value;
		cerr << value << '\n';
	}
	return value;
}
#endif