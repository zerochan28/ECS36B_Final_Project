#include "Person.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <strings.h>

Person::Person() {
}

Person::Person(string name, string phone_number, string address, int age,
    double height, double weight) {
  this->name = name;
  this->phone_number = phone_number;
  this->address = address;
  this->age = age;
  this->height = height;
  this->weight = weight;
}

string Person::getPersonName() {
  return this->name;
}

void Person::setPersonName(string name) {
  this->name = name;
}

string Person::getPersonPhone() {
  return this->phone_number;
}

void Person::setPersonPhone(string phone_number) {
  this->phone_number = phone_number;
}

/*
string Person::getPersonRole()
{
	return this->role;
}

void Person::setPersonRole(string address)
{
	this->role = role;
}

bool Person::operator==(Person& aperson)
{
	return ((this->name == aperson.getPersonName()) && (this->phone_number == aperson.getPersonPhone())
	&& (this->role == aperson.getPersonRole()) && (this->address == aperson.getPersonAddress()));
}

*/

string Person::getPersonAddress() {
  return this->address;
}

void Person::setPersonAddress(string address) {
  this->address = address;
}

int Person::getPersonAge() {
  return this->age;
}

void Person::setPersonAge(int age) {
  this->age = age;
}

double Person::getPersonHeight() {
  return this->height;
}

void Person::setPersonHeight(double height) {
  this->height = height;
}

double Person::getPersonWeight() {
  return this->weight;
}

void Person::setPersonWeight(double weight) {
  this->weight = weight;
}
