///////////////////////////////////////
// COMP/ELEC/MECH 450/550
// Project 3
// Authors: Riley Kuhlman, Eric Jia
//////////////////////////////////////

#ifndef RANDOM_TREE_H
#define RANDOM_TREE_H


#include "ompl/geometric/planners/PlannerIncludes.h"


namespace ompl
{
    namespace geometric
    {
        class RTP  : public base::Planner
        {
        public:
            RTP(const base::SpaceInformationPtr &si);

            base::PlannerStatus solve(const base::PlannerTerminationCondition & ptc);
        };

    }  // namespace geometric
}  // namespace ompl

#endif
