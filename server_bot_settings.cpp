#include "sleepy_discord/sleepy_discord.h"

#include "server_bot_settings.hpp"

ServerBotSettings::ServerBotSettings() {
	logsChannel = SleepyDiscord::Snowflake<SleepyDiscord::Channel>();
	botAdminRole = SleepyDiscord::Snowflake<SleepyDiscord::Role>();
	//mutedUsers = std::vector<SleepyDiscord::Snowflake<SleepyDiscord::User> >();
	permissions = {2, 2};
}

bool ServerBotSettings::operator==(const ServerBotSettings& acrRhs) const {
	if((silent == acrRhs.silent) && (noLogs == acrRhs.noLogs) && (prefix == acrRhs.prefix) 
		&& (logsChannel == acrRhs.logsChannel) && (botAdminRole == acrRhs.botAdminRole)
		&& (mutedUsers == acrRhs.mutedUsers) && (permissions == acrRhs.permissions)
	) {
	    return true;
	}
	else {
		return false;
	}
}

bool ServerBotSettings::operator!=(const ServerBotSettings& acrRhs) const {
	if(!operator==(acrRhs)) {
		return true;
	}
	else {
		return false;
	}
}

bool ServerBotSettingsComparator::operator()(const ServerBotSettings& acrLhs, const ServerBotSettings& acrRhs) const {
	if(acrRhs == ServerBotSettings() && acrRhs != ServerBotSettings()) {
		return 0;
	}
	else {
		return 1;
	}
}

bool ServerBotSettingsComparator::operator()(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrLhs, const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrRhs) const {
	if(acrLhs == SleepyDiscord::Snowflake<SleepyDiscord::Server>() && acrRhs != SleepyDiscord::Snowflake<SleepyDiscord::Server>()) {
		return 0;
	}
	else {
		return 1;
	}
}