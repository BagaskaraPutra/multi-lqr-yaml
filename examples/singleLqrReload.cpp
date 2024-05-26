#include <iostream>
#include <string>

#include "dlqr.hpp"

int main(int argc, char *argv[]) 
{
    std::string filePath;
    if (argc <= 1){
        filePath = "../config/singleLqr.yaml";
    } else {
        filePath = argv[1];
    }
    multilqr::Dlqr singleLqr;
    
    singleLqr.LoadConfig(filePath);
    printf("\n");
    std::cout << "Single discrete-time LQR gain K: " << std::endl;
    std::cout << singleLqr.GetGain() << std::endl;
    
    singleLqr.LoadConfig("../config/singleLqrExample2.yaml");
    printf("\n");
    std::cout << "Single discrete-time LQR gain K: " << std::endl;
    std::cout << singleLqr.GetGain() << std::endl;

    return 0;
}