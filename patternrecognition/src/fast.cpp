/*
 * TDDD86 Pattern Recognition
 * This program computes and plots all line segments involving 4 points
 * in a file using Qt.
 */

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include "Point.h"
#include <set>
#include <map>

// constants
static const int SCENE_WIDTH = 512;
static const int SCENE_HEIGHT = 512;

void render_points(QGraphicsScene* scene, const vector<Point>& points) {
    for(const auto& point : points) {
        point.draw(scene);
    }
}

void render_line(QGraphicsScene* scene, const Point& p1, const Point& p2) {
    p1.lineTo(scene, p2);
}


class comparator {
public:
    explicit comparator(Point point) : p(point){}

    bool operator ()(Point q, Point r){
        return p.slopeTo(q) < p.slopeTo(r);
    }

private:
    Point p;
};



int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // open file
    string filename = "input12800.txt";
    ifstream input;
    input.open(filename);

    // the vector of points
    vector<Point> points;

    // read points from file
    int N;
    int x;
    int y;

    input >> N;

    for (int i = 0; i < N; ++i) {
        input >> x >> y;
        points.push_back(Point(x, y));
    }
    input.close();

    // setup graphical window
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    view->setScene(scene);
    // draw points to screen all at once
    render_points(scene, points);
    view->scale(1, -1); //screen y-axis is inverted
    view->resize(view->sizeHint());
    view->setWindowTitle("Brute Force Pattern Recognition");
    view->show();

    // sort points by natural order
    // makes finding endpoints of line segments easy
    sort(points.begin(), points.end());
    auto begin = chrono::high_resolution_clock::now();

    // iterates through all points
    for (int i = 0 ; i < N; ++i) {
        vector<Point> slopeVector;
        // adds all points other than i to a vector and sorts by slope
        for (int j = 0; j < N; j++) {
            if (j != i) {
                slopeVector.push_back(points.at(j));
            }
        }
        sort(slopeVector.begin(), slopeVector.end(), comparator(points.at(i)));

        // iterates through the sorted vector and renders
        //the lines with min 4 points including point i
        for(unsigned j=0; j<slopeVector.size()-3; j++) {
            if(slopeVector[j].slopeTo(points.at(i)) == slopeVector[j+2].slopeTo(points.at(i)) && i != (int)j) {
                double slope = slopeVector[j].slopeTo(points.at(i));
                Point largestPoint = slopeVector[j];
                Point smallestPoint = slopeVector[j];
                while (slopeVector[j+1].slopeTo(points.at(i)) == slope) {
                    if (slopeVector[j+1] > largestPoint) largestPoint = slopeVector[j+1];
                    else if (slopeVector[j+1] < smallestPoint) smallestPoint = slopeVector[j+1];
                    j++;
                }
                render_line(scene, smallestPoint, largestPoint);
                a.processEvents(); // show rendered line




            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    cout << "Computing line segments took "
         << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;

    return a.exec(); // start Qt event loop
}
