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

const int MAX = 1 << 10;
int U[MAX],D[MAX];
int L[MAX],R[MAX];
int n,m1,m2;
int ord1[MAX],ord2[MAX];

void work(int *good,int *bad,int m,int *ord) {
	vi totret,firstret, totforw,firstretbut;
	loop(i,m) ord[i] = i;
	loop(i,m) {
		if(good[i] < 0) {
			if(good[i] - bad[i] >= 0) firstretbut.pb(i);
			else firstret.pb(i);
		}
		else if(good[i] - bad[i] < 0) totret.pb(i);
		else totforw.pb(i);
	}
	m = 0;
	for(int x : totforw) ord[m++] = x;
	sort(all(firstretbut),[good,bad](const int & a,const int &b) {
		return good[a] - bad[a] > good[b] - bad[b];
	});
	for(int x : firstretbut) ord[m++] = x;
	for(int x : firstret) ord[m++] = x;
	for(int x : totret) ord[m++] = x;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(i,n) {
		int t; scanf("%d",&t);
		if(t == 1) {
			scanf("%d %d",R + m1,L + m1);
			m1++;
		}
		else {
			scanf("%d %d",U + m2,D + m2);
			m2++;
		}
	}
	work(R,L,m1,ord1);
	work(U,D,m2,ord2);
	ll x = 1,y = 1;
	loop(i,m1) {
		int j = ord1[i];
		x += R[j];
		if(x <= 0) {
			puts("NO");
			return 0;
		}
		x -= L[j];
		if(x <= 0) {
			puts("NO");
			return 0;
		}
	}
	loop(i,m2) {
		int j = ord2[i];
		y += U[j];
		if(y <= 0) {
			puts("NO");
			return 0;
		}
		y -= D[j];
		if(y <= 0) {
			puts("NO");
			return 0;
		}
	}
	puts("YES");
	printf("(%lld, %lld)\n",x,y);
	return 0;
}
