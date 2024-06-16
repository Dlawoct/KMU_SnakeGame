#include "SnakeGame.h"

SnakeGame::SnakeGame()
{
	stage = 1;


    for(int i = 0; i < 4; i++)
	{
		for (int y = 0; y < MAX; y++)
	    {
		    for (int x = 0; x < MAX; x++)
		    {
                // 테두리 라인
                if (x == 0 || x == MAX - 1 || y == 0 || y == MAX - 1) {
                    // 왼쪽 상단, 왼쪽 하단, 오른쪽 상단, 오른쪽 하단 -> immune wall
					if ((x == 0 && y == 0) || (x == 0 && y == MAX - 1) || (x == MAX - 1 && y == 0) || (x == MAX - 1 && y == MAX - 1))
						map[i][y][x] = IMMUNE_WALL;
                    // 꼭짓점 제외 모두 그냥 벽
					else
						map[i][y][x] = WALL;
				}
				else
					map[i][y][x] = BLANK;
		    }
	    }
	}

	// 임의로 장애물 벽 생성하고 리스트에 저장
	for(int i = 0; i < 4; i++)
	{
		if (i==0)
			continue;
		else if (i==1) {
			for(int y = 5; y <= 10; y++)
			{
				map[i][y][5] = map[i][y][10] = WALL;
			}
		} else if (i==2) {
			for(int x = 5; x <= 10; x++)
			{
				map[i][15][x] = map[i][8][x] = WALL;
			}
		} else if (i==3) {
			for(int x = 3; x <= 10; x++)
			{
				map[i][x][15] = map[i][x][12] = WALL;
			}
		}

	}

	mission[0].maxLength = 3;
	mission[0].isMaxLength = false;
	mission[0].maxGrowth = 1;
	mission[0].isMaxGrowth = false;
	mission[0].maxPoison = 1;
	mission[0].isMaxPoison = false;
	mission[0].maxGate = 1;
	mission[0].isMaxGate = false;

	mission[1].maxLength = 5;
	mission[1].isMaxLength = false;
	mission[1].maxGrowth = 2;
	mission[1].isMaxGrowth = false;
	mission[1].maxPoison = 2;
	mission[1].isMaxPoison = false;
	mission[1].maxGate = 2;
	mission[1].isMaxGate = false;

	mission[2].maxLength = 6;
	mission[2].isMaxLength = false;
	mission[2].maxGrowth = 3;
	mission[2].isMaxGrowth = false;
	mission[2].maxPoison = 3;
	mission[2].isMaxPoison = false;
	mission[2].maxGate = 3;
	mission[2].isMaxGate = false;

	mission[3].maxLength = 7;
	mission[3].isMaxLength = false;
	mission[3].maxGrowth = 4;
	mission[3].isMaxGrowth = false;
	mission[3].maxPoison = 4;
	mission[3].isMaxPoison = false;
	mission[3].maxGate = 4;
	mission[3].isMaxGate = false;


	// 아이템 초기화
	for (int i = 0; i < 2; i++)
	{
		itemList[i].x = -1;
		itemList[i].y = -1;
	}
	//게이트 초기
	for (int i = 0; i < 2; i++)
	{
		gate[i].x = -1;
		gate[i].y = -1;
	}
	// 아이템 시간 초기화
	itemTimer = 0;
	gateTimer = 0;
}
//맵의 숫자에 맞춰 지정된 색을 입힘
void SnakeGame::renderMap(int map[MAX][MAX])
{
	clear();
	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			int color = Color::WHITE;

			if (map[y][x] == WALL)
				color = Color::YELLOW;
			else if (map[y][x] == HEAD)
				color = Color::CYAN;
			else if (map[y][x] == BODY)
				color = Color::BLUE;
			else if (map[y][x] == GROWTH)
				color = Color::GREEN;
			else if (map[y][x] == POISON)
				color = Color::RED;
			else if (map[y][x] == IMMUNE_WALL)
				color = Color::BLACK;
			else if(map[y][x] == GATE)
				color = Color::MAGENTA;

			renderBlock(color);
		}
		//점수판
		if (y == 0)
			printw("    Score Board  %d Stage", stage);
		else if (y == 1)
			printw("    B : %d/%d",snake.getLength(), mission[stage - 1].maxLength);
		else if (y == 2)
			printw("    + : %d", snake.getGrowthCount());
		else if (y == 3)
			printw("    - : %d", snake.getPoisonCount());
		else if (y == 4)
			printw("    G : %d", snake.getGate());
		else if (y == 7)
			printw("     Mission");
		else if (y == 8)
			printw("    B : %d (%c)", mission[stage - 1].maxLength, mission[stage - 1].isMaxLength ? 'v' : ' ');
		else if (y == 9)
			printw("    + : %d (%c)", mission[stage - 1].maxGrowth, mission[stage - 1].isMaxGrowth ? 'v' : ' ');
		else if (y == 10)
			printw("    - : %d (%c)", mission[stage - 1].maxPoison, mission[stage - 1].isMaxPoison ? 'v' : ' ');
		else if (y == 11)
			printw("    G : %d (%c)", mission[stage - 1].maxGate, mission[stage - 1].isMaxGate ? 'v' : ' ');
		printw("\n");
	}
}
//실질적으로 색을 넣는 부분
void SnakeGame::renderBlock(int color)
{
	attron(COLOR_PAIR(color));
	printw("  ");
	attroff(COLOR_PAIR(color));
}
//일정 시간이 지나면 아이템과 게이트 배치
void SnakeGame::resetItems(int Map[MAX][MAX])
{
	if (++itemTimer == CREATE_ITEM_TIME)
	{
		setItem(Map);
		itemTimer = 0;
	}
	if (++gateTimer == CREATE_GATE_TIME)
	{
		setGate(Map);
		gateTimer = 0;
	}
}
//실질적으로 게이트를 만드는 부분
void SnakeGame::setGate(int map[MAX][MAX])
{
	for (int i = 0; i < 2; i++)
	{
		int lastY = gate[i].y;
		int lastX = gate[i].x;

		do
		{
			if (rand() % 2 == 0) {
				gate[i].x = MAX - 1;
				gate[i].y = rand() % (MAX - 2) + 1;
			}
			else {
				gate[i].x = 0;
				gate[i].y = rand() % (MAX - 2) + 1;
			}
		}
		while(i == 1 && gate[0].y == gate[1].y && gate[0].x == gate[1].x);

		// 게이트가 있다면
		if (lastY != -1 && lastX != -1)
			// 게이트 제거
			map[lastY][lastX] = WALL;
		// 게이트 재할당
		map[gate[i].y][gate[i].x] = GATE;
	}
}
//실질적으로 아이템을 만드는 부분
void SnakeGame::setItem(int Map[MAX][MAX])
{
	for (int i = 0; i < 2; i++)
	{
		if (itemList[i].x != -1 && itemList[i].y != -1)
			Map[itemList[i].y][itemList[i].x] = BLANK;

		do
		{
			itemList[i].x = rand() % (MAX - 2) + 1;
			itemList[i].y = rand() % (MAX - 2) + 1;
		}
		while(snake.checkNode(itemList[i].x, itemList[i].y)
			|| Map[itemList[i].y][itemList[i].x] != BLANK);

		itemList[i].isGrowth = rand() % 2 == 0 ? true : false;
		if (itemList[i].isGrowth)
			Map[itemList[i].y][itemList[i].x] = GROWTH;
		else
			Map[itemList[i].y][itemList[i].x] = POISON;
	}
}

//미션 달성을 확인
bool SnakeGame::checkMissionClear()
{
	if (snake.getLength() >= mission[stage - 1].maxLength)
		mission[stage - 1].isMaxLength = true;
	if (snake.getGrowthCount() >= mission[stage - 1].maxGrowth)
		mission[stage - 1].isMaxGrowth = true;
	if (snake.getPoisonCount() >= mission[stage - 1].maxPoison)
		mission[stage - 1].isMaxPoison = true;
	if (snake.getGate() >= mission[stage - 1].maxGate)
		mission[stage - 1].isMaxGate = true;


	if (mission[stage - 1].isMaxGate && mission[stage - 1].isMaxGrowth && mission[stage - 1].isMaxLength && mission[stage - 1].isMaxPoison)
		return true;
	return false;
}


void SnakeGame::gameStart()
{
	snake.setSnake(MAX / 2, MAX / 2);
	snake.updateMap(map[0]);


	while (true)
	{
		// 방향키 입력
		snake.input();

		int check;
		int (&currentMap)[MAX][MAX] = map[stage - 1];

		// 아이템 재배치
		resetItems(currentMap);

		check = snake.update(currentMap, gate);
		if(check == -1)
			break;

		// 미션 다 통과하면
		if (checkMissionClear())
		{
			stage++;
			if (stage > 4)
				return;

			for (int y = 0; y < MAX; y++)
			{
				for (int x = 0; x < MAX; x++)
				{
					// snake 지우기
					if (currentMap[y][x] == HEAD || currentMap[y][x] == BODY)
						currentMap[y][x] = BLANK;
				}
			}
			// snake 재배치
			snake.setSnake(MAX / 2 - 2, MAX / 2);
			snake.updateMap(currentMap);

			// gate 초기화
			currentMap[gate[0].y][gate[0].x] = WALL;
			currentMap[gate[1].y][gate[1].x] = WALL;

			// item시간 초기화
			itemTimer = 0;
			gateTimer = 0;
		}
		// 맵 다시 그리기
		renderMap(currentMap);

		// 1ms 뒤에 실행 (실행 지연시키기)
		napms(1);
	}
}
SnakeGame::~SnakeGame()
{

}
