#include "bot_client.hpp"

void MyClientClass::onMessage(SleepyDiscord::Message message) {
	if (message.startsWith(m_prefix + "prefix ")) {
		if(checkPermissions(message.member, ADMIN) == true) {
			changePrefix(message.content.substr(m_prefix.size() + strlen("prefix ")));
		}
	}
	else if (message.startsWith(m_prefix + "hello")) {
		if(checkPermissions(message.member, NON_ADMIN) == true) {
			hello(message.channelID, message.author);
		}
	}

	else if (message.startsWith(m_prefix + "echo ")) {
		if(checkPermissions(message.member, NON_ADMIN) == true) {
			echo(message.channelID, message.content.substr(m_prefix.size() + strlen("echo ")));
		}
	}

	else if (message.startsWith(m_prefix + "mute voice ")) {
		if(checkPermissions(message.member, ADMIN) == true) {
			muteVoice(message.serverID, message.content.substr(m_prefix.size() + strlen("mute voice ")));
		}
	}

	else if (message.startsWith(m_prefix + "unmute voice ")) {
		if(checkPermissions(message.member, ADMIN) == true) {
			unmuteVoice(message.serverID, message.content.substr(m_prefix.size() + strlen("unmute voice ")));
		}
	}

	else if (message.startsWith(m_prefix + "mute text ")) {
		if(checkPermissions(message.member, ADMIN) == true) {
			muteText(message.serverID, getSnowflake(message.content.substr(m_prefix.size() + strlen("mute text "))));
		}
	}

	else if (message.startsWith(m_prefix + "unmute text ")) {
		if(checkPermissions(message.member, ADMIN) == true) {
			unmuteText(message.serverID, getSnowflake(message.content.substr(m_prefix.size() + strlen("unmute text "))));
		}
	}


	else if (message.startsWith(m_prefix + "bot_admin_role set ")) {
		if (checkPermissions(message.member, ADMIN) == true) {
		auto words = split(message.content);
			setBotAdminRole(getSnowflake(message.content.substr(m_prefix.size() + strlen("bot_admin_role set "))));
			logAction("**BOT ADMIN ROLE SET**\n```Set to: " + words[2] + "\nSet by: " + message.author.username + "#" + message.author.discriminator + "\n```");
		}
	}

	else if (message.startsWith(m_prefix + "nologs")) {
		if (checkPermissions(message.member, ADMIN) == true) {
			logsDisable();
		}
	}

	else if (message.startsWith(m_prefix + "logs disable")) {
		if (checkPermissions(message.member, ADMIN) == true) {
			logsDisable();
		}
	}

	else if (message.startsWith(m_prefix + "logs enable")) {
		if (checkPermissions(message.member, ADMIN) == true) {
			logsDisable(false);
		}
	}

	else if (message.startsWith(m_prefix + "logs ")) {
		if(checkPermissions(message.member, ADMIN) == true) {
			setLogsChannel(SleepyDiscord::Snowflake<SleepyDiscord::Channel>(getSnowflake(message.content.substr(m_prefix.size() + strlen("logs ")))));
			logAction("Logs enabled in " + message.content.substr(m_prefix.size() + strlen("logs ")));
		}
	}
		
	else if (message.startsWith(m_prefix + "silent")) {
		if (checkPermissions(message.member, ADMIN) == true) {
			setSilent();
		}
	}

	else if (message.startsWith(m_prefix + "nosilent")) {
		if (checkPermissions(message.member, ADMIN) == true) {
			setSilent(false);
		}
	}

	else if (message.startsWith(m_prefix + "delete ")) {
		if(checkPermissions(message.member, ADMIN) == true) {
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
			logAction(log);
		}
    }

	else if (message.startsWith(m_prefix + "permissions set ")) {
		if(checkPermissions(message.member, ADMIN) == true) {
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
			setPermissions(perms[words[3]], type[words[2]]);
			logAction("**PERMISSIONS CHANGE:**\n```Type: " + words[3] + "\nSet to: " + words[2] + "\nSet by: " + message.author.username + "#" + message.author.discriminator + "```\n");
		}
	}

	else if (message.startsWith(m_prefix + "die")) {
		if(checkPermissions(message.member, ADMIN) == true) {
			die(message.channelID);
		}
	}

	else if(message.startsWith(m_prefix)) {
		echo(message.channelID, "Unknown command.");
	}

	if(isMuted(message.author.ID)) {
		deleteMessage(message.channelID, message.ID);
	}
}

void MyClientClass::onServer(SleepyDiscord::Server server) {
    SleepyDiscord::Snowflake<SleepyDiscord::Server> snowflake = server;
    m_serverBotSettings.emplace(snowflake, ServerBotSettings { false, false, "F!", nullptr, nullptr, nullptr } );
}

void MyClientClass::changePrefix(const std::string& newPrefix) {
	m_prefix = newPrefix;
}

void MyClientClass::hello(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channel, const SleepyDiscord::User& user) {
	echo(channel, "Hello, " + user.username);
}

void MyClientClass::echo(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channel, const std::string& message) {
	if (m_silent == false) {
		sendMessage(channel, message);
	}
}

void MyClientClass::muteVoice(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::User>& user) {
	muteServerMember(server, user, true);
}

void MyClientClass::unmuteVoice(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::User>& user) {
	muteServerMember(server, user, false);
}

void MyClientClass::muteText(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::User> user) {
	if(std::count(m_mutedUsers.begin(), m_mutedUsers.end(), user) == 0) {
		m_mutedUsers.push_back(user);
	}
}

void MyClientClass::unmuteText(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::User> user) {
	if(std::count(m_mutedUsers.begin(), m_mutedUsers.end(), user) > 0) {
		m_mutedUsers.erase(std::find(m_mutedUsers.begin(), m_mutedUsers.end(), user));
	}
}

void MyClientClass::setBotAdminRole(const SleepyDiscord::Snowflake<SleepyDiscord::Role>& role) {
	m_botAdminRole = role;
}

void MyClientClass::setLogsChannel(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channel) {
	m_logsChannel = channel;
}

void MyClientClass::logsDisable(bool b) {
	m_noLogs = b;
}

void MyClientClass::setSilent(bool b) {
	m_silent = b;
}

void MyClientClass::logAction(const std::string& str) {
	if (m_noLogs == false) {
		if (m_logsChannel != SleepyDiscord::Snowflake<SleepyDiscord::Channel>()) {
			echo(m_logsChannel, str);
		}
	}
}

void MyClientClass::setPermissions(COMMAND_PERMISSION commandPerm, COMMAND_TYPE commandType) {
	if(commandType == ROLE_ALL) {
		m_permissions[COMMAND_TYPE::ADMIN] = commandPerm;
		m_permissions[COMMAND_TYPE::NON_ADMIN] = commandPerm;
	} else {
		m_permissions[commandType] = commandPerm;
	}
}

void MyClientClass::die(const SleepyDiscord::Snowflake<SleepyDiscord::Channel> channel) {
	echo(channel, "Okay.");
	exit(0);
}

std::vector<std::string> MyClientClass::split(std::string string) {
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

std::string MyClientClass::getSnowflake(const std::string str) {
	if(str.find("<@!") != std::string::npos) {
		return str.substr(3, str.size() - 3 - 1);
	}
	else if(str.find("<#") != std::string::npos) {
		return str.substr(2, str.size() - 2 - 1);
	}
	else if (str.find("<@&") != std::string::npos) {
		return str.substr(3, str.size() - 3 - 1);
	}
	else throw std::runtime_error("getSnowflake(): string is not a member, role, or channel mention.");
}

bool MyClientClass::isMuted(const SleepyDiscord::Snowflake<SleepyDiscord::User>& user) {
	if(std::count(m_mutedUsers.begin(), m_mutedUsers.end(), user) >= 1) {
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

bool MyClientClass::checkPermissions(const SleepyDiscord::ServerMember& member, COMMAND_TYPE commandType) {
	if(m_permissions[commandType] == OWNER_ONLY && isOwner(member.user.ID)) {
		return true;
	} 
	else if ((m_permissions[commandType] == BOT_ADMIN && hasRole(member, m_botAdminRole)) || isOwner(member.user.ID)) {
		return true;
	}
	else if (m_permissions[commandType] == CMD_ALL) {
		return true;
	}
	else {
		return false;
	}
}