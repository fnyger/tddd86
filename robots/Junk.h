/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef JUNK_H
#define JUNK_H

#include "Unit.h"
#include "Robot.h"
#include <QGraphicsScene>

class Junk : public Robot {
public:
    Junk(const Point& p);

    Junk();

    /*
     * did not crash yet
     */
    virtual bool canMove() const;

    /*
     * Crashes and remembers it
     */
    void doCrash();

    /*
     * Return whether the robot crashed
     */
    bool justCrashed() const;

    /*
    * Draws this junk onto the given QGraphicsScene.
    */
    virtual void draw(QGraphicsScene* scene) const;

};

#endif // JUNK_H
