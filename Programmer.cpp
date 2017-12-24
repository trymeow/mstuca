#include "Programmer.h"
#include <sstream>

using namespace std;

void Programmer::setName(string name) { name_ = name; }
string Programmer::getName() const { return name_; }
void Programmer::setIBMnumber(unsigned number) { IBMnumber_ = number; }
unsigned Programmer::getIBMnumber() const { return IBMnumber_; }
void Programmer::setcipher(int n) { cipher_ = n; }
int Programmer::getcipher() const { return cipher_; }
void Programmer::setdate(string date) { date_ = date; }
string Programmer::getdate() const { return date_; }
void Programmer::setStime(string str) {
  istringstream buffer(str);
  unsigned hour;
  buffer >> hour;
  stime_ = hour * 60;
  buffer.ignore();
  buffer >> hour;
  stime_ += hour;
}
void Programmer::setStime(unsigned stime) { stime_ = stime; }
void Programmer::setEtime(string str) {
  istringstream buffer(str);
  unsigned hour;
  buffer >> hour;
  etime_ = hour * 60;
  buffer.ignore();
  buffer >> hour;
  etime_ += hour;
}
void Programmer::setEtime(unsigned etime) { etime_ = etime; }
unsigned Programmer::getStime() const { return stime_; }
unsigned Programmer::getEtime() const { return etime_; }
void Programmer::appendToName(string name) { name_.append(name); }
void Programmer::setIBMnumber(string str) {
  istringstream buffer(str);
  buffer >> IBMnumber_;
}
void Programmer::setcipher(string str) {
  istringstream buffer(str);
  buffer >> cipher_;
}
ostream &operator<<(ostream &os, const Programmer &pr) {
  os << pr.name_ << '\t' << pr.IBMnumber_ << '\t' << pr.cipher_ << '\t'
     << pr.date_ << '\t' << pr.stime_ << '\t' << pr.etime_ << endl;
  return os;
}
bool Programmer::operator<(const Programmer &pr) const {
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
