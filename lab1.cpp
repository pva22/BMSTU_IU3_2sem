using namespace std;
#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>



const string DefaultVehicleName = "Untyped vehicle";
const string DefaultCoachName = "Default Coach";
const string DefaultAutomobileName = "Default Automobile";
const string DefaultAeroplaneName = "Default Aeroplane";

const double DefaultVehicleSpeed = -1.;
const double DefaultCoachSpeed = 10.;
const double DefaultAutomobileSpeed = 100.;
const double DefaultAeroplaneSpeed = 500.;

const double DefaultTimeToBoot = 0.01;

// Классы
class Vehicle {
public:
	//Конструктор ТС по умолчанию
	Vehicle() : totalDistance(0), totalTime(0), baseSpeed(DefaultVehicleSpeed) {
		this->name = DefaultVehicleName;
	}
	//Параметризованый конструтор ТС
	Vehicle(string name, double inBaseSpeed) : totalDistance(0),
		totalTime(0), baseSpeed(inBaseSpeed) {
		this->name = name;
	}
	//Деструктор ТС
	virtual ~Vehicle() {}
	//Метод получения информации об имени ТС
	string GetName() {
		return name;
	}
	//Метод получения информации о скорости при покупке
	double GetBaseSpeed() {
		return baseSpeed;
	}
	//Метод получения информации о текущем пробеге
	double GetTotalDistance() {
		return totalDistance;
	}
	//Метод получения информации о текущем времени эксплуатации
	double GetTotalTime() {
		return totalTime;
	}
	//Абстрактный метод совершения поездки
	//Возвращает на true, если поезка удачна и false, если случилась авария.
	virtual bool MakeTrip(double distance) = 0;

	//Абстрактный метод получения информации о текущей скорости
	virtual double GetSpeed() = 0;

	//Оператор сравнения по умолчанию
	bool operator < (Vehicle& rhs) {
		if (GetSpeed() < rhs.GetSpeed()) {
			return true;
		}
		return false;
	}
protected:
	double totalDistance;
	//Счетчик общего времени эксплуатации
	double totalTime;
private:
	string name;
	double baseSpeed;
};
class Coach :public Vehicle {
public:
	Coach(const string name = DefaultCoachName, double inBaseSpeed = DefaultAutomobileSpeed) : Vehicle(name, inBaseSpeed) {
	}
	double GetSpeed()
	{
		return GetBaseSpeed() * exp(-totalTime / 500.);
	}
	bool MakeTrip(double distanceOfTrip) {
		double timeOfTrip = distanceOfTrip / GetSpeed();
		if (totalDistance + distanceOfTrip > MAX_DISTANCE) {
			return false;
		}
		totalDistance += distanceOfTrip;
		totalTime += timeOfTrip;
		return true;
	}
private:
	int MAX_DISTANCE = 1000;
};
class Automobile :public Vehicle {
public:
	Automobile(string name = DefaultAutomobileName, double inBaseSpeed = DefaultAutomobileSpeed) : Vehicle(name, inBaseSpeed) {}
	double GetSpeed()
	{
		return GetBaseSpeed() * exp(-totalDistance / 500.);
	}
	bool MakeTrip(double distanceOfTrip) {
		double timeOfTrip = distanceOfTrip / GetSpeed();
		totalDistance += distanceOfTrip;
		totalTime += timeOfTrip;
		return true;
	}
};
class Computer {
public:
	Computer() : baseTimeToBoot(DefaultTimeToBoot) {}
	double GetTimeToBoot() { // возвращает время загрузки компьютера
		return baseTimeToBoot;
	}
	void ComputerUpdate(double newTimeToBoot) {
		baseTimeToBoot = newTimeToBoot;
	}
protected:
	double baseTimeToBoot;
};
class Aeroplane :public Vehicle, public Computer {
public:
	Aeroplane(string name = DefaultAeroplaneName, double inBaseSpeed = DefaultAeroplaneSpeed) : Vehicle(name, inBaseSpeed) {
		Repair();
	}
	double GetSpeed() {
		return GetBaseSpeed();
	}
	void Repair() {
		timeSinceLastRepair = 0.;
	}
	double GetTimeSinceLastRepair() {
		return timeSinceLastRepair;
	}
	bool MakeTrip(double distanceOfTrip) {
		double timeOfTrip = distanceOfTrip / GetSpeed() + GetTimeToBoot();
		if (timeSinceLastRepair + timeOfTrip > MAX_FLY_TIME) {
			return false;
		}
		timeSinceLastRepair += timeOfTrip;
		totalDistance += distanceOfTrip;
		totalTime += timeOfTrip;
		return true;
	}
private:
	double timeSinceLastRepair;
	double MAX_FLY_TIME = 100.;
};

// Функции для работы с классами
void CommitRandomTrips(vector<Vehicle*>& vehicles) {
	srand(time(0));
	for (int i = 0; i < vehicles.size(); ++i) {
		double randomDistance = double(rand() % 30);
		vehicles[i]->MakeTrip(randomDistance);
	}
}
void DisplayVehicles(const vector<Vehicle*> vehicles) {
	cout << "Name" << setw(35) << "Speed" << setw(35) << "Dist" << setw(35) << "Time" << endl;
	for (int i = 0; i < vehicles.size(); i++)
	{
		cout << vehicles[i]->GetName() << setw(35) << vehicles[i]->GetSpeed() << setw(35) << vehicles[i]->GetTotalDistance() << setw(35) << vehicles[i]->GetTotalTime() << endl;
	}
	cout << endl;
}

// Функции для сортировок
template <class MyType>
void MySwap(MyType& v1, MyType& v2) {
	MyType v3 = v1;
	v1 = v2;
	v2 = v3;
}
template <class ArrayType, class LessFunctionType>
int FindMinimumIndex(ArrayType& data_array, int beginIndex, int endIndex, LessFunctionType LessFunction) {
	int minimumIndex = beginIndex;
	for (int element_number = beginIndex + 1; element_number <= endIndex; ++element_number) {
		if (LessFunction(data_array[element_number], data_array[minimumIndex])) {
			minimumIndex = element_number;
		}
	}
	return minimumIndex;
}


// Сортировки 
template <class ArrayType, class LessFunctionType>
void SelectionSort(ArrayType& data_array, int beginIndex, int endIndex, LessFunctionType LessFunction) {
	for (int element_number = beginIndex; element_number < endIndex; ++element_number) {
		int minimumIndex = FindMinimumIndex(data_array, element_number, endIndex, LessFunction);
		MySwap(data_array[minimumIndex], data_array[element_number]);
	}
}


// Функции сравнения
bool CompareDefault(Vehicle* lhs, Vehicle* rhs) {
	return *lhs < *rhs;
}
bool CompareTime(Vehicle* lhs, Vehicle* rhs) {
	return
		lhs->GetTotalTime() < rhs->GetTotalTime();
}
bool CompareSpeed(Vehicle* lhs, Vehicle* rhs) {
	return lhs->GetSpeed() <= rhs->GetSpeed();
}
bool CompareTimeSinceLastRepair(Vehicle* lhs, Vehicle* rhs) {
	return dynamic_cast <Aeroplane*>(lhs)->GetTimeSinceLastRepair() >= dynamic_cast <Aeroplane*>(rhs)->GetTimeSinceLastRepair();
}

template<class T>
vector<T> operator + (vector<T> v1, vector<T> v2) {
	vector<T> vec;
	for (int i = 0; i < v1.size(); i++) {
		vec.push_back(v1[i]);
	}
	for (int i = 0; i < v2.size(); i++) {
		vec.push_back(v2[i]);
	}
	return vec;
}

template <class ArrayType>
void InseptionSort(ArrayType& data_array, int len) {
	for (int i = 1; i < len; i++) {
		Vehicle* key = data_array[i];
		int j = i - 1;
		while (j >= 0 && data_array[j]->GetTotalTime() > key->GetTotalTime()) {
			data_array[j + 1] = data_array[j];
			data_array[j] = key;
			j--;
		}
	}
}


int main() {
	setlocale(LC_ALL, "ru");
	vector <Coach> coaches;
	vector <Automobile> automobiles;
	vector <Aeroplane> aeroplanes;

	//Добавление конкретных объектов
	coaches.push_back(Coach("Coach 1     ", 9.));
	coaches.push_back(Coach("Coach 2     ", 11.));
	coaches.push_back(Coach("Coach 3     ", 10.));
	coaches.push_back(Coach("Coach 4     ", 9.5));
	coaches.push_back(Coach("Coach 5     "));
	coaches.push_back(Coach());

	automobiles.push_back(Automobile("Automobile 1"));
	automobiles.push_back(Automobile("Automobile 2", 90.));
	automobiles.push_back(Automobile("Automobile 3", 120.));
	automobiles.push_back(Automobile("Automobile 4", 150.));
	automobiles.push_back(Automobile());

	aeroplanes.push_back(Aeroplane("Aeroplane 1", 1030.));
	aeroplanes.push_back(Aeroplane("Aeroplane 2", 560.));
	aeroplanes.push_back(Aeroplane("Aeroplane 3", 2200.));
	aeroplanes.push_back(Aeroplane());

	vector<Vehicle*> coachPointers;
	vector<Vehicle*> automobilePointers;
	vector<Vehicle*> aeroplanePointers;

	for (int i = 0; i < coaches.size(); i++) {
		coachPointers.push_back(&coaches[i]);
	}
	for (int i = 0; i < automobiles.size(); i++) {
		automobilePointers.push_back(&automobiles[i]);
	}
	for (int i = 0; i < aeroplanes.size(); i++) {
		aeroplanePointers.push_back(&aeroplanes[i]);
	}

	vector<Vehicle*> vehiclePointers = coachPointers + automobilePointers + aeroplanePointers;


	// Проверка работоспособности
	cout << setw(35) << "Начальные данные" << endl;
	DisplayVehicles(vehiclePointers);
	for (int i = 0; i < vehiclePointers.size() - 1; ++i) {
		CommitRandomTrips(vehiclePointers);
	}

	cout << setw(35) << "После поездок" << endl;
	DisplayVehicles(vehiclePointers);

	cout << setw(35) << "Сортировка выбором по скорости" << endl;
	SelectionSort(vehiclePointers, 0, vehiclePointers.size() - 1, CompareSpeed);
	DisplayVehicles(vehiclePointers);

	cout << setw(35) <<"Сортировка вставками по времени" << endl;
	InseptionSort(vehiclePointers, vehiclePointers.size());
	DisplayVehicles(vehiclePointers);
	return 0;
}

