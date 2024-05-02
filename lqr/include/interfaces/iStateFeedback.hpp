#ifndef ISTATE_FEEDBACK_HPP
#define ISTATE_FEEDBACK_HPP

#include <iostream>
#include <cmath>
#include <yaml-cpp/yaml.h>

#include <eigen3/Eigen/Eigen>
#include <eigen3/Eigen/Dense>

#include "continuousLtiStateSpace.hpp"
#include "discreteLtiStateSpace.hpp"
#include "stateSpaceUtils.hpp"

namespace multilqr
{
class IStateFeedback
{
public:
    virtual Eigen::MatrixXd GetGain() = 0;
    virtual bool LoadConfigLqrNode(YAML::Node& lqrNode) = 0;
    virtual bool LoadConfig(const std::string& configPath) = 0;
    
    // virtual bool SetGain(Eigen::MatrixXd K) = 0;
    // virtual bool SetSystem(ILtiStateSpace* sys) = 0;
};
}

#endif