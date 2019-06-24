#pragma once
#include"PCB.h"
#include"RCB.h"
#include"ResoureManager.h"

extern list<Ready> Priority_PID_List;
extern list<Block> Block_PID_List;
extern list<RCB> Res_List;
extern list<PCB> Pcb_List;


class ProcessManager
{
public:
	//��������
	bool Create(PID_TYPE pid, int priority, RID_TYPE NeedResID, unsigned int NeedRes_Num, PID_TYPE Parent_pid);
	//�ͷŽ���
	bool Destroy(PID_TYPE pid);
	//ɱ���ӽ���
	bool KillTree(PID_TYPE pid);

	
	bool Exist_PCB(PID_TYPE pid);//����Ƿ����Ѵ��ڵ�PCB
	bool Exist_Priority(PID_TYPE pid, int priority);//����Ƿ��Ѵ������ȼ�����
	bool Exist_RES(PID_TYPE pid, RID_TYPE NeedResID, unsigned int NeedRes_Num);//����Ƿ����Ѵ��ڵ���Դ
	
	bool Del_PCB(PID_TYPE pid);//��PCB������ɾ��PCB
	bool Del_PL_Proc_Node(PID_TYPE pid);//�����ȼ�����ɾ�����̽ڵ�
	bool Del_BL_Proc_Node(PID_TYPE pid);//�ӵȴ�����ɾ�����̽ڵ�
	bool Del_RCB_WaitingNode(PID_TYPE pid);//����Դ����ɾ�����̽ڵ�
};
