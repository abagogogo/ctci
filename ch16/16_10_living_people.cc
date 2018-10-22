#include <bits/stdc++.h>

using namespace std;

struct People {
    int birth;
    int death;

    People(int birth_year, int death_year) {
        birth = birth_year;
        death = death_year;
    }
};

#define BRUTE_FORCE 1
#define SORTING     2
#define COUNTING    3
#define METHOD COUNTING //SORTING //BRUTE_FORCE

#if METHOD==BRUTE_FORCE
int get_max_alive_year(vector<People> &people, int min, int max) {
    int years = max - min + 1;
    int cnt[years];
    memset(cnt, 0, sizeof(cnt));

    int max_alive = 0;
    int max_idx  = 0;
    for (auto p : people) {
        for (int i = p.birth; i <= p.death; ++i) {
            cnt[i-min]++;
        }
    }
    for (int i = 0; i < years; ++i) {
        if (cnt[i] > max_alive) {
            max_alive = cnt[i];
            max_idx = i; 
        }
    }
    return min + max_idx;
}
#elif METHOD==SORTING
void get_sorted_years(vector<People> &people, vector<int> &years, bool copy_birth_year) {
    for (auto p : people) {
        years.push_back(copy_birth_year ? p.birth : p.death);
    }
    sort(years.begin(), years.end());
}

int get_max_alive_year(vector<People> &people, int min, int max) {
    vector<int> birth_years;
    vector<int> death_years;

    get_sorted_years(people, birth_years, true);
    get_sorted_years(people, death_years, false);

    int bi = 0;
    int di = 0;
    int max_alive = 0;
    int alive_cnt = 0;
    int max_idx = 0;
    while (bi < birth_years.size()) {
        if (birth_years[bi] <= death_years[di]) {
            ++alive_cnt;
            if (alive_cnt > max_alive) {
                max_alive = alive_cnt;
                max_idx = birth_years[bi];
            }
            ++bi;
        } else {
            --alive_cnt;
            ++di;
        }
    }
    return min + max_idx;
}
#elif METHOD==COUNTING
int get_max_alive_year(vector<People> &people, int min, int max) {
    int delta[max - min + 2];

    memset(delta, 0, sizeof(delta));
    for (auto p : people) {
        delta[p.birth - min]++;
        delta[p.death + 1 - min]--;
    }

    int max_alive = 0;
    int max_idx = 0;
    int sum = 0;
    for (int i = 0; i < max - min + 2; ++i) {
        sum += delta[i];
        if (sum > max_alive) {
            max_alive = sum;
            max_idx = i;
        }
    }
    return min + max_idx;
}
#endif

int main(void) {
    vector<People> people = {
        {12, 15},
        {20, 90},
        {10, 98},
        { 1, 72},
        {10, 98},
        {23, 82},
        {13, 98},
        {83, 99},
        {75, 94}};

    cout << get_max_alive_year(people, 0, 100) << endl;;
    return 0;
}
