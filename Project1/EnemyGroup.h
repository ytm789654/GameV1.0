/*
	这个文件描述一次战斗中，敌方单位的集合EnemyGroup。
	成员为vector <RoleBase*> Objs
	每次攻击完成后，都要判断下
*/
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Role.h"

class EnemyGroup
{
public:
	EnemyGroup();
	~EnemyGroup();
	void AddRole(BattleRole *);
	bool IsBattleLose();
private:
	vector <BattleRole*> m_Roles;	//一次战斗中的单位集合。
};

EnemyGroup::EnemyGroup()
{
}

EnemyGroup::~EnemyGroup()
{
	while (m_Roles.size() != 0)
	{
		delete m_Roles[0];
		m_Roles.erase(m_Roles.begin());
	}
	cout << "delete OK!" << endl;
}

inline void EnemyGroup::AddRole(BattleRole *Obj)
{
	m_Roles.push_back(Obj);
}

inline bool EnemyGroup::IsBattleLose()			
{
	for (int i = 0;i < m_Roles.size();i++)
	{
		if (!m_Roles[i]->IsDead())
			return false;
	}
	return true;
}
