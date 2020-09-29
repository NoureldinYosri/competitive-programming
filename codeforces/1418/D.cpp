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

int n, m;
vi A;
multiset<int> MS;
set<int> S;


void erase(int x){
    auto ptr = S.find(x);
    auto nxt = ptr, prv = ptr;
    nxt++;
    if(nxt != S.end()){
        MS.erase(MS.find(*nxt - x));
    }
    if(prv != S.begin()){
        prv--;
        MS.erase(MS.find(x - *prv));
        if(nxt != S.end()) MS.insert(*nxt - *prv);
    }
    S.erase(ptr);
}

void insert(int x){
    auto nxt = S.upper_bound(x);
    if(nxt != S.begin() && nxt != S.end()) {
        auto prv = nxt; prv--;
        MS.erase(MS.find(*nxt - *prv));
    }
    S.insert(x);
    auto ptr = S.find(x);
    nxt = ptr; nxt++;
    auto prv = ptr;
    if(nxt != S.end()) MS.insert(*nxt - x);
    if(prv != S.begin()){
        prv--;
        MS.insert(x - *prv);
    }
}

int solve(){
    if(sz(S) <= 1) return 0;
    return *S.rbegin() - *S.begin() - *MS.rbegin();
}

int main(int argc, char **argv) {
    scanf("%d %d", &n, &m);
    vi A(n);
    for(int & a : A) scanf("%d", &a);
    sort(all(A));
    S = set<int>{all(A)};
    for(int i = 1; i < n; i++) MS.insert(A[i] - A[i-1]);
    printf("%d\n", solve());
    while(m--){
        int t, x; scanf("%d %d", &t, &x);
        if(t == 0) erase(x);
        else insert(x);
        printf("%d\n", solve());
    }
    return 0;
}
