#pragma once
#include "pch.h"
using namespace std;

#define LOG_INFO(fmt, ...) Singletone<Log::LogManager>::getInstance().log(Log::Type::kInfo, fmt, __VA_ARGS__); \

namespace Log
{
	enum class Type
	{
		kInfo = 0
		, kWarn
		, kError
		, kCri
		, kMax = kCri
	};

	string typeToString(Type type);

	class LogBase
	{
	public:
		LogBase() {}
		virtual ~LogBase() {}

		virtual void initialize() {}
		virtual void unInitialize() {}
		virtual void log(const char* msg) {}
	};

	class LogInfo : public LogBase
	{
	public:
		LogInfo(Type type);
		virtual ~LogInfo();

		virtual void initialize();
		virtual void unInitialize();
		virtual void log(const char* msg);
	private:
		Type type_;
		string stringType_;
		ofstream fs_;
		string fileName_;
	};

	class LogManager : Singletone<LogManager>
	{
	public:
		LogManager() {}
		virtual ~LogManager();

		void log(Type type, const char* fmt, ...);
	private:
		unordered_map<Type, LogBase*> logMap_;
	};
}
