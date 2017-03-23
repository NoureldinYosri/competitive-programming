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

const int MAX = 500'010;
int LEN[MAX],END[MAX],n;
string I[MAX];
char buffer[MAX];
vi cut[MAX][26];
int trie[MAX][26];

void insert(char *p,int i){
	int cur = 0;
	static int siz = 0;
	for(;*p;p++){
		int z = 0;
		for(int c = *p - 'a' + 1;c < 26;c++)
			z |= trie[cur][c] != 0;
		if(z){
			for(int c = 0;c < 26;c++)
				if(trie[cur][c]){
				//	cerr << "erase " << cur << " " << char('a' + c) << " at " << i << endl;
					trie[cur][c] = 0;
					cut[cur][c].pb(i);
				}
		}
		if(!trie[cur][*p - 'a']) trie[cur][*p - 'a'] = ++siz;
		cur = trie[cur][*p - 'a'];
	}
	for(int c = 0;c < 26;c++)
		if(trie[cur][c]){
			trie[cur][c] = 0;
			cut[cur][c].pb(i);
		}	
}

void trace(const char *p,int t){
	int cur = 0;	
	for(;*p;p++){
		if(!trie[cur][*p - 'a']) break;
		vi & V = cut[cur][*p - 'a'];
		if(upper_bound(all(V),t) != V.end()) break;
		putchar(*p);
		cur = trie[cur][*p - 'a'];
	}
	puts("");
}

int main(){
	scanf("%d",&n);
	loop(i,n) {
		scanf("%s",buffer);
		I[i] = string(buffer + 1);
		char *p = buffer + 1;
		insert(p,i);
	}
	loop(i,n){
		putchar('#');
		trace(I[i].c_str() ,i);
	}
	
	return 0;
}
