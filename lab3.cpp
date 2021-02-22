#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>
#include <sstream>
using namespace std;

struct Teacher {
	string surname;
	int exams;
	map <string, string> dates;
};

int main() {
	setlocale(LC_ALL, "ru");
	srand(time(0));
	string path = "C:/Users/pva22/Desktop/teachers.bin";


	int length;
	cout << "Введите количество преподавателей: ";
	cin >> length;
	vector <Teacher> teachers_input(length);

	// Алфавит для генерации названия экзамена
	char alphabet[26];
	for (int i = 97, n = 0; i <= 122; ++i, ++n) alphabet[n] = (char)i;

	// Считывание информации о преподавателях
	for (int i = 0; i < length; ++i) {
		cout << "Введите фамилию (латинскими буквами): ";
		cin >> teachers_input[i].surname;
		teachers_input[i].exams = rand() % 7 + 1;
		for (int k = 0; k < teachers_input[i].exams; ++k) {
			// Генерируем название экзамена
			char e[6];
			for (int a = 0; a < 6; ++a) e[a] = alphabet[rand() % 26];
			string exam;
			for (int a = 0; a < 6; ++a) exam += e[a];
			// Добавляем "0" для корректной формы записи даты
			string day = to_string(rand() % 30 + 1);
			if (day.length() == 1) day = "0" + day;
			string month = to_string(rand() % 12 + 1);
			if (month.length() == 1) month = "0" + month;
			string year = to_string(rand() % 30 + 2000);
			teachers_input[i].dates.insert(pair<string, string>(exam, day + "." + month + "." + year));
		}
	}

	// Запись информации в файл
	ofstream in(path, ios::binary);
	for (int i = 0; i < length; ++i) {
		in.write((char*)&teachers_input[i], sizeof(Teacher));
	}
	in.close();
	cout << "Файл записан успешно.\n";

	// Считывание информации из файла
	vector <Teacher> teachers_output;
	ifstream out(path, ios::binary);
	Teacher* teacher = new Teacher;
	while (out.read((char*)teacher, sizeof(Teacher)))
		teachers_output.push_back(*teacher);
	teacher = nullptr;
	delete teacher;
	out.close();

	// Вывод для редактирования
	int decision;
	cout << "Редактировать даты экзаменов? (Да: 1|Нет: 0): ";
	cin >> decision;
	while (decision) {
		for (int i = 0; i < teachers_output.size(); ++i) {
			cout << i << "------" + teachers_output[i].surname + "\n";
		}

		int person;
		cout << "Выберите преподавателя для редактирования (число): ";
		cin >> person;

		for (auto k = teachers_output[person].dates.begin(); k != teachers_output[person].dates.end(); ++k) {
			cout << k->first + ": " + k->second + "\n";
		}

		string exam_to_change;
		if (person <= teachers_output.size() && person >= 0) {
			cout << "Выберите экзамен для редактирования (название как в списке): ";
			cin >> exam_to_change;
		}
		else
			cout << "Выбран неверный преподаватель.\n";

		if (teachers_output[person].dates.find(exam_to_change) != teachers_output[person].dates.end()) {
			cout << "Введите новую дату в формате ДД.ММ.ГГГГ: ";
			string date;
			cin >> date;
			teachers_output[person].dates[exam_to_change] = date;
			cout << "Успешно записано.\n";
		}
		else
			cout << "Введен неверный экзамен.\n";
		cout << "Продолжить редактирование? (Да: 1|Нет: 0): ";
		cin >> decision;
	}

	// Запись обновленной информации в файл
	ofstream ino(path, ios::binary);
	for (int i = 0; i < teachers_output.size(); ++i) {
		ino.write((char*)&teachers_output[i], sizeof(Teacher));
	}
	ino.close();
	cout << "Файл перезаписан успешно.\n";


	// Считывание информации из файла
	vector <Teacher> teachers_output;
	ifstream out(path, ios::binary);
	Teacher* teacher = new Teacher;
	while (out.read((char*)teacher, sizeof(Teacher)))
		teachers_output.push_back(*teacher);
	teacher = nullptr;
	delete teacher;
	out.close();
	for (int i = 0; i < teachers_output.size(); i++) {
		cout << teachers_output[i].surname << endl;
	}


	return 0;
}
