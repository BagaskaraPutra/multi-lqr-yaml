#ifndef DLQR_HPP
#define DLQR_HPP

#include <iostream>
#include <cmath>
#include <yaml-cpp/yaml.h>

#include <eigen3/Eigen/Eigen>
#include <eigen3/Eigen/Dense>

#include "iLqr.hpp"
#include "stateSpaceUtils.hpp"

using namespace Eigen;

namespace multilqr
{
class Dlqr : public ILqr
{
public:
    Dlqr(const std::string& configPath);
    Dlqr(const Eigen::MatrixXd& A, 
        const Eigen::MatrixXd& B,
        const Eigen::MatrixXd& Q,
        const Eigen::MatrixXd& R);
    Dlqr(YAML::Node& lqrNode);
    ~Dlqr();
    static Eigen::MatrixXd CalcGain(const Eigen::MatrixXd& A, const Eigen::MatrixXd& B, const Eigen::MatrixXd& Q, const Eigen::MatrixXd& R);
    static Eigen::MatrixXd CalcGain(DiscreteLtiStateSpace& sysd, const Eigen::MatrixXd& Q, const Eigen::MatrixXd& R);
    Eigen::MatrixXd GetGain() override;
    bool LoadConfigLqrNode(YAML::Node& lqrNode) override;
    bool LoadConfig(const std::string& configPath) override;

private:
    const int MAX_RICCATI_ITERATIONS = 152;
    
    bool loadConfigConstructor(const std::string& configPath);
    bool calcGain();
    
    bool _tuningMode;
    int _num_inputs;
    int _num_states;
    int _num_outputs;
    ContinuousLtiStateSpace* _pContinuousSystem;
    DiscreteLtiStateSpace* _pDiscreteSystem;
    Eigen::MatrixXd _Q, _R, _K;
};
}

#endif