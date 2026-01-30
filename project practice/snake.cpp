#include<iostream>
#include<vector>
#include<list>
#include<string>
#include <random>
#include<windows.h>
#include<conio.h>
using namespace std;

//用来生成随机数
static std::random_device rd;
static std::mt19937 gen(rd());
int get_random(int min, int max) {
	std::uniform_int_distribution<int> dis(min, max);
	return dis(gen);
}

#define W 120
#define H 30

struct pos {
	int x;
	int y;
};

pos getnextpos() {
	pos tmp;
	tmp.x = get_random(1, W - 2);
	tmp.y = get_random(1, H - 2);
	return tmp;
}

enum class direction { up, down, left, right };

class snake {
private:
	pos head;
	list<pos> body;
	direction dir;
	int len;
public:
	snake() {
		head={ W / 2,H / 2 };
		dir = (direction)get_random(0, 3);
		len = 1;
	}
	void turndir(char c) {
		direction dir_=dir;
		if (c == 'w') { dir_ = direction::up; }
		else if (c == 's') { dir_ = direction::down; }
		else if (c == 'a') { dir_ = direction::left; }
		else if (c == 'd') { dir_ = direction::right; }
		bool able = true;
		if (dir == direction::up && dir_ == direction::down) 
			able=false;
		else if (dir == direction::down && dir_ == direction::up) 
			able = false;
		else if (dir == direction::left && dir_ == direction::right) 
			able = false;
		else if (dir == direction::right && dir_ == direction::left) 
			able = false;
		if(able) dir = dir_;
	}
	bool move(pos& foodpos) {
		body.insert(body.begin(), head);
		if (dir == direction::up) { head.y -= 1; }
		else if (dir == direction::down) { head.y += 1; }
		else if (dir == direction::left) { head.x -= 1; }
		else { head.x += 1; }
		if (foodpos.x == head.x && foodpos.y == head.y) {
			foodpos = getnextpos();
			int  able;
			do {
				able = 0;
				for (pos p : body) {
					int x = p.x, y = p.y;
					if (x == foodpos.x && y == foodpos.y) {
						able = 1;
						foodpos = getnextpos();
					}
				}
				if(head.x == foodpos.x && head.y == foodpos.y) {
					able = 1;
					foodpos = getnextpos();
				}
			} while (able);
			len++;
		}
		else {
			body.pop_back();
		}
		bool touch = false;
		if (head.x == 0 || head.x == W - 1 
			|| head.y == 0 || head.y == H - 1) {
			touch = true;
		}
		if (len == (W - 1) * (H - 1)) touch = true;
		for (pos tmp : body) {
			int x = tmp.x, y = tmp.y;
			if (head.x == x && head.y == y) touch = true;
		}
		return touch;
	}
	void inmap(vector<vector<char>>& map) {
		for (pos p : body) {
			int x = p.x, y = p.y;
			map[y][x] = 'O';
		}
		map[head.y][head.x] = '@';
	}
};

void drawmap(vector<vector<char>>& map) {
	system("cls");
	string s="";
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			s+=map[i][j];
		}
		if (i != H - 1) s+='\n';
	}
	cout << s;
}

int main() {
	snake snake_1;
	bool havefood(true);
	pos foodpos = getnextpos();
	while (foodpos.x == W / 2 && foodpos.y == H / 2) {
		foodpos = getnextpos();
	}
	bool win(true);

	while (win) {
		vector<vector<char>> map(H, vector<char>(W));
		map[0][0] = '+', map[0][W - 1] = '+';
		for (int i = 1; i < W - 1; ++i) { map[0][i] = '-'; }
		for (int i = 1; i < H - 1; ++i) {
			map[i][0] = '|', map[i][W - 1] = '|';
			for (int j = 1; j < W - 1; ++j) { map[i][j] = ' '; }
		}
		map[H - 1][0] = '+', map[H - 1][W - 1] = '+';
		for (int i = 1; i < W - 1; ++i) { map[H - 1][i] = '-'; }
		map[foodpos.y][foodpos.x] = '*';

		if (_kbhit()) {
			char dir='哈';
			dir = _getch();
			snake_1.turndir(dir);
		}
		bool touch = snake_1.move(foodpos);
		snake_1.inmap(map);
		drawmap(map);
		if (touch) break;
		Sleep(200);
	}
	cout << endl << "Game Over";
	return 0;
}