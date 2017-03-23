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

int A[3000],n;
int F[3000],m,S[3000*3000],M;
int frq[3000];
ll cnt_pair[3000];
ll cnt[3000*3000];

ll C(ll n,int k){
	if(k == 2) return n * (n - 1)/2;
	else if(k == 3) return n*(n - 1)*(n - 2)/6;
	else return n*(n - 1)*(n - 2)*(n - 3)/24;
}

ll solve1(){
	ll type1 = 0,type2 = 0,type3 = 0,type4 = 0;
	loop(i,m) {
		int k = 0;	
		loop(j,i){
			int sum = F[i] + F[j];
			while(k != m && F[k] < sum) k++;
			if(k != m && F[k] == sum) {
				int idx = k;
				type2 += C(frq[i],2) * C(frq[j],2) * C(frq[idx],2) ;
				type4 += C(frq[idx],2) * cnt_pair[idx] * frq[i] * frq[j];
				cnt_pair[idx] += frq[i] * frq[j];		
			}
		}
	}
	loop(i,m) loop(j,i) if(F[i] == 2*F[j]){
		//cerr << F[j] << " " << F[i] << endl;	
		type1 += C(frq[i],2) * C(frq[j],4);
		type3 += C(frq[i],2) * C(frq[j],2) * cnt_pair[i]; 
	}
	//cerr << type1 << " " << type2 << " " << type3 << " " << type4 << endl;
	return type1 + type2 + type3 + type4;
}

void compress(){
	loop(i,m) loop(j,i) S[M++] = F[i] + F[j];
	sort(S,S + M);
	M = unique(S,S + M) - S;
}

ll solve2(){
	compress();
	ll type1 = 0,type2 = 0,type3 = 0;
	loop(i,m) {		
		loop(j,i) {
			int sum = F[i] + F[j];
			int k = lower_bound(S,S + M,sum) - S;
			cnt[k] += frq[i] * frq[j];
		}
	}
	loop(i,m) {
		int k = i-1,k2 = i-1;
		loop(j,i) {
			if(F[i]%F[j] == 0 && F[i]/F[j] == 3) type1 += C(frq[j],3)*C(frq[i],3);
			if(3*F[j] != F[i] && binary_search(F,F + m,F[i] - 2*F[j])){
				while(k2 >= 0 && F[k2] + 2*F[j] > F[i]) k2--;
				if(k2 >= 0 && F[k2] + 2*F[j] == F[i]) type2 += frq[k2] * C(frq[j],2) * C(frq[i],3);
			}
			int sum = F[i] - F[j];		
			if(!binary_search(S,S + M,sum)) continue;
			ll tmp = cnt[lower_bound(S,S + M,sum) - S];
			while(k >= 0 && F[k] + F[j] > sum) k--;	
			if(k >= 0 && k != j && F[k] + F[j] == sum) tmp -= frq[j] * frq[k];
			//cerr << F[i] << " " << A[j] << " " << sum << " " << tmp << " " << frq[j] << endl;
			type3 += tmp * C(frq[i],3) * frq[j];
		}
	}
	type3 /= 3;
	//cerr << type1 << " " << type2 << " " << type3 << endl;
	return type1 + type2 + type3;
}


int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i),F[i] = A[i];
	sort(F,F + n);
	m = unique(F,F + n) - F;
	loop(i,n) frq[lower_bound(F,F + m,A[i]) - F]++;
	
	ll ans = 0,x,y;
	
//	cerr << "1 1 2 2 -> " << (x = solve1()) << endl;
//	cerr << "1 1 1 3 -> " << (y = solve2()) << endl;
//	ans = x + y;
	ans = solve1();
	ans += solve2();
	cout << ans << endl;	
	
	return 0;
}
