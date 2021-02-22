#include <iostream>

#include <random>

#include <ctime>

#include <cmath>

#include <iomanip>

using namespace std;

typedef struct elem{

	int value;
	int stroka;
	int stolbec;
	elem* Ladr;
	elem* Radr;

};

void add(elem** nach, elem** kon, int i, int j, int value) {// добавление элемента в список
	int a;
	elem* t;
	t = new(elem);
	t->stroka = i;
	t->stolbec = j;
	t->value = value;
	if (*nach == NULL) {
		t->Ladr = NULL;
		t->Radr = NULL;
		*nach = t;
		*kon = t;
	}

	else {
		t->Radr = NULL;
		t->Ladr = *kon;
		(*kon)->Radr = t;
		*kon = t;
	}

}

elem* poisk(int i, int j, elem* nach) {//поиск заданного элемента в списке
	elem* t, * q;
	t = nach;
	q = t;
	while (t != NULL) {
		if ((t->stroka == i) && (t->stolbec == j)) {
			q = t;
			return q;
		}
		else
			t = t->Radr;
	}
	q = NULL;
	return q;
}

void prosm(elem* nach, int a, int b) { //просмотр содержимого списка
	elem* c;
	for (int i = 0; i < a; ++i) {
		for (int j = 0; j < b; ++j) {
			c = poisk(i, j, nach);
			if (c) {
				cout << setw(3);
				cout << c->value;
				if (j == (b - 1)) cout << endl;
			}
			else {
				cout << setw(3);
				cout << 0;
				if (j == (b - 1)) cout << endl;
			}
		}
	}
}

elem* summ(elem* nach1, elem* nach2, int a, int b) {
	elem* c1 = NULL;
	elem* c2 = NULL;
	elem* sumn = NULL; // начало итоговой матрицы
	elem* sumk = NULL; // конец итоговой матрицы
	for (int i = 0; i < a; ++i) {
		for (int j = 0; j < b; ++j) {
			c1 = poisk(i, j, nach1);
			c2 = poisk(i, j, nach2);
			// если на [i][j] месте в обоих списках отсутсвует элемент, значит он равен 0 в матрице
			// перебираем списки в поисках информации об элементе [i][j]
			if (c1 && c2)
				add(&sumn, &sumk, i, j, c1->value + c2->value);
			else if (c1)
				add(&sumn, &sumk, i, j, c1->value);
			else if (c2)
				add(&sumn, &sumk, i, j, c2->value);
			else
				continue;
		}
	}
	return sumn;
}
int main() {
	srand(time(NULL));
	setlocale(LC_ALL, "ru");
	elem* nach1 = NULL;
	elem* kon1 = NULL;
	elem* nach2 = NULL;
	elem* kon2 = NULL;
	int a, b;
	cout << "Введите размерность матриц: ";
	cin >> a >> b;
	cout << endl;
	// Заполнение 2 списков-элементов матриц nach1 и nach2
	for (int i = 0; i < a; ++i) {
		for (int j = 0; j < b; ++j) {
			int value = rand() % 15;
			if (value != 0) { // если элемент равен нулю, его в матрице не будет
				add(&nach1, &kon1, i, j, value);
			}
			else
				continue;
		}
	}
	for (int i = 0; i < a; ++i) {
		for (int j = 0; j < b; ++j) {
			int value = rand() % 15;
			if (value != 0) {
				add(&nach2, &kon2, i, j, value);
			}
			else
				continue;
		}
	}
	cout << "Матрица 1" << endl << endl;
	prosm(nach1, a, b);
	cout << endl << "Матрица 2" << endl << endl;
	prosm(nach2, a, b);
	elem* sum = summ(nach1, nach2, a, b);
	cout << endl << "Сложенная матрица" << endl << endl;
	prosm(sum, a, b);
	return 0;
}