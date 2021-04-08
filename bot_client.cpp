#include "bot_client.hpp"
#include "mention.hpp"

void MyClientClass::onMessage(SleepyDiscord::Message message) {
	const std::string& prefix = m_serverBotSettings[message.serverID].prefix;
	if (message.startsWith(prefix + "prefix ")) {
		changePrefix(message.serverID, message.member, message.member, message.channelID, message.content.substr(prefix.size() + strlen("prefix ")));
	}
	else if (message.startsWith(prefix + "hello")) {
		hello(message.serverID, message.member, message.channelID, message.author);
	}
	else if (message.startsWith(prefix + "echo ")) {
		echo(message.serverID, message.member, message.channelID, message.content.substr(prefix.size() + strlen("echo ")));
	}
	else if (message.startsWith(prefix + "mute voice ")) {
		muteVoice(message.serverID, message.member, message.content.substr(prefix.size() + strlen("mute voice ")));
	}

	else if (message.startsWith(prefix + "unmute voice ")) {
		unmuteVoice(message.serverID, message.member, message.content.substr(prefix.size() + strlen("unmute voice ")));
	}

	else if (message.startsWith(prefix + "mute text ")) {
		muteText(message.serverID, message.member, getSnowflake(message.content.substr(prefix.size() + strlen("mute text "))));
	}

	else if (message.startsWith(prefix + "unmute text ")) {
		unmuteText(message.serverID, message.member, getSnowflake(message.content.substr(prefix.size() + strlen("unmute text "))));
	}

	else if (message.startsWith(prefix + "bot_admin_role set ")) {
		setBotAdminRole(message.serverID, message.member, getSnowflake(message.content.substr(prefix.size() + strlen("bot_admin_role set "))));
	}

	else if (message.startsWith(prefix + "nologs")) {
		logsDisable(message.serverID, message.member);
	}

	else if (message.startsWith(prefix + "logs disable")) {
		logsDisable(message.serverID, message.member);
	}

	else if (message.startsWith(prefix + "logs enable")) {
		logsDisable(message.serverID, message.member, false);
	}

	else if (message.startsWith(prefix + "logs ")) {
		setLogsChannel(message.serverID, message.member, SleepyDiscord::Snowflake<SleepyDiscord::Channel>(getSnowflake(message.content.substr(prefix.size() + strlen("logs ")))));
	}
		
	else if (message.startsWith(prefix + "silent")) {
		setSilent(message.serverID, message.member);
	}

	else if (message.startsWith(prefix + "nosilent")) {
		setSilent(message.serverID, message.member, false);
	}

	else if (message.startsWith(prefix + "delete ")) {
		deleteMsg(message.serverID, message.member, message);
	}

	else if (message.startsWith(prefix + "permissions set ")) {
		setPermissions(message.serverID, message.member, toCommandPerm(split(message.content)[3]), toCommandType(split(message.content)[2]));
	}

	else if (message.startsWith(prefix + "die")) {
		die(message.serverID, message.member, message.channelID);
	}

	else if(message.startsWith(prefix)) {
		echo(message.serverID, message.member, message.channelID, "Unknown command.");
	}

	if(isMuted(message.serverID, message.member)) {
		deleteMsg(message.serverID, message.member, message);
	}
}

void MyClientClass::fn_changePrefix(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::ServerMember& member, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channel, const std::string& newPrefix) {
	if(newPrefix.find(" ") != std::string::npos) {
		echo(server, member, channel, "Prefix may not contain whitespace.");
	}
	m_serverBotSettings[server].prefix = newPrefix;
}

void MyClientClass::fn_hello(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channel, const SleepyDiscord::User& user) {
	fn_echo(server, channel, "Hello, " + Mention<SleepyDiscord::User>(user));
}

void MyClientClass::fn_echo(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channel, const std::string& message) {
	if (m_serverBotSettings[server].silent == false) {
		sendMessage(channel, message);
	}
}

void MyClientClass::fn_muteVoice(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::User>& user) {
	muteServerMember(server, user, true);
}

void MyClientClass::fn_unmuteVoice(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::User>& user) {
	muteServerMember(server, user, false);
}

void MyClientClass::fn_muteText(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::ServerMember>& member) {
	if(std::count(m_serverBotSettings[server].mutedUsers.begin(), m_serverBotSettings[server].mutedUsers.end(), member) == 0) {
		m_serverBotSettings[server].mutedUsers.push_back(member);
	}
}

void MyClientClass::fn_unmuteText(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::ServerMember>& member) {
	if(std::count(m_serverBotSettings[server].mutedUsers.begin(), m_serverBotSettings[server].mutedUsers.end(), member) > 0) {
		m_serverBotSettings[server].mutedUsers.erase(std::find(m_serverBotSettings[server].mutedUsers.begin(), m_serverBotSettings[server].mutedUsers.end(), member));
	}
}

void MyClientClass::fn_setBotAdminRole(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::ServerMember& member, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& role) {
	m_serverBotSettings[server].botAdminRole = role;
	logAction(server, member, "**BOT ADMIN ROLE SET**\n```Set to: " + role.string() + "\nSet by: " + member.user.username + "#" + member.user.discriminator + "\n```");
}

void MyClientClass::fn_setLogsChannel(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::ServerMember& member, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channel) {
	m_serverBotSettings[server].logsChannel = channel;
	logAction(server, member, "Logs enabled in " + Mention<SleepyDiscord::Snowflake<SleepyDiscord::Channel>>(channel));
}

void MyClientClass::fn_logsDisable(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, bool b) {
	m_serverBotSettings[server].noLogs = b;
}

void MyClientClass::fn_setSilent(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, bool b) {
	m_serverBotSettings[server].silent = b;
}

void MyClientClass::fn_deleteMsg(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::ServerMember& member, SleepyDiscord::Message& message) {
	deleteMsg(message.serverID, message.member, message);
	std::string log = "**MESSAGE DELETE:**\n```Message ID: " + message.ID.string() + "\nDeleted by: " + member.user.username + "#" + member.user.discriminator + "\nChannel: " + message.channelID.string() + "\nMessage content: " + message.content + "\n```";
	fn_logAction(server, member, log);
}

void MyClientClass::fn_logAction(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::ServerMember& member, const std::string& str) {
	if (m_serverBotSettings[server].noLogs == false) {
		if (m_serverBotSettings[server].logsChannel != SleepyDiscord::Snowflake<SleepyDiscord::Channel>()) {
			echo(server, member, m_serverBotSettings[server].logsChannel, str);
		}
	}
}

void MyClientClass::fn_setPermissions(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::ServerMember& member, COMMAND_PERMISSION commandPerm, COMMAND_TYPE commandType) {
	if(commandType == ROLE_ALL) {
		m_serverBotSettings[server].permissions[COMMAND_TYPE::ADMIN] = commandPerm;
		m_serverBotSettings[server].permissions[COMMAND_TYPE::NON_ADMIN] = commandPerm;
	} else {
		m_serverBotSettings[server].permissions[commandType] = commandPerm;
	}

	std::map<COMMAND_PERMISSION, std::string> perms = {
		{ COMMAND_PERMISSION::OWNER_ONLY, std::string("owner_only") },
		{ COMMAND_PERMISSION::BOT_ADMIN, std::string("bot_admin") },
		{ COMMAND_PERMISSION::CMD_ALL, std::string("all") }
	};
	std::map<COMMAND_TYPE, std::string> type = {
		{ COMMAND_TYPE::ADMIN, std::string("admin") },
		{ COMMAND_TYPE::NON_ADMIN, std::string("non_admin") },
		{ COMMAND_TYPE::ROLE_ALL, std::string("all") }
	};

	logAction(server, member, "**PERMISSIONS CHANGE:**\n```Type: " + type[commandType] + "\nSet to: " + perms[commandPerm] + "\nSet by: " + member.user.username + "#" + member.user.discriminator + "```\n");
}

void MyClientClass::fn_die(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::Channel> channel) {
	fn_echo(server, channel, "Okay.");
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

MyClientClass::COMMAND_PERMISSION MyClientClass::toCommandPerm(const std::string& string) {
	std::map<std::string, COMMAND_PERMISSION> perms = {
		{ std::string("owner_only"), COMMAND_PERMISSION::OWNER_ONLY },
		{ std::string("bot_admin"), COMMAND_PERMISSION::BOT_ADMIN },
		{ std::string("all"), COMMAND_PERMISSION::CMD_ALL }
	};
	return perms[string];
}

MyClientClass::COMMAND_TYPE MyClientClass::toCommandType(const std::string& string) {
	std::map<std::string, COMMAND_TYPE> type = {
		{ std::string("admin"), COMMAND_TYPE::ADMIN },
		{ std::string("non_admin"), COMMAND_TYPE::NON_ADMIN },
		{ std::string("all"), COMMAND_TYPE::ROLE_ALL }
	};
	return type.at(string);
}

bool MyClientClass::isMuted(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::ServerMember>& member) {
	if(std::count(m_serverBotSettings[server].mutedUsers.begin(), m_serverBotSettings[server].mutedUsers.end(), member) >= 1) {
		return true;
	} else {
		return false;
	}
}