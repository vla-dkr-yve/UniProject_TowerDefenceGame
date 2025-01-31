#pragma once
#include <string>
#include<unordered_map>
class DataBase
{
private:
	static const char* dir;
	
public:
	static std::string Username;
	static bool IsUserAdmin;

	static std::unordered_map<std::string, int> Leaders;

	static int CreateDB();
	static int CreateTable();
	static int InsertAdmin();
	static int CheckPasswordByUsername(std::string username, std::string password);
	static int LoginUser(std::string username, std::string password);
	static int InsertNewScore(std::string username, std::string newScore);
	static int DeleteUser(std::string name);
	static std::unordered_map<std::string, int>& GetLeaders();
	static int GetLeadersCallback(void* data, int argc, char** argv, char** azColName);
};

