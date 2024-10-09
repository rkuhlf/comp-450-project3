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
(5.58464,6.23707)
(1.45533,-8.50886)
(-6.09075,-9.34923)
(0.644713,-1.55564)
(-4.18051,-1.59189)
(7.7257,-8.49706)
(2.15462,-9.04206)
(3.98321,-8.44318)
(-8.01124,4.68241)
(9.74437,-9.9187)
(-8.94437,-2.42413)
(-3.39707,-9.60734)
GOALS
(5.58464,6.23707)
STARTS
(1.45533,-8.50886)
EDGES
0 0 0 0 0 0 0 0 0 0 0 0 
0 0 1 1 0 1 1 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 0 
0 0 0 0 1 0 0 0 0 0 1 0 
0 0 0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 1 0 0 0 0 
0 0 0 0 0 0 0 0 0 1 0 1 
0 0 0 0 0 0 0 0 1 0 0 0 
1 0 0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 0 
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
    plt.savefig("./out2.png")