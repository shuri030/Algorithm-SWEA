#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <string.h>
#include <algorithm>
using namespace std;

typedef struct cell {
	int xx;
	int yy;
	int live_time;
	int dead_time;
	int state;

}cell;

int N, M, K;
int board[701][701]; // -1 : dead
int tmp[701][701];
bool isin[701][701]; // false : empty
queue<cell> q;
vector<pair<int, int> > sp;
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
int cnt = 0;

int main()
{
	int T;
	scanf("%d", &T);

	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d %d", &N, &M, &K);

		//input
		for (int i = 340; i <= 340 + N - 1; i++) {
			for (int j = 340; j <= 340 + M - 1; j++) {
				scanf("%d", &board[i][j]);

				if (board[i][j] != 0) {
					q.push({ i, j, board[i][j], board[i][j] + board[i][j], 2});
					isin[i][j] = true; //들어있다
					cnt++;
				}
			}
		}

		int len = q.size();
		int x, y, lt, dt, s, nx, ny;
		int flag = 0;

		//K초만큼
		for (int h = 0; h <= K; h++) {
			len = q.size();

			for (int j = 1; j <= len; j++) {
				x = q.front().xx; y = q.front().yy;
				lt = q.front().live_time; dt = q.front().dead_time;
				s = q.front().state;
				q.pop();

				if (s == -1) { continue; } //죽었으면 패스

				if (s == 2) { //비활인 아이들
					if (h == lt) {//활성화
						//딸깍
						q.push({ x, y, lt, dt, 1 });
					}
					else {
						q.push({ x, y, lt, dt, 2 });
					}

				}
				else if (s == 1 && h == lt + 1) { //활성화 & 번식할시간

					for (int k = 0; k < 4; k++) {
						nx = x + dx[k]; ny = y + dy[k];
						if (board[nx][ny] == 0 && isin[nx][ny] == false) {
							if (tmp[nx][ny] == 0) {
								sp.push_back({ nx, ny });
								tmp[nx][ny] = board[x][y];
							}
							else {
								tmp[nx][ny] = max(tmp[nx][ny], board[x][y]);
							}
							flag = 1;
						}
					}

				}
				if (s == 1 && h == dt) { //활성화 & 죽을 시간
					board[x][y] = -1;
					cnt--;
				}
				else if (s == 1 && h != dt) {
					q.push({ x, y, lt, dt, 1 });
				}

			}

			//한번에 옮기기
			if (flag != 0) {
				for (int i = 0; i < sp.size(); i++) {
					int ix = sp[i].first;
					int iy = sp[i].second;
					board[ix][iy] = tmp[ix][iy];
					isin[ix][iy] = true;
					q.push({ ix, iy, h + board[ix][iy], h + 2 * board[ix][iy], 2 });
					tmp[ix][iy] = 0;
					cnt++;
				}
			}
			sp.clear();
			flag = 0;
		}


		printf("#%d %d\n", tc, cnt);
		memset(board, 0, sizeof(board));
		memset(isin, 0, sizeof(isin));
		while (!q.empty()) { q.pop();  }
		cnt = 0;
	}

	return 0;

}
