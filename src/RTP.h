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

            /** \brief Set the goal bias

                In the process of randomly selecting states in
                the state space to attempt to go towards, the
                algorithm may in fact choose the actual goal state, if
                it knows it, with some probability. This probability
                is a real number between 0.0 and 1.0; its value should
                usually be around 0.05 and should not be too large. It
                is probably a good idea to use the default value. */
            void setGoalBias(double goalBias)
            {
                goalBias_ = goalBias;
            }

            /** \brief Get the goal bias the planner is using */
            double getGoalBias() const
            {
                return goalBias_;
            }
        
        protected:
            double goalBias_{.05};
        };
    
    }  // namespace geometric
}  // namespace ompl

#endif
