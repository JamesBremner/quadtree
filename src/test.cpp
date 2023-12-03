
#include <iostream>
#include <sstream>
#include <vector>

#include "cRunWatch.h"

#include "cxy.h"
#include "quadtree.h"
#include "octree.h"

// construct vector of randomly located 2D points
std::vector<cxy>
random(int count)
{
    std::vector<cxy> vp;
    for (int k = 0; k < count; k++)
        vp.push_back(
            cxy(
                (rand() % 3800 - 2000) / 100.0,
                (rand() % 3800 - 2000) / 100.0));
    return vp;
}
std::vector<quad::c3Point>
random3(int count)
{
    std::vector<quad::c3Point> vp;
    for (int k = 0; k < count; k++)
        vp.push_back(
            quad::c3Point(
                (rand() % 3800 - 2000) / 100.0,
                (rand() % 3800 - 2000) / 100.0,
                (rand() % 3800 - 2000) / 100.0));
    return vp;
}

/// Linear search point vector for neighbours
std::vector<cxy *>
search(
    std::vector<cxy> &vp,
    const cxy &center,
    float dim)
{
    raven::set::cRunWatch aWatcher("vector_search");
    std::vector<cxy *> fp;
    float dim2 = dim / 2;
    for (auto &tp : vp)
    {
        if (
            center.x - dim2 <= tp.x &&
            tp.x <= center.x + dim2 &&
            center.y - dim2 <= tp.y &&
            tp.y <= center.y + dim2)
            fp.push_back(&tp);
    }
    return fp;
}

/// Search point vector for neighbours using quadtree
std::vector<cxy *>
searchQuad(
    std::vector<cxy> &vp,
    const cxy &center,
    float dim)
{
    using namespace quad;

    cCell* quadtree;

    // construct quadtree of points
    {
        raven::set::cRunWatch aWatcher("construct_quad");
        quadtree = new cCell(cxy(0, 0), 100);
        for (auto &p : vp)
        {
            quadtree->insert(p);
        }
    }

    // quadtree search
    {
        raven::set::cRunWatch aWatcher("search_quad");
        return quadtree->find(
            cCell(cxy(10, 10), dim));
    }

    delete quadtree;
}
std::vector<quad::c3Point *>
searchOct(
    std::vector<quad::c3Point> &vp,
    const quad::c3Point &center,
    float dim)
{
    using namespace quad;

    c3Cell* octree;

    // construct octree of points
    {
        raven::set::cRunWatch aWatcher("construct_oct");
        octree = new c3Cell(c3Point(0, 0, 0), 100);
        for (auto &p : vp)
        {
            octree->insert(p);
        }
    }

    // octree search
    {
        raven::set::cRunWatch aWatcher("search_oct");
        return octree->find(
            c3Cell(c3Point(10, 10, 10), dim));
    }

    delete octree;
}

main()
{
    raven::set::cRunWatch::Start();

    using namespace quad;

    std::cout << "quadtree performace test\n";

    std::vector<int> testcounts{100, 500, 1000, 5000, 10000};
    for (int count : testcounts)
    {
        std::cout << "\nPoint count " << count << "\n";

        // 10 tests with different random points
        for (int test = 0; test < 10; test++)
        {
            // construct vector of random points
            std::vector<cxy> vp = random(count);

            // quadtree search
            auto fp = searchQuad(vp, cxy(10, 10), 2);

            // vector search
            fp = search(vp, cxy(10, 10), 2);

            std::vector<c3Point> vp3 = random3(count);
            auto f2p = searchOct(vp3, c3Point(10, 10, 10), 2);
        }

        raven::set::cRunWatch::Report();
        raven::set::cRunWatch::Clear();
    }
}