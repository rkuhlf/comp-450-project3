///////////////////////////////////////
// COMP/ELEC/MECH 450/550
// Project 3
// Authors: Riley Kuhlman, Eric Jia
//////////////////////////////////////

#include <iostream>

#include "RTP.h"

ompl::geometric::RTP::RTP(const base::SpaceInformationPtr &si) : base::Planner(si, "RTP") {
    std::cout << "Creating RTP\n";
}

ompl::base::PlannerStatus ompl::geometric::RTP::solve(const base::PlannerTerminationCondition &ptc)
{   
    bool solved(false);
    bool approximate(false);
    return {solved, approximate};
}
