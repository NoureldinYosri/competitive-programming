#include <iostream>
#include <tr1/unordered_map>
const int MAXN = 100005;
int n, m, w[MAXN + 5], q, l, r;
std::tr1::unordered_map<int, int> phi;
 
int get_phi(int x) {
	std::tr1::unordered_map<int, int>::iterator it;
	it = phi.find(x);
	if(it != phi.end())
		return it->second;
	int res = 1;
	for(int i = 2; i*i <= x; ++i) {
		if(x%i == 0) {
			x /= i;
			while(x%i == 0) {
				x /= i;
				res *= i;
			}
			res *= i - 1;
		}
	}
	if(x > 1)
		res *= x - 1;
	return phi[x] = res;
}
 
int Power(int a, int b, int p) {
	long long base = a, res = 1;
	bool flag = false;
	while(b > 0) {
		if(b & 1) {
			if(res*base >= p)
				flag = true;
			res = res*base%p;
		}
		if(base*base >= p)
			flag = true;
		base = base*base%p;
		b >>= 1;
	}
	if(flag == true)
		res += p;
	return res;
}
 
int solve(int i, int p) {
	if(i == r + 1 || p == 1)
		return 1;
	return Power(w[i], solve(i + 1, get_phi(p)), p);
}
 
int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0), std::cout.tie(0);
	std::cin >> n >> m;
	for(int i = 1; i <= n; ++i)
		std::cin >> w[i];
	std::cin >> q;
	while(q--) {
		std::cin >> l >> r;
		std::cout << solve(l, m)%m << "\n";
	}
	return 0;
}
