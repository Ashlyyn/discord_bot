#ifndef _SERVER_BOT_SETTINGS_H_
#define _SERVER_BOT_SETTINGS_H_

#include <array>
#include <vector>
#include <string>

#include "sleepy_discord/sleepy_discord.h"

struct ServerBotSettings {
    bool silent = false; // don't send any messages
    bool noLogs = false; // don't log anything
	std::string prefix = "F!";
	SleepyDiscord::Snowflake<SleepyDiscord::Channel> logsChannelID; // channel for logs - set with setLogsChannel()/F!logs <channelID>
	SleepyDiscord::Snowflake<SleepyDiscord::Role> botAdminRoleID; // ID of role that allows user to execute admin commands
	std::vector<SleepyDiscord::Snowflake<SleepyDiscord::User>> mutedUserIDs; // IDs of users text muted
    std::array<int, 2> permissions = { // permissions for admin and non-admin commands
		2, 2
	};

	ServerBotSettings(); // base constructor
	bool operator==(const ServerBotSettings& acrRhs) const;
	bool operator!=(const ServerBotSettings& acrRhs) const;
};

struct ServerBotSettingsComparator {
	bool operator()(const ServerBotSettings& arcLhs, const ServerBotSettings& acrRhs) const;
	bool operator()(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrLhs, const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrRhs) const;
};

#endif