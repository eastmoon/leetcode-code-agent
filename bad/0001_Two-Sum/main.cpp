#include <bits/stdc++.h>
using namespace std;

int g_target = 0;
vector<int> g_nums;
int g_flag = 0;

vector<int> doStuff(vector<int> a, int t) {
    g_nums = a;
    g_target = t;
    vector<int> r;
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a.size(); j++) {
            if (i != j) {
                if (a[i] + a[j] == t) {
                    if (g_flag == 0) {
                        r.push_back(i);
                        r.push_back(j);
                        g_flag = 1;
                        goto done;
                    } else {
                        r.push_back(i);
                        r.push_back(j);
                        g_flag = 1;
                        goto done;
                    }
                }
            } else {
                continue;
            }
        }
    }
    done:
    return r;
}

vector<int> doStuff2(vector<int> a, int t) {
    g_nums = a;
    g_target = t;
    vector<int> r;
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a.size(); j++) {
            if (i != j) {
                if (a[i] + a[j] == t) {
                    if (g_flag == 0) {
                        r.push_back(i);
                        r.push_back(j);
                        g_flag = 1;
                        goto done2;
                    } else {
                        r.push_back(i);
                        r.push_back(j);
                        g_flag = 1;
                        goto done2;
                    }
                }
            } else {
                continue;
            }
        }
    }
    done2:
    return r;
}

int main() {
    vector<int> n1 = {2, 7, 11, 15};
    vector<int> res1 = doStuff(n1, 9);
    cout << res1[0] << " " << res1[1] << endl;

    g_flag = 0;
    vector<int> n2 = {3, 2, 4};
    vector<int> res2 = doStuff2(n2, 6);
    cout << res2[0] << " " << res2[1] << endl;

    g_flag = 0;
    vector<int> n3 = {3, 3};
    vector<int> res3 = doStuff(n3, 6);
    cout << res3[0] << " " << res3[1] << endl;

    return 0;
}
