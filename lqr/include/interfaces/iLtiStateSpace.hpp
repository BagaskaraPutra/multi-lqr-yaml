#ifndef ILTI_STATE_SPACE_HPP
#define ILTI_STATE_SPACE_HPP

#include <iostream>
#include <cmath>
#include <eigen3/Eigen/Eigen>
#include <eigen3/Eigen/Dense>
#include <eigen3/unsupported/Eigen/MatrixFunctions>

namespace multilqr
{
class ILtiStateSpace
{
public:
    virtual bool ValidateABCD() = 0;
    virtual void PrintParameters() = 0;
    virtual bool SetABCD(const Eigen::MatrixXd& A, 
                const Eigen::MatrixXd& B,
                const Eigen::MatrixXd& C,
                const Eigen::MatrixXd& D) = 0;
    virtual Eigen::MatrixXd GetA() = 0;
    virtual Eigen::MatrixXd GetB() = 0;
    virtual Eigen::MatrixXd GetC() = 0;
    virtual Eigen::MatrixXd GetD() = 0;
};
}

#endif