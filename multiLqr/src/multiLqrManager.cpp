#include "multiLqrManager.hpp"

namespace multilqr{
MultiLqrManager::MultiLqrManager(const std::string& configPath)
{
   loadConfigConstructor(configPath);
}

MultiLqrManager::~MultiLqrManager()
{
    for (auto& lqrController : _lqrControllers){
        delete lqrController.second;
    }
}

void MultiLqrManager::LoadConfig(const std::string &configPath)
{
    YAML::Node multiLqrNode;
    try
    {
        multiLqrNode = YAML::LoadFile(configPath.c_str());
    }
    catch(const std::exception& e)
    {
        std::cout << "Failed to load: " << configPath << std::endl;
        return;
    }
    _tuningMode = multiLqrNode["tuningMode"].as<bool>();
    if (_tuningMode)
    {
        YAML::Node variantsNode = multiLqrNode["LqrVariants"];
    }
}

void MultiLqrManager::LoadConfigLqrVariantsNode(YAML::Node &variantsNode)
{
    for (YAML::const_iterator itVariants=variantsNode.begin(); itVariants != variantsNode.end(); ++itVariants) 
    {
        std::string variant = itVariants->first.as<std::string>();
        std::cout << variant << std::endl;
        YAML::Node lqrNode = variantsNode[variant];
        _lqrControllers[variant] =  new Dlqr(lqrNode);
    }
}

std::map<std::string, Eigen::MatrixXd> MultiLqrManager::GetGains()
{
    std::map<std::string, Eigen::MatrixXd> gains;
    for (auto& lqrController : _lqrControllers){
        gains[lqrController.first] = lqrController.second->GetGain();
    }
    return gains;
}

void MultiLqrManager::loadConfigConstructor(const std::string &configPath)
{
    YAML::Node multiLqrNode;
    try
    {
        multiLqrNode = YAML::LoadFile(configPath.c_str());
    }
    catch(const std::exception& e)
    {
        std::cout << "Failed to load: " << configPath << std::endl;
        return;
    }
    YAML::Node variantsNode = multiLqrNode["LqrVariants"];
    LoadConfigLqrVariantsNode(variantsNode);
    std::cout<<"[MultiLqrManager] Finished loading config constructor: "<<configPath<<std::endl;
}

}