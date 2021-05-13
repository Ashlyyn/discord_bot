#include "command.hpp"
#include "bot_client.hpp"

#include "sleepy_discord/sleepy_discord.h"

bool Command::checkPermissions(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID) const {
	std::mutex mutex;
	std::lock_guard lock(mutex);

	assert(m_client->m_serverBotSettings.at(acrServerID).permissions[m_commandType] != MyClientClass::COMMAND_PERMISSION::PERM_ERR);

	SleepyDiscord::User lUser = m_client->getUser(acrUserID);
	// if server's permissions for command's command type is owner only and user is owner
	if(m_client->m_serverBotSettings.at(acrServerID).permissions[m_commandType] == MyClientClass::COMMAND_PERMISSION::OWNER_ONLY && MyClientClass::isOwner(acrUserID)) {
    	return true;
	} 
	// else if server's permissions for command's command type is set to admin role and user has role
    else if (((m_client->m_serverBotSettings.at(acrServerID).permissions[m_commandType] == MyClientClass::COMMAND_PERMISSION::BOT_ADMIN) && (m_client->hasRole(m_client->m_servers.at(acrServerID), acrUserID, m_client->m_serverBotSettings.at(acrServerID).botAdminRoleID))) || MyClientClass::isOwner(acrUserID)) {
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