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

const int MAX = 1 << 20;
int n,Q;
int ID[MAX],W[MAX];
int a,b;
multiset<int> diff,SZ;


int find(int u){
	return ID[u] = (u == ID[u]) ? u : find(ID[u]);
}

bool connected(int a,int b){return find(a) == find(b);}

int join(int a,int b){
	a = find(a),b = find(b);
	if(W[a] < W[b]) swap(a,b);
	ID[b] = a;
	return W[a] += W[b];
}

void remove_one(int w){
	cerr << "here " << w << endl;
	multiset<int>::iterator v = SZ.lower_bound(w);
	multiset<int>::iterator u = v,t = v; t++;
	cerr << 1 << endl;
	if(t != SZ.end()) diff.erase(diff.find(*t - *v));
	cerr << 2 << endl;	
	if(v != SZ.begin()){
		--u;
		diff.erase(diff.find(*v - *u));
		if(t != SZ.end()) diff.insert(*t - *v);
	}
	cerr << 3 << endl;
	SZ.erase(SZ.find(w));
}


void remove(int w1,int w2){
	if(w1 > w2) swap(w1,w2);
	cerr << w1 << " " << w2 << endl;
	multiset<int>::iterator v = SZ.upper_bound(w1); --v;
	multiset<int>::iterator u = v,t = v; ++t;
	if(w1 == w2 || *t == w2){
		diff.erase(diff.find(w2 - w1));
		if(w1 == w2){
			v = SZ.lower_bound(w1);
			u = t = v;
			t++;
		}
		++t;
		if(t != SZ.end()) diff.erase(diff.find(*t - w2));
		if(u != SZ.begin()){
			u--;
			diff.erase(diff.find(w1 - *u));
			if(t != diff.end()) diff.insert(*t - *u);
		}
		SZ.erase(SZ.find(w1));
		SZ.erase(SZ.find(w2));	
	}
	else remove_one(w1),remove_one(w2);
}

void insert(int w){
	SZ.insert(w);
	multiset<int>::iterator p = SZ.lower_bound(w);
	multiset<int>::iterator q = p;
	++q;
	if(q != SZ.end()) diff.insert(*q - w);
	if(p != SZ.begin()){
		--p;
		diff.insert(w - *p);
		if(q != SZ.end()) diff.erase(diff.find(*q - *p));
	}
}

int main(){
	scanf("%d %d",&n,&Q);
	loop(i,n + 1) W[i] = 1,ID[i] = i;
	loop(i,n) SZ.insert(1);
	loop(i,n - 1) diff.insert(0);
	while(Q--){
		print(SZ,int);
		print(diff,int);
		scanf("%d %d",&a,&b);
		if(connected(a,b)) {
			printf("%d\n",*diff.begin());
			continue;
		}
		int w1 = W[find(a)],w2 = W[find(b)],w3 = join(a,b);
		remove(w1,w2);
		insert(w3);
		printf("%d\n",*diff.begin());
	}		
	return 0;
}
