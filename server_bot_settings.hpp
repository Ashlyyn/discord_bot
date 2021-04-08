#ifndef _SERVER_BOT_SETTINGS_H_
#define _SERVER_BOT_SETTINGS_H_

#include <array>
#include <vector>
#include <string>

#include "sleepy_discord/sleepy_discord.h"

struct ServerBotSettings {
    bool silent = false;
    bool noLogs = false;
	std::string prefix = "F!";
	SleepyDiscord::Snowflake<SleepyDiscord::Channel> logsChannel;
	SleepyDiscord::Snowflake<SleepyDiscord::Role> botAdminRole;
	std::vector<SleepyDiscord::Snowflake<SleepyDiscord::User>> mutedUsers;
    std::array<int, 2> permissions = {
		2, 2
	};

	ServerBotSettings();
	bool operator==(const ServerBotSettings& acrRhs) const;
	bool operator!=(const ServerBotSettings& acrRhs) const;
};

struct ServerBotSettingsComparator {
	bool operator()(const ServerBotSettings& arcLhs, const ServerBotSettings& acrRhs) const;
	bool operator()(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrLhs, const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrRhs) const;
};

#endif