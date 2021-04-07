#include "bot_client.hpp"
#include "mention.hpp"

void MyClientClass::onMessage(SleepyDiscord::Message message) {
	const std::string& prefix = m_serverBotSettings[message.serverID].prefix;
	if (message.startsWith(prefix + "prefix ")) {
		if(checkPermissions(message.serverID, message.member, ADMIN) == true) {
			changePrefix(message.serverID, message.content.substr(prefix.size() + strlen("prefix ")));
		}
	}
	else if (message.startsWith(prefix + "hello")) {
		if(checkPermissions(message.serverID, message.member, NON_ADMIN) == true) {
			hello(message.serverID, message.channelID, message.author);
		}
	}

	else if (message.startsWith(prefix + "echo ")) {
		if(checkPermissions(message.serverID, message.member, NON_ADMIN) == true) {
			echo(message.serverID, message.channelID, message.content.substr(prefix.size() + strlen("echo ")));
		}
	}

	else if (message.startsWith(prefix + "mute voice ")) {
		if(checkPermissions(message.serverID, message.member, ADMIN) == true) {
			muteVoice(message.serverID, message.content.substr(prefix.size() + strlen("mute voice ")));
		}
	}

	else if (message.startsWith(prefix + "unmute voice ")) {
		if(checkPermissions(message.serverID, message.member, ADMIN) == true) {
			unmuteVoice(message.serverID, message.content.substr(prefix.size() + strlen("unmute voice ")));
		}
	}

	else if (message.startsWith(prefix + "mute text ")) {
		if(checkPermissions(message.serverID, message.member, ADMIN) == true) {
			muteText(message.serverID, getSnowflake(message.content.substr(prefix.size() + strlen("mute text "))));
		}
	}

	else if (message.startsWith(prefix + "unmute text ")) {
		if(checkPermissions(message.serverID, message.member, ADMIN) == true) {
			unmuteText(message.serverID, getSnowflake(message.content.substr(prefix.size() + strlen("unmute text "))));
		}
	}


	else if (message.startsWith(prefix + "bot_admin_role set ")) {
		if (checkPermissions(message.serverID, message.member, ADMIN) == true) {
		auto words = split(message.content);
			setBotAdminRole(message.serverID, getSnowflake(message.content.substr(prefix.size() + strlen("bot_admin_role set "))));
			logAction(message.serverID, "**BOT ADMIN ROLE SET**\n```Set to: " + words[2] + "\nSet by: " + message.author.username + "#" + message.author.discriminator + "\n```");
		}
	}

	else if (message.startsWith(prefix + "nologs")) {
		if (checkPermissions(message.serverID, message.member, ADMIN) == true) {
			logsDisable(message.serverID);
		}
	}

	else if (message.startsWith(prefix + "logs disable")) {
		if (checkPermissions(message.serverID, message.member, ADMIN) == true) {
			logsDisable(message.serverID);
		}
	}

	else if (message.startsWith(prefix + "logs enable")) {
		if (checkPermissions(message.serverID, message.member, ADMIN) == true) {
			logsDisable(message.serverID, false);
		}
	}

	else if (message.startsWith(prefix + "logs ")) {
		if(checkPermissions(message.serverID, message.member, ADMIN) == true) {
			setLogsChannel(message.serverID, SleepyDiscord::Snowflake<SleepyDiscord::Channel>(getSnowflake(message.content.substr(prefix.size() + strlen("logs ")))));
			logAction(message.serverID, "Logs enabled in " + message.content.substr(prefix.size() + strlen("logs ")));
		}
	}
		
	else if (message.startsWith(prefix + "silent")) {
		if (checkPermissions(message.serverID, message.member, ADMIN) == true) {
			setSilent(message.serverID);
		}
	}

	else if (message.startsWith(prefix + "nosilent")) {
		if (checkPermissions(message.serverID, message.member, ADMIN) == true) {
			setSilent(message.serverID, false);
		}
	}

	else if (message.startsWith(prefix + "delete ")) {
		if(checkPermissions(message.serverID, message.member, ADMIN) == true) {
			std::string log;
			std::vector<std::string> words = split(message.content);
			if (words.size() > 2) {
				log = "**MESSAGE DELETE:**\n```Message ID: " + words[2] + "\nDeleted by: " + message.author.username + "\nChannel: " + words[1] + "\nMessage content: " + message.content + "\n```";
				deleteMessage(SleepyDiscord::Snowflake<SleepyDiscord::Channel>(words[1]), SleepyDiscord::Snowflake<SleepyDiscord::Message>(words[2]));
			}
			else {
				log = "**MESSAGE DELETE:**\n```Message ID: " + words[1] + "\nDeleted by: " + message.author.username + "\nChannel: " + message.channelID.string() + "\nMessage content: " + message.content +"\n```";
				deleteMessage(message.channelID, SleepyDiscord::Snowflake<SleepyDiscord::Message>(words[1]));
			}
			logAction(message.serverID, log);
		}
    }

	else if (message.startsWith(prefix + "permissions set ")) {
		if(checkPermissions(message.serverID, message.member, ADMIN) == true) {
			auto words = split(message.content);
			std::map<std::string, COMMAND_PERMISSION> perms = {
				{ std::string("owner_only"), COMMAND_PERMISSION::OWNER_ONLY },
				{ std::string("bot_admin"), COMMAND_PERMISSION::BOT_ADMIN },
				{ std::string("all"), COMMAND_PERMISSION::CMD_ALL }
			};
			std::map<std::string, COMMAND_TYPE> type = {
				{ std::string("admin"), COMMAND_TYPE::ADMIN },
				{ std::string("non_admin"), COMMAND_TYPE::NON_ADMIN },
				{ std::string("all"), COMMAND_TYPE::ROLE_ALL }
			};
			setPermissions(message.serverID, perms[words[3]], type[words[2]]);
			logAction(message.serverID, "**PERMISSIONS CHANGE:**\n```Type: " + words[3] + "\nSet to: " + words[2] + "\nSet by: " + message.author.username + "#" + message.author.discriminator + "```\n");
		}
	}

	else if (message.startsWith(prefix + "die")) {
		if(checkPermissions(message.serverID, message.member, ADMIN) == true) {
			die(message.serverID, message.channelID);
		}
	}

	else if(message.startsWith(prefix)) {
		echo(message.serverID, message.channelID, "Unknown command.");
	}

	if(isMuted(message.serverID, message.member)) {
		deleteMessage(message.channelID, message.ID);
	}
}

void MyClientClass::onServer(SleepyDiscord::Server server) {
//	SleepyDiscord::Snowflake<SleepyDiscord::Server> snowflake = SleepyDiscord::Snowflake<SleepyDiscord::Server>(server);
//	m_serverBotSettings[snowflake] = ServerBotSettings();
}

void MyClientClass::changePrefix(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const std::string& newPrefix) {
	m_serverBotSettings[server].prefix = newPrefix;
}

void MyClientClass::hello(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channel, const SleepyDiscord::User& user) {
	echo(server, channel, "Hello, " + Mention<SleepyDiscord::User>(user));
}

void MyClientClass::echo(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channel, const std::string& message) {
	if (m_serverBotSettings[server].silent == false) {
		sendMessage(channel, message);
	}
}

void MyClientClass::muteVoice(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::User>& user) {
	muteServerMember(server, user, true);
}

void MyClientClass::unmuteVoice(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::User>& user) {
	muteServerMember(server, user, false);
}

void MyClientClass::muteText(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::ServerMember>& member) {
	if(std::count(m_serverBotSettings[server].mutedUsers.begin(), m_serverBotSettings[server].mutedUsers.end(), member) == 0) {
		m_serverBotSettings[server].mutedUsers.push_back(member);
	}
}

void MyClientClass::unmuteText(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::ServerMember>& member) {
	if(std::count(m_serverBotSettings[server].mutedUsers.begin(), m_serverBotSettings[server].mutedUsers.end(), member) > 0) {
		m_serverBotSettings[server].mutedUsers.erase(std::find(m_serverBotSettings[server].mutedUsers.begin(), m_serverBotSettings[server].mutedUsers.end(), member));
	}
}

void MyClientClass::setBotAdminRole(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& role) {
	m_serverBotSettings[server].botAdminRole = role;
}

void MyClientClass::setLogsChannel(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channel) {
	m_serverBotSettings[server].logsChannel = channel;
}

void MyClientClass::logsDisable(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, bool b) {
	m_serverBotSettings[server].noLogs = b;
}

void MyClientClass::setSilent(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, bool b) {
	m_serverBotSettings[server].silent = b;
}

void MyClientClass::logAction(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const std::string& str) {
	if (m_serverBotSettings[server].noLogs == false) {
		if (m_serverBotSettings[server].logsChannel != SleepyDiscord::Snowflake<SleepyDiscord::Channel>()) {
			echo(server, m_serverBotSettings[server].logsChannel, str);
		}
	}
}

void MyClientClass::setPermissions(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, COMMAND_PERMISSION commandPerm, COMMAND_TYPE commandType) {
	if(commandType == ROLE_ALL) {
		m_serverBotSettings[server].permissions[COMMAND_TYPE::ADMIN] = commandPerm;
		m_serverBotSettings[server].permissions[COMMAND_TYPE::NON_ADMIN] = commandPerm;
	} else {
		m_serverBotSettings[server].permissions[commandType] = commandPerm;
	}
}

void MyClientClass::die(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::Channel> channel) {
	echo(server, channel, "Okay.");
	exit(0);
}

std::vector<std::string> MyClientClass::split(const std::string& string) {
	std::vector<std::string> vec;
	int pos = 0;
	while (1) {
		int temp = pos;
		pos = string.find(" ", pos);
		std::string word = string.substr(temp, pos - temp);
		if (pos < temp) {
			std::string word = string.substr(temp);
			if (word.find_first_not_of(' ') != std::string::npos) {
				vec.push_back(word);
			}
			break;
		}

		if (word.find_first_not_of(' ') != std::string::npos) {
			vec.push_back(word);
		}
		pos++;
	}
	return vec;
}

std::string MyClientClass::getSnowflake(const std::string& str) {
	if(str.find("<@!") != std::string::npos) { // User mention
		return str.substr(3, str.size() - 3 - 1);
	}
	else if(str.find("<#") != std::string::npos) { // Channel mention
		return str.substr(2, str.size() - 2 - 1);
	}
	else if (str.find("<@&") != std::string::npos) { // Role mention
		return str.substr(3, str.size() - 3 - 1);
	}
	else throw std::runtime_error("getSnowflake(): string is not a member, role, or channel mention.");
}

bool MyClientClass::isMuted(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::ServerMember>& member) {
	if(std::count(m_serverBotSettings[server].mutedUsers.begin(), m_serverBotSettings[server].mutedUsers.end(), member) >= 1) {
		return true;
	} else {
		return false;
	}
}

bool MyClientClass::hasRole(const SleepyDiscord::ServerMember& member, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& role) {
	bool b = false;
	for (const auto& memberRole : member.roles) {
		if (memberRole == role) {
			b = true;
		}
	}
	return b;
}

bool MyClientClass::isOwner(const SleepyDiscord::Snowflake<SleepyDiscord::User>& user) {
	if (user == 518216114665291786) {
		return true;
	}
	else {
		return false;
	}
}

bool MyClientClass::checkPermissions(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::ServerMember& member, COMMAND_TYPE commandType) {
	if(m_serverBotSettings[server].permissions[commandType] == OWNER_ONLY && isOwner(member.user.ID)) {
		return true;
	} 
	else if ((m_serverBotSettings[server].permissions[commandType] == BOT_ADMIN && hasRole(member, m_serverBotSettings[server].botAdminRole)) || isOwner(member.user.ID)) {
		return true;
	}
	else if (m_serverBotSettings[server].permissions[commandType] == CMD_ALL) {
		return true;
	}
	else {
		return false;
	}
}