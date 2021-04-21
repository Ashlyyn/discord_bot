#include "sleepy_discord/sleepy_discord.h"

#include "server_bot_settings.hpp"

ServerBotSettings::ServerBotSettings() {
	// initialize variables
	logsChannelID = SleepyDiscord::Snowflake<SleepyDiscord::Channel>();
	botAdminRoleID = SleepyDiscord::Snowflake<SleepyDiscord::Role>();
	permissions = {2, 2};
}

bool ServerBotSettings::operator==(const ServerBotSettings& acrRhs) const {
	if((silent == acrRhs.silent) && (noLogs == acrRhs.noLogs) && (prefix == acrRhs.prefix) 
		&& (logsChannelID == acrRhs.logsChannelID) && (botAdminRoleID == acrRhs.botAdminRoleID)
		&& (mutedUserIDs == acrRhs.mutedUserIDs) && (permissions == acrRhs.permissions)
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