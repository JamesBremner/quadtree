# quadtree

A quadtree is used to partition a two-dimensional space by recursively subdividing it into four quadrants or regions. The leaf cell contains a point.  

https://en.wikipedia.org/wiki/Quadtree

# Performance Test
 
 Comparing performance of quadtree and simple search through vector of points in finding neighbours of a point.  If there are less than 1000 points to search, the performance is similar, at less than a microsecond for each search.  For more than 1000 points, the advantage of a quadtree becomes significant.
 
![image](https://user-images.githubusercontent.com/2046227/134812073-3a073669-5281-4bc4-8b2c-7b4aaa894c98.png)

Here is the test code

https://github.com/JamesBremner/quadtree/blob/3820f92b246981c8be9125909bd49057f138c159/src/test.cpp#L45-L79
