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

const int MAX = 100'000 + 10;
int hate[2*MAX],W[2*MAX],id[2*MAX];
char buffer[MAX];
map<string,int> M;

int find(int u){
	return id[u] = (id[u] == u) ? u : find(id[u]);
}

int join(int a,int b){
	a = find(a),b = find(b);
	if(a == b) return a;
	if(W[a] < W[b]) swap(a,b);
	W[a] += W[b];
	id[b] = a;
	return a;
}



int read(){
	scanf("%s",buffer);
	string s = string(buffer);
	if(M.find(s) == M.end()) {
		int x = sz(M);
		M[s] = x;
	}
	return M[s];
}

int main(){
	int n,m,q;
	scanf("%d %d %d",&n,&m,&q);
	loop(i,n) read();
	loop(i,n) {
		hate[i] = i + n,id[i] = i,W[i] = 1;
		hate[i + n] = i;
		id[i + n] = i + n;
		W[i + n] = 1;
	}
	loop(i,m){
		int t,x,y;
		scanf("%d",&t);
		x = read();
		y = read();
		if(t == 1){
			if(find(hate[x]) == find(y)) puts("NO");
			else {
				join(x,y);
				join(hate[x],hate[y]);
				puts("YES");
			}
		}
		else{
			if(find(x) == find(y)) puts("NO");
			else{
				join(x,hate[y]);
				join(hate[x],y);
				puts("YES");
			}
		}
	}
	loop(i,q){
		int x = read(),y = read();
		if(find(x) == find(y)) puts("1");
		else if(find(x) == find(hate[y])) puts("2");
		else puts("3");
	}	
		
	return 0;
}
