#include "DataBase.h"
#include <sqlite3.h>
#include <string>

const char* DataBase::dir = "LeaderBoard.db";
std::string DataBase::Username;
bool DataBase::IsUserAdmin = 0;

std::unordered_map<std::string, int> DataBase::Leaders;

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
		"username TEXT NOT NULL UNIQUE, "
		"pass CHAR(10) NOT NULL, "
		"maxScore INT DEFAULT 0,"
		"isAdmin BOOL DEFAULT 0);";

	int exit = 0;
	exit = sqlite3_open(dir, &DB);

	char* messageError;

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

	if (exit != SQLITE_OK)
	{
		sqlite3_free(messageError);
	}
	sqlite3_close(DB);

	return 0;
}

int DataBase::InsertAdmin()
{
	sqlite3* DB;
	char* messageError;

	int exit = sqlite3_open(dir, &DB);

	std::string sql = R"(
    INSERT INTO USERS (username, pass, maxScore, isAdmin)
    SELECT 'admin', 'admin', 0, true
    WHERE NOT EXISTS (
        SELECT 1 FROM USERS WHERE username = 'admin' AND isAdmin = true
    );
)";

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK)
	{
		sqlite3_free(messageError);
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

		std::string sql = "INSERT INTO USERS (username, pass) VALUES (?,?);";
		int rc = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);
		if (rc != SQLITE_OK)
		{
			sqlite3_close(DB);
			return 0;
		}

		sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

		rc = sqlite3_step(stmt);

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
	
	std::string sqlGet = "SELECT maxScore FROM USERS WHERE username = ?;";

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

			std::string sqlUpdate = "UPDATE USERS SET maxScore = ? WHERE USERNAME = ?;";

			exit = sqlite3_prepare_v2(DB, sqlUpdate.c_str(), -1, &stmt, nullptr);

			sqlite3_bind_text(stmt, 1, newScore.c_str(), 0 - 1, SQLITE_STATIC);
			sqlite3_bind_text(stmt, 2, username.c_str(), 0 - 1, SQLITE_STATIC);

			exit = sqlite3_step(stmt);
		}
	}
	else {
		return 0;
	}
	sqlite3_finalize(stmt);
	sqlite3_close(DB);

	return 1;
}

int DataBase::DeleteUser(std::string name)
{
	sqlite3* DB;
	sqlite3_stmt* stmt;

	int exit = sqlite3_open(dir, &DB);
	
	std::string sql("DELETE FROM USERS WHERE username = ?;");

	exit = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);

	sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);

	exit = sqlite3_step(stmt);
	
	Leaders = GetLeaders();

	return 0;
}

int DataBase::CheckPasswordByUsername(std::string username, std::string password)
{
	sqlite3* DB;
	sqlite3_stmt* stmt;

	int exit = sqlite3_open(dir, &DB);
	
	std::string sql = "SELECT username, pass, isAdmin FROM USERS WHERE username = ?;";

	exit = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);

	if (exit != SQLITE_OK)
	{
		sqlite3_close(DB);
		return 0;
	}

	sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

	if (exit = sqlite3_step(stmt))
	{
		const char* retrievedUsername = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
		const char* retrievedPass = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		const char* retrievedIsUserAdmin = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

		if (retrievedUsername == NULL || retrievedPass == NULL)
		{
			return 0;
		}


		if (password == retrievedPass)
		{
			sqlite3_finalize(stmt);
			sqlite3_close(DB);

			Username = username;
			IsUserAdmin = retrievedIsUserAdmin;
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
	auto* res = static_cast<std::unordered_map<std::string, int>*>(data);

	if (argc < 2) {
		return 1;
	}

	std::string name;
	int score = 0;

	for (int i = 0; i < argc; i++) {
		if (azColName[i] && argv[i]) {
			if (std::string(azColName[i]) == "username") {
				name = argv[i];
			}
			else if (std::string(azColName[i]) == "maxScore") {
				score = std::stoi(argv[i]);
			}
		}
	}

	(*res)[name] = score;

	return 0;
}

std::unordered_map<std::string, int>& DataBase::GetLeaders()
{
	sqlite3* DB;

	int exit = sqlite3_open(dir, &DB);

	std::string sql = "SELECT username, maxscore FROM USERS ORDER BY MAXSCORE DESC LIMIT 5;";

	Leaders.clear();

	sqlite3_exec(DB, sql.c_str(), GetLeadersCallback, &Leaders, NULL);

	sqlite3_close(DB);

	return Leaders;
}