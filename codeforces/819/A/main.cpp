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


string get_a(string & ret,int a){
	vi usable(26,1);
	for(int i = 0;i < a && i < sz(ret);i++)
		usable[ret[sz(ret)-i-1] - 'a'] = 0;
	string r = "";
	for(int i = 0;i < 26 && sz(r) < a;i++)
		if(usable[i])
			r += i + 'a';
	assert(sz(r) == a);
	return r;
}

string get_blk(string & ret,int a,int b){
	string r = get_a(ret,a);
	loop(i,b) r.pb(r[a-1]);
	return r;
}

string work(int a,int b,int & offset,int & period){
	string ret , cur_blk = "";
	map<string,int> vis;
	int ti = 0;
	while(vis.find(cur_blk = get_blk(ret,a,b)) == vis.end()) {
		ret += cur_blk;
		vis[cur_blk] = ti++;
	}
	offset = (a + b)*vis[cur_blk];
	period = (a + b)*(ti - vis[cur_blk]);
	return ret;
}



int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	int a,b,l,r;
	cin >> a >> b >> l >> r;
	l--,r--;
	if(b > a) {
		int len = a + b;
		int u = l/len,v = r/len;
		if(v - u > 1) cout << a + 1 << endl;
		else if(u == v){
			l %= len,r %= len;
			assert(r >= l);
			if(l >= a) cout << 1 << endl;
			else cout << min(r,a-1) - l + 1 << endl;
		}
		else {
			l %= len,r %= len;
			cerr << l << " " << r << " " << a << " " << b << endl;
			int ans = min(min(r,a-1),l-1) + 1;
			if(l < a) ans += a - l + 1;
			else ans++;
			cout << ans << endl;
		}
	}
	else {
		int offset,period;
		string str = work(a,b,offset,period);
		//cerr << str << endl;
		if(r < offset) {
			set<char> S;
			for(;l <= r;l++) S.insert(str[l]);
			cout << sz(S) << endl;
		}
		else {
			set<char> S;
			for(;l < offset;l++) S.insert(str[l]);
			l -= offset,r -= offset;
			int u = l/period,v = r/period;
			if(v - u > 1) {
				loop(i,period) S.insert(str[offset + i]);
			}
			else if(u == v){
				l %= period;
				r %= period;
				int t = r/(a + b);
				r = min(r,t*(a + b) + a - 1);
				r = max(l,r);
				for(;l <= r;l++) S.insert(str[l]);
			}
			else {
				l %= period;
				r %= period;
				cerr << l << " " << r << " " << str.substr(offset,sz(str) - offset) << endl;
				int t = r/(a + b);
				r = min(r,t*(a + b) + a - 1);
				for(;l + offset < sz(str);l++) S.insert(str[l + offset]);
				for(l=0;l <= r;l++) S.insert(str[l + offset]);
			}
			cout << sz(S) << endl;
		}
	}
	return 0;
}
