#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
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
using namespace std;

struct suffixAutomata{
	vector<map<int,int> > to;
	vi link,len;
	int q0,nq;

	int create_state(){
		int q = sz(link);
		link.pb(0);
		len.pb(0);
		to.pb(map<int,int>());
		return q;
	}

	suffixAutomata(){
		nq = q0 = create_state();
	}

	void insert(int c){
		int q = nq;
		nq = create_state();
		len[nq] = len[q] + 1;
		while(to[q].find(c) == to[q].end()) {
			to[q][c] = nq;
			q = link[q];
		}
		if(to[q][c] == nq) link[nq] = 0;
		else{
			int t = to[q][c];
			if(len[t] == len[q] + 1) link[nq] = t;
			else {
				int clone = create_state();
				to[clone] = to[t];
				link[clone] = link[t];
				len[clone] = len[q] + 1;
				link[nq] = link[t] = clone;
				while(to[q][c] == t) {
					to[q][c] = clone;
					q = link[q];
				}
			}
		}
	}

	suffixAutomata(const char *S) {
		int n = strlen(S);
		link.reserve(2*n+3);
		to.reserve(2*n+3);
		len.reserve(2*n+3);
		nq = q0 = create_state();
		for(const char *p = S;*p;p++)
			insert(*p);
	}


	friend ostream& operator << (ostream & st,const suffixAutomata & SA) {
		st << "transitions" << endl;
		for(int u = 0;u < sz(SA.to);u++)
			for(auto & p : SA.to[u])
				st << u << " " << p.yy << " " << (char) p.xx << endl;
		st << "links" << endl;
		for(int u = 0;u < sz(SA.to);u++)
			st << u << ": " << SA.link[u] << endl;
		return st;
	}

};


int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	string T,P;
	cin >> T >> P;
	suffixAutomata SA(T.c_str());
//	cout << SA << endl;
	int q = SA.q0;
	int ans = 0,len = 0;
	for(char c : P) {
		while(q != SA.q0 && !SA.to[q].count(c)) {
			q = SA.link[q];
			len = SA.len[q];
		}
		if(SA.to[q].count(c)) q = SA.to[q][c],len++;
		ans = max(ans,len);
	}
	cout << ans << endl;
	return 0;
}
