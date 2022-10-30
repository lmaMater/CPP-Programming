#include <iostream>

using namespace std;

class Point {
private:
    double x;
    double y;
public:
    Point() {
        x = 0;
        y = 0;
    }

    Point(double x_pos, double y_pos)
            : x(x_pos), y(y_pos) {}

    [[nodiscard]]
    double getX() const {
        return x;
    }

    [[nodiscard]]
    double getY() const {
        return y;
    }

    static string to_string() {
        return format("(%d, %d)", 1, 2);
    }
};