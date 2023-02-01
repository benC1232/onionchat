#pragma once
#include "IDataBase.h"
#include "sqlite3.h"
#include <map>
#include <string>
#include <vector>
#define NUM_OF_NODES 1


class SqliteDataBase: public IDataBase {
public:
    SqliteDataBase();
    virtual ~SqliteDataBase() override;
    virtual bool addNewNode(NewNode newNodeStruct) override;
    virtual bool deleteNode(std::string IP) override;
    virtual NodeData* getRoute(Blacklist blacklist) override;


        private:
    sqlite3* db;


};

