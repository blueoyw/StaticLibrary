#pragma once
#include "pch.h"

using namespace std;

class Thread
{
public:
	Thread(thread& t, string name);
	virtual ~Thread();

	size_t id();
	string& name();
private:
	size_t id_;
	string name_;
	thread& t_;
};

class ThreadManager : public Singletone<ThreadManager>
{
public:
	ThreadManager();
	virtual ~ThreadManager();

	void put(Thread* t);
	void remove(size_t id);
	Thread* at(size_t id);
private:
	unordered_map<size_t, Thread*> threadPool_;
};

