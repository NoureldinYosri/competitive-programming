#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

int id[2001],W[2001],n;

int get(int a){
	return id[a] = (id[a] == a) ? a : get(id[a]);
}

int join(int a,int b){
	a = get(a),b = get(b);
	if(a == b) return 0;
	if(W[a] < W[b]) swap(a,b);
	W[a] += W[b];
	id[b] = a;
	return 1;
}

int main(){
	loop(i,2001) id[i] = i,W[i] = 1;
	scanf("%d",&n);
	set<int> X,Y;
	int ans = -1;
	loop(i,n){
		int a,b;
		scanf("%d %d",&a,&b);
		ans -= join(a,b + 1000);
		X.insert(a);
		Y.insert(b);
	}
	ans += sz(X) + sz(Y);
	printf("%d\n",ans);
	return 0;
}
