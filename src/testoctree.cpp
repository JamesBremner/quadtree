
#include <iostream>
#include <sstream>
#include <vector>

#include "cRunWatch.h"

#include "octree.h"

// construct vector of randomly located points
std::vector<quad::c3Point>
random(int count)
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
std::vector<quad::c3Point *>
search(
    std::vector<quad::c3Point> &vp,
    const quad::c3Point &center,
    float dim)
{
    raven::set::cRunWatch aWatcher("vector_search");
    std::vector<quad::c3Point *> fp;
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
std::vector<quad::c3Point *>
searchOct(
    std::vector<quad::c3Point> &vp,
    const quad::c3Point &center,
    float dim)
{
    using namespace quad;

    c3Cell* octree;

    // construct quadtree of points
    {
        raven::set::cRunWatch aWatcher("construct_oct");
        octree = new c3Cell(c3Point(0, 0, 0), 100);
        for (auto &p : vp)
        {
            octree->insert(p);
        }
    }

    // quadtree search
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
            std::vector<c3Point> vp = random(count);

            // quadtree search
            auto fp = searchOct(vp, c3Point(10, 10, 10), 2);

            // vector search
            fp = search(vp, quad::c3Point(10, 10, 10), 2);
        }

        raven::set::cRunWatch::Report();
        raven::set::cRunWatch::Clear();
    }
}