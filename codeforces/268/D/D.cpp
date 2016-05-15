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

int A[1 << 20],n,a,b;
int B[1 << 20],Z[1 << 20];
multiset<int> S;
map<int,vi > M;

int main(){
	scanf("%d %d %d",&n,&a,&b);
	loop(i,n) {
		scanf("%d",&A[i]),S.insert(A[i]);	
		M[A[i]];
		M[A[i]].pb(i);
	}
	loop(i,n){
		if(Z[i] == 0){
			Z[i] = 1;
			if(S.find(a - A[i]) != S.end()){
				S.erase(S.find(A[i]));
				if(a - A[i] != A[i]) {
					S.erase(S.find(a - A[i]));
					Z[M[a - A[i]].back()] = 1;
					M[a - A[i]].pop_back();
				}
			}  
			else if(S.find(b - A[i]) != S.end()){
				S.erase(S.find(A[i])); B[i] = 1;  
				if(b - A[i] != A[i]) {
					S.erase(S.find(b - A[i]));
					Z[M[b - A[i]].back()] = 1;
					B[M[b - A[i]].back()] = 1;
					M[b - A[i]].pop_back();
				}			
			}
			else {
				cout << "NO" << endl;
				return 0;
			}
		}
	}	
	loop(i,n) printf("%d%s",B[i],(i == n - 1) ? "\n" : " ");
	return 0;
}
