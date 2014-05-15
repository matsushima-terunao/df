// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: プログラムに必要な追加ヘッダーをここで参照してください。

#include <string>
#include <Windows.h>

#define fopen my_fopen

static FILE* my_fopen(const char* path, const char* mode)
{
	FILE* fp;
	fopen_s(&fp, path, mode);
	return fp;
}

class Reader
{
private:
	FILE* fp;
public:
	Reader(const char* path)
	{
		this->fp = fopen(path, "rt");
	}
	void close()
	{
		fclose(fp);
	}
	const char* readLine(std::string& buf)
	{
		buf.clear();
		if (0 != feof(fp))
		{
			return NULL;
		}
		int c;
		while (EOF != (c = fgetc(fp)))
		{
			if ('\n' == c)
			{
				break;
			}
			buf += (char)c;
		}
		return buf.c_str();
	}
};

class Log
{
public:
	bool debugEnabled;
	Log(bool debugEnabled)
	{
		this->debugEnabled = debugEnabled;
	}
	void trace(const char* msg) const
	{
		if (debugEnabled)
		{
			print(msg);
		}
	}
	void trace(std::string& msg) const
	{
		trace(msg.c_str());
	}
	void debug(const char* msg) const
	{
		if (debugEnabled)
		{
			print(msg);
		}
	}
	void debug(std::string& msg) const
	{
		debug(msg.c_str());
	}
	void error(const char* msg) const
	{
		print(msg);
	}
	void error(std::string& msg) const
	{
		error(msg.c_str());
	}
protected:
	void print(const char* msg) const
	{
		//printf("%s\n", msg);
		OutputDebugStringA(msg);
		OutputDebugStringA("\n");
	}
};

class LogE : public Log
{
public:
	LogE() : Log(true) {}
};

static std::string str(int value)
{
	char buf[10];
	sprintf_s(buf, "%d", value);
	return std::string(buf);
}
