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

map<string,int> M;
int n,k,cnt,mx;
set<string> cont[1 << 20];
char buffer[10];
deque<string> dq;
multiset<int> MS;

void pop(){
	string s = dq.front(); dq.pop_front();
	cont[M[s]].erase(s);
	MS.erase(MS.find(M[s]));
	M[s]--;
	if(M[s]) cont[M[s]].insert(s),MS.insert(M[s]);
}

void insert(){
	string s = string(buffer);
	dq.pb(s);
	if(M[s]) cont[M[s]].erase(s),MS.erase(MS.find(M[s]));
	M[s]++;
	cont[M[s]].insert(s);
	MS.insert(M[s]);
}

int main(){
	int T; scanf("%d",&T);
	range(t,1,T){
		scanf("%d %d",&n,&k);
		loop(i,n + 1) cont[i].clear();
		M.clear(),MS.clear(),dq.clear(); mx = cnt = 0;
		printf("Case %d:\n",t);
		loop(i,n){
			if(dq.size() == k) pop();
			scanf("%s",buffer);
			insert();			
			printf("%s %d\n",cont[*MS.rbegin()].begin()->c_str(),*MS.rbegin());
		}
	}	
	return 0;
}
