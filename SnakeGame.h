#include <ncurses.h>
#include <cstdlib>
#include "Color.h"
#include "Constant.h"
#include "Snake.h"
using namespace std;

struct Item
{
	int x;
	int y;
	bool isGrowth;
};

struct Mission
{
	int maxLength;
	bool isMaxLength;
	int maxGrowth;
	bool isMaxGrowth;
	int maxPoison;
	bool isMaxPoison;
	int maxGate;
	bool isMaxGate;
};

class SnakeGame
{
private:
	Mission mission[4];
	Snake snake;
	Gate gate[2];
	Item itemList[2];

	int stage;
	int map[4][MAX][MAX];

	int itemTimer;
	int gateTimer;

public:
    SnakeGame();
	~SnakeGame();

	bool checkMissionClear();
	void setGate(int Map[MAX][MAX]);
	void resetItems(int Map[MAX][MAX]);
	void setItem(int Map[MAX][MAX]);
	void renderMap(int Map[MAX][MAX]);
	void renderBlock(int color);
	void gameStart();
};
