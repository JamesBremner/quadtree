#include "cxy.h"

namespace quad
{
    class cCell
    {
    public:
        /** construct empty cell
     * @param[in] p location of cell center
     * @param[in] dim full dimension of cell
     * 
     * top left of cell at p.x - dim/2, p.y - dim/2
     */
        cCell(const cxy &p, float dim);

        ~cCell();

        /** insert point
     * @param[in] p location of point
     * @return true if point inserted into cell or one of cell's children
     */
        bool insert(const cxy &p);

        /** find points in region
     * @param[in] region
     * @return vector of pointers to points in region
     */
        std::vector<cxy *>
        find(const cCell &range);

        /// text
        std::string text(bool children = true) const;

        friend std::ostream &operator<<(std::ostream &os, cCell p)
        {
            if (p.myPoint.isValid())
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
        cxy center;  // point at center of cell
        float dim;      // half dimension of square cell
        cxy myPoint; // point in cell
        cCell *nw;
        cCell *sw;
        cCell *ne;
        cCell *se;
        static std::vector<cxy *> myPointsFound;

        bool contains(const cxy &p) const;
        void subdivide();
        bool childInsert(const cxy &p);
        void findrec(
            const cCell &range);
    };
}
