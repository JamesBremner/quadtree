namespace quad
{
    class cPoint
    {
    public:
        float x;
        float y;
        bool valid;
        cPoint()
            : valid(false)
        {
        }
        cPoint(float X, float Y)
            : x(X),
              y(Y),
              valid(true)
        {
        }
        bool operator==(const cPoint &o) const
        {
            float min = 0.01;
            if (!valid)
                return false;
            if (!o.valid)
                return false;
            return fabs(x - o.x) < min && fabs(y - o.y) < min;
        }
        friend std::ostream &operator<<(std::ostream &os, cPoint p)
        {
            os << "(" << p.x << "," << p.y << ")";
            return os;
        }
    };

    typedef std::shared_ptr<cPoint> point_t;

    class cCell
    {
    public:
        /** construct empty cell
     * @param[in] p location of cell center
     * @param[in] dim dimension of cell
     */
        cCell(point_t p, float dim);

        ~cCell();

        /** insert point
     * @param[in] p location of point
     * @return true if point inserted into cell or one of cell's children
     */
        bool insert(point_t p);

        /** find points in region
     * @param[in] region
     * @return vector of pointers to points in region
     */
        std::vector<point_t >
        find(const cCell &range);

        /// text
        std::string text(bool children = true) const;

        friend std::ostream &operator<<(std::ostream &os, cCell p)
        {
            if (p.myPoint->valid)
                os << "point " << p.myPoint;
            else
                os << "empty ";
            os
                << " in cell at " << p.center
                << " size " << 2 * p.dim << "\n";
            return os;
        }

    private:
        point_t  center;  // point at center of cell
        float dim;      // half dimension of square cell
        point_t  myPoint; // point in cell
        cCell *nw;
        cCell *sw;
        cCell *ne;
        cCell *se;
        static std::vector<point_t > myPointsFound;

        bool contains(point_t p) const;
        void subdivide();
        bool childInsert(point_t p);
        bool intersect(const cCell &range) const;
        void findrec(
            const cCell &range);
    };
}
