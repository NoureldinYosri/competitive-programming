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

const int MAX = 3e5 + 1;
int not_prime[MAX];
int P[MAX],cnt = 0;
int N;
int S[MAX],E[MAX];

void sieve(){
	range(i,2,N)
		if(!not_prime[i]){
			P[cnt++] = i;
			for(ll j = i*1LL*i;j <= N;j += i)
				not_prime[j] = 1;
		}
}

void ask(int x){
	cout << x << endl;
}

int read(){
	char c; scanf(" %c",&c);
	if(c == '<') return -1;
	if(c == '=') return 0;
	return 1;
}
void erase(int idx){
	if(idx != cnt-1) swap(P[idx],P[cnt-1]);
	cnt--;
}

int main(){
	scanf("%d",&N);
	sieve();
	vi R;
	loop(i,42) {
		ask(2);
		if(i) R.pb(read());
		else {
			char c ; scanf(" %c",&c);
			if(c == 'O') return 0;
			if(c == '>') R.pb(1);
			else if(c == '<') R.pb(-1);
			else R.pb(0);
		}
	}
	loop(i,N+1) S[i] = 1,E[i] = i - 1;
	vi cand(P,P + cnt);		
	for(int r : R){
		assert(r != 0);
		loop(i,cnt){
			int p = P[i];
		//	if(p == 79) cerr << S[p] << " " << E[p] << " (" << r << ") -> " ;
			if(r == 1){
				if((p + 1)/2 <= S[p]) erase(i),i--;
				else{
					E[p] = min(E[p],p/2);
			//		if(p == 79) prp(mp(S[p],E[p]));
					S[p] <<= 1;
					E[p] <<= 1;
				}
			}
			else{
				if(E[p] < (p + 1)/2) erase(i),i--;
				else{
					S[p] = max(S[p],(p + 1)/2);
				//	if(p == 79) prp(mp(S[p],E[p]));
					S[p] = (S[p] << 1)%p;
					E[p] = (E[p] << 1)%p;
				}
			}
	//		if(p == 79) cerr << S[p] << " " << E[p] << endl;
		}
	}
	assert(cnt <= 10);
	for(int i = cnt-1;i >= 0;i--){
		int p = P[i]; set<int> S;
		range(i,1,p-1) S.insert(i);
		for(int r : R){
			vi D;
			if(r == 1) {
				for(int x : S) if(x > p/2) D.pb(x);
			}
			else {
				for(int x : S) if(x <= p/2) D.pb(x);
			}
			for(int x : D) S.erase(x);
			set<int> T = S;
			S.clear();
			for(int x : T) S.insert((x << 1)%p);
		}
		if(!S.empty()){
			ask(p);
			return 0;
		}
	}
	assert(0);	
	return 0;
}
