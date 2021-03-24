#include "food.cpp"
#include "food.h"
#include "fridge_design.cpp"
#include "grocery_client.h"
#include "report_client.h"
#include "report_server.h"
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <jsonrpccpp/server.h>
#include <jsonrpccpp/server/connectors/httpserver.h>
#include <list>
#include <sstream>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <strings.h>
#include <time.h>
#include <unistd.h>
#include <vector>

using namespace jsonrpc;
using namespace std;

vector<Drinks> Drink_list;
vector<Vegetable_or_Fruits> VF_list;
vector<Snacks> Snacks_list;
vector<Meat> Meat_list;
int finish = 1;
int drink_order = 0;
int vf_order = 0;
int snack_order = 0;
int meat_order = 0;
double age = 0;
double user_bmi = 0;
double calorie_intake = 2000;
double calorie_max = 0;
double carbo_intake = 70;
double protein_intake = 50;
double fat_intake = 12;
void default_fridge();
void check_food();
void check_done();
void off_fridge();

void make_zero() {
  int drink_num = Drink_list.size();
  int vf_num = VF_list.size();
  int snack_num = Snacks_list.size();
  int meat_num = Meat_list.size();

  for (int i = 0; i < drink_num; i++) {
    Drink_list[i].intake_zero();
  }

  for (int i = 0; i < vf_num; i++) {
    VF_list[i].intake_zero();
  }

  for (int i = 0; i < snack_num; i++) {
    Snacks_list[i].intake_zero();
  }

  for (int i = 0; i < meat_num; i++) {
    Meat_list[i].intake_zero();
  }
}

string intake_report() {
  string out_report = "\nYour Today's Food Report is listed below:\n";
  out_report += "Total Calories Intake: ";
  out_report += to_string(calorie_intake);
  out_report += " kcal\n";
  out_report += "Carbohydrates Intake: ";
  out_report += to_string(carbo_intake);
  out_report += " g\n";
  out_report += "Protein Intake: ";
  out_report += to_string(protein_intake);
  out_report += " g\n";
  out_report += "Fat Intake: ";
  out_report += to_string(fat_intake);
  out_report += " g\n\n";
  return out_report;
}

void import_order(string food_name, int quantity, string food_type) {

  Json::Value result;

  HttpClient httpclient("localhost:8302");
  grocery_client myClient(httpclient, JSONRPC_CLIENT_V2);
  try {
    result = myClient.Order_Food("Order_food", food_name, quantity, food_type);
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
}

string random_import(string type) {

  Json::Value result;

  HttpClient httpclient("localhost:8302");
  grocery_client myClient(httpclient, JSONRPC_CLIENT_V2);
  try {
    result = myClient.Order_Food("order_food", "Random", 1, type);
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }

  string name = result["status"].asString();
  int quantity = 1;

  int food_index = -1;
  int type_index = 0;
  if (type == "Drink") {
    int index;
    for (index = 0; index < Drink_list.size(); index++) {
      if (name == Drink_list[index].getFoodName()) {
        food_index = index;
        type_index = 1;
        break;
      }
    }
  } else if (type == "VF") {
    int index;
    for (index = 0; index < VF_list.size(); index++) {
      if (name == VF_list[index].getFoodName()) {
        food_index = index;
        type_index = 2;
        break;
      }
    }
  } else if (type == "Snack") {
    int index;
    for (index = 0; index < Snacks_list.size(); index++) {
      if (name == Snacks_list[index].getFoodName()) {
        food_index = index;
        type_index = 3;
        break;
      }
    }
  } else if (type == "Meat") {
    int index;
    for (index = 0; index < Meat_list.size(); index++) {
      if (name == Meat_list[index].getFoodName()) {
        food_index = index;
        type_index = 4;
        break;
      }
    }
  }

  if (food_index != -1) {
    if (type_index == 1) {
      int food_quantity = Drink_list[food_index].getFoodQuantity();
      food_quantity += quantity;
      Drink_list[food_index].setFoodQuantity(food_quantity);
      //std::cout << "Order successfully, now you have " << food_quantity << " " << name << " in the fridge" << std::endl;
    } else if (type_index == 2) {
      int food_quantity = VF_list[food_index].getFoodQuantity();
      food_quantity += quantity;
      VF_list[food_index].setFoodQuantity(food_quantity);
      //std::cout << "Order successfully, now you have " << food_quantity << " " << name << " in the fridge" << std::endl;
    } else if (type_index == 3) {
      int food_quantity = Snacks_list[food_index].getFoodQuantity();
      food_quantity += quantity;
      Snacks_list[food_index].setFoodQuantity(food_quantity);
      //std::cout << "Order successfully, now you have " << food_quantity << " " << name << " in the fridge" << std::endl;
    } else if (type_index == 4) {
      int food_quantity = Meat_list[food_index].getFoodQuantity();
      food_quantity += quantity;
      Meat_list[food_index].setFoodQuantity(food_quantity);
      //std::cout << "Order successfully, now you have " << food_quantity << " " << name << " in the fridge" << std::endl;
    }
  } else {
    if (type == "Drink") {
      Drinks new_drink(result["size"].asString(), result["flavor"].asString(),
          name, quantity);
      new_drink.set_low_limit(result["limit_low"].asInt());
      new_drink.set_24_limit(result["limit_24"].asInt());
      new_drink.set_30_limit(result["limit_30"].asInt());
      new_drink.set_high_limit(result["limit_high"].asInt());
      new_drink.setEnergy(result["calorie"].asDouble());
      new_drink.setCarbo(result["carbo"].asDouble());
      new_drink.setProtein(result["protein"].asDouble());
      new_drink.setFat(result["fat"].asDouble());
      Drink_list.push_back(new_drink);
    } else if (type == "VF") {
      Vegetable_or_Fruits new_VF(result["color"].asString(),
          result["size"].asString(), name, quantity);
      new_VF.set_low_limit(result["limit_low"].asInt());
      new_VF.set_24_limit(result["limit_24"].asInt());
      new_VF.set_30_limit(result["limit_30"].asInt());
      new_VF.set_high_limit(result["limit_high"].asInt());
      new_VF.setEnergy(result["calorie"].asDouble());
      new_VF.setCarbo(result["carbo"].asDouble());
      new_VF.setProtein(result["protein"].asDouble());
      new_VF.setFat(result["fat"].asDouble());
      VF_list.push_back(new_VF);
    } else if (type == "Snack") {
      Snacks new_snack(result["size"].asString(), result["color"].asString(),
          result["flavor"].asString(), name, quantity);
      new_snack.set_low_limit(result["limit_low"].asInt());
      new_snack.set_24_limit(result["limit_24"].asInt());
      new_snack.set_30_limit(result["limit_30"].asInt());
      new_snack.set_high_limit(result["limit_high"].asInt());
      new_snack.setEnergy(result["calorie"].asDouble());
      new_snack.setCarbo(result["carbo"].asDouble());
      new_snack.setProtein(result["protein"].asDouble());
      new_snack.setFat(result["fat"].asDouble());
      Snacks_list.push_back(new_snack);
    } else if (type == "Meat") {
      Meat new_meat(result["size"].asString(), name, quantity);
      new_meat.set_low_limit(result["limit_low"].asInt());
      new_meat.set_24_limit(result["limit_24"].asInt());
      new_meat.set_30_limit(result["limit_30"].asInt());
      new_meat.set_high_limit(result["limit_high"].asInt());
      new_meat.setEnergy(result["calorie"].asDouble());
      new_meat.setCarbo(result["carbo"].asDouble());
      new_meat.setProtein(result["protein"].asDouble());
      new_meat.setFat(result["fat"].asDouble());
      Meat_list.push_back(new_meat);
    }
  }

  string return_str = name;
  return_str += " 1 ";
  return_str += result["size"].asString();
  return_str += "\n";
  return return_str;
}

string food_import() {

  int drink_num = Drink_list.size();
  int vf_num = VF_list.size();
  int snack_num = Snacks_list.size();
  int meat_num = Meat_list.size();

  int i = 0;

  string import_list = "Based on your diet, smart fridge import those "
                       "following foods automatically\n";

  for (i = 0; i < drink_num; i++) {
    if (Drink_list[i].get_intake() == 1) {
      import_order(Drink_list[i].getFoodName(), 1, "Drink");
      int food_quantity = (int)Drink_list[i].getFoodQuantity();
      food_quantity++;
      Drink_list[i].setFoodQuantity(food_quantity);
      import_list += Drink_list[i].getFoodName();
      import_list += " 1 ";
      import_list += Drink_list[i].getDrinkSize();
      import_list += "\n";
    }
    if ((Drink_list[i].get_intake() > 1)
        && (Drink_list[i].getFoodQuantity() < 8)) {
      import_order(Drink_list[i].getFoodName(),
          Drink_list[i].get_limit(user_bmi), "Drink");
      int food_quantity = (int)Drink_list[i].getFoodQuantity();
      food_quantity++;
      Drink_list[i].setFoodQuantity(food_quantity);
      import_list += Drink_list[i].getFoodName();
      import_list += " ";
      import_list += to_string(Drink_list[i].get_limit(user_bmi));
      import_list += " ";
      import_list += Drink_list[i].getDrinkSize();
      import_list += "\n";
    }
  }

  for (i = 0; i < vf_num; i++) {
    if (VF_list[i].get_intake() == 1) {
      import_order(VF_list[i].getFoodName(), 1, "VF");
      int food_quantity = (int)VF_list[i].getFoodQuantity();
      food_quantity++;
      VF_list[i].setFoodQuantity(food_quantity);
      import_list += VF_list[i].getFoodName();
      import_list += " 1 ";
      import_list += VF_list[i].getVegSize();
      import_list += "\n";
    }
    if ((VF_list[i].get_intake() > 1) && (VF_list[i].getFoodQuantity() < 10)) {
      import_order(
          VF_list[i].getFoodName(), VF_list[i].get_limit(user_bmi), "VF");
      int food_quantity = (int)VF_list[i].getFoodQuantity();
      food_quantity++;
      VF_list[i].setFoodQuantity(food_quantity);
      import_list += VF_list[i].getFoodName();
      import_list += " ";
      import_list += to_string(VF_list[i].get_limit(user_bmi));
      import_list += " ";
      import_list += VF_list[i].getVegSize();
      import_list += "\n";
    }
  }

  for (i = 0; i < snack_num; i++) {
    if (Snacks_list[i].get_intake() == 1) {
      import_order(Snacks_list[i].getFoodName(), 1, "Snack");
      int food_quantity = (int)Snacks_list[i].getFoodQuantity();
      food_quantity++;
      Snacks_list[i].setFoodQuantity(food_quantity);
      import_list += Snacks_list[i].getFoodName();
      import_list += " 1 ";
      import_list += Snacks_list[i].getSnackSize();
      import_list += "\n";
    }
    if ((Snacks_list[i].get_intake() > 1)
        && (Snacks_list[i].getFoodQuantity() < 5)) {
      import_order(Snacks_list[i].getFoodName(),
          Snacks_list[i].get_limit(user_bmi), "Snack");
      int food_quantity = (int)Snacks_list[i].getFoodQuantity();
      food_quantity++;
      Snacks_list[i].setFoodQuantity(food_quantity);
      import_list += Snacks_list[i].getFoodName();
      import_list += " ";
      import_list += to_string(Snacks_list[i].get_limit(user_bmi));
      import_list += " ";
      import_list += Snacks_list[i].getSnackSize();
      import_list += "\n";
    }
  }

  for (i = 0; i < meat_num; i++) {
    if (Meat_list[i].get_intake() == 1) {
      import_order(Meat_list[i].getFoodName(), 1, "Meat");
      int food_quantity = (int)Meat_list[i].getFoodQuantity();
      food_quantity++;
      Meat_list[i].setFoodQuantity(food_quantity);
      import_list += Meat_list[i].getFoodName();
      import_list += " 1 ";
      import_list += Meat_list[i].getMeatSize();
      import_list += "\n";
    }
    if ((Meat_list[i].get_intake() > 1)
        && (Meat_list[i].getFoodQuantity() < 5)) {
      import_order(
          Meat_list[i].getFoodName(), Meat_list[i].get_limit(user_bmi), "Meat");
      int food_quantity = (int)Meat_list[i].getFoodQuantity();
      food_quantity++;
      Meat_list[i].setFoodQuantity(food_quantity);
      import_list += Meat_list[i].getFoodName();
      import_list += " ";
      import_list += to_string(Meat_list[i].get_limit(user_bmi));
      import_list += " ";
      import_list += Meat_list[i].getMeatSize();
      import_list += "\n";
    }
  }

  import_list
      += "\nSmart Fridge randomly import some food, hope you enjoy it :)\n";
  import_list += random_import("Drink");
  import_list += random_import("VF");
  import_list += random_import("Snack");
  import_list += random_import("Meat");
  import_list += "\n";
  return import_list;
}

void load_foodlist() {
  ifstream ifile;

  if (user_bmi < 18.5) {
    calorie_max = 2500;
  } else if (user_bmi < 24) {
    calorie_max = 2300;
  } else if (user_bmi < 30) {
    calorie_max = 2100;
  } else {
    calorie_max = 2000;
  }

  if (user_bmi > 30) {
    ifile.open("food/food_high.txt", ios::in);
  } else {
    ifile.open("food/food.txt", ios::in);
  }
  if (ifile) {
    int number_foods;
    ifile >> number_foods;
    for (int i = 0; i < number_foods; i++) {
      std::string food_type;
      ifile >> food_type;
      if (food_type == "Drinks") {
        std::string size;
        std::string flavor;
        std::string food_name;
        unsigned int quantity;
        ifile >> size;
        ifile >> flavor;
        ifile >> food_name;
        ifile >> quantity;
        Drinks tem_drink(size, flavor, food_name, quantity);
        double calorie;
        double carbo;
        double protein;
        double fat;
        ifile >> calorie;
        ifile >> carbo;
        ifile >> protein;
        ifile >> fat;
        tem_drink.setEnergy(calorie);
        tem_drink.setCarbo(carbo);
        tem_drink.setProtein(protein);
        tem_drink.setFat(fat);
        int limit_low;
        int limit_24;
        int limit_30;
        int limit_high;
        ifile >> limit_low;
        ifile >> limit_24;
        ifile >> limit_30;
        ifile >> limit_high;
        tem_drink.set_low_limit(limit_low);
        tem_drink.set_24_limit(limit_24);
        tem_drink.set_30_limit(limit_30);
        tem_drink.set_high_limit(limit_high);
        //std::cout << size << " " << flavor << " " << food_name << " " << quantity << std::endl;
        Drink_list.push_back(tem_drink);
      } else if (food_type == "VF") {
        std::string color;
        std::string size;
        std::string food_name;
        unsigned int quantity;
        ifile >> color;
        ifile >> size;
        ifile >> food_name;
        ifile >> quantity;
        Vegetable_or_Fruits tem_veg(color, size, food_name, quantity);
        double calorie;
        double carbo;
        double protein;
        double fat;
        ifile >> calorie;
        ifile >> carbo;
        ifile >> protein;
        ifile >> fat;
        tem_veg.setEnergy(calorie);
        tem_veg.setCarbo(carbo);
        tem_veg.setProtein(protein);
        tem_veg.setFat(fat);
        int limit_low;
        int limit_24;
        int limit_30;
        int limit_high;
        ifile >> limit_low;
        ifile >> limit_24;
        ifile >> limit_30;
        ifile >> limit_high;
        tem_veg.set_low_limit(limit_low);
        tem_veg.set_24_limit(limit_24);
        tem_veg.set_30_limit(limit_30);
        tem_veg.set_high_limit(limit_high);
        //std::cout << color << " " << size << " " << food_name << " " << quantity << std::endl;
        VF_list.push_back(tem_veg);
      } else if (food_type == "Snacks") {
        std::string size;
        std::string color;
        std::string flavor;
        std::string food_name;
        unsigned int quantity;
        ifile >> size;
        ifile >> color;
        ifile >> flavor;
        ifile >> food_name;
        ifile >> quantity;
        Snacks tem_snack(size, color, flavor, food_name, quantity);
        double calorie;
        double carbo;
        double protein;
        double fat;
        ifile >> calorie;
        ifile >> carbo;
        ifile >> protein;
        ifile >> fat;
        tem_snack.setEnergy(calorie);
        tem_snack.setCarbo(carbo);
        tem_snack.setProtein(protein);
        tem_snack.setFat(fat);
        int limit_low;
        int limit_24;
        int limit_30;
        int limit_high;
        ifile >> limit_low;
        ifile >> limit_24;
        ifile >> limit_30;
        ifile >> limit_high;
        tem_snack.set_low_limit(limit_low);
        tem_snack.set_24_limit(limit_24);
        tem_snack.set_30_limit(limit_30);
        tem_snack.set_high_limit(limit_high);
        //std::cout << size << " " << color << " " << flavor << " " << food_name << " " << quantity << std::endl;
        Snacks_list.push_back(tem_snack);
      } else if (food_type == "Meat") {
        std::string size;
        std::string food_name;
        unsigned int quantity;
        ifile >> size;
        ifile >> food_name;
        ifile >> quantity;
        Meat tem_meat(size, food_name, quantity);
        double calorie;
        double carbo;
        double protein;
        double fat;
        ifile >> calorie;
        ifile >> carbo;
        ifile >> protein;
        ifile >> fat;
        tem_meat.setEnergy(calorie);
        tem_meat.setCarbo(carbo);
        tem_meat.setProtein(protein);
        tem_meat.setFat(fat);
        int limit_low;
        int limit_24;
        int limit_30;
        int limit_high;
        ifile >> limit_low;
        ifile >> limit_24;
        ifile >> limit_30;
        ifile >> limit_high;
        tem_meat.set_low_limit(limit_low);
        tem_meat.set_24_limit(limit_24);
        tem_meat.set_30_limit(limit_30);
        tem_meat.set_high_limit(limit_high);
        //std::cout << size << " " << food_name << " " << quantity << std::endl;
        Meat_list.push_back(tem_meat);
      }
    }
  }
}

std::string print_food() {
  int drink_num = Drink_list.size();
  int vf_num = VF_list.size();
  int snack_num = Snacks_list.size();
  int meat_num = Meat_list.size();

  std::string food_string;

  for (int i = 0; i < drink_num; i++) {
    Drinks tem_drink = Drink_list[i];
    if (tem_drink.getFoodQuantity() == 0)
      continue;
    food_string += "\n";
    food_string += tem_drink.getDrinkFlavor();
    food_string += " ";
    food_string += tem_drink.getFoodName();
    food_string += " ";
    food_string += to_string(tem_drink.getFoodQuantity());
    food_string += " ";
    food_string += tem_drink.getDrinkSize();
    food_string += "   Calorie:";
    stringstream str_ss;
    str_ss << tem_drink.getEnergy();
    string food_energy = str_ss.str();
    food_string += food_energy;
  }

  for (int i = 0; i < vf_num; i++) {
    Vegetable_or_Fruits tem_vf = VF_list[i];
    if (tem_vf.getFoodQuantity() == 0)
      continue;
    food_string += "\n";
    food_string += tem_vf.getVegColor();
    food_string += " ";
    food_string += tem_vf.getFoodName();
    food_string += " ";
    food_string += to_string(tem_vf.getFoodQuantity());
    food_string += " ";
    food_string += tem_vf.getVegSize();
    food_string += "   Calorie:";
    stringstream str_ss;
    str_ss << tem_vf.getEnergy();
    string food_energy = str_ss.str();
    food_string += food_energy;
  }

  for (int i = 0; i < snack_num; i++) {
    Snacks tem_snack = Snacks_list[i];
    if (tem_snack.getFoodQuantity() == 0)
      continue;
    food_string += "\n";
    food_string += tem_snack.getSnackColor();
    food_string += " ";
    food_string += tem_snack.getSnackFlavor();
    food_string += " ";
    food_string += tem_snack.getFoodName();
    food_string += " ";
    food_string += to_string(tem_snack.getFoodQuantity());
    food_string += " ";
    food_string += tem_snack.getSnackSize();
    food_string += "   Calorie:";
    stringstream str_ss;
    str_ss << tem_snack.getEnergy();
    string food_energy = str_ss.str();
    food_string += food_energy;
  }

  for (int i = 0; i < meat_num; i++) {
    Meat tem_meat = Meat_list[i];
    if (tem_meat.getFoodQuantity() == 0)
      continue;
    food_string += "\n";
    food_string += tem_meat.getFoodName();
    food_string += " ";
    food_string += to_string(tem_meat.getFoodQuantity());
    food_string += " ";
    food_string += tem_meat.getMeatSize();
    food_string += "   Calorie:";
    stringstream str_ss;
    str_ss << tem_meat.getEnergy();
    string food_energy = str_ss.str();
    food_string += food_energy;
  }
  return food_string;
}

class fridge_server : public report_server {
  public:
  fridge_server(
      jsonrpc::AbstractServerConnector &conn, jsonrpc::serverVersion_t type);
  virtual Json::Value FoodReport(const std::string &action, double value);
  virtual Json::Value Get_Food(const std::string &action,
      const std::string &name, int quantity, const std::string &type);
  virtual Json::Value Order_Food(const std::string &action,
      const std::string &name, int quantity, const std::string &type);
};

fridge_server::fridge_server(
    AbstractServerConnector &connector, serverVersion_t type)
    : report_server(connector, type) {
}

HttpServer httpserver(8300);
fridge_server s(
    httpserver, JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
// member functions

Json::Value fridge_server::FoodReport(const std::string &action, double value) {
  Json::Value result;
  std::string command = action;

  if (command == "Check") {
    std::string food_list = print_food();
    result["response"] = food_list;
    check_food();
    sleep(3);
    check_done();
  } else if (command == "Quit") {
    finish = 0;
    result["response"] = "successful";
  } else if (command == "Open") {
    if (user_bmi == 0) {
      std::cout << "\n\n         Smart Fridge Starting Up.....\n" << std::endl;
      user_bmi = value;
      //cout << "User BMI: " << user_bmi << endl;
      load_foodlist();
      sleep(2);
      result["response"] = "successful";
      default_fridge();
    } else {
      user_bmi = value;
      result["response"] = "successful";
      default_fridge();
    }
  } else if (command == "Next") {
    //cout << "Next Command, zero" << endl;
    string intake_chart = intake_report();
    //cout << intake_chart << endl;
    string import_food = food_import();
    calorie_intake = 0;
    carbo_intake = 0;
    protein_intake = 0;
    fat_intake = 0;
    drink_order = 0;
    vf_order = 0;
    meat_order = 0;
    snack_order = 0;
    result["response"] = intake_chart + import_food;
    make_zero();
  } else if (command == "Age") {
    age = value;
    result["response"] = "successful";
  }

  return result;
}

Json::Value fridge_server::Get_Food(const std::string &action,
    const std::string &name, int quantity, const std::string &type) {

  Json::Value result;
  grab_food();
  if (type == "Drink") {
    int index;
    for (index = 0; index < Drink_list.size(); index++) {
      if (name == Drink_list[index].getFoodName()) {
        break;
      }
    }
    int food_quantity = Drink_list[index].getFoodQuantity();
    if (food_quantity == 0) {
      result["status"] = "fail";
      result["reason"] = "The food is not found in fridge";
      result["new_quantity"] = 0;
    } else {
      if ((Drink_list[index].getDrinkFlavor() == "Alcohol") && age < 21) {
        result["status"] = "fail";
        result["reason"] = "People under 21 cannot drink Alcohol";
        result["new_quantity"] = food_quantity;
      } else {
        if (food_quantity >= quantity) {
          int current_intake = Drink_list[index].get_intake();
          int new_intake = current_intake + quantity;
          int food_limit = Drink_list[index].get_limit(user_bmi);
          if (new_intake <= food_limit) {
            double added_energy = quantity * Drink_list[index].getEnergy();
            double new_energy = added_energy + calorie_intake;
            if (new_energy <= (calorie_max + 100)) {
              calorie_intake = new_energy;
              food_quantity -= quantity;
              double added_carbo = quantity * Drink_list[index].getCarbo();
              double added_protein = quantity * Drink_list[index].getProtein();
              double added_fat = quantity * Drink_list[index].getFat();
              carbo_intake += added_carbo;
              protein_intake += added_protein;
              fat_intake += added_fat;
              Drink_list[index].consume(quantity);
              Drink_list[index].setFoodQuantity(food_quantity);
              result["status"] = "successful";
              result["reason"] = "successful";
              result["new_quantity"] = food_quantity;
            } else {
              result["status"] = "reject";
              result["reason"] = "Request number exceeds the calorie limit";
              int max_intake = (int)calorie_max;
              result["new_quantity"] = max_intake;
            }
          } else {
            result["status"] = "denied";
            result["reason"] = "Request number exceeds the limit";
            result["new_quantity"] = food_limit;
          }
        } else {
          result["status"] = "fail";
          result["reason"] = "There is no enough food in fridge";
          result["new_quantity"] = food_quantity;
        }
      }
    }
  } else if (type == "VF") {
    int index;
    for (index = 0; index < VF_list.size(); index++) {
      if (name == VF_list[index].getFoodName())
        break;
    }
    int food_quantity = VF_list[index].getFoodQuantity();
    if (food_quantity == 0) {
      result["status"] = "fail";
      result["reason"] = "The food is not found in fridge";
      result["new_quantity"] = 0;
    } else {
      if (food_quantity >= quantity) {
        int current_intake = VF_list[index].get_intake();
        int new_intake = current_intake + quantity;
        int food_limit = VF_list[index].get_limit(user_bmi);
        if (new_intake <= food_limit) {
          double added_energy = quantity * VF_list[index].getEnergy();
          double new_energy = added_energy + calorie_intake;
          if (new_energy <= (calorie_max + 100)) {
            calorie_intake = new_energy;
            food_quantity -= quantity;
            double added_carbo = quantity * VF_list[index].getCarbo();
            double added_protein = quantity * VF_list[index].getProtein();
            double added_fat = quantity * VF_list[index].getFat();
            carbo_intake += added_carbo;
            protein_intake += added_protein;
            fat_intake += added_fat;
            VF_list[index].consume(quantity);
            VF_list[index].setFoodQuantity(food_quantity);
            result["status"] = "successful";
            result["reason"] = "successful";
            result["new_quantity"] = food_quantity;
          } else {
            result["status"] = "reject";
            result["reason"] = "Request number exceeds the calorie limit";
            int max_intake = (int)calorie_max;
            result["new_quantity"] = max_intake;
          }
        } else {
          result["status"] = "denied";
          result["reason"] = "Request number exceeds the item limit";
          result["new_quantity"] = food_limit;
        }
      } else {
        result["status"] = "fail";
        result["reason"] = "There is no enough food in fridge";
        result["new_quantity"] = food_quantity;
      }
    }
  } else if (type == "Snack") {
    int index;
    for (index = 0; index < Snacks_list.size(); index++) {
      if (name == Snacks_list[index].getFoodName())
        break;
    }
    int food_quantity = Snacks_list[index].getFoodQuantity();
    if (food_quantity == 0) {
      result["status"] = "fail";
      result["reason"] = "The food is not found in fridge";
      result["new_quantity"] = 0;
    } else {
      if (food_quantity >= quantity) {
        int current_intake = Snacks_list[index].get_intake();
        int new_intake = current_intake + quantity;
        int food_limit = Snacks_list[index].get_limit(user_bmi);
        if (new_intake <= food_limit) {
          double added_energy = quantity * Snacks_list[index].getEnergy();
          double new_energy = added_energy + calorie_intake;
          if (new_energy <= (calorie_max + 100)) {
            calorie_intake = new_energy;
            food_quantity -= quantity;
            double added_carbo = quantity * Snacks_list[index].getCarbo();
            double added_protein = quantity * Snacks_list[index].getProtein();
            double added_fat = quantity * Snacks_list[index].getFat();
            carbo_intake += added_carbo;
            protein_intake += added_protein;
            fat_intake += added_fat;
            Snacks_list[index].consume(quantity);
            Snacks_list[index].setFoodQuantity(food_quantity);
            result["status"] = "successful";
            result["reason"] = "successful";
            result["new_quantity"] = food_quantity;
          } else {
            result["status"] = "reject";
            result["reason"] = "Request number exceeds the calorie limit";
            int max_intake = (int)calorie_max;
            result["new_quantity"] = max_intake;
          }
        } else {
          result["status"] = "denied";
          result["reason"] = "Request number exceeds the limit";
          result["new_quantity"] = food_limit;
        }
      } else {
        result["status"] = "fail";
        result["reason"] = "There is no enough food in fridge";
        result["new_quantity"] = food_quantity;
      }
    }
  } else if (type == "Meat") {
    int index;
    for (index = 0; index < Meat_list.size(); index++) {
      if (name == Meat_list[index].getFoodName())
        break;
    }
    int food_quantity = Meat_list[index].getFoodQuantity();
    if (food_quantity == 0) {
      result["status"] = "fail";
      result["reason"] = "The food is not found in fridge";
      result["new_quantity"] = 0;
    } else {
      if (food_quantity >= quantity) {
        int current_intake = Meat_list[index].get_intake();
        int new_intake = current_intake + quantity;
        int food_limit = Meat_list[index].get_limit(user_bmi);
        if (new_intake <= food_limit) {
          double added_energy = quantity * Meat_list[index].getEnergy();
          double new_energy = added_energy + calorie_intake;
          if (new_energy <= (calorie_max + 100)) {
            calorie_intake = new_energy;
            food_quantity -= quantity;
            double added_carbo = quantity * Meat_list[index].getCarbo();
            double added_protein = quantity * Meat_list[index].getProtein();
            double added_fat = quantity * Meat_list[index].getFat();
            carbo_intake += added_carbo;
            protein_intake += added_protein;
            fat_intake += added_fat;
            Meat_list[index].consume(quantity);
            Meat_list[index].setFoodQuantity(food_quantity);
            result["status"] = "successful";
            result["reason"] = "successful";
            result["new_quantity"] = food_quantity;
          } else {
            result["status"] = "reject";
            result["reason"] = "Request number exceeds the calorie limit";
            int max_intake = (int)calorie_max;
            result["new_quantity"] = max_intake;
          }
        } else {
          result["status"] = "denied";
          result["reason"] = "Request number exceeds the limit";
          result["new_quantity"] = food_limit;
        }
      } else {
        result["status"] = "fail";
        result["reason"] = "There is no enough food in fridge";
        result["new_quantity"] = food_quantity;
      }
    }
  } else {
    result["status"] = "fail";
    result["reason"] = "Food Type does not match";
    result["new_quantity"] = 0;
  }

  if (result["status"].asString() == "successful") {
    sleep(1);
    grab_done();
  } else {
    sleep(1);
    grab_fail();
  }
  return result;
}

Json::Value fridge_server::Order_Food(const std::string &action,
    const std::string &name, int quantity, const std::string &type) {

  Json::Value result;
  Json::Value order_result;
  order_food();

  if (type == "Drink") {
    if ((quantity + drink_order) > 5) {
      order_result["status"] = "fail";
      order_result["reason"] = "You can only order 5 drinks per day";
      order_result["new_quantity"] = 0;
      return order_result;
    }
  } else if (type == "VF") {
    if ((quantity + vf_order) > 6) {
      order_result["status"] = "fail";
      order_result["reason"] = "You can only order 5 veggies or fruits per day";
      order_result["new_quantity"] = 0;
      return order_result;
    }
  } else if (type == "Snack") {
    if ((quantity + snack_order) > 5) {
      order_result["status"] = "fail";
      order_result["reason"] = "You can only order 5 snacks per day";
      order_result["new_quantity"] = 0;
      return order_result;
    }
  } else if (type == "Meat") {
    if ((quantity + meat_order) > 5) {
      order_result["status"] = "fail";
      order_result["reason"] = "You can only order 5 meat per day";
      order_result["new_quantity"] = 0;
      return order_result;
    }
  } else {
    order_result["status"] = "fail";
    order_result["reason"] = "Food type is wrong";
    order_result["new_quantity"] = 0;
    return order_result;
  }

  HttpClient httpclient("localhost:8302");
  grocery_client myClient(httpclient, JSONRPC_CLIENT_V2);
  try {
    result = myClient.Order_Food("order_food", name, quantity, type);
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }

  int food_index = -1;
  int type_index = 0;
  if (type == "Drink") {
    int index;
    for (index = 0; index < Drink_list.size(); index++) {
      if (name == Drink_list[index].getFoodName()) {
        food_index = index;
        type_index = 1;
        break;
      }
    }
  } else if (type == "VF") {
    int index;
    for (index = 0; index < VF_list.size(); index++) {
      if (name == VF_list[index].getFoodName()) {
        food_index = index;
        type_index = 2;
        break;
      }
    }
  } else if (type == "Snack") {
    int index;
    for (index = 0; index < Snacks_list.size(); index++) {
      if (name == Snacks_list[index].getFoodName()) {
        food_index = index;
        type_index = 3;
        break;
      }
    }
  } else if (type == "Meat") {
    int index;
    for (index = 0; index < Meat_list.size(); index++) {
      if (name == Meat_list[index].getFoodName()) {
        food_index = index;
        type_index = 4;
        break;
      }
    }
  }

  order_result["status"] = result["status"];
  order_result["reason"] = result["reason"];

  if (result["status"].asString() == "successful") {

    if (food_index != -1) {
      if (type_index == 1) {
        int food_quantity = Drink_list[food_index].getFoodQuantity();
        food_quantity += quantity;
        Drink_list[food_index].setFoodQuantity(food_quantity);
        order_result["new_quantity"] = food_quantity;
        drink_order += quantity;
        //std::cout << "Order successfully, now you have " << food_quantity << " " << name << " in the fridge" << std::endl;
      } else if (type_index == 2) {
        int food_quantity = VF_list[food_index].getFoodQuantity();
        food_quantity += quantity;
        VF_list[food_index].setFoodQuantity(food_quantity);
        order_result["new_quantity"] = food_quantity;
        vf_order += quantity;
        //std::cout << "Order successfully, now you have " << food_quantity << " " << name << " in the fridge" << std::endl;
      } else if (type_index == 3) {
        int food_quantity = Snacks_list[food_index].getFoodQuantity();
        food_quantity += quantity;
        Snacks_list[food_index].setFoodQuantity(food_quantity);
        order_result["new_quantity"] = food_quantity;
        snack_order += quantity;
        //std::cout << "Order successfully, now you have " << food_quantity << " " << name << " in the fridge" << std::endl;
      } else if (type_index == 4) {
        int food_quantity = Meat_list[food_index].getFoodQuantity();
        food_quantity += quantity;
        Meat_list[food_index].setFoodQuantity(food_quantity);
        order_result["new_quantity"] = food_quantity;
        meat_order += quantity;
        //std::cout << "Order successfully, now you have " << food_quantity << " " << name << " in the fridge" << std::endl;
      }
    } else {
      order_result["new_quantity"] = quantity;
      if (type == "Drink") {
        Drinks new_drink(result["size"].asString(), result["flavor"].asString(),
            name, quantity);
        new_drink.set_low_limit(result["limit_low"].asInt());
        new_drink.set_24_limit(result["limit_24"].asInt());
        new_drink.set_30_limit(result["limit_30"].asInt());
        new_drink.set_high_limit(result["limit_high"].asInt());
        new_drink.setEnergy(result["calorie"].asDouble());
        new_drink.setCarbo(result["carbo"].asDouble());
        new_drink.setProtein(result["protein"].asDouble());
        new_drink.setFat(result["fat"].asDouble());
        Drink_list.push_back(new_drink);
        drink_order += quantity;
      } else if (type == "VF") {
        Vegetable_or_Fruits new_VF(result["color"].asString(),
            result["size"].asString(), name, quantity);
        new_VF.set_low_limit(result["limit_low"].asInt());
        new_VF.set_24_limit(result["limit_24"].asInt());
        new_VF.set_30_limit(result["limit_30"].asInt());
        new_VF.set_high_limit(result["limit_high"].asInt());
        new_VF.setEnergy(result["calorie"].asDouble());
        new_VF.setCarbo(result["carbo"].asDouble());
        new_VF.setProtein(result["protein"].asDouble());
        new_VF.setFat(result["fat"].asDouble());
        VF_list.push_back(new_VF);
        vf_order += quantity;
      } else if (type == "Snack") {
        Snacks new_snack(result["size"].asString(), result["color"].asString(),
            result["flavor"].asString(), name, quantity);
        new_snack.set_low_limit(result["limit_low"].asInt());
        new_snack.set_24_limit(result["limit_24"].asInt());
        new_snack.set_30_limit(result["limit_30"].asInt());
        new_snack.set_high_limit(result["limit_high"].asInt());
        new_snack.setEnergy(result["calorie"].asDouble());
        new_snack.setCarbo(result["carbo"].asDouble());
        new_snack.setProtein(result["protein"].asDouble());
        new_snack.setFat(result["fat"].asDouble());
        Snacks_list.push_back(new_snack);
        snack_order += quantity;
      } else if (type == "Meat") {
        Meat new_meat(result["size"].asString(), name, quantity);
        new_meat.set_low_limit(result["limit_low"].asInt());
        new_meat.set_24_limit(result["limit_24"].asInt());
        new_meat.set_30_limit(result["limit_30"].asInt());
        new_meat.set_high_limit(result["limit_high"].asInt());
        new_meat.setEnergy(result["calorie"].asDouble());
        new_meat.setCarbo(result["carbo"].asDouble());
        new_meat.setProtein(result["protein"].asDouble());
        new_meat.setFat(result["fat"].asDouble());
        Meat_list.push_back(new_meat);
        meat_order += quantity;
      }
    }
  }
  order_done();
  return order_result;
}

int main() {

  s.StartListening();

  while (finish) {
    sleep(1);
  }
  s.StopListening();
  off_fridge();
  sleep(2);
  system("clear");
  return 0;
}
