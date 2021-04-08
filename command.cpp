#include "command.hpp"
#include "bot_client.hpp"

#include "sleepy_discord/sleepy_discord.h"

bool Command::isOwner(const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUser) {
	if (acrUser == 518216114665291786) {
		return true;
	}
	else {
		return false;
	}
}

bool Command::hasRole(const SleepyDiscord::ServerMember& acrMember, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& acrRole) {
	for (const auto& lMemberRole : acrMember.roles) {
	    if (lMemberRole == acrRole) {
            return true;
		}
	}
	return false;
}

bool Command::checkPermissions(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServer, const SleepyDiscord::ServerMember& acrMember) const {
	if(m_client->m_serverBotSettings[arServer].permissions[m_commandType] == MyClientClass::COMMAND_PERMISSION::OWNER_ONLY && isOwner(acrMember.user.ID)) {
    	return true;
	} 
    else if ((m_client->m_serverBotSettings[arServer].permissions[m_commandType] == MyClientClass::COMMAND_PERMISSION::BOT_ADMIN && hasRole(acrMember, m_client->m_serverBotSettings[arServer].botAdminRole)) || isOwner(acrMember.user.ID)) {
		return true;
    }
    else if (m_client->m_serverBotSettings[arServer].permissions[m_commandType] == MyClientClass::COMMAND_PERMISSION::CMD_ALL) {
    	return true;
	}
    else {
	    return false;
	}
}