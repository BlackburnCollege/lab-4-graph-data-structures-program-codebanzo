#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

struct EdgeNode 
{
    int toIndex;
    EdgeNode* next;
};

struct VertexNode 
{
    int x;
    int y;
    EdgeNode* edgeHead;

    VertexNode(int xv = 0, int yv = 0) 
    {
        x = xv;
        y = yv;
        edgeHead = nullptr;
    }
};

struct EdgeRecord 
{
    int x1, y1;
    int x2, y2;
};

class Graph 
{
private:
    std::vector<VertexNode> vertices;
    std::vector<EdgeRecord> edgeList;

public:
    Graph();
    ~Graph();
    void clear();

    bool loadFromFile(const std::string& filename);
    bool edgeExists(int x1, int y1, int x2, int y2);
    void printGraph();
    bool intersectsWith(Graph& other);

private:
    int findVertexIndex(int x, int y);
    void addEdgeInternal(int fromIndex, int toIndex);

    // Skiena-style geometry helpers
    int ccw(int ax, int ay, int bx, int by, int cx, int cy);
    bool onSegment(int ax, int ay, int bx, int by, int cx, int cy);
    bool segmentsIntersect(const EdgeRecord& e1, const EdgeRecord& e2);
};

#endif


