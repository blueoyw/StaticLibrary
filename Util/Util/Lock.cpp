#include "pch.h"
#include "Lock.h"

using namespace std;

Lock::Lock(const char* name, uint32 line)
{
	name_ = string(name);
	line_ = line;
	cout << "construct name=" << name_.c_str() << " line="<< line_ <<"\n";
}

Lock::~Lock()
{
	cout << "destructor name=" << name_.c_str() << " line=" << line_ << "\n";
}

const string & Lock::name()
{
	return name_;
}

uint64 Lock::id()
{
	return id_;
}

void Lock::setThreadId(int32 id)
{
	id_ = id;
	cout << "set id=" << id << "\n";
}

void Lock::lock()
{
	cout << "lock name=" << name_.c_str() << " line=" << line_ << "\n";
	lock_.lock();
}

void Lock::unlock()
{
	lock_.unlock();
	cout << "unlock name=" << name_.c_str() << " line=" << line_ << "\n";

	name_.clear();
	line_ = kInvalidLine;
}

LockGuard::LockGuard(const char* name, uint32 line)
	: lock_(name, line)
{
	lock_.lock();
}

LockGuard::~LockGuard()
{
	lock_.unlock();
}
