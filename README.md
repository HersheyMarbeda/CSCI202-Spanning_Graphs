# CSCI 202: Spanning Graphs

## Assignment Description
1. Write a program that implements Fleury's algorithm

## Documentation
This C++ program implements Fleury’s Algorithm to find an Eulerian Path or Circuit in an undirected graph. The program first checks that the graph is connected and that the degree conditions for Eulerian traversal are satisfied. It determines if there are odd-degree vertices, which indicate the presence of an Eulerian Path, or if all vertices have even degrees, which suggests an Eulerian Circuit. Additionally, the algorithm avoids traversing bridge edges unless absolutely necessary to maintain the graph's connectivity. Users are prompted to input the number of vertices, edges, and the pairs of edges, with input validation included to ensure accuracy. Finally, the program outputs the Eulerian Path or Circuit using a depth-first search approach, ensuring the graph remains connected throughout the traversal.

## Resources Used
- [GeeksforGeeks: Fleury’s Algorithm for printing Eulerian Path or Circuit](https://www.geeksforgeeks.org/fleurys-algorithm-for-printing-eulerian-path/)
