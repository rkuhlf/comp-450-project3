Overleaf: https://www.overleaf.com/1191816873cktytrkpzhpv#40bfd3

RRT planner: https://github.com/ompl/ompl/blob/main/src/ompl/geometric/planners/rrt/src/RRT.cpp

RRT header: https://github.com/ompl/ompl/blob/main/src/ompl/geometric/planners/rrt/RRT.h


Presumably Planner is a field that's public in the Planner class.

Code:
- Square robot is set to a side length of 0.5
- For env1point ... \
Generated Start: (5.31718,8.78763)\
Generated Goal: (-3.37481,-9.77697)
- For env1box   ... \
Generated Start: (4.80789, 6.55316, 0.496718)\
Generated Goal: (4.45794, -8.17775, -2.15407)
- For env2point ... \
Generated Start: (6.92782,-4.96663)\
Generated Goal: (-3.85608,5.30082)
- For env2box   ... \
Generated Start: (2.29839, -8.14192, -2.23593)\
Generated Goal: (6.1286, 9.96771, -2.33564)


TODOs:
- Switch out the nn data structure.
- Delete the random stuff that's left over from RRT.
- Do the items.
