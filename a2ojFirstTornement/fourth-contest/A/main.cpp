#pragma GCC optimize ("O3")
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
#define popcnt(x) __builtin_popcountll(x)
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

char str[1 << 20];
int n;
vector<pi> P;

bool cond(int a,int b,int c,int d) {
	return (str[a] == str[b]) && (str[c] == str[d]);
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%s",str);
	n = strlen(str);
	if(n <= 1) {
		puts("NO");
		return 0;
	}
	int i = 0,j = n-1;
	for(;i < j;i++,j--) {
		if(str[i] != str[j])
			P.pb(mp(i,j));
	}
	if(P.empty()) {
		puts("YES");
		return 0;
	}
	if(sz(P) > 2) {
		puts("NO");
		return 0;
	}
	if(sz(P) == 2) {
		int a = P[0].xx,b = P[0].yy,c = P[1].xx,d = P[1].yy;
		if(cond(c,b,a,d) || cond(d,b,c,a) || cond(a,c,b,d) || cond(a,d,c,b)) {
			puts("YES");
			return 0;
		}
		puts("NO");
		return 0;
	}
	if(n%2 == 0) {
		puts("NO");
		return 0;
	}
	int a = P[0].xx,b = P[0].yy;
	int c1 = str[a],c2 = str[b];
	if(c1 == str[n/2] || c2 == str[n/2]) {
		puts("YES");
	}
	else puts("NO");

	return 0;
}
