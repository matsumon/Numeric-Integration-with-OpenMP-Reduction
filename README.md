# Numeric-Integration-with-OpenMP-Reduction
Introduction

We all know that the equation of a unit sphere centered at the origin is x2 + y2 + z2 = 1. But, there is something called a superquadric whose equation is xN + yN + zN = 1. In this exercise, we will use parallel reduction to compute the volume of a superquadric using N=0.7.

Using some number of subdivisions in both X and Y, NUMNODESxNUMNODES, take NUMNODES2 height samples.

We will think of each height sample as sitting on a 2D tile. That really makes that height sample act as a volume where the tile is extruded vertically from the bottom to the top.

Think about a pin rising at each dot from the floor to the top of the superquadric surface. This pin's contribution to the overall volume is its height times the area of the tile underneath it.
Note: tiles along the edges will have only 1/2 the area of tiles in the middle.
Note: tiles in the corners will have only 1/4 the area of tiles in the middle. The volume contribution of each extruded height tile needs to be weighted accordingly. The logic of this is for you to figure out.

Requirements

Compute the total volume by using the given Height function. (Note that this will give you Z=0. to Z=Height. As the superquadric has a negative half in addition to a positive half, double the 0.-Height area as your final answer.

Use a variety of number of subdivisions (NUMNODES). Pick at least 8 different ones.

Use a variety of number of threads (NUMT). You must use at least 1, 2, and 4.

Record the data in units of something that gets larger as speed increases. Joe Parallel used "MegaHeights Computed Per Second", but you can use anything that makes sense.

From the speed-up that you are seeing, use the "Inverse Amdahl's Law" to determine the Parallel Fraction for this application.

From the Parallel Fraction, determine what maximum speed-up you could ever get, regardless of how many cores/threads you throw at this, even with a million cores.

Your commentary write-up (turned in as a PDF file) should include:

    Tell what machine you ran this on
    What do you think the actual volume is?
    Show the performances you achieved in tables and two graphs showing:
        Performance as a function of NUMNODES with colored lines showing different NUMT values
        Performance as a function of NUMT with colored lines showing different NUMNODES values 
    (See the example in the Project Notes.)
    What patterns are you seeing in the speeds?
    Why do you think it is behaving this way?
    What is the Parallel Fraction for this application, using the Inverse Amdahl equation?
    Given that Parallel Fraction, what is the maximum speed-up you could ever get? 

The Height-Evaluation Code

In this code sample, NUMNODES is the number of nodes, or dots, subdividing the floor area. So, for example, NUMNODES=4 means that there are 4 dots on each side edge.

Each node has some amount of tile space surrounding it. 
