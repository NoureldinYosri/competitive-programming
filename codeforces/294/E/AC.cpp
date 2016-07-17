#include<iostream>
#include<fstream>
#include<cstdio>
#include<vector>
#include<string>
#include<cstring>
#include<queue>
#include<map>
#include<set>
#include<algorithm>
#include<iomanip>
#include<bitset>
using namespace std;

const int N = 100100;

int n, m, niv[N], p[19][N], nrnod[N];
vector<int> v[N];

void df(int nod, int pp) {

    nrnod[nod] = 1;

    for(vector<int>::iterator it = v[nod].begin(); it != v[nod].end(); ++it) if(*it != pp) {
        niv[*it] = niv[nod] + 1;
        p[0][*it] = nod;
        df(*it, nod);

        nrnod[nod] += nrnod[*it];
    }
}

int lca(int a, int b) {
    if(niv[a] > niv[b])
        swap(a, b);

    int k;
    for(k = 18; k >= 0; --k)
        if(niv[b] - (1<<k) >= niv[a])
            b = p[k][b];

    for(k = 18; k >= 0; --k)
    if(p[k][a] != p[k][b]) {
        a = p[k][a];
        b = p[k][b];
    }

    if(a == b)
        return a;
    return p[0][a];
}

int par(int nr, int nod) {
    int k;

    for(k = 18; k >= 0; --k)
    if((1<<k) <= nr) {
        nr -= (1<<k);
        nod = p[k][nod];
    }

    return nod;
}

int main() {
    int i, j;
    //freopen("ttt", "r", stdin);

    cin >> n;
    for(i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }

    df(1, 0);
    for(i = 1; i < 19; ++i)
        for(j = 1; j <= n; ++j)
            p[i][j] = p[i - 1][p[i - 1][j]];

    cin >> m;

    for(i = 1; i <= m; ++i) {
        int lc, a, b;
        cin >> a >> b;

        if(a == b) {
            cout << n << "\n";
            continue;
        }

        lc = lca(a, b);

        int sum = niv[a] + niv[b] - 2 * niv[lc];

        if(sum % 2 == 1) {
            cout << "0\n";
            continue;
        }
        else {
            sum /= 2;
            if(niv[a] > niv[b])
                swap(a, b);


            int nod = par(sum, b);

            int nrel = nrnod[nod];

            if(nod == lc) {
                nrel = n;
                nrel -= nrnod[par(sum - 1, a)];
            }
            nrel -= nrnod[par(sum - 1, b)];

            cout << nrel << "\n";
        }
    }

    return 0;
}
