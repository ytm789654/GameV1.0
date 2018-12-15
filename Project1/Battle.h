#pragma once
#include <iostream>
#include <string>
#include "Player.h"
#include "EnemyGroup.h"
using namespace std;

class Battle
{
public:
	Battle(Player * _pPlayer, EnemyGroup * _pEnemyGroup) 
		:m_pPlayer(_pPlayer),m_pEnemyGroup(_pEnemyGroup)
	{
		DoBattle();
	}

	void DoBattle()		//主要战斗流程
	{
		//todo
		/*这里无限循环直到有一方输掉。
		   每个单位都有速度值，给每个单位一个行动条值，初始化为0.当进入战斗后，每个单位在下方的每次循环中行动条值都加上自身速度。
		   当行动条值大于某特定值ActVal（这里由本GM设定，暂定为1000），则该单位进入行动状态，同时将该单位的行动条值扣掉ActVal（1000）.
		   每次循环在加完行动条值后还是按照行动条值排个序，这样同时行动条值过1000的就可以按照速度先后行动了。
		   单位死亡状态下，行动条值为0.
		   可能这种写法会有性能问题，不过反正是个单机，到时候有问题再优化8. 
		*/
		while (!m_pPlayer->IsLose() && !m_pEnemyGroup->IsBattleLose)
		{

		}
	}
private:
	Player* m_pPlayer;
	EnemyGroup* m_pEnemyGroup;
};