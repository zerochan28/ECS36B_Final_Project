//
// Created by nicholas on 11/18/2020.
// Checked by Saifedin Maani on 11/19/2020

#ifndef SMART_FRIDGE_MAIN_PERSONS_H
#define SMART_FRIDGE_MAIN_PERSONS_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <strings.h>

using namespace std;

class Person {
  public:
  Person();
  Person(string name, string phone_number, string address, int age,
      double height, double weight);
  string getPersonName();
  void setPersonName(string name);
  string getPersonPhone();
  void setPersonPhone(string phone_number);
  string getPersonAddress();
  void setPersonAddress(string address);
  int getPersonAge();
  void setPersonAge(int age);
  double getPersonHeight();
  void setPersonHeight(double height);
  double getPersonWeight();
  void setPersonWeight(double height);

  /*
	string getPersonRole();
	void setPersonRole(string role);
    void printName();
	void printPhone();
	void printRole();
	void printAddress();
	*/

  protected:
  std::string name;
  std::string phone_number;
  std::string address;
  //string role;
  int age;
  double height;
  double weight;
};

#endif //SMART_FRIDGE_MAIN_PERSONS_H
