#pragma once
#include <afxsock.h> 
//

class Socket1 :public CAsyncSocket {
public:
	Socket1();
	virtual ~Socket1();
	virtual void OnReceive(int nErrorCode);
	//主要用到的就是这个函数
};