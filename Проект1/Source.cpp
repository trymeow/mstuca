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
	ofstream fout;
	ifstream fin;

	deque<Programmer> a = parse("Text.txt");
	while (!a.empty()) {
		Programmer c = a.front();   
		cout << c.getName() << " " << c.getIBMnumber() << " " << c.getcipher() << " " << c.getdate() << " " << c.getStime() << " " << c.getEtime() << endl;
		string IBMnumber = to_string(c.getIBMnumber());
		IBMnumber.append(".dat");
		cout << "IBMnumber: " << IBMnumber << endl;
		fout.open(IBMnumber, ios::out | ios::binary);
		if (!fout) { cout << "Ошибка открытия бинарного файла\n"; system("pause"); exit(0); }
		string  strn = c.getName();
		int n = strn.length();
		fout.write((char*)&n, sizeof(n));
		const char* str1 = strn.c_str();
		fout.write((char*)&str1, sizeof(str1));
		int tmp = c.getcipher();
		fout.write((char*)&tmp, sizeof(tmp));
		string  strd = c.getdate();
		int d = strd.length();
		fout.write((char*)&n, sizeof(n));
		const char* str2 = strd.c_str();
		fout.write((char*)&str2, sizeof(str2));
		tmp = c.getStime();
		fout.write((char*)&tmp, sizeof(tmp));
		tmp = c.getEtime();
		fout.write((char*)&tmp, sizeof(tmp));
		fout.close();
		fin.open(IBMnumber, ios::in | ios::binary);
		fin.read((char*)&n, sizeof(n));
		cout << n << endl;
		fin.read((char*)&str1, sizeof(str1));
		cout << str1 << endl; 
		fin.read((char*)&tmp, sizeof(tmp));
		cout << tmp << endl  ;
		fin.read((char*)&d, sizeof(d));
		fin.read((char*)&str2, sizeof(str2));
		cout << str2 << endl;
		fin.read((char*)&tmp, sizeof(tmp));
		cout << tmp << endl;
		fin.read((char*)&tmp, sizeof(tmp));
		cout << tmp << endl;
		fin.close();
		a.pop_front();
	};
	system("pause");
	return 0;
}

