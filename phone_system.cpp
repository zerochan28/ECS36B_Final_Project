#include "Person.cpp"
#include "Person.h"
#include "report_client.h"
#include "report_server.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <jsonrpccpp/server.h>
#include <jsonrpccpp/server/connectors/httpserver.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <strings.h>
#include <time.h>
#include <unistd.h>

using namespace jsonrpc;
using namespace std;

void loading(int num) {
  sleep(1);
  std::cout << num << "..." << std::endl;
  return;
}

void all_set() {
  std::cout << "\nYou are all set, loading the smart configuration for you"
            << std::endl;
  loading(3);
  loading(2);
  loading(1);
  std::cout << "Loading Successfully" << std::endl;
  sleep(3);
  system("clear");
}

void open_fridge(double bmi) {
  HttpClient httpclient("localhost:8300");
  report_client myClient(httpclient, JSONRPC_CLIENT_V2);
  Json::Value result;

  try {
    result = myClient.FoodReport("Open", bmi);
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
}

void age_report(int age) {
  HttpClient httpclient("localhost:8300");
  report_client myClient(httpclient, JSONRPC_CLIENT_V2);
  Json::Value result;

  double report_age = (double)age;

  try {
    result = myClient.FoodReport("Age", report_age);
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
}

void send_command(std::string command) {

  HttpClient httpclient("localhost:8300");
  report_client myClient(httpclient, JSONRPC_CLIENT_V2);
  std::string report_command;
  Json::Value result;

  report_command = command;

  try {
    result = myClient.FoodReport(report_command, 0);
    if (command == "Check") {
      std::cout << "Here, is the food list in Smart Fridge" << std::endl;
      std::string food_list = result["response"].asString();
      std::cout << food_list << "\n" << std::endl;
    } else if (command == "Next") {
      std::cout << result["response"].asString();
    }
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
}

void Get_Food() {
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
    if (result["status"].asString() == "successful") {
      std::cout << "Pick up successfully, now you have "
                << result["new_quantity"].asString() << " " << food_name
                << " in the fridge" << std::endl;
    } else if (result["status"].asString() == "fail") {
      std::cout << "Pick up failed, because " << result["reason"] << std::endl;
    } else if (result["status"].asString() == "denied") {
      std::cout << "Pick up denied by smart fridge, you can only take "
                << result["new_quantity"].asString() << " serving per day"
                << std::endl;
    } else {
      std::cout << "Pick up denied by smart fridge, you can only take "
                << result["new_quantity"].asString()
                << " calorie per day. STOP EATING!" << std::endl;
    }
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  return;
}

void Order_Food() {
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
    if (result["status"].asString() == "successful") {
      std::cout << "Order successfully, now you have "
                << result["new_quantity"].asString() << " " << food_name
                << " in the fridge" << std::endl;
    } else {
      std::cout << "Order failed, because " << result["reason"] << std::endl;
    }
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  return;
}

Person load_user(Person user) {
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

  std::cout << "Welcome " << user.getPersonName() << " :) " << std::endl;
  std::cout << "Please follow the instruction to update setting\n" << std::endl;
  std::cout << "Enter Your Age: ";
  while (!(std::cin >> user_age)) {
    std::cout << "Please enter a valid input" << std::endl;
    std::cout << "Enter Your Age: ";
    std::cin.clear();
    std::cin.ignore(100000, '\n');
  }
  while (user_age <= 0) {
    std::cout << "Please enter a valid age: " << std::endl;
    while (!(std::cin >> user_age)) {
      std::cout << "please enter valid input:" << std::endl;
      std::cin.clear();
      std::cin.ignore(1000000, '\n');
    }
    std::cin.clear();
    std::cin.ignore(100000, '\n');
  }
  if (user_age < 21) {
    std::cout << "The age you entered indicates you are under 21, the smart "
                 "fridge will not allow you to consume alcholic drinks"
              << std::endl;
  }

  user.setPersonAge(user_age);
  user_file << user.getPersonAge() << endl;
  std::cout << "Enter Your Height (inch): ";
  while (!(std::cin >> user_height)) {
    std::cout << "Please enter a valid input" << std::endl;
    std::cout << "Enter Your Height(inch): ";
    std::cin.clear();
    std::cin.ignore(100000, '\n');
  }
  while (user_height <= 0 || user_height >= 100) {
    std::cout << "Please enter a valid height: ";
    while (!(std::cin >> user_height)) {
      std::cout << "please enter valid input:" << std::endl;
      std::cin.clear();
      std::cin.ignore(1000000, '\n');
    }
    std::cin.clear();
    std::cin.ignore(100000, '\n');
  }
  user.setPersonHeight(user_height);
  user_file << user.getPersonHeight() << endl;

  std::cout << "Enter Your Weight (kg): ";
  while (!(std::cin >> user_weight)) {
    std::cout << "Please enter a valid input" << std::endl;
    std::cout << "Enter Your Weight(kg): ";
    std::cin.clear();
    std::cin.ignore(100000, '\n');
  }
  while (user_weight <= 0) {
    std::cout << "Enter a valid weight(kg): ";
    while (!(std::cin >> user_weight)) {
      std::cout << "please enter valid input:" << std::endl;
      std::cin.clear();
      std::cin.ignore(1000000, '\n');
    }
    std::cin.clear();
    std::cin.ignore(100000, '\n');
  }
  user.setPersonWeight(user_weight);
  user_file << user.getPersonWeight() << endl;
  std::cout << "Enter Your Phone number: ";
  while (!(std::cin >> user_phone)) {
    std::cout << "Please enter a valid input" << std::endl;
    std::cout << "Enter Your Phone number ";
    std::cin.clear();
    std::cin.ignore(100000, '\n');
  }
  while (user_phone.size() <= 9) {
    std::cout << "Enter a valid Phone number: ";
    while (!(std::cin >> user_phone)) {
      std::cout << "please enter valid input:" << std::endl;
      std::cin.clear();
      std::cin.ignore(1000000, '\n');
    }
    std::cin.clear();
    std::cin.ignore(100000, '\n');
  }

  user.setPersonPhone(user_phone);
  user_file << user.getPersonPhone() << endl;
  std::cout << "Enter Your Address: ";
  while (!(std::cin >> user_address)) {
    std::cout << "Please enter a valid input" << std::endl;
    std::cout << "Enter Your Address ";
    std::cin.clear();
    std::cin.ignore(100000, '\n');
  }
  while (user_address.size() <= 3) {
    std::cout << "Enter a valid Address: ";
    while (!(std::cin >> user_address)) {
      std::cout << "please enter valid input:" << std::endl;
      std::cin.clear();
      std::cin.ignore(1000000, '\n');
    }
    std::cin.clear();
    std::cin.ignore(100000, '\n');
  }

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

  std::cout << "Welcome " << user.getPersonName() << " :) " << std::endl;
  std::cout << "Please follow the instruction to update setting\n" << std::endl;
  std::cout << "Enter Your Age: ";
  while (!(std::cin >> user_age)) {
    std::cout << "Please enter a valid input" << std::endl;
    std::cout << "Enter Your Age: ";
    std::cin.clear();
    std::cin.ignore(100000, '\n');
  }
  while (user_age <= 0) {
    std::cout << "Please enter a valid age: " << std::endl;
    while (!(std::cin >> user_age)) {
      std::cout << "please enter valid input:" << std::endl;
      std::cin.clear();
      std::cin.ignore(1000000, '\n');
    }
    std::cin.clear();
    std::cin.ignore(100000, '\n');
  }
  if (user_age < 21) {
    std::cout << "The age you entered indicates you are under 21, the smart "
                 "fridge will not allow you to order/consume alcholic drinks"
              << std::endl;
  }

  user.setPersonAge(user_age);
  user_file << user.getPersonAge() << endl;
  std::cout << "Enter Your Height (inch): ";
  while (!(std::cin >> user_height)) {
    std::cout << "Please enter a valid input" << std::endl;
    std::cout << "Enter Your Height(inch): ";
    std::cin.clear();
    std::cin.ignore(100000, '\n');
  }
  while (user_height <= 0 || user_height >= 100) {
    std::cout << "Please enter a valid height: ";
    while (!(std::cin >> user_height)) {
      std::cout << "please enter valid input:" << std::endl;
      std::cin.clear();
      std::cin.ignore(1000000, '\n');
    }
    std::cin.clear();
    std::cin.ignore(100000, '\n');
  }
  user.setPersonHeight(user_height);
  user_file << user.getPersonHeight() << endl;

  std::cout << "Enter Your Weight (kg): ";
  while (!(std::cin >> user_weight)) {
    std::cout << "Please enter a valid input" << std::endl;
    std::cout << "Enter Your Weight(kg): ";
    std::cin.clear();
    std::cin.ignore(100000, '\n');
  }
  while (user_weight <= 0) {
    std::cout << "Enter a valid weight(kg): ";
    while (!(std::cin >> user_weight)) {
      std::cout << "please enter valid input:" << std::endl;
      std::cin.clear();
      std::cin.ignore(1000000, '\n');
    }
    std::cin.clear();
    std::cin.ignore(100000, '\n');
  }
  user.setPersonWeight(user_weight);
  user_file << user.getPersonWeight() << endl;
  std::cout << "Enter Your Phone number: ";
  while (!(std::cin >> user_phone)) {
    std::cout << "Please enter a valid input" << std::endl;
    std::cout << "Enter Your Phone number ";
    std::cin.clear();
    std::cin.ignore(100000, '\n');
  }
  while (user_phone.size() <= 9) {
    std::cout << "Enter a valid Phone number: ";
    while (!(std::cin >> user_phone)) {
      std::cout << "please enter valid input:" << std::endl;
      std::cin.clear();
      std::cin.ignore(1000000, '\n');
    }
    std::cin.clear();
    std::cin.ignore(100000, '\n');
  }

  user.setPersonPhone(user_phone);
  user_file << user.getPersonPhone() << endl;
  std::cout << "Enter Your Address: ";
  while (!(std::cin >> user_address)) {
    std::cout << "Please enter a valid input" << std::endl;
    std::cout << "Enter Your Address ";
    std::cin.clear();
    std::cin.ignore(100000, '\n');
  }
  while (user_address.size() <= 3) {
    std::cout << "Enter a valid Address: ";
    while (!(std::cin >> user_phone)) {
      std::cout << "please enter valid input:" << std::endl;
      std::cin.clear();
      std::cin.ignore(1000000, '\n');
    }
    std::cin.clear();
    std::cin.ignore(100000, '\n');
  }

  user.setPersonAddress(user_address);
  user_file << user.getPersonAddress() << endl;

  user_file.close();

  double height = user_height * 0.0254;
  double bmi = (user_weight) / pow(height, 2);
  open_fridge(bmi);

  return user;
}

void fridge_interface() {
  std::cout << "\n--------------------------------------------------"
            << std::endl;
  std::cout << "---------------Smart Fridge System----------------"
            << std::endl;
  std::cout << "-                                                -"
            << std::endl;
  std::cout << "-                                                -"
            << std::endl;
  std::cout << "-           Get: Get the food in fridge          -"
            << std::endl;
  std::cout << "-           Update: Update your profile          -"
            << std::endl;
  std::cout << "-         Check: Check the food in fridge        -"
            << std::endl;
  std::cout << "-        Next: Pick the food for next meal       -"
            << std::endl;
  std::cout << "-        Order: Order the food from Grocery      -"
            << std::endl;
  std::cout << "-        Quit: Quit the Smart Fridge System      -"
            << std::endl;
  std::cout << "-                                                -"
            << std::endl;
  std::cout << "-                                                -"
            << std::endl;
  std::cout << "--------------------------------------------------\n"
            << std::endl;
  return;
}
