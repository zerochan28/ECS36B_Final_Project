#ifndef FOOD_H
#define FOOD_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <strings.h>

using namespace std;

class Food {
  protected:
  unsigned int quantity;
  string food_name;
  double calories;
  double carbo;
  double protein;
  double fat;
  int limit_low;
  int limit_24;
  int limit_30;
  int limit_high;
  int intake;

  public:
  Food();
  Food(string food_name, unsigned int quantity);
  void setFoodName(string name);
  void setFoodQuantity(unsigned int quantity);
  void setEnergy(double value_in);
  void setCarbo(double value_in);
  void setFat(double value_in);
  void setProtein(double value_in);
  void set_low_limit(int value_in);
  void set_24_limit(int value_in);
  void set_30_limit(int value_in);
  void set_high_limit(int value_in);
  void intake_zero();
  void consume(int value_in);
  int get_intake();
  string getFoodName();
  double getEnergy();
  double getCarbo();
  double getFat();
  double getProtein();
  int get_low_limit();
  int get_24_limit();
  int get_30_limit();
  int get_high_limit();
  int get_limit(double bmi);
  unsigned int getFoodQuantity();
};

class Drinks : public Food {

  private:
  string drink_size;
  string drink_flavor;

  public:
  Drinks();
  Drinks(string size, string flavor, string food_name, unsigned int quantity);
  void setDrinkSize(string size);
  string getDrinkSize();
  void setDrinkFlavor(string flavor);
  string getDrinkFlavor();
};

class Vegetable_or_Fruits : public Food {
  private:
  string veg_size;
  string veg_color;

  public:
  Vegetable_or_Fruits();
  Vegetable_or_Fruits(
      string color, string size, string food_name, unsigned int quantity);
  void setVegColor(string color);
  string getVegColor();
  void setVegSize(string size);
  string getVegSize();
};

class Snacks : public Food {
  private:
  string snack_size;
  string snack_color;
  string snack_flavor;

  public:
  Snacks();
  Snacks(string size, string color, string flavor, string food_name,
      unsigned int quantity);
  void setSnackSize(string size);
  string getSnackSize();
  void setSnackColor(string color);
  string getSnackColor();
  void setSnackFlavor(string flavor);
  string getSnackFlavor();
};

class Meat : public Food {
  private:
  string meat_size;

  public:
  Meat();
  Meat(string size, string food_name, unsigned int quantity);
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
