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

map<int,int> f[128];
bool debug ;

void insert(char c,int pos,int cnt){
	if(cnt <= 0) return ;
	map<int,int> & M = f[c];
	if(debug) {
		for(auto p : M) prp(p);
		cerr << endl;
	}
	auto it = M.lower_bound(pos);
	if(it != M.end() && it->first == pos + cnt ) {
		cnt += it->second;
		M.erase(it);
		return insert(c,pos,cnt);
	}
	if(it != M.begin()){
		it--;
		if(it->first + it->second == pos) {
			pos = it->first;
			cnt += it->second;
			M.erase(it);
		}
	}
	M[pos] = cnt;
}

int get(char c,int l,int r){
	auto & M = f[c];
	auto it = M.upper_bound(l);
	if(it != M.end() && it->first <= r){
		int k = min(r - it->first + 1,it->second),q = it->second - k;
		M.erase(it);
		insert(c,r+1,q);
		return k + get(c,l,r);		
	}
	int ret = 0;
	if(it != M.begin()){
		it--;
		if(l < it->first + it->second){
			int k = min(r,it->first + it->second - 1) - l + 1,q = it->second,s = it->first;
			M.erase(it);
			insert(c,s,l - s);
			insert(c,r+1,q - (r - s + 1));
			ret = k;
		}
	}
	return ret;
}

char line[1 << 20];

void PRINT(){
	for(char c = 'a';c <= 'z';c++)
		for(auto p : f[c]){
			int pos = p.xx,len = p.second;
			loop(i,len) line[pos + i - 1] = c;
		}
//	cerr << line << endl;
}

int main(){
	int n,m; scanf("%d %d %s",&n,&m,line);	
	loop(i,n) insert(line[i],i + 1,1);

	loop(i,m){
		int l,r,k; scanf("%d %d %d",&l,&r,&k);
		int cnt[128] = {0};
		for(char c = 'a';c <= 'z';c++)
			cnt[c] = get(c,l,r);
		if(k == 1){
			for(char c = 'a';c <= 'z';c++){
				if(!cnt[c]) continue;
				insert(c,l,cnt[c]);
				l += cnt[c];
			}
		}
		else {
			for(char c = 'z';c >= 'a';c--){
				if(!cnt[c]) continue;
				insert(c,l,cnt[c]);
				l += cnt[c];
			}
		}
	}	
	PRINT();
	puts(line);

	return 0;
}
