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
#include <fstream>
#include "phone_system.cpp"


using namespace std;

int main() {
    std::string user_name;
    system("clear");
    std::cout << "Welcome to using Smart Life System" << std::endl;
    std::cout << "Enter Your Name" << std::endl;
    std::cin >> user_name;
    system("clear");

    Person user;
    user.setPersonName(user_name);

    ifstream ifile;
    std::string file_name = "user/" + user_name + ".txt";
    ifile.open(file_name, ios::in);
    if(ifile){
        std::cout << user_name << ", our Database already found you" << std::endl;
        std::cout << "Please enter Y or N to confirm you information\n" << std::endl;
        ifile.close();
        user = load_user(user);
        std::string user_infor = user.getPersonName() + " Phone: " + user.getPersonPhone() + " Address:" + user.getPersonAddress() + "\n";
        std::cout << user_infor << std::endl;
        std::string user_check;
        std::cin >> user_check;
        if(user_check == "Y"){
            std::cout << "\nThank you for your confirmation : )" << std::endl;
        } else if(user_check == "N"){
            std::cout << "Start to create a new user" << std::endl;
            user = new_user(user);
        }
    } else {
        user = new_user(user);
    }
    send_command("Open");
    all_set();
    
    std::string Day[7]={"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};
    std::string Time[3]={"Morning","Afternoon","Evening"};
    int index_day = 0;
    int index_time = 0;

    bool system_continue = true;
    while(system_continue){
        system("clear");
        std::cout << "\n" << Day[index_day] << std::endl;
        fridge_interface();
        string fridge_command;
        std::cout << "Good " << Time[index_time] << "! " << user.getPersonName() << ", please enter the command to operate:" << std::endl;
        std::cin >> fridge_command;
        if(fridge_command == "Update"){
            user = change_user(user);
            std::cout << "\nPlease wait 5 seconds and we will back to homepage" << std::endl;
            sleep(5);
        } else if (fridge_command == "Get"){
            Get_Food();
            std::cout << "\nPlease wait 5 seconds and we will back to homepage" << std::endl;
            sleep(5);
        } else if (fridge_command == "Check"){
            send_command("Check");
            char Com;
            std::cout << "Press any to continue" << std::endl;
            std::cin >> Com;
        } else if (fridge_command == "Order"){
            Order_Food();
            char Com;
            std::cout << "Press any to continue" << std::endl;
            std::cin >> Com;
        } else if (fridge_command == "Next"){
            if(index_time==2){
                index_time=0;
                if(index_day==6){
                    index_day=0;
                }else{
                    index_day++;
                }
            }else{
                index_time++;
            }
        } else if (fridge_command == "Quit" || fridge_command == "Q"){
            system_continue = false;
            send_command("Quit");
        }
    }
    
    std::cout << "\n\nThank you for using the system, Bye" << std::endl;
    sleep(3);
    system("clear");
    return 0;

}
