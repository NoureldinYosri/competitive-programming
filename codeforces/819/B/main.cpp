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

int P[1 << 20],n;
ll cost;
int small,big;
deque<int> pos;

void debug(int k){
	vi Q(n);
	Q[n-1] = k;
	loop(i,n-1) {
		k = (k + 1)%n;
		Q[i] = k;
	}
	loop(i,n) Q[i] = P[i] - Q[i];
	print(Q,int);
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	pos.resize(n);
	loop(i,n) {
		scanf("%d",P + i); P[i]--;
		int d = P[i] - i;
		cost += abs(d);
		if(d <= 0) small++;
		else pos[d]++,big++;
	}
	ll best = cost; int sh = 0;
	loop(nxt,n-1) {
		int d = P[n-1-nxt] - (n-1);
		if(d <= 0) small--;
		else {
			big--;
			pos[d]--;
		}
		cost -= abs(d);
		cost += small - big;
		cost += P[n-1-nxt];
		//cerr << nxt << " " << small << " " << big << " " << cost << endl;
		//debug(nxt);
		if(cost < best) {
			best = cost;
			sh = nxt+1;
		}

		big -= pos[1];
		small += pos[1];
		pos.pop_front();
		pos.push_back(0);
		d = P[n-1-nxt];
		if(d <= 0) small++;
		else pos[d]++,big++;
	}
	cout << best << " " << sh << endl;
	return 0;
}
