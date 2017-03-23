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

int USB_cnt,PS_cnt,USB_PS,m;
vl USB,PS;

int main(){
	scanf("%d %d %d %d",&USB_cnt,&PS_cnt,&USB_PS,&m);
	loop(i,m){
		int p; char buffer[20];
		scanf("%d %s",&p,buffer);
		if(buffer[0] == 'U') USB.pb(p);
		else PS.pb(p);
	}
	sort(all(USB));
	sort(all(PS));
	ll lst = 0;
	for(ll & x : USB) lst = x = x + lst;	
	lst = 0;
	for(ll & x : PS) lst = x = x + lst;	
	int tot = 0; ll ans = LLONG_MAX;
	loop(i,USB_cnt + USB_PS + 1){
		if(i > sz(USB)) break;
		int j = PS_cnt + USB_PS - max(0,i - USB_cnt);
		j = min(j,sz(PS));
		ll price = (i ? USB[i - 1] : 0) + (j ? PS[j - 1] : 0);
		if(i + j > tot) ans = price,tot = i + j;
		else if(i + j == tot) ans = min(ans,price);
	}
	loop(j,PS_cnt + USB_PS + 1){
		if(j > sz(PS)) break;
		int i = USB_cnt + USB_PS - max(0,j - PS_cnt);
		i = min(i,sz(USB));
		ll price = (i ? USB[i - 1] : 0) + (j ? PS[j - 1] : 0);
		if(i + j > tot) ans = price,tot = i + j;
		else if(i + j == tot) ans = min(ans,price);		
	}
	cerr << tot << " " << ans << endl;
	cout << tot << " " << ans << endl;
	return 0;
}
