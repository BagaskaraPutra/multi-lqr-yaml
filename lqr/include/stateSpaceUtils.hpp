#ifndef STATE_SPACE_UTILS_HPP
#define STATE_SPACE_UTILS_HPP

#include "continuousLtiStateSpace.hpp"
#include "discreteLtiStateSpace.hpp"

namespace multilqr{
    class StateSpaceUtils{
    public:        
        static bool c2d(ContinuousLtiStateSpace* continuous, DiscreteLtiStateSpace* discrete, double samplingPeriod);
        static bool d2c(DiscreteLtiStateSpace* discrete, ContinuousLtiStateSpace* continuous);
    };
}

#endif