#include "Constant.h"
#include <ncurses.h>

struct Gate {
    // Gate의 x,y 좌표
    int x;
    int y;
};

enum Direction {
    LEFT, // 0
    RIGHT, // 1
    UP, // 2
    DOWN // 3
};

struct Node
{
	int x;
	int y;
	int lastX;
	int lastY;
	Node* next;
};

class Snake
{
private:
	Node* Head;
	Direction direction, last_direction;
	int oldClock;
	int length;
	int growCount;
	int poisonCount;
	int gateCount;
	// bool moveTic;

public:
  	Snake();
	~Snake();

	bool checkTail(int x, int y);
	void isMaxGate(int Map[][MAX],Gate gate[2]);
	bool poison();
	void growth();
	bool checkItem(int Map[MAX][MAX]);
	bool checkNode(int x, int y);
	void input();
	void deleteMap(int Map[][MAX]);
	void deleteSnake(Node* Node);
	void setSnake(int x, int y);
	int update(int Map[][MAX],Gate gate[2]);
	void updateMap(int Map[][MAX]);
	bool move(int Map[][MAX], Gate gate[2]);
	void moveTail(Node* Node);
	Direction nextDirection(Direction direction, int count);

	int getLength() { return length; }
	int getGrowthCount() { return growCount; }
	int getPoisonCount() { return poisonCount; }
	int getGate() { return gateCount; }


};
