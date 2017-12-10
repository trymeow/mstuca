#include <deque>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Programmer {
public:
  void setName(string name) { name_ = name; }
  string getName() { return name_; }
  void setIBMnumber(unsigned number) { IBMnumber_ = number; }
  unsigned getIBMnumber() { return IBMnumber_; }
  void setcipher(int n) { cipher_ = n; }
  int getcipher() { return cipher_; }
  void setdate(string date) { date_ = date; }
  string getdate() { return date_; }
  void setStime(string str) {
    istringstream buffer(str);
    unsigned hour;
    buffer >> hour;
    stime_ = hour * 60;
    buffer.ignore();
    buffer >> hour;
    stime_ += hour;
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
  unsigned getStime() { return stime_; }
  unsigned getEtime() { return etime_; }
  void appendToName(string name) { name_.append(name); }
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

deque<Programmer> parse(string filename) {
  ifstream fin;
  fin.open(filename);
  deque<Programmer> mydeque;
  while (!fin.eof()) {
    Programmer a;
    string str;
    fin >> str;
    if (str.empty())
      break;
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
  return mydeque;
}

void rec(deque<Programmer> workers) {

  while (!workers.empty()) {
    Programmer c = workers.front();
    ofstream fout;
    string IBMnumber = to_string(c.getIBMnumber());
    IBMnumber.append(".dat");
    cout << "IBMnumber: " << IBMnumber << endl;
    fout.open(IBMnumber, ios::out | ios::app | ios::binary);
    if (!fout) {
      cout << "Ошибка открытия бинарного файла\n";
      system("pause");
      exit(0);
    }
    string strn = c.getName();
    int n = strn.length();
    fout.write((char *)&n, sizeof(n));
    const char *str1 = strn.c_str();
    fout.write(str1, n);
    int tmp = c.getcipher();
    fout.write((char *)&tmp, sizeof(tmp));
    string strd = c.getdate();
    int d = strd.length();
    fout.write((char *)&d, sizeof(d));
    const char *str2 = strd.c_str();
    fout.write(str2, d);
    tmp = c.getStime();
    fout.write((char *)&tmp, sizeof(tmp));
    tmp = c.getEtime();
    fout.write((char *)&tmp, sizeof(tmp));
    fout.close();
    workers.pop_front();
  }
}

void output(string number) {
  ifstream fin;
  fin.open(number, ios::in | ios::binary);
  while (!fin.eof()) {
    int n = 0;
    fin.read((char *)&n, sizeof(n));
    if (fin.eof())
      break;
    cout << n << "\n";
    char *str1 = new char[n + 1]();
    fin.read(str1, n);
    cout << str1 << endl;
    int tmp;
    fin.read((char *)&tmp, sizeof(tmp));
    cout << tmp << endl;
    int d;
    fin.read((char *)&d, sizeof(d));
    cout << d << "\n";
    char *str2 = new char[d + 1]();
    fin.read(str2, d);
    cout << str2 << endl;
    fin.read((char *)&tmp, sizeof(tmp));
    cout << tmp << endl;
    fin.read((char *)&tmp, sizeof(tmp));
    cout << tmp << endl;
  }
  fin.close();
}

int main() {
  setlocale(LC_ALL, "rus");
  deque<Programmer> a = parse("Text.txt");
  rec(a);
  string namebd;
  cin >> namebd;
  output(namebd);
  return 0;
}



