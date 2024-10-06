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
            /** \brief Representation of a motion

                This only contains pointers to parent motions as we
                only need to go backwards in the tree. */
            class Motion
            {
            public:
                Motion() = default;

                /** \brief Constructor that allocates memory for the state */
                Motion(const base::SpaceInformationPtr &si) : state(si->allocState())
                {
                }

                ~Motion() = default;

                /** \brief The state contained by the motion */
                base::State *state{nullptr};

                /** \brief The parent motion in the exploration tree */
                Motion *parent{nullptr};
            };

            RNG rng_;
            base::StateSamplerPtr sampler_;
            double goalBias_{.05};

            /** \brief A list of every motion in the tree so that we can easily pick a random one. */
            std::vector<Motion *> motions_;

            /** \brief The root of the tree of motions. */
            Motion* rootMotion_;
        };
    
    }  // namespace geometric
}  // namespace ompl

#endif
