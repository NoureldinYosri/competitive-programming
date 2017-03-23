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
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 1000*1000 + 10;

int trie[MAX][128],fail[MAX],cnt = 1;
vector<pair<char,int> > children[MAX];
vi output[MAX];
string I[MAX];
char T[MAX],buffer[MAX];
bool yes[MAX];

void insert(const char *P,int id){
	int cur = 0;
	for(const char *ptr = P;*ptr;ptr++){
		if(!trie[cur][*ptr]) {
			children[cur].pb(mp(*ptr,cnt));			
			trie[cur][*ptr] = cnt++;
		}
		cur = trie[cur][*ptr];
	}
	output[cur].pb(id);
	I[id] = string(P);
}

void BuildFailureFunction(){
	queue<int> q; 	
	fail[0] = 0;
	for(auto & e : children[0]) {
		fail[e.yy] = 0;
		q.push(e.yy);
	}
	while(!q.empty()){
		int p = q.front(); q.pop();
		for(auto & e : children[p]){
			char c = e.xx;
			int u = e.yy,v = fail[p];
			while(!trie[v][c] && v) v = fail[v];
			fail[u] = v = trie[v][c];
			for(int x : output[v])
				output[u].pb(x);
			sort(all(output[u]));
			output[u].resize(unique(all(output[u])) - output[u].begin());
			q.push(u);
		}
	}
}

void match(const char *T){
	int cur = 0;
	//string aux;
	for(const char *ptr = T;*ptr;ptr++){
	//	aux += *ptr;
		while(!trie[cur][*ptr] && cur) cur = fail[cur];
		cur = trie[cur][*ptr];
		if(!output[cur].empty()){
		//	cerr << "till " << aux <<  " matching : ";
			for(int id : output[cur]){
		//		cerr << I[id] << " ";
				yes[id] = 1;
			}
		//	cerr << endl;
		}
	}
}


int main(){
	scanf("%s",T);
	int n; scanf("%d",&n);
	loop(i,n){
		scanf("%s",buffer);
		insert(buffer,i);
	}
	match(T);
	loop(i,n) printf("%c\n",yes[i] ? 'Y' : 'N');	
	return 0;
}
