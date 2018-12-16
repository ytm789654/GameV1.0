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

	void DoBattle()		//��Ҫս������
	{
		//todo
		/*��������ѭ��ֱ����һ�������
		   ÿ����λ�����ٶ�ֵ����ÿ����λһ���ж���ֵ����ʼ��Ϊ0.������ս����ÿ����λ���·���ÿ��ѭ�����ж���ֵ�����������ٶȡ�
		   ���ж���ֵ����ĳ�ض�ֵActVal�������ɱ�GM�趨���ݶ�Ϊ1000������õ�λ�����ж�״̬��ͬʱ���õ�λ���ж���ֵ�۵�ActVal��1000��.
		   ÿ��ѭ���ڼ����ж���ֵ���ǰ����ж���ֵ�Ÿ�������ͬʱ�ж���ֵ��1000�ľͿ��԰����ٶ��Ⱥ��ж��ˡ�
		   ��λ����״̬�£��ж���ֵΪ0.
		   ��������д�������������⣬���������Ǹ���������ʱ�����������Ż�8. 
		*/
		while (true)
		{
			BuildActiveRolesVec();
			for (int i = 0;i < m_ActiveRoles.size();i++)		//Ӧ�ò���ÿ�ζ�����buildһ�Σ���߿����ɲ������趨���ǲ��ǹ����˵�flag����ֱ�����߼���߿������vector����������ôд��
				m_ActiveRoles[i]->SetActionValue( m_ActiveRoles[i]->GetActionValue() + m_ActiveRoles[i]->GetSpeed() );		//ÿ��ʱ������ÿ����ɫ�ж������ϸ��Ե�Speed
			sort(m_ActiveRoles.begin(), m_ActiveRoles.end(), cmp);
			for (int i = 0;i < m_ActiveRoles.size();i++)
				if (m_ActiveRoles[i]->GetActionValue() > MaxActionBarValue && !m_ActiveRoles[i]->IsDead())
				{
					m_ActiveRoles[i]->Action(m_pPlayer->GetPlayerBattleRoles(), m_pEnemyGroup->GetBattleRoles());
					m_ActiveRoles[i]->SetActionValue(m_ActiveRoles[i]->GetActionValue() % MaxActionBarValue);	//�����ж���,���ﵽ�׼����ػ���ȡ����ء�������
				}
			if (m_pPlayer->IsBattleLose() || m_pEnemyGroup->IsBattleLose())
				break;
		}
		cout << "Battle is over!" << endl;
	}
private:
	Player* m_pPlayer;
	EnemyGroup* m_pEnemyGroup;
	vector <BattleRole* > m_ActiveRoles;	//�ܻ������ս����ɫ���ϡ�
};