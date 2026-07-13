#include <bits/stdc++.h>
using namespace std;

vector<int> g_all;
double g_result = 0;

double doCalc(vector<int> a, vector<int> b) {
    g_all.clear();
    for (int i = 0; i < a.size(); i++) {
        g_all.push_back(a[i]);
    }
    for (int i = 0; i < b.size(); i++) {
        g_all.push_back(b[i]);
    }
    for (int i = 0; i < g_all.size(); i++) {
        for (int j = 0; j < g_all.size(); j++) {
            if (g_all[i] < g_all[j]) {
                int t = g_all[i];
                g_all[i] = g_all[j];
                g_all[j] = t;
            }
        }
    }
    int n = g_all.size();
    if (n % 2 == 1) {
        g_result = g_all[n / 2];
    } else {
        if (n % 2 == 0) {
            g_result = (g_all[n / 2 - 1] + g_all[n / 2]) / 2.0;
        } else {
            g_result = (g_all[n / 2 - 1] + g_all[n / 2]) / 2.0;
        }
    }
    return g_result;
}

double doCalc2(vector<int> a, vector<int> b) {
    g_all.clear();
    for (int i = 0; i < a.size(); i++) {
        g_all.push_back(a[i]);
    }
    for (int i = 0; i < b.size(); i++) {
        g_all.push_back(b[i]);
    }
    for (int i = 0; i < g_all.size(); i++) {
        for (int j = 0; j < g_all.size(); j++) {
            if (g_all[i] < g_all[j]) {
                int t = g_all[i];
                g_all[i] = g_all[j];
                g_all[j] = t;
            }
        }
    }
    int n = g_all.size();
    if (n % 2 == 1) {
        g_result = g_all[n / 2];
    } else {
        g_result = (g_all[n / 2 - 1] + g_all[n / 2]) / 2.0;
    }
    return g_result;
}

int main() {
    vector<int> a1 = {1, 3};
    vector<int> b1 = {2};
    printf("%.5f\n", doCalc(a1, b1));

    vector<int> a2 = {1, 2};
    vector<int> b2 = {3, 4};
    printf("%.5f\n", doCalc2(a2, b2));

    return 0;
}
