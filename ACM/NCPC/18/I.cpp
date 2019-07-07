#ifdef ACTIVE
#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
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
using namespace std;

string names[1024],nums[1024],S;
char buffer[1024];
int n;

void read(string & s){
	scanf("%s",buffer);
	s = string(buffer);
}

void canonize(string & s,int len) {
	s = string(len - sz(s),'0') + s;
}

bool is_zero(){
	for(char c : S)
		if(c != '0')
			return 0;
	return 1;
}

string subtract(string a,string b) {
	string ret (sz(a),'0');
	int r = 0;
	for(int i = sz(a) - 1;i >= 0;i--) {
		int da = a[i] - '0',db = b[i] - '0';
		int res = da - db - r;
		r = 0;
		if(res < 0) {
			res += 10;
			r++;
		}
		ret[i] = res + '0';
	}
	assert(r == 0);
	return ret;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d",&n);
	read(S);
	loop(i,n){
		read(names[i]);
		read(nums[i]);
	}
	int len = sz(S);
	loop(i,n) len = max(len,sz(nums[i]));

	canonize(S,len);
	loop(i,n) canonize(nums[i],len);

	vi ord(n);
	loop(i,n) ord[i] = i;
	sort(all(ord),[](const int & a,const int & b){
		return nums[a] < nums[b];
	});
	vector<string> people;
	int end = sz(ord) - 1;
	while(!is_zero() && end >= 0) {
		if(nums[ord[0]] > S) break;
		int s = 0,e = end;
		while(s < e) {
			int mid = s + (e-s+1)/2;
			if(nums[ord[mid]] <= S) s = mid;
			else e = mid - 1;
		}
		S = subtract(S,nums[ord[s]]);
		people.push_back(names[ord[s]]);
		end = s-1;
	}
	if(!is_zero()) people.clear();
	printf("%d\n",sz(people));
	for(string name : people)
		printf("%s\n",name.c_str());
	return 0;
}
#endif
