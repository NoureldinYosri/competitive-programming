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

int CTR[64],n,K;
ll A[1 << 20];
ll X;

ll eval(){
	ll ans = 0;
	loop(i,64) if(CTR[i]) ans |= 1 << i;
	return ans;
}

void F(int i){
	ll x = A[i];
	for(int j = 0;x;x >>= 1,j++)
		CTR[j] -= x & 1;
	x = A[i] * X;
	A[i] = x;
	for(int j = 0;x;x >>= 1,j++)
		CTR[j] += x & 1;
}

void iF(int i){
	ll x = A[i];
	for(int j = 0;x;x >>= 1,j++)
		CTR[j] -= x & 1;
	x = A[i] / X;
	A[i] = x;
	for(int j = 0;x;x >>= 1,j++)
		CTR[j] += x & 1;
}

int main(){
	scanf("%d %d %I64d",&n,&K,&X);
	loop(i,n) {
		scanf("%I64d",A + i);
		ll x = A[i];
		for(int j = 0;x;j++,x >>= 1)
			CTR[j] += x & 1;
	}
	loop(i,K){
		int c = 0;
		ll cmax = 0;
		loop(j,n){
			F(j);
			ll tmp = eval();
			if(tmp > cmax){
				cmax = tmp;
				c = j;
			}
			else if(tmp == cmax && A[j] > A[c]*X) c = j
			iF(j);
		}
		F(c);		
	}
	cout << eval() << endl;
	return 0;
}
