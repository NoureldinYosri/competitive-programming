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
int vis[MAX],A[MAX],D[MAX],n,m,cnt = 0;
 
 
bool can(int e){
	ll sum = 0; cnt = 0;
	memset(vis,0,sizeof vis);
	for(;e >= 0;e--){
		int subject = D[e];
		if(!subject) sum--;
		else{
			if(vis[subject]) sum--;
			else{
				vis[subject] = 1;
				sum += A[subject];
				cnt++;
			}
		}
		sum = max(sum,0LL);
		if(!sum && cnt == m) return 1;
	}
	return 0;
}
 
 
int main(){
	scanf("%d %d",&n,&m);
	loop(i,n) scanf("%d",D + i);
	loop(i,m) scanf("%d",A + i + 1);
	int s = 0,e = n-1;
	while(s < e){
		int m = (s + e) >> 1;
		if(can(m)) e = m;
		else s = m + 1;
	}
	if(!can(s)) s = -1;
	else s++;	
	cout << s << endl;
	return 0;
}
 
