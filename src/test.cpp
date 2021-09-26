
#include <iostream>
#include <sstream>
#include <vector>

#include "cRunWatch.h"

#include "quadtree.h"

// construct vector of randomly located points
std::vector<quad::cPoint>
random(int count)
{
    std::vector<quad::cPoint> vp;
    for (int k = 0; k < count; k++)
        vp.push_back(
            quad::cPoint(
                (rand() % 3800 - 2000) / 100.0,
                (rand() % 3800 - 2000) / 100.0));
    return vp;
}

/// Linear search point vector for neighbours
std::vector<quad::cPoint *>
search(
    std::vector<quad::cPoint> &vp,
    const quad::cPoint &center,
    float dim)
{
    raven::set::cRunWatch aWatcher("search");
    std::vector<quad::cPoint *> fp;
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

main()
{
    raven::set::cRunWatch::Start();

    using namespace quad;

    std::cout << "quadtree performace test\n";

    std::vector<int> testcounts { 100, 500, 1000, 5000, 10000 };
    for (int count : testcounts )
    {

        std::cout << "\nPoint count " << count << "\n";

        for (int test = 0; test < 10; test++)
        {
            // construct vector of random points
            std::vector<cPoint> vp = random(count);

            // construct quadtree of points
            cCell quadtree(cPoint(0, 0), 100);
            for (auto &p : vp) {
                quadtree.insert(p);
            }

            // quadtree search
            auto fp = quadtree.find(cCell(cPoint(10, 10), 2));

            // vector search
            fp = search(vp, quad::cPoint(10, 10), 2);
        }

        raven::set::cRunWatch::Report();
        raven::set::cRunWatch::Clear();
    }
}