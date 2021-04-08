#include "sleepy_discord/sleepy_discord.h"

#include "server_bot_settings.hpp"

ServerBotSettings::ServerBotSettings() {
	logsChannel = SleepyDiscord::Snowflake<SleepyDiscord::Channel>();
	SleepyDiscord::Snowflake<SleepyDiscord::Role>();
	std::vector<SleepyDiscord::Snowflake<SleepyDiscord::User> >();
}

bool ServerBotSettings::operator==(const ServerBotSettings& rhs) const {
	if((silent == rhs.silent) && (noLogs == rhs.noLogs) && (prefix == rhs.prefix) 
		&& (logsChannel == rhs.logsChannel) && (botAdminRole == rhs.botAdminRole)
		&& (mutedUsers == rhs.mutedUsers) && (permissions == rhs.permissions)
	) {
	    return true;
	}
	else {
		return false;
	}
}

bool ServerBotSettings::operator!=(const ServerBotSettings& rhs) const {
	if(!operator==(rhs)) {
		return true;
	}
	else {
		return false;
	}
}

bool ServerBotSettingsComparator::operator()(const ServerBotSettings& lhs, const ServerBotSettings& rhs) const {
	if(lhs == ServerBotSettings() && rhs != ServerBotSettings()) {
		return 0;
	}
	else {
		return 1;
	}
}

bool ServerBotSettingsComparator::operator()(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& lhs, const SleepyDiscord::Snowflake<SleepyDiscord::Server>& rhs) const {
	if(lhs == SleepyDiscord::Snowflake<SleepyDiscord::Server>() && rhs != SleepyDiscord::Snowflake<SleepyDiscord::Server>()) {
		return 0;
	}
	else {
		return 1;
	}
}