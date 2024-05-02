#ifndef DISCRETE_LTI_STATE_SPACE_HPP
#define DISCRETE_LTI_STATE_SPACE_HPP

#include "continuousLtiStateSpace.hpp"

namespace multilqr{
    class DiscreteLtiStateSpace : public ContinuousLtiStateSpace
    {
    public:
        DiscreteLtiStateSpace();
        DiscreteLtiStateSpace(const Eigen::MatrixXd& A, 
                      const Eigen::MatrixXd& B, 
                      const Eigen::MatrixXd& C,
                      const Eigen::MatrixXd& D,
                      double samplingPeriod);
        DiscreteLtiStateSpace(const Eigen::MatrixXd& A, 
                      const Eigen::MatrixXd& B);
        ~DiscreteLtiStateSpace();

        void PrintParameters() override;

        bool SetABCD(const Eigen::MatrixXd& A, 
                    const Eigen::MatrixXd& B,
                    const Eigen::MatrixXd& C,
                    const Eigen::MatrixXd& D,
                    double samplingPeriod);            

        double GetSamplingPeriod();

        void Resample(double samplingPeriod);

    protected:       
        double _samplingPeriod;
        ContinuousLtiStateSpace* _pContinuousSystem;  
    };
}

#endif