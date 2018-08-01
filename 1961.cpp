#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

int board[8][8];

int main()
{
	int t, N, c;
	int i1, i2, i3, j1, j2, j3;
	scanf("%d", &t);

	for(int tc = 1; tc <= t; tc++) {
		scanf("%d", &N);
		c = N;
		for(int i = 1; i <= N; i++) {
			for(int j = 1; j <= N; j++) {
				scanf("%d", &board[i][j]);
			}
		}
		i1 = N; j1 = 1;
		i2 = N; j2 = N;
		i3 = 1; j3 = N;

		printf("#%d\n", tc);
		while(c > 0) {
			
			for(int i = i1; i >= 1; i--) {
				printf("%d", board[i][j1]);
			}
		    printf(" "); j1++;

			for(int j = j2; j >= 1; j--) {
				printf("%d", board[i2][j]);
			}
			printf(" "); i2--;

			for(int i = i3; i <= N; i++) {
				printf("%d", board[i][j3]);
			}
			printf("\n"); j3--;

			c--;
		}

		memset(board, 0, sizeof(board));
	}

    return 0;
}