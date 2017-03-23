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

ll w,m;
ll val[1 << 20];
ll LIM = 1e18;
ll val2[1 << 20];

int main(){
	cin >> w >> m;
	vl pows{1};
	loop(i,100){
		if(pows.back() <= LIM/w) pows.pb(pows.back()*w);
		else break;
	}

	int n = min(20,sz(pows));
	loop(msk,1 << n1){
		ll sum = 0;
		loop(i,n1) if(msk & (1 << i)) {
			if(sum > LIM - pows[i]) break;		
			sum += pows[i];	
		}
		if(sum == LIM) continue;		
		val[idx++] = sum;
	}
	sort(val,val + idx);
	prArr(val,idx,ll);
	loop(i,idx){
		if(binary_search(val + i + 1,val + idx,m + val[i])){
			puts("YES");
			return 0;
		}
	}
	int idx2 = 0;
	loop(msk,1 << n2){
		ll sum = 0;
		loop(i,n2) if(msk & (1 << i)) {
			if(sum > LIM - pows[i + n1]) break;		
			sum += pows[i + n1];	
		}
		if(sum == LIM) continue;
		if(sum == m){
			puts("YES");
			return 0;
		}
		if(binary_search(val,val + idx,sum + m) || binary_search(val,val + idx,sum - m)){
			puts("YES");
			return 0;
		}
		val2[idx2++] = sum;
	}
	sort(val2,val2 + idx2);
	prArr(val2,idx2,ll);
	loop(i,idx2){
		if(binary_search(val2 + i + 1,val2 + idx2,m + val2[i])){
			puts("YES");
			return 0;
		}
	}

	puts("NO");
	
	return 0;
}
