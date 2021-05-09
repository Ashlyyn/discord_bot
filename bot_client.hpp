#ifndef _BOT_CLIENT_H_
#define _BOT_CLIENT_H_

#include <map>
#include <vector>

#include "sleepy_discord/sleepy_discord.h"

#include "command.hpp"
#include "server_bot_settings.hpp"

class MyClientClass : public SleepyDiscord::DiscordClient {
public:
	using SleepyDiscord::DiscordClient::DiscordClient;

	// command object				  		name					client 	command type (admin or non-admin)	function pointer			noOwner
	Command changePrefix 		 = Command("prefix",				this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_changePrefix);
	Command hello 				 = Command("hello",					this, Command::COMMAND_TYPE::NON_ADMIN, &MyClientClass::fn_hello);
	Command echo  				 = Command("echo",					this, Command::COMMAND_TYPE::NON_ADMIN, &MyClientClass::fn_echo);
	Command dmUser  			 = Command("dm",					this, Command::COMMAND_TYPE::ADMIN, 	&MyClientClass::fn_dmUser);
	Command muteVoice			 = Command("mute voice", 			this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_muteVoice,	true);
	Command unmuteVoice			 = Command("unmute voice", 			this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_unmuteVoice,	true);
	Command muteText			 = Command("mute text", 			this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_muteText,	true);
	Command unmuteText			 = Command("unmute text", 			this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_unmuteText,	true);
	Command kick				 = Command("kick", 					this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_kick,		true);
	Command ban					 = Command("ban", 					this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_ban,			true);
	Command unban				 = Command("unban", 				this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_unban);
	Command invite				 = Command("invite send", 			this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_invite);
	Command setBotAdminRole 	 = Command("bot_admin_role set",	this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_setBotAdminRole);
	Command logsDisable			 = Command("logs disable", 			this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_logsDisable);
	Command logsEnable			 = Command("logs enable", 			this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_logsDisable);
	Command setLogsChannel		 = Command("logs", 					this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_setLogsChannel);
	Command setSilent			 = Command("silent",				this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_setSilent);
	Command noSilent 			 = Command("nosilent", 				this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_logsDisable);
	Command deleteMsg			 = Command("message delete",		this, Command::COMMAND_TYPE::ADMIN,	  	&MyClientClass::fn_deleteMsg);
	Command logAction			 = Command("log_action",			this, Command::COMMAND_TYPE::ADMIN,	  	&MyClientClass::fn_logAction);
	Command setPermissions		 = Command("permissions set",		this, Command::COMMAND_TYPE::ADMIN,	  	&MyClientClass::fn_setPermissions);
	Command renameChannel		 = Command("channel rename",		this, Command::COMMAND_TYPE::ADMIN,	  	&MyClientClass::fn_setChannelName);
	Command setChannelTopic		 = Command("channel topic set",		this, Command::COMMAND_TYPE::ADMIN,	  	&MyClientClass::fn_setChannelTopic);
	Command removeChannel		 = Command("channel delete",		this, Command::COMMAND_TYPE::ADMIN,	  	&MyClientClass::fn_deleteChannel);
	Command pin					 = Command("pin",					this, Command::COMMAND_TYPE::ADMIN,	  	&MyClientClass::fn_pinMessage);
	Command unpin				 = Command("unpin",					this, Command::COMMAND_TYPE::ADMIN,	  	&MyClientClass::fn_unpinMessage);
	Command changeNickname		 = Command("nickname",				this, Command::COMMAND_TYPE::ADMIN,	  	&MyClientClass::fn_changeNickname);
	Command revokeRole			 = Command("role revoke",			this, Command::COMMAND_TYPE::ADMIN,	  	&MyClientClass::fn_removeRole);
	Command rmRole			 	 = Command("role delete",			this, Command::COMMAND_TYPE::ADMIN,	  	&MyClientClass::fn_deleteRole);
	Command pruneUsers			 = Command("prune",					this, Command::COMMAND_TYPE::ADMIN,	  	&MyClientClass::fn_pruneUsers);
	Command deleteInviteCode	 = Command("invite delete",			this, Command::COMMAND_TYPE::ADMIN,	  	&MyClientClass::fn_deleteInvite);
	Command deleteChannelInvites = Command("channel delete invites",this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_deleteChannelInvites);
	Command deleteServerInvites	 = Command("invites delete all",	this, Command::COMMAND_TYPE::ADMIN, 	&MyClientClass::fn_deleteAllInvites);
	Command leave				 = Command("leave",					this, Command::COMMAND_TYPE::ADMIN,	  	&MyClientClass::fn_leaveServer);
	Command status				 = Command("status",				this, Command::COMMAND_TYPE::ADMIN,	  	&MyClientClass::fn_setStatus);
	Command setBotActivity		 = Command("bot activity set",		this, Command::COMMAND_TYPE::ADMIN,	  	&MyClientClass::fn_setBotActivity);
	Command setBotIdle			 = Command("bot idle set",			this, Command::COMMAND_TYPE::ADMIN,	  	&MyClientClass::fn_setBotIdle);
	Command setBotStatus		 = Command("bot status set",		this, Command::COMMAND_TYPE::ADMIN,	  	&MyClientClass::fn_setBotStatus);
	Command setBotAFK			 = Command("bot afk set",			this, Command::COMMAND_TYPE::ADMIN,	  	&MyClientClass::fn_setBotAFK);

	Command die					 = Command("die",					this, Command::COMMAND_TYPE::ADMIN,	  	&MyClientClass::fn_die);
	Command bannedOps			 = Command("banned_ops",			this, Command::COMMAND_TYPE::NON_ADMIN,	&MyClientClass::fn_bannedOps);
	Command sonarPing			 = Command("sonar_ping",			this, Command::COMMAND_TYPE::ADMIN,		&MyClientClass::fn_sonarPing,	true);
	Command fuckoff				 = Command("fuckoff",				this, Command::COMMAND_TYPE::ADMIN,	  	&MyClientClass::fn_leaveServer);

	void init();
	void readConfig();
	void parseServers();

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

	struct {
		std::string activity = "";
		uint64_t idleSince = 0;
		SleepyDiscord::Status status = SleepyDiscord::Status::online;
		bool AFK = false;
	} botStatus;

	inline static SleepyDiscord::Snowflake<SleepyDiscord::User> s_ownerID = 518216114665291786;
	inline static SleepyDiscord::Snowflake<SleepyDiscord::User> s_botID   = 783177811950960670;

	std::string m_config;

	// std::string used in place of SleepyDiscord::Snowflake to prevent needing to supply a hash
	std::unordered_map<std::string, SleepyDiscord::Server> m_servers;	// map server IDs to server objects
	std::unordered_map<std::string, SleepyDiscord::Snowflake<SleepyDiscord::Channel>> m_userDMchannelIDs; // map server IDs to DM channel IDs
	std::unordered_map<std::string, ServerBotSettings> m_serverBotSettings; // map server IDs to their respective settings struct
	std::unordered_map<std::string, std::pair<SleepyDiscord::User, bool>> m_bannedUsers; // map server IDs to users banned from servers 
																						 // and whether they were banned via the bot
	std::unordered_map<std::string, std::pair<SleepyDiscord::User, bool>> m_kickedUsers; // map server IDs to users kicked from the server
																						 // same thing with the bool

protected:
	// functions for bot - to be passed to their respective Command object 
	// server ID and user must be passed for permissions checking even if the function does not use it directly
	void fn_changePrefix		(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const std::string& acrNewPrefix);
	void fn_hello				(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID);
	void fn_echo				(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const std::string& acrMessage);
	void fn_dmUser				(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrDMedUserID, 	const std::string& acrMessage = "");
	void fn_muteVoice			(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrMutedUserID);
	void fn_unmuteVoice			(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrMutedUserID);
	void fn_muteText			(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrMutedUserID);
	void fn_unmuteText			(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrMutedUserID);
	void fn_kick				(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrKickedUserID, const std::string& acrReason = "");
	void fn_ban					(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrBannedUserID, const std::string& acrReason = "", int acDeleteMessageDays = 36500);
	void fn_unban				(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrBannedUserID, const std::string& acrReason = "");
	void fn_invite				(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrInvitedUserID);
	void fn_setBotAdminRole		(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& acrRoleID);
	void fn_setLogsChannel		(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID);
	void fn_logsDisable			(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, bool b = true);
	void fn_setSilent			(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, bool b = true);
	void fn_deleteMsg			(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, SleepyDiscord::Message& arMessage);
	void fn_logAction			(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const std::string& acrString);
	void fn_setPermissions		(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, COMMAND_PERMISSION aCommandPerm, COMMAND_TYPE aCommandType);
	//void fn_purgeMessages		(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, int aCount = 0);
	void fn_setChannelName		(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const std::string& acrName = "");
	void fn_setChannelTopic		(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const std::string& acrTopic = "");
	void fn_deleteChannel		(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID);
	//void fn_removeReactions	(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const SleepyDiscord::Snowflake<SleepyDiscord::Message>& acrMessageID);
	void fn_pinMessage			(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const SleepyDiscord::Snowflake<SleepyDiscord::Message>& acrMessageID);
	void fn_unpinMessage		(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const SleepyDiscord::Snowflake<SleepyDiscord::Message>& acrMessageID);
	void fn_changeNickname		(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrNicknamedUser, const std::string& acrNickname = "");
	void fn_removeRole			(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrRemovedUser, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& acrRoleID);
	void fn_deleteRole			(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& role);
	void fn_pruneUsers			(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, int aNumDays = 0);
	void fn_deleteInvite		(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const std::string& acrInviteCode);
	void fn_deleteChannelInvites(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID);
	void fn_deleteAllInvites	(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser);
	void fn_leaveServer			(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser);
	void fn_setStatus			(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const std::string& acrActivityName = "", const SleepyDiscord::Status acStatus = SleepyDiscord::Status::online, bool abAFK = false, int aIdleTime = 0);
	void fn_setBotActivity		(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const std::string& acrActivityName = "");
	void fn_setBotIdle			(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, int aIdleTime = 0);
	void fn_setBotStatus		(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Status acStatus = SleepyDiscord::Status::online);
	void fn_setBotAFK			(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, bool abAFK = false);

	void fn_die					(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID);
	void fn_bannedOps			(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID);
	void fn_sonarPing			(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrPingedUserID, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, unsigned int aCount = 0);

	static std::vector<std::string> split		 (const std::string& acrString); // split string into vector of words
	static std::string				getSnowflake (const std::string& acrString); // get ID from mention
	static COMMAND_TYPE				toCommandType(const std::string& acrString); // map string to command type
	static COMMAND_PERMISSION		toCommandPerm(const std::string& acrString); // map string to command perm
	static SleepyDiscord::Status	toStatus	 (const std::string& acrString); // map string to status
	static bool						isBot		 (const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID);
		   bool						isMuted		 (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID) const;
};

#endif