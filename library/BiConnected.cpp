void dfsBi(int u,int p,int dfs_root) {
	dfs_low[u] = dfs_num[u] = dfs_time++;
	int t = 0;
	for(int v : G[u]){
		if (dfs_num[v] == -1) {
			if (u == dfs_root) t++;
			dfsBi(v,u,dfs_root);
			if (u != dfs_root && dfs_low[v] >= dfs_num[u])
				articulation_vertex[u] = 1;
			if (dfs_low[v] > dfs_num[u])
				printf(" Edge (%d, %d) is a bridge\n", u, v);
			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
		}
		else if (v != p)
			dfs_low[u] = min(dfs_low[u], dfs_num[v]);
	}
	if(u == dfs_root && t > 1) articulation_vertex[u] = 1;
}

void init(){
	memset(dfs_num,-1,sizeof dfs_num);
	dfs_time = 0;
}
