#include "stateSpaceUtils.hpp"
#include "discretizationType.hpp"

namespace multilqr{
    bool StateSpaceUtils::c2d(ContinuousLtiStateSpace* continuous, DiscreteLtiStateSpace* discrete, double samplingPeriod)
    {
        // Zero-order hold (ZOH) discretization
        // Ad = exp(A*Ts)
        // Bd = A.inv()*(Ad - I)*B
        
        if (samplingPeriod <= 0.0 || continuous == NULL){
            return false;
        }

        Eigen::MatrixXd Ad = (continuous->GetA()*samplingPeriod).MatrixBase::exp();
        Eigen::MatrixXd Bd = continuous->GetA().inverse()*(Ad-Eigen::MatrixXd::Identity(Ad.rows(), Ad.cols()))*continuous->GetB();
        
        if (discrete == NULL){
            discrete = new DiscreteLtiStateSpace(Ad, Bd, continuous->GetC(), continuous->GetD(), samplingPeriod);
        } else {
            discrete->SetABCD(Ad, Bd, continuous->GetC(), continuous->GetD(), samplingPeriod);
        }
        return true;
    }

    bool StateSpaceUtils::d2c(DiscreteLtiStateSpace* discrete, ContinuousLtiStateSpace* continuous)
    {
        // Continous-time system from zero-order hold (ZOH) discretization
        // A = log(Ad)/Ts
        // B = (Ad-I).inv()*A*Bd

        if (discrete == NULL){
            return false;
        }
         
        Eigen::MatrixXd A = discrete->GetA().MatrixBase::log() / discrete->GetSamplingPeriod();
        Eigen::MatrixXd B = (discrete->GetA()-Eigen::MatrixXd::Identity(discrete->GetA().rows(), discrete->GetA().cols())).inverse() * A * discrete->GetB();

        if (continuous == NULL){
            continuous = new ContinuousLtiStateSpace(A, B, discrete->GetC(), discrete->GetD());
        } else {
            continuous->SetABCD(A, B, discrete->GetC(), discrete->GetD());
        }
        return true;
    }
}