#pragma once
#include<iostream>

typedef struct NodeData{
    unsigned char ip[4];
    unsigned char port[2];
    std::string encryption;
    int key;
}NodeData;