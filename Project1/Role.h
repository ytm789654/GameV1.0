#pragma once
#define MaxActionBarValue 1000
#define PlayerCamp 1
#define EnemyCamp 0 
#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
	��ɫ�Ļ��࣬��ɫָ��ҲٿصĽ�ɫ�������Ĺ���ȡ�
*/
class RoleBase
{
public:
	RoleBase(string _name,int _HpMax = 500,int _MpMax = 500, int _ATK = 50, int _DEF = 20,int _Speed = 30)
		:m_name(_name), m_HpMax(_HpMax),m_Hp(_HpMax),m_MpMax(_MpMax),m_Mp(m_MpMax),m_ATK(_ATK),m_DEF(_DEF),m_Alive(true),m_Speed(_Speed)
	{
		cout << " Role " << m_name << " is created!" << endl;
	}

	RoleBase(RoleBase *Role)
	{
		m_name = Role->GetName();
		m_HpMax = Role->GetHpMax();
		m_Hp = Role->GetHp();
		m_MpMax = Role->GetMpMax();
		m_Mp = Role->GetMp();
		m_ATK = Role->GetATK();
		m_DEF = Role->GetDEF();
		m_Speed = Role->GetSpeed();
		m_Alive = true;
	}

	~RoleBase()
	{
		cout << " destroy role " << m_name << endl;
	}

	string GetName()
	{
		return m_name;
	}

	void SetName(const string &_name)
	{
		m_name = _name;
	}

	int GetHpMax()
	{
		return m_HpMax;
	}

	void SetHpMax(int _HpMax)
	{
		m_HpMax = _HpMax;
	}

	int GetMpMax()
	{
		return m_MpMax;
	}

	void SetMpMax(int _MpMax)
	{
		m_MpMax = _MpMax;
	}

	int GetHp()
	{
		return m_Hp;
	}

	void SetHp(int _Hp)
	{
		if (_Hp > 0 && _Hp<m_HpMax)
			m_Hp = _Hp;
		if (_Hp <= 0)
			m_Hp = 0;
		if (_Hp > m_HpMax)
			m_Hp = m_HpMax;
	}

	void  AddHp(int value)
	{
		SetHp(m_Hp + value);
	}

	void ReduceHp(int value)
	{
		SetHp(m_Hp - value);
	}

	int GetMp()
	{
		return m_Mp;
	}

	void SetMp(int _Mp)
	{
		if (_Mp > 0 && _Mp < m_MpMax)
			m_Mp = _Mp;
		if (_Mp <= 0)
			m_Mp = 0;
		if (_Mp > m_MpMax)
			m_Mp = m_MpMax;
	}

	void  AddMp(int value)
	{
		SetHp(m_Mp + value);
	}

	void ReduceMp(int value)
	{
		SetHp(m_Mp - value);
	}

	int GetATK()
	{
		return m_ATK;
	}

	void SetATK(int _ATK)
	{
		m_ATK = _ATK;
	}

	int GetDEF()
	{
		return m_DEF;
	}

	void SetDEF(int _DEF)
	{
		m_DEF = _DEF;
	}

	int GetSpeed()
	{
		return m_Speed;
	}

	void SetSpeed(int _Speed)
	{
		if (_Speed < 0)
			m_Speed = 0;
		else
			m_Speed = _Speed;
	}

	void AddSpeed(int _value)
	{
		SetSpeed(m_Speed + _value);
	}

	void ReduceSpeed(int _value)
	{
		SetSpeed(m_Speed - _value);
	}

	bool IsDead()
	{
		return !(m_Hp > 0);
	}

protected:				//Ϊ�������ܹ����ʣ������protected
	string m_name;
	int m_HpMax;
	int m_Hp;
	int m_MpMax;
	int m_Mp;
	int m_ATK;
	int m_DEF;
	int m_Speed;
	bool m_Alive;
};

class BattleRole :public RoleBase
{
public:
	BattleRole(RoleBase* Role, int _Camp)			//������ҵĽ�ɫ���ݴ���BattleRole�������ҵ�role���͸��ˣ������������ҲҪ�ġ�
		:RoleBase(Role)
	{
		m_ActionValue = 0;
		m_Camp = _Camp;
	}

	BattleRole(string _name,  int _Camp , int _HpMax = 500, int _MpMax = 500, int _ATK = 50, int _DEF = 20, int _Speed = 30)
		:RoleBase(_name,_HpMax,_MpMax,_ATK,_DEF,_Speed)
	{
		m_ActionValue = 0;
		m_Camp = _Camp;
	}
	virtual void Attack(BattleRole * Obj)		//����Obj
	{
		cout << m_name << " attck " << Obj->GetName() << endl;
		Obj->BeAttacked(this);
	}

	virtual void BeAttacked(BattleRole * Obj)	//��Obj����
	{
		int damage = Obj->GetATK() - m_DEF;
		ReduceHp(damage);
		cout << m_name << " be attacked by " << Obj->GetName() << " ,damaged:" << damage << endl;
		m_Alive = !IsDead();
		if (!m_Alive)
			cout << m_name << " is dead!" << endl;
	}

	int GetActionValue()
	{
		return m_ActionValue;
	}

	void SetActionValue(int _value)
	{
		if (_value < 0)
			m_ActionValue = 0;
		else
			m_ActionValue = _value;
	}

	void AddActionValue(int _value)
	{
		SetActionValue(m_ActionValue + _value);
	}

	void ReduceActionValue(int _value)
	{
		SetActionValue(m_ActionValue - _value);
	}

	void Action(vector<BattleRole*> PlayerRoles, vector<BattleRole*> EnemyRoles )		//����Һ������ĵ�����Ϊ������������ֲ���ѡȡĿ�ꡣ
	{
		cout <<m_name<< " Action! Choose to attack !" << endl;
		if (m_Camp == PlayerCamp)
			for (int i = 0;i < EnemyRoles.size();i++)
				Attack(EnemyRoles[i]);
		if (m_Camp == EnemyCamp)
			for (int i = 0;i < PlayerRoles.size();i++)
				Attack(PlayerRoles[i]);
	}

private:
	int m_ActionValue;	//�ж�ֵ��ÿһ��ʱ�����ڼ���һ�Σ����ٶ���أ����ж�ֵ����һ��ֵʱ�ý�ɫ�ж�һ�Ρ�
	int m_Camp;	//��Ӫ 1 Ϊ��ң�0Ϊ����
};