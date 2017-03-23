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

ll ccw(pi O,pi A,pi B){
	return (A.yy *1LL* B.xx *1LL* O.xx *1LL* O.yy - A.yy *1LL* O.xx *1LL* B.xx *1LL* B.yy - O.yy *1LL* B.xx *1LL* A.xx *1LL* A.yy + A.xx *1LL* B.xx *1LL* A.yy *1LL* B.yy) - 
		(A.xx *1LL* B.yy *1LL* O.xx *1LL* O.yy - A.xx *1LL* O.yy *1LL* B.xx *1LL* B.yy - O.xx *1LL* B.yy *1LL* A.xx *1LL* A.yy + A.xx *1LL* B.xx *1LL* A.yy *1LL* B.yy);
}

pi P[1 << 20];
int n;
int ord[1 << 20];
map<pi,vi> M;

int main(){
	scanf("%d",&n);
	loop(i,n) {
		scanf("%d %d",&P[i].xx,&P[i].yy);
		M[P[i]].pb(i+1);
	}
	n = 0;
	for(auto p : M)
		P[n++] = p.xx;
	loop(i,n) ord[i] = i;
	sort(ord,ord + n,[](const int & a,const int & b){
		return P[b] < P[a];
	});
	deque<int> CH;
	int k = 0;
	for(int i = n-1;i >= 0;i--){
		while(k > 1 && ccw(P[CH[k - 2]],P[CH[k - 1]],P[ord[i]]) > 0) {
			k--;
			CH.pop_back();
		} 
		CH.pb(ord[i]);
		k++;
	}
//	print(CH,int);		
	while(k > 1 && P[CH[k - 2]].xx == P[CH[k - 1]].xx && P[CH[k - 2]].xx < P[CH[k - 1]].xx) CH.pop_back(),k--;
	int mx = INT_MIN;
	for(int x : CH) mx = max(mx,P[x].yy);
	int e = 0;
	loop(i,sz(CH)) if(mx == P[CH[i]].yy) e = i;
	loop(i,e) CH.pop_front();	
	
	deque<int> out;
	for(int x : CH)
		for(int y : M[P[x]])
			out.pb(y);
	CH = out;
//	print(CH,int);		

	sort(all(CH));
	for(int x : CH) printf("%d ",x);
	puts("");
	return 0;
}
