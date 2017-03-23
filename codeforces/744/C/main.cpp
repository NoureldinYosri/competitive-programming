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


int n;
vector<vi> Q[20];
int ans[1001];

int write(vi Q){
	printf("%d\n",sz(Q));
	loop(i,sz(Q)) printf("%d%c",Q[i]," \n"[i+1==sz(Q)]);
	fflush(stdout);
}

vi read(){
	vi ret;
	loop(i,n) {
		int x; scanf("%d",&x);
		ret.pb(x);
	}
	return ret;
}

void create(int l,int r,int d){
	if(l == r) return;
	int m = (l + r) >> 1;
	vi q1,q2;
	for(int i = l;i <= m;i++) q1.pb(i);
	for(int i = m+1;i <= r;i++) q2.pb(i);
	if(Q[d].empty()) Q[d].pb(q1),Q[d].pb(q2);
	else{
		Q[d][0].insert(Q[d][0].end(),q1.begin(),q1.end());
		Q[d][1].insert(Q[d][1].end(),q2.begin(),q2.end());
	}
	create(l,m,d+1);
	create(m+1,r,d+1);
}

int main(){
	scanf("%d",&n);
	create(1,n,0);
	fill(ans+1,ans+n+1,INT_MAX);
	for(int d = 0;!Q[d].empty();d++){
		for(vi q : Q[d]){
			write(q);
			vi r = read();
			for(int i = 1;i <= n;i++)
				if(!binary_search(all(q),i))
					ans[i] = min(ans[i],r[i-1]);
		}
	}
	cout << -1 << endl;
	range(i,1,n) printf("%d%c",ans[i]," \n"[i==n]);
	fflush(stdout);
	return 0;
}
