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


const int MAXA = 3 << 20;
int freq[MAXA], pref[MAXA];
vi small, B;
vector<ll> ways(MAXA, 0);


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
    int n; scanf("%d", &n);
    loop(i, n){
        int a; scanf("%d", &a);
        freq[a]++;
    }
    int m; scanf("%d", &m);
    B.resize(m);
	for(int & b : B) scanf("%d", &b);
	for(int i = 1; i*(ll)i < MAXA; i++) if(freq[i]) {
        ways[i*i] += freq[i]*(freq[i] - 1LL);
        for(int j = i+1, lim = (MAXA-1)/i; j <= lim; j++){
			ways[i*j] += 2*freq[i]*(ll)freq[j];
		}
    }

	for(int i = 1; i < MAXA; i++)
		ways[i] += ways[i-1];		
    ll tot = n*(n-1LL);
	for(int x : B){
		ll ans = tot;
		ans -= ways[x - 1];
        printf("%lld\n", ans);
    }
    return 0;
}
