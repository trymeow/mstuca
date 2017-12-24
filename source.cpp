#include <algorithm>
#include <deque>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Programmer {
public:
  void setName(string name) { name_ = name; }
  string getName() const { return name_; }
  void setIBMnumber(unsigned number) { IBMnumber_ = number; }
  unsigned getIBMnumber() const { return IBMnumber_; }
  void setcipher(int n) { cipher_ = n; }
  int getcipher() const { return cipher_; }
  void setdate(string date) { date_ = date; }
  string getdate() const { return date_; }
  void setStime(string str) {
    istringstream buffer(str);
    unsigned hour;
    buffer >> hour;
    stime_ = hour * 60;
    buffer.ignore();
    buffer >> hour;
    stime_ += hour;
  }
  void setStime(unsigned stime) { stime_ = stime; }
  void setEtime(string str) {
    istringstream buffer(str);
    unsigned hour;
    buffer >> hour;
    etime_ = hour * 60;
    buffer.ignore();
    buffer >> hour;
    etime_ += hour;
  }
  void setEtime(unsigned etime) { etime_ = etime; }
  unsigned getStime() const { return stime_; }
  unsigned getEtime() const { return etime_; }
  void appendToName(string name) { name_.append(name); }
  void setIBMnumber(string str) {
    istringstream buffer(str);
    buffer >> IBMnumber_;
  }
  void setcipher(string str) {
    istringstream buffer(str);
    buffer >> cipher_;
  }
  friend ostream &operator<<(ostream &os, const Programmer &pr) {
    os << pr.name_ << '\t' << pr.IBMnumber_ << '\t' << pr.cipher_ << '\t'
       << pr.date_ << '\t' << pr.stime_ << '\t' << pr.etime_ << endl;
    return os;
  }
  bool operator<(const Programmer &pr) const {
    if (this->name_ < pr.name_)
      return 1;
    else if (this->name_ > pr.name_)
      return 0;
    else if (this->date_ < pr.date_)
      return 1;
    else if (this->date_ > pr.date_)
      return 0;
    else if (this->stime_ < pr.stime_)
      return 1;
    else
      return 0;
    return 0;
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

deque<Programmer> output(string namefile) {
  ifstream fin;
  fin.open(namefile, ios::in | ios::binary);
  deque<Programmer> programmers;
  if (!fin) {
    cout << "can't open " << namefile << endl;
    exit(0);
  }
  while (!fin.eof()) {
    Programmer pr;
    unsigned number = stoul(namefile);
    pr.setIBMnumber(number);
    int n = 0;
    fin.read((char *)&n, sizeof(n));
    if (fin.eof())
      break;
    char *str1 = new char[n + 1]();
    fin.read(str1, n);
    pr.setName(str1);
    unsigned tmp;
    fin.read((char *)&tmp, sizeof(tmp));
    pr.setcipher(tmp);
    unsigned d;
    fin.read((char *)&d, sizeof(d));
    char *str2 = new char[d + 1]();
    fin.read(str2, d);
    pr.setdate(str2);
    fin.read((char *)&tmp, sizeof(tmp));
    pr.setStime(tmp);
    fin.read((char *)&tmp, sizeof(tmp));
    pr.setEtime(tmp);
    programmers.push_back(pr);
  }
  fin.close();
  return programmers;
}

deque<Programmer> all_programmer() {
  namespace fs = std::experimental::filesystem;
  deque<Programmer> prog;
  for (auto &p : fs::directory_iterator(".")) {
    fs::path pth = p.path();
    if (pth.extension() == ".dat") {
      deque<Programmer> pr = output(pth.filename());
      prog.insert(prog.begin(), pr.begin(), pr.end());
    }
  }
  return prog;
}

bool cmp_by_theme(const Programmer &pr1, const Programmer &pr2) {
  if (pr1.getName() < pr2.getName())
    return 1;
  else if (pr1.getName() > pr2.getName())
    return 0;
  else if (pr1.getName() == pr2.getName()) {
    if (pr1.getcipher() < pr2.getcipher())
      return 1;
    else if (pr1.getcipher() > pr2.getcipher())
      return 0;
    else if (pr1.getcipher() == pr2.getcipher()) {
      if (pr1.getIBMnumber() < pr2.getIBMnumber())
        return 1;
      else
        return 0;
    }
  }
}

bool cmp_by_name(const Programmer &pr1, const Programmer &pr2) {
  if (pr1.getName() < pr2.getName())
    return 1;
  else if (pr1.getName() > pr2.getName())
    return 0;
  else if (pr1.getName() == pr2.getName()) {
    if (pr1.getIBMnumber() < pr2.getIBMnumber())
      return 1;
    else
      return 0;
  }
}

int main() {
  setlocale(LC_ALL, "rus");
  deque<Programmer> a = parse("Text.txt");
  rec(a);
  while (1) {
    string command;
    cout << "enter command" << endl;
    cin >> command;
    if (command == "show") {
      string namebd;
      cout << " enter data base" << endl;
      cin >> namebd;

      deque<Programmer> pr = output(namebd);
      sort(pr.begin(), pr.end());
      for (auto it = pr.begin(); it != pr.end(); it++)
        cout << *it;
    }

    else if (command == "calculate") {
      string namebd;
      cout << " enter data base" << endl;
      cin >> namebd;

      deque<Programmer> pr = output(namebd);
      sort(pr.begin(), pr.end());
      unsigned counter = 0;
      for (auto it = pr.begin(); it != pr.end(); it++) {
        if (it == pr.begin()) {
          cout << it->getName() << endl;
          counter++;
          continue;
        }
        if (it->getName() == (it - 1)->getName())
          continue;
        cout << it->getName() << endl;
        counter++;
      }
      cout << counter << endl;
    } else if (command == "theme") {
      unsigned counter = 0;
      deque<Programmer> programmer = all_programmer();
      sort(programmer.begin(), programmer.end(), cmp_by_theme);
      for (auto it = programmer.begin(); it != programmer.end(); it++) {
        if (it == programmer.begin()) {
          counter++;
          if (it + 1 == programmer.end())
            cout << it->getName() << '\t' << it->getcipher() << '\t' << counter
                 << endl;
          continue;
        }
        if (it->getName() == (it - 1)->getName()) {
          if (it->getcipher() == (it - 1)->getcipher()) {
            if (it->getIBMnumber() != (it - 1)->getIBMnumber()) {
              counter++;
              if (it + 1 == programmer.end())
                cout << it->getName() << '\t' << it->getcipher() << '\t'
                     << counter << endl;
            }
          } else {
            cout << (it - 1)->getName() << '\t' << (it - 1)->getcipher() << '\t'
                 << counter << endl;
            counter = 1;
          }
        } else {
          cout << (it - 1)->getName() << '\t' << (it - 1)->getcipher() << '\t'
               << counter << endl;
          counter = 1;
        }
      }
    } else if (command == "pr_info") {
      unsigned counter = 0;
      deque<Programmer> programmer = all_programmer();
      sort(programmer.begin(), programmer.end(), cmp_by_name);
      for (auto it = programmer.begin(); it != programmer.end(); it++) {
        if (it == programmer.begin()) {
          counter++;
          if (it + 1 == programmer.end())
            cout << it->getName() << '\t' << counter << endl;
          continue;
        }
        if (it->getName() == (it - 1)->getName()) {
          if (it->getIBMnumber() != (it - 1)->getIBMnumber()) {
            counter++;
            if (it + 1 == programmer.end())
              cout << it->getName() << '\t' << counter << endl;
          } else if (it + 1 == programmer.end()) {
            cout << (it - 1)->getName() << '\t' << counter << endl;
            counter = 1;
          }
        } else {
          cout << (it - 1)->getName() << '\t' << counter << endl;
          counter = 1;
        }
      }
    } else if (command == "exit")
      exit(0);

    else
      cout << "error" << endl;
  }
  return 0;
}
