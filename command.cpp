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

bool Command::hasRole(SleepyDiscord::Server& arServer, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& acrRole) {
	const SleepyDiscord::ServerMember& lcrMember = *arServer.findMember(acrUser);
	for (const auto& lMemberRole : lcrMember.roles) {
	    if (lMemberRole == acrRole) {
            return true;
		}
	}
	return false;
}

bool Command::checkPermissions(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServer, const SleepyDiscord::User& acrUser) const {
	if(m_client->m_serverBotSettings[acrServer].permissions[m_commandType] == MyClientClass::COMMAND_PERMISSION::OWNER_ONLY && isOwner(acrUser.ID)) {
    	return true;
	} 
    else if (((m_client->m_serverBotSettings[acrServer].permissions[m_commandType] == MyClientClass::COMMAND_PERMISSION::BOT_ADMIN) && (hasRole(m_client->m_servers.at(acrServer), acrUser, m_client->m_serverBotSettings[acrServer].botAdminRole))) || isOwner(acrUser.ID)) {
		return true;
    }
    else if (m_client->m_serverBotSettings[acrServer].permissions[m_commandType] == MyClientClass::COMMAND_PERMISSION::CMD_ALL) {
    	return true;
	}
    else {
	    return false;
	}
}