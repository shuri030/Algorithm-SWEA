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

typedef struct ball {

    int x;
    int y;
    int dir;
    int score;

}ball;

typedef struct Worm {
    int x1 = 0, y1 = 0;
    int x2 = 0, y2 = 0;
}Worm;

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
int main()
{
    int tc;
    scanf("%d", &tc);

    for (int t = 1; t <= tc; t++) {
        vector<pair<int, int> > start;
        Worm worm[5];

        scanf("%d", &N);

        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                scanf("%d", &board[i][j]);

                if (board[i][j] == 0) { //시작할 수 있는 곳
                    start.push_back({ i,j });
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

        int sx, sy;
        ball b;
        queue<ball> q;
        int ball_x, ball_y, ball_dir, ball_score = 0;
        int nx, ny, wx, wy, wn;

        for (int i = 0; i < start.size(); i++) {
            sx = start[i].first; sy = start[i].second;

            //다음이 벽 아닌곳만 돌기
            for (int k = 0; k < 4; k++) {

                b.x = sx; b.y = sy;
                b.score = 0; b.dir = k;
                if (b.x + dx[b.dir] <= 0 || b.y + dy[b.dir] <= 0 || b.x + dx[b.dir] > N || b.y + dy[b.dir] > N) {
                    if (ans < b.dir) { ans = b.dir; }
                    continue;
                }

                q.push(b);

                while (!q.empty()) {
                    ball_x = q.front().x; ball_y = q.front().y;
                    ball_dir = q.front().dir; ball_score = q.front().score; //현재
                    q.pop();
                    nx = ball_x + dx[ball_dir]; ny = ball_y + dy[ball_dir]; //다음

                    //다음 가려던 곳이 시작점이면
                    if ((nx == sx) && (ny == sy)) {
                        if (ball_score > ans) {
                            ans = ball_score;
                        }
                        break;
                    }
                    //다음 가려던 곳이 블랙홀이면
                    else if (board[nx][ny] == -1) {
                        if (ball_score > ans) {
                            ans = ball_score;
                        }
                        break;
                    }
                    //다음 가려는 곳이 벽이면
                    else if (nx <= 0 || ny <= 0 || nx > N || ny > N) {
                        ball_dir = where_can_i_go(5, ball_dir);
                        ball_score++;
                        q.push({ nx, ny, ball_dir, ball_score });
                    }

                    //다음 가려던 곳이 블럭이면
                    else if (board[nx][ny] >= 1 && board[nx][ny] <= 5) {
                        ball_score++;
                        ball_dir = where_can_i_go(board[nx][ny], ball_dir);
                        q.push({ nx, ny, ball_dir, ball_score });
                    }

                    //다음 가려던 곳이 웜홀이면
                    else if (board[nx][ny] >= 6 && board[nx][ny] <= 10) {

                        wn = board[nx][ny] - 6;

                        if (worm[wn].x1 == nx && worm[wn].y1 == ny) {
                            nx = worm[wn].x2; ny = worm[wn].y2;
                        }
                        else {
                            nx = worm[wn].x1; ny = worm[wn].y1;
                        }

                        q.push({ nx, ny, ball_dir, ball_score });

                    }
                    //다음 가려던 곳이 빈 곳이면
                    else if (board[nx][ny] == 0) {
                        q.push({ nx, ny, ball_dir, ball_score });
                    }
                }

                while (!q.empty()) { q.pop(); }

            }


        }

        printf("#%d %d\n", t, ans);
        //초기화
        ans = -INT_MAX / 2;
        memset(board, 0, sizeof(board));

    }

    return 0;

}
