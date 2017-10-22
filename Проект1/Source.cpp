#include <iostream>
#include <fstream>
#include <string>

 
using namespace  std;
ifstream fin;

int main() {
	//comment
	setlocale(LC_ALL, "rus");
	fin.open("Text.txt");
	if (!fin.is_open())
		cout << "ошибка открытия файла";
	string str;
	while (!fin.eof()) {
		getline(fin, str);
		cout << str << endl;
	}
	system("pause");
	return 0;
}
