#include "command.hpp"
#include "bot_client.hpp"

#include "sleepy_discord/sleepy_discord.h"

bool Command::isOwner(const SleepyDiscord::Snowflake<SleepyDiscord::User>& user) {
	if (user == 518216114665291786) {
		return true;
	}
	else {
		return false;
	}
}

bool Command::hasRole(const SleepyDiscord::ServerMember& member, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& role) {
	for (const auto& memberRole : member.roles) {
	    if (memberRole == role) {
            return true;
		}
	}
	return false;
}

bool Command::checkPermissions(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::ServerMember& member) const {
	if(m_client->m_serverBotSettings[server].permissions[m_commandType] == MyClientClass::COMMAND_PERMISSION::OWNER_ONLY && isOwner(member.user.ID)) {
    	return true;
	} 
    else if ((m_client->m_serverBotSettings[server].permissions[m_commandType] == MyClientClass::COMMAND_PERMISSION::BOT_ADMIN && hasRole(member, m_client->m_serverBotSettings[server].botAdminRole)) || isOwner(member.user.ID)) {
		return true;
    }
    else if (m_client->m_serverBotSettings[server].permissions[m_commandType] == MyClientClass::COMMAND_PERMISSION::CMD_ALL) {
    	return true;
	}
    else {
	    return false;
	}
}