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

map<pi,int> cnt;

int main(){
	loop(i,4){
		int x1,y1,x2,y2; cin >> x1 >> y1 >> x2 >> y2;
		if(mp(x1,y1) == mp(x2,y2)) {
			puts("NO");
			return 0;
		}
		if(x1 != x2 && y1 != y2){
			puts("NO");
			return 0;
		}
		int h = y1 == y2;
		cnt[mp(x1,y1)] |= 1 << h;
		cnt[mp(x2,y2)] |= 1 << h;
	}
	if(sz(cnt) != 4){
		puts("NO");
		return 0;
	}
	for(auto p : cnt) if(p.yy != 3){
		puts("NO");
		return 0;
	}	
	puts("YES");
	
	return 0;
}
