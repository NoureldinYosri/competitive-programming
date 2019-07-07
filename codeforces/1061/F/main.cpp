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

bool read(){
	string s; cin >> s;
	return s == "Yes";
}

bool ask(int a,int b,int c) {
	cout << "? " << a << " " << b << " " << c << endl;
	cout.flush();
	return read();
}


int main(int argc,char **argv){
	int n,k;
	cin >> n >> k;
	int ctr = 60*n;

	set<int> cand;
	for(int i = 1;i <= n;i++)
		cand.insert(i);
	for(;ctr > 10 && sz(cand) > 2;ctr--) {
		vi C{all(cand)};
		random_shuffle(all(C));
		int g = C[0];
		int a = C[1],b = C[2];
		if(ask(a,g,b)) {
			cand.erase(a);
			cand.erase(b);
		}
		else cand.erase(g);
	}

	int root = *cand.begin();
	if(sz(cand) > 1) {
		int g1 = *cand.begin(),g2 = *cand.rbegin();
		int c ;
		vi aux;
		for(c = 1;c <= n;c++){
			if(c != g1 && c != g2) aux.pb(c);
		}

		for(;ctr > 0 && !aux.empty();) {
			random_shuffle(all(aux));
			int a = aux.back();
			ctr--;
			if(!ask(a,g1,g2))
				swap(g1,g2);
		}
		root = g1;

	}
	cout << "! " << root << endl;
	return 0;
}
