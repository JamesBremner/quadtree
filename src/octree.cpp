#include <iostream>
#include <sstream>
#include <vector>

#include "cRunWatch.h"

#include "octree.h"

namespace quad
{
    std::vector<c3Point *> c3Cell::myPointsFound;

    c3Cell::c3Cell(const c3Point &p, float d)
        : center(p), dim(d / 2), nwd(0)
    {
    }

    c3Cell::~c3Cell()
    {
        if (nwd)
        {
            delete nwd;
            delete swd;
            delete ned;
            delete sed;
            delete nwu;
            delete swu;
            delete neu;
            delete seu;
        }
    }

    bool c3Cell::contains(const c3Point &p) const
    {
        if (!(center.x - dim <= p.x && p.x <= center.x + dim))
            return false;
        if (!(center.y - dim <= p.y && p.y <= center.y + dim))
            return false;
        if (!(center.z - dim <= p.z && p.z <= center.z + dim))
            return false;
        return true;
    }
    void c3Cell::subdivide()
    {
        //TODO
        float dim2 = dim / 2;
        nwd = new c3Cell(c3Point(center.x - dim2, center.y - dim2, center.z - dim2), dim);
        swd = new c3Cell(c3Point(center.x - dim2, center.y + dim2, center.z - dim2), dim);
        ned = new c3Cell(c3Point(center.x + dim2, center.y - dim2, center.z - dim2), dim);
        sed = new c3Cell(c3Point(center.x + dim2, center.y + dim2, center.z - dim2), dim);
        nwu = new c3Cell(c3Point(center.x - dim2, center.y - dim2, center.z + dim2), dim);
        swu = new c3Cell(c3Point(center.x - dim2, center.y + dim2, center.z + dim2), dim);
        neu = new c3Cell(c3Point(center.x + dim2, center.y - dim2, center.z + dim2), dim);
        seu = new c3Cell(c3Point(center.x + dim2, center.y + dim2, center.z + dim2), dim);

        if (myPoint.valid)
        {
            // move point to child
            childInsert(myPoint);
            myPoint.valid = false;
        }
    }
    bool c3Cell::insert(const c3Point &p)
    {
        // check point located in cell
        if (!contains(p))
            return false;

        // check cell is an empty leaf
        if (!myPoint.valid)
        {
            if (!nwd)
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
        if (!nwd)
            subdivide();

        childInsert(p);
        return true;
    }

    bool c3Cell::childInsert(const c3Point &p)
    {
        if (nwd->insert(p))
            return true;
        if (swd->insert(p))
            return true;
        if (ned->insert(p))
            return true;
        if (sed->insert(p))
            return true;
        if (nwu->insert(p))
            return true;
        if (swu->insert(p))
            return true;
        if (neu->insert(p))
            return true;
        if (seu->insert(p))
            return true;

        std::cout << "quadtree insertion error\n"
                  << p << " " << text(false) << "\n";
        throw std::runtime_error("quadtree insertion error");
    }

    std::vector<c3Point *>
    c3Cell::find(const c3Cell &range)
    {
        myPointsFound.clear();
        findrec(range);
        return myPointsFound;
    }
    void c3Cell::findrec(
        const c3Cell &range)
    {
        //std::cout << "look in " << text(false) << "\n";

        // check that range and cell overlap
        if (!intersect(range))
            return;

        // check if point in cell is in range
        if (myPoint.valid)
            if (range.contains(myPoint))
            {
                //std::cout << "found " << myPoint.text();
                myPointsFound.push_back(&myPoint);
            }
        if (!nwd)
            return;

        // find points in children and range
        nwd->findrec(range);
        swd->findrec(range);
        ned->findrec(range);
        sed->findrec(range);
        nwu->findrec(range);
        swu->findrec(range);
        neu->findrec(range);
        seu->findrec(range);
    }
    bool c3Cell::intersect(const c3Cell &range) const
    {
        float dx = center.x - range.center.x;
        float dy = center.y - range.center.y;
        float dz = center.z - range.center.z;
        float d2 = dx * dx + dy * dy + dz * dz;
        return d2 < (dim + range.dim) * (dim + range.dim);
    }

    std::string c3Cell::text(bool children) const
    {
        std::stringstream ss;
        if (myPoint.valid)
            ss << "point " << myPoint;
        else
            ss << "empty ";
        ss
            << " in cell at " << center
            << " size " << 2 * dim << "\n";
        if (children)
            if (nwd)
            {
                ss << nwd->text();
                ss << swd->text();
                ss << ned->text();
                ss << sed->text();
                ss << nwu->text();
                ss << swu->text();
                ss << neu->text();
                ss << seu->text();
            }
        return ss.str();
    }

}
