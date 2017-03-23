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

int A[8][3];

bool valid_dim(int k){
	int B[8];
	loop(i,8) B[i] = A[i][k];
	return unique(B,B + 8) - B != 1;
}

ll get_dist(int i,int j){
	ll ret = 0;
	loop(k,3) ret += (A[i][k] - A[j][k])*1LL*(A[i][k] - A[j][k]);
	return ret;
}

bool valid(){
	if(!valid_dim(0) || !valid_dim(1) || !valid_dim(2)) return 0;
	deque<ll> dist;
	loop(i,8) loop(j,i) dist.pb(get_dist(i,j));
	sort(all(dist));
	deque<ll> tmp = dist;
	tmp.resize(unique(all(tmp)) - tmp.begin());
	if(sz(tmp) != 3) return 0;
	if(tmp[1] != tmp[0] * 2) return 0;
	if(tmp[2] != tmp[0] + tmp[1]) return 0;
	loop(i,12) if(dist[i] != dist[0]) return 0;
	loop(i,12) dist.pop_front();
	loop(i,12) if(dist[i] != dist[0]) return 0;
	loop(i,12) dist.pop_front();
	loop(i,4) if(dist[i] != dist[0]) return 0;
	return 1;	
}

bool valid(int L){
	deque<ll> dist;
	loop(i,L) loop(j,i) dist.pb(get_dist(i,j));
	sort(all(dist));
	deque<ll> tmp = dist;
	tmp.resize(unique(all(tmp)) - tmp.begin());
	if(sz(tmp) > 3) return 0;
	if(sz(tmp) > 1 && tmp[1] != tmp[0] * 2) return 0;
	if(sz(tmp) > 2 && tmp[2] != tmp[0] + tmp[1]) return 0;
	int ctr = 0; ll x = dist[0];
	while(!dist.empty() && dist.front() == x) dist.pop_front(),ctr++;
	if(ctr > 12) return 0;
	ctr = 0,x = dist.empty() ? 0 : dist.front();
	while(!dist.empty() && dist.front() == x) dist.pop_front(),ctr++;
	if(ctr > 12) return 0;
	ctr = 0,x = dist.empty() ? 0 : dist.front();
	while(!dist.empty() && dist.front() == x) dist.pop_front(),ctr++;
	if(ctr > 4) return 0;
 	return 1;
}

bool bt(int i){
	if(i == 8) return valid();
	sort(A[i],A[i] + 3);
	do{
		if(!valid(i+1)) continue;
		if(bt(i + 1)) return 1;
	}while(next_permutation(A[i],A[i] + 3));
	return 0;
}

int main(){
	loop(i,8) loop(j,3) scanf("%d",&A[i][j]);
	if(bt(0)) {
		puts("YES");
		loop(i,8) loop(j,3) printf("%d%c",A[i][j]," \n"[j==2]);
	}	
	else puts("NO");
	
	return 0;
}
