# Arranging schedule for robot

## Question
Robots A and B commute on an undirected graph denoted as G. As both robots are controlled by a radio wave, their distance cannot be reduced below a specific threshold, denoted as 'r.' Initially, the two robots are positioned at distinct locations, A at point 'a' and B at point 'b' on the graph G. Robot A aims to move to point C, while Robot B intends to reach point D.

This movement can be represented by creating a schedule, wherein only one robot can relocate through an edge at a time, moving from a vertex to its neighboring vertex. Eventually, Robot A reaches point C, and Robot B reaches point D.

A schedule is considered correct if it ensures that, at no point, the distance between the two robots falls below the threshold 'r.' The value of 'r' remains constant throughout the movement.
## Usage Instructions

The program takes input from the user in the following format:

1. The first line contains the number of vertices n < 100 and the number of edges m in the graph G.
2. The next m lines, each containing 3 numbers x y w, represent an edge {x, y} in the graph G with weight w.
3. The next line contains four numbers a b c d representing the starting and ending vertices of the two robots.
4. The last line contains a number r > 0.

The program will output the movement schedule if possible, and if not, it will display 'Cannot!'

## Example

Consider the graph below with starting vertices a = 0, b = 2; ending vertices c = 2, d = 3; and r = 4. Here is a movement schedule:
