#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include "cutest.h"
#include "octree.h"
#include "quadtree.h"

using namespace quad;

TEST(quad_intersect)
{
    // test range: 10 unit square centred at 5,5
    cCell range(cPoint(5, 5), 10);
    cCell p1(cPoint(5, 5), 1);
    CHECK(
        range.intersect(p1));
    cCell p2(cPoint(50, 50), 1);
    CHECK(
        !range.intersect(p2));
}

TEST(oct_intersect)
{
    // test range: 10 unit cube centred at 5,5,5
    c3Cell range(c3Point(5, 5, 5), 10);
    c3Cell p1(c3Point(5, 5, 5), 1);
    CHECK(
        range.intersect(p1));
    c3Cell p2(c3Point(50, 50, 50), 1);
    CHECK(
        !range.intersect(p2));
}

TEST(oct_insert)
{
    // an empty leaf
    c3Cell t(c3Point(5, 5, 5), 10);
    CHECK(t.isLeaf());

    // a leaf with a point
    CHECK(t.insert(c3Point(4, 4, 4)));
    CHECK(t.isLeaf());

    // a parent
    CHECK(t.insert(c3Point(6, 6, 6)));
    CHECK(!t.isLeaf());
}

TEST(quadtree)
{
    std::vector<quad::cPoint> vp;
    vp.push_back(cPoint(5, 5));
    cCell quadtree(cPoint(0, 0), 100);
    for (auto &p : vp)
    {
        quadtree.insert(p);
    }
    auto r = quadtree.find(
        cCell(cPoint(4, 4), 2));
    CHECK_EQUAL(1, r.size());
    r.clear();
    r = quadtree.find(
        cCell(cPoint(1, 1), 2));
    CHECK_EQUAL(0, r.size());
}

TEST(octree)
{
    // construct point cloud
    std::vector<quad::c3Point> vp;
    vp.push_back(c3Point(5, 5, 5));
    vp.push_back(c3Point(25, 5.1, 5));
    vp.push_back(c3Point(25, 5.2, 5));
    vp.push_back(c3Point(25, 5, 5.3));

    // construct octree containing point cloud
    c3Cell octree(
        c3Point(0, 0, 0),
        100,
        vp);

    auto r = octree.find(
        c3Cell(c3Point(4, 4, 4), 2));
    CHECK_EQUAL(1, r.size());
    CHECK(r[0]->x == 5 && r[0]->y == 5 && r[0]->z == 5);

    r.clear();
    r = octree.find(
        c3Cell(c3Point(4, 4, 7), 2));
    CHECK_EQUAL(0, r.size());

    r.clear();
    r = octree.find(
        c3Cell(c3Point(25, 5, 5), 2));
    CHECK_EQUAL(3, r.size());
}

int main()
{
    raven::set::UnitTest::RunAllTests();
    return 0;
}
