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

const int MAX = 10*1000 + 10;
int n;
char *I[MAX],buffer[50];

int brute_force() {
	set<string> S{I,I + n};
	vector<string> V {all(S)};
	for(string s : V)
		for(string t : V) {
			for(int i = 1;i <= sz(s);i++)
				for(int j = 1;j <= sz(t);j++) {
					string tmp = s.substr(0,i) + t.substr(sz(t)-j,j);
//					if(S.count(tmp))
//						cerr << s << " " << i << " " << t << " " << j << " -> " << tmp << endl;
					S.insert(tmp);
				}
		}
	return sz(S);
}

int pref[MAX*50][128],suff[MAX*50][128];
int siz1,siz2;

void insert(char *ptr,int trie[MAX*50][128],int & siz) {
	int cur = 0;
	for(;*ptr;ptr++) {
		if(!trie[cur][*ptr]) {
			trie[cur][*ptr] = ++siz;
//			cerr << cur << " " << trie[cur][*ptr] << " " << *ptr << endl;
		}
		cur = trie[cur][*ptr];
	}
}

set<string> aux;
set<pi> vis;
void dfs(int u,int v,string A,string B) {
	if(vis.count(mp(u,v))) return;
	vis.insert(mp(u,v));
	if(sz(A) && sz(B)) {
		string tmp = B;
		reverse(all(tmp));
		tmp = A + tmp;
		if(aux.count(tmp))
			cerr << A + " + " + B + " = " + tmp << endl;
		aux.insert(tmp);
	}
	for(char c = 'a';c <= 'z';c++)
		if(pref[u][c])
			dfs(pref[u][c],v,A + c,B);
	for(char c = 'a';c <= 'z';c++)
		if(suff[v][c])
			dfs(u,suff[v][c],A,B + c);

}

void getDublicates(){
	dfs(0,0,"","");
}

ll solve(){
	ll ret = 0;
	for(int i = 0;i < n;i++) {
		insert(I[i],pref,siz1);
		reverse(I[i],I[i] + strlen(I[i]));
		insert(I[i],suff,siz2);
		reverse(I[i],I[i] + strlen(I[i]));
	}
	ret = siz1 * (ll) siz2;
//	getDublicates();
	set<string> S;
	for(int i = 0;i < n;i++)
		S.insert(string(I[i]));
	for(string  s : S)
		ret -= sz(s) - 2;
	return ret;
}

int main(int argc,char **argv){
	freopen("dictionary.in","r",stdin);
#ifndef HOME
	freopen("dictionary.out","w",stdout);
#endif
	scanf("%d",&n);
	loop(i,n) {
		scanf("%s",buffer);
		I[i] = new char[strlen(buffer)+1];
		strcpy(I[i],buffer);
	}
	printf("%lld\n",solve());
	cout << "correct: " << brute_force() << endl;
	return 0;
}
