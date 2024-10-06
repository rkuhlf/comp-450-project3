Overleaf: https://www.overleaf.com/1191816873cktytrkpzhpv#40bfd3

RRT planner: https://github.com/ompl/ompl/blob/main/src/ompl/geometric/planners/rrt/src/RRT.cpp

RRT header: https://github.com/ompl/ompl/blob/main/src/ompl/geometric/planners/rrt/RRT.h


Presumably Planner is a field that's public in the Planner class.

TODOs:
- Switch out the nn data structure.
- Delete the random stuff that's left over from RRT.
- Implement square and point robot being different. Implement different environments.
- Make sure that the random start and end don't spawn inside of an obstacle.
- Exercise 2.
    - Visualize the robot's baths to see if it looks right.
