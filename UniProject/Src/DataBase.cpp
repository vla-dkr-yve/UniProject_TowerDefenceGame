#include "DataBase.h"
#include <sqlite3.h>
#include <string>
#include <iostream>

const char* DataBase::dir = "LeaderBoard.db";

std::vector<std::string> DataBase::Leaders;

int DataBase::CreateDB()
{
	sqlite3* DB;
	int exit = 0;

	exit = sqlite3_open(dir, &DB);
	
	sqlite3_close(DB);

	return 0;
}

int DataBase::CreateTable()
{
	sqlite3* DB;

	std::string sql = "CREATE TABLE IF NOT EXISTS USERS("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"USERNAME TEXT NOT NULL UNIQUE, "
		"PASS CHAR(10) NOT NULL, "
		"MAXSCORE INT DEFAULT 0);";

	try
	{
		int exit = 0;
		exit = sqlite3_open(dir, &DB);

		char* messageError;

		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

		if (exit != SQLITE_OK)
		{
			std::cerr << "Error Create Table\n";
			sqlite3_free(messageError);
		}
		else {
			std::cout << "Table created Succesfully\n";
		}
		sqlite3_close(DB);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}


	return 0;
}

int DataBase::InsertData()
{
	sqlite3* DB;
	char* messageError;

	int exit = sqlite3_open(dir, &DB);

	std::string sql = "INSERT INTO USERS (USERNAME, PASS, MAXSCORE) VALUES ('Anybis', '1111', 100);";

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK)
	{
		std::cerr << "Error Insert\n";
		sqlite3_free(messageError);
	}
	else {
		std::cout << "Records created Succesfully";
	}

	return 0;
}

int DataBase::UpdateData()
{
	sqlite3* DB;
	char* messageError;

	int exit = sqlite3_open(dir, &DB);

	std::string sql("UPDATE USERS SET MAXSCORE = 200 WHERE USERNAME = 'Anybis';");

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

	if (exit != SQLITE_OK)
	{
		std::cerr << "Error Update\n";
		sqlite3_free(messageError);
	}
	else {
		std::cout << "Records updated succesfully\n";
	}


	return 0;
}


int DataBase::DeleteData()
{
	sqlite3* DB;

	int exit = sqlite3_open(dir, &DB);

	std::string sql("DELETE FROM USERS;");
	sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);

	return 0;
}

//int DataBase::SelectData()
//{
//	sqlite3* DB;
//
//	int exit = sqlite3_open(dir, &DB);
//	
//	std::string sql = "SELECT * FROM USERS;";
//
//	sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);
//	return 0;
//}

int DataBase::callback(void* data, int argc, char** argv, char** azColName)
{
	auto* res = static_cast<std::vector<std::string>*>(data);

	std::string row;
	for (int i = 0; i < argc; i++)
	{
		if (argv)
		{
			row += azColName[i];
			row += " : ";
			row += argv[i];
			row += " | ";
		}
		else {
			row += azColName[i];
			row += " : NULL | ";
		}
	}

	res->push_back(row);
	return 0;
}

std::vector<std::string>& DataBase::GetLeaders()
{
	sqlite3* DB;

	int exit = sqlite3_open(dir, &DB);

	std::string sql = "SELECT USERNAME, MAXSCORE FROM USERS;";

	Leaders.clear();

	sqlite3_exec(DB, sql.c_str(), callback, &Leaders, NULL);

	return Leaders;
}
