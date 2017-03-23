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

struct train{
	int from ,to;
	int start_time ,journey_time;
	int prob ,max_delay ;
};

const int MAX = 200;
map<string,int> M;
char buffer[100];
train Q[MAX];

int get(){
	int siz = sz(M);
	string s = string(buffer);
	if(M.find(s) == M.end()) M[s] = siz;
	return M[s];
}

int main(){
	int T; scanf("%d",&T);
	while(T--){
		M.clear();
		scanf("%s",buffer);
		int s = get();
		scanf("%s",buffer);
		int e = get();
		int n; scanf("%d",&n);
		loop(i,n){
			scanf("%s",buffer);
			int x = get();
			scanf("%s",buffer);
			int y = get();
			int m,t,p,d;
			scanf("%d %d %d %d",&m,&t,&p,&d);
			train & T = Q[i];
			T.from = x; T.to   = y;
			T.start_time = m; T.journey_time = t;
			T.prob = p; T.max_delay = d;
		}
	}	
	
	return 0;
}
