#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

double get_part(string s) {
	char vowel_letters[5] = { 'a','e', 'i', 'o', 'u' };
	double vowel_counter = 0;
	double counter = 0;

	for (char & c : s) {
		for (int i = 0; i < 5; i++) {
			if (int(c) == int(vowel_letters[i])) {
				vowel_counter = vowel_counter + 1;
			}
		}
		counter = counter + 1;
	}
	return vowel_counter / counter;
}

int get_max(vector<double> a) {
	double max = 0;
	for (int i = 0; i < a.size(); i++) {
		if (a[i] > max) {
			max = i;
		}
	}
	return max;
}

int get_min(vector<double> a) {
	double min = 100;
	for (int i = 0; i < a.size(); i++) {
		if (a[i] < min) {
			min = i;
		}
	}
	return min;
}


int main() {
	setlocale(LC_ALL, "ru");

	ifstream fin;
	fin.exceptions(ifstream::badbit | ifstream::failbit);

	string path = "C:/Users/pva22/Desktop/hand_made_file.txt";

	vector <string> list_of_strings;

	// чтение из файла
	try
	{
		cout << "Попытка открыть файл" << endl;

		fin.open(path);

		cout << "Файл успешно открыт" << endl;

		while (!fin.eof()) {
			string str = " ";
			getline(fin, str);
			list_of_strings.push_back(str);
		}


	}
	catch (const ifstream::failure & ex)
	{
		cout << ex.what() << endl;

		cout << ex.code() << endl;

		cout << "Ошибка открытия файла!" << endl;
	}

	vector<double> list_of_parts;
	for (int i = 0; i < list_of_strings.size(); i++) {
		list_of_parts.push_back(get_part(list_of_strings[i]));
	}

	for (int i = 0; i < list_of_parts.size(); i++) {
		cout << i << ": " << list_of_parts[i] << endl;
	}


	int min = get_min(list_of_parts) + 1;
	int max = get_max(list_of_parts);

	ofstream fout;
	string path_out = "C:/Users/pva22/Desktop/out.txt";

	//запись в файл
	try
	{
		fout.open(path_out, ofstream::app);
		for (min; min < max; min++) {
			fout << list_of_strings[min];
			fout << endl;
		}
	}
	catch (const std::exception&)
	{
		cout << "Ошибка открытия файла!" << endl;
	}
	return 0;
}