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

int n,m;
char buffer[1 << 20];

string S[3];

set<int> pos[128];


bool greedy(int who,vi & P) {
	int j = -1;
	for(char c : S[who]) {
		auto ptr = lower_bound(all(pos[c]),j);
		if(ptr == pos[c].end()) return 0;
		j = *ptr;
		P.push_back(j);
		pos[c].erase(ptr);
	}
	return 1;
}


bool solve(){
	vi ord;
	loop(i,3) ord.pb(i);

	do{
		vi P[3];
		bool can = 1;
		loop(i,3) can &= greedy(ord[i],P[i]);
		loop(i,3) {
			for(int j : P[i]){
				char c = buffer[j];
				pos[c].insert(j);
			}
		}
		if(can) return 1;
	}while(next_permutation(all(ord)));
	return 0;
}


int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d %d %s" ,&n,&m,buffer);
	loop(i,n) pos[(int)buffer[i]].insert(i);

	for(int t = 0;t < m;t++) {
		int who;
		char type;
		scanf(" %c %d",&type,&who);
		who--;
		if(type == '+') {
			char c; scanf(" %c",&c);
			S[who].push_back(c);
		}
		else {
			if(!S[who].empty())
				S[who].pop_back();
		}
		puts(solve() ? "YES" : "NO");
	}
	return 0;
}
