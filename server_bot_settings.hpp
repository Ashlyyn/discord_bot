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
	std::vector<SleepyDiscord::Snowflake<SleepyDiscord::ServerMember> > mutedUsers;
    std::array<int, 2> permissions = {
		2, 2
	};

	ServerBotSettings();
	bool operator==(const ServerBotSettings& rhs) const;
	bool operator!=(const ServerBotSettings& rhs) const;
};

struct ServerBotSettingsComparator {
	bool operator()(const ServerBotSettings& lhs, const ServerBotSettings& rhs) const;
	bool operator()(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& lhs, const SleepyDiscord::Snowflake<SleepyDiscord::Server>& rhs) const;
};

#endif