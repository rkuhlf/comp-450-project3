import matplotlib.patches as patches
import matplotlib.pyplot as plt
import numpy as np

data = """
OBSTACLES
[0,0,5,5]
[5,0,3,2]
[-5,2,3,2]
[-5,-8,3,5]
[5,-8,3,5]
VERTICES
(-1.61048,-5.4481)
(2.12972,-7.3227)
(-7.56994,3.62442)
(-4.95083,4.4881)
(7.90792,8.95192)
(-3.1494,8.9103)
(3.4693,-0.295228)
(3.06699,-3.80778)
(-0.98933,8.5091)
(7.15273,9.12458)
(-0.879013,-8.12323)
(-3.12391,6.98161)
(7.13083,6.76177)
(1.79862,-5.27843)
(5.59295,6.61302)
(6.0164,-9.66805)
(0.125628,-0.349312)
(-3.25977,4.13773)
(-0.728041,4.15783)
GOALS
(-1.61048,-5.4481)
STARTS
(2.12972,-7.3227)
EDGES
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 1 0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 0 1 1 0 0 1 0 0 0 0 0 0 1 1 0 0 0 
0 0 0 0 0 0 0 0 1 0 0 0 1 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 1 0 0 0 1 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 
0 0 0 0 0 0 0 0 0 0 1 1 0 0 0 0 0 1 1 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
"""


if __name__ == "__main__":    
    # Split the data into lines
    lines = data.strip().split('\n')
    
    plt.figure(figsize=(10, 8))

    i = 1
    # Add the obstacles.
    while lines[i] != "VERTICES":
        x, y, w, h = eval(lines[i])
        rectangle = patches.Rectangle((x, y), w, h, linewidth=2, edgecolor='blue', facecolor='lightblue')
        plt.gca().add_patch(rectangle)
        i += 1

    i += 1
    
    # Parse the coordinates
    coordinates = []    
    while lines[i] != "GOALS":
        x, y = eval(lines[i])  # Safely evaluate the tuple
        coordinates.append((x, y))
        i += 1
        
    i += 1

    # Add the goals.
    while lines[i] != "STARTS":
        x, y = eval(lines[i])
        plt.scatter([x], [y], marker="*", c="black", s=100, label="goal", zorder=2)
        i += 1

    i += 1
    
    # Add the starts.
    while lines[i] != "EDGES":
        x, y = eval(lines[i])
        plt.scatter([x], [y], marker="s", c="black", s=100, label="start", zorder=2)
        i += 1

    i += 1

    # Parse the adjacency matrix
    adjacency_matrix = []
    for line in lines[i:]:  # The remaining lines contain the matrix
        row = list(map(int, line.split()))
        adjacency_matrix.append(row)

    # Convert coordinates to numpy array for easier indexing
    coordinates = np.array(coordinates)

    # Create a new plot
    # Plot the points
    plt.scatter(coordinates[:, 0], coordinates[:, 1], color='blue', marker='o', label='Vertices')

    # Plot the edges based on the adjacency matrix
    num_vertices = len(coordinates)
    for i in range(num_vertices):
        for j in range(num_vertices):
            if adjacency_matrix[i][j] == 1:  # If there's an edge
                plt.plot([coordinates[i][0], coordinates[j][0]], [coordinates[i][1], coordinates[j][1]], 'r-')

    # Set labels and title
    plt.xlabel('X Coordinate')
    plt.ylabel('Y Coordinate')
    plt.title('Graph Representation of PlannerData')
    plt.axhline(0, color='black',linewidth=0.5, ls='--')
    plt.axvline(0, color='black',linewidth=0.5, ls='--')
    plt.grid(color = 'gray', linestyle = '--', linewidth = 0.5)
    plt.legend()
    plt.axis('equal')  # Equal scaling of axes

    # Show the plot
    plt.savefig("./out.png")