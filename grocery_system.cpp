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

using namespace jsonrpc;
using namespace std;

void loading(int num){
    sleep(1);
    std::cout << num << "..." << std::endl;
    return;
}

void default_system(){
    std::cout << "This is the Davis grocery system\n" << std::endl;
    std::cout << "A. Check All goods in grocery" << std::endl;
    std::cout << "B. Review All order record" << std::endl;
    std::cout << "Q. Quit the grocery system" << std::endl;
    std::cout << "Enter the button to confrim operation\n";
}

void new_message(){
    system("clear");
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "|                                         |" << std::endl;
    std::cout << "|     Hello!                              |" << std::endl;
    std::cout << "|     We recived new Order!               |" << std::endl;
    std::cout << "|     Enter B to check it.                |" << std::endl;
    std::cout << "|                                         |" << std::endl;
    std::cout << "|                  Food Order System      |" << std::endl;
    std::cout << "|                                         |" << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
}