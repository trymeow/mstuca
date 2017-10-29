#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


 
using namespace  std;

class Programmer {
public:
	void setName(string name) {
		name_ = name;
	};
	string getName() {
		return name_;
	};
	void setIBMnumber(unsigned number) {
		IBMnumber_ = number;
	};
	unsigned getIBMnumber() {
		return IBMnumber_;
	};
	void setcipher(int n) {
		cipher_ = n;
	};
	int getcipher() {
		return cipher_;
	};
	void setdate(string date) {
		date_ = date;
	};
	string getdate () {
		return date_;
	
	};
	void setStime(unsigned time) {
		stime_ = time;
	};
	void setEtime(unsigned time) {
		etime_ = time;
	};
	unsigned getStime() {
		return stime_;
	};
	unsigned getEtime() {
		return etime_;
	}
	void appendToName(string name) {
		name_.append(name);
	}
	void buf(string str) {
		istringstream buffer(str);
		buffer >> IBMnumber_;
		buffer.clear();
		;
	}
	void bufci(string str) {
		istringstream buffer(str);
		buffer >> cipher_;
		buffer.clear();
	}

private:
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
	a.setName (str);
	a.appendToName(" ");
	fin >> str;
	a.appendToName(str);
	fin >> str;
	a.buf(str);
	fin >> str;
	a.bufci(str);
	fin >> str;
	a.setdate(str);
	fin >> str;
	istringstream buffer(str);
	buffer.str(str);
	unsigned hour;
	buffer >> hour;
	a.setStime(hour * 60);
	buffer.ignore();
	buffer >> hour;
	a.setStime(hour + a.getStime()) ;
	fin >> str;
	buffer.clear();
	buffer.str(str);
	buffer >> hour;
	a.setEtime(hour * 60);
	buffer.ignore();
	buffer >> hour ;
	a.setEtime(hour + a.getEtime()) ;


	
	cout << a.getName()<< " "<< a.getIBMnumber()<< " " << a.getcipher() << " " << a.getdate()<< " " << a.getStime()<< " "<< a.getEtime();
	system("pause");
	return 0;
}

