#include"ProcessManager.h"
//����Ƿ����Ѵ��ڵ�PCB
bool ProcessManager::Exist_PCB(PID_TYPE pid)
{ 
	bool flag = false;
	for (list<PCB>::iterator ite = Pcb_List.begin(); ite != Pcb_List.end(); ite++)
	{
		if ((ite->get_pid() == pid) && (ite->get_available() == true))//�Ѵ�������Ч
		{
			flag=true;
		}
	}
	return flag;
}

bool Ascending(const Ready &Ready1, const Ready &Ready2)
{
	return (Ready1.Priority<Ready2.Priority);
}


//����Ƿ��Ѵ������ȼ�����
bool  ProcessManager::Exist_Priority(PID_TYPE pid, int priority)
{
	bool P_FLAG = false;
	for (list<Ready>::iterator ite = Priority_PID_List.begin(); ite != Priority_PID_List.end(); ite++)
	{
		if (ite->Priority == priority && (ite->Priority_PID_Queue.begin()->PID != -1))//�Ѵ��ڵ����ȼ�����,PID!=-1
		{
			PID_Node pid_Node;
			pid_Node.PID = pid;
			pid_Node.Available = true;
			ite->Priority_PID_Queue.push_back(pid_Node);
			P_FLAG = true;
			break;
		}
		else if (ite->Priority == priority && (ite->Priority_PID_Queue.begin()->PID == -1))//�Ѵ��ڵ����ȼ�����,PID=-1
		{
			ite->Priority_PID_Queue.begin()->PID = pid;
			ite->Priority_PID_Queue.begin()->Available = true;
			P_FLAG = true;
			break;
		}
	}
	if (false == P_FLAG)//�����ڵ����ȼ�����
	{
		Ready Ready_List;
		Ready_List.Priority = priority;
		PID_Node pid_Node;
		pid_Node.PID = pid;
		pid_Node.Available = true;
		Ready_List.Priority_PID_Queue.push_back(pid_Node);//��pid���뵽���ȼ�����
		Priority_PID_List.push_back(Ready_List);//�����ȼ����мӵ�������
		Priority_PID_List.sort(Ascending);
	}
	return true;
}

//����Ƿ����Ѵ��ڵ���Դ
bool  ProcessManager::Exist_RES(PID_TYPE pid,RID_TYPE NeedResID, unsigned int NeedRes_Num)
{
	bool R_FLAG = false;
	for (list<RCB>::iterator ite = Res_List.begin(); ite != Res_List.end(); ite++)
	{
		if (ite->get_rid() == NeedResID)//�Ѵ��ڵ���Դ����
		{
			Waiting_PID wp;
			wp.pid = pid;
			wp.NeedResNumber = NeedRes_Num;
			wp.Available = true;
			ite->add_WaitingList(wp);
			R_FLAG = true;
			break;
		}
	}
	if (false == R_FLAG)//�����ڵ���Դ����
	{
		RCB tempRCB(pid, NeedRes_Num, NeedResID, NeedRes_Num);
		Res_List.push_back(tempRCB);

	}

	return true;
}


//��PCB������ɾ��PCB
bool  ProcessManager::Del_PCB(PID_TYPE pid)
{
	bool flag = false;
	for (list<PCB>::iterator ite_pcb = Pcb_List.begin(); ite_pcb != Pcb_List.end(); ite_pcb++)
	{

		if ((ite_pcb->get_pid() == pid) && (ite_pcb->get_available() == true))//�Ѵ�������Ч
		{
			Pcb_List.erase(ite_pcb);
			flag = true;
			break;
		}
		
	}
	return flag;
}

//�����ȼ���ɾ�����̽ڵ�
bool ProcessManager::Del_PL_Proc_Node(PID_TYPE pid)
{
	bool flag=false;
	int priority=0;
	for (list<PCB>::iterator ite_pcb = Pcb_List.begin(); ite_pcb != Pcb_List.end(); ite_pcb++)
	{

		if ((ite_pcb->get_pid() == pid) && (ite_pcb->get_available() == true))//�Ѵ�������Ч
		{
			priority = ite_pcb->get_priority();
			break;
		}

	}

	for (list<Ready>::iterator ite = Priority_PID_List.begin(); ite != Priority_PID_List.end(); ite++)
	{
		if (ite->Priority == priority)//�Ѵ��ڵ����ȼ�����
		{
			for (list<PID_Node>::iterator ite_Queue_Node = (ite->Priority_PID_Queue).begin(); ite_Queue_Node != (ite->Priority_PID_Queue).end(); ite_Queue_Node++)
			{
				if ((ite_Queue_Node->PID == pid)&&(ite_Queue_Node->Available==true))
				{
					(ite->Priority_PID_Queue).erase(ite_Queue_Node);
					flag = true;
					break;
				}
			}
			break;
		}
	}
	return flag;
}

//�ӵȴ�����ɾ�����̽ڵ�
bool ProcessManager::Del_BL_Proc_Node(PID_TYPE pid)
{
	bool flag = false;
	for (list<Block>::iterator ite = Block_PID_List.begin(); ite != Block_PID_List.end(); ite++)
	{
		if ((ite->PID == pid) && (ite->Available == true))//�Ѵ�������Ч
		{
			Block_PID_List.erase(ite);
			flag = true;
			break;
		}
	}
	return flag;
}


//����Դ����ɾ�����̽ڵ�
bool ProcessManager::Del_RCB_WaitingNode(PID_TYPE pid)
{
	list<PCB>::iterator ite_pcb;
	for (list<PCB>::iterator ite = Pcb_List.begin(); ite != Pcb_List.end(); ite++)
	{
		if ((ite->get_pid() == pid) && (ite->get_available() == true))//�Ѵ�������Ч
		{
			ite_pcb = ite;
			break;
		}
	}

	for (list<RCB>::iterator ite = Res_List.begin(); ite != Res_List.end(); ite++)
	{
		for (vector<R_Node>::iterator ite_res_vec = (ite_pcb->get_ResNodeVec()).begin(); ite_res_vec != (ite_pcb->get_ResNodeVec()).end(); ite_res_vec++)
		{
			if (ite->get_rid() == ite_res_vec->ResID)//���ڵ���ԴID
			{
				for (list<Waiting_PID>::iterator ite_res_Node = (ite->Waiting_List).begin(); ite_res_Node != (ite->Waiting_List).end(); ite_res_Node++)
				{
					if ((ite_pcb->get_pid() == ite_res_Node->pid)&&(ite_res_Node->Available==true))
					{
						(ite->Waiting_List).erase(ite_res_Node);
					}
				}
			}
		}

	}
	return true;
}


bool ProcessManager::Create(PID_TYPE pid, int priority, RID_TYPE NeedResID, unsigned int NeedRes_Num, PID_TYPE Parent_pid)
{
	//����Ƿ����Ѵ��ڵ�PCB
    if (true == Exist_PCB(pid))
	{
		cout << "PCB Block�Ѵ���,�����´���" << endl;
	}
	//�½����̣���ʼ��PCB  
	PCB Proc(pid, NeedResID, NeedRes_Num, priority, Parent_pid);  
	Pcb_List.push_back(Proc);

	//����Ƿ��Ѵ������ȼ�����
	Exist_Priority(pid, priority);
	
	//����Ƿ����Ѵ��ڵ���Դ
	Exist_RES(pid, NeedResID, NeedRes_Num);
	

	return true;
}

bool ProcessManager::Destroy(PID_TYPE pid)
{
	//��PCB����ɾ��PCB
	KillTree(pid);

	//�����ȼ���ɾ�����̽ڵ�
	Del_PL_Proc_Node(pid);

	//�ӵȴ�����ɾ�����̽ڵ�
	Del_BL_Proc_Node(pid);

	//��RCB����ɾ���ȴ����̽ڵ�
	Del_RCB_WaitingNode(pid);
	return true;
}

bool ProcessManager::KillTree(PID_TYPE pid)
{
	//��PCB�����в���PCB block
	for (list<PCB>::iterator ite = Pcb_List.begin(); ite != Pcb_List.end(); ite++)
	{

		if ((ite->get_pid() == pid) && (ite->get_available() == true))//�Ѵ�������Ч
		{
			for (list<PID_TYPE>::iterator ite_Child_Node = (ite->FCTree).Children_Node.begin(); ite_Child_Node != (ite->FCTree).Children_Node.end(); ite_Child_Node++)
			{
				if (-1 != (((ite->FCTree).Children_Node).front()))
				{
					for (list<PID_TYPE>::iterator ite_list = (((ite->FCTree).Children_Node).begin()); ite_list != (((ite->FCTree).Children_Node).end()); ite_list++)//������ӽڵ������Ƚ����ͷ�
					{
						KillTree(pid);
					}
				}
				
			}
			Del_PCB(pid);
			break;
		}
	}

	return true;
}