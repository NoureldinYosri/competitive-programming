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
int A[MAX],B[MAX],n,a,b;
map<int,int> M;
int main(){
	scanf("%d %d %d",&n,&a,&b);
	loop(i,n) scanf("%d",A + i),M[A[i]] = i;
	queue<int> q;
	loop(i,n){
		int x = A[i];
		bool c1 = M.find(a - x) != M.end();
		bool c2 = M.find(b - x) != M.end();
		if(c1 && c2) continue;
		if(!c1 && !c2){
			puts("NO");
			return 0;
		}
		q.push(A[i]);
	}

	while(!q.empty()){
		int x = q.front(); q.pop();
		if(M.find(x) == M.end()) continue;
		bool c1 = M.find(a - x) != M.end();
		bool c2 = M.find(b - x) != M.end();
		if(!c1 && !c2){
			puts("NO");
			return 0;
		}
		if(c1){
			B[M[x]] = B[M[a - x]] = 1;
			if(M.find(a - x) != M.end()) M.erase(a - x);		
			x = a - x;
			if(M.find(b - x) != M.end()) q.push(b - x);
		}
		else{
			B[M[x]] = B[M[b - x]] = 2;
			if(M.find(b - x) != M.end()) M.erase(b - x);		
			x = b - x;
			if(M.find(a - x) != M.end()) q.push(a - x);
		}	
		if(M.find(x) != M.end()) M.erase(x);
	}	
	loop(i,n) B[i] = max(B[i],1);
	puts("YES");
	loop(i,n) printf("%d%c",--B[i]," \n"[i==n-1]);
//	prArr(B,n,int);
	
	return 0;
}
