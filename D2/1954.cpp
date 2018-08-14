#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;
int N;
int board[103][103];
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

void draw(int x, int y)
{
	int n = 1, d = 0, xx, yy;
	int m_cnt = 1;
	board[x][y] = n++;

	while(m_cnt < N * N) {
		xx = x + dx[d]; 
		yy = y + dy[d];
		if((xx < 1) || (yy < 1) || (xx > N) || (yy > N) || (board[xx][yy] != 0)) {
			d++;
			if(d == 4) { d = 0; }
			x = x + dx[d]; 
			y = y + dy[d]; //제자리로
		}
		else {
			x = x + dx[d]; 
			y = y + dy[d]; //그 방향으로
		}
		m_cnt++;
		board[x][y] = n++;
	}
}
void show()
{
	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= N; j++) {
			printf("%d ", board[i][j]);
		}
		printf("\n");
	}
}
int main()
{	
	int t;
	scanf("%d", &t);
	
	for(int tc = 1; tc <= t; tc++) {
		scanf("%d", &N);
		draw(1, 1);
		printf("#%d\n", tc);
		show();
		memset(board, 0, sizeof(board));
	}

    return 0;
}