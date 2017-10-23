#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


 
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
	Programmer a;
	string str;
	fin >> str;
	a.name_ = str;
	a.name_.append(" ");
	fin >> str;
	a.name_.append(str);
	fin >> str;
	istringstream buffer(str);
	buffer >> a.IBMnumber_;
	fin >> str;
	buffer.clear();
	buffer.str(str);
	buffer >> a.cipher_;
	buffer.clear();
	fin >> str;
	a.date_ = str;
	fin >> str;
	buffer.str(str);
	unsigned hour;
	buffer >> hour;
	a.stime_ = hour * 60;
	buffer.ignore();
	buffer >> hour;
	a.stime_ = hour + a.stime_;
	fin >> str;
	buffer.clear();
	buffer.str(str);
	buffer >> hour;
	a.etime_ = hour * 60;
	buffer.ignore();
	buffer >> hour ;
	a.etime_ = hour + a.etime_;


	cout << a.name_ << '\t' << a.IBMnumber_ << '\t' << a.cipher_ << " " << a.date_ << " "<< a.stime_ << " " << a.etime_;

	system("pause");
	return 0;
}

