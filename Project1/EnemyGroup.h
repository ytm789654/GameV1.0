/*
	����ļ�����һ��ս���У��з���λ�ļ���EnemyGroup��
	��ԱΪvector <RoleBase*> Objs
	ÿ�ι�����ɺ󣬶�Ҫ�ж���˫��ʤ��
*/
#pragma once
#define EnemyCamp 0
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "Role.h"

class EnemyGroup
{
public:
	EnemyGroup();
	~EnemyGroup();
	void AddRole(BattleRole *);
	bool IsBattleLose();
	vector <BattleRole*> GetBattleRoles();
	void ReleaseBattleRoles();
private:
	vector <BattleRole*> m_BattleRoles;	//һ��ս���еĵ�λ���ϡ�
};

EnemyGroup::EnemyGroup()
{
	int EnemyNum = rand() % 3 + 1;
	cout << "This battle total " << EnemyNum << " enemies" << endl;
	for (int i = 0;i < EnemyNum;i++)
	{
		BattleRole* pEnemyRole = new BattleRole("Monster", EnemyCamp ,200,200,30,10,10);
		AddRole(pEnemyRole);
	}
}

EnemyGroup::~EnemyGroup()
{
	ReleaseBattleRoles();
	cout << "delete OK!" << endl;
}

inline void EnemyGroup::AddRole(BattleRole *Obj)
{
	m_BattleRoles.push_back(Obj);
}

inline bool EnemyGroup::IsBattleLose()			
{
	for (int i = 0;i < m_BattleRoles.size();i++)
	{
		if (!m_BattleRoles[i]->IsDead())
			return false;
	}
	return true;
}

inline vector<BattleRole*> EnemyGroup::GetBattleRoles()
{
	return m_BattleRoles;
}

inline void EnemyGroup::ReleaseBattleRoles()
{
	for (int i = 0;i < m_BattleRoles.size();i++)
		delete m_BattleRoles[i];
	m_BattleRoles.clear();
}
