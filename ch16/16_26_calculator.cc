#include <bits/stdc++.h>

using namespace std;

struct Solution {
    unordered_map<char,int> priority;

    Solution() {
        priority[' '] = 0; // blank for termination.
        priority['+'] = 1;
        priority['-'] = 1;
        priority['*'] = 2;
        priority['/'] = 2;
    }

    double eval(string sequence) {
        stack<double> val_stack;
        stack<char>   op_stack;

        int i = 0; 
        while (i < sequence.length()) {
            // get number and push
            int value = parse_number(sequence, i);
            val_stack.push((double)value);

            // move to the operator
            if (i >= sequence.length()) break;
            char op = parse_operator(sequence, i);
            collapse_top(op, val_stack, op_stack);
            op_stack.push(op);
        }

        // do final collapse
        collapse_top(' ', val_stack, op_stack);
        if (val_stack.size() == 1 && op_stack.size() == 0) 
            return val_stack.top();
        return 0;
    }

    void collapse_top(char new_op, stack<double> &val_stack, stack<char> &op_stack) {
        while (op_stack.size() >= 1 && val_stack.size() >= 2 &&
               priority[new_op] <= priority[op_stack.top()]) {

            double second = val_stack.top(); val_stack.pop();
            double first = val_stack.top(); val_stack.pop();
            char op = op_stack.top(); op_stack.pop();
            double collapsed = calc_op(first, op, second);
            val_stack.push(collapsed);
        }
    }

    double calc_op(double first, char op, double second) {
        if (op == '+') return first + second;
        else if (op == '-') return first - second;
        else if (op == '*') return first * second;
        else if (op == '/') return first / second;
        else return second;
    }

    int parse_number(string &seq, int &offset) {
        int num = 0;
        while (offset < seq.length() && seq[offset] >= '0' && seq[offset] <= '9') {
            num *= 10;
            num += seq[offset++] - '0';
        }
        return num;
    }

    char parse_operator(string &seq, int &offset) {
        if (offset < seq.length()) {
            char op = seq[offset++];
            return op;
        }
        return ' ';
    }
};

int main(void) {
    Solution sol;

    string expr = "2*3+5/6*3+15";
    double ans = 23.5;

    double res = sol.eval(expr);
    cout << (ans == res ? "[PASS]" : "[FAIL]") << expr << " = " << res << endl;
    return 0;
}
