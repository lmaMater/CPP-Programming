#include "point.h"

using namespace std;

class PolygonalChain {
protected:
    int number_of_points;
public:
    vector <Point> points;

    [[maybe_unused]]
    PolygonalChain(int length, Point point, ...) {
        number_of_points = length;

        Point *ptr = &point;
        for (int i = 0; i < number_of_points; i++, ptr++) {
            points.push_back(*ptr);
        }
    }

    explicit PolygonalChain(const vector <Point> &vec)
            : number_of_points(int(vec.size())), points(vec) {}

    double Perimeter() {
        double perimeter = 0;
        for (int i = 0; i < number_of_points - 1; i++) {
            perimeter += sqrt(
                    pow(points[i + 1].getX() - points[i].getX(), 2)
                    + pow(points[i + 1].getY() - points[i].getY(), 2)
            );
        }
        return perimeter;
    }

    void print() {
        cout << "{\n";
        for (Point point: points) {
            point.print();
            cout << "\n";
        }
        cout << "}\n";
    }
};