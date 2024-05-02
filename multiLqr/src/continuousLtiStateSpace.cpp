#include "continuousLtiStateSpace.hpp"
#include "stateSpaceUtils.hpp"

namespace multilqr{
ContinuousLtiStateSpace::ContinuousLtiStateSpace()
{
    _systemTimeType = CONTINUOUS;
}

ContinuousLtiStateSpace::ContinuousLtiStateSpace(const Eigen::MatrixXd& A, 
                                                const Eigen::MatrixXd& B, 
                                                const Eigen::MatrixXd& C,
                                                const Eigen::MatrixXd& D)
{
    SetABCD(A, B, C, D);
    _systemTimeType = CONTINUOUS;
}

ContinuousLtiStateSpace::ContinuousLtiStateSpace(const Eigen::MatrixXd& A, 
                                                const Eigen::MatrixXd& B)
{
    SetABCD(A, B, Eigen::MatrixXd::Identity(A.rows(), A.cols()), Eigen::MatrixXd::Zero(A.rows(), B.cols()));
    _systemTimeType = CONTINUOUS;
}

bool ContinuousLtiStateSpace::ValidateABCD()
{
    if (_A.rows() == _A.cols() == _B.rows() == _C.cols() &&
         _C.rows() == _D.rows() && _B.cols() == _D.cols()){
        return true;
    } else {
        return false;
    }
}

void ContinuousLtiStateSpace::PrintParameters()
{
    std::cout<<"Continuous-time LTI state space:" << std::endl;
    std::cout << "A:" << std::endl;
    std::cout << _A << std::endl;
    std::cout << "B:" << std::endl;
    std::cout << _B << std::endl;
    std::cout << "C:" << std::endl;
    std::cout << _C << std::endl;
    std::cout << "D:" << std::endl;
    std::cout << _D << std::endl;
}

bool ContinuousLtiStateSpace::SetABCD(const Eigen::MatrixXd& A, 
                            const Eigen::MatrixXd& B,
                            const Eigen::MatrixXd& C,
                            const Eigen::MatrixXd& D)
{
    _A = A;
    _B = B;
    _C = C;
    _D = D;
    return ValidateABCD();
}

Eigen::MatrixXd ContinuousLtiStateSpace::GetA()
{
    return _A;
}

Eigen::MatrixXd ContinuousLtiStateSpace::GetB()
{
    return _B;
}

Eigen::MatrixXd ContinuousLtiStateSpace::GetC()
{
    return _C;
}

Eigen::MatrixXd ContinuousLtiStateSpace::GetD()
{
    return _D;
}

}