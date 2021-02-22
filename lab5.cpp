#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");

	ifstream fin;
	string path = "C:/Users/pva22/Desktop/hand_made.txt";
	stack<char> sym_stack;

	// посимвольное чтение из файла и добавление в стек 
	try
	{
		fin.open(path);
		char ch;
		while (fin.get(ch)){
			sym_stack.push(ch);
		}
	}
	catch (const ifstream::failure & ex)
	{
		cout << ex.what() << endl;
		cout << ex.code() << endl;
		cout << "Ошибка открытия файла!" << endl;
	}
	fin.close();

	cout << "Размер стека до обработки всех элементов: " << sym_stack.size() << endl;

	// обработка стека
	int all_sym_counter = 0;
	int sym_counter = 0;
	while (!sym_stack.empty()) {
		if (sym_stack.top() == char(123) || sym_stack.top() == char(125)){
			sym_counter++;
		}
		all_sym_counter++;
		sym_stack.pop();
	}
	cout << "Размер стека после обработки всех элементов: " << sym_stack.size() << endl;
	cout << "Кол-во всех символов: " << all_sym_counter << endl;
	cout << "Кол-во ({ или }): " << sym_counter << endl;

	return 0;
}
