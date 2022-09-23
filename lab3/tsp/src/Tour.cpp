// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour()
{

    // TODO: write this member
}

Tour::~Tour()
{
    // TODO: write this member
}

void Tour::show()
{

    Node* current = startNode;
    if(current == nullptr) {
        cout << "fanns inga haha du är sämst" << endl;
        return;
    }
    do {
        std::cout << current->point.toString() << endl;
        current = current->next;
    } while(current != startNode);
    // TODO: write this member
}

void Tour::draw(QGraphicsScene *scene)
{
    Node* current = startNode;
    if(current == nullptr) {
        cout << "fanns inga haha du är sämst" << endl;
        return;
    }
    do {
        current->point.drawTo(current->next->point, scene);
        current = current->next;
    } while(current != startNode);
    // TODO: write this member
}

int Tour::size()
{
    int size = 0;
    Node* current = startNode;
    if(current == nullptr) {
        cout << "fanns inga haha du är sämst" << endl;
        return 0;
    }
    do {
        size++;
        current = current->next;
    } while(current != startNode);
    return size;
    // TODO: write this member
}

double Tour::distance()
{
    double distance = 0;
    Node* current = startNode;
    if(current == nullptr) {
        cout << "fanns inga haha du är sämst" << endl;
        return distance;
    }    do {
        distance += current->point.distanceTo(current->next->point);
        current = current->next;
    } while(current != startNode);
    return distance;
    // TODO: write this member
}

void Tour::insertNearest(Point p)
{
    Node* current = startNode;
    if(current == nullptr) {
        Node* newNode = new Node(p);
        newNode->next = newNode;
        startNode = newNode;
        return;
    }

    double currDistance = startNode->point.distanceTo(p);

    current = startNode->next;
    Node* nearest = startNode;
    double distance;
    while(current != startNode) {
        distance = current->point.distanceTo(p);
        if(distance < currDistance) {
            nearest = current;
            currDistance = distance;
        }
        current = current->next;
    }

    Node* newNode = new Node(p, nearest->next);
    nearest->next = newNode;

    // TODO: write this member
}

void Tour::insertSmallest(Point p)
{
    // TODO: write this member
}
