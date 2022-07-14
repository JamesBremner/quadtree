# quadtree

A quadtree is used to partition a two-dimensional space by recursively subdividing it into four quadrants or regions. The leaf cell contains a point.  

https://en.wikipedia.org/wiki/Quadtree

# Performance Test
 
 Comparing performance of quadtree and simple search through vector of points in finding neighbours of a point.  If there are less than 100 points to search, the performance is similar, at less than a microsecond for each search.  For more than 100 points, the advantage of a quadtree becomes significant, so long as you need to do enough searches to pay for the initial cost of building the tree.  All times in the table are microseconds
 
| Points | Vector search 1 point neighbors | Quadtree build | Quadtree search 1 point neighbors |
|---|---|---|---|
100 | 0.5 | 45 | 0.3
500 | 2 | 161 | 0.4
1000 | 5 | 325 | 1
5000 | 20 | 1840 | 1
10000 | 43 | 4000 | 3


