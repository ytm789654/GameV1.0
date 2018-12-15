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
		while (!m_pPlayer->IsLose() && !m_pEnemyGroup->IsBattleLose)
		{

		}
	}
private:
	Player* m_pPlayer;
	EnemyGroup* m_pEnemyGroup;
};