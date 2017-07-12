#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;


struct val{
	ll first;
	int second;
public:
	bool operator < (const val & o) const {
		return tie(first,second) < tie(o.first,o.second);
	}
};

int S,n;
val A[1 << 20];

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&S);
	loop(i,n) scanf("%lld",&A[i].first),A[i].second = i + 1;
	sort(A,A + n);
	int K = 0;
	for(int k = 1;k <= n;k++){
		loop(i,n) A[i].xx += A[i].yy;
		for(int i = 0;i < n;i++){
			int j = i;
			while(j && A[j] < A[j - 1]) {
				swap(A[j - 1],A[j]);
				j--;
			}
		}
		ll sum = 0; int ctr = 0;
		loop(i,n){
			if(sum + A[i].xx <= S){
				sum += A[i].xx;
				ctr++;
			}
			else break;
			if(ctr == k) break;
		}
		K = k;
		if(ctr < k){
			if(k == 1) {
				cout << "0 0" << endl;
				return 0;
			}
			else {
				K = k - 1;
				loop(i,n) A[i].xx -= A[i].yy;
				break;
			}
		}
		while(n && A[n-1].xx > S) n--;
	}
	ll sum = 0; int ctr = 0;
	loop(i,K){
		sum += A[i].xx;
	}
	cout << K << " " << sum << endl;
	return 0;
}
