#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
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

const int MAX = 1e5 + 1e2;
int id[MAX],W[MAX];

int get(int a){
	return id[a] = (a == id[a]) ? a : get(id[a]);
}

void join(int a,int b){
	a = get(a),b = get(b);
	if(a == b) return;
	if(W[a] < W[b]) swap(a,b);
	W[a] += W[b];
	id[b] = a;
}

int main(){
	int n,m; scanf("%d %d",&n,&m);
	loop(i,n) W[i] = 1,id[i] = i;
	loop(i,m){
		int a,b; scanf("%d %d",&a,&b);
		join(a,b);
	}	
	ll cnt = 0,ans = 0;
	loop(i,n) if(i == get(i)){
		ans += cnt*W[i];
		cnt += W[i];
	}
	cout << ans << endl;
	cerr << ans << endl;
	return 0;
}
