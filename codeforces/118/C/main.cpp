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

int cnt[10];
char buffer[1 << 20];
int n,k;

int get_cost(int d,vi & aux){
	int need = max(0,k - cnt[d]),cost = 0;	
	int s = d - 1,e = d + 1;
	aux = vi(10,0);
	while(s >= 0 && e <= 9 && need){
		if(abs(s - d) < abs(e - d)){
			int diff = min(need,cnt[s]);
			cost += abs(s - d)*diff;
			need -= diff;
			aux[s] = diff;
			s--;
		}
		else{
			int diff = min(need,cnt[e]);
			cost += abs(e - d)*diff;
			need -= diff;
			aux[e] = diff;
			e++;
		}
	}
	while(s >= 0 && need){
		int diff = min(need,cnt[s]);
		cost += abs(s - d)*diff;
		need -= diff;
		aux[s] = diff;
		s--;
	}
	while(e <= 9 && need){
		int diff = min(need,cnt[e]);
		cost += abs(e - d)*diff;
		need -= diff;
		aux[e] = diff;
		e++;
	}
	if(need) return INT_MAX;
	return cost;
}

string build_string(int d,vi & aux){
	string ret = string(buffer);
	loop(i,n) if(ret[i] - '0' > d && aux[ret[i] - '0']) {
		aux[ret[i] - '0']--;
		ret[i] = d + '0';
	}
	loop(j,d) {
		for(int i = n-1;i >= 0 && aux[j];i--)
			if(ret[i] == j + '0')
				ret[i] = d + '0',aux[j]--;
	}
	return ret;
}

int main(){
	scanf("%d %d %s",&n,&k,buffer);
	loop(i,n) cnt[buffer[i] - '0']++;
	int ans = INT_MAX;
	
	loop(d,10){
		vi aux;
		ans = min(ans,get_cost(d,aux));
	}
	cout << ans << endl;
	vector<string> vs;
	loop(d,10){
		vi aux;
		if(get_cost(d,aux) == ans) vs.pb(build_string(d,aux));	
	}
	sort(all(vs));
	cout << vs[0] << endl;
	return 0;
}
