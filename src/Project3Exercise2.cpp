///////////////////////////////////////
// COMP/ELEC/MECH 450/550
// Project 3
// Authors: Riley Kuhlman, Eric Jia
//////////////////////////////////////

#include <iostream>

// The collision checker routines
#include "CollisionChecking.h"

// Your random tree planner
#include "RTP.h"


using namespace ompl::geometric;
using namespace ompl::base;

void planPoint(const std::vector<Rectangle> &obstacles)
{
    std::cout << "planning Point\n";

    auto ss = std::make_shared<RealVectorStateSpace>(2);

    RealVectorBounds bounds(2);
    bounds.setLow(-10);
    bounds.setHigh(10);
    ss->setBounds(bounds);

    auto si = std::make_shared<SpaceInformation>(ss);
    si->setStateValidityChecker([](const State *) { return true; });
    si->setup();

    ScopedState<> start(ss), goal(ss);
    start.random();
    goal.random();
    auto pdef = std::make_shared<ProblemDefinition>(si);
    pdef->setStartAndGoalStates(start, goal);

    RTP planner(si);
    planner.setProblemDefinition(pdef);
    planner.setGoalBias(0.2);

    PlannerStatus solved = planner.Planner::solve(5.0);

    if (solved) {
        std::cout << "Found solution:" << std::endl;
        pdef->getSolutionPath()->print(std::cout);
    } else {
        std::cout << "No solution found" << std::endl;
    }
}

void planBox(const std::vector<Rectangle> &obstacles)
{
    std::cout << "planning Box\n";

    // TODO: Use your implementation of RTP to plan for a rotating square robot.
}

void makeEnvironment1(std::vector<Rectangle> &obstacles)
{
    std::cout << "using environment1\n";

    obstacles.push_back(Rectangle{0, 0, 1, 1});
}

void makeEnvironment2(std::vector<Rectangle> &obstacles)
{
    std::cout << "using environment2\n";

    // TODO: Fill in the vector of rectangles with your second environment.
}

int main(int /* argc */, char ** /* argv */)
{
    int robot, choice;
    std::vector<Rectangle> obstacles;

    do
    {
        std::cout << "Plan for: " << std::endl;
        std::cout << " (1) A point in 2D" << std::endl;
        std::cout << " (2) A rigid box in 2D" << std::endl;

        std::cin >> robot;
    } while (robot < 1 || robot > 2);

    do
    {
        std::cout << "In Environment: " << std::endl;
        // TODO: Make this a general environment.
        std::cout << " (1) One square" << std::endl;
        // TODO: Make this a narrow passageway.
        std::cout << " (2) TODO" << std::endl;

        std::cin >> choice;
    } while (choice < 1 || choice > 2);

    switch (choice)
    {
        case 1:
            makeEnvironment1(obstacles);
            break;
        case 2:
            makeEnvironment2(obstacles);
            break;
        default:
            std::cerr << "Invalid Environment Number!" << std::endl;
            break;
    }

    switch (robot)
    {
        case 1:
            planPoint(obstacles);
            break;
        case 2:
            planBox(obstacles);
            break;
        default:
            std::cerr << "Invalid Robot Type!" << std::endl;
            break;
    }

    return 0;
}
