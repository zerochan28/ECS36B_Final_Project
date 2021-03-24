CC = g++ -std=c++14
LDFLAGS = -ljsoncpp -lmicrohttpd -ljsonrpccpp-common -ljsonrpccpp-server -ljsonrpccpp-client -lcurl

all: smart_phone smart_fridge grocery report_client.h report_server.h

report_client.h:		food_report.json
	jsonrpcstub food_report.json --cpp-server=report_server --cpp-client=report_client

report_server.h:		food_report.json
	jsonrpcstub food_report.json --cpp-server=report_server --cpp-client=report_client

grocery_client.h:		grocery_report.json
	jsonrpcstub grocery_report.json --cpp-server=grocery_server --cpp-client=grocery_client

grocery_server.h:		grocery_report.json
	jsonrpcstub grocery_report.json --cpp-server=grocery_server --cpp-client=grocery_client

smart_phone.o : smart_phone.cpp phone_system.cpp Person.cpp Person.h report_client.h grocery_client.h
	$(CC) -c smart_phone.cpp

smart_phone : smart_phone.o
	$(CC) -o smart_phone smart_phone.o $(LDFLAGS)

smart_fridge.o : smart_fridge.cpp food.cpp food.h fridge_design.cpp report_server.h grocery_client.h
	$(CC) -c smart_fridge.cpp

smart_fridge : smart_fridge.o
	$(CC) -o smart_fridge smart_fridge.o $(LDFLAGS)

grocery.o: grocery.cpp food.cpp food.h grocery_server.h
	$(CC) -c grocery.cpp

grocery: grocery.o
	$(CC) -o grocery grocery.o $(LDFLAGS)

clean:
	rm -f *.o smart_phone smart_fridge grocery

format:
	clang-format -i -style=file *.cpp *.h
