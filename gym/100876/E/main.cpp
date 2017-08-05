#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;


const ll threshold = 11;
ll A[1 << 15];
int n;
vi bits;
vi suff;

bool solve(){
	bits.clear();
	ll l = 2*9*A[0],r = 2*11*A[0];
	bits.pb(1);
	for(int i = 1;i < n;i++){
		if(2*A[i] > 5*A[0]) return 0;
//		cerr << 2*A[i] << " " << 3*A[0] << endl;
		if(2*A[i] > 3*A[0]) {
			bits.pb(bits.back()^1);
			l = max(l,9*A[i]);
			r = min(r,11*A[i]);
		}
		else{
//			cerr << i << " " << l << " " << 20*A[i] << " " << r << endl;
			if(i != n-1) {
				bits.pb(bits.back());
				l = max(l,18*A[i+1]);
				r = min(r,22*A[i+1]);
			}
			l = max(l,18*A[i]);
			r = min(r,22*A[i]);
			i++;
		}
	}
	if(l > r) return 0;
	if(bits.empty() || bits.back() != 0) return 0;
	return 1;
}

int main(){
	freopen("hspace.in", "r", stdin);
	freopen("hspace.out", "w", stdout);
	bits.reserve(1 << 20);
	int K; scanf("%d",&K);
	while(K--){
		scanf("%d",&n);
		loop(i,n) scanf("%lld",A + i);
		if(solve()) {
			for(int b : bits) putchar(b + '0');
			puts("");
//			print(bits,int);
		}
		else {
			puts("ERROR");
//			cerr << "ERROR" << endl;
		}
	}
	return 0;
}
