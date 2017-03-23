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

char line[1 << 20];
int L ;
int cnt[10];
int get_r(int s,int l){
	if(line[s] == '0') return 7;
	int r = 0;
	loop(i,l) r = (r*10 + line[s + i] - '0')%7;
	return r;
}

int work(){
	int r = get_r(0,L-10);
	loop(i,10) r = (r*10)%7;
	r = 7 - r; r %= 7;
	int s = L - 10;
	sort(line + s,line + L);
	do{
		if(get_r(s,10) == r) {
			cout << line << endl;
			return 1;
		}
	}while(next_permutation(line + s,line + L));
	return 0;
}

void solve(){
	loop(i,L) cnt[line[i]-'0']++;
	loop(i,L) {
		if(line[i] != '0'){
			swap(line[i],line[0]);
			if(work()) return;
			swap(line[i],line[0]);
		}
	}
	cout << 0 << endl;
}


int main(){
	cin >> line;
	L = strlen(line);
	if(L <= 10) {
		sort(line,line + L);
		do{
			if(get_r(0,L) == 0) {
				cout << line << endl;
				return 0;
			}
		}while(next_permutation(line,line + L));
		cout << 0 << endl;
	}
	else{
		loop(i,L) cnt[line[i]-'0']++;
		int s = 0;
		for(int i = 9;i >= 0;i--)
			while(cnt[i] > 1){
				line[s++] = i + '0';
				cnt[i]--;
			}
		int t = s;
		for(int i = 9;i >= 0;i--)
			while(cnt[i]){
				line[s++] = i + '0';
				cnt[i]--;
			}
		if(line[0] == '0'){
			solve();
			return 0;
		}
		s = t;
		if(!work()) cout << 0 << endl;
	}	
	
	
	return 0;
}
