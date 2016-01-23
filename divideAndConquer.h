#include <vector>

class Coord {
public:
    double x, y, x1, y1, distance = DBL_MAX;
    void operator=(const Coord &c )
    {
        this->x = c.x;
        this->y = c.y;
        this->x1 = c.x1;
        this->y1 = c.y1;
        this->distance = c.distance;
    }
    void setCoord(double x, double y){
        this->x = x;
        this->y = y;
    }
    void setClosestPair(double x, double y, double distance){
        this->x1 = x;
        this->y1 = y;
        this->distance = distance;
    }
};

Coord bruteForce(Coord c[], int n);
Coord bruteForce(std::vector<Coord> c, int n);
int compareX(const void* a, const void* b);
int compareY(const void* a, const void* b);
void bruteAlgorithm();
void divideAndConquer();
Coord divideAndConquerRec(int indexValue, Coord c[]);
void divideAndConquerOptimal();
Coord divideAndConquerRecOptimal(int indexValue, std::vector<Coord> cX, std::vector<Coord> cY);
Coord stripClosest(int size, double min, Coord c[]);
Coord stripClosestOptimal(int size, double min, std::vector<Coord> c);
double calcDistance(Coord c1, Coord c2);
bool isEqual(double a, double b);
bool vSortY(const Coord a, const Coord b);
bool vSortX(const Coord a, const Coord b);
