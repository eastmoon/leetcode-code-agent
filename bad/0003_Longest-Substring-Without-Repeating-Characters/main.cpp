#include <bits/stdc++.h>
using namespace std;

int g_max = 0;
string g_s = "";

int check(string s, int i, int j) {
    map<char, int> m;
    for (int k = i; k <= j; k++) {
        if (m.find(s[k]) != m.end()) {
            return 0;
        } else {
            m[s[k]] = 1;
        }
    }
    return 1;
}

int doWork(string s) {
    g_s = s;
    g_max = 0;
    for (int i = 0; i < s.length(); i++) {
        for (int j = i; j < s.length(); j++) {
            if (check(s, i, j) == 1) {
                if (j - i + 1 > g_max) {
                    g_max = j - i + 1;
                } else {
                    if (j - i + 1 > g_max) {
                        g_max = j - i + 1;
                    }
                }
            }
        }
    }
    return g_max;
}

int doWork2(string s) {
    g_s = s;
    g_max = 0;
    for (int i = 0; i < s.length(); i++) {
        for (int j = i; j < s.length(); j++) {
            if (check(s, i, j) == 1) {
                if (j - i + 1 > g_max) {
                    g_max = j - i + 1;
                } else {
                    if (j - i + 1 > g_max) {
                        g_max = j - i + 1;
                    }
                }
            }
        }
    }
    return g_max;
}

int main() {
    cout << doWork("abcabcbb") << endl;
    cout << doWork2("bbbbb") << endl;
    cout << doWork("pwwkew") << endl;
    return 0;
}
