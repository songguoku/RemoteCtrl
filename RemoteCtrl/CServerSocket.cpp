#include "pch.h"
#include "CServerSocket.h"

CServerSocket* CServerSocket::m_Instance = NULL;//
CServerSocket::CHelper CServerSocket::m_chelper;//��ʹ��new����������ϵͳ�Զ�����CHelper���������Ӷ�����CServerSocket����

CServerSocket* pserver = CServerSocket::getInstance();//
//CServerSocket server;//server��������main��������ǰ���죬main�������ú�����
//��������ʹ��CServerSocket�������