#include "Functions.h"
#include "Programmer.h"
#include <algorithm>
#include <experimental/filesystem>
#include <fstream>

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
  else {
    if (pr1.getcipher() < pr2.getcipher())
      return 1;
    else if (pr1.getcipher() > pr2.getcipher())
      return 0;
    else {
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
  else {
    if (pr1.getIBMnumber() < pr2.getIBMnumber())
      return 1;
    else
      return 0;
  }
}

deque<pair<string, unsigned>> working_units_number() {
  deque<Programmer> pr = all_programmer();
  unsigned counter = 0;
  deque<pair<string, unsigned>> res;
  sort(pr.begin(), pr.end(), cmp_by_name);
  for (auto it = pr.begin(); it != pr.end(); it++) {
    if (it == pr.begin()) {
      counter++;
      if (it + 1 == pr.end())
        res.push_back(make_pair(it->getName(), counter));
      continue;
    }
    if (it->getName() == (it - 1)->getName()) {
      if (it->getIBMnumber() != (it - 1)->getIBMnumber()) {
        counter++;
        if (it + 1 == pr.end())
          res.push_back(make_pair(it->getName(), counter));
      } else if (it + 1 == pr.end()) {
        res.push_back(make_pair((it - 1)->getName(), counter));
        counter = 1;
      }
    } else {

      res.push_back(make_pair((it - 1)->getName(), counter));
      counter = 1;
    }
  }
  return res;
}

bool cmp_by_quantity(const pair<string, unsigned> &pr1,
                     const pair<string, unsigned> &pr2) {
  if (pr1.second < pr2.second)
    return 1;
  else if (pr1.second > pr2.second)
    return 0;
  else {
    if (pr1.first < pr2.first)
      return 1;
    else
      return 0;
  }
}

void show_database() {
  string namebd;
  cout << " enter data base" << endl;
  cin >> namebd;

  deque<Programmer> pr = output(namebd);
  sort(pr.begin(), pr.end());
  for (auto it = pr.begin(); it != pr.end(); it++)
    cout << *it;
}

void calc_different_pr() {
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
}

void show_by_different_theme() {
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
            cout << it->getName() << '\t' << it->getcipher() << '\t' << counter
                 << endl;
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
}

void calc_all_pr() {
  deque<Programmer> programmer = all_programmer();
  cout << "number of programmers: " << programmer.size() << endl;
}

void number_of_working_on_different_ibm() {
  deque<pair<string, unsigned>> res = working_units_number();
  for (auto it = res.begin(); it != res.end(); it++) {
    cout << it->first << '\t' << it->second << endl;
  }
}

void show_info_about_pr() {
  deque<Programmer> programmer = all_programmer();
  string FIO;
  cout << "enter FIO" << endl;
  cin.ignore();
  getline(cin, FIO);
  for (auto it = programmer.begin(); it != programmer.end(); it++) {
    if (it->getName() == FIO)
      cout << "  " << it->getIBMnumber() << '\t' << it->getcipher() << '\t'
           << it->getdate() << '\t' << it->getStime() << '\t' << it->getEtime()
           << endl;
  }
}

void show_sorted_by_number_of_works() {
  deque<pair<string, unsigned>> res = working_units_number();
  sort(res.begin(), res.end(), cmp_by_quantity);
  for (auto it = res.begin(); it != res.end(); it++) {
    cout << it->first << '\t' << it->second << endl;
  }
}

void write_new_to_bd() {
  deque<Programmer> a = parse("Text.txt");
  rec(a);
}
