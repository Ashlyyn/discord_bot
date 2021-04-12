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

	// command object				  name					client 	command type (admin or non-admin)	function pointer			noOwner
	Command changePrefix 	= Command("prefix",				this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_changePrefix);
	Command hello 			= Command("hello",				this, Command::COMMAND_TYPE::NON_ADMIN, &MyClientClass::fn_hello);
	Command echo  			= Command("echo",				this, Command::COMMAND_TYPE::NON_ADMIN, &MyClientClass::fn_echo);
	Command dmUser  		= Command("dm",					this, Command::COMMAND_TYPE::ADMIN, 	&MyClientClass::fn_dmUser);
	Command muteVoice		= Command("mute voice", 		this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_muteVoice,	true);
	Command unmuteVoice		= Command("unmute voice", 		this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_unmuteVoice,	true);
	Command muteText		= Command("mute text", 			this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_muteText,	true);
	Command unmuteText		= Command("unmute text", 		this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_unmuteText,	true);
	Command kick			= Command("kick", 				this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_kick,		true);
	Command ban				= Command("ban", 				this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_ban,			true);
	Command unban			= Command("unban", 				this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_unban);
	Command invite			= Command("invite", 			this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_invite);
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
	Command bannedOps		= Command("banned_ops",			this, Command::COMMAND_TYPE::NON_ADMIN,	&MyClientClass::fn_bannedOps);

	// client function overrides
	void onMessage(SleepyDiscord::Message aMessage) override;
	void onServer(SleepyDiscord::Server aServer) override;
	void onBan(SleepyDiscord::Snowflake<SleepyDiscord::Server> aServerID, SleepyDiscord::User aUser) override;
	void onRemoveMember(SleepyDiscord::Snowflake<SleepyDiscord::Server> aServerID, SleepyDiscord::User aRemovedUser) override;

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

	std::unordered_map<std::string, SleepyDiscord::Server> m_servers;	// map server IDs to servers
	std::unordered_map<std::string, SleepyDiscord::Snowflake<SleepyDiscord::Channel>> m_userDMchannelIDs;
	std::unordered_map<std::string, ServerBotSettings> m_serverBotSettings; // map server IDs to their respective settings struct
	std::unordered_map<std::string, std::pair<SleepyDiscord::User, bool>> m_bannedUsers; // map server IDs to users banned from servers 
																						 // and whether they were banned via the bot
	std::unordered_map<std::string, std::pair<SleepyDiscord::User, bool>> m_kickedUsers; // map server IDs to users kicked from the server
																						 // same thing with the bool

protected:
	// functions for bot - to be passed to their respective Command object; server ID and user must be passed for permissions checking even if the function does not use it directly
	void fn_changePrefix	(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const std::string& acrNewPrefix);
	void fn_hello			(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID);
	void fn_echo			(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const std::string& acrMessage);
	void fn_dmUser			(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrDMedUserID, 	const std::string& acrMessage = "");
	void fn_muteVoice		(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrMutedUserID);
	void fn_unmuteVoice		(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrMutedUserID);
	void fn_muteText		(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrMutedUserID);
	void fn_unmuteText		(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrMutedUserID);
	void fn_kick			(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrKickedUserID, const std::string& acrReason = "");
	void fn_ban				(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrBannedUserID, const std::string& acrReason = "", int acDeleteMessageDays = 36500);
	void fn_unban			(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrBannedUserID, const std::string& acrReason = "");
	void fn_invite			(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrInvitedUserID);
	void fn_setBotAdminRole	(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& acrRoleID);
	void fn_setLogsChannel	(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID);
	void fn_logsDisable		(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, bool b = true);
	void fn_setSilent		(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, bool b = true);
	void fn_deleteMsg		(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, SleepyDiscord::Message& arMessage);
	void fn_logAction		(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const std::string& acrString);
	void fn_setPermissions	(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, COMMAND_PERMISSION aCommandPerm, COMMAND_TYPE aCommandType);
	void fn_die				(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID);
	void fn_bannedOps		(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID);

private:
	const SleepyDiscord::Snowflake<SleepyDiscord::User> ownerID = 518216114665291786;
	static std::vector<std::string> split	(const std::string& acrString); // split string into vector of words
	static std::string getSnowflake			(const std::string& acrString); // get ID from mention
	static COMMAND_TYPE toCommandType		(const std::string& acrString); // map string to command type
	static COMMAND_PERMISSION toCommandPerm	(const std::string& acrString); // map string to command perm
		   bool isMuted						(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID);
};

#endif