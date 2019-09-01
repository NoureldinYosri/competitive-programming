#ifdef DEBUG
#include <bits/stdc++.h>

using namespace std;

#define loop(i, n) for(int i = 0;i < int(n);i++)
#define rloop(i, n) for(int i = int(n);i >= 0;i--)
#define range(i, a, b) for(int i = int(a);i <= int(b);i++)
#define SZ(c) int(c.size())
#define ALL(c) c.begin(), c.end()
#define RALL(c) c.rbegin(), c.rend()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define fr first
#define sc second
#define sfi1(v) scanf("%d",&v)
#define sfi2(v1, v2) scanf("%d %d",&v1,&v2)
#define sfi3(v1, v2, v3) scanf("%d %d %d",&v1,&v2,&v3)
#define sfll1(v) scanf("%I64d",&v);
#define sfll2(v1, v2) scanf("%I64d %I64d",&v1,&v2)
#define sfll3(v1, v2, v3) scanf("%I64d %I64d %I64d",&v1,&v2,&v3)
#define endl '\n'
#define cross(a, b) ((conj(a)*(b)).imag())

typedef complex<long double> point;
typedef vector<int> vi;
typedef vector<pair<int, int> > vii;
typedef long long ll;
typedef pair<int, int> pii;

const double EPS = 1e-9;
const int N = 1e5 + 5;
int x[N], y[N];
int nxt[N], prv[N];
int n;

long double polygonArea(const vector<point> &p) {
    long double res = 0;
    for (int i = 0; i < SZ(p); i++) {
        int j = (i + 1) % SZ(p);
        res += cross(p[i], p[j]);
    }
    return fabs(res) / 2;
}

bool intersect(const point &a, const point &b, const point &p, const point &q,
               point &ret) {

    //handle degenerate cases (2 parallel lines, 2 identical lines,   line is 1 point)

    long double d1 = cross(p - a, b - a);
    long double d2 = cross(q - a, b - a);
    ret = (d1 * q - d2 * p) / (d1 - d2);
    if (fabs(d1 - d2) > EPS) return 1;
    return 0;
}

int main() {

#ifndef ONLINE_JUDGE
    //freopen("in.in", "r", stdin);
    //freopen("out.in", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    double ans = 0;
    cin >> n;
    loop(i, n)cin >> x[i] >> y[i];
    rloop(i, n - 1) {
        nxt[i] = i + 1;
        while (nxt[i] < n && y[nxt[i]] < y[i])nxt[i] = nxt[nxt[i]];
    }

    loop(i, n) {
        prv[i] = i - 1;
        while (prv[i] >= 0 && y[prv[i]] < y[i])prv[i] = prv[prv[i]];
    }

    loop(i, n) {
        if (nxt[i] == i + 1)continue;
        if (nxt[i] == n) {
            rloop(k, n - 1) {
                if (prv[k] == k - 1)continue;
                if (prv[k] < i)break;
                vector<point> polygon;
                range(j, prv[k] + 1, k)polygon.pb(point(x[j], y[j]));
                point a = point(-1e7, y[k]), b = point(1e7, y[k]);
                point p = point(x[prv[k]], y[prv[k]]), q = point(x[prv[k] + 1], y[prv[k] + 1]);
                point ret(0, 0);
                intersect(a, b, p, q, ret);
                polygon.pb(ret);
                ans += polygonArea(polygon);
                k = prv[k] + 1;
            }
        } else {
            vector<point> polygon;
            range(j, i, nxt[i] - 1)polygon.pb(point(x[j], y[j]));
            point a = point(-1e7, y[i]), b = point(1e7, y[i]);
            point p = point(x[nxt[i]], y[nxt[i]]), q = point(x[nxt[i] - 1], y[nxt[i] - 1]);
            point ret(0, 0);
            intersect(a, b, p, q, ret);
            polygon.pb(ret);
            ans += polygonArea(polygon);
        }
        i = nxt[i] - 1;
    }

    cout << fixed << setprecision(12) << ans << endl;


    return 0;
}


#endif
