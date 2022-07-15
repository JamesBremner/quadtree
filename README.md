# quadtree

A quadtree is used to partition a two-dimensional space by recursively subdividing it into four quadrants or regions. The leaf cell contains a point.  

https://en.wikipedia.org/wiki/Quadtree

# octree

A octree is used to partition a three-dimensional space by recursively subdividing it into eight regions. The leaf cell contains a point.  

# Performance Test
 
 Comparing performance of quadtree and simple search through vector of points in finding neighbours of a point.  If there are less than 100 points to search, the performance is similar, at less than a microsecond for each search.  For more than 100 points, the advantage of a quadtree becomes significant, so long as you need to do enough searches to pay for the initial cost of building the tree.  All times in the table are microseconds
 
| Points | 2D Vector search<br> 1 point neighbors | Quadtree build | Quadtree search<br> 1 point neighbors | Octree build | Octree search
|---|---|---|---|---|---|
100 | 0.5 | 45 | 0.3| 64| 1
500 | 2 | 161 | 0.4||
1000 | 5 | 3250 | 1 ||
5000 | 20 | 18400 | 1 |24000|3
10000 | 43 | 40000 | 3 |55000|7

# Usage

```C++
    // construct point cloud
    std::vector<quad::c3Point> vp;
    vp.push_back(c3Point(5, 5, 5));
    vp.push_back(c3Point(25, 5.1, 5));
    vp.push_back(c3Point(25, 5.2, 5));
    vp.push_back(c3Point(25, 5, 5.3));

    // construct octree containing point cloud
    c3Cell octree(
        c3Point(0, 0, 0),       /// octree centered at origin
        100,                    /// octree extent, cube with sides 100 units
        vp);                    /// points

    // vector of pointers to points within 2 units of 4,4,4
    auto neighbors = octree.find(
        c3Cell(c3Point(4, 4, 4),
        2));
```
