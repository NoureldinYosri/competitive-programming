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

int X[1024],Y[1024],n;

bool isVertical(int i){
	return X[i] == X[i + 1];
}

bool intersect(int x,int y,int j){
	if(!isVertical(j)) return 0;
	if(2*X[j] < x) return 0;	
	int dy = Y[j + 1] - Y[j];
	if(dy > 0) return 2*Y[j] <= y && y < 2*Y[j + 1];
	else return 2*Y[j + 1] <= y && y < 2*Y[j];
}
int main(){
	cin >> n;
	loop(i,n+1) cin >> X[i] >> Y[i];
	int ans = 0;	
	loop(i,n) {
		int dx = X[i + 1] - X[i],dy = Y[i + 1] - Y[i];
		int g = __gcd(abs(dx),abs(dy));
		dx /= g,dy /= g;
		int x = 2*X[i + 1] + dx,y = 2*Y[i + 1] + dy,cnt = 0;
		loop(j,n) cnt += intersect(x,y,j);
		ans += cnt & 1;
	}
	cerr << ans << endl;
	cout << ans << endl;	
	
	return 0;
}
