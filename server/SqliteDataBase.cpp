//
// Created by orime on 12/14/2022.
//

#include <random>
#include "SqliteDataBase.h"
#include "sqlite3.h"
#define NUM_OF_NODES 1
SqliteDataBase::SqliteDataBase() {
    this->db = nullptr;
    int rc = sqlite3_open("database.sqlite", &this->db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(this->db) << std::endl;
        exit(0);
    }
    else {
        std::cout << "Opened database successfully" << std::endl;
    }

    std::string sql = "CREATE TABLE IF NOT EXISTS Nodes ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "EncryptionType TEXT NOT NULL,"
                      "PublicKey TEXT NOT NULL,"
                      "PrivateKey TEXT NOT NULL,"
                      "IP TEXT NOT NULL,"
                      "Port INTEGER NOT NULL,"
                      "ISP TEXT NOT NULL,"
                      "COUNTRY TEXT NOT NULL,"
                      "CONTINENT TEXT NOT NULL,"
                      "RegionName TEXT NOT NULL,"
                      "City TEXT NOT NULL"
                      ");";
    char* zErrMsg = 0;
    rc = sqlite3_exec(this->db, sql.c_str(), nullptr, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "Table created successfully" << std::endl;
    }
}

/*
 * std::string continent;
    std::string country;
    std::string regionName;
    std::string city;
 */

SqliteDataBase::~SqliteDataBase() {
    sqlite3_close(this->db);
}

bool SqliteDataBase::addNewNode(NewNode newNodeStruct){
    std::string sql = "INSERT INTO Nodes (EncryptionType, PublicKey, PrivateKey, IP, Port, ISP, COUNTRY, CONTINENT, RegionName, City) "
                      "VALUES ('" + newNodeStruct.encryptionType + "', " + std::to_string(newNodeStruct.publicKey) + ", " + std::to_string(newNodeStruct.privateKey) + ", '" + newNodeStruct.ipdata.ip + "', " + std::to_string(newNodeStruct.port) + ", '" + newNodeStruct.ipdata.isp+"', '" + newNodeStruct.ipdata.country+"', '" + newNodeStruct.ipdata.continent+"', '" + newNodeStruct.ipdata.regionName+"', '" + newNodeStruct.ipdata.city+"');";
    char* zErrMsg = 0;
    int rc = sqlite3_exec(this->db, sql.c_str(), nullptr, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        return false;
    } else {
        std::cout << "Records created successfully" << std::endl;
        return true;
    }

}



bool SqliteDataBase::deleteNode(std::string IP) {
    std::string sql = "DELETE from Nodes where ip='" + IP + "';";
    char* zErrMsg = 0;
    int rc = sqlite3_exec(this->db, sql.c_str(), nullptr, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        return false;
    } else {
        std::cout << "Records deleted successfully" << std::endl;
        return true;
    }
}


int callback(void* nodes, int argc, char** argv, char** azColName) {
    NewNode newNode;
    IpData ipData;
    newNode.encryptionType = std::string(argv[1]);
    newNode.publicKey = std::stoi(argv[2]);
    newNode.privateKey = std::stoi(argv[3]);
    ipData.ip = std::string(argv[4]);
    newNode.port = std::stoi(argv[5]);
    ipData.isp = std::string(argv[6]);
    ipData.country = std::string(argv[7]);
    ipData.continent = std::string(argv[8]);
    ipData.regionName = std::string(argv[9]);
    ipData.city = std::string(argv[10]);
    newNode.ipdata = ipData;
    ((std::vector<NewNode>*)nodes)->push_back(newNode);

    return 0;

}

//a function that checks if an object is in a vector of the same type
template<typename T>
bool isInVector(std::vector<T> vector, T object) {
    for (auto& i : vector) {
        if (i == object) {
            return true;
        }
    }
    return false;
}

/*
 * the function gets a IpData struct and a blacklist struct and returns a NodeData array with the route, every node in the route is a NodeData struct that all of the parameters in the struct are not in one of the vectors in the blacklist struct
 */
NodeData* SqliteDataBase::getRoute(Blacklist blackList) {
    NodeData* route = new NodeData[NUM_OF_NODES];
    int i = 0;
    //for evey node in the database check if the node is in the blacklist if it is not add it to the route
    std::string sql = "SELECT * from Nodes;";
    char* zErrMsg = 0;
    auto nodeStructs = new std::vector<NewNode>;
    int rc = sqlite3_exec(this->db, sql.c_str(), callback, (void*)nodeStructs, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }

    //randomize the vector
    std::shuffle(nodeStructs->begin(), nodeStructs->end(), std::mt19937(std::random_device()()));

    for(auto node : *nodeStructs){
        if (!isInVector(blackList.continent, node.ipdata.continent) && !isInVector(blackList.country, node.ipdata.country) && !isInVector(blackList.regionName, node.ipdata.regionName) && !isInVector(blackList.city, node.ipdata.city) && !isInVector(blackList.isp, node.ipdata.isp)) {
            route[i].encryption = node.encryptionType;
            route[i].key = node.publicKey;
            route[i].ip = node.ipdata.ip;
            route[i].port = node.port;

            i++;
        }
        if (i == NUM_OF_NODES) {
            break;
        }
    }


    if (i != NUM_OF_NODES) return nullptr;
    return route;
}



