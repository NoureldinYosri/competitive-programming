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

const int MAX = 300*1000 + 10;
int n,p;
int X[MAX],Y[MAX];
int ctr[MAX];
int BIT[MAX];
int taraf2wl[MAX];
map<int,int> taraftany[MAX];

void add(int p) {
	for(;p < MAX;p += LSOne(p))
		BIT[p]++;
}

int get(int p){
	int ret = 0;
	for(;p;p ^= LSOne(p))
		ret += BIT[p];
	return ret;
}



int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&p);
	range(i,1,n) {
		scanf("%d %d",X + i,Y + i);
		if(X[i] > Y[i]) swap(X[i],Y[i]);
		ctr[X[i]]++;
		ctr[Y[i]]++;
		taraf2wl[X[i]]++;
		taraftany[Y[i]][X[i]]++;
	}

	ll ans = 0;
	range(i,1,n){
		int cnt = ctr[i];
		ll tmp = get(MAX - 1) - get(max(p - cnt,0));
		for(auto it : taraftany[i]){
			if(ctr[i] + ctr[it.xx] >= p) tmp--;
			if(ctr[i] + ctr[it.xx] - it.yy >= p)
				tmp++;
		}
		add(ctr[i] + 1);
//		cerr << i << " " << tmp << endl;
		ans += tmp;
	}

	cout << ans << endl;


	return 0;
}
