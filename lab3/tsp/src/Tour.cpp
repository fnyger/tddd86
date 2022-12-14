/*
 * Tour.cpp implements the tour class behaviour declared in Tour.h
 */


#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour()
{
}

Tour::~Tour()
{
    if(startNode == nullptr) {
        return;
    }
    Node* current = startNode->next;
    do {
        Node* temp = current;
        current = temp->next;
        delete temp;
    } while(current != startNode);
    delete startNode;
}

void Tour::show() const
{

    Node* current = startNode;
    if(current == nullptr) {
        cout << "No nodes" << endl;
        return;
    }
    do {
        std::cout << current->point.toString() << endl;
        current = current->next;
    } while(current != startNode);
}

void Tour::draw(QGraphicsScene *scene) const
{
    Node* current = startNode;
    if(current == nullptr) {
        cout << "No nodes" << endl;
        return;
    }
    do {
        current->point.drawTo(current->next->point, scene);
        current = current->next;
    } while(current != startNode);
    // TODO: write this member
}

int Tour::size() const
{
    int size = 0;
    Node* current = startNode;
    if(current == nullptr) {
        cout << "No nodes" << endl;
        return 0;
    }
    do {
        size++;
        current = current->next;
    } while(current != startNode);
    return size;
    // TODO: write this member
}

double Tour::distance() const
{
    double distance = 0;
    Node* current = startNode;
    if(current == nullptr) {
        cout << "No nodes" << endl;
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

}

void Tour::insertSmallest(Point p)
{
    Node* current = startNode;
    if(current == nullptr) {
        Node* newNode = new Node(p);
        newNode->next = newNode;
        startNode = newNode;
        return;
    }

    double currDistance = startNode->point.distanceTo(startNode->next->point);
    double newDistance = startNode->point.distanceTo(p) + startNode->next->point.distanceTo(p);
    double bestDiff = newDistance - currDistance;

    current = startNode->next;
    Node* bestPre = startNode;
    while(current != startNode) {
        double currDistance = current->point.distanceTo(current->next->point);
        double newDistance = current->point.distanceTo(p) + current->next->point.distanceTo(p);
        double difference = newDistance - currDistance;

        if(difference < bestDiff) {
            bestPre = current;
            bestDiff = difference;
        }
        current = current->next;
    }

    Node* newNode = new Node(p, bestPre->next);
    bestPre->next = newNode;
}
