namespace quad
{
    class c3Point
    {
    public:
        float x;
        float y;
        float z;
        bool valid;
        int userData;
        c3Point()
            : valid(false)
        {
        }
        c3Point(float X, float Y, float Z)
            : x(X),
              y(Y),
              z(Z),
              valid(true)
        {
        }
        c3Point(float X, float Y, float Z, int user)
            : x(X),
              y(Y),
              z(Z),
              valid(true),
              userData(user)
        {
        }
        bool operator==(const c3Point &o) const
        {
            float min = 0.01;
            if (!valid)
                return false;
            if (!o.valid)
                return false;
            return (
                std::fabs(x - o.x) < min &&
                std::fabs(y - o.y) < min &&
                std::fabs(z - o.z) < min);
        }
        friend std::ostream &operator<<(std::ostream &os, c3Point p)
        {
            os << "(" << p.x << "," << p.y << "," << p.z << ")";
            return os;
        }
    };

    class c3Cell
    {
    public:
        /** construct empty cell
         * @param[in] p location of cell center
         * @param[in] dim full dimension of cell
         *
         * top left of cell at p.x - dim/2, p.y - dim/2
         */
        c3Cell(const c3Point &p, float dim);

        c3Cell(
            const c3Point &center,
            float dim,
            const std::vector< c3Point >& vp );

        ~c3Cell();

        /** insert point
         * @param[in] p location of point
         * @return true if point inserted into cell or one of cell's children
         */
        bool insert(const c3Point &p);

        /** find points in region
         * @param[in] region
         * @return vector of pointers to points in region
         */
        std::vector<c3Point *>
        find(const c3Cell &range);

        /// text
        std::string text(bool children = true) const;

        // true if two ranges intersect
        bool intersect(const c3Cell &range) const;

        bool isLeaf() const
        {
            return nwd == 0;
        }

    private:
        c3Point center;  // point at center of cell
        float dim;      // half dimension of square cell
        c3Point myPoint; // point in cell
        c3Cell *nwd;
        c3Cell *swd;
        c3Cell *ned;
        c3Cell *sed;
        c3Cell *nwu;
        c3Cell *swu;
        c3Cell *neu;
        c3Cell *seu;
        static std::vector<c3Point *> myPointsFound;

        bool contains(const c3Point &p) const;
        void subdivide();
        bool childInsert(const c3Point &p);

        void findrec(
            const c3Cell &range);
    };
}
