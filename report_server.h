/**
 * This file is generated by jsonrpcstub, DO NOT CHANGE IT MANUALLY!
 */

#ifndef JSONRPC_CPP_STUB_REPORT_SERVER_H_
#define JSONRPC_CPP_STUB_REPORT_SERVER_H_

#include <jsonrpccpp/server.h>

class report_server : public jsonrpc::AbstractServer<report_server> {
  public:
  report_server(jsonrpc::AbstractServerConnector &conn,
      jsonrpc::serverVersion_t type = jsonrpc::JSONRPC_SERVER_V2)
      : jsonrpc::AbstractServer<report_server>(conn, type) {
    this->bindAndAddMethod(
        jsonrpc::Procedure("FoodReport", jsonrpc::PARAMS_BY_NAME,
            jsonrpc::JSON_OBJECT, "action", jsonrpc::JSON_STRING, "value",
            jsonrpc::JSON_REAL, NULL),
        &report_server::FoodReportI);
    this->bindAndAddMethod(
        jsonrpc::Procedure("Get_Food", jsonrpc::PARAMS_BY_NAME,
            jsonrpc::JSON_OBJECT, "action", jsonrpc::JSON_STRING, "name",
            jsonrpc::JSON_STRING, "quantity", jsonrpc::JSON_INTEGER, "type",
            jsonrpc::JSON_STRING, NULL),
        &report_server::Get_FoodI);
    this->bindAndAddMethod(
        jsonrpc::Procedure("Order_Food", jsonrpc::PARAMS_BY_NAME,
            jsonrpc::JSON_OBJECT, "action", jsonrpc::JSON_STRING, "name",
            jsonrpc::JSON_STRING, "quantity", jsonrpc::JSON_INTEGER, "type",
            jsonrpc::JSON_STRING, NULL),
        &report_server::Order_FoodI);
  }

  inline virtual void FoodReportI(
      const Json::Value &request, Json::Value &response) {
    response = this->FoodReport(
        request["action"].asString(), request["value"].asDouble());
  }
  inline virtual void Get_FoodI(
      const Json::Value &request, Json::Value &response) {
    response = this->Get_Food(request["action"].asString(),
        request["name"].asString(), request["quantity"].asInt(),
        request["type"].asString());
  }
  inline virtual void Order_FoodI(
      const Json::Value &request, Json::Value &response) {
    response = this->Order_Food(request["action"].asString(),
        request["name"].asString(), request["quantity"].asInt(),
        request["type"].asString());
  }
  virtual Json::Value FoodReport(const std::string &action, double value) = 0;
  virtual Json::Value Get_Food(const std::string &action,
      const std::string &name, int quantity, const std::string &type)
      = 0;
  virtual Json::Value Order_Food(const std::string &action,
      const std::string &name, int quantity, const std::string &type)
      = 0;
};

#endif //JSONRPC_CPP_STUB_REPORT_SERVER_H_
