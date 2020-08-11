#pragma once

#include <mysql++11.h>

#include "IDatabase.h"

#pragma comment(lib, "mysqlclient.lib")

class MySql : public IDatabase
{
public:
	explicit MySql(std::string server, std::string username, std::string password, std::string db_name,
		std::string table_players, std::string table_groups)
		: table_players_(move(table_players)),
		table_groups_(move(table_groups))
	{
		try
		{
			daotk::mysql::connect_options options;
			options.server = move(server);
			options.username = move(username);
			options.password = move(password);
			options.dbname = move(db_name);
			options.autoreconnect = true;
			options.timeout = 30;

			bool result = db_.open(options);
			if (!result)
			{
				Log::GetLog()->critical("Failed to open connection!");
				return;
			}

			result = db_.query(fmt::format("CREATE TABLE IF NOT EXISTS {} ("
				"Id INT NOT NULL AUTO_INCREMENT,"
				"SteamId BIGINT(11) NOT NULL,"
				"PermissionGroups VARCHAR(256) NOT NULL DEFAULT 'Default,',"
				"PRIMARY KEY(Id),"
				"UNIQUE INDEX SteamId_UNIQUE (SteamId ASC));", table_players_));

			if (!result)
			{
				Log::GetLog()->critical("({} {}) Failed to create table!", __FILE__, __FUNCTION__);
			}
		}
		catch (const std::exception & exception)
		{
			Log::GetLog()->critical("({} {}) Unexpected DB error {}", __FILE__, __FUNCTION__, exception.what());
		}
	}

	bool AddPlayer(uint64 steam_id) override
	{
		try
		{
			return db_.query(fmt::format("INSERT INTO {} (SteamId) VALUES ({});", table_players_, steam_id));
		}
		catch (const std::exception & exception)
		{
			Log::GetLog()->error("({} {}) Unexpected DB error {}", __FILE__, __FUNCTION__, exception.what());
			return false;
		}
	}

	bool IsPlayerExists(uint64 steam_id) override
	{
		try
		{
			const auto result = db_.query(fmt::format("SELECT count(1) FROM {} WHERE SteamId = {};", table_players_,
				steam_id))
				.get_value<int>();
			return result > 0;
		}
		catch (const std::exception & exception)
		{
			Log::GetLog()->error("({} {}) Unexpected DB error {}", __FILE__, __FUNCTION__, exception.what());
			return false;
		}
	}

	bool IsGroupExists(const FString& group) override
	{
		try
		{
			const auto result = db_.query(fmt::format("SELECT count(1) FROM {} WHERE GroupName = '{}';", table_groups_,
				group.ToString()))
				.get_value<int>();

			return result > 0;
		}
		catch (const std::exception & exception)
		{
			Log::GetLog()->error("({} {}) Unexpected DB error {}", __FILE__, __FUNCTION__, exception.what());
		}

		return false;
	}

	std::optional<std::string> AddGroup(const FString& group) override
	{
		if (IsGroupExists(group))
			return "Group already exists";

		try
		{
			const bool res = db_.query(fmt::format("INSERT INTO {} (GroupName) VALUES ('{}');", table_groups_,
				group.ToString()));
			if (!res)
			{
				return "Unexpected DB error";
			}
		}
		catch (const std::exception & exception)
		{
			Log::GetLog()->error("({} {}) Unexpected DB error {}", __FILE__, __FUNCTION__, exception.what());
			return "Unexpected DB error";
		}

		return {};
	}


private:
	daotk::mysql::connection db_;
	std::string table_players_;
	std::string table_groups_;
};
