#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
    st << "(" << p.first << ", " << p.second << ")";
    return st;
}
using namespace std;
const double eps = 1e-9;
const int MAXN = 500000;
int prime[MAXN+1], mu[MAXN+1];
vi divs[MAXN+1];

void sieve(){
    mu[1] = 1;
    for(int i = 2; i <= MAXN; i++){
        if(prime[i] == 0){
            prime[i] = i;
            for(ll j = i*(ll)i; j <= MAXN; j += i)
                prime[j] = i;
        }
        int p = prime[i];
        ll q = p*(ll)p;
        if(i%q == 0){
            mu[i] = 0;
        } else {
            mu[i] = -mu[i/p];
        }
    }
    for(int d = 1; d <= MAXN; d++) if(mu[d]){
        for(int n = d; n <= MAXN; n += d)
            divs[n].pb(d);
    }
}

int n;
ll k;


pi Farey(int a, int b, int c, int d, double x, const function<bool(const pi &, const pi & )> & cmp){
    int p = a + c, q = b + d;
    if(q > n) return min(pi(a, b), pi(c, d), cmp);
    double v = p/(double)q;
    if(x <= v) return min(pi(p, q), Farey(a, b, p, q, x, cmp), cmp);
    else return min(pi(p, q), Farey(p, q, c, d, x, cmp), cmp);
}

pi getFrac(double x){
    auto cmp = [x](const pi & A, const pi & B){
        double a = A.first/(double)A.second;
        double b = B.first/(double)B.second;
        return abs(a-x) < abs(b-x);
    };
    return Farey(0, 1, 1, 1, x, cmp);
}

ll getCount(const double & x){
    ll ret = 0;
    for(int m = 1; m <= n; m++){
        int N = floor(m*x);
        int tmp = 0;
        for(int d : divs[m])
            tmp += mu[d]*(N/d);
        ret += tmp;
    }
    return ret;
}

int main(){
#ifdef HOME
    freopen("in.in", "r", stdin);
#endif
    sieve();
    cin >> n >> k;
    
    double s = 0, e = 1;
    for(int t = 0; t < 90; t++){
        double m = s + (e-s)/2.0;
//      cerr << s << " " << e << endl;
        if(getCount(m) >= k) e = m;
        else s = m;
    }
    auto [a, b] = getFrac(e);
    printf("%d %d\n", a, b);
    
    return 0;
}
