#pragma once
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
		cout << "Player init is OK!" << endl;
	}

	~Player()
	{
		while (m_Roles.size() != 0)
		{
			delete m_Roles[0];
			m_Roles.erase(m_Roles.begin());
		}
		cout << "delete OK!" << endl;
	}

	bool IsLose()
	{
		for (int i = 0;i < m_Roles.size();i++)
			if (!m_Roles[i]->IsDead())
				return false;
		return true;
	}
private:
	vector <RoleBase *> m_Roles;	//玩家当前操控的角色。
};