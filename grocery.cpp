#include "food.cpp"
#include "food.h"
#include "grocery_server.h"
#include "grocery_system.cpp"
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
#include <queue>
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
list<std::string> Order_list;

class warehouse_server : public grocery_server {
  public:
  warehouse_server(
      jsonrpc::AbstractServerConnector &conn, jsonrpc::serverVersion_t type);
  virtual Json::Value Command(
      const std::string &action, const std::string &your_json);
  virtual Json::Value Order_Food(const std::string &action,
      const std::string &name, int quantity, const std::string &type);
};

warehouse_server::warehouse_server(
    AbstractServerConnector &connector, serverVersion_t type)
    : grocery_server(connector, type) {
}

HttpServer httpserver(8302);
warehouse_server s(
    httpserver, JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)

Json::Value warehouse_server::Command(
    const std::string &action, const std::string &your_json) {
  Json::Value result;
  result["response"] = "successful";
  return result;
}

Json::Value warehouse_server::Order_Food(const std::string &action,
    const std::string &name, int quantity, const std::string &type) {
  Json::Value result;

  int food_result = 0;
  int type_result = 0;
  if (type == "Drink") {
    int index;
    if (name == "Random") {
      int total_num = Drink_list.size();
      index = rand() % total_num;
      food_result = 1;
      result["status"] = Drink_list[index].getFoodName();
      result["size"] = Drink_list[index].getDrinkSize();
      result["flavor"] = Drink_list[index].getDrinkFlavor();
      result["limit_low"] = Drink_list[index].get_low_limit();
      result["limit_24"] = Drink_list[index].get_24_limit();
      result["limit_30"] = Drink_list[index].get_30_limit();
      result["limit_high"] = Drink_list[index].get_high_limit();
      result["calorie"] = Drink_list[index].getEnergy();
      result["carbo"] = Drink_list[index].getCarbo();
      result["protein"] = Drink_list[index].getProtein();
      result["fat"] = Drink_list[index].getFat();
    } else {
      for (index = 0; index < Drink_list.size(); index++) {
        if (name == Drink_list[index].getFoodName()) {
          food_result = 1;
          result["size"] = Drink_list[index].getDrinkSize();
          result["flavor"] = Drink_list[index].getDrinkFlavor();
          result["limit_low"] = Drink_list[index].get_low_limit();
          result["limit_24"] = Drink_list[index].get_24_limit();
          result["limit_30"] = Drink_list[index].get_30_limit();
          result["limit_high"] = Drink_list[index].get_high_limit();
          result["calorie"] = Drink_list[index].getEnergy();
          result["carbo"] = Drink_list[index].getCarbo();
          result["protein"] = Drink_list[index].getProtein();
          result["fat"] = Drink_list[index].getFat();
          break;
        }
      }
    }
  } else if (type == "VF") {
    int index;
    if (name == "Random") {
      int total_num = VF_list.size();
      index = rand() % total_num;
      food_result = 1;
      result["status"] = VF_list[index].getFoodName();
      result["size"] = VF_list[index].getVegSize();
      result["color"] = VF_list[index].getVegColor();
      result["limit_low"] = VF_list[index].get_low_limit();
      result["limit_24"] = VF_list[index].get_24_limit();
      result["limit_30"] = VF_list[index].get_30_limit();
      result["limit_high"] = VF_list[index].get_high_limit();
      result["calorie"] = VF_list[index].getEnergy();
      result["carbo"] = VF_list[index].getCarbo();
      result["protein"] = VF_list[index].getProtein();
      result["fat"] = VF_list[index].getFat();
    } else {
      for (index = 0; index < VF_list.size(); index++) {
        if (name == VF_list[index].getFoodName()) {
          food_result = 1;
          result["size"] = VF_list[index].getVegSize();
          result["color"] = VF_list[index].getVegColor();
          result["limit_low"] = VF_list[index].get_low_limit();
          result["limit_24"] = VF_list[index].get_24_limit();
          result["limit_30"] = VF_list[index].get_30_limit();
          result["limit_high"] = VF_list[index].get_high_limit();
          result["calorie"] = VF_list[index].getEnergy();
          result["carbo"] = VF_list[index].getCarbo();
          result["protein"] = VF_list[index].getProtein();
          result["fat"] = VF_list[index].getFat();
          break;
        }
      }
    }

  } else if (type == "Snack") {
    int index;
    if (name == "Random") {
      int total_num = Snacks_list.size();
      index = rand() % total_num;
      food_result = 1;
      result["status"] = Snacks_list[index].getFoodName();
      result["size"] = Snacks_list[index].getSnackSize();
      result["color"] = Snacks_list[index].getSnackColor();
      result["flavor"] = Snacks_list[index].getSnackFlavor();
      result["limit_low"] = Snacks_list[index].get_low_limit();
      result["limit_24"] = Snacks_list[index].get_24_limit();
      result["limit_30"] = Snacks_list[index].get_30_limit();
      result["limit_high"] = Snacks_list[index].get_high_limit();
      result["calorie"] = Snacks_list[index].getEnergy();
      result["carbo"] = Snacks_list[index].getCarbo();
      result["protein"] = Snacks_list[index].getProtein();
      result["fat"] = Snacks_list[index].getFat();
    } else {
      for (index = 0; index < Snacks_list.size(); index++) {
        if (name == Snacks_list[index].getFoodName()) {
          food_result = 1;
          result["size"] = Snacks_list[index].getSnackSize();
          result["color"] = Snacks_list[index].getSnackColor();
          result["flavor"] = Snacks_list[index].getSnackFlavor();
          result["limit_low"] = Snacks_list[index].get_low_limit();
          result["limit_24"] = Snacks_list[index].get_24_limit();
          result["limit_30"] = Snacks_list[index].get_30_limit();
          result["limit_high"] = Snacks_list[index].get_high_limit();
          result["calorie"] = Snacks_list[index].getEnergy();
          result["carbo"] = Snacks_list[index].getCarbo();
          result["protein"] = Snacks_list[index].getProtein();
          result["fat"] = Snacks_list[index].getFat();
          break;
        }
      }
    }

  } else if (type == "Meat") {
    int index;
    if (name == "Random") {
      int total_num = Meat_list.size();
      index = rand() % total_num;
      food_result = 1;
      result["status"] = Meat_list[index].getFoodName();
      result["size"] = Meat_list[index].getMeatSize();
      result["limit_low"] = Meat_list[index].get_low_limit();
      result["limit_24"] = Meat_list[index].get_24_limit();
      result["limit_30"] = Meat_list[index].get_30_limit();
      result["limit_high"] = Meat_list[index].get_high_limit();
      result["calorie"] = Meat_list[index].getEnergy();
      result["carbo"] = Meat_list[index].getCarbo();
      result["protein"] = Meat_list[index].getProtein();
      result["fat"] = Meat_list[index].getFat();

    } else {
      for (index = 0; index < Meat_list.size(); index++) {
        if (name == Meat_list[index].getFoodName()) {
          food_result = 1;
          result["size"] = Meat_list[index].getMeatSize();
          result["limit_low"] = Meat_list[index].get_low_limit();
          result["limit_24"] = Meat_list[index].get_24_limit();
          result["limit_30"] = Meat_list[index].get_30_limit();
          result["limit_high"] = Meat_list[index].get_high_limit();
          result["calorie"] = Meat_list[index].getEnergy();
          result["carbo"] = Meat_list[index].getCarbo();
          result["protein"] = Meat_list[index].getProtein();
          result["fat"] = Meat_list[index].getFat();
          break;
        }
      }
    }
  } else {
    result["status"] = "failed";
    result["reason"] = "Food type not matches";
    type_result = 1;
  }

  if (food_result) {
    new_message();
    default_system();
    std::string new_order;
    if (name == "Random") {
      new_order = type + " " + to_string(quantity) + " "
                  + result["status"].asString();
    } else {
      new_order = type + " " + to_string(quantity) + " " + name;
    }

    Order_list.push_back(new_order);
    if (name != "Random") {
      result["status"] = "successful";
    }
    result["reason"] = "successful";
  } else {
    result["status"] = "failed";
    if (!type_result) {
      result["reason"] = "Food cannot found in grocery";
    }
  }

  return result;
}

std::string print_food() {
  int drink_num = Drink_list.size();
  int vf_num = VF_list.size();
  int snack_num = Snacks_list.size();
  int meat_num = Meat_list.size();

  std::string food_string;

  for (int i = 0; i < drink_num; i++) {
    Drinks tem_drink = Drink_list[i];
    food_string += "\n";
    food_string += tem_drink.getDrinkFlavor();
    food_string += " ";
    food_string += tem_drink.getFoodName();
    food_string += " Unit: ";
    food_string += tem_drink.getDrinkSize();
    food_string += " Calorie: ";
    stringstream str_ss;
    str_ss << tem_drink.getEnergy();
    string food_energy = str_ss.str();
    food_string += food_energy;
  }

  for (int i = 0; i < vf_num; i++) {
    Vegetable_or_Fruits tem_vf = VF_list[i];
    food_string += "\n";
    food_string += tem_vf.getVegColor();
    food_string += " ";
    food_string += tem_vf.getFoodName();
    food_string += " Unit: ";
    food_string += tem_vf.getVegSize();
    food_string += " Calorie: ";
    stringstream str_ss;
    str_ss << tem_vf.getEnergy();
    string food_energy = str_ss.str();
    food_string += food_energy;
  }

  for (int i = 0; i < snack_num; i++) {
    Snacks tem_snack = Snacks_list[i];
    food_string += "\n";
    food_string += tem_snack.getSnackColor();
    food_string += " ";
    food_string += tem_snack.getSnackFlavor();
    food_string += " ";
    food_string += tem_snack.getFoodName();
    food_string += " Unit: ";
    food_string += tem_snack.getSnackSize();
    food_string += " Calorie: ";
    stringstream str_ss;
    str_ss << tem_snack.getEnergy();
    string food_energy = str_ss.str();
    food_string += food_energy;
  }

  for (int i = 0; i < meat_num; i++) {
    Meat tem_meat = Meat_list[i];
    food_string += "\n";
    food_string += tem_meat.getFoodName();
    food_string += " Unit: ";
    food_string += tem_meat.getMeatSize();
    food_string += " Calorie: ";
    stringstream str_ss;
    str_ss << tem_meat.getEnergy();
    string food_energy = str_ss.str();
    food_string += food_energy;
  }
  return food_string;
}

void print_order() {
  int order_size = Order_list.size();
  for (int i = 0; i < order_size; i++) {
    std::string tem_str = Order_list.front();
    Order_list.pop_front();
    std::cout << "Order No." << (i + 1) << ": " << tem_str << std::endl;
    Order_list.push_back(tem_str);
  }
  return;
}

int main() {
  system("clear");
  string grocery_list[3];
  grocery_list[0] = "warehouse/davis_store.txt";
  grocery_list[1] = "warehouse/santa_cruz_store.txt";
  grocery_list[2] = "warehouse/berkeley_store.txt";
  for (int i = 0; i < 3; i++) {
    ifstream ifile;
    string file_name = grocery_list[i];
    ifile.open(file_name, ios::in);
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
          double calorie;
          double carbo;
          double protein;
          double fat;
          ifile >> size;
          ifile >> flavor;
          ifile >> food_name;
          Drinks tem_drink(size, flavor, food_name, 999999);
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
          double calorie;
          double carbo;
          double protein;
          double fat;
          ifile >> color;
          ifile >> size;
          ifile >> food_name;
          Vegetable_or_Fruits tem_veg(color, size, food_name, 999999);
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
          double calorie;
          double carbo;
          double protein;
          double fat;
          ifile >> size;
          ifile >> color;
          ifile >> flavor;
          ifile >> food_name;
          Snacks tem_snack(size, color, flavor, food_name, 999999);
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
          double calorie;
          double carbo;
          double protein;
          double fat;
          ifile >> size;
          ifile >> food_name;
          Meat tem_meat(size, food_name, 999999);
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
    ifile.close();
  }

  s.StartListening();

  bool system_continue = true;
  while (system_continue) {
    system("clear");
    default_system();
    string grocery_command;
    std::cin >> grocery_command;
    if (grocery_command == "A") {
      std::cout << print_food() << "\n" << std::endl;
      std::string check_continue;
      std::cout << "Enter anything to continue:";
      std::cin >> check_continue;
    } else if (grocery_command == "B") {
      std::cout << std::endl;
      print_order();
      std::string check_continue;
      std::cout << "\nEnter anything to continue:";
      std::cin >> check_continue;
    } else if (grocery_command == "Q") {
      system_continue = false;
      std::cout << "System Turn Off" << std::endl;
      std::cout << "Byebye" << std::endl;
      loading(3);
      loading(2);
      loading(1);
      system("clear");
    } else {
      std::cout << "Invaild Command, Jumo to homepage" << std::endl;
      loading(3);
      loading(2);
      loading(1);
    }
  }

  s.StartListening();
  return 0;
}