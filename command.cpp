#include "command.hpp"
#include "bot_client.hpp"

#include "sleepy_discord/sleepy_discord.h"

bool Command::isOwner(const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID) {
	if (acrUserID == 518216114665291786) {
		return true;
	}
	else {
		return false;
	}
}

bool Command::hasRole(SleepyDiscord::Server& arServer, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& acrRoleID) {
	const SleepyDiscord::ServerMember& lcrMember = *arServer.findMember(acrUserID);
	for (const auto& lMemberRoleID : lcrMember.roles) {
	    if (lMemberRoleID == acrRoleID) {
            return true;
		}
	}
	return false;
}

bool Command::checkPermissions(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::User& acrUser) const {
	if(m_client->m_serverBotSettings[acrServerID].permissions[m_commandType] == MyClientClass::COMMAND_PERMISSION::OWNER_ONLY && isOwner(acrUser.ID)) {
    	return true;
	} 
    else if (((m_client->m_serverBotSettings[acrServerID].permissions[m_commandType] == MyClientClass::COMMAND_PERMISSION::BOT_ADMIN) && (hasRole(m_client->m_servers.at(acrServerID), acrUser, m_client->m_serverBotSettings[acrServerID].botAdminRoleID))) || isOwner(acrUser.ID)) {
		return true;
    }
    else if (m_client->m_serverBotSettings[acrServerID].permissions[m_commandType] == MyClientClass::COMMAND_PERMISSION::CMD_ALL) {
    	return true;
	}
    else {
	    return false;
	}
}