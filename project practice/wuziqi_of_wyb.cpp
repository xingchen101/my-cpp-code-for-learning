#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

const int qipan_size = 15;
const char kong = '.';
const char player1 = 'O';
const char player2 = 'X';

class wuziqi {
private:
	vector<vector<char>> board;
	char currentplayer;
	bool gameover = false;
	//得分系统
	int score1;
	int score2;

	//初始化棋盘
	void initboard() {
		board = vector<vector<char>>(qipan_size, vector<char>(qipan_size, kong));

		score1 = 0; score2 = 0;
		currentplayer = player1;
	}

	//打印棋盘
	void printboard() {
		cout << "  ";
		//列数
		for (int i = 0; i < qipan_size; i++)
		{
			if (i < 10) cout << " " << i << " ";
			else cout << i << " ";
		}
		cout << endl;
		for (int i = 0; i < qipan_size; i++)
		{
			if (i < 10) cout << " " << i;
			else cout << i;
			for (int j = 0; j < qipan_size; j++)
			{
				cout << " " << board[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl ;
	}
	//落子
	bool luozi(int row, int col) {
		if (row < 0 || row >= qipan_size || col < 0 || col >= qipan_size||board[row][col]!=kong) return false;
		board[row][col] = currentplayer;
		return true;
	}
	//切换玩家
	void switchplayer() {
		currentplayer = (currentplayer == player1 ? player2 : player1);
	}
	//判断胜利
	bool victory(int row, int col) {
		int ans;
		//方向向量
		int dx[] = { 1, 0, 1, 1 };
		int dy[] = { 0, 1, 1, -1 };

		char current = board[row][col];

		for (int i = 0; i < 4; i++)
		{
			ans = 1;
			//正方向
			int x = row + dx[i];
			int y = col + dy[i];

			while (x >= 0 && x < qipan_size && y >= 0 && y < qipan_size && board[x][y] == current) {
				ans++;
				x += dx[i];
				y += dy[i];
			}

			//反方向
			x = row - dx[i];
			y = col - dy[i];

			while (x >= 0 && x < qipan_size && y >= 0 && y < qipan_size && board[x][y] == current) {
				ans++;
				x -= dx[i];
				y -= dy[i];
			}
			if (ans >= 5) {
				return true;
			}
		}
		return false;
	}
	// 清理输入缓冲区
	void clearInputBuffer() {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

public:
	wuziqi() {
		initboard();
	}
	//当前比分
	void currentscore() {
		cout << "得分（player1:player2)" << score1 << ':' << score2 << endl;
	}

	//开始游戏
	void startgame() {
		cout << "oi 欢迎来到五子棋游戏" << endl;
		cout << "player1：O" << endl;
		cout << "player2：X" << endl;
		cout << "player1先开始哦" << endl;
		cout << "===================" << endl;

		printboard();

		int row, col;
		while (!gameover) {
			cout << "当前为玩家：" << currentplayer << endl;
			cin >> row >> col;
			if (!luozi(row, col)) {
				cout << "您的棋子已被创飞！" << endl;
				cout << "再来一次" << endl;
				continue;
			}

			printboard();

			//检查是否胜利
			if (victory(row, col)) {
				gameover = true;
				cout << "玩家"<< currentplayer<<"获胜" << endl;
				cout << "我们赢,你们输，我们要赢得金杯，你们空手而归" << endl;

				//得分系统
				if (currentplayer == player1)score1++;
				else score2++;
				currentscore();
				break;
			}
			switchplayer();
		}
	}
};
int main()
{
	wuziqi game;
	char again;
	do {
		game.startgame();
		cout << "再来一局吗？再来一局拉爆对面！" << endl;
		cout << "输入（y/n)" << endl;
		cin >> again;
	} while (again == 'y' || again == 'Y');

	cout << "拜拜了您嘞" << endl;
	return 0;
}