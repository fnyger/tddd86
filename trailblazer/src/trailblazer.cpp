// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
#include "set.h"
#include "queue.h"
#include "stack.h"
#include <algorithm>

// TODO: include any other headers you need; remove this comment
using namespace std;

/*
 * This helper recursively finds the shortest path from
 * the start node to the end node with depth first search.
 */
vector<Node *> depthFirstSearchRecursiveHelper(Vertex* current, Vertex* end) {
    vector<Vertex*> path;
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

vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    vector<Vertex*> path = depthFirstSearchRecursiveHelper(start, end);

    return path;
}

vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    Queue<Vertex*> queue;
    queue.enqueue(start);
    vector<Vertex*> path;

    while(queue.size()) {
        Vertex* current = queue.dequeue();
        if(current == end) {
            do {
                current->setColor(GREEN);
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

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}
