/*
 * This file implements different search algorithms used in adapter.cpp.
 * Functions are defined in trailblazer.h
 */
#include "costs.h"
#include "trailblazer.h"
#include "queue.h"
#include "stack.h"
#include <algorithm>
#include "unordered_map"
#include "pqueue.h"

using namespace std;

/*
 * This helper recursively finds the shortest path from
 * the start node to the end node with depth first search.
 */
vector<Node *> depthFirstSearchRecursiveHelper(Vertex* current, Vertex* end) {    vector<Vertex*> path;
    path.push_back(current);

    current->visited = true;
    current->setColor(GREEN);

    if(current == end) {
        return path;
    }

    for(auto arc: current->arcs) {
        if(!arc->finish->visited) {
            vector<Vertex*> newPath;
            newPath = depthFirstSearchRecursiveHelper(arc->finish, end);

            if(newPath.size()) {
                for (auto node: newPath) {
                    path.push_back(node);
                }

                return path;
            }
        }
    }

    current->setColor(GRAY);
    path.pop_back();

    return path;
}

/*
 * Search in graph from single source start to end using depth first search algorithm.
 * Returns vector of path.
 */
vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    vector<Vertex*> path = depthFirstSearchRecursiveHelper(start, end);

    return path;
}

/*
 * Search in graph from single source start to end using breadth first search algorithm.
 * Returns vector of path.
 */
vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    Queue<Vertex*> queue;
    queue.enqueue(start);
    vector<Vertex*> path;

    while(queue.size()) {
        Vertex* current = queue.dequeue();
        current->setColor(GREEN);
        if(current == end) {
            do {
                path.push_back(current);
                current = current->previous;
            } while (current != start);

            path.push_back(start);
            start->setColor(GREEN);
            reverse(path.begin(), path.end());

            return path;
        }

        for(auto arc: current->arcs){
            if(!arc->finish->visited) {
                arc->finish->visited = true;
                arc->finish->previous = current;
                queue.enqueue(arc->finish);
                arc->finish->setColor(YELLOW);
            }
        }
    }

    return path;
}


/*
 * Search in graph from single source start to end using dijkstra's algorithm
 * Returns vector of shortest path.
 */
vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {

    graph.resetData();
    vector<Vertex*> path;
    unordered_map<Vertex*, double> dist;
    PriorityQueue<Vertex*> prioQ;

    for(auto node: graph.getNodeSet()) {
        dist.insert({node, __DBL_MAX__});
        prioQ.enqueue(node, dist[node]);
    }
    dist[start] = 0;
    prioQ.changePriority(start, 0);

    start->setColor(GREEN);

    while(!prioQ.isEmpty()) {

        Vertex* current = prioQ.dequeue();
        current->visited = true;
        current->setColor(GREEN);

        if(current == end) {
            do {
                path.push_back(current);
                current = current->previous;
            } while (current != start);
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }

        for(auto arc: current->arcs) {

            if(!arc->finish->visited) {
                double distance = dist[current] + arc->cost;
                if(distance < dist[arc->finish]) {

                    prioQ.changePriority(arc->finish, distance);
                    arc->finish->setColor(YELLOW);
                    arc->finish->previous = current;
                    dist[arc->finish] = distance;
                }
            }

        }
    }


    return path;
}

/*
 * A* search in graph from single source vertex start to end
 * Returns vector of shortest path.
 */
vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    vector<Vertex*> path;
    unordered_map<Vertex*, double> distToStart;
    PriorityQueue<Vertex*> prioQ;

    for(auto node: graph.getNodeSet()) {
        distToStart.insert({node, __DBL_MAX__});
        prioQ.enqueue(node, __DBL_MAX__);
    }
    distToStart[start] = 0;
    prioQ.changePriority(start, start->heuristic(end));

    start->setColor(GREEN);

    while(!prioQ.isEmpty()) {

        Vertex* current = prioQ.dequeue();
        current->visited = true;
        current->setColor(GREEN);

        if(current == end) {
            do {
                path.push_back(current);
                current = current->previous;
            } while (current != start);
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }

        for(auto arc: current->arcs) {

            if(!arc->finish->visited) {
                double distance = distToStart[current] + arc->cost;
                if(distance < distToStart[arc->finish]) {
                    distToStart[arc->finish] = distance;

                    prioQ.changePriority(arc->finish, distance + arc->finish->heuristic(end));
                    arc->finish->setColor(YELLOW);
                    arc->finish->previous = current;
                }
            }
        }
    }


    return path;
}
