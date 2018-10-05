#include <iostream>
#include <vector>

using namespace std;

void perm(char *data, int cnt, vector< vector<char> > *result)
{
    vector< vector<char> > tmp;

    if (cnt == 1) {
        result->push_back(vector<char>(data, data+1));
        return;
    }
    perm(data, cnt - 1, &tmp);

    for (int i = 0; i < tmp.size(); i++) {
        for (int j = 0; j < cnt; j++) {
            result->push_back(tmp[i]);

            vector<char> &curr = result->back();
            curr.insert(curr.begin() + j, data[cnt-1]);
        }
    }
}

void permutate(char *data, int cnt)
{
    vector< vector<char> >result; 

    perm(data, cnt, &result);
    for (int i = 0; i < result.size(); i++) {
        cout << i << " : ";
        for (int j = 0; j < result.at(i).size(); j++) {
            cout << result[i][j];
        }
        cout << endl;
    }
}

int main(void)
{
    char data[] = "abc";

    permutate(data, 3);
    return 0;
}
