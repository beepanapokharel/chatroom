#ifndef LOGIN_H
#define LOGIN_H
#include<stdio.h>
#include <string>
using namespace std;
void authenticate(const std::string &username, const std::string &password);
string duplicateusercheck();
void signup();
string userlogin(int buf);
void display(string message);
#endif
