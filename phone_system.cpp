#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <strings.h>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include <exception>
#include <unistd.h> 
#include <time.h>
#include <fstream>
#include <jsonrpccpp/server/connectors/httpserver.h>
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <jsonrpccpp/server.h>
#include "report_client.h"
#include "report_server.h"
#include "Person.cpp"
#include "Person.h"

using namespace jsonrpc;
using namespace std;

void loading(int num){
    sleep(1);
    std::cout << num << "..." << std::endl;
    return;
}

void all_set(){
    std::cout << "\nYou are all set, loading the smart configuration for you" << std::endl;
    loading(3);
    loading(2);
    loading(1);
    std::cout << "Loading Successfully" << std::endl;
    sleep(3);
    system("clear");
}


void send_command(std::string command){

    HttpClient httpclient("localhost:8300");
    report_client myClient(httpclient, JSONRPC_CLIENT_V2);
    std::string report_command;
    Json::Value result;

    report_command = command;

    try {
        result = myClient.FoodReport("food report", report_command);
        if(command == "Check"){
            std::cout << "Here, is the food list in Smart Fridge" << std::endl;
            std::string food_list= result["response"].asString();
            std::cout << food_list << "\n" << std::endl;
        }
    } catch (JsonRpcException &e) {
        cerr << e.what() << endl;
    }

}

void Get_Food(){
    std::string food_name;
    std::string food_type;
    int pick_num;

    std::cout << "Enter the type of food (Drink/VF/Snack/Meat): ";
    std::cin >> food_type;
    std::cout << "Enter the name of food: ";
    std::cin >> food_name;
    std::cout << "Enter the quantity you want to pick up: ";
    std::cin >> pick_num;

    HttpClient httpclient("localhost:8300");
    report_client myClient(httpclient, JSONRPC_CLIENT_V2);
    Json::Value result;
    try {
        result = myClient.Get_Food("food report", food_name, pick_num, food_type);
        if(result["status"].asString() == "successful"){
            std::cout << "Pick up successfully, now you have " << result["new_quantity"].asString() << " " << food_name << " in the fridge" << std::endl;
        } else {
            std::cout << "Pick up failed, because " << result["reason"] << std::endl;
        }
    } catch (JsonRpcException &e) {
        cerr << e.what() << endl;
    }
    return;
}

void Order_Food(){
    std::string food_name;
    std::string food_type;
    int pick_num;

    std::cout << "Enter the type of food (Drink/VF/Snack/Meat): ";
    std::cin >> food_type;
    std::cout << "Enter the name of food: ";
    std::cin >> food_name;
    std::cout << "Enter the quantity you want to pick up: ";
    std::cin >> pick_num;

    HttpClient httpclient("localhost:8300");
    report_client myClient(httpclient, JSONRPC_CLIENT_V2);
    Json::Value result;
    try {
        result = myClient.Order_Food("food report", food_name, pick_num, food_type);
        if(result["status"].asString() == "successful"){
            std::cout << "Order successfully, now you have " << result["new_quantity"].asString() << " " << food_name << " in the fridge" << std::endl;
        } else {
            std::cout << "Order failed, because " << result["reason"] << std::endl;
        }
    } catch (JsonRpcException &e) {
        cerr << e.what() << endl;
    }
    return;

}

Person load_user(Person user){
    ifstream ifile;
    std::string file_name = "user/" + user.getPersonName() + ".txt";
    ifile.open(file_name, ios::in);
    std::string data;
    int user_age;
    double user_height;
    double user_weight;
    std::string user_phone;
    std::string user_address;
    
    ifile >> data;
    user.setPersonName(data);
    ifile >> user_age;
    user.setPersonAge(user_age);
    ifile >> user_height;
    user.setPersonHeight(user_height);
    ifile >> user_weight;
    user.setPersonWeight(user_weight);
    ifile >> user_phone;
    user.setPersonPhone(user_phone);
    ifile >> user_address;
    user.setPersonAddress(user_address);
    
    ifile.close();
    return user;
}


Person new_user(Person user) {
    ofstream user_file;
    std::string file_name = "user/" + user.getPersonName() + ".txt";
    user_file.open(file_name, ios::out);

    user_file << user.getPersonName() << endl;
    int user_age;
    double user_height;
    double user_weight;
    std::string user_phone;
    std::string user_address;
    
    std::cout << "Welcome " << user.getPersonName() << " :) "<< std::endl;
    std::cout << "Please follow the instruction to finish setting\n" << std::endl;
    std::cout << "Enter Your Age" << std::endl;
    std::cin >> user_age;
    user.setPersonAge(user_age);
    user_file << user.getPersonAge() << endl;
    std::cout << "Enter Your Height (inch)" << std::endl;
    std::cin >> user_height;
    user.setPersonHeight(user_height);
    user_file << user.getPersonHeight() << endl;
    std::cout << "Enter Your Weight (kg)" << std::endl;
    std::cin >> user_weight;
    user.setPersonWeight(user_weight);
    user_file << user.getPersonWeight() << endl;
    std::cout << "Enter Your Phone number" << std::endl;
    std::cin >> user_phone;
    user.setPersonPhone(user_phone);
    user_file << user.getPersonPhone() << endl;
    std::cout << "Enter Your Address" << std::endl;
    std::cin >> user_address;
    user.setPersonAddress(user_address);
    user_file << user.getPersonAddress() << endl;
    
    user_file.close();
    return user;

}

Person change_user(Person user) {
    ofstream user_file;
    std::string file_name = "user/" + user.getPersonName() + ".txt";
    user_file.open(file_name, ios::out);

    user_file << user.getPersonName() << endl;
    int user_age;
    double user_height;
    double user_weight;
    std::string user_phone;
    std::string user_address;
    
    std::cout << "Please follow the instruction to change your profile\n" << std::endl;
    std::cout << "Enter Your Age" << std::endl;
    std::cin >> user_age;
    user.setPersonAge(user_age);
    user_file << user.getPersonAge() << endl;
    std::cout << "Enter Your Height (inch)" << std::endl;
    std::cin >> user_height;
    user.setPersonHeight(user_height);
    user_file << user.getPersonHeight() << endl;
    std::cout << "Enter Your Weight (kg)" << std::endl;
    std::cin >> user_weight;
    user.setPersonWeight(user_weight);
    user_file << user.getPersonWeight() << endl;
    std::cout << "Enter Your Phone number" << std::endl;
    std::cin >> user_phone;
    user.setPersonPhone(user_phone);
    user_file << user.getPersonPhone() << endl;
    std::cout << "Enter Your Address" << std::endl;
    std::cin >> user_address;
    user.setPersonAddress(user_address);
    user_file << user.getPersonAddress() << endl;
    
    user_file.close();
    return user;

}

void fridge_interface(){
    std::cout << "\n--------------------------------------------------" << std::endl;
    std::cout << "---------------Smart Fridge System----------------" << std::endl;
    std::cout << "-                                                -" << std::endl;
    std::cout << "-                                                -" << std::endl;
    std::cout << "-           Get: Get the food in fridge          -" << std::endl;
    std::cout << "-           Update: Update your profile          -" << std::endl;
    std::cout << "-         Check: Check the food in fridge        -" << std::endl;
    std::cout << "-        Next: Pick the food for next meal       -" << std::endl;
    std::cout << "-        Order: Order the food from Grocery      -" << std::endl;
    std::cout << "-        Quit: Quit the Smart Fridge System      -" << std::endl;
    std::cout << "-                                                -" << std::endl;
    std::cout << "-                                                -" << std::endl;
    std::cout << "--------------------------------------------------\n" << std::endl;
    return;
}
