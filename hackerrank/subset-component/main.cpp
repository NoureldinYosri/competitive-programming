#pragma GCC optimize("O3")
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
#define check(x,i) (((x >> i) & 1) != 0)
using namespace std;

int id[64],W[64],K,n;
unsigned ll A[20];
vi B[20];

inline int get(int a){
	return id[a] = (a == id[a]) ? a : get(id[a]);
}
inline void join(int a,int b){
	if(b == -1) return;
	a = get(a),b = get(b);
	if(a == b) return;
	K--;
	if(W[a] < W[b]) swap(a,b);
	W[a] += W[b];
	id[b] = a;
}

int main(){
	cin >> n;
	loop(i,n) cin >> A[i];
	int ans = 0;
	loop(i,n) loop(b,64) if(check(A[i],b)) B[i].pb(b);
	loop(msk,1 << n) {
		loop(i,64) id[i] = i,W[i] = 1;
		K = 64;
		int omsk = msk;
		while(omsk){
			int i = ffs(omsk) - 1;
			int lst = -1;
			for(int b : B[i]) {
				if(lst != -1){
					int a = get(lst),c = get(b);
					if(a == c) continue;
					if(W[a] < W[c]) a ^= c ^= a ^= c;
					W[a] += W[c];
					id[c] = a;
					K--;
					if(K == 1) break;
				}
				lst = b;
				if(K == 1) break;
			}
			omsk ^= LSOne(omsk);
		}
		ans += K;
	}
	cerr << ans << endl;
	cout << ans << endl;
	
	return 0;
}
