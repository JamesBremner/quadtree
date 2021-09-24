
#include <iostream>
#include <sstream>
#include <vector>

#include "cRunWatch.h"

#include "quadtree.h"

main()
{
    raven::set::cRunWatch::Start();

    using namespace quad;

    std::cout << "quadtree\n";

    std::vector< cPoint > vp {
        { 10, 10 },
        { 5, 5 }
    };

    cCell quadtree(cPoint(0, 0), 100);

    for ( auto& p : vp )
        quadtree.insert( p );


    std::cout << quadtree.text() << "\n";

    auto fp = quadtree.find(cCell(cPoint(10, 10), 20));
    for (auto p : fp)
        std::cout << p->text() << " ";
    std::cout << "\n";
    fp = quadtree.find(cCell(cPoint(10, 10), 2));
    for (auto p : fp)
        std::cout << p->text() << " ";
    std::cout << "\n";

    raven::set::cRunWatch::Report();
}