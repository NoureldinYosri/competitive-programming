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
using namespace std;

ll BIT[1 << 20];
int N;

void update(int x,ll v){
	for(;x <= N;x += x & (-x)) BIT[x] += v;
}

ll get(int x){
	ll ans = 0;
	for(;x;x -= x & (-x)) ans += BIT[x];
	return ans;
}

char S[1 << 20],Z[1 << 20];

int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%s %s",S,Z);
		N = strlen(S);
		queue<int> A,B;
		loop(i,N) 
			if(S[i] == 'a') A.push(i);
			else B.push(i);
		fill(BIT,BIT + N + 1,0);
		ll ans = 0;
		loop(i,N){
			cout << i << " " << i + get(i) << " " << S[i + get(i)]<< " " << sz(A) << " " << sz(B) << endl;		
			if(S[i + get(i)] != Z[i]){
				if(S[i + get(i)] == 'a') {
					if(B.empty()){
						ans = -1;
						break;
					}
					int u = B.front(); B.pop();
					update(i + 1,-1);
					update(u + 1,1);
					ans += u - i;
					cout << i << " B " << u - i << endl;
				}
				else{
					if(A.empty()){
						ans = -1;
						break;
					}
					int u = A.front(); A.pop();
					update(i + 1,-1);
					update(u + 1,1);
					ans += u - i;
					cout << i << " A " <<  u - i << endl;
				}
			} 
			else if(S[i + get(i)] == 'a') A.pop();
			else B.pop();
		}		
		printf("%lld\n",ans);	
	}
}
