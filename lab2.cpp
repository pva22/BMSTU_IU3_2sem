#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <fstream>
using namespace std;

struct Car {
	string name;
	int maxSpeed;
	int passengers;
	int consumption;
};


int main() {
	srand(time(0));
	setlocale(LC_ALL, "ru");

	ofstream ofs("C:/Users/pva22/Desktop/input_to_read.txt");
	int length;
	cout << "Введите количество автомобилей: ";
	cin >> length;
	vector <Car> cars(length);
	for (int i = 0; i < length; i++)
	{
		cout << "Введите марку: ";
		cin >> cars[i].name; ofs << cars[i].name + " ";

		cars[i].maxSpeed = rand() % 600 + 1; ofs << cars[i].maxSpeed << " ";
		cars[i].passengers = rand() % 10 + 1; ofs << cars[i].passengers << " ";
		cars[i].consumption = rand() % 50 + 1; ofs << cars[i].consumption << endl;
	}
	ofs.close();

	vector<Car> read_cars(length);
	ofstream of("C:/Users/pva22/Desktop/output_cars.txt");
	ifstream ifs("C:/Users/pva22/Desktop/input_to_read.txt");
	if (ifs.is_open()) {
		for (int i = 0; i < length; ++i) {
			string str;
			ifs >> str;
			read_cars[i].name = str;
			int speed, pass, cons;
			ifs >> speed >> pass >> cons;
			read_cars[i].maxSpeed = speed;
			read_cars[i].passengers = pass;
			read_cars[i].consumption = cons;
		}
	}
	ifs.close();

	// Работа с пользователем
	int usermaxspeed = 0;
	int userpass = 100000;
	int userconsump = 100000;
	int desicion;

	cout << "Хотите задать параметры? Если ДА то нажмите 1, если НЕТ, то 0" << endl;
	cin >> desicion;
	while (desicion) {
		int des;
		cout << "Выберите параметры для подбора: " << endl;
		cout << " Максимальная скорость : если хотите задать нажмите 0" << endl;
		cout << " Количество пассажиров : если хотите задать нажмите 1" << endl;
		cout << " Расход на 100 км. : если хотите задать нажмите 2" << endl;
		cin >> des;
		if (des == 0) {
			cout << "Введите желаемую максимальную скорость: ";
			cin >> usermaxspeed;
		}
		if (des == 1) {
			cout << "Введите желаемое количество пассажиров: ";
			cin >> userpass;
		}
		if (des == 2) {
			cout << "Введите желаемый расход на 100 км: ";
			cin >> userconsump;
		}
		cout << "Если хотите продолжить ввод нажмите 1, если нет, то 0" << endl;
		cin >> desicion;
	}

	// Проверка на пользовательские данные и запись в файл
	for (int i = 0; i < length; i++) {
		if ((read_cars[i].consumption <= userconsump) && (read_cars[i].maxSpeed >= usermaxspeed) && (read_cars[i].passengers <= userpass))
			of << read_cars[i].name << endl;
	}
	of.close();
	return 0;
}



