#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define prp(p) cout << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cout << #A << ": "; copy(A,A + n,ostream_iterator<t>(cout," " )); cout << endl
using namespace std;

int A[1 << 20],V[1 << 20],n;
int B[1 << 20];
int Q[1 << 20];

int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%d",&A[i]),A[i]--;
	vi odd;
	vector<pi> even;
	loop(i,n){ 
		if(V[i] == 0){
			if(A[i] == i){
				B[i] = i;			
				continue;
			}		
			int j = i,ctr = 0;
			while(!V[j]){
				V[j] = 1;
				j = A[j];
				++ctr;
			}
			if(!(ctr & 1)) even.pb(mp(ctr,i));
			else odd.pb(i);	
		}
	}
	sort(all(even));
	loop(i,sz(even)){
		if(i == n - 1 || even[i].xx != even[i + 1].xx){
			cout << -1 << endl;
			return 0;
		}
		int a = even[i].yy,b = even[i + 1].yy,u,v,c = 1;
		u = a; v = b;
		while(c || (u != a)){
			c = 0;
			B[u] = v;
			u = A[u];
			swap(u,v);
		}
		i++;
	}
	for(int i : odd){
		int j = i,u = i,c = 1,idx = 0,e = 0;
		while(c || j!=i){
			c = 0;
			V[e++] = j;
			j = A[j];
		}
		for(j = 0;j < e;j++){
			Q[idx] = V[j];
			idx += 2;
			if(idx >= e) idx -= e;
		}
		for(j = 0;j < e;j++){
			int u = Q[j],v = (j + 1 == e) ? Q[0] : Q[j + 1];
			B[u] = v;
		}
	}
	loop(i,n) printf("%d%c",B[i] + 1,(i + 1 == n) ? '\n' : ' ');
	return 0;
}
