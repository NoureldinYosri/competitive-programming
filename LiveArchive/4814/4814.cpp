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

int A[3],B[3],ord[3];
int V[53];

bool cant_lose(){
	loop(i,3) ord[i] = i;
	do{
		int his_score = 0;
		loop(i,3) his_score += A[i] < B[ord[i]];
		if(his_score <= 1) return 0;
	}while(next_permutation(ord,ord + 3));
	return 1;
}

int solve(){
	for(int i = 1;i <= 52;i++){
		if(V[i]) continue;
		B[2] = i;
		if(cant_lose()) return i;
	}
	return -1;
}

int main(){
	while(1){
		fill(V,V + 53,0);
		loop(i,3) scanf("%d",A + i),V[A[i]] = 1;
		loop(i,2) scanf("%d",B + i),V[B[i]] = 1;
		if(V[0]) break;
		printf("%d\n",solve());	
	}		
	return 0;
}
