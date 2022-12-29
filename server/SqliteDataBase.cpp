//
// Created by orime on 12/14/2022.
//

#include <random>
#include "SqliteDataBase.h"
#include "sqlite3.h"

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
    std::string sql = "INSERT INTO Nodes (EncryptionType, PublicKey, PrivateKey, IP, Port, ISP, COUNTRY, CONTINENT, RegionName, City"
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
    std::vector<NewNode>* nodesVector = (std::vector<NewNode>*)nodes;
    for (int i = 0; i < argc; i++) {
        NewNode newNode;
        newNode.encryptionType = argv[0];
        newNode.publicKey = std::stoi(argv[1]);
        newNode.privateKey = std::stoi(argv[2]);
        newNode.ipdata.ip = argv[3];
        newNode.port = std::stoi(argv[4]);
        newNode.ipdata.isp = argv[5];
        newNode.ipdata.country = argv[6];
        newNode.ipdata.continent = argv[7];
        newNode.ipdata.regionName = argv[8];
        newNode.ipdata.city = argv[9];
        nodesVector->push_back(newNode);

    }
    nodes = (void*)nodesVector;


}

/*
 * the function gets a ipData struct and a blacklist struct and returns a NodeData array with the route, every node in the route is a NodeData struct that all of the parameters in the struct are not in one of the vectors in the blacklist struct
 */
NodeData* SqliteDataBase::getRoute(ipData ipData,Blacklist blackList) {
    NodeData* route = new NodeData[3];
    int i = 0;
    //for evey node in the database check if the node is in the blacklist if it is not add it to the route
    std::string sql = "SELECT * from Nodes;";
    char* zErrMsg = 0;
    std::vector<NewNode>* nodeStructs;
    int rc = sqlite3_exec(this->db, sql.c_str(), callback, (void*)nodeStructs, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }

    //randomize the vector
    std::shuffle(nodeStructs->begin(), nodeStructs->end(), std::mt19937(std::random_device()()));


    for (auto node : *nodeStructs) {
        if (std::find(blackList.continent.begin(), blackList.continent.end(), node.ipdata.continent) == blackList.continent.end() &&
            std::find(blackList.country.begin(), blackList.country.end(), node.ipdata.country) == blackList.country.end() &&
            std::find(blackList.regionName.begin(), blackList.regionName.end(), node.ipdata.regionName) == blackList.regionName.end() &&
            std::find(blackList.city.begin(), blackList.city.end(), node.ipdata.city) == blackList.city.end()) {
            route[i].encryption = node.encryptionType;
            route[i].key = node.publicKey;
            route[i].ip = node.ipdata.ip;
            route[i].port = node.port;
            i++;

        }
        if (i == 3) {
            break;
        }
    }

    if (i != 3) {
        return nullptr;
    }
    return route;
}



