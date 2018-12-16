#pragma once
#define PlayerCamp 1
#include <iostream>
#include "Role.h"
#include <vector>
using namespace std;

class Player
{
public:
	Player()
	{
		RoleBase * p = new RoleBase("XiaoMing");
		m_Roles.push_back(p);
		cout << " Player init is OK!" << endl;
	}

	~Player()
	{
		ReleaseBattleRoles();
		ReleaseRoles();
		cout << "Player delete OK!" << endl;
	}

	bool IsLose()
	{
		for (int i = 0;i < m_Roles.size();i++)
			if (!m_Roles[i]->IsDead())
				return false;
		return true;
	}
	/******************ս���߼����****************/
	bool BattlePreparation()
	{
		//�����ԭ����BattleRoles
		ReleaseBattleRoles();
		//�ٸ������ڵ�role����һ��BattleRoles;
		for (int i = 0;i < m_Roles.size();i++)
		{
			BattleRole * pBattleRole = new BattleRole(m_Roles[i] , PlayerCamp);
			m_BattleRoles.push_back(pBattleRole);
		}
		if (!m_BattleRoles.size())
			return false;
		else
			return true;
	}

	vector <BattleRole*> GetPlayerBattleRoles()
	{
		return m_BattleRoles;
	}

	bool IsBattleLose()
	{
		for (int i = 0;i < m_Roles.size();i++)
			if (!m_Roles[i]->IsDead())
				return false;
		return true;
	}

	/******************�ͷ��ڴ����*****************/
	void ReleaseRoles()
	{
		for (int i = 0;i < m_Roles.size();i++)
			delete m_Roles[i];
		m_Roles.clear();
	}

	void ReleaseBattleRoles()
	{
		for (int i = 0;i < m_BattleRoles.size();i++)
			delete m_BattleRoles[i];
		m_BattleRoles.clear();
	}

private:
	vector <RoleBase *> m_Roles;	//��ҵ�ǰ�ٿصĽ�ɫ��
	vector <BattleRole*> m_BattleRoles;	//ս����ɫ��
};