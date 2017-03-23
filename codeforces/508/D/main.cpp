#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 4e5 + 1e2;
int n;
char S[MAX][4];
map<string,int> M;
vi G[MAX];
int to[MAX],head[MAX],deg[MAX],nxt[MAX],done[MAX],cnt;
string rev[MAX];
vi out;
int src,snk;

void add_edge(int a,int b){
	++cnt;
	to[cnt] = b;
	deg[a]++; deg[b]--;
	nxt[cnt] = head[a];
	head[a] = cnt;
}


string pref(char *S){
	char tmp[4]; strcpy(tmp,S);
	tmp[2] = 0;
	return string(tmp);
}

string suff(char *S){
	return string(S + 1);
}


int main(){
	scanf("%d",&n);
	int m = 0;
	loop(i,n) {
		scanf("%s",S[i]);
		if(M.find(pref(S[i])) == M.end()) rev[m] = pref(S[i]),M[pref(S[i])] = m++;
		if(M.find(suff(S[i])) == M.end()) rev[m] = suff(S[i]),M[suff(S[i])] = m++;
		assert(m <= MAX);
		add_edge(M[pref(S[i])],M[suff(S[i])]);		
	}
	int odd = 0,one = 0,mone = 0;
	loop(i,m) if(deg[i] & 1) {
		odd++;
		if(deg[i] == 1) src = i,one++;
		if(deg[i] == -1) snk = i,mone++;
	}
	if(one > 1 || mone > 1 || !(odd == 2 || odd == 0)){
		puts("NO");
		return 0;
	}
	if(!odd) snk = to[head[src]];
	vi ST; int cur = src;
	while(1){
		if(head[cur]){
			ST.pb(cur);
			int e = head[cur];
			head[cur] = nxt[e];
			cur = to[e];
		}
		else{
			out.pb(cur);
			if(ST.empty()) break;
			cur = ST.back();
			ST.pop_back();
		}
	}
	reverse(all(out));
	if(sz(out) != n+1){
		puts("NO");
		return 0;
	}
	loop(i,n){
		int x = out[i],y = out[i+1];
		if(rev[x][1] != rev[y][0]){
			puts("NO");
			return 0;
		}
	}
	puts("YES");
	putchar(rev[src][0]);
	//cerr << rev[src][0];
	for(int x : out) {
		putchar(rev[x][1]);
	//	cerr << rev[x][1];
	}
	puts("");
	//cerr << endl;
	return 0;
}
