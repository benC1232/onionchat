//
// Created by orime on 12/14/2022.
//

#include "SqliteDataBase.h"

SqliteDataBase::SqliteDataBase() {
    this->db = nullptr;
    int rc = sqlite3_open("database.db", &this->db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(this->db) << std::endl;
        exit(0);
    } else {
        std::cout << "Opened database successfully" << std::endl;
    }


    std::string sql = "CREATE TABLE IF NOT EXISTS Nodes ("
                      "EncryptionType TEXT NOT NULL,"
                      "PublicKey int NOT NULL,"
                      "PrivateKey int NOT NULL,"
                        "IP TEXT NOT NULL,"
                        "Port int NOT NULL,"
                        "ISP TEXT NOT NULL,"
                        "owner TEXT NOT NULL,"
                        "BandWidth int NOT NULL"
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


SqliteDataBase::~SqliteDataBase() {
    sqlite3_close(this->db);
}

bool SqliteDataBase::addNewNode(NewNode newNodeStruct){
    std::string sql = "INSERT INTO Nodes (EncryptionType, PublicKey, PrivateKey, IP, Port, ISP, owner, BandWidth) "
                      "VALUES ('" + newNodeStruct.encryptionType + "', " + std::to_string(newNodeStruct.publicKey) + ", " + std::to_string(newNodeStruct.privateKey) + ", '" + newNodeStruct.ip + "', " + std::to_string(newNodeStruct.port) + ", '" + newNodeStruct.isp + "', '" + newNodeStruct.owner + "', " + std::to_string(newNodeStruct.bandWidth) + ");";
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

