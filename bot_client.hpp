#ifndef _BOT_CLIENT_H_
#define _BOT_CLIENT_H_

#include <map>
#include <vector>

#include "sleepy_discord/sleepy_discord.h"

#include "command.hpp"
#include "server_bot_settings.hpp"
#include "constants.hpp"
#include "server_cache.hpp"

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
	Command fuckoff				 = Command("fuckoff",				this, Command::COMMAND_TYPE::ADMIN,	  	&MyClientClass::fn_leaveServer); // more or less an alias of leave

	void init			 (); // initialization - grab data from server_info.json, set s_botID
	void readConfig		 (); // read config.json, verify ownerID is valid, set s_ownerID if so, exit if not
	void readServerInfo	 (); // read server_info.json into m_serverInfoJSON, or create if not already present
	void parseServers	 (); // parse serverInfo and set bot settings accordingly
	void addServerInfo   (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID); // add new server to server info
	void updateServerInfo(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID); // update existing server info
	void removeServerInfo(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID); // remove server info (i.e. if server is deleted)

	// client function overrides
	void onMessage		(SleepyDiscord::Message aMessage) override;
	void onServer		(SleepyDiscord::Server aServer) override;
	void onDeleteServer (SleepyDiscord::UnavailableServer aRemovedServer) override;
	void onBan			(SleepyDiscord::Snowflake<SleepyDiscord::Server> aServerID, SleepyDiscord::User aUser) override;
	void onUnban		(SleepyDiscord::Snowflake<SleepyDiscord::Server> aServerID, SleepyDiscord::User aUnbannedUser) override;
	void onMember		(SleepyDiscord::Snowflake<SleepyDiscord::Server> aServerID, SleepyDiscord::ServerMember aMember) override;
	void onRemoveMember	(SleepyDiscord::Snowflake<SleepyDiscord::Server> aServerID, SleepyDiscord::User aRemovedUser) override;

	// helper functions

	// public to allow access from Command
	bool hasRole(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& acrRoleID);

	inline static bool isOwner(const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID) {
		return acrUserID == s_ownerID;
	}
	

    enum COMMAND_PERMISSION {
		PERM_ERR = -1,
		OWNER_ONLY,
		BOT_ADMIN,
		CMD_ALL
	};

	enum COMMAND_TYPE {
		TYPE_ERR = -1,
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

	// server cache, used to reduce web requests when possible for efficiency purposes
	inline static ServerCache m_cache = ServerCache();

	// default-initialized to prevent linker errors
	inline static SleepyDiscord::Snowflake<SleepyDiscord::User> s_botID	  = SleepyDiscord::Snowflake<SleepyDiscord::User>();
	inline static SleepyDiscord::Snowflake<SleepyDiscord::User> s_ownerID = SleepyDiscord::Snowflake<SleepyDiscord::User>();

	std::string m_configJSON; // config info from config.json
	std::string m_serverInfoJSON; // server info from server_info.json


protected:
	// functions for bot - to be passed to their respective Command object 
	// server ID and user must be passed for permissions checking even if the function does not use it directly
	void fn_changePrefix		(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const std::string& acrNewPrefix);
	void fn_hello				(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID);
	void fn_echo				(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const std::string& acrMessage);
	void fn_dmUser				(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrDMedUserID, 	const std::string& acrMessage = "");
	void fn_muteVoice			(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrMutedUserID);
	void fn_unmuteVoice			(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrMutedUserID);
	void fn_muteText			(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrMutedUserID);
	void fn_unmuteText			(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrMutedUserID);
	void fn_kick				(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrKickedUserID, const std::string& acrReason = "");
	void fn_ban					(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrBannedUserID, const std::string& acrReason = "", int acDeleteMessageDays = 36500);
	void fn_unban				(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrBannedUserID, const std::string& acrReason = "");
	void fn_invite				(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrInvitedUserID);
	void fn_setBotAdminRole		(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& acrRoleID);
	void fn_setLogsChannel		(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID);
	void fn_logsDisable			(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, bool b = true);
	void fn_setSilent			(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, bool b = true);
	void fn_deleteMsg			(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, SleepyDiscord::Message& arMessage);
	void fn_logAction			(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const std::string& acrString);
	void fn_setPermissions		(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, COMMAND_PERMISSION aCommandPerm, COMMAND_TYPE aCommandType);
	//void fn_purgeMessages		(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, int aCount = 0);
	void fn_setChannelName		(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const std::string& acrName = "");
	void fn_setChannelTopic		(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const std::string& acrTopic = "");
	void fn_deleteChannel		(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID);
	//void fn_removeReactions	(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const SleepyDiscord::Snowflake<SleepyDiscord::Message>& acrMessageID);
	void fn_pinMessage			(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const SleepyDiscord::Snowflake<SleepyDiscord::Message>& acrMessageID);
	void fn_unpinMessage		(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const SleepyDiscord::Snowflake<SleepyDiscord::Message>& acrMessageID);
	void fn_changeNickname		(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrNicknamedUser, const std::string& acrNickname = "");
	void fn_removeRole			(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrRemovedUser, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& acrRoleID);
	void fn_deleteRole			(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& role);
	void fn_pruneUsers			(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, int aNumDays = 0);
	void fn_deleteInvite		(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const std::string& acrInviteCode);
	void fn_deleteChannelInvites(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID);
	void fn_deleteAllInvites	(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID);
	void fn_leaveServer			(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID);
	void fn_setStatus			(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const std::string& acrActivityName = "", const SleepyDiscord::Status acStatus = SleepyDiscord::Status::online, bool abAFK = false, int aIdleTime = 0);
	void fn_setBotActivity		(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const std::string& acrActivityName = "");
	void fn_setBotIdle			(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, int aIdleTime = 0);
	void fn_setBotStatus		(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Status acStatus = SleepyDiscord::Status::online);
	void fn_setBotAFK			(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, bool abAFK = false);

	void fn_die					(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID);
	void fn_bannedOps			(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID);
	void fn_sonarPing			(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrPingedUserID, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, unsigned int aCount = 0);

	static std::vector<std::string> split		 (const std::string& acrString); // split string into vector of words
	static std::string				getSnowflake (const std::string& acrString); // get ID from mention
	static COMMAND_TYPE				toCommandType(const std::string& acrString); // map string to command type
	static COMMAND_PERMISSION		toCommandPerm(const std::string& acrString); // map string to command perm
	static SleepyDiscord::Status	toStatus	 (const std::string& acrString); // map string to status
		  		  bool 				hasPermission(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Permission acPermission);
		   		  bool				isMuted		 (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID) const;

	inline static bool isBot(const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID) {
		return acrUserID == s_botID;
	}
};

#endif