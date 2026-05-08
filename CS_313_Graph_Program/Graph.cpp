#include "Graph.h"
#include <iostream>
#include <fstream>
#include <algorithm>

Graph::Graph() 
{}

Graph::~Graph() 
{
    clear();
}

void Graph::clear() 
{
    for (auto& v : vertices) 
    {
        EdgeNode* curr = v.edgeHead;
        while (curr) 
        {
            EdgeNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
        v.edgeHead = nullptr;
    }
    vertices.clear();
    edgeList.clear();
}

int Graph::findVertexIndex(int x, int y) 
{
    for (int i = 0; i < static_cast<int>(vertices.size()); i++) 
    {
        if (vertices[i].x == x && vertices[i].y == y)
            return i;
    }
    return -1;
}

void Graph::addEdgeInternal(int fromIndex, int toIndex) 
{
    EdgeNode* e = new EdgeNode;
    e->toIndex = toIndex;
    e->next = vertices[fromIndex].edgeHead;
    vertices[fromIndex].edgeHead = e;
}

bool Graph::loadFromFile(const std::string& filename) 
{
    clear();
    //pray it opens
    std::ifstream file(filename);
    if (!file.is_open()) 
    {
        std::cout << "Could not open file.\n";
        return false;
    }

    int numVertices, numEdges;
    char c1, c2, c3;

    file >> numVertices >> numEdges;

    for (int i = 0; i < numEdges; i++) 
    {
        int x1, y1, x2, y2;
        file >> x1 >> c1 >> y1 >> c2 >> x2 >> c3 >> y2;

        int idx1 = findVertexIndex(x1, y1);
        if (idx1 == -1) 
        {
            vertices.push_back(VertexNode(x1, y1));
            idx1 = static_cast<int>(vertices.size()) - 1;
        }

        int idx2 = findVertexIndex(x2, y2);
        if (idx2 == -1) 
        {
            vertices.push_back(VertexNode(x2, y2));
            idx2 = static_cast<int>(vertices.size()) - 1;
        }

        addEdgeInternal(idx1, idx2);
        addEdgeInternal(idx2, idx1);

        edgeList.push_back({ x1, y1, x2, y2 });
    }

    return true;
}

bool Graph::edgeExists(int x1, int y1, int x2, int y2) 
{
    int idx1 = findVertexIndex(x1, y1);
    int idx2 = findVertexIndex(x2, y2);

    if (idx1 == -1 || idx2 == -1)
        return false;

    EdgeNode* curr = vertices[idx1].edgeHead;
    while (curr) 
    {
        if (curr->toIndex == idx2)
            return true;
        curr = curr->next;
    }
    return false;
}

void Graph::printGraph() 
{
    std::cout << "Number of Vertices: " << vertices.size()
        << " Number of Edges: " << edgeList.size() << "\n";

    std::cout << "Vertices: ";
    for (int i = 0; i < static_cast<int>(vertices.size()); i++) 
    {
        std::cout << "(" << vertices[i].x << "," << vertices[i].y << ")";
        if (i < static_cast<int>(vertices.size()) - 1)
            std::cout << ", ";
    }
    std::cout << "\n";

    for (int i = 0; i < static_cast<int>(edgeList.size()); i++) 
    {
        std::cout << "Edge " << i + 1 << ": ("
            << edgeList[i].x1 << "," << edgeList[i].y1 << ") - ("
            << edgeList[i].x2 << "," << edgeList[i].y2 << ")\n";
    }
}

//geometric functions to check intersections
//test counter clockwise
int Graph::ccw(int ax, int ay, int bx, int by, int cx, int cy) 
{
    long long area2 =
        static_cast<long long>(bx - ax) * (cy - ay) -
        static_cast<long long>(cx - ax) * (by - ay);

    if (area2 > 0) return 1;
    if (area2 < 0) return -1;
    return 0;
}
//is c on the segment ab?
bool Graph::onSegment(int ax, int ay, int bx, int by, int cx, int cy) 
{
    return (cx >= std::min(ax, bx) && cx <= std::max(ax, bx) &&
        cy >= std::min(ay, by) && cy <= std::max(ay, by));
}
//do they intersect? use counter clockwise
bool Graph::segmentsIntersect(const EdgeRecord& e1, const EdgeRecord& e2) 
{
    int d1 = ccw(e1.x1, e1.y1, e1.x2, e1.y2, e2.x1, e2.y1);
    int d2 = ccw(e1.x1, e1.y1, e1.x2, e1.y2, e2.x2, e2.y2);
    int d3 = ccw(e2.x1, e2.y1, e2.x2, e2.y2, e1.x1, e1.y1);
    int d4 = ccw(e2.x1, e2.y1, e2.x2, e2.y2, e1.x2, e1.y2);

    if (d1 * d2 < 0 && d3 * d4 < 0)
        return true;

    if (d1 == 0 && onSegment(e1.x1, e1.y1, e1.x2, e1.y2, e2.x1, e2.y1)) return true;
    if (d2 == 0 && onSegment(e1.x1, e1.y1, e1.x2, e1.y2, e2.x2, e2.y2)) return true;
    if (d3 == 0 && onSegment(e2.x1, e2.y1, e2.x2, e2.y2, e1.x1, e1.y1)) return true;
    if (d4 == 0 && onSegment(e2.x1, e2.y1, e2.x2, e2.y2, e1.x2, e1.y2)) return true;

    return false;
}
//compare every edge from 1 with 2 to check
bool Graph::intersectsWith(Graph& other) 
{
    for (const auto& e1 : edgeList) 
    {
        for (const auto& e2 : other.edgeList) 
        {
            if (segmentsIntersect(e1, e2))
                return true;
        }
    }
    return false;
}
