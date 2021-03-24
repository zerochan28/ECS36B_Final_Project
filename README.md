# UC Davis Final Project ECS36B - Fall 2020
> Linhao Chen, Gigi Dao, Saifedin Maani, Nicholas Goray (Team 2)
> Professor: Felix Wu
> 12/17/2020

## SPECIAL NOTES

Please ignore the following warnings when you type "make" and compile the programs
  warning: dynamic exception specifications are deprecated in C++11 [-Wdeprecated]
The program works good as long as if can compile successfully.

## Purpose of Program

For the final project, we have decided to pursue designing the foundations of a smart food networking 
application. Among the different topics, this topic is the most interesting, since it is a computer 
solution that has not been commercialized till this day. Although companies like Samsung and Philips 
have developed smart fridges, with computer control systems integrated within the fridge. The world 
has not yet seen a fully automated food ordering and consumption system. It is a system where a smart 
fridge, perhaps a network of fridges, can communicate with the user and a network of grocery stores 
to make food orders, diet recommendations for the user, and make consuming health food easier for everyone.


## Building

Typing "make" can built it as same as "make all".

Typing ./smart_fridge to run the fridge program

Typing ./smart_phone to run the phone program

Typing ./grocery to run the grocery program

Typing "make clean" can clean things up

Typing "make format" can set up the format for all files

## Usage

Please run all of three programs first:
./smart_fridge
./smart_phone
./grocery

After you run all the programs, the phone system will ask you to enter your name,
if the user name is not on the user database, the application will ask you to enter
some basic information to create a user on database. Then you will enter the main page
of the smart phone App and smart fridge will set up as long as you finish the setting in
smart phone. Now you can enjoy the flexibility of smart phone - fridge - grocery system.

************************************************************************************************************************************************
Here is the usage of each command in smart_phone:

Get:You can grab food by using the application. Enter the food type, food name, and quantity
Smart fridge will evaluate your diet and agree or deny your request. It will deny in the following cases:
- Your daily calorie intake exceeds the max based on your BMI
- You already took max number of specific food per day (i.e. You are set to get max 2 Cola per day so you cannot get more)
- Food is not avaiable
- Food number in fridge is not enough

Update: You can update your personal information by using this command, following the direction and you will all set.

Next: Go to next day, and smart fridge will return a diet report based on your diet in that day. It will also automatically
import some your favorite foods and randomly import some foods to increase your diet diversity.

Order: You can order food by using the application. Enter the food type, food name, and quantity
Smart fridge will evaluate your diet and agree or deny your request. It will deny in the following cases:
- You already took too much type of food per day(i.e. If you ordered more than 5 servings meat in a day, the system will deny your request)

Quit: Quit the program and Smart Fridge will shutdown as well.

************************************************************************************************************************************************
Here is the usage of each command in grocery system:

A: It will check all the foods in grocery networking

B: It will check all the orders recived from smart fridge

Q: Quit the grocery system

************************************************************************************************************************************************
