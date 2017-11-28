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

const int mod = 1e9 + 7;
const int MAX = 1 << 20;

pi P[MAX];
vi Xs,Ys;
int n;
int num[MAX],cnt[MAX];
int BIT[MAX];



int add(int a,int b) {
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a,int b){
	return (a*1LL*b)%mod;
}
void update(int p,int v){
	for(;p <= n;p += LSOne(p))
		BIT[p] = add(BIT[p],v);
}
int get(int p) {
	int ret = 0;
	for(;p;p ^= LSOne(p))
		ret = add(ret,BIT[p]);
	return ret;
}
int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	Xs.reserve(n);
	Ys.reserve(n);
	loop(i,n) {
		scanf("%d %d",&P[i].xx,&P[i].yy);
		Xs.pb(P[i].xx);
		Ys.pb(P[i].yy);
	}
	sort(all(Xs));
	Xs.resize(unique(all(Xs)) - Xs.begin());
	sort(all(Ys));
	Ys.resize(unique(all(Ys)) - Ys.begin());
	loop(i,n){
		P[i].xx = upper_bound(all(Xs),P[i].xx) - Xs.begin();
		P[i].yy = upper_bound(all(Ys),P[i].yy) - Ys.begin();
	}

	int f = 1;

	for(int i = 0;i < n;) {
		int j = i;
		while(j < n && P[i].xx == P[j].xx) j++;
		int old_f = f;
		for(int k = i,y;k < j;k++){
			y = P[k].yy;
			num[y] = get(y);
		}
		for(int k = i,y,tmp;k < j;k++){
			y = P[k].yy;
			tmp = add(f,-get(y));
			f = add(f,tmp);
			update(1,tmp);
		}


		cerr << f << endl;
		for(int k = i,y;k < j;k++){
			y = P[k].yy;
			int dueToY = add(get(y),-num[y]);
			cerr << "due " << dueToY << endl;
			int thus = add(f,-dueToY);
			f = add(f,thus);

		}
		for(int y = 1;y <= sz(Ys);y++)
			cerr << get(y) << " ";
		cerr << endl;
		cerr << f << endl;
		i = j;
	}
	cout << f << endl;
	return 0;
}
