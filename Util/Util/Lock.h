#pragma once
#include "pch.h"
using namespace std;

class Lock
{
public:
	Lock(const char* name, uint32 line);
	virtual ~Lock();

	const string& name();
	uint64 id();
	void setThreadId(int32 id);
	
	void lock();
	void unlock();
	
private:
	mutex lock_;
	string name_;
	int line_;
	uint64 id_;
};

class LockGuard
{
public:
	LockGuard(const char* name, uint32 line);
	virtual ~LockGuard();
private:
	Lock lock_;
};