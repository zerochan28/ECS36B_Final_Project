// Created by Saifedin Maani on 11/18/2020 8:47 PM
// Edited by Linhao Chen on 11/22/2020

#include "food.h"

// Food Object
Food::Food()
{
	
}

Food::Food(string food_name,unsigned int quantity)
{
  this->food_name = food_name;
  this->quantity = quantity;
}


void Food::setFoodName(string name)
{
	this->food_name = name;
}

void Food::setFoodQuantity(unsigned int quantity)
{
	this->quantity = quantity;
}

string Food::getFoodName()
{
  return this->food_name;
}

unsigned int Food::getFoodQuantity()
{
  return this->quantity;
}

// Drink Object

Drinks::Drinks()
{

}

Drinks::Drinks(string size,string flavor,string food_name,unsigned int quantity): Food (food_name, quantity)
{
	this->drink_size = size;
	this->drink_flavor = flavor;
}

void Drinks::setDrinkSize(string size)
{
	this->drink_size = size;
}

string Drinks::getDrinkSize()
{
	return this->drink_size;
}

void Drinks::setDrinkFlavor(string flavor)
{
	this->drink_flavor = flavor;
}

string Drinks::getDrinkFlavor()
{
	return this->drink_flavor;
}

// Veggeies Object
Vegetable_or_Fruits::Vegetable_or_Fruits()
{
	
}
	
Vegetable_or_Fruits::Vegetable_or_Fruits(string color, string size, string food_name,unsigned int quantity): Food (food_name, quantity)
{
	this->veg_size = size;
	this->veg_color = color;
}

void Vegetable_or_Fruits::setVegColor(string color)
{
	this->veg_color = color;
}

string Vegetable_or_Fruits::getVegColor()
{
	return this->veg_color;
}

void  Vegetable_or_Fruits::setVegSize(string size)
{
	this->veg_size = size;
}

string Vegetable_or_Fruits::getVegSize()
{
	return this->veg_size;
}

// Snacks Object
Snacks::Snacks()
{
	
}

Snacks::Snacks(string size, string color, string flavor, string food_name, unsigned int quantity): Food (food_name, quantity)
{
	this->snack_size = size;
	this->snack_color = color;
	this->snack_flavor = flavor;	
}

void Snacks::setSnackSize(string size)
{
	this->snack_size = size;
}


string Snacks::getSnackSize()
{
	return this->snack_size;
}

void Snacks::setSnackColor(string color)
{
	this->snack_color = color;
}

string Snacks::getSnackColor()
{
	return this->snack_color;
}

void Snacks::setSnackFlavor(string flavor)
{
	this->snack_flavor = flavor;
}

string Snacks::getSnackFlavor()
{
	return this->snack_flavor;
}

// Meat Object
Meat::Meat()
{
	
}

Meat::Meat(string size,string food_name, unsigned int quantity): Food (food_name, quantity)
{
	this->meat_size = size;
}

void Meat::setMeatSize(string size)
{
	this->meat_size = size;
}

string Meat::getMeatSize()
{
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




 



