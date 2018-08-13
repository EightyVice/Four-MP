#pragma once

#define LOG_NONE	0x0
#define LOG_ON		0x1
#define LOG_DEBUG	0x2
#define LOG_INFO	0x4
#define LOG_ERROR	0x8
#define LOG_WARNING 0x10

class Logger
{
public:
	virtual void Log(const wchar_t *type, const wchar_t *string, char*) = 0;
	virtual void Log(const char *type, const char *string, char*) = 0;
};

namespace Log
{
	void AddLogger(Logger* iLog);
	void SetState(unsigned int state);

	void Debug(const wchar_t *string, ...);
	void Info(const wchar_t *string, ...);
	void Error(const wchar_t *string, ...);
	void Warning(const wchar_t *string, ...);
	void Other(const wchar_t *type, const wchar_t *string, ...);
	void Void(const wchar_t *string, ...);

	void Debug(const char *string, ...);
	void Info(const char *string, ...);
	void Error(const char *string, ...);
	void Warning(const char *string, ...);
	void Other(const char *type, const char *string, ...);
	void Void(const char *string, ...);
}
