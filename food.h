//Saifedin Maani
//11/18/2020 8:48 PM

#ifndef FOOD_H
#define FOOD_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <strings.h>

using namespace std;


class Food
{
  protected:
	unsigned int quantity;
	string food_name;	
	
  public:
	Food();
	Food(string food_name,unsigned int quantity);
	void setFoodName(string name);
	void setFoodQuantity(unsigned int quantity);
	string getFoodName();
	unsigned int getFoodQuantity();	
};

class Drinks : public Food
{
	
private:
	string drink_size;
	string drink_flavor;
	
  public:
	Drinks();
	Drinks(string size, string flavor,string food_name,unsigned int quantity);
	void setDrinkSize(string size);
	string getDrinkSize();
	void setDrinkFlavor(string flavor);
	string getDrinkFlavor();
};

class Vegetable_or_Fruits : public Food
{
  private:
    string veg_size;
	string veg_color;
	
  public:
	Vegetable_or_Fruits();
	Vegetable_or_Fruits(string color, string size, string food_name,unsigned int quantity);
	void setVegColor(string color);
	string getVegColor();
	void setVegSize(string size);
	string getVegSize();
};



class Snacks : public Food
{
  private:
	string snack_size;
	string snack_color;
	string snack_flavor;
	
  public:
	Snacks();
	Snacks(string size, string color, string flavor, string food_name, unsigned int quantity);
	void setSnackSize(string size);
	string getSnackSize();
	void setSnackColor(string color);
	string getSnackColor();
	void setSnackFlavor(string flavor);
	string getSnackFlavor();
};



class Meat : public Food
{		
  private:
	string meat_size;
	
  public:
	Meat();
	Meat(string size,string food_name, unsigned int quantity);
	void setMeatSize(string size);
	string getMeatSize();
};


/*
class NewFood : public Food
{
	
	
  private:

	char food_size;
	string food_color;
	string food_flavor;
	bool need_size;
	bool need_color;
	bool need_flavor;
	
  public:

	NewFood();
	NewFood(char size ,string color ,string flavor, string name, unsigned int quant);
	void needFoodSize(bool need_size);
	void needFoodColor(bool need_color);
	void needFoodFlavor(bool need_flavor);
	void setFoodSize(char size);
	char getFoodSize();
	void setFoodColor(string color);
	string getFoodColor();
	void setFoodFlavor(string flav);
	string getFoodFlavor();
	
};

*/

#endif
