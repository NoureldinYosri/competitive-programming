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

const int MAX = 100'010;
int A[MAX],n,offset;
int dp[100][100][2];
pair<int,pi> util[100][100][2];
int cnt[MAX];
int B[MAX];

int eval(int s,int e){
	int cur = 1;
	for(int i = s;i <= e;i++)
		cur = (!cur) || A[i];
	return cur;
}

int solve(int s,int e,int t){
	if(dp[s - offset][e - offset][t] != -1) return dp[s - offset][e - offset][t];
	int & ret = dp[s - offset][e - offset][t]; ret = 0;
	pair<int,pi> & aux = util [s - offset][e - offset][t];
	if(t == eval(s,e)) {
		aux.xx = -1;	
		return ret = 1;
	}
	for(int k = s;k < e && !ret;k++){
		if(t == 0) {
			ret = solve(s,k,1) && solve(k+1,e,0);
			aux.xx = k;
			aux.yy.xx = 1;
			aux.yy.yy = 0;
		}
		else if(solve(s,k,0)) {
			ret = 1;
			aux.xx = k;
			aux.yy.xx = 0;
			aux.yy.yy = -1;
		}
		else{
			ret = solve(s,k,1) && solve(k+1,e,1);
			aux.xx = k;
			aux.yy.xx = 1;
			aux.yy.yy = 1;
		}
	}
	return ret;
}

void recon(int s,int e,int t){
	if(t == -1 || util[s - offset][e - offset][t].xx == -1) {
		for(int i = s;i <= e;i++){
			loop(k,cnt[i]){
				printf("%d",A[i]);
				if(k != cnt[i]-1) printf("->");
			}
			if(i != e) printf("->");
		}
		return;
	}
	int k = util[s - offset][e - offset][t].xx;
	int t1 = util[s - offset][e - offset][t].yy.xx;
	int t2 = util[s - offset][e - offset][t].yy.yy;
	recon(s,k,t1);
	printf("->");
	putchar('(');
	recon(k+1,e,t2);
	putchar(')');
}

int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	int m = 0;
	loop(i,n) {
		if(!A[i]){
			B[m] = A[i];
			cnt[m++] = 1;
			continue;
		}
		int j = i;
		while(j < n && A[j]) j++;
		cnt[m] = j - i;
		B[m] = 1;
		m++;
		i = j - 1;
	}
	copy(B,B + m,A);
	n = m;

	memset(dp,-1,sizeof dp);
	if (n < 100) {
		offset = 0;
		cerr << solve(0,n-1,0) << endl;
		puts(solve(0,n-1,0) ? "YES" : "NO");
		if(solve(0,n-1,0)) recon(0,n-1,0);
	}
	else{
		offset = n - 100;
		int cur = 1;
		loop(i,offset) cur = !cur || A[i];
		if(!cur) offset++;
		cerr << solve(offset,n-1,0) << endl;
		puts(solve(offset,n-1,0) ? "YES" : "NO");
		if(solve(offset,n-1,0)){
			loop(i,offset) {
				loop(j,cnt[i])			
					printf("%d->",A[i]);
			}
			recon(offset,n-1,0);
		}
	}
	
	return 0;
}
