#include "discreteLtiStateSpace.hpp"
#include "stateSpaceUtils.hpp"

namespace multilqr{

DiscreteLtiStateSpace::DiscreteLtiStateSpace()
{
    _pContinuousSystem = NULL;
    _systemTimeType = DISCRETE;
}

DiscreteLtiStateSpace::DiscreteLtiStateSpace(const Eigen::MatrixXd& A, 
                  const Eigen::MatrixXd& B, 
                  const Eigen::MatrixXd& C,
                  const Eigen::MatrixXd& D,
                  double samplingPeriod)
: ContinuousLtiStateSpace(A,B,C,D)
{
    _pContinuousSystem = NULL;
    SetABCD(A,B,C,D,samplingPeriod);
    _systemTimeType = DISCRETE;
}

DiscreteLtiStateSpace::DiscreteLtiStateSpace(const Eigen::MatrixXd& A, 
                                                const Eigen::MatrixXd& B)
: ContinuousLtiStateSpace(A,B)
{
    _pContinuousSystem = NULL;
    SetABCD(A, B, Eigen::MatrixXd::Identity(A.rows(), A.cols()), Eigen::MatrixXd::Zero(A.rows(), B.cols()), -1);
    _systemTimeType = DISCRETE;
}

DiscreteLtiStateSpace::~DiscreteLtiStateSpace()
{
    if (_pContinuousSystem != NULL){
        delete _pContinuousSystem;
        _pContinuousSystem = NULL;
    }
}

void DiscreteLtiStateSpace::PrintParameters()
{
    std::cout<<"Discrete-time LTI state space:" << std::endl;
    std::cout << "A:" << std::endl;
    std::cout << _A << std::endl;
    std::cout << "B:" << std::endl;
    std::cout << _B << std::endl;
    std::cout << "C:" << std::endl;
    std::cout << _C << std::endl;
    std::cout << "D:" << std::endl;
    std::cout << _D << std::endl;
    std::cout << "sampling period (seconds): " << _samplingPeriod << std::endl;
}

bool DiscreteLtiStateSpace::SetABCD(const Eigen::MatrixXd& A, 
                            const Eigen::MatrixXd& B,
                            const Eigen::MatrixXd& C,
                            const Eigen::MatrixXd& D,
                            double samplingPeriod)
{
    _A = A;
    _B = B;
    _C = C;
    _D = D;
    if (samplingPeriod <= 0.0){
        std::cout << "[WARNING] Sampling period cannot be negative" << std::endl;
        return false;
    }
    _samplingPeriod = samplingPeriod;
    if (_pContinuousSystem == NULL){
        _pContinuousSystem = new ContinuousLtiStateSpace();
    }
    StateSpaceUtils::d2c(this, _pContinuousSystem);
    return ValidateABCD();
}

double DiscreteLtiStateSpace::GetSamplingPeriod()
{
    return _samplingPeriod;
}

void DiscreteLtiStateSpace::Resample(double samplingPeriod)
{
    if (samplingPeriod <= 0.0){
        return;
    }
    StateSpaceUtils::c2d(_pContinuousSystem, this, samplingPeriod);
}

}