#include <iostream>
#include <fstream>
#include <string>

 
using namespace  std;
ifstream fin;

int main() {
	setlocale(LC_ALL, "rus");
	fin.open("Text.txt");
	if (!fin.is_open())
		cout << "������ �������� �����";
	string str;
	fin >> str;
	cout << str<< '\n';
	system("pause");
	return 0;
}
