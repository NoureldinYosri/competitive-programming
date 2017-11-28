int getMinCost(){
	int m = sz(V);
	T[m] = '$';
	loop(i,m) T[i + m + 1] = str[V[i]];
	loop(i,m) T[i + 2*m + 1] = str[V[i]];
	int M = 3*m + 1;
	T[M] = 0;
	//cerr << T << endl;
	fill(fail,fail + M,0);
	for(int i = 1;i < M;i++){
		int l = fail[i-1];
		while(l && T[l] != T[i]) l = fail[l - 1];
		if(T[l] == T[i]) ++l;
		fail[i] = l;
	}
	//prArr(fail,M,int);
	for(int i = m+1;i < M;i++)
		if(fail[i] == m){
//			cerr << i << " " << i - 2*m << endl;
			return i - 2*m ;
		}
	assert(0);
	return -1;
}

int getMin(){
	int m = sz(V);
	loop(i,m) T[i] = str[V[i]];
	loop(i,m) T[i + m] = str[V[i]];
	m <<= 1;
	T[m] = 0;
	fill(fail,fail + m,-1);
	int k = 0;
	for(int j = 1;j < m;j++){
		char sj = T[j];
		int i = fail[j-k-1];
		while(i != -1 && sj != T[k+i+1]) {
			if(sj < T[k + i + 1])
				k = j-i+1;
			i = fail[i];
		}
		if(sj != T[k+i+1]) {
			if(sj < T[k])
				k = j;
			fail[j-k] = -1;
		}
		else fail[j-k] = i + 1;
	}
	m >>= 1;
	for(int i = 0;i < m;i++)
		T[i] = T[i + k];
	int ret = getMinCost();
	assert(ret <= k);
	k = 0;
	for(int x : V) str[x] = T[k++];
	return ret;
}
