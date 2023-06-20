#include "pch.h"
#include "Thread.h"

Thread::Thread(thread& t, string name)
	:t_(t)
	, name_(name)
{
	std::stringstream ss;
	ss << t.get_id();
	ss >> id_;
}

Thread::~Thread()
{
	t_.join();

	LOG_INFO("id:%llu name:%s", id_, name_.c_str());
}

size_t Thread::id()
{
	return id_;
}

string & Thread::name()
{
	return name_;
}

ThreadManager::ThreadManager()
{

}

ThreadManager::~ThreadManager()
{
	for (auto t : threadPool_)
	{
		LOG_INFO("id:%llu name:%s", t.second->id(), t.second->name().c_str());
	}
}

void ThreadManager::put(Thread* t)
{
	threadPool_.insert(make_pair(t->id(), t));
}

void ThreadManager::remove(size_t id)
{
	auto itor = threadPool_.find(id);
	if (itor == threadPool_.end())
		return;
	delete itor->second;
	threadPool_.erase(id);
}

Thread* ThreadManager::at(size_t id)
{
	auto itor = threadPool_.find(id);
	if (threadPool_.end() == itor)
		return nullptr;
	return itor->second;
}
