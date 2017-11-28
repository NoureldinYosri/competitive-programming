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

vi who[2*26];
int n;
char buffer[4*2 + 1];
vector<vi> content;
bool vis[40*1000][2*26+1];

void read_molecule() {
	scanf("%s",buffer);
	vi aux;
	for(int i = 0;i < 8;i += 2) {
		if(buffer[i] == '0') continue;
		int c = buffer[i] - 'A';
		int sgn = 0;
		if(buffer[i + 1] == '-') sgn = 1;
		aux.pb(c*2 + sgn);
	}
	if(sz(aux) <= 1) return;
	content.pb(aux);
}

string i2c(int x){
	string ret = "00";
	ret[0] = 'A' + (x/2);
	if(x&1) ret[1] = '-';
	else ret[1] = '+';
	return ret;
}

void output(vi & V) {
//	for(int x : V) cerr << i2c(x) << " ";
//	cerr << endl;
}

int dfs(int cur,int from,int target) {
	vis[cur][from] = 1;
	for(int f : content[cur]){
		if(f == from) {
			from = 2*26;
			continue;
		}
		if(f == target) {
			output(content[cur]);
			return 1;
		}
		for(int nxt : who[f^1])
			if(!vis[nxt][f^1] && dfs(nxt,f^1,target)){
				output(content[cur]);
				return 1;
			}
	}
	return 0;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	int n; scanf("%d",&n);
	loop(i,n) read_molecule();
	sort(all(content));
	content.resize(unique(all(content)) - content.begin());
	loop(i,sz(content))
		for(int x : content[i])
			who[x].pb(i);
	loop(i,2*26) {
		sort(all(who[i]));
		who[i].resize(unique(all(who[i])) - who[i].begin());
	}
//	for(auto V: content) {
//		print(V,int);
//	}
	loop(i,26*2){
		int j = i ^ 1;
		memset(vis,0,sizeof vis);
		loop(cur,sz(content)){
			bool yes = 0;
			for(int f : content[cur])
				yes |= f == i;
			if(yes && !vis[cur][i] && dfs(cur,i,j)){
//				cerr << "target pair is " << i2c(i) << " " << i2c(j) << endl;
				puts("unbounded");
				return 0;
			}
		}
	}
	puts("bounded");
	return 0;
}
