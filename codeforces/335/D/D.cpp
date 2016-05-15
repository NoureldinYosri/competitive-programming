#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define prp(p) cout << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cout << #A << ": "; copy(A,A + n,ostream_iterator<t>(cout," " )); cout << endl
using namespace std;


int P[1 << 20],W[1 << 20],n,m;
pair<pi,int> E[1 << 20];
int F[1 << 20],T[1 << 20];

int get(int a){
	int b = a;
	while(a != P[a]) a = P[a];
	while(b != P[b]){
		int t = P[b];
		P[b] = a;
		b = t;
	}
	return a;
}

void join(int a,int b){
	a = get(a),b = get(b);
	if(a == b) return ;
	if(W[a] < W[b]) swap(a,b);
	W[a] += W[b];
	P[b] = a;
}

int main(){
  	scanf("%d %d",&n,&m);
	loop(i,n + 1) P[i] = i,W[i] = 1;
	loop(i,m) scanf("%d %d",&E[i].xx.xx,&E[i].xx.yy),E[i].xx.yy ^= 1,E[i].yy = i;
	sort(E,E + m);
	int s = 2,e = 3;
	set<int> S;
	loop(i,n) S.insert(i + 1);
	loop(i,m){
		if(E[i].xx.yy){
			int idx = E[i].yy;
			if(get(s) != get(e)){
				puts("-1");
				return 0;
			}
			F[idx] = s++;
			T[idx] = e;
			if(s == e) s = 2,e++;
		}
		else{
			if(sz(S) < 2) {
				puts("-1");
				return 0;
			}
			int u = *S.begin(); S.erase(S.begin());
			int v = *S.begin(); S.erase(S.begin());
			int idx = E[i].yy;
			F[idx] = u;
			T[idx] = v;
			join(u,v);
			S.insert(get(u));
		}
	}
	if(sz(S) == 1){
		loop(i,m) printf("%d %d\n",F[i],T[i]);
	}
	else puts("-1");
	return 0;
}
