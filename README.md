# quadtree

A quadtree is used to partition a two-dimensional space by recursively subdividing it into four quadrants or regions. The leaf cell contains a point.  

https://en.wikipedia.org/wiki/Quadtree

# octree

A octree is used to partition a three-dimensional space by recursively subdividing it into eight regions. The leaf cell contains a point.  

# Performance Test
 
 Comparing performance of quadtree and simple search through vector of points in finding neighbours of a point.  If there are less than 100 points to search, the performance is similar, at less than a microsecond for each search.  For more than 100 points, the advantage of a quadtree becomes significant, so long as you need to do enough searches to pay for the initial cost of building the tree.  All times in the table are microseconds
 
| Points | Vector search<br> 1 point neighbors | Quadtree build | Quadtree search<br> 1 point neighbors | Octree build | Octree search
|---|---|---|---|---|---|
100 | 0.5 | 45 | 0.3| 64| 1
500 | 2 | 161 | 0.4||
1000 | 5 | 3250 | 1 ||
5000 | 20 | 18400 | 1 |24000|3
10000 | 43 | 40000 | 3 |55000|7


