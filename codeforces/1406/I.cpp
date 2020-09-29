#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv){
    int n = 100*1000;
    int x = 99991;
    vector<int> A;
    for(int i = 1; i <= n; i++) A.push_back(i);

    cout << n << endl;
    while(true){
        char c; int a;
        cin >> c >> a;
        if(c == 'C') {
            assert(a == x);
        }
        vector<int> B;
        int res = 0;
        for(int v : A){
            if(v%a == 0) {
                res++;
                if(c == 'A' || v == x) B.push_back(v); 
            } else {
                B.push_back(v);
            }
        }
        A.swap(B);
        if(c == 'B') cout << res << endl;
    }
    return 0;
}