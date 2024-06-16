#include "Snake.h"
#include <stdlib.h>



Snake::Snake()
{
	Head = NULL;
	direction = LEFT;
	growCount = 0;
	poisonCount = 0;
	gateCount = 0;
	// moveTic = false;
}
//snake의 머리부터 끝까지를 blank로 바꾸며 map을 초기화
void Snake::deleteMap(int Map[][MAX])
{
	Map[Head->y][Head->x] = BLANK;
	Node* temp = Head->next;
	while (temp != NULL)
	{
		Map[temp->y][temp->x] = BLANK;
		temp = temp->next;
	}
}
//snake가 인자값과 같은 위치를 포함하고 있는지
bool Snake::checkNode(int x, int y)
{

	Node* temp = Head;
	while (temp != NULL)
	{
		if (temp->x == x && temp->y == y)
			return true;
		temp = temp->next;
	}
	return false;
}
//gate를 통한 이동
void Snake::isMaxGate(int Map[][MAX], Gate gate[2])
{
	for (int i = 0; i < 2; i++)
	{
		if (gate[i].x == Head->x && gate[i].y == Head->y)
		{
			gateCount++;
			Direction current_direction = direction;
			const int dir[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
			for(int j = 0; j < 4; j++)
			{
				current_direction = nextDirection(current_direction, j);
				int next_y = gate[1 - i].y + dir[current_direction][0];
				int next_x = gate[1 - i].x + dir[current_direction][1];

				if(Map[next_y][next_x] != WALL) {
					Head->y = next_y;
					Head->x = next_x;
					break;
				}
			}
			direction = current_direction;
			break;
		}
	}
}

//snake의 (머리빼고) 몸이 인자의 위치(x,y)를 포함하는지
bool Snake::checkTail(int x, int y)
{
	Node* temp = Head->next;
	while (temp != NULL)
	{
		if (temp->x == x && temp->y == y)
			return true;
		temp = temp->next;
	}
	return false;
}
//poison을 먹었을 때
bool Snake::poison()
{
	Node* temp = Head;
	while (temp->next != NULL)
	{
		if (temp->next->next == NULL)
		{
			delete temp->next;
			temp->next = NULL;
			length--;
			if (length <= 2)
				return false;
			return true;
		}
		temp = temp->next;
	}
	return true;
}
//growth를 먹었을 때
void Snake::growth()
{
	Node* temp = Head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new Node;
	temp->next->x = temp->lastX;
	temp->next->y = temp->lastY;
	temp->next->next = NULL;
	length++;
}
//먹은 아이템의 종류 확인
bool Snake::checkItem(int Map[MAX][MAX])
{
	switch (Map[Head->y][Head->x])
	{
	case GROWTH:
		growth();
		growCount++;
		break;
	case POISON:
		poisonCount++;
		return poison();
	}
	return true;
}

bool Snake::move(int Map[][MAX], Gate gate[2])
{
	deleteMap(Map);
	Head->lastX = Head->x;
	Head->lastY = Head->y;
	switch (direction)
	{
	case LEFT:
		Head->x--;
		break;
	case RIGHT:
		Head->x++;
		break;
	case UP:
		Head->y--;
		break;
	case DOWN:
		Head->y++;
		break;
	}
	last_direction = direction;

	if (checkTail(Head->x, Head->y))
	{
		deleteSnake(Head);
		Head=NULL;
		return false;
	}
	isMaxGate(Map, gate);
	if (Map[Head->y][Head->x] == WALL)
	{
		deleteSnake(Head);
		Head=NULL;
		return false;
	}
	moveTail(Head);
	if(!checkItem(Map))
		return false;
	updateMap(Map);
	return true;
}
//head 방향으로 이동
void Snake::moveTail(Node* Node)
{
	if (Node->next == NULL)
		return;
	Node->next->lastX = Node->next->x;
	Node->next->lastY = Node->next->y;
	Node->next->x = Node->lastX;
	Node->next->y = Node->lastY;
	moveTail(Node->next);
}

void Snake::deleteSnake(Node* Node)
{
	if (Node == NULL)
		return;
	deleteSnake(Node->next);
	delete Node;
}

void Snake::setSnake(int x, int y)
{
	direction = LEFT;
	if (Head != NULL)
	{
		deleteSnake(Head);
		Head = NULL;
	}
	Head = new Node;
	Head->x = x;
	Head->y = y;
	Head->next = NULL;
	for (int i = 1; i <= 2; i++)
	{
		Node* add = new Node;
		add->x = Head->x + i;
		add->y = Head->y;
		add->next = NULL;
		Node* temp = Head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = add;
	}
	oldClock = 0;
	length = 3;
	growCount = 0;
	poisonCount = 0;
	gateCount = 0;
}

int Snake::update(int Map[][MAX], Gate gate[2])
{
	if(++oldClock >= 500) {
		if(!move(Map,gate))
			return -1;
		oldClock = 0;
		return 1;
	}
	return 0;
}
//키보드 입력을 통해 움직일 방향 설정
void Snake::input()
{
	int ch = getch(); //키보드에서 입력 받아옴

	switch (ch)
	{
	case KEY_LEFT:
		if (last_direction == RIGHT)
			exit(0);
		if (last_direction != RIGHT)
			direction = LEFT;
		break;
	case KEY_RIGHT:
		if (last_direction == LEFT)
			exit(0);
		if (last_direction != LEFT)
			direction = RIGHT;
		break;
	case KEY_UP:
		if (last_direction == DOWN)
			exit(0);
		if (last_direction != DOWN)
			direction = UP;
		break;
	case KEY_DOWN:
		if (last_direction == UP)
			exit(0);
		if (last_direction != UP)
			direction = DOWN;
		break;
	}
}
//map에서 색표현을 위해 지정된 숫자 대입
void Snake::updateMap(int Map[][MAX])
{
	Map[Head->y][Head->x] = HEAD;
	Node* temp = Head->next;
	while (temp != NULL)
	{
		Map[temp->y][temp->x] = BODY;
		temp = temp->next;
	}
}

Snake::~Snake()
{
	if (Head != NULL)
	{
		deleteSnake(Head);
		Head = NULL;
	}
}

Direction Snake::nextDirection(Direction direction, int count)
{
	const static Direction next[4] = {RIGHT, UP, LEFT, DOWN};
	const static int dir_to_idx[4] = {2, 0, 1, 3};

	if(count == 0)
		return direction;
	if(count == 1)
		return next[(dir_to_idx[direction] + 3) % 4];
	if(count == 2)
		return next[(dir_to_idx[direction] + 1) % 4];
	return next[(dir_to_idx[direction] + 2) % 4];
}
