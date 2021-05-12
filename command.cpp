#include "command.hpp"
#include "bot_client.hpp"

#include "sleepy_discord/sleepy_discord.h"

bool Command::isOwner(const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID) {
	if (acrUserID == MyClientClass::s_ownerID) {
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
	std::mutex mutex;
	std::lock_guard lock(mutex);

	assert(m_client->m_serverBotSettings.at(acrServerID).permissions[m_commandType] != MyClientClass::COMMAND_PERMISSION::ERR);

	// if server's permissions for command's command type is owner only and user is owner
	if(m_client->m_serverBotSettings.at(acrServerID).permissions[m_commandType] == MyClientClass::COMMAND_PERMISSION::OWNER_ONLY && isOwner(acrUser.ID)) {
    	return true;
	} 
	// else if server's permissions for command's command type is set to admin role and user has role
    else if (((m_client->m_serverBotSettings.at(acrServerID).permissions[m_commandType] == MyClientClass::COMMAND_PERMISSION::BOT_ADMIN) && (hasRole(m_client->m_servers.at(acrServerID), acrUser.ID, m_client->m_serverBotSettings.at(acrServerID).botAdminRoleID))) || isOwner(acrUser.ID)) {
		return true;
    }
	// else if server's permissions for command's command type is set to all
    else if (m_client->m_serverBotSettings.at(acrServerID).permissions[m_commandType] == MyClientClass::COMMAND_PERMISSION::CMD_ALL) {
    	return true;
	}
    else {
	    return false;
	}
}