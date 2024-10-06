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

// Enable so that the program outputs a bunch of data that can be pasted into a python file.
const bool SERIALIZE_DATA = true;

void planPoint(const std::vector<Rectangle> &obstacles)
{
    std::cout << "planning Point\n";

    auto ss = std::make_shared<RealVectorStateSpace>(2);

    RealVectorBounds bounds(2);
    bounds.setLow(-10);
    bounds.setHigh(10);
    ss->setBounds(bounds);

    auto si = std::make_shared<SpaceInformation>(ss);
    si->setStateValidityChecker([obstacles](const State * state) {
        return isValidStatePoint(state, obstacles);
    });
    si->setup();

    ScopedState<> start(ss), goal(ss);
    bool validStatesFound = false;
    while (!validStatesFound) {
        // Generate random start and goal states
        start.random();
        goal.random();

        // Check if both states are valid
        if (si->isValid(start.get()) && si->isValid(goal.get())) {
            validStatesFound = true;
        } else {
            std::cout << "Invalid start or goal state, regenerating..." << std::endl;
        }
    }

    auto pdef = std::make_shared<ProblemDefinition>(si);
    pdef->setStartAndGoalStates(start, goal);

    RTP planner(si);
    planner.setProblemDefinition(pdef);
    planner.setGoalBias(0.15);

    PlannerStatus solved = planner.Planner::solve(5.0);


    if (solved) {
        std::cout << "Found solution:" << std::endl;
        pdef->getSolutionPath()->print(std::cout);

        PlannerData plannerData(si);
        planner.getPlannerData(plannerData);

        if (SERIALIZE_DATA) {
            std::cout << "OBSTACLES" << std::endl;
            for (const Rectangle& obstacle : obstacles) {
                std::cout << "[" << obstacle.x << "," << obstacle.y << "," << obstacle.width << "," << obstacle.height << "]" << std::endl;
            }

            std::cout << "VERTICES" << std::endl;

            for (unsigned int i = 0; i < plannerData.numVertices(); ++i)
            {
                const State *state = plannerData.getVertex(i).getState();
                const auto *vectorState = state->as<RealVectorStateSpace::StateType>();

                double x = vectorState->values[0];
                double y = vectorState->values[1];
                std::cout << "(" << x << "," << y << ")" << std::endl;
            }

            std::cout << "GOALS" << std::endl;
            for (unsigned int i = 0; i < plannerData.numGoalVertices(); ++i)
            {
                const State *state = plannerData.getGoalVertex(i).getState();
                const auto *vectorState = state->as<RealVectorStateSpace::StateType>();

                double x = vectorState->values[0];
                double y = vectorState->values[1];
                std::cout << "(" << x << "," << y << ")" << std::endl;
            }

            std::cout << "STARTS" << std::endl;
            for (unsigned int i = 0; i < plannerData.numStartVertices(); ++i)
            {
                const State *state = plannerData.getStartVertex(i).getState();
                const auto *vectorState = state->as<RealVectorStateSpace::StateType>();

                double x = vectorState->values[0];
                double y = vectorState->values[1];
                std::cout << "(" << x << "," << y << ")" << std::endl;
            }

            std::cout << "EDGES" << std::endl;

            // Loop over each edge and update the matrix
            for (unsigned int i = 0; i < plannerData.numVertices(); ++i)
            {
                for (unsigned int j = 0; j < plannerData.numVertices(); ++j)
                {
                    if (plannerData.edgeExists(i, j))
                    {
                        std::cout << 1 << " ";
                    } else {
                        std::cout << 0 << " ";
                    }
                }

                std::cout << std::endl;
            }

        }
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

    obstacles.push_back(Rectangle{0, 0, 5, 5});
    obstacles.push_back(Rectangle{5, 0, 3, 2});
    obstacles.push_back(Rectangle{-5, 2, 3, 2});
    obstacles.push_back(Rectangle{-5, -8, 3, 5});
    obstacles.push_back(Rectangle{5, -8, 3, 5});
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
