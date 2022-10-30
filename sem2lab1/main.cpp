#include <iostream>
#include <vector>
#include <cmath>
#include "point.h"
#include "polygonal_chain.h"

using namespace std;

//3. Замкнутая ломаная
class ClosedPolygonalChain : public PolygonalChain {
public:
    explicit ClosedPolygonalChain(const vector<Point> &vec)
            : PolygonalChain(vec) {
        if (vec.begin() != vec.end()) {
            //throw MismatchException();
        }
    }
};

// Площадь: формула шнуровки
//4. Многоугольник
class Polygon {
protected:
    ClosedPolygonalChain contour;
public:
    explicit Polygon(vector<Point> &vec)
            : contour(vec) {
        if (vec.size() < 3) {
            // throw WrongPointsAmountException();
        }
    }

    double Perimeter() {
        return contour.Perimeter();
    }

    static double Area() {
        double area = 0;;
        return area;
    }
};

//5. Треугольник
class Triangle : public Polygon {
public:
    explicit Triangle(vector<Point> &vec)
            : Polygon(vec) {
        if (vec.size() != 3) {
            // throw Exception;
        }
    }
};

//6. Трапеция
bool areParallel(pair<Point, Point> line1, pair<Point, Point> line2) {
    bool verdict = true;
    ///////////////
    return verdict;
}
bool isTrapezoid(Point p1, Point p2, Point p3, Point p4) {
    bool verdict1 = areParallel(make_pair(p1, p2), make_pair(p3, p4));
    bool verdict2 = areParallel(make_pair(p1, p4), make_pair(p2, p3));

    return verdict1 ^ verdict2;
}

class Trapezoid : public Polygon {
public:
    explicit Trapezoid(vector<Point> &vec)
            : Polygon(vec) {
        if (vec.size() != 4) {
            // throw WrongPointsAmountException();
        }

        if (!isTrapezoid(vec[0], vec[1], vec[2], vec[3])) {
            // throw WrongShapeException();
        }
    }
};
//7. Правильный многоугольник

bool isRegularPolygon(vector<Point>& vec) {
    bool verdict = true;
    ;
    return verdict;
}

class RegularPolygon : public Polygon {
public:
    explicit RegularPolygon(vector<Point> &vec)
            : Polygon(vec) {
        if (vec.size() != 4) {
            // throw WrongPointsAmountException();
        }

        if (!isRegularPolygon(vec)) {
            // throw WrongShapeException();
        }
    }
};

/*
class LineSegment {
private:
    Point begin;
    Point end;
    float length;
public:
    LineSegment(Point begin_point, Point end_point) {
        begin = begin_point;
        end = end_point;
        length = sqrt(
                pow((end.getX() - begin.getX()), 2)
                + pow((end.getY() - begin.getY()), 2)
                );
    }

    Point getBegin(){
        return begin;
    }

    Point getEnd() {
        return end;
    }

    float getLength() {
        return length;
    }

    void print() {
        cout << "(" << begin.getX() << ", " <<  begin.getY() << ")";
        cout << " - ";
        cout << "(" << end.getX() << ", " <<  end.getY() << ")";
    }
};

class PolygonalChain {
private:
    int length;
    vector<LineSegment> segments;
public:
    PolygonalChain(int segments_amount, LineSegment segment, ...){
        length = segments_amount;
        LineSegment *ptr = &segment;

        for (int i = 0; i < length; i++) {
            segments.push_back(*(ptr++));
        }
    }

    PolygonalChain(vector<LineSegment> segments){
        length = segments.size();

    }
    void print() {
        for (LineSegment segment : segments) {
            segment.print();
            cout << '\n';
        }
    }

};
*/

int main() {
    Point a(1, 2);
    cout << a;
    cout << "\n\n\n\n";
    vector<Point> pts;
    pts.emplace_back(-1, 1);
    pts.emplace_back(1, 1);
    pts.emplace_back(1, -1);

    PolygonalChain chain();

    string s = " ";
    cout << s.length();

    return 0;
}
