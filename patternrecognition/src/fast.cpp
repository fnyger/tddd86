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

bool sjuukt(pair<double, set<Point>>& a,
         pair<double, set<Point>>& b)
{
    return a.second.size() > b.second.size();
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

struct comp {
    bool operator()(const std::pair<const double, std::set<Point>> &x, const std::pair<const double, std::set<Point>> &y) const {
        return x.second.size() < y.second.size();
    }
};


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // open file
    string filename = "mystery10089.txt";
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

    // iterate through all combinations of 4 points
    for (int i = 0 ; i < N; ++i) {
        std::map<double, set<Point>> pMap;
        vector<Point> pVec;
        for (int j = 0; j < N; j++) {
            if (j != i) {
                pVec.push_back(points.at(j));
            }
        }
        sort(pVec.begin(), pVec.end(), comparator(points.at(i)));



        for(int j=0; j<pVec.size()-3; j++) {


            if(pVec[j].slopeTo(points.at(i)) == pVec[j+2].slopeTo(points.at(i)) && i != j) {
                double slope = pVec[j].slopeTo(points.at(i));

                while (pVec[j].slopeTo(points.at(i)) == slope) {
                    render_line(scene, points.at(i), pVec[j]);
                    a.processEvents(); // show rendered line
                    j++;
                }

            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    cout << "Computing line segments took "
         << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;

    return a.exec(); // start Qt event loop
}