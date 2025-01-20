#pragma once
#include <vector>
#include <string>
class DataBase
{
private:
	static const char* dir;
	
public:
	static std::string Username;

	static std::vector<std::string> Leaders;

	static int CreateDB();
	static int CreateTable();
	static int InsertData();
	static int UpdateData();
	static int CheckPasswordByUsername(std::string username, std::string password);
	static int LoginUser(std::string username, std::string password);
	static int DeleteData();
	static std::vector<std::string>& GetLeaders();
	static int callback(void* data, int argc, char** argv, char** azColName);
	static int GetLeadersCallback(void* data, int argc, char** argv, char** azColName);
	//static int callbackLeaders(void* NotUsed, int argc, char** argv, char** azColName, std::string& text);
};

