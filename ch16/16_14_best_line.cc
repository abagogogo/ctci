#include <bits/stdc++.h>

using namespace std;

static double epsilon = 0.0001;

struct Point {
    double x;
    double y;
};

struct Line {
    double slope;
    double intercept;
    bool infinite_slope;

    Line() {
        infinite_slope = false;
    }

    Line(const Point &p, const Point &q) {
        if (abs(p.x - q.x) > epsilon) { // if x's are different
            slope = (p.y - q.y) / (p.x - q.x); // compute slope
            intercept = p.y - slope * p.x; // slope = (intercept - py) / (0 - px)
        } else {
            infinite_slope = true;
            intercept = p.x;
        }
    }

    double floor_to_nearest_epsilon(double d) {
        int r = (int)(d / epsilon);
        return ((double) r) * epsilon;
    }

    bool is_equivalent(double a, double b) {
        return abs(a - b) < epsilon;
    }

    bool is_equivalent(Line *another) {
        if (is_equivalent(another->slope, this->slope) &&
            is_equivalent(another->intercept, this->intercept) &&
            is_equivalent(another->infinite_slope, this->infinite_slope)) {
            return true;
        } else {
            return false;
        }
    }
};

struct Solution {
    using SLOPE_MAP = unordered_map<double, vector<Line *>>;

    Line* find_best_line(vector<Point> &points) {
        SLOPE_MAP lines_by_slope = get_list_of_lines(points);
        return get_best_line(lines_by_slope);
    }
    
    SLOPE_MAP get_list_of_lines(vector<Point> &points) {
        SLOPE_MAP lines_by_slope;
        for (int i = 0; i < points.size(); ++i) {
            for (int j = i + 1; j < points.size(); ++j) {
                Line* line = new Line(points[i], points[j]);
                double key = line->floor_to_nearest_epsilon(line->slope);
                //cout << "[DBG] line: slope=" << line->slope << ", intercept=" << line->intercept << ", infinite_slope=" << line->infinite_slope << endl;
                //cout << "[DBG] key=" << key << endl;
                lines_by_slope[key].push_back(line);
            }
        }
        return lines_by_slope;
    }

    Line* get_best_line(SLOPE_MAP &lines_by_slope) {
        Line *best_line = nullptr;
        int best_cnt = 0;

        for (auto it = lines_by_slope.begin(); it != lines_by_slope.end(); ++it) {
            double slope = it->first;
            auto lines = it->second;
            cout << "[DBG] get_best_line(): slope=" << slope << ", #lines=" << lines.size() << endl;

            for (auto line : lines) {
                int cnt = count_equivalent_lines(lines_by_slope, line);
                if (cnt > best_cnt) {
                    //cout << "[DBG] get_best_line(): slope=" << slope << ", cnt=" << cnt << endl;
                    best_cnt = cnt;
                    best_line = line;
                }
            }
        }
        return best_line;
    }

    int count_equivalent_lines(SLOPE_MAP &lines_by_slope, Line *line) {
        double key = line->floor_to_nearest_epsilon(line->slope);
        int cnt = count_equivalent_lines(lines_by_slope[key], line);
        cnt += count_equivalent_lines(lines_by_slope[key - epsilon], line);
        cnt += count_equivalent_lines(lines_by_slope[key + epsilon], line);
        return cnt;
    }

    int count_equivalent_lines(vector<Line *> lines, Line *line) {
        int cnt = 0;
        for (auto parallel_line :lines) {
            if (parallel_line->is_equivalent(line)) cnt++;
        }
        return cnt;
    }
};

int main(void) {
    Solution sol;
    //vector<Point> points = {{0.0, 0.0}, {2.0, 0.0}, {1.0, 1.0}, {2.0, 2.0}};
    vector<Point> points = {{0.0, 0.0}, {1.0, 1.0}, {2.0, 2.0}, {2.0, 0.0}};

    Line* line = sol.find_best_line(points);
    cout << "line: slope=" << line->slope << ", intercept=" << line->intercept << ", infinite_slope=" << line->infinite_slope << endl;
 
    return 0;
}
