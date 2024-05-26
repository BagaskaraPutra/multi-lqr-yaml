#ifndef MULTI_LQR_MANAGER_HPP
#define MULTI_LQR_MANAGER_HPP

#include "iLqr.hpp"
#include "dlqr.hpp"

namespace multilqr{
    class MultiLqrManager
    {
    public:
        MultiLqrManager();
        MultiLqrManager(const std::string& configPath);
        ~MultiLqrManager();
        void LoadConfig(const std::string& configPath);
        void LoadConfigLqrVariantsNode(YAML::Node& variantsNode);
        std::map<std::string, Eigen::MatrixXd> GetGains();
    protected:
        void loadConfigConstructor(const std::string& configPath);
        std::map<std::string, ILqr*> _lqrControllers;
        bool _tuningMode;
        std::string _configPath;    
    };
}

#endif