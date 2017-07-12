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
#define popcnt(x) ((int)__builtin_popcountll(x))
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

int A[1 << 20],n;
int two = 0,three = 0;
ll p2[18],p3[12];

int mininmize(ll sh,ll sw,int rh,int rw){
	int ret = 1000;
	for(int atwo = 0;atwo <= min(17,two);atwo++){
		if(ret <= atwo) break;
		for(int btwo = 0;btwo <= min(17,two - atwo);btwo++){
			if(ret <= atwo + btwo) break;
			for(int athree = 0;athree <= min(11,three);athree++){
				if(ret <= atwo + btwo + athree) break;
				for(int bthree = 0;bthree <= min(11,three - athree);bthree++){
					if((rh + sh - 1)/sh <= p2[atwo]*p3[athree] && (rw + sw - 1)/sw <= p2[btwo]*p3[bthree]){
						ret = min(ret,atwo + btwo + athree + bthree);
						break;
					}
				}
			}
		}
	}
	return ret;
}

int solve(int h,int w,int a,int b){
	int rh = (a + h - 1)/h,rw = (b + w - 1)/w;
	int ret = 1000;
	for(int k = 0;k <= n;k++){
		loop(msk,1 << k){
			if(popcnt(msk) > 9) continue;
			if(k - popcnt(msk) > 9) continue;
			ll sh = 1,sw = 1;
			loop(i,k) {
				if(msk & (1 << i)) sh = min(rh+0LL,sh*A[i]);
				else sw = min(rw+0LL,sw*A[i]);
			}
			ret = min(ret,k + mininmize(sh,sw,rh,rw));
		}
	}
	return ret;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	int a,b,h,w;
	scanf("%d %d %d %d",&a,&b,&h,&w);
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	sort(A,A + n);
	reverse(A,A + n);
	while(n > 0 && A[n-1] == 1) n--;

	while(n > 0 && A[n-1] == 2) {
		two++;
		n--;
	}
	while(n > 0 && A[n-1] == 3) {
		three++;
		n--;
	}
	n = min(n,18);
	two = min(two,17*2);
	three = min(three,11*2);

	p2[0] = p3[0] = 1;
	loop(i,17) p2[i + 1] = p2[i] * 2;
	loop(i,11) p3[i + 1] = p3[i] * 3;

	int ans = min(solve(h,w,a,b),solve(h,w,b,a));
	if(ans >= 1000) ans = -1;
	cout << ans << endl;

	return 0;
}
