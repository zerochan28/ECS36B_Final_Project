#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <strings.h>
#include <iomanip>
#include <cstdlib>
#include <stdbool.h>
#include <sstream>
#include <ctime>
#include <exception>
#include <unistd.h> 
#include <time.h>
#include <list>
#include <cstring>
#include <fstream>
#include <vector>
#include <jsonrpccpp/server/connectors/httpserver.h>
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <jsonrpccpp/server.h>
#include "report_client.h"
#include "grocery_client.h"
#include "report_server.h"
#include "fridge_design.cpp"
#include "food.cpp"
#include "food.h"

using namespace jsonrpc;
using namespace std;


vector <Drinks> Drink_list;
vector <Vegetable_or_Fruits> VF_list;
vector <Snacks> Snacks_list;
vector <Meat> Meat_list;
int finish = 1;
void default_fridge();
void check_food();
void check_done();
void off_fridge();


std::string print_food(){
    int drink_num = Drink_list.size();
    int vf_num = VF_list.size();
    int snack_num = Snacks_list.size();
    int meat_num = Meat_list.size();

    std::string food_string;

    for(int i = 0; i < drink_num; i++) {
        Drinks tem_drink = Drink_list[i];
        food_string += "\n";
        food_string += tem_drink.getDrinkFlavor();
        food_string += " ";
        food_string += tem_drink.getFoodName();
        food_string += " ";
        food_string += to_string(tem_drink.getFoodQuantity());
        food_string += " ";
        food_string += tem_drink.getDrinkSize();
    }

    for(int i = 0; i < vf_num; i++) {
        Vegetable_or_Fruits tem_vf = VF_list[i];
        food_string += "\n";
        food_string += tem_vf.getVegColor();
        food_string += " ";
        food_string += tem_vf.getFoodName();
        food_string += " ";
        food_string += to_string(tem_vf.getFoodQuantity());
        food_string += " ";
        food_string += tem_vf.getVegSize();
    }

    for(int i = 0; i < snack_num; i++) {
        Snacks tem_snack = Snacks_list[i];
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
    }

    for(int i = 0; i < meat_num; i++) {
        Meat tem_meat = Meat_list[i];
        food_string += "\n";
        food_string += tem_meat.getFoodName();
        food_string += " ";
        food_string += to_string(tem_meat.getFoodQuantity());
        food_string += " ";
        food_string += tem_meat.getMeatSize();
    }
    return food_string;
}

class fridge_server : public report_server
{
public:
  fridge_server(jsonrpc::AbstractServerConnector &conn, jsonrpc::serverVersion_t type);
  virtual Json::Value FoodReport(const std::string& action, const std::string& your_json);
  virtual Json::Value Get_Food(const std::string& action, const std::string& name, int quantity, const std::string& type);
  virtual Json::Value Order_Food(const std::string& action, const std::string& name, int quantity, const std::string& type);
};

fridge_server::fridge_server(AbstractServerConnector &connector, serverVersion_t type): report_server(connector, type)
{

}


HttpServer httpserver(8300);
fridge_server s(httpserver, JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
// member functions

Json::Value
fridge_server::FoodReport
(const std::string& action, const std::string& your_json)
{
  Json::Value result;
  std::string command = your_json;
  if(command == "Check"){
    std::string food_list = print_food();
    result["response"] = food_list;
    check_food();
    sleep(3);
    check_done();
  } else if(command == "Quit"){
      finish=0;
      result["response"] = "successful";
  } else if(command == "Open"){
      std::cout << "\n\n         Smart Fridge Starting Up.....\n" << std::endl;
      sleep(2);
      result["response"] = "successful";
      default_fridge();
  }

  return result;
}

Json::Value
fridge_server::Get_Food
(const std::string& action, const std::string& name, int quantity, const std::string& type){
    
    Json::Value result;
    grab_food();
    if(type == "Drink"){
        int index;
        for(index = 0; index < Drink_list.size(); index++){
            if(name == Drink_list[index].getFoodName()){
                break;
            }
        }
        int food_quantity = Drink_list[index].getFoodQuantity();
        if(food_quantity >= quantity){
            food_quantity -= quantity;
            Drink_list[index].setFoodQuantity(food_quantity);
            result["status"] = "successful";
            result["reason"] = "successful";
            result["new_quantity"] = food_quantity;
        } else {
            result["status"] = "fail";
            result["reason"] = "There is no enough food in fridge";
            result["new_quantity"] = food_quantity;
        }
    } else if(type == "VF"){
        int index;
        for(index = 0; index < VF_list.size(); index++){
            if(name == VF_list[index].getFoodName()) break;
        }
        int food_quantity = VF_list[index].getFoodQuantity();
        if(food_quantity >= quantity){
            food_quantity -= quantity;
            VF_list[index].setFoodQuantity(food_quantity);
            result["status"] = "successful";
            result["reason"] = "successful";
            result["new_quantity"] = food_quantity;
        } else {
            result["status"] = "fail";
            result["reason"] = "There is no enough food in fridge";
            result["new_quantity"] = food_quantity;
        }
    } else if(type == "Snack"){
        int index;
        for(index = 0; index < Snacks_list.size(); index++){
            if(name == Snacks_list[index].getFoodName()) break;
        }
        int food_quantity = Snacks_list[index].getFoodQuantity();
        if(food_quantity >= quantity){
            food_quantity -= quantity;
            Snacks_list[index].setFoodQuantity(food_quantity);
            result["status"] = "successful";
            result["reason"] = "successful";
            result["new_quantity"] = food_quantity;
        } else {
            result["status"] = "fail";
            result["reason"] = "There is no enough food in fridge";
            result["new_quantity"] = food_quantity;
        }
    } else if(type == "Meat"){
        int index;
        for(index = 0; index < Meat_list.size(); index++){
            if(name == Meat_list[index].getFoodName()) break;
        }
        int food_quantity = Meat_list[index].getFoodQuantity();
        if(food_quantity >= quantity){
            food_quantity -= quantity;
            Meat_list[index].setFoodQuantity(food_quantity);
            result["status"] = "successful";
            result["reason"] = "successful";
            result["new_quantity"] = food_quantity;
        } else {
            result["status"] = "fail";
            result["reason"] = "There is no enough food in fridge";
            result["new_quantity"] = food_quantity;
        }
    }
    if(result["status"].asString()=="successful"){
        sleep(3);
        grab_done();
    } else {
        sleep(3);
        grab_fail();
    }
    return result;
}

Json::Value
fridge_server::Order_Food
(const std::string& action, const std::string& name, int quantity, const std::string& type){
    
    Json::Value result;
    Json::Value order_result;
    order_food();
    std::cout << "Order Received" << type << " " << quantity << " " << name << std::endl;
    
    HttpClient httpclient("localhost:8302");
    grocery_client myClient(httpclient, JSONRPC_CLIENT_V2);
    try {
        result = myClient.Order_Food("order_food", name, quantity, type);
        if(result["status"].asString() == "successful"){
            std::cout << "Order successfully, now you have " << name << " in the fridge" << std::endl;
        } else {
            std::cout << "Order failed, because " << result["reason"] << std::endl;
        }
    } catch (JsonRpcException &e) {
        cerr << e.what() << endl;
    }

    int food_index = -1;
    int type_index = 0;
    if(type == "Drink"){
        int index;
        for(index = 0; index < Drink_list.size(); index++){
            if(name == Drink_list[index].getFoodName()){
                food_index = index;
                type_index = 1;
                break;
            }
        }
    } else if(type == "VF"){
        int index;
        for(index = 0; index < VF_list.size(); index++){
            if(name == VF_list[index].getFoodName()){
                food_index = index;
                type_index = 2;
                break;
            }
        }
    } else if(type == "Snack"){
        int index;
        for(index = 0; index < Snacks_list.size(); index++){
            if(name == Snacks_list[index].getFoodName()){
                food_index = index;
                type_index = 3;
                break;
            }
        }
    } else if(type == "Meat"){
        int index;
        for(index = 0; index < Meat_list.size(); index++){
            if(name == Meat_list[index].getFoodName()){
                food_index = index;
                type_index = 4;
                break;
            }
        }
    }

    order_result["status"] = result["status"];
    order_result["reason"] = result["reason"];

    if(result["status"].asString() == "successful"){
        
        if(food_index != -1){
            if(type_index == 1){
               int food_quantity = Drink_list[food_index].getFoodQuantity();
               food_quantity += quantity;
               Drink_list[food_index].setFoodQuantity(food_quantity);
               order_result["new_quantity"] = food_quantity;
               //std::cout << "Order successfully, now you have " << food_quantity << " " << name << " in the fridge" << std::endl;
            } else if(type_index == 2){
               int food_quantity = VF_list[food_index].getFoodQuantity();
               food_quantity += quantity;
               VF_list[food_index].setFoodQuantity(food_quantity);
               order_result["new_quantity"] = food_quantity;
               //std::cout << "Order successfully, now you have " << food_quantity << " " << name << " in the fridge" << std::endl;
            } else if(type_index == 3){
               int food_quantity = Snacks_list[food_index].getFoodQuantity();
               food_quantity += quantity;
               Snacks_list[food_index].setFoodQuantity(food_quantity);
               order_result["new_quantity"] = food_quantity;
               //std::cout << "Order successfully, now you have " << food_quantity << " " << name << " in the fridge" << std::endl;
            } else if(type_index == 4){
               int food_quantity = Meat_list[food_index].getFoodQuantity();
               food_quantity += quantity;
               Meat_list[food_index].setFoodQuantity(food_quantity);
               order_result["new_quantity"] = food_quantity;
               //std::cout << "Order successfully, now you have " << food_quantity << " " << name << " in the fridge" << std::endl;
            }
        } else {
            order_result["new_quantity"] = quantity;
            if(type == "Drink"){
                Drinks new_drink(result["size"].asString(),result["flavor"].asString(),name,quantity);
                Drink_list.push_back(new_drink);
            } else if(type == "VF"){
                Vegetable_or_Fruits new_VF(result["color"].asString(),result["size"].asString(),name,quantity);
                VF_list.push_back(new_VF);
            } else if(type == "Snacks"){
                Snacks new_snack(result["size"].asString(),result["color"].asString(),result["flavor"].asString(),name,quantity);
                Snacks_list.push_back(new_snack);
            } else if(type == "Meat"){
                Meat new_meat(result["size"].asString(),name,quantity);
                Meat_list.push_back(new_meat);
            }
        }
    }
    order_done();
    return order_result;
}


int main() {

    ifstream ifile;
    ifile.open("food/food.txt", ios::in);
    if(ifile){
        int number_foods;
        ifile >> number_foods;
        for(int i=0; i < number_foods; i++){
            std::string food_type;
            ifile >> food_type;
            if(food_type == "Drinks"){
                std::string size;
                std::string flavor;
                std::string food_name;
                unsigned int quantity;
                ifile >> size;
                ifile >> flavor;
                ifile >> food_name;
                ifile >> quantity;
                Drinks tem_drink(size,flavor,food_name,quantity);
                //std::cout << size << " " << flavor << " " << food_name << " " << quantity << std::endl;
                Drink_list.push_back(tem_drink);
            } else if(food_type == "VF"){
                std::string color;
                std::string size;
                std::string food_name;
                unsigned int quantity;
                ifile >> color;
                ifile >> size;
                ifile >> food_name;
                ifile >> quantity;
                Vegetable_or_Fruits tem_veg(color,size,food_name,quantity);
                //std::cout << color << " " << size << " " << food_name << " " << quantity << std::endl;
                VF_list.push_back(tem_veg);
            } else if(food_type == "Snacks"){
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
                Snacks tem_snack(size,color,flavor,food_name,quantity);
                //std::cout << size << " " << color << " " << flavor << " " << food_name << " " << quantity << std::endl;
                Snacks_list.push_back(tem_snack);
            } else if(food_type == "Meat"){
                std::string size;
                std::string food_name;
                unsigned int quantity;
                ifile >> size;
                ifile >> food_name;
                ifile >> quantity;
                Meat tem_meat(size, food_name, quantity);
                //std::cout << size << " " << food_name << " " << quantity << std::endl;
                Meat_list.push_back(tem_meat);
            }
        }
    }

    s.StartListening();

    while(finish){

    }
    sleep(1);
    s.StopListening();
    off_fridge();
    sleep(3);
    system("clear");
    return 0;
}
