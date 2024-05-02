#ifndef CONTINUOUS_LTI_STATE_SPACE_HPP
#define CONTINUOUS_LTI_STATE_SPACE_HPP

#include <iostream>
#include <cmath>
#include <eigen3/Eigen/Eigen>
#include <eigen3/Eigen/Dense>
#include <eigen3/unsupported/Eigen/MatrixFunctions>

#include "iLtiStateSpace.hpp"
#include "systemTimeType.hpp"

namespace multilqr{
    class ContinuousLtiStateSpace : public ILtiStateSpace
    {
    public:
        ContinuousLtiStateSpace();
        ContinuousLtiStateSpace(const Eigen::MatrixXd& A, 
                                const Eigen::MatrixXd& B, 
                                const Eigen::MatrixXd& C,
                                const Eigen::MatrixXd& D);

        ContinuousLtiStateSpace(const Eigen::MatrixXd& A, 
                                const Eigen::MatrixXd& B);

        bool ValidateABCD() override;

        void PrintParameters() override;

        bool SetABCD(const Eigen::MatrixXd& A, 
                    const Eigen::MatrixXd& B,
                    const Eigen::MatrixXd& C,
                    const Eigen::MatrixXd& D) override;

        Eigen::MatrixXd GetA() override;
        Eigen::MatrixXd GetB() override;
        Eigen::MatrixXd GetC() override;
        Eigen::MatrixXd GetD() override;

    protected:
        SystemTimeType _systemTimeType;
        Eigen::MatrixXd _A, _B, _C, _D;
    };
}

#endif