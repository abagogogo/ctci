#include <bits/stdc++.h>

using namespace std;

using Endpoint = vector<double>;
using Square   = vector<Endpoint>;
using Line     = vector<Endpoint>;

bool equal_line(const Line &l1, const Line &l2) {
    return l1[0][0] == l2[0][0] && l1[0][1] == l2[0][1] && l1[1][0] == l2[1][0] && l1[1][1] == l2[1][1];
}

struct Solution {
    
    Line bisect(const Square &s0, const Square &s1) {
        // find median of each square
        Endpoint m0 = find_median(s0);
        Endpoint m1 = find_median(s1);
    
        double dx = m0[0] - m1[0];
        double dy = m0[1] - m1[1];
        
        if (dx == 0.0) {
            // slop = inf
            const Square &upper = (m0[1] <= m1[1]) ? s0 : s1;
            const Square &lower = (m0[1] >  m1[1]) ? s0 : s1;

            double mx = m0[0];
            double uy = upper[0][1];
            double ly = lower[1][1];
            return {{mx, uy}, {mx, ly}};
        } else if (dy == 0.0) {
            // slop = 0
            const Square &left  = (m0[0] <= m1[0]) ? s0 : s1;
            const Square &right = (m0[0] >  m1[0]) ? s0 : s1;

            double my = m0[1];
            double lx = left[0][0];
            double rx = right[1][0];
            return {{lx, my}, {rx, my}};
        } 
        
        double slope = dy / dx;
        if (abs(slope) <= 1.0) {
            // slop <= 1
            const Square &left  = (m0[0] <= m1[0]) ? s0 : s1;
            const Square &right = (m0[0] >  m1[0]) ? s0 : s1;

            // y - m0[1] / x - m0[0] = slope
            double lx = left[0][0];
            double ly = slope * (lx - m0[0]) + m0[1];

            // m0[1] - y / m0[0] - x = slope
            double rx = right[1][0];
            double ry = slope * (rx - m0[0]) + m0[1];
            return {{lx, ly}, {rx, ry}};
        } else {
            // slop > 1
            const Square &upper = (m0[1] <= m1[1]) ? s0 : s1;
            const Square &lower = (m0[1] >  m1[1]) ? s0 : s1;

            // y - m0[1] / x - m0[0] = slope
            double ly = upper[0][1];
            double lx = (ly - m0[1]) / slope + m0[0];
            double ry = lower[1][1];
            double rx = (ry - m0[1]) / slope + m0[0];
            return {{lx, ly}, {rx, ry}};
        }
    }

    Endpoint find_median(const Square s) {
        double x = (s[0][0] + s[1][0]) / 2.0;
        double y = (s[0][1] + s[1][1]) / 2.0;
        return {x, y};
    }
};

int main(void) {
    Solution sol;

    vector<pair<Square, Square>> tests = {
        {{{0.0, 0.0}, {3.0, 3.0}}, {{0.0, 5.0}, {3.0, 8.0}}},
        {{{0.0, 0.0}, {3.0, 3.0}}, {{5.0, 0.0}, {8.0, 3.0}}},
        {{{0.0, 0.0}, {3.0, 3.0}}, {{5.0, 5.0}, {8.0, 8.0}}},
        {{{0.0, 5.0}, {3.0, 8.0}}, {{3.0, 2.0}, {6.0, 5.0}}},
        };
    vector<Line> answers = {
        {{1.5, 0.0}, {1.5, 8.0}},
        {{0.0, 1.5}, {8.0, 1.5}},
        {{0.0, 0.0}, {8.0, 8.0}},
        {{0.0, 8.0}, {6.0, 2.0}},
        };

    for (int i = 0; i < tests.size(); ++i) {
        auto test = tests[i];
        auto ans  = answers[i];

        Line result = sol.bisect(test.first, test.second);
        cout << (equal_line(result, ans) ? "[PASS]" : "[FAIL]") << " Test " << i << endl;

        for (auto sq : {test.first, test.second}) {
            cout << "Square: (" << sq[0][0] << ", " << sq[0][1] << ")";
            cout << " - (" << sq[1][0] << ", " << sq[1][1] << ")" << endl; 
        }
        cout << "Result: ";
        for (int i = 0; i < 2; ++i) {
            auto pt = result[i];
            cout << "(" << pt[0] << ", " << pt[1] << ")";
            if (i == 0) cout << " - ";
        }
        cout << endl;
    }

    return 0;
}
