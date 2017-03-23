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

const int MAX = 200000 + 100;
int A[MAX],B[MAX],no[MAX],n;
int C[MAX],k,m;
vi pos[MAX];

int f(int x,int c){
	int cnt = n - x;	
	loop(i,k) cnt -= pos[C[i]].end() - upper_bound(all(pos[C[i]]),x);
	if(c) cnt -= pos[A[x]].end() - upper_bound(all(pos[A[x]]),x);	
	if(!cnt && no[A[x]]) cnt--;
	return cnt;
}

int main(){
	pos[0].pb(0);
	scanf("%d",&n);
	range(i,1,n) {
		scanf("%d %d",A + i,B + i);
		pos[A[i]].pb(i);
	}
	scanf("%d",&m);
	loop(g,m){
		scanf("%d",&k);
		loop(i,k) scanf("%d",C + i),no[C[i]] = 1;
		int s = 1,e = n;
		while(s < e){
			int mid = s + (e - s + 1)/2;
			if(f(mid,0) >= 0) s = mid;
			else e = mid - 1;
		}
		if(no[A[s]]) s = 0;
		else{
			int c = A[s];
			s = 0,e = sz(pos[c]) - 1;
			while(s < e){
				int mid = (s + e) >> 1;
				if(f(pos[c][mid],1) == 0) e = mid;
				else s = mid + 1;
			}
			s = pos[c][s];
		}
		printf("%d %d\n",A[s],B[s]);
		loop(i,k) no[C[i]] = 0;
	}	
	return 0;
}
