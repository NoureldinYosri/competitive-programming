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

int main(){
	int T; scanf("%d",&T);
	range(t,1,T){
		queue<int> atA,atB;
		queue<int> A,B;
		int turn,NA,NB; scanf("%d %d %d",&turn,&NA,&NB);
		loop(i,NA){
			int h,m; scanf("%d:%d",&h,&m);
			A.push(h*60 + m);
		}
		loop(i,NB){
			int h,m; scanf("%d:%d",&h,&m);
			B.push(h*60 + m);
		}
		while(!A.empty() || !B.empty()){
			int t;
			if(A.empty()) t = B.front(),B.pop();
			else if(B.empty()) t = A.front(),A.pop();
			else if(A.front() > B.front()) t = B.front(),B.pop();
			else t = A.front(),A.pop();
			int x = atA.empty() ? 3600 : atA.front(),y = atB.empty() ? 3600 : atB.front();
			
		}
		printf("%d\n",atA.size() + atB.size());
	}
	
	return 0;
}
