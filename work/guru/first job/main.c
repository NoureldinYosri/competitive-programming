#include <stdio.h>
#include <string.h>
#define MAXM 20
#define MAXN 20

char G[MAXM][MAXN + 1];
int has_path_to_white[MAXM][MAXN + 1];
int has_path_to_black[MAXM][MAXN + 1];
int m,n;
int dx[] = {-1,0,1,0},dy[] = {0,-1,0,1};

void dfs(int x,int y,int has_path[MAXM][MAXN + 1]){
	if(has_path[x][y] != 0) return;	 // we already visited this cell
	has_path[x][y] = 1;  // mark cell(x,y) as visited
	int i;
	for(i = 0;i < 4;i++){
		int nx = x + dx[i],ny = y + dy[i];
		if(nx < 0 || nx >= m || ny < 0 || ny >= n) continue; // cell doesn't exist 
		if(G[nx][ny] != '.') continue;  // not an empty cell
		dfs(nx,ny,has_path);
	}
}

void solve(){
	// clear the arrays
	memset(has_path_to_white,0,sizeof has_path_to_white);
	memset(has_path_to_black,0,sizeof has_path_to_black);
	// interate over all cells and mark all cells with a path to a black or a white cell
	int i,j;	
	for(i = 0;i < m;i++)
		for(j = 0;j < n;j++)
			if(G[i][j] == 'B')
				dfs(i,j,has_path_to_black);
			else if(G[i][j] == 'W')
				dfs(i,j,has_path_to_white);
	// compute scores
	int white = 0,black = 0; // scores
	for(i = 0;i < m;i++)
		for(j = 0;j < n;j++){
			if(G[i][j] != '.') continue;
			// for a cell to belong to one of them it has to have a path to one and no path to the other
			if(has_path_to_white[i][j]==1 && has_path_to_black[i][j]==0) white++;
			if(has_path_to_white[i][j]==0 && has_path_to_black[i][j]==1) black++;	
		}
	// print scores
	printf("white score = %d ,black score = %d\n",white,black);
}

int main(){
	// read dimentions of the grid
	scanf("%d %d",&m,&n);	
	// read grid;
	int i;
	for(i = 0;i < m;i++)
		scanf("%s",G[i]);
	solve();
	return 0;
}
