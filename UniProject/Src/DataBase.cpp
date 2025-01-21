#include "DataBase.h"
#include <sqlite3.h>
#include <string>
#include <iostream>

const char* DataBase::dir = "LeaderBoard.db";
std::string DataBase::Username;

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


int DataBase::LoginUser(std::string username, std::string password)
{
	// 1 - Success login, -1 - Incorrect password, 0 - Total fail, 2 - New User created
	int res = CheckPasswordByUsername(username, password);
	if (res == 1 || res == -1)
	{
		return res;
	}
	else if (res == 0)
	{
		sqlite3* DB;
		sqlite3_stmt* stmt;

		int exit = sqlite3_open(dir, &DB);

		std::string sql = "INSERT INTO USERS (USERNAME, PASS) VALUES (?,?);";
		int rc = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);
		if (rc != SQLITE_OK)
		{
			std::cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << '\n';
			sqlite3_close(DB);
			return 0;
		}

		sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

		rc = sqlite3_step(stmt);
		if (rc != SQLITE_DONE)
		{
			std::cerr << "Error inserting data: " << sqlite3_errmsg(DB) << '\n';
		}
		else {
			std::cout << "Data inserted successfully.\n";
		}

		sqlite3_finalize(stmt);

		sqlite3_close(DB);
		return 2;
	}

}

int DataBase::InsertNewScore(std::string username, std::string newScore)
{
	sqlite3* DB;
	sqlite3_stmt* stmt;

	int exit = sqlite3_open(dir, &DB);
	
	std::string sqlGet = "SELECT MAXSCORE FROM USERS WHERE USERNAME = ?;";

	exit = sqlite3_prepare_v2(DB, sqlGet.c_str(), -1, &stmt, nullptr);

	sqlite3_bind_text(stmt, 1, username.c_str(), 0 - 1, SQLITE_STATIC);

	exit = sqlite3_step(stmt);

	if (exit)
	{
		const char* oldScore = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));

		if (oldScore > newScore)
		{
			return 1;
		}
		else {
			sqlite3_finalize(stmt);

			std::string sqlUpdate = "UPDATE USERS SET MAXSCORE = ? WHERE USERNAME = ?;";

			exit = sqlite3_prepare_v2(DB, sqlUpdate.c_str(), -1, &stmt, nullptr);

			sqlite3_bind_text(stmt, 1, newScore.c_str(), 0 - 1, SQLITE_STATIC);
			sqlite3_bind_text(stmt, 2, username.c_str(), 0 - 1, SQLITE_STATIC);

			exit = sqlite3_step(stmt);

			if (exit == SQLITE_OK)
			{
				std::cout << "Success\n";
			}
			else {
				std::cout << "no Success\n";
			}
		}
	}
	else {
		return 0;
	}
	sqlite3_finalize(stmt);
	sqlite3_close(DB);

	return 1;
}

int DataBase::DeleteData()
{
	sqlite3* DB;

	int exit = sqlite3_open(dir, &DB);
	
	std::string sql("DELETE FROM USERS;");

	sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);

	return 0;
}

int DataBase::CheckPasswordByUsername(std::string username, std::string password)
{
	sqlite3* DB;
	sqlite3_stmt* stmt;

	int exit = sqlite3_open(dir, &DB);
	
	std::string sql = "SELECT USERNAME, PASS FROM USERS WHERE USERNAME = ?;";

	exit = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);

	if (exit != SQLITE_OK)
	{
		std::cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << '\n';
		sqlite3_close(DB);
		return 0;
	}

	sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

	if (exit = sqlite3_step(stmt))
	{
		const char* retrievedUsername = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
		const char* retrievedPass = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

		if (retrievedUsername == NULL || retrievedPass == NULL)
		{
			return 0;
		}


		if (password == retrievedPass)
		{
			sqlite3_finalize(stmt);
			sqlite3_close(DB);

			Username = username;

			return 1;
		}
		else {
			return -1;
		}
	}

	sqlite3_finalize(stmt);
	sqlite3_close(DB);
	return 0;

}

int DataBase::GetLeadersCallback(void* data, int argc, char** argv, char** azColName)
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

	std::string sql = "SELECT USERNAME, MAXSCORE FROM USERS ORDER BY MAXSCORE DESC LIMIT 5;";

	Leaders.clear();

	sqlite3_exec(DB, sql.c_str(), GetLeadersCallback, &Leaders, NULL);

	sqlite3_close(DB);

	return Leaders;
}

int DataBase::callback(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
	{
		std::cout << azColName[i] << " : " << argv[i] << '\n';
	}
	return 0;
}
