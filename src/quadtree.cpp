#include <iostream>
#include <sstream>
#include <vector>

#include "cRunWatch.h"

#include "quadtree.h"

namespace quad
{
    std::vector<cxy *> cCell::myPointsFound;

    cCell::cCell(const cxy &p, float d)
        : center(p), dim(d / 2), nw(0)
    {
    }

    cCell::~cCell()
    {
        if (nw)
        {
            delete nw;
            delete sw;
            delete ne;
            delete se;
        }
    }

    bool cCell::contains(const cxy &p) const
    {
        if (!(center.x - dim <= p.x && p.x <= center.x + dim))
            return false;
        if (!(center.y - dim <= p.y && p.y <= center.y + dim))
            return false;
        return true;
    }
    void cCell::subdivide()
    {
        float dim2 = dim / 2;
        nw = new cCell(cxy(center.x - dim2, center.y - dim2), dim);
        sw = new cCell(cxy(center.x - dim2, center.y + dim2), dim);
        ne = new cCell(cxy(center.x + dim2, center.y - dim2), dim);
        se = new cCell(cxy(center.x + dim2, center.y + dim2), dim);

        if (myPoint.isValid())
        {
            // move point to child
            childInsert(myPoint);
            myPoint.invalidate();
        }
    }
    bool cCell::insert(const cxy &p)
    {
        // check point located in cell
        if (!contains(p))
            return false;

        // check cell is an empty leaf
        if (!myPoint.isValid())
        {
            if (!nw)
            {
                // store point here
                myPoint = p;
                return true;
            }
        }
        else if (myPoint == p)
        {
            // point at same location as previously added
            //std::cout << "dup ";
            //throw std::runtime_error("dup");
            return true;
        }

        // subdivide leaf
        if (!nw)
            subdivide();

        childInsert(p);
        return true;
    }

    bool cCell::childInsert(const cxy &p)
    {
        if (nw->insert(p))
            return true;
        if (sw->insert(p))
            return true;
        if (ne->insert(p))
            return true;
        if (se->insert(p))
            return true;

        std::cout << "quadtree insertion error\n"
                  << p << " " << text(false) << "\n";
        throw std::runtime_error("quadtree insertion error");
    }

    std::vector<cxy *>
    cCell::find(const cCell &range)
    {
        myPointsFound.clear();
        findrec(range);
        return myPointsFound;
    }
    void cCell::findrec(
        const cCell &range)
    {
        //std::cout << "look in " << text(false) << "\n";

        // check that range and cell overlap
        if (!intersect(range))
            return;

        // check if point in cell is in range
        if (myPoint.isValid())
            if (range.contains(myPoint))
            {
                //std::cout << "found " << myPoint.text();
                myPointsFound.push_back(&myPoint);
            }
        if (!nw)
            return;

        // find points in children and range
        nw->findrec(range);
        sw->findrec(range);
        ne->findrec(range);
        se->findrec(range);
    }
    bool cCell::intersect(const cCell &range) const
    {
        // calculate distance squared between centers
        float dx = center.x - range.center.x;
        float dy = center.y - range.center.y;
        float d2 = dx * dx + dy * dy;

        // calculate max distance squared between centers
        // that still has an overlap in the corners of the cells
        float dmax = 2 * (dim + range.dim) * (dim + range.dim);

        return d2 <= dmax;
    }

    std::string cCell::text(bool children) const
    {
        std::stringstream ss;
        if (myPoint.isValid())
            ss << "point " << myPoint;
        else
            ss << "empty ";
        ss
            << " in cell at " << center
            << " size " << 2 * dim << "\n";
        if (children)
            if (nw)
            {
                ss << nw->text();
                ss << sw->text();
                ss << ne->text();
                ss << se->text();
            }
        return ss.str();
    }

}
