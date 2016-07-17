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

int A[100];

int main(){
	int T,N,a;
	scanf("%d",&T);
	loop(t,T){
		scanf("%d",&N);
		int ones = 0;	
		PQ<pi> pq;
		loop(i,N) scanf("%d",A + i),pq.push(mp(A[i],i));
		printf("Case #%d:",t + 1);
		if(N == 2){
			int c = A[1] > A[0];
			for(;A[c] > A[1 - c];A[c]--) printf(" %c",c + 'A');
			for(;A[0];A[0]--) printf(" AB");
			puts("");
		}	
		else if(N & 1){
			while(!pq.empty()){
				auto q = pq.top(); pq.pop();
				if(q.xx == 1) continue;
				printf(" %c",q.yy + 'A');
				q.xx--;
				pq.push(q);
			}
			for(int i = 2;i < N;i++) printf(" %c",i + 'A');
			puts(" AB");
		}
		else{
			while(!pq.empty()){
				auto q = pq.top(); pq.pop();
				if(q.xx == 1) continue;
				printf(" %c",q.yy + 'A');
				q.xx--;
				pq.push(q);
			}
			for(int i = 0;i < N/2;i ++) printf(" %c%c",2*i + 'A',2*i + 1 + 'A');
			puts("");
		}
				
	}
	return 0;
}
