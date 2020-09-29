#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const ll inf = 0x3f3f3f3f3f3f3f3f;
const int mxn = 300001;
int n, m;
ll a[mxn], b[mxn], vl[mxn], vr[mxn], id[mxn];

struct segTree{
	int l, r;
	segTree *left, *right;
	ll sum, vmn, vmx, val;
	
	segTree(int a, int b){
		l = a, r = b;
		if(l != r){
			int mid = (l + r) / 2;
			left = new segTree(l, mid);
			right = new segTree(mid + 1, r);
			pull();
		}else{
			sum = 0;
			rset();
		}
	}
	
	void rset(){
		 vmn = inf, vmx = -inf, val = vmx - vmn;
	}
	
	void pull(){
		sum = left->sum + right->sum;
		vmn = min(left->vmn, left->sum + right->vmn);
		vmx = max(left->vmx, left->sum + right->vmx);
		val = max({left->val, right->val, left->sum + right->vmx - left->vmn});
	}
	
	void add(int x, int v){
		if(x < l || r < x) return;
		if(l == r){
			sum += v;
			if(!~v) rset();
			else vmn = sum - a[vl[x] - 1] - 1, vmx = sum - a[vr[x]], val = vmx - vmn;
			return;
		}
		left->add(x, v);
		right->add(x, v);
		pull();
	}
};

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 1; i <= m; i++){
		cin >> a[i];
		a[i] += a[i - 1];
	} 
	for(int i = 0; i < n; i++){
		cin >> vl[i] >> vr[i] >> b[i];
		id[i] = i;
	} 
	
	sort(id, id + n, [&](int x, int y){
			return b[x] > b[y];
	});
	
	ll ret = 0;
	segTree tre(0, n - 1);
	for(int i = 0; i < n; i++){
		tre.add(id[i], 1);
		if(tre.val <= 0) ret += b[id[i]];
		else tre.add(id[i], -1);
	}
	
	cout << ret << endl;

	return 0;
}