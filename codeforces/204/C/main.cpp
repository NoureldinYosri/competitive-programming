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



const int MAX = 1 << 18;
char A[MAX],B[MAX];
int n;
vi pos[128];
vl suff[128],pref[128];
vl aux;

void bf(){
	int fA[MAX] = {0},fB[MAX] = {0};
	for(int l = 1;l <= n;l++)
		for(int offset1 = 0;offset1 <= n-l;offset1++)
			for(int offset2 = 0;offset2 <= n-l;offset2++)
				for(int k = 0;k < l;k++) {
					int i = offset1 + k,j = offset2 + k;
					if(A[i] == B[j]){
						if(j <= i) fA[i]++;
						else fB[i]++;
 					}
				}
	for(int i = 0;i < n;i++)
		cerr << i << " " << A[i] << " -> " << fA[i] << " " << fB[i] << endl;
	cerr << "================================" << endl;
}


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %s %s",&n,A,B);
	//bf();
	loop(i,n) pos[(int)B[i]].pb(i);
	double ans = 0;
	loop(i,128) if(!pos[i].empty()){
		ll sum = 0;
		for(int x : pos[i]) {
			sum += x+1;
			pref[i].pb(sum);
		}

		sum = 0;
		reverse(all(pos[i]));
		for(int x : pos[i]) {
			sum += n-x;
			aux.pb(sum);
		}
		reverse(all(pos[i]));
		reverse(all(aux));
		suff[i].swap(aux);
//		print(suff[i],int);
	}
	loop(i,n) {
		int c = A[i];
		if(suff[c].empty()) continue;
		auto p = upper_bound(all(pos[c]),i);
		int idx = p - pos[c].begin();
		ll a = 0,b = 0;
		// sum for j <= i ... j + n - i
		a = (n - i + 0LL)*(idx ? pref[c][idx - 1] : 0);
		//
//		ll cnt = sz(pos[c]) - idx;
		ll r = 0;
		if(idx != sz(pos[c])) r = suff[c][idx];
		b = (i+1)*r ;
	//	cerr << i << " " << (char)c << " -> " << a << " " << b   << " r = " << r<< endl;
		ans += a + b;
	}
	ll tot = 0;
	for(int l = 1;l <= n;l++){
		ll cnt = n - l + 1;
		tot += cnt*cnt;
	}
	printf("%.10f\n",ans*1.0/tot);
	return 0;
}
