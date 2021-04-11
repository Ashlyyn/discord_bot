#include "bot_client.hpp"
#include "mention.hpp"

void MyClientClass::onMessage(SleepyDiscord::Message aMessage) {
	const std::string& lcrPrefix = m_serverBotSettings[aMessage.serverID].prefix;
	if (aMessage.startsWith(lcrPrefix + "prefix ")) {
		changePrefix(aMessage.serverID, aMessage.author, aMessage.channelID, aMessage.content.substr(lcrPrefix.size() + strlen("prefix ")));
	} else if (aMessage.startsWith(lcrPrefix + "hello")) {
		hello(aMessage.serverID, aMessage.author, aMessage.channelID);
	} else if (aMessage.startsWith(lcrPrefix + "echo ")) {
		echo(aMessage.serverID, aMessage.author, aMessage.channelID, aMessage.content.substr(lcrPrefix.size() + strlen("echo ")));
	} else if (aMessage.startsWith(lcrPrefix + "mute voice ")) {
		muteVoice(aMessage.serverID, aMessage.author, aMessage.content.substr(lcrPrefix.size() + strlen("mute voice ")));
	} else if (aMessage.startsWith(lcrPrefix + "unmute voice ")) {
		unmuteVoice(aMessage.serverID, aMessage.author, aMessage.content.substr(lcrPrefix.size() + strlen("unmute voice ")));
	} else if (aMessage.startsWith(lcrPrefix + "mute text ")) {
		muteText(aMessage.serverID, aMessage.author, getSnowflake(aMessage.content.substr(lcrPrefix.size() + strlen("mute text "))));
	} else if (aMessage.startsWith(lcrPrefix + "unmute text ")) {
		unmuteText(aMessage.serverID, aMessage.author, getSnowflake(aMessage.content.substr(lcrPrefix.size() + strlen("unmute text "))));
	} else if (aMessage.startsWith(lcrPrefix + "bot_admin_role set ")) {
		setBotAdminRole(aMessage.serverID, aMessage.author, getSnowflake(aMessage.content.substr(lcrPrefix.size() + strlen("bot_admin_role set "))));
	} else if (aMessage.startsWith(lcrPrefix + "nologs")) {
		logsDisable(aMessage.serverID, aMessage.author);
	} else if (aMessage.startsWith(lcrPrefix + "logs disable")) {
		logsDisable(aMessage.serverID, aMessage.author);
	} else if (aMessage.startsWith(lcrPrefix + "logs enable")) {
		logsDisable(aMessage.serverID, aMessage.author, false);
	} else if (aMessage.startsWith(lcrPrefix + "logs ")) {
		setLogsChannel(aMessage.serverID, aMessage.author, SleepyDiscord::Snowflake<SleepyDiscord::Channel>(getSnowflake(aMessage.content.substr(lcrPrefix.size() + strlen("logs ")))));
	} else if (aMessage.startsWith(lcrPrefix + "silent")) {
		setSilent(aMessage.serverID, aMessage.author);
	} else if (aMessage.startsWith(lcrPrefix + "nosilent")) {
		setSilent(aMessage.serverID, aMessage.author, false);
	} else if (aMessage.startsWith(lcrPrefix + "delete ")) {
		deleteMsg(aMessage.serverID, aMessage.author, aMessage);
	} else if (aMessage.startsWith(lcrPrefix + "permissions set ")) {
		setPermissions(aMessage.serverID, aMessage.author, toCommandPerm(split(aMessage.content)[3]), toCommandType(split(aMessage.content)[2]));
	} else if (aMessage.startsWith(lcrPrefix + "die")) {
		die(aMessage.serverID, aMessage.author, aMessage.channelID);
	} else if (aMessage.startsWith(lcrPrefix + "banned_ops")) {
		bannedOps(aMessage.serverID, aMessage.author, aMessage.channelID);
	}

	else if(aMessage.startsWith(lcrPrefix)) {
		echo(aMessage.serverID, aMessage.author, aMessage.channelID, "Unknown command.");
	}

	if(isMuted(aMessage.serverID, aMessage.author.ID)) {
		deleteMsg(aMessage.serverID, aMessage.author, aMessage);
	}
}

void MyClientClass::onServer(SleepyDiscord::Server aServer) {
	m_servers[SleepyDiscord::Snowflake<SleepyDiscord::Server>(aServer)] = aServer;
}

void MyClientClass::fn_changePrefix(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const std::string& acrNewPrefix) {
	if(acrNewPrefix.find(" ") != std::string::npos) {
		echo(arServerID, acrUser, acrChannelID, "Prefix may not contain whitespace.");
	}
	m_serverBotSettings[arServerID].prefix = acrNewPrefix;
}

void MyClientClass::fn_hello(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID) {
	echo(arServerID, acrUser, acrChannelID, "Hello, " + Mention<SleepyDiscord::User>(acrUser));
}

void MyClientClass::fn_echo(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const std::string& acrMessage) {
	if (m_serverBotSettings[arServerID].silent == false) {
		sendMessage(acrChannelID, acrMessage);
	}
}

void MyClientClass::fn_muteVoice(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser) {
	muteServerMember(arServerID, acrUser.ID, true);
}

void MyClientClass::fn_unmuteVoice(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser) {
	muteServerMember(arServerID, acrUser.ID, false);
}

void MyClientClass::fn_muteText(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser) {
	if(std::count(m_serverBotSettings[arServerID].mutedUserIDs.begin(), m_serverBotSettings[arServerID].mutedUserIDs.end(), acrUser) == 0) {
		m_serverBotSettings[arServerID].mutedUserIDs.push_back(acrUser);
	}
}

void MyClientClass::fn_unmuteText(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser) {
	if(std::count(m_serverBotSettings[arServerID].mutedUserIDs.begin(), m_serverBotSettings[arServerID].mutedUserIDs.end(), acrUser) > 0) {
		m_serverBotSettings[arServerID].mutedUserIDs.erase(std::find(m_serverBotSettings[arServerID].mutedUserIDs.begin(), m_serverBotSettings[arServerID].mutedUserIDs.end(), acrUser));
	}
}

void MyClientClass::fn_setBotAdminRole(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& acrRoleID) {
	m_serverBotSettings[arServerID].botAdminRoleID = acrRoleID;
	logAction(arServerID, acrUser, "**BOT ADMIN ROLE SET**\n```Set to: " + acrRoleID.string() + "\nSet by: " + acrUser.username + "#" + acrUser.discriminator + "\n```");
}

void MyClientClass::fn_setLogsChannel(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID) {
	m_serverBotSettings[arServerID].logsChannelID = acrChannelID;
	//fprintf(stderr, "Logs Channel ID: %s (%s)\n", acrChannelID.string().c_str(), m_serverBotSettings[arServerID].logsChannelID.string().c_str());
	logAction(arServerID, acrUser, "Logs enabled in " + Mention<SleepyDiscord::Snowflake<SleepyDiscord::Channel>>(acrChannelID));
}

void MyClientClass::fn_logsDisable(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, bool b) {
	m_serverBotSettings[arServerID].noLogs = b;
}

void MyClientClass::fn_setSilent(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, bool b) {
	m_serverBotSettings[arServerID].silent = b;
}

void MyClientClass::fn_deleteMsg(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, SleepyDiscord::Message& arMessage) {
	deleteMsg(arMessage.serverID, arMessage.member, arMessage);
	std::string lLog = "**MESSAGE DELETE:**\n```Message ID: " + arMessage.ID.string() + "\nDeleted by: " + acrUser.username + "#" + acrUser.discriminator + "\nChannel: " + arMessage.channelID.string() + "\nMessage content: " + arMessage.content + "\n```";
	logAction(arServerID, acrUser, lLog);
}

void MyClientClass::fn_logAction(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const std::string& acrString) {
	if (m_serverBotSettings[arServerID].noLogs == false) {
		if (m_serverBotSettings[arServerID].logsChannelID != SleepyDiscord::Snowflake<SleepyDiscord::Channel>()) {
			echo(arServerID, acrUser, m_serverBotSettings[arServerID].logsChannelID, acrString);
		}
	}
}

void MyClientClass::fn_setPermissions(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, COMMAND_PERMISSION aCommandPerm, COMMAND_TYPE aCommandType) {
	if(aCommandType == ROLE_ALL) {
		m_serverBotSettings[arServerID].permissions[COMMAND_TYPE::ADMIN] = aCommandPerm;
		m_serverBotSettings[arServerID].permissions[COMMAND_TYPE::NON_ADMIN] = aCommandPerm;
	} else {
		m_serverBotSettings[arServerID].permissions[aCommandType] = aCommandPerm;
	}

	std::map<COMMAND_PERMISSION, std::string> lPerms = {
		{ COMMAND_PERMISSION::OWNER_ONLY, std::string("owner_only") },
		{ COMMAND_PERMISSION::BOT_ADMIN, std::string("bot_admin") },
		{ COMMAND_PERMISSION::CMD_ALL, std::string("all") }
	};
	std::map<COMMAND_TYPE, std::string> lType = {
		{ COMMAND_TYPE::ADMIN, std::string("admin") },
		{ COMMAND_TYPE::NON_ADMIN, std::string("non_admin") },
		{ COMMAND_TYPE::ROLE_ALL, std::string("all") }
	};

	logAction(arServerID, acrUser, "**PERMISSIONS CHANGE:**\n```Type: " + lType[aCommandType] + "\nSet to: " + lPerms[aCommandPerm] + "\nSet by: " + acrUser.username + "#" + acrUser.discriminator + "```\n");
}

void MyClientClass::fn_die(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID) {
	const std::string lcMessage = "Okay.";
	echo(arServerID, acrUser, acrChannelID, lcMessage);
	std::exit(0);
}

void MyClientClass::fn_bannedOps(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID) {
	const std::string lcMessage = "Aruni, Clash, Oryx.";
	echo(arServerID, acrUser, acrChannelID, lcMessage);
}


std::vector<std::string> MyClientClass::split(const std::string& acrString) {
	std::vector<std::string> lVec;
	int lPos = 0;
	while (1) {
		int lTemp = lPos;
		lPos = acrString.find(" ", lPos);
		std::string lWord = acrString.substr(lTemp, lPos - lTemp);
		if (lPos < lTemp) {
			std::string word = acrString.substr(lTemp);
			if (lWord.find_first_not_of(' ') != std::string::npos) {
				lVec.push_back(word);
			}
			break;
		}

		if (lWord.find_first_not_of(' ') != std::string::npos) {
			lVec.push_back(lWord);
		}
		lPos++;
	}
	return lVec;
}

std::string MyClientClass::getSnowflake(const std::string& acrString) {
	if(acrString.find("<@!") != std::string::npos) { // User mention
		return acrString.substr(3, acrString.size() - 3 - 1);
	}
	else if(acrString.find("<#") != std::string::npos) { // Channel mention
		return acrString.substr(2, acrString.size() - 2 - 1);
	}
	else if (acrString.find("<@&") != std::string::npos) { // Role mention
		return acrString.substr(3, acrString.size() - 3 - 1);
	}
	else throw std::runtime_error("getSnowflake(): string is not a member, role, or channel mention.");
}

MyClientClass::COMMAND_PERMISSION MyClientClass::toCommandPerm(const std::string& acrString) {
	if((acrString != "owner_only") && (acrString != "bot_admin") && (acrString != "all")) {
		std::string lError = "toCommandPerm: invalid string provided (" + acrString + ")";
		throw std::runtime_error(lError);
	}

	std::map<std::string, COMMAND_PERMISSION> lPerms = {
		{ std::string("owner_only"), COMMAND_PERMISSION::OWNER_ONLY },
		{ std::string("bot_admin"), COMMAND_PERMISSION::BOT_ADMIN },
		{ std::string("all"), COMMAND_PERMISSION::CMD_ALL }
	};
	return lPerms.at(acrString);
}

MyClientClass::COMMAND_TYPE MyClientClass::toCommandType(const std::string& acrString) {
	if((acrString != "admin") && (acrString != "non_admin") && (acrString != "all")) {
		std::string lError = "toCommandType: invalid string provided (" + acrString + ")";
		throw std::runtime_error(lError);
	}

	std::map<std::string, COMMAND_TYPE> lType = {
		{ std::string("admin"), COMMAND_TYPE::ADMIN },
		{ std::string("non_admin"), COMMAND_TYPE::NON_ADMIN },
		{ std::string("all"), COMMAND_TYPE::ROLE_ALL }
	};
	return lType.at(acrString);
}

bool MyClientClass::isMuted(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUser) {
	if(std::count(m_serverBotSettings[acrServerID].mutedUserIDs.begin(), m_serverBotSettings[acrServerID].mutedUserIDs.end(), acrUser) >= 1) {
		return true;
	} else {
		return false;
	}
}