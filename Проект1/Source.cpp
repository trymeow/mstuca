#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <deque>


 
using namespace  std;

class Programmer {
public:
	void setName(string name) {
		name_ = name;
	}
	string getName() {
		return name_;
	}
	void setIBMnumber(unsigned number) {
		IBMnumber_ = number;
	}
	unsigned getIBMnumber() {
		return IBMnumber_;
	}
	void setcipher(int n) {
		cipher_ = n;
	}
	int getcipher() {
		return cipher_;
	}
	void setdate(string date) {
		date_ = date;
	}
	string getdate () {
		return date_;
	}
	void setStime(string str) {
		istringstream buffer(str);
		unsigned hour;
		buffer >> hour;
		stime_ = hour * 60 ;
		buffer.ignore();
		buffer >> hour;
		stime_ += hour ;
	}
	void setEtime(string str) {
		istringstream buffer(str);
		unsigned hour;
		buffer >> hour;
		etime_ = hour * 60;
		buffer.ignore();
		buffer >> hour;
		etime_ += hour;
	}
	unsigned getStime() {
		return stime_;
	}
	unsigned getEtime() {
		return etime_;
	}
	void appendToName(string name) {
		name_.append(name);
	}
	void setIBMnumber(string str) {
		istringstream buffer(str);
		buffer >> IBMnumber_;
	}
	void setcipher(string str) {
		istringstream buffer(str);
		buffer >> cipher_;
	}

private:
	string name_;
	unsigned IBMnumber_;
	int cipher_;
	string date_;
	unsigned stime_;
	unsigned etime_;


};


deque<Programmer> parse( string filename) {
	ifstream fin;
	fin.open(filename);
	deque<Programmer> mydeque;
	while (!fin.eof()) {
		Programmer a;
		string str;
		fin >> str;
		a.setName(str);
		a.appendToName(" ");
		fin >> str;
		a.appendToName(str);
		fin >> str;
		a.setIBMnumber(str);
		fin >> str;
		a.setcipher(str);
		fin >> str;
		a.setdate(str);
		fin >> str;
		a.setStime(str);
		fin >> str;
		a.setEtime(str);
		mydeque.push_back(a);
	}
	return mydeque ;
}



int main() {
	//comment
	setlocale(LC_ALL, "rus");
	ifstream fin;
	deque<Programmer> a = parse("Text.txt");
	while (!a.empty()) {
		Programmer c = a.front();   
		cout << c.getName() << " " << c.getIBMnumber() << " " << c.getcipher() << " " << c.getdate() << " " << c.getStime() << " " << c.getEtime() << endl;
		a.pop_front();
	};
	system("pause");
	return 0;
}

