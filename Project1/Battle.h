#pragma once
#define MaxActionBarValue 1000
#include <iostream>
#include <string>
#include <algorithm>
#include "Player.h"
#include "EnemyGroup.h"
using namespace std;

bool cmp(BattleRole* A, BattleRole* B)
{
	return A->GetActionValue() > B->GetActionValue();
}

class Battle
{
public:
	Battle(Player * _pPlayer, EnemyGroup * _pEnemyGroup) 
		:m_pPlayer(_pPlayer),m_pEnemyGroup(_pEnemyGroup)
	{
		if (m_pPlayer->BattlePreparation())
			DoBattle();
		else
			cout << "Init player battle role error!" << endl;
	}

	void BuildActiveRolesVec()
	{
		m_ActiveRoles.clear();
		vector <BattleRole*> PlayerBattleRoles = m_pPlayer->GetPlayerBattleRoles();
		for (int i = 0;i < PlayerBattleRoles.size();i++)
			if(!PlayerBattleRoles[i]->IsDead())
				m_ActiveRoles.push_back(PlayerBattleRoles[i]);
		vector <BattleRole*> EnemyBattleRoles = m_pEnemyGroup->GetBattleRoles();
		for (int i = 0;i < EnemyBattleRoles.size();i++)
			if(!EnemyBattleRoles[i]->IsDead())
				m_ActiveRoles.push_back(EnemyBattleRoles[i]);
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
		while (true)
		{
			BuildActiveRolesVec();
			for (int i = 0;i < m_ActiveRoles.size();i++)		//应该不用每次都重新build一次，后边看看可不可以设定个是不是挂了人的flag或者直接在逻辑里边控制这个vector，这里先这么写着
				m_ActiveRoles[i]->SetActionValue( m_ActiveRoles[i]->GetActionValue() + m_ActiveRoles[i]->GetSpeed() );		//每个时间周期每个角色行动条加上各自的Speed
			sort(m_ActiveRoles.begin(), m_ActiveRoles.end(), cmp);
			for (int i = 0;i < m_ActiveRoles.size();i++)
				if (m_ActiveRoles[i]->GetActionValue() > MaxActionBarValue && !m_ActiveRoles[i]->IsDead())
				{
					m_ActiveRoles[i]->Action(m_pPlayer->GetPlayerBattleRoles(), m_pEnemyGroup->GetBattleRoles());
					m_ActiveRoles[i]->SetActionValue(m_ActiveRoles[i]->GetActionValue() % MaxActionBarValue);	//重置行动条,这里到底减好呢还是取余好呢。。。。
				}
			if (m_pPlayer->IsBattleLose() || m_pEnemyGroup->IsBattleLose())
				break;
		}
		cout << "Battle is over!" << endl;
	}
private:
	Player* m_pPlayer;
	EnemyGroup* m_pEnemyGroup;
	vector <BattleRole* > m_ActiveRoles;	//能活动的所有战斗角色集合。
};