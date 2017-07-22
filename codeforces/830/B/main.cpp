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


vi idx[1 << 20];
int A[1 << 20],n;

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(i,n) {
		scanf("%d",A + i);
		idx[A[i]].pb(i);
	}
	sort(A,A + n);
	int m = unique(A,A + n) - A;
	ll ans = 0;
	int cnt = 0,lst = -1;
	vi V{A,A + m},tmp;
	for(int x : V){
		if(cnt & 1) {
			loop(i,sz(idx[x])) idx[x][i] += n;
		}
		int nlst = 0;
		for(int y : idx[x]) {
			if(y > lst) {
				ans += cnt + 1;
				nlst = y;
			//	cerr << "type 1 : " << x << " " << cnt  << " y = " << y << endl;
			}
			else tmp.pb(y);
		}
//		print(tmp,int);
		lst = nlst;
		if(!tmp.empty()) {
			++cnt;
			for(int iy : tmp){
				int y = iy;
				if(y >= n) y -= n;
				else y += n;
			//	cerr << "type 2 : " << x << " " << cnt  << " y = " << y << endl;
				ans += cnt + 1;
				lst = y;
			}
			tmp.clear();
		}
	}
	cout << ans << endl;

	return 0;
}
