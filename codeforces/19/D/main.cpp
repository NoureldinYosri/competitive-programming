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

const int MAX = 200*1000 + 10;
int n,m;
int X[MAX],Y[MAX],aux[MAX];
string com[MAX];
char buffer[20];

int ST[MAX*4];
multiset<int> MS[MAX];

void update(int node,int s,int e,int pos,int val,int op) {
	if(s == e) {
		if(op) MS[s].insert(val);
		else MS[s].erase(MS[s].find(val));
		if(MS[s].empty()) ST[node] = 0;
		else ST[node] = *MS[s].rbegin();
		return;
	}
	int m = (s + e ) >> 1,left = node << 1,right = left | 1;
	if(pos <= m) update(left,s,m,pos,val,op);
	else update(right,m+1,e,pos,val,op);
	ST[node] = max(ST[left],ST[right]);
}

pi query(int node,int s,int e,int pos,int y) {
	if(ST[node] <= y) return mp(-1,-1);
	if(s == e){
		auto p = MS[s].upper_bound(y);
		if(p == MS[s].end()) return mp(-1,-1);
		else return mp(aux[s],*p);
	}
	int m = (s + e ) >> 1,left = node << 1,right = left | 1;
	if(m < pos) return query(right,m+1,e,pos,y);
	pi ret = query(left,s,m,pos,y);
	if(ret.xx == -1) ret = query(right,m+1,e,pos,y);
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(i,n) {
		scanf("%s %d %d",buffer,X + i,Y + i);
		com[i] = string(buffer);
		aux[i] = X[i];
	}
	sort(aux,aux + n);
	m = unique(aux,aux + n) - aux;
	loop(i,n) X[i] = lower_bound(aux,aux + m,X[i]) - aux;
	loop(i,n){
		char c = com[i][0];
		if(c == 'a') update(1,0,m-1,X[i],Y[i],1);
		else if(c == 'r') update(1,0,m-1,X[i],Y[i],0);
		else {
			pi ans = mp(-1,-1);
			if(X[i]+1 <= m-1) ans = query(1,0,m-1,X[i]+1,Y[i]);
			if(ans.xx == -1) puts("-1");
			else printf("%d %d\n",ans.xx,ans.yy);
		}
	}


	return 0;
}
