#include"ResoureManager.h"

void ResoureManager::Request( RID_TYPE rid, unsigned int InitResNum)
{
	for (list<RCB>::iterator ite=Res_List.begin();ite!= Res_List.end();ite++)
	{
		if (ite->get_rid() == rid)
		{
			cout << "��Դ�Ѵ���,�޷�����"<<endl;
			return;
		}
	}
	//������Դ,�����������Դ������Դ������
	RCB RCB_Block(rid, InitResNum);
	Res_List.push_back(RCB_Block);

}

void ResoureManager::Release(RID_TYPE rid, unsigned int InitResNum)
{
	for (list<RCB>::iterator ite = Res_List.begin(); ite != Res_List.end(); ite++)
	{
		if (ite->get_rid() == rid)
		{
			cout << "�ѳɹ��ͷ���Դ" << endl;
			Res_List.erase(ite);
			return;
		}
	}
}