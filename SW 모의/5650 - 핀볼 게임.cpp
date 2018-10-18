#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <algorithm>
using namespace std;

int N, M;
int board[103][103];
int dx[4] = { -1, 0, 1, 0 };//상 우 하 좌
int dy[4] = { 0, 1, 0, -1 };
int ans = -INT_MAX / 2;
int sx, sy;

typedef struct Worm {
	int x1 = 0, y1 = 0;
	int x2 = 0, y2 = 0;
}Worm;
Worm worm[5];

int where_can_i_go(int block_num, int cur_dir)
{
	if (block_num == 1) {
		if (cur_dir == 0) { return 2; }//상 - 하
		else if (cur_dir == 1) { return 3;} //우 - 좌
		else if (cur_dir == 2) { return 1;} //하 - 우
		else if (cur_dir == 3) { return 0;} //좌 - 상
	}
	else if (block_num == 2) {
		if (cur_dir == 0) { return 1; } // 상 - 우
		else if (cur_dir == 1) { return 3; } //우 - 좌
		else if (cur_dir == 2) { return 0; } //하 - 상
		else if (cur_dir == 3) { return 2; } // 좌 - 하
	}
	else if (block_num == 3) {
		if (cur_dir == 0) { return 3; } // 상 - 좌
		else if (cur_dir == 1) { return 2; } //우 - 하
		else if (cur_dir == 2) { return 0; } //하 - 상
		else if (cur_dir == 3) { return 1; } // 좌 - 우

	}
	else if (block_num == 4) {
		if (cur_dir == 0) { return 2; } // 상 - 하
		else if (cur_dir == 1) { return 0; } //우 - 상
		else if (cur_dir == 2) { return 3; } //하 - 좌
		else if (cur_dir == 3) { return 1; } //좌 -우
	}
	else if (block_num == 5) {
		if (cur_dir == 0) { return 2; } // 상 - 하
		else if (cur_dir == 1) { return 3; } //우 - 좌
		else if (cur_dir == 2) { return 0; } //하 - 상
		else if (cur_dir == 3) { return 1; } //좌 - 우

	}

}
int go(int x, int y, int dir)
{
	int nx, ny, n_dir = dir;
	int score = 0;
	int cx, cy;

	cx = x;
	cy = y;

	//다음에 올 것이..
	while (1) {
		nx = cx + dx[n_dir]; ny = cy + dy[n_dir];
		//시작점일때
		if ((nx == sx) && (ny == sy)) {
			return score;
		}

		//블랙홀일때
		else if (board[nx][ny] == -1) {
			return score;
		}

		//벽 일때
		else if (nx <= 0 || ny <= 0 || nx > N || ny > N) {
			n_dir = where_can_i_go(5, n_dir);
			score++;
		}

		//블록일때
		else if (board[nx][ny] >= 1 && board[nx][ny] <= 5) {
			n_dir = where_can_i_go(board[nx][ny], n_dir);
			score++;
		}

		//웜홀일때
		else if (board[nx][ny] >= 6 && board[nx][ny] <= 10) {

			int wn = board[nx][ny] - 6;

			if (!(worm[wn].x1 == nx && worm[wn].y1 == ny)) {
				cx = worm[wn].x1; cy = worm[wn].y1;
			}
			else {
				cx = worm[wn].x2; cy = worm[wn].y2;
			}
			continue;
		}
		cx = nx; cy = ny;
	}

	return score;
}
int main()
{
	int tc;
	scanf("%d", &tc);

	for (int t = 1; t <= tc; t++) {

		queue<pair<int, int> > start;

		scanf("%d", &N);

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				scanf("%d", &board[i][j]);

				if (board[i][j] == 0) { //시작할 수 있는 곳
					start.push({ i,j });
				}
				else if (board[i][j] >= 6 && board[i][j] <= 10) { //웜홀
					if (worm[board[i][j] - 6].x1 == 0 && worm[board[i][j] - 6].y1 == 0) {
						worm[board[i][j] - 6].x1 = i;
						worm[board[i][j] - 6].y1 = j;
					}
					else {
						worm[board[i][j] - 6].x2 = i;
						worm[board[i][j] - 6].y2 = j;
					}
				}
			}
		}

		int xx, yy, s = 0;

		while (!start.empty()) {
			xx = start.front().first; yy = start.front().second; start.pop();
			sx = xx; sy = yy;

			for (int k = 0; k < 4; k++) {
				s = go(xx, yy, k);
				if (ans < s) { ans = s; }
			}

		}

		printf("#%d %d\n", t, ans);
		//초기화
		ans = -INT_MAX / 2;
		memset(board, 0, sizeof(board));
		for (int i = 0; i < 5; i++) {
			worm[i].x1 = worm[i].x2 = worm[i].y1 = worm[i].y2 = 0;
		}

	}

	return 0;

}
