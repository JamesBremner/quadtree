namespace quad {
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
    std::string text()
    {
        std::stringstream ss;
        ss << "(" << x << "," << y << ")";
        return ss.str();
    }
};

class cCell
{
public:
    /** construct empty cell
     * @param[in] p location of cell center
     * @param[in] dim dimension of cell
     */
    cCell(const cPoint &p, float dim);

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
    std::string text( bool children = true );

private:
    cPoint center;  // point at center of cell
    float dim;      // half dimension of square cell
    cPoint myPoint; // point in cell
    cCell *nw;
    cCell *sw;
    cCell *ne;
    cCell *se;

    bool contains(const cPoint &p) const;
    void subdivide();
    bool childInsert(const cPoint &p);
    bool intersect(const cCell &range) const;
    void findrec(
        const cCell &range,
        std::vector<cPoint *>& vp );
};
}
