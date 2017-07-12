#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

const int MAXN = 10*1000,MAX = 1 << 24,num_bits = 24;
string str[MAXN];
int ans[MAX],n;
int f[MAX],g[MAX],psi[24][MAX >> 12];
unordered_map<int,int> lookup;

void read_input(){
	scanf("%d",&n);
	char buffer[5];
	loop(i,n) {
		scanf("%s",buffer);
		str[i] = string(buffer);
		sort(all(str[i]));
		str[i].resize(unique(all(str[i])) - str[i].begin());
	}
}
int brute_force(int msk){
	int ret = 0;
	for (int i = 0;i < n;i++) {
		int cur = 0;
		for (char c : str[i]) cur |= 1 << (c - 'a');
		if ((cur & msk) != 0)
			ret++;
	}
	return ret;
}
void count1(){
	for (int i = 0;i < n;i++){
		int first = -1,second = -1,third = -1;
		for (char c : str[i]) {
			int k = c - 'a';
			if (first == -1) first = k;
			else if(second == -1) second = k;
			else third = k;
		}
		if(first != -1) f[1 << first]++;
		if(second != -1) f[1 << second]++;
		if(third != -1) f[1 << third]++;
	}
	for (int msk = 0;msk < (1 << num_bits);msk++)
		for(int omsk = msk;omsk;omsk ^= LSOne(omsk))
			ans[msk] += f[LSOne(omsk)];
}

void count2(){
	memset(f,0,sizeof f);
	for (int i = 0;i < n;i++){
		int first = -1,second = -1,third = -1;
		for (char c : str[i]) {
			int k = c - 'a';
			if (first == -1) first = k;
			else if(second == -1) second = k;
			else third = k;
		}
		if(second != -1) f[(1 << first) | (1 << second)]++;
		if(third != -1) {
			f[(1 << first) | (1 << third)]++;
			f[(1 << second) | (1 << third)]++;
		}
	}

	for(int right = 0;right < (1 << 12);right++) {
		int msk = right;
		for(int msk1 = msk;msk1;msk1 ^= LSOne(msk1))
			for(int msk2 = msk1 ^ LSOne(msk1);msk2;msk2 ^= LSOne(msk2))
				g[msk] += f[LSOne(msk1) | LSOne(msk2)];
	}
	for(int left = 0;left < (1 << 12);left++) {
		int msk = left << 12;
		for(int msk1 = msk;msk1;msk1 ^= LSOne(msk1))
			for(int msk2 = msk1 ^ LSOne(msk1);msk2;msk2 ^= LSOne(msk2))
				g[msk] += f[LSOne(msk1) | LSOne(msk2)];
	}


	for (int msk = 0;msk < (1 << num_bits);msk++){
		int left = msk & 0xFFF000,right = msk & 0xFFF;
		ans[msk] -= g[left];
		ans[msk] -= g[right];
		for(int lm = left;lm;lm ^= LSOne(lm))
			for(int rm = right;rm;rm ^= LSOne(rm))
				ans[msk] -= f[LSOne(lm) | LSOne(rm)];
	}
}

void count3(){
	memset(f,0,sizeof f);
	memset(g,0,sizeof g);
	for (int i = 0;i < n;i++){
		int first = -1,second = -1,third = -1;
		for (char c : str[i]) {
			int k = c - 'a';
			if (first == -1) first = k;
			else if(second == -1) second = k;
			else third = k;
		}
		if(third != -1) f[(1 << first) | (1 << second) | (1 << third)]++;
	}
	for(int right = 0;right < (1 << 12);right++) {
		int msk = right;
		for(int msk1 = msk;msk1;msk1 ^= LSOne(msk1))
			for(int msk2 = msk1 ^ LSOne(msk1);msk2;msk2 ^= LSOne(msk2))
				for(int msk3 = msk2 ^ LSOne(msk2);msk3;msk3 ^= LSOne(msk3))
					g[msk] += f[LSOne(msk1) | LSOne(msk2) | LSOne(msk3)];
	}
	for(int left = 0;left < (1 << 12);left++) {
		int msk = left << 12;
		for(int msk1 = msk;msk1;msk1 ^= LSOne(msk1))
			for(int msk2 = msk1 ^ LSOne(msk1);msk2;msk2 ^= LSOne(msk2))
				for(int msk3 = msk2 ^ LSOne(msk2);msk3;msk3 ^= LSOne(msk3))
					g[msk] += f[LSOne(msk1) | LSOne(msk2) | LSOne(msk3)];
	}

	for(int right = 0;right < (1 << 12);right++) {
		int msk = right;
		for(int msk1 = msk;msk1;msk1 ^= LSOne(msk1))
			for(int msk2 = msk1 ^ LSOne(msk1);msk2;msk2 ^= LSOne(msk2))
				for(int left = 12;left < 24;left++)
					psi[left][right] += f[LSOne(msk1) | LSOne(msk2) | (1 << left)];
	}
	for(int left = 0;left < (1 << 12);left++) {
		int msk = left << 12;
		for(int msk1 = msk;msk1;msk1 ^= LSOne(msk1))
			for(int msk2 = msk1 ^ LSOne(msk1);msk2;msk2 ^= LSOne(msk2))
				for(int right = 0;right < 12;right++)
					psi[right][left] += f[LSOne(msk1) | LSOne(msk2) | (1 << right)];
	}

	for (int msk = 0;msk < (1 << num_bits);msk++){
		int left = msk & 0xFFF000,right = msk & 0xFFF;
		ans[msk] += g[left];
		ans[msk] += g[right];
		for(int r = right;r;r ^= LSOne(r))
			ans[msk] += psi[lookup[LSOne(r)]][left >> 12];
		for(int l = left;l;l ^= LSOne(l))
			ans[msk] += psi[lookup[LSOne(l)]][right];
	}

}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	loop(i,24) lookup[1 << i] = i;
	read_input();
	count1();
	count2();
	count3();
	//prArr(ans,(1 << num_bits),int);
	int out = 0;
	/*loop(msk,(1 << 24)) {
		int a = ans[msk],b = brute_force(msk);
		if(a != b) {
			cerr << "failed on " << msk << " expected " << b << " found " << a << endl;
			return 0;
		}
	}*/
	//prArr(ans,(1 << 4),int);
	loop(msk,(1 << 24)) out ^= ans[msk]*ans[msk];
	cout << out << endl;
	return 0;
}
