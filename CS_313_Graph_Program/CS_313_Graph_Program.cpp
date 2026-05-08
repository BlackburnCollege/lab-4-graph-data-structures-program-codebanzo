#include <iostream>
#include "Graph.h"
//Menu Loop to load graph, search for edge, print graph, load 2nd graph and compare, or exit
int main() 
{
    Graph g1, g2;
    bool g1Loaded = false;
    bool g2Loaded = false;

    while (true) 
    {
        std::cout << "\n--- Graph Menu ---\n";
        std::cout << "1. Load Graph File\n";
        std::cout << "2. Search For Edge\n";
        std::cout << "3. Print Graph\n";
        std::cout << "4. Load and Compare 2nd Graph\n";
        std::cout << "5. Exit\n";
        std::cout << "Choice: ";

        int choice;
        std::cin >> choice;
        //load graph file
        if (choice == 1) 
        {
            std::string file;
            std::cout << "Enter filename: ";
            std::cin >> file;
            g1Loaded = g1.loadFromFile(file);
        }
		//search for edge
        else if (choice == 2) 
        {
            if (!g1Loaded) 
            {
                std::cout << "Load a graph first.\n";
                continue;
            }
            int x1, y1, x2, y2;
            std::cout << "Enter x1 y1 x2 y2: ";
            std::cin >> x1 >> y1 >> x2 >> y2;

            if (g1.edgeExists(x1, y1, x2, y2))
                std::cout << "Edge exists.\n";
            else
                std::cout << "Edge does NOT exist.\n";
        }
		//print graph
        else if (choice == 3) 
        {
            if (!g1Loaded) 
            {
                std::cout << "Load a graph first.\n";
                continue;
            }
            g1.printGraph();
        }
		//load and compare 2nd graph
        else if (choice == 4) 
        {
            if (!g1Loaded) 
            {
                std::cout << "Load the first graph first.\n";
                continue;
            }

            std::string file2;
            std::cout << "Enter 2nd filename please: ";
            std::cin >> file2;

            g2Loaded = g2.loadFromFile(file2);

            if (g2Loaded) 
            {
                if (g1.intersectsWith(g2))
                    std::cout << "Graphs intersect.\n";
                else
                    std::cout << "Graphs do NOTTTTT intersect.\n";
            }
        }
		//exit
        else if (choice == 5) 
        {
            break;
        }
    }

    return 0;
}
