///////////////////////////////////////
// COMP/ELEC/MECH 450/550
// Project 3
// Authors: Eric Jia, Riley Kuhlman
//////////////////////////////////////

#include <iostream>

#include <omplapp/apps/SE3RigidBodyPlanning.h>
#include <ompl/geometric/SimpleSetup.h>
#include <ompl/geometric/planners/prm/PRM.h>
#include <ompl/geometric/planners/est/EST.h>
#include <ompl/geometric/planners/rrt/RRT.h>
#include <ompl/tools/benchmark/Benchmark.h>

// Your random tree planner
#include "RTP.h"

void benchmarkApartment()
{
    ompl::app::SE3RigidBodyPlanning setup;

    // load robot and environment
    std::string dir_path = "/usr/local/share/ompl/resources/3D";
    std::string robot_fname = dir_path + "/Apartment_robot.dae";
    std::string env_fname = dir_path + "/Apartment_env.dae";
    setup.setRobotMesh(robot_fname);
    setup.setEnvironmentMesh(env_fname);

    // set start and goal
    ompl::base::ScopedState<ompl::base::SE3StateSpace> start(setup.getSpaceInformation());
    ompl::base::ScopedState<ompl::base::SE3StateSpace> goal(start);
    start->setXYZ(-4.96, -40.62, 70.57);
    start->rotation().setIdentity();
    goal->setXYZ(200.49, -40.62, 70.57);
    goal->rotation().setIdentity();

    setup.setStartAndGoalStates(start, goal);

    setup.getSpaceInformation()->setStateValidityCheckingResolution(0.01);

    setup.setup();
    setup.print();

    // benchmarking
    ompl::tools::Benchmark b(setup, "benchmarking apartment");
    b.addPlanner(ompl::base::PlannerPtr(new ompl::geometric::RTP(setup.getSpaceInformation())));
    b.addPlanner(ompl::base::PlannerPtr(new ompl::geometric::PRM(setup.getSpaceInformation())));
    b.addPlanner(ompl::base::PlannerPtr(new ompl::geometric::EST(setup.getSpaceInformation())));
    b.addPlanner(ompl::base::PlannerPtr(new ompl::geometric::RRT(setup.getSpaceInformation())));

    // request
    ompl::tools::Benchmark::Request req;
    req.maxTime = 10.0;
    req.maxMem = 200.0;
    req.runCount = 50;
    req.displayProgress = true;
    b.benchmark(req);

    // save results
    b.saveResultsToFile();

}

void benchmarkHome()
{
    ompl::app::SE3RigidBodyPlanning setup;

    // load robot and environment
    std::string dir_path = "/usr/local/share/ompl/resources/3D";
    std::string robot_fname = dir_path + "/Home_robot.dae";
    std::string env_fname = dir_path + "/Home_env.dae";
    setup.setRobotMesh(robot_fname);
    setup.setEnvironmentMesh(env_fname);

    // set start and goal
    ompl::base::ScopedState<ompl::base::SE3StateSpace> start(setup.getSpaceInformation());
    ompl::base::ScopedState<ompl::base::SE3StateSpace> goal(start);
    start->setXYZ(-4.96, -40.62, 70.57);
    start->rotation().setIdentity();
    goal->setXYZ(200.49, -40.62, 70.57);
    goal->rotation().setIdentity();

    setup.setStartAndGoalStates(start, goal);

    setup.getSpaceInformation()->setStateValidityCheckingResolution(0.01);

    setup.setup();
    setup.print();

    // benchmarking
    ompl::tools::Benchmark b(setup, "benchmarking apartment");
    b.addPlanner(ompl::base::PlannerPtr(new ompl::geometric::RTP(setup.getSpaceInformation())));
    b.addPlanner(ompl::base::PlannerPtr(new ompl::geometric::PRM(setup.getSpaceInformation())));
    b.addPlanner(ompl::base::PlannerPtr(new ompl::geometric::EST(setup.getSpaceInformation())));
    b.addPlanner(ompl::base::PlannerPtr(new ompl::geometric::RRT(setup.getSpaceInformation())));

    // request
    ompl::tools::Benchmark::Request req;
    req.maxTime = 10.0;
    req.maxMem = 200.0;
    req.runCount = 50;
    req.displayProgress = true;
    b.benchmark(req);

    // save results
    b.saveResultsToFile();
}

int main(int /* argc */, char ** /* argv */)
{
    int environment;

    do
    {
        std::cout << "Benchmark for: " << std::endl;
        std::cout << " (1) Apartment" << std::endl;
        std::cout << " (2) Home" << std::endl;

        std::cin >> environment;
    } while (environment < 1 || environment > 2);

    switch (environment)
    {
        case 1:
            benchmarkApartment();
            break;
        case 2:
            benchmarkHome();
            break;
        default:
            std::cerr << "Invalid Environment!" << std::endl;
            break;
    }

    return 0;
}
