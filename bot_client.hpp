#ifndef _BOT_CLIENT_H_
#define _BOT_CLIENT_H_

#include <array>
#include <map>
#include <vector>

#include "sleepy_discord/sleepy_discord.h"

#include "command.hpp"
#include "server_bot_settings.hpp"

class MyClientClass : public SleepyDiscord::DiscordClient {
public:
	using SleepyDiscord::DiscordClient::DiscordClient;

	Command changePrefix 	= Command("prefix",				this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_changePrefix);
	Command hello 			= Command("hello",				this, Command::COMMAND_TYPE::NON_ADMIN, &MyClientClass::fn_hello);
	Command echo  			= Command("echo",				this, Command::COMMAND_TYPE::NON_ADMIN, &MyClientClass::fn_echo );
	Command muteVoice		= Command("mute voice", 		this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_muteVoice);
	Command unmuteVoice		= Command("unmute voice", 		this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_unmuteVoice);
	Command muteText		= Command("mute text", 			this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_muteText);
	Command unmuteText		= Command("unmute text", 		this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_unmuteText);
	Command setBotAdminRole = Command("bot_admin_role set", this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_setBotAdminRole);
	Command logsDisable		= Command("logs disable", 		this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_logsDisable);
	Command logsEnable		= Command("logs enable", 		this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_logsDisable);
	Command setLogsChannel	= Command("logs", 				this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_setLogsChannel);
	Command setSilent		= Command("silent",				this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_setSilent);
	Command noSilent 		= Command("nosilent", 			this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_logsDisable);
	Command deleteMsg		= Command("message delete",		this, Command::COMMAND_TYPE::ADMIN,	  	&MyClientClass::fn_deleteMsg);
	Command logAction		= Command("log_action",			this, Command::COMMAND_TYPE::ADMIN,	  	&MyClientClass::fn_logAction);
	Command setPermissions	= Command("permissions set",	this, Command::COMMAND_TYPE::ADMIN,	  	&MyClientClass::fn_setPermissions);
	Command die				= Command("die",				this, Command::COMMAND_TYPE::ADMIN,	  	&MyClientClass::fn_die);

	void onMessage(SleepyDiscord::Message message) override;

    enum COMMAND_PERMISSION {
		OWNER_ONLY,
		BOT_ADMIN,
		CMD_ALL
	};

	enum COMMAND_TYPE {
		ADMIN,
		NON_ADMIN,
		ROLE_ALL
	};

	std::map<SleepyDiscord::Snowflake<SleepyDiscord::Server>, ServerBotSettings, ServerBotSettingsComparator> m_serverBotSettings;

protected:
	void fn_changePrefix	(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::ServerMember& member, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channel, const std::string& newPrefix);
	void fn_hello			(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channel, const SleepyDiscord::User& user);
	void fn_echo			(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channel, const std::string& message);
	void fn_muteVoice		(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::User>& user);
	void fn_unmuteVoice		(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::User>& user);
	void fn_muteText		(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::ServerMember>& member);
	void fn_unmuteText		(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::ServerMember>& member);
	void fn_setBotAdminRole	(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::ServerMember& member, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& role);
	void fn_setLogsChannel	(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::ServerMember& member, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channel);
	void fn_logsDisable		(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, bool b = true);
	void fn_setSilent		(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, bool b = true);
	void fn_deleteMsg		(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::ServerMember& member, SleepyDiscord::Message& message);
	void fn_logAction		(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::ServerMember& member, const std::string& str);
	void fn_setPermissions	(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::ServerMember& member, COMMAND_PERMISSION commandPerm, COMMAND_TYPE commandType);
	void fn_die				(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::Channel> channel);


private:
	static std::vector<std::string> split(const std::string& string);
	static std::string getSnowflake(const std::string& str);
	static COMMAND_TYPE toCommandType(const std::string& string);
	static COMMAND_PERMISSION toCommandPerm(const std::string& string);
	bool isMuted(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::ServerMember>& member);
};

#endif