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
#include <queue>
#include <jsonrpccpp/server/connectors/httpserver.h>
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <jsonrpccpp/server.h>
#include "food.cpp"
#include "food.h"
#include "grocery_server.h"
#include "grocery_system.cpp"

using namespace jsonrpc;
using namespace std;

vector <Drinks> Drink_list;
vector <Vegetable_or_Fruits> VF_list;
vector <Snacks> Snacks_list;
vector <Meat> Meat_list;
list <std::string> Order_list;

class warehouse_server : public grocery_server
{
public:
  warehouse_server(jsonrpc::AbstractServerConnector &conn, jsonrpc::serverVersion_t type);
  virtual Json::Value Command(const std::string& action, const std::string& your_json);
  virtual Json::Value Order_Food(const std::string& action, const std::string& name, int quantity, const std::string& type);
};

warehouse_server::warehouse_server(AbstractServerConnector &connector, serverVersion_t type): grocery_server(connector, type)
{

}

HttpServer httpserver(8302);
warehouse_server s(httpserver, JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)

Json::Value
warehouse_server::Command
(const std::string& action, const std::string& your_json)
{
    Json::Value result;
    result["response"] = "successful";
    return result;
}

Json::Value
warehouse_server::Order_Food
(const std::string& action, const std::string& name, int quantity, const std::string& type)
{
    Json::Value result;
    int food_result = 0;
    int type_result = 0;
    if(type == "Drink"){
        int index;
        for(index = 0; index < Drink_list.size(); index++){
            if(name == Drink_list[index].getFoodName()){
                food_result=1;
                result["size"]=Drink_list[index].getDrinkSize();
                result["flavor"]=Drink_list[index].getDrinkFlavor();
                break;
            }
        }
    } else if(type == "VF"){
        int index;
        for(index = 0; index < VF_list.size(); index++){
            if(name == VF_list[index].getFoodName()){
                food_result=1;
                result["size"]=VF_list[index].getVegSize();
                result["color"]=VF_list[index].getVegColor();
                break;
            }
        }
    } else if(type == "Snack"){
        int index;
        for(index = 0; index < Snacks_list.size(); index++){
            if(name == Snacks_list[index].getFoodName()){
                food_result=1;
                result["size"]=Snacks_list[index].getSnackSize();
                result["color"]=Snacks_list[index].getSnackColor();
                result["flavor"]=Snacks_list[index].getSnackFlavor();
                break;
            }
        }
    } else if(type == "Meat"){
        int index;
        for(index = 0; index < Meat_list.size(); index++){
            if(name == Meat_list[index].getFoodName()){
                food_result=1;
                result["size"]=Meat_list[index].getMeatSize();
                break;
            }
        }
    } else {
        result["status"] = "failed";
        result["reason"] = "Food type not matches";
        type_result = 1;
    }

    if(food_result){
        new_message();
        default_system();
        std::string new_order = type +" " + to_string(quantity) + " " + name;
        Order_list.push_back(new_order);
        result["status"] = "successful";
        result["reason"] = "successful";
    } else {
        result["status"] = "failed";
        if(!type_result){
            result["reason"] = "Food cannot found in grocery";
        }
        
    }

    return result;
}


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

void print_order(){
    int order_size = Order_list.size();
    for(int i = 0; i < order_size; i++){
        std::string tem_str = Order_list.front();
        Order_list.pop_front();
        std::cout << "Order No." << (i+1) << ": "<< tem_str << std::endl;
        Order_list.push_back(tem_str);
    }
    return;
}


int main(){
    system("clear");
    ifstream ifile;
    ifile.open("warehouse/goods.txt", ios::in);
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
                ifile >> size;
                ifile >> flavor;
                ifile >> food_name;
                Drinks tem_drink(size,flavor,food_name,999999);
                //std::cout << size << " " << flavor << " " << food_name << " " << quantity << std::endl;
                Drink_list.push_back(tem_drink);
            } else if(food_type == "VF"){
                std::string color;
                std::string size;
                std::string food_name;
                ifile >> color;
                ifile >> size;
                ifile >> food_name;
                Vegetable_or_Fruits tem_veg(color,size,food_name,999999);
                //std::cout << color << " " << size << " " << food_name << " " << quantity << std::endl;
                VF_list.push_back(tem_veg);
            } else if(food_type == "Snacks"){
                std::string size;
                std::string color;
                std::string flavor;
                std::string food_name;
                ifile >> size;
                ifile >> color;
                ifile >> flavor;
                ifile >> food_name;
                Snacks tem_snack(size,color,flavor,food_name,999999);
                //std::cout << size << " " << color << " " << flavor << " " << food_name << " " << quantity << std::endl;
                Snacks_list.push_back(tem_snack);
            } else if(food_type == "Meat"){
                std::string size;
                std::string food_name;
                ifile >> size;
                ifile >> food_name;
                Meat tem_meat(size, food_name, 999999);
                //std::cout << size << " " << food_name << " " << quantity << std::endl;
                Meat_list.push_back(tem_meat);
            }
        }
    }

    

    s.StartListening();

    bool system_continue = true;
    while(system_continue){
        system("clear");
        default_system();
        string grocery_command;
        std::cin >> grocery_command;
        if(grocery_command == "A"){
            std::cout << print_food() << "\n" << std::endl;
            std::string check_continue;
            std::cout << "Enter anything to continue:";
            std::cin >> check_continue;
        } else if(grocery_command == "B"){
            std::cout << std::endl;
            print_order();
            std::string check_continue;
            std::cout << "\nEnter anything to continue:";
            std::cin >> check_continue;
        } else if(grocery_command == "Q"){
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