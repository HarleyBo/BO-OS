#include"SchedulerManager.h"
#include"PCB.h"

void SchedulerManager::time_out()
{
	list<PCB>::iterator p;
	//�����Ƿ�����������еĽ���
	for (list<PCB>::iterator ite = Pcb_List.begin(); ite != Pcb_List.end(); ite++)
	{
		if ((ite->get_status() == 2 ) && (ite->get_available() == true))//����״̬(0:ready 1:blocked 2:running)
		{
			ite->set_status(0);//�޸ĳɾ���̬
			p = ite;
			break;
		}
	}

	bool P_FLAG = false;
	//�����Ƿ��Ѵ��ڵ�������ȼ�
	for (list<Ready>::iterator ite = Priority_PID_List.begin(); ite != Priority_PID_List.end(); ite++)
	{
		if (ite->Priority == p->get_priority() && (ite->Priority_PID_Queue.begin()->PID!=-1))//�Ѵ��ڵ����ȼ�����,PID!=-1
		{
			PID_Node pid_Node;
			pid_Node.PID = p->get_pid();
			pid_Node.Available = true;
			ite->Priority_PID_Queue.push_back(pid_Node);
			P_FLAG = true;
			break;
		}
		else if (ite->Priority == p->get_priority() && (ite->Priority_PID_Queue.begin()->PID == -1))//�Ѵ��ڵ����ȼ�����,PID=-1
		{
			ite->Priority_PID_Queue.begin()->PID = p->get_pid();
			ite->Priority_PID_Queue.begin()->Available = true;
			P_FLAG = true;
			break;
		}
	}
	if (false == P_FLAG)//�����ڵ����ȼ�����
	{
		Ready Ready_List;
		Ready_List.Priority = p->get_priority();
		PID_Node pid_Node;
		pid_Node.PID = p->get_pid();
		pid_Node.Available = true;
		Ready_List.Priority_PID_Queue.push_back(pid_Node);//��pid���뵽���ȼ�����
		Priority_PID_List.push_back(Ready_List);//�����ȼ����мӵ�������
	}


	//�����Ƿ��Ѵ��ڵ����ȼ������е�������ȼ�
	for (list<Ready>::iterator ite = Priority_PID_List.begin(); ite != Priority_PID_List.end(); ite++)
	{
		if ((ite->Priority_PID_Queue.begin()->PID != -1) && (ite->Priority_PID_Queue.begin()->Available != false))//�Ѵ��ڵ����ȼ�����
		{
			//�Ӿ��������е���
			ite->Priority_PID_Queue.pop_front();
			for (list<PCB>::iterator ites = Pcb_List.begin(); ites != Pcb_List.end(); ites++)
			{

				if (ites->get_pid() == ite->Priority_PID_Queue.begin()->PID)//��Pcb_List�������ҵ���Ӧ��pid
				{
					ites->set_status(2);

					//����Դ�ȴ�������ɾ��
					for (list<RCB>::iterator ite_res = Res_List.begin(); ite_res != Res_List.end(); ite_res++)
					{
						for (vector<R_Node>::iterator ite_res_vec = (p->get_ResNodeVec()).begin(); ite_res_vec != (p->get_ResNodeVec()).end(); ite_res_vec++)
						{
							if (ite_res->get_rid() == ite_res_vec->ResID)//�Ѵ��ڵ���Դ����
							{
								for (list<Waiting_PID>::iterator ite_res_Node = (ite_res->Waiting_List).begin(); ite_res_Node != (ite_res->Waiting_List).end(); ite_res_Node++)
								{
									if (ites->get_pid() == ite_res_Node->pid)
									{
										(ite_res->Waiting_List).erase(ite_res_Node);
										break;
									}
								}
								break;
							}
						}

					}

					break;
				}


			}
			break;
		}
	}


}

void SchedulerManager::Scheduler()
{
	list<PCB>::iterator p;
	//�����Ƿ�����������еĽ���
	for (list<PCB>::iterator ite = Pcb_List.begin(); ite != Pcb_List.end(); ite++)
	{
		if ((ite->get_status() == 2) && (ite->get_available() == true))//����״̬(0:ready 1:blocked 2:running)
		{
			if ((this->priority < p->get_priority()) && (this->Status != 2))
			{
				ite->set_status(0);//�޸ĳ� ����̬
				p = ite;
				break;
			}
		}
	}
	
	

	if ((this->priority < p->get_priority()) && (this->Status != 2))
	{
		bool P_FLAG = false;
		//�����Ƿ��Ѵ��ڵ����ȼ�
		for (list<Ready>::iterator ite = Priority_PID_List.begin(); ite != Priority_PID_List.end(); ite++)
		{
			if (ite->Priority == p->get_priority() && (ite->Priority_PID_Queue.begin()->PID != -1))//�Ѵ��ڵ����ȼ�����,PID!=-1
			{
				PID_Node pid_Node;
				pid_Node.PID = p->get_pid();
				pid_Node.Available = true;
				ite->Priority_PID_Queue.push_back(pid_Node);
				P_FLAG = true;
				break;
			}
			else if (ite->Priority == p->get_priority() && (ite->Priority_PID_Queue.begin()->PID == -1))//�Ѵ��ڵ����ȼ�����,PID=-1
			{
				ite->Priority_PID_Queue.begin()->PID = p->get_pid();
				ite->Priority_PID_Queue.begin()->Available = true;
				P_FLAG = true;
				break;
			}
		}
		if (false == P_FLAG)//�����ڵ����ȼ�����
		{
			Ready Ready_List;
			Ready_List.Priority = p->get_priority();
			PID_Node pid_Node;
			pid_Node.PID = p->get_pid();
			pid_Node.Available = true;
			Ready_List.Priority_PID_Queue.push_back(pid_Node);//��pid���뵽���ȼ�����
			Priority_PID_List.push_back(Ready_List);//�����ȼ����мӵ�������

		}
	}
	




	for (list<Ready>::iterator ite = Priority_PID_List.begin(); ite != Priority_PID_List.end(); ite++)
	{
		if (this->priority == ite->Priority)//�Ѵ��ڵ����ȼ�����
		{

			for (list<PID_Node>::iterator ites = (ite->Priority_PID_Queue).begin(); ites != (ite->Priority_PID_Queue).end(); ites++)
			{
				//�Ӿ��������е���
				if (ites->PID == this->PID)
				{
					(ite->Priority_PID_Queue).erase(ites);
					for (list<PCB>::iterator ites = Pcb_List.begin(); ites != Pcb_List.end(); ites++)
					{
						if (ites->get_pid() == this->PID)//��Pcb_List�������ҵ���Ӧ��pid
						{
							ites->set_status(2);
							//����Դ�ȴ�������ɾ��
							for (list<RCB>::iterator ite_res = Res_List.begin(); ite_res != Res_List.end(); ite_res++)
							{
								for (vector<R_Node>::iterator ite_res_vec = (p->get_ResNodeVec()).begin(); ite_res_vec != (p->get_ResNodeVec()).end(); ite_res_vec++)
								{
									if (ite_res->get_rid() == ite_res_vec->ResID)//�Ѵ��ڵ���Դ����
									{
										for (list<Waiting_PID>::iterator ite_res_Node = (ite_res->Waiting_List).begin(); ite_res_Node != (ite_res->Waiting_List).end(); ite_res_Node++)
										{
											if (ites->get_pid() == ite_res_Node->pid)
											{
												ite_res->Waiting_List.erase(ite_res_Node);
												break;
											}
										}
										break; 
									}

								}

							}
							break;
						}
					}
					break;
				}

			}
			break;
		}

	}

	

}