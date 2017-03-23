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

int ctr[128],lst[128];
string s;
vi V;

int main(){
	cin >> s;
	int n = sz(s);
	loop(i,n){
		ctr[s[i]]++;
		lst[s[i]] = i;
	}
	range(i,'a','z') if(ctr[i] & 1) V.pb(lst[i]),ctr[i]--;
	if(sz(V) & 1) {
		ctr[s[V.back()]]++;	
		V.pop_back();
	}
	char to = 'z';
	for(int i : V) to = min(to,s[i]);
	if(!V.empty()) ctr[s[V.back()]] += sz(V);
	deque<char> dq;
	range(i,'a','z') if(ctr[i] & 1){
		assert(dq.empty());
		while(ctr[i]){
			dq.pb((char)i);
			ctr[i]--;
		}		
	}	
	range(i,'a','z') if(ctr[i]){
		int b = 1;
		assert(ctr[i]%2 == 0);
		while(ctr[i]){
			if(b) dq.pb((char)i);
			else dq.push_front(char(i));
			ctr[i]--;
			b ^= 1;
		}		
	}	
	for(char c : dq) putchar(c);
	puts("");
//	print(dq,char);	
	return 0;
}
