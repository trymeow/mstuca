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
		return cipher_
	};
	void setdate(string date) {

		date_ = date;
	};
	string date () {
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

private:
	unsigned stime_;
	unsigned etime_;
	string name_;
	unsigned IBMnumber_;
	int cipher_;
	string date_;


};

int main() {
	//comment
	/*setlocale(LC_ALL, "rus");
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
	a.gettime = hour * 60;
	buffer.ignore();
	buffer >> hour;
	a.gettime += hour ;
	fin >> str;
	buffer.clear();
	buffer.str(str);
	buffer >> hour;
	a.etime_ = hour * 60;
	buffer.ignore();
	buffer >> hour ;
	a.etime_ += hour ;


	cout << a.name_ << '\t' << a.IBMnumber_ << '\t' << a.cipher_ << " " << a.date_ << " "<< a.gettime << " " << a.etime_;
*/
	Programmer a;
	unsigned time = 21321;
	a.setStime(time);
	a.setEtime(time + 10);
	cout << a.getStime() << '\t' << a.getEtime() << '\n';
	system("pause");
	return 0;
}

