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

const int MAX = 50 * 1000 + 1;
int X[MAX],Y[MAX],n;
map<pi,int> lst_h,lst_v;
ll black = 0,white = 0;	

void solve(int w,int h,int first_cell_black){
	cerr << w << " " << h << endl;
	ll x = w*1LL*h;
	ll y = x >> 1; x -= y;
	if(first_cell_black) swap(x,y);
	black += x;
	white += y;
}

int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%d %d",X + i,Y + i);
	loop(i,n){
		int j = i + 1; j = (j == n) ? 0 : j;
		if(X[i] == X[j]){
			if(lst_v.find(mp(X[j],X[i])) != lst_v.end()){
				int L = abs(lst_v[mp(X[j],X[i])] - Y[i]);
				solve(L,abs(Y[j] - Y[i]),(X[j] & 1) ^ (Y[j] & 1) ^ 1);
				lst_h.erase(mp(X[j],X[i]));
			}
			else lst_v[mp(X[i],X[j])] = Y[j];
		}
		else{
			if(lst_h.find(mp(Y[j],Y[i])) != lst_h.end()){
				int L = abs(lst_h[mp(Y[j],Y[i])] - X[i]);
				solve(L,abs(X[j] - X[i]),(X[j] & 1) ^ (Y[j] & 1));
				lst_h.erase(mp(Y[j],Y[i]));
			}
			else lst_h[mp(Y[i],Y[j])] = X[j];
		}
	}
	cout << black << " " << white << endl;
	cerr << black << " " << white << endl;
	
	return 0;
}
