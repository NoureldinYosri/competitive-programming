/*
ID: noueld1
LANG: C++
TASK: fence8
*/
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
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
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

int sub[50],req[1 << 20],sum_sub = 0,sum_req = 0,N,R;
int freq[1 << 8],cumm[1 << 8];
int ans = 0;

int backtrack(int idx,int rem,int mx,int waste,int n){
	if(waste < 0) return 0;
	if(n == 0) return 1;
 	if(idx == -1) return 0;	
	if(mx == 0) return backtrack(idx - 1,sub[idx],128,waste - rem,n);
	if(!freq[mx]) return backtrack(idx,rem,mx - 1,waste,n);
	int tmp = 0;
	if(rem >= mx) {
		freq[mx]--;	
		tmp = backtrack(idx,rem - mx,mx,waste,n - 1);	
		freq[mx]++;
		if(tmp) return 1;
	}
	return backtrack(idx,rem,mx - 1,waste,n);
}

bool f(int m){
	sum_req = 0;
	fill(freq,freq + 129,0);
	loop(i,m) {
		sum_req += req[i];
		freq[req[i]]++;
	}
	return	backtrack(N - 1,sub[N - 1],128,sum_sub - sum_req,m);
}

int solve(){
	int s = 0,e = R;
	while(s < e){
		int m = (s + e) >> 1;
		if(f(m)) s = m + 1;
		else e = m;
	}
	return s - !f(s);
}

int main(){
	freopen("fence8.in","r",stdin);
	freopen("fence8.out","w",stdout);
	scanf("%d",&N);	
	loop(i,N) scanf("%d",sub + i),sum_sub += sub[i];
	scanf("%d",&R);	
	loop(i,R) {
		scanf("%d",req + i);
		freq[req[i]]++;
		sum_req += req[i];	
	}
	for(int i = (1 << 8) - 1;i >= 0;i--) cumm[i] = freq[i] + ((i != (1 << 8) - 1) ? cumm[i + 1] : 0);
	sort(sub,sub + N);
	sort(req,req + R);
	printf("%d\n",solve());	
	return 0;
}
