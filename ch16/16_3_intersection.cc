#include <bits/stdc++.h>

using namespace std;

struct Point {
    double x;
    double y;

    Point(double a_x, double a_y) {
        x = a_x;
        y = a_y;
    }

    void swap(Point &another) {
        double tmp_x = x;
        double tmp_y = y;
        x = another.x;
        y = another.y;
        another.x = tmp_x;
        another.y = tmp_y;
    }
};

struct Line {
    double slope;
    double y_intercept;

    Line(Point &start, Point &end) {
        double delta_y = end.y - start.y;
        double delta_x = end.x - start.x;
        slope = delta_y / delta_x; // if delta_x = 0.0, slope will be inf.
        y_intercept = end.y - slope * end.x; // y = ax + b => b = y - ax
    }
};

bool is_between(double start, double middle, double end) {
    if (start > end) {
        return end <= middle && middle <= start;
    } else {
        return start <= middle && middle <= end;
    }
}

bool is_between(const Point &start, const Point &middle, const Point &end) {
    return is_between(start.x, middle.x, end.x) 
        && is_between(start.y, middle.y, end.y);
}

Point get_intersection(Point start1, Point end1, Point start2, Point end2) {
    // Rearranging these so that, in order of x values: 
    // start is before end and point1 is before point2.
    // This will make some of the later logic simpler.
    if (start1.x > end1.x) start1.swap(end1);
    if (start2.x > end2.x) start2.swap(end2);
    if (start1.x > start2.x) {
        start1.swap(start2);
        end1.swap(end2);
    }

    // Compute lines (including slope and y-intercept).
    Line line1(start1, end1);
    Line line2(start2, end2);

    // If the lines are parallel, they intercep only if 
    // they have the same y intercept and start 2 is on line 1.
    if (line1.slope == line2.slope) {
        if (line1.y_intercept == line2.y_intercept 
         && is_between(start1, start2, end1)) {
            return start2;
        }
        return Point(std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
    }

    // Get intersection coordinate.
    double x = (line2.y_intercept - line1.y_intercept) / (line1.slope - line2.slope);
    double y = x * line1.slope + line1.y_intercept;
    Point intersection(x, y);

    // check if it's within both line segment range.
    if (is_between(start1, intersection, end1) 
     && is_between(start2, intersection, end2)) {
        return intersection;
    }
    return Point(std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
}

int main(void) {
    Point start1(0.0, 0.0), end1(3.0, 3.0);
    Point start2(0.0, 2.0), end2(2.0, 0.0);

    Point intercept = get_intersection(start1, end1, start2, end2);
    cout << "Interception = (" << intercept.x << ", " << intercept.y << ")" << endl;
    return 0;
}
