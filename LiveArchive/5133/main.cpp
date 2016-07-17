#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
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
struct machine{
	ll DayAvail,BuyPrice,SellPrice,profit;
public:
	machine(){}
	machine(int a,int b,int c,int d):DayAvail(a),BuyPrice(b),SellPrice(c),profit(d){}
	bool operator < (const machine & o){
		return DayAvail < o.DayAvail;
	}
};

int N,C,D;
machine Machine[1 << 20];
set<pl> line;


double inter(pl A,pl B){
	return (B.yy - A.yy + 0.0)/(A.xx - B.xx);
}

void trim_front(ll a,ll b){
	while(1){
		auto u = line.upper_bound(mp(a,b));	
		if(u == line.end()) return;
		auto v = u; v++;
		if(v == line.end()) return;
		if(inter(mp(a,b),*u) <= inter(*u,*v)) return;
		line.erase(u);
	}
}

void trim_back(ll a,ll b){
	while(1){
		auto u = line.upper_bound(mp(a,b));	
		if(u == line.begin()) return;
		u--;
		auto v = u;
		if(v == line.begin()) return;
		--v;
		if(inter(*v,*u) <= inter(*u,mp(a,b))) return;
		line.erase(u);
	}
}

void insert(ll a,ll b){
	auto u = line.upper_bound(mp(a,b));
	if(u == line.end() || u == line.begin()){
		trim_front(a,b);
		trim_back(a,b);
		line.insert(mp(a,b));
	}
	auto v = u--; swap(u,v);
	if(inter(*u,mp(a,b)) <= inter(mp(a,b),*v)){
		trim_front(a,b);
		trim_back(a,b);
		line.insert(mp(a,b));
	}
}

ll f(ll x,pl A){
	return A.xx * x + A.yy;
}

ll get(int i){
	ll x = Machine[i].DayAvail;
	while(sz(line) > 1){
		auto v = line.begin();
		auto u = v++;
		if(f(x,*u) <= f(x,*v)) line.erase(u);
		else break;
	}
	return f(x,*line.begin());
}


ll solve(){
	line.clear(); line.insert(mp(0LL,C));
	Machine[N++] = machine(D + 1,0,0,0);
	sort(Machine,Machine + N);
	ll ans = 0;
	loop(i,N){
		/*
			argmax Machine[j]*profit * (Machine[i].DayAvail - Machine[j].DayAvail - 1) + Machine[j].SellPrice
					- Machine[j].BuyPrice
			Machine[j]*profit * Machine[i].DayAvail - Machine[j]*profit*(Machine[j].DayAvail + 1) + Machine[j].SellPrice
					- Machine[j].BuyPrice

			a = Machine[j]*profit
			b = - Machine[j]*profit*(Machine[j].DayAvail + 1) + Machine[j].SellPrice
					- Machine[j].BuyPrice + maximum_possible_balance
		*/
		ans = get(i);
		insert(Machine[i]*profit,-Machine[i]*profit*(Machine[i].DayAvail + 1LL)+Machine[i].SellPrice- Machine[i].BuyPrice + ans);
	}
	return ans;
}


int main(){

	return 0;
}
