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

const int MAX = 1 << 20;
const ll oo = 1LL << 60;
int cnt[301];
vl vals[301];
ll dp[MAX];
int n,S;
vi ring;
class curve{
public:
	int s,w,t;
	curve(){s=w=0;t=-1;}
	curve(int s,int w){
		this->s = s;
		this->w = w;
		t = -1;
	}
	ll eval(int tw) const {
		assert(tw > w);
		tw = (tw - w)/s - 1;
		if(tw >= sz(vals[s])) return 0;
		return dp[w] + vals[s][tw];
	}
	int get_time(const curve & o){
		int st = 1,en = cnt[s];
		while(st < en){
			int m = (st + en) >> 1;
			if(this->eval(o.w + m*s) <= o.eval(o.w + m*s)) en = m;
			else st = m + 1;
		}
		return o.w + st*s;
	}
};
deque<curve> dq;


void bf(){
	vl dp(S + 1,-oo);
	dp[0] = 0;
	for(int s = 1;s <= 300;s++) if(cnt[s]) {
		for(int k = 0;k < cnt[s];k++){
			for(int w = S;w - s >= 0;w--)
				dp[w] = max(dp[w],dp[w - s] + vals[s][k]);
		}
	}
	print(dp,ll);
}

int main(){
	#ifndef ONLINE_JUDGE
//		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&S);
	loop(i,n){
		int s,v;
		scanf("%d %d",&s,&v);
		vals[s].pb(v);
		cnt[s]++;
	}
//	bf();
	range(s,1,300){
		if(!cnt[s]) continue;
		sort(all(vals[s]));
		reverse(all(vals[s]));
//		cerr << s << " : ";
//		print(vals[s],ll);
		ll sum = 0;
		for(auto & v : vals[s])
			v = sum += v;
	}
	fill(dp,dp + S + 1,-oo);
	dp[0] = 0;
	range(s,1,300){
		if(!cnt[s]) continue;
		for(int r = 0;r < s;r++){
			ring.clear();
			dq.clear();

			for(int i = r;i <= S;i += s) ring.pb(i);
			int nxt = sz(ring) - 1;
			for(int i = 0;nxt >= 0 && i < cnt[s];i++,nxt--)	{
				curve C = curve(s,ring[nxt]);
				if(!dq.empty()) C.t = C.get_time(dq[0]);
				while(sz(dq) > 1 && C.t >= dq[0].t) {
					dq.pop_front();
					if(dq.empty()) C.t = -1;
					else C.t = C.get_time(dq[0]);
				}
				dq.push_front(C);
			}

			for(int cur = sz(ring)-1;cur > 0;cur--){
				int tw = ring[cur];
				while(!dq.empty() && dq.back().w >= tw) dq.pop_back();
				if(nxt >= 0){
					curve C = curve(s,ring[nxt]);
					if(!dq.empty()) C.t = C.get_time(dq[0]);
					while(sz(dq) > 1 && C.t >= dq[0].t) {
						dq.pop_front();
						if(dq.empty()) C.t = -1;
						else C.t = C.get_time(dq[0]);
					}
					dq.push_front(C);
					nxt--;
				}
				while(sz(dq) > 1 && dq[sz(dq) - 1].eval(tw) <= dq[sz(dq) - 2].eval(tw)) dq.pop_back();
				dp[tw] = max(dp[tw],dq.back().eval(tw));
			}
		}
/*		loop(i,S+1) {
			if(dp[i] < 0) cerr << "NO ";
			else cerr << dp[i] << " ";
		}
		cerr << endl;
*/	}
	ll mx = 0;
	range(s,1,S) {
		mx = max(mx,dp[s]);
		printf("%lld%c",mx," \n"[s==S]);
	}
	return 0;
}


