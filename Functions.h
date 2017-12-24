#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "Programmer.h"
#include <deque>

using namespace std;

deque<Programmer> parse(string filename);
void rec(deque<Programmer> workers);
deque<Programmer> output(string namefile);
deque<Programmer> all_programmer();
bool cmp_by_theme(const Programmer &pr1, const Programmer &pr2);
bool cmp_by_name(const Programmer &pr1, const Programmer &pr2);
deque<pair<string, unsigned>> working_units_number();
bool cmp_by_quantity(const pair<string, unsigned> &pr1,
                     const pair<string, unsigned> &pr2);
void show_database();
void calc_different_pr();
void show_by_different_theme();
void calc_all_pr();
void number_of_working_on_different_ibm();
void show_info_about_pr();
void show_sorted_by_number_of_works();
void write_new_to_bd();

#endif
