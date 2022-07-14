namespace quad
{
    class cPoint
    {
    public:
        float x;
        float y;
        bool valid;
        int userData;
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
        cPoint(float X, float Y, int user)
            : x(X),
              y(Y),
              valid(true),
              userData(user)
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

    class cCell
    {
    public:
        /** construct empty cell
     * @param[in] p location of cell center
     * @param[in] dim full dimension of cell
     * 
     * top left of cell at p.x - dim/2, p.y - dim/2
     */
        cCell(const cPoint &p, float dim);

        ~cCell();

        /** insert point
     * @param[in] p location of point
     * @return true if point inserted into cell or one of cell's children
     */
        bool insert(const cPoint &p);

        /** find points in region
     * @param[in] region
     * @return vector of pointers to points in region
     */
        std::vector<cPoint *>
        find(const cCell &range);

        /// text
        std::string text(bool children = true) const;

        friend std::ostream &operator<<(std::ostream &os, cCell p)
        {
            if (p.myPoint.valid)
                os << "point " << p.myPoint;
            else
                os << "empty ";
            os
                << " in cell at " << p.center
                << " size " << 2 * p.dim << "\n";
            return os;
        }
        // true if two ranges intersect
        bool intersect(const cCell &range) const;

    private:
        cPoint center;  // point at center of cell
        float dim;      // half dimension of square cell
        cPoint myPoint; // point in cell
        cCell *nw;
        cCell *sw;
        cCell *ne;
        cCell *se;
        static std::vector<cPoint *> myPointsFound;

        bool contains(const cPoint &p) const;
        void subdivide();
        bool childInsert(const cPoint &p);

        void findrec(
            const cCell &range);
    };
}
