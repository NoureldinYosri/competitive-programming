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


const int oo = 1 << 29;
int A[75],n;
int dp[75][75][3][3][3][3];
vi aux;
bool done(int l,int r,int iL,int iR,int oL,int oR){
	if(iL != oL || iR != oR) return 0;
	aux.clear();
	for(int i = l;i <= r;i++) aux.pb(A[i]);
	aux[0] = iL;
	aux.back() = iR;
	int L = sz(aux);
	loop(i,L - 1) if(aux[i] == 0 && aux[i + 1] == 1) return 0;
	return 1;	
}


int solve2(int iL,int iR,int oL,int oR){
	int ret = 0;
	if(iL == 0 && iR == 1) return oo;
	return ret;
}

int solve1(int iL,int iR,int oL,int oR){
	if(iL != iR) return oo;
	return 0;
}

int solve(int l,int r,int iL,int iR){
	int & ret = dp[l][r][iL][iR][oL][oR];
	if(ret != -1) return ret;	
	if(r == l + 1) return ret = solve2(iL,iR);
	if(l == r) return ret = solve1(iL,iR);
	if(done(l,r,iL,iR,oL,oR)) return 0;
	ret = oo;
	vi V(A + l,A + r + 1),T;
	V[0] = iL;
	V.back() = iR;
	
	for(int s = 0;s < sz(V);s++){
		T = V;
		int tmp = 0,to = 0;
		for(int e = s;e < sz(V);e++){
			int cur = e;
			while(cur != to) {
				swap(V[cur - 1],V[cur]);
				--cur;
				tmp++;
			}
			if(
		}
	}
	return ret;
}
int main(){
	string s; cin >> n >> s;
	loop(i,n) {
		if(s[i] == 'V') A[i] = 0;
		else if(s[i] == 'K') A[i] = 1;
		else A[i] = 2;
	}
	memset(dp,-1,sizeof dp);
	int ans = oo;
	loop(i,3) loop(j,3) 	ans = min(ans,solve(0,n-1,A[0],A[n - 1],i,j));
	cerr << ans << endl;
	cout << ans << endl;
	return 0;
}
