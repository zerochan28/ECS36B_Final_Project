#include "food.h"

// Food Object
Food::Food() {
}

Food::Food(string food_name, unsigned int quantity) {
  this->intake = 0;
  this->food_name = food_name;
  this->quantity = quantity;
}

void Food::setFoodName(string name) {
  this->food_name = name;
}

void Food::setFoodQuantity(unsigned int quantity) {
  this->quantity = quantity;
}

void Food::setEnergy(double value_in) {
  this->calories = value_in;
}

void Food::setCarbo(double value_in) {
  this->carbo = value_in;
}

void Food::setFat(double value_in) {
  this->fat = value_in;
}

void Food::setProtein(double value_in) {
  this->protein = value_in;
}

void Food::intake_zero() {
  this->intake = 0;
}

void Food::consume(int value_in) {
  int current_intake = this->intake;
  current_intake = current_intake + value_in;
  this->intake = current_intake;
}

int Food::get_intake() {
  return this->intake;
}

void Food::set_low_limit(int value_in) {
  this->limit_low = value_in;
}

void Food::set_24_limit(int value_in) {
  this->limit_24 = value_in;
}

void Food::set_30_limit(int value_in) {
  this->limit_30 = value_in;
}

void Food::set_high_limit(int value_in) {
  this->limit_high = value_in;
}

string Food::getFoodName() {
  return this->food_name;
}

double Food::getEnergy() {
  return this->calories;
}

double Food::getCarbo() {
  return this->carbo;
}

double Food::getFat() {
  return this->fat;
}

double Food::getProtein() {
  return this->protein;
}

int Food::get_low_limit() {
  return this->limit_low;
}

int Food::get_24_limit() {
  return this->limit_24;
}

int Food::get_30_limit() {
  return this->limit_30;
}

int Food::get_high_limit() {
  return this->limit_high;
}

int Food::get_limit(double bmi) {
  if (bmi < 18.5) {
    return this->get_low_limit();
  } else if (bmi < 24) {
    return this->get_24_limit();
  } else if (bmi < 30) {
    return this->get_30_limit();
  }
  return this->get_high_limit();
}

unsigned int Food::getFoodQuantity() {
  return this->quantity;
}

// Drink Object

Drinks::Drinks() {
}

Drinks::Drinks(
    string size, string flavor, string food_name, unsigned int quantity)
    : Food(food_name, quantity) {
  this->drink_size = size;
  this->drink_flavor = flavor;
}

void Drinks::setDrinkSize(string size) {
  this->drink_size = size;
}

string Drinks::getDrinkSize() {
  return this->drink_size;
}

void Drinks::setDrinkFlavor(string flavor) {
  this->drink_flavor = flavor;
}

string Drinks::getDrinkFlavor() {
  return this->drink_flavor;
}

// Veggeies Object
Vegetable_or_Fruits::Vegetable_or_Fruits() {
}

Vegetable_or_Fruits::Vegetable_or_Fruits(
    string color, string size, string food_name, unsigned int quantity)
    : Food(food_name, quantity) {
  this->veg_size = size;
  this->veg_color = color;
}

void Vegetable_or_Fruits::setVegColor(string color) {
  this->veg_color = color;
}

string Vegetable_or_Fruits::getVegColor() {
  return this->veg_color;
}

void Vegetable_or_Fruits::setVegSize(string size) {
  this->veg_size = size;
}

string Vegetable_or_Fruits::getVegSize() {
  return this->veg_size;
}

// Snacks Object
Snacks::Snacks() {
}

Snacks::Snacks(string size, string color, string flavor, string food_name,
    unsigned int quantity)
    : Food(food_name, quantity) {
  this->snack_size = size;
  this->snack_color = color;
  this->snack_flavor = flavor;
}

void Snacks::setSnackSize(string size) {
  this->snack_size = size;
}

string Snacks::getSnackSize() {
  return this->snack_size;
}

void Snacks::setSnackColor(string color) {
  this->snack_color = color;
}

string Snacks::getSnackColor() {
  return this->snack_color;
}

void Snacks::setSnackFlavor(string flavor) {
  this->snack_flavor = flavor;
}

string Snacks::getSnackFlavor() {
  return this->snack_flavor;
}

// Meat Object
Meat::Meat() {
}

Meat::Meat(string size, string food_name, unsigned int quantity)
    : Food(food_name, quantity) {
  this->meat_size = size;
}

void Meat::setMeatSize(string size) {
  this->meat_size = size;
}

string Meat::getMeatSize() {
  return this->meat_size;
}

/*
NewFood::NewFood()
{
	
	
}

NewFood::NewFood(char size ,string color ,string flavor, string name, unsigned int quant) : Food (name, quant)
{
	this->food_size = size;
	this->food_color = color;
	this->food_flavor = flavor;
	this->food_name = name;
	this->quantity = quant;
	
	
}

void NewFood::needFoodSize(bool need_size)
{
	
	this->need_size = need_size;
	
}

void NewFood::needFoodColor(bool need_color)
{
	
	this->need_color = need_color;
	
}

void NewFood::needFoodFlavor(bool need_flavor)
{
	
	this->need_flavor = need_color;
	
}

void NewFood::setFoodSize(char size)
{
	this->food_size = size;
	
}

char NewFood::getFoodSize()
{
	return this->food_size;
	
}
void NewFood::setFoodColor(string color)
{
	this->food_color = color;
	
}

string NewFood::getFoodColor()
{
	return this->food_color;
	
}



void NewFood::setFoodFlavor(string flav)
{
	this->food_flavor = flav;
}

string NewFood::getFoodFlavor()
{
	return this->food_flavor;
}

*/
