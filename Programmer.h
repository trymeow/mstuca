#ifndef PROGRAMMER_H
#define PROGRAMMER_H

#include <iostream>

using namespace std;

class Programmer {
public:
  void setName(string name);
  string getName() const;
  void setIBMnumber(unsigned number);
  unsigned getIBMnumber() const;
  void setcipher(int n);
  int getcipher() const;
  void setdate(string date);
  string getdate() const;
  void setStime(string str);
  void setStime(unsigned stime);
  void setEtime(string str);
  void setEtime(unsigned etime);
  unsigned getStime() const;
  unsigned getEtime() const;
  void appendToName(string name);
  void setIBMnumber(string str);
  void setcipher(string str);
  friend ostream &operator<<(ostream &os, const Programmer &pr);
  bool operator<(const Programmer &pr) const;

private:
  string name_;
  unsigned IBMnumber_;
  int cipher_;
  string date_;
  unsigned stime_;
  unsigned etime_;
};

#endif
