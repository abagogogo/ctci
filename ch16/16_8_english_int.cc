#include <bits/stdc++.h>

using namespace std;

string smalls[] = {"Zero", "One", "Two", "Three", "Four", 
                   "Five", "Six", "Seven", "Eight", "Nine",
                   "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen",
                   "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"}; 

string tens[] = {"", "", "Twenty", "Thirty", "Fourty", "Fifty",
                 "Sixty", "Seventy", "Eighty", "Ninety"};

string hundred = "Hundred";

string bigs[] = {"", "Thousand", "Million", "Billion"};

string negative = "Negative";

string deque_to_string(const deque<string> &parts);
string convert_chunk(int num);

string convert(int num) {
    if (num == 0) return smalls[0]; // 0 is a special case.
    if (num < 0) return negative + " " + convert(-num);

    deque<string> parts;
    int idx = 0;
    while (num > 0) {
        if (num % 1000 != 0) { 
            string chunk = convert_chunk(num % 1000) + " " + bigs[idx];
            parts.push_front(chunk);
        } // else we skip chunk with 0.
        num /= 1000;
        ++idx;
    }

    return deque_to_string(parts);
}

string deque_to_string(const deque<string> &parts) {
    int len = 0;
    for (auto str : parts) len += (str.length() + 1);
    
    string ans;
    ans.reserve(len);
    for (int i = 0; i < parts.size() - 1; ++i) {
        ans += parts[i] + " ";
    }
    if (!parts.empty()) ans += parts.back();
    return ans;
}

string convert_chunk(int num) {
    deque<string> parts;

    // Convert hundred place
    if (num >= 100) {
        parts.push_back(smalls[num / 100]);
        parts.push_back(hundred);
        num = num % 100;
    }

    // Convert tens place
    if (num >= 10 && num <= 19) {
        parts.push_back(smalls[num]);
    } else if (num >= 20) {
        parts.push_back(tens[num / 10]);
        num = num % 10;
    }

    // Convert ones place. 0 has been done before.
    if (num >= 1 && num <= 9) {
        parts.push_back(smalls[num]);
    }

    return deque_to_string(parts);
}

int main(void) {
    int num; 
    num = 0;
    cout << num << " = " << convert(num) << endl;
    num = 1234;
    num = 1234;
    cout << num << " = " << convert(num) << endl;
    num = 19323984;
    cout << num << " = " << convert(num) << endl;
    num = 2000000000;
    cout << num << " = " << convert(num) << endl;
    return 0;
}
