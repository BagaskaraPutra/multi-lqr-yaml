#ifndef ILQR_HPP
#define ILQR_HPP

#include <iostream>
#include <cmath>
#include <yaml-cpp/yaml.h>

#include <eigen3/Eigen/Eigen>
#include <eigen3/Eigen/Dense>

#include "iStateFeedback.hpp"
#include "continuousLtiStateSpace.hpp"
#include "discreteLtiStateSpace.hpp"
#include "stateSpaceUtils.hpp"

namespace multilqr
{
class ILqr : public IStateFeedback
{
public:
    virtual bool LoadConfigLqrNode(YAML::Node& lqrNode) = 0;
};
}

#endif