/*
 * Tour is sequential collection of points.
 *
 */

#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"

class Tour {
public:

    Tour();
    ~Tour();

    /*
     * Prints coordinates for each node to stdout
     */
    void show() const;

    /*
     * Draws lines between neighbouring nodes to scene
     */
    void draw(QGraphicsScene* scene) const;

    /*
     * Returns size of tour
     */
    int size() const;

    /*
     * Returns total distance of tour
     */
    double distance() const;

    /*
     * Insert point with the "nearest" heuristic
     */
    void insertNearest(Point p);

    /*
     * Insert point with the "smallest" heuristic
     */
    void insertSmallest(Point p);

private:
    Node* startNode = nullptr; //Pointer to first node in the circular linked list
};

#endif // TOUR_H
