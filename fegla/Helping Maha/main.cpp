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
#define pl pair<ll,ll>
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

int cnt[10] = {6,2,5,5,4,5,6,3,7,6};
vi G[50];

int eval(int t){
	int h = t / 3600; t %= 3600;
	int m = t / 60; t %= 60;
	int s = t;
	h = cnt[h/10] + cnt[h%10];
	m = cnt[m/10] + cnt[m%10];
	s = cnt[s/10] + cnt[s%10];
	return h + m + s;
}

void init(){
	loop(i,24*60*60*2) {
		int t = i%(24*60*60);
		G[eval(t)].pb(i);
	}
}

void output_time(int t){
	int h = t / 3600; t %= 3600;
	int m = t / 60; t %= 60;
	int s = t;
	if(h < 10) putchar('0');
	printf("%d:",h);
	if(m < 10) putchar('0');
	printf("%d:",m);
	if(s < 10) putchar('0');
	printf("%d\n",s);
}

int read_time(){
	int h,m,s; scanf(" %d:%d:%d",&h,&m,&s);
	return h*3600 + m*60 + s;
}

int main(){
	freopen("helping.in", "r", stdin);
	init();
	int T; scanf("%d",&T);
	while(T--) {
		int N; scanf("%d",&N);
		int t = read_time();
		int o = 0,best = 1 << 28;
		range(n,1,N) {
			auto p = lower_bound(all(G[n]),t);
			if(p != G[n].end() && abs(*p - t) < best){
				best = abs(*p - t);
				o = *p;
			}
		}
		o %= 24*3600;
		output_time(o);
	}
	return 0;
}
