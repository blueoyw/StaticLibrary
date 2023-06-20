#include "pch.h"
#include "Log.h"

using namespace Log;

LogInfo::LogInfo(Type type)
	: type_(type)
{
	cout << "LogInfo constructor\n";
	stringType_ = typeToString(type_);
	initialize();
}

LogInfo::~LogInfo()
{
	cout << "LogInfo destructor\n";
	unInitialize();
}

void LogInfo::initialize()
{
	cout << "LogInfo initialzie\n";

	fileName_ = "./Log/test.log";

	fs_.open(fileName_.c_str(), ios::app);
	if (fs_.is_open() == false)
	{
		cout << fileName_.c_str() << " open fila.\n";
		return;
	}
	fs_ << "initialize() \n";
}

void LogInfo::unInitialize()
{
	cout << "LogInfo unInitialzie\n";
	fs_.close();
}

void LogInfo::log(const char * msg)
{
	char log[1024] = { 0, };

	std::time_t t = std::time(nullptr);
	std::tm* now = std::localtime(&t);

	char buffer[128];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %X", now);

	fs_ << "[" << buffer << "] ";
	cout << stringType_.c_str() << "[" << buffer << "] ";
	cout << "(tid=" << std::this_thread::get_id() << ")";

	fs_ << msg << "\n";
	cout << msg << "\n";
}

Log::LogManager::~LogManager()
{
	for (auto itor : logMap_)
	{
		delete itor.second;
	}
}

void Log::LogManager::log(Type type, const char * fmt, ...)
{
	const int kBufSize = 1024;
	va_list args;
	va_start(args, fmt);
	char buf[kBufSize] = { 0, };
	vsnprintf(buf, kBufSize, fmt, args);
	va_end(args);

	auto itor = logMap_.find(type);
	if (itor == logMap_.end())
	{
		switch (type)
		{
		case Type::kInfo:
		{
			LogBase* base = new LogInfo(type);
			auto itor = logMap_.insert(make_pair(type, base));
			dynamic_cast<LogInfo*>(base)->log(buf);
		}
		break;
		default:
			break;
		}
	}
	else
	{
		switch (type)
		{
		case Type::kInfo:
		{
			dynamic_cast<LogInfo*>(itor->second)->log(buf);
		}
		break;
		default:
			break;
		}
	}
}

string Log::typeToString(Type type)
{
	string rtn = "None";
	switch (type)
	{
	case Type::kInfo: rtn = "Info"; break;
	case Type::kWarn: rtn = "Warn"; break;
	case Type::kError: rtn = "Error"; break;
	case Type::kCri: rtn = "Cri"; break;
	}
	return rtn;
}
