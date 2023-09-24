#include "pch.h"
#include "CServerSocket.h"

CServerSocket* CServerSocket::m_Instance = NULL;//
CServerSocket::CHelper CServerSocket::m_chelper;//不使用new创建对象，让系统自动调用CHelper析构函数从而析构CServerSocket对象

CServerSocket* pserver = CServerSocket::getInstance();//
//CServerSocket server;//server变量会在main函数调用前构造，main函数调用后析构
//不能随意使用CServerSocket定义变量