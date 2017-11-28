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

int f[1000],n;
char line[1 << 23];
int m;
int pf[1 << 23];

bool contains(int cur,int msk) {
	return (cur & msk);
}

int GetLen(int msk,int l){
	while(l && !contains(f[l],msk)) l = pf[l - 1];
	if(contains(f[l],msk)) l++;
	return l;
}

void BuildFailure(){
	pf[0] = 0;
	range(i,1,n - 1) pf[i] = GetLen(f[i],pf[i - 1]);
}


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	while(scanf("%d",&n) == 1) {
		loop(i,n) {
			f[i] = 0;
			int cnt; scanf("%d",&cnt);
			loop(j,cnt) {
				int d; scanf("%d",&d);
				f[i] |= 1 << d;
			}
		}
		BuildFailure();
		scanf("%s",line);
		m = strlen(line);
		int l = 0;
		for(int i = 0;i < m;i++) {
			l = GetLen(1 << (line[i] - '0'),l);
			if(l == n) {
				for(int j = 0;j < n;j++) putchar(line[i - n + j + 1]);
				puts("");
				l = pf[n - 1];
			}
		}
	}
	return 0;
}
