#include <iostream>

#include "multiLqrManager.hpp"

int main(int argc, char *argv[]) 
{
    std::string filePath;
    if (argc <= 1){
        filePath = "../config/multiLqr.yaml";
    } else {
        filePath = argv[1];
    }
    multilqr::MultiLqrManager multiLqr;

    multiLqr.LoadConfig(filePath);
    printf("\n");
    std::cout << "Multiple discrete-time LQR gains: " << std::endl;
    std::map<std::string, Eigen::MatrixXd> multiGains = multiLqr.GetGains();
    for (auto& gain: multiGains){
        std::cout << gain.first << " Config Gain: " << gain.second << std::endl;
    }

    multiLqr.LoadConfig("../config/multiLqrExample2.yaml");
    printf("\n");
     std::cout << "Multiple discrete-time LQR gains: " << std::endl;
    multiGains = multiLqr.GetGains();
    for (auto& gain: multiGains){
        std::cout << gain.first << " Config Gain: " << gain.second << std::endl;
    }        
    return 0;
}