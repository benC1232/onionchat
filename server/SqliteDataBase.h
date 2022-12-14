#pragma once
#include "IDataBase.h"
#include "sqlite3.h"
#include <map>
#include <string>
#include <vector>


class SqliteDataBase: public IDataBase {
public:
    SqliteDataBase();
    virtual ~SqliteDataBase() override;
    virtual NodeData* getRoute() override;
    virtual bool addNewNode(NewNode newNodeStruct) override;
    virtual bool deleteNode(std::string IP) override;

private:
    sqlite3* db;


};
