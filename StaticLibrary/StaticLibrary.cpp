// StaticLibrary.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "Util/Lock.h"
#include "Util/Singletone.h"
#include "Util/Log.h"

int main()
{
    std::cout << "Hello World!\n";
	// LockGuard& lockGuard = Singletone<LockGuard>::getInstance();
	//LockGuard lockGuard(__FUNCTION__, __LINE__);
	LOG_INFO("test");
	int i = 3;
	LOG_INFO("i=%d", i);

	ThreadManager& tm = ThreadManager::getInstance();
	thread t1([](int cnt)
	{
		for (int i = 0; i < cnt; i++)
		{
			LOG_INFO("i=%d", i);
		}
	}, 3
	);

	LOG_INFO("test1");
	Thread tr1(t1, "t1");
	tm.put(&tr1);

	thread t2([](int cnt)
	{
		for (int i = 0; i < cnt; i++)
		{
			LOG_INFO("i=%d", i);
		}
	}, 3
	);

	LOG_INFO("test2");
	Thread tr2(t2, "t2");
	tm.put(&tr2);

	LOG_INFO("end");

	//Log::LogManager& logManager = Singletone<Log::LogManager>::getInstance(); \
	//logManager.log(Log::Type::kInfo, fmt, ...)

}