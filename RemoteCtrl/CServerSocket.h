#pragma once
#include"pch.h"
#include"framework.h"

class CServerSocket
{
public:
	static CServerSocket* getInstance() {
		if (m_Instance == NULL) {
			m_Instance = new CServerSocket();
		}
		return m_Instance;
	}
	bool InitSocket() {
		
		if (m_sock == -1) return false;
		sockaddr_in serv_adr;
		int adr_len = sizeof(serv_adr);
		memset(&serv_adr, 0, sizeof(serv_adr));
		serv_adr.sin_family = AF_INET;
		serv_adr.sin_addr.s_addr = INADDR_ANY;
		serv_adr.sin_port = htons(9527);
		//bind
		if (bind(m_sock, (sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)return false;

		if (listen(m_sock, 1) == -1)return false;
		return true;
	}
	bool AcceptClient() {
		sockaddr_in client_adr;
		int adr_len = sizeof(client_adr);
		SOCKET m_client = accept(m_sock, (sockaddr*)&client_adr, &adr_len);//TODO:check return value
		if (m_client == -1) { return false; }
		return true;
	}
	int DealCommand() {
		if (m_client == -1)return false;
		char buffer[1024]="";
		while (true) {
			int len = recv(m_client, buffer, sizeof(buffer), 0);
			if (len <= 0) { return -1; }
		}
		//TODO:处理命令
	}
	bool Send(const char* pData, int nSize) {
		if (m_client == -1) { return false; }
		return send(m_client, pData, nSize, 0) > 0;
	}
private:
	SOCKET m_sock,m_client;
	static CServerSocket* m_Instance;//这里只是声明，需要另外定义
	CServerSocket& operator = (const CServerSocket & ss){}
	CServerSocket(const CServerSocket& ss){
		m_sock = ss.m_sock;
		m_client = ss.m_client;
	}
	CServerSocket() {

		m_client = INVALID_SOCKET;//-1
		if (InitSockEnv() == FALSE) {
			MessageBox(NULL, _T("can't initialize socket environment,please check network setting."), _T("initialize error."), MB_OK | MB_ICONERROR);
			exit(0);
		}
		m_sock = socket(PF_INET, SOCK_STREAM, 0);
	}
	~CServerSocket() {
		
		closesocket(m_sock);
		WSACleanup();
		
	}
	BOOL InitSockEnv() {
		WSADATA data;
		if (WSAStartup(MAKEWORD(1, 1), &data) != 0) {
			return FALSE;
		}
		return TRUE;
	}
	static void releaseInstance() {
		if (m_Instance != NULL) {
			CServerSocket* tmp = m_Instance;
			m_Instance = NULL;
			delete tmp;
		}
	}
	class CHelper {//CHelper用于确保CServerSocket对象被析构
	public:
		CHelper() {
			CServerSocket::getInstance();
		}
		~CHelper() {
			CServerSocket::releaseInstance();
		}
	};
	static CHelper m_chelper;
};
extern CServerSocket server;
