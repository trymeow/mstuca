#include <iostream>
#include <fstream>
#include <string>

 
using namespace  std;

class Programmer {
public:
	string name_;
	unsigned IBMnumber_;
	int cipher_;
	string date_;
	unsigned stime_;
	unsigned etime_;



};

int main() {
	//comment
	setlocale(LC_ALL, "rus");
	ifstream fin;
	fin.open("Text.txt");
	if (!fin.is_open())
		cout << "ошибка открытия файла";
	string str;
	while (!fin.eof()) {
		getline(fin, str);
		cout << str << endl;
	}
	Programmer a;
	system("pause");
	return 0;
}

