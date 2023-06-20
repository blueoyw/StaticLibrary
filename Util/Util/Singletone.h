#pragma once
#include "pch.h"

template <class T>
class Singletone
{
public: 
	static T& getInstance()
	{
		static T instance;
		return instance;
	}

	Singletone(const Singletone&) = delete;
	Singletone& operator=(const Singletone&) = delete;

protected : 
	Singletone() {}
	virtual ~Singletone() {}
};

