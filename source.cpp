#include "Functions.h"
#include "Programmer.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  setlocale(LC_ALL, "rus");

  write_new_to_bd();

  while (1) {
    string command;
    cout << "enter command" << endl;
    cin >> command;

    if (command == "show")
      show_database();
    else if (command == "calculate")
      calc_different_pr();
    else if (command == "theme")
      show_by_different_theme();
    else if (command == "pr_info")
      number_of_working_on_different_ibm();
    else if (command == "calc_pr")
      calc_all_pr();
    else if (command == "info_about_pr")
      show_info_about_pr();
    else if (command == "sort_by_number")
      show_sorted_by_number_of_works();
    else if (command == "exit")
      exit(0);
    else
      cout << "error" << endl;
  }

  return 0;
}
