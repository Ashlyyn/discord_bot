#include <thread>
#include <chrono>

#include "bot_client.hpp"
#include "mention.hpp"

void MyClientClass::onMessage(SleepyDiscord::Message aMessage) {
	const std::string& lcrPrefix = m_serverBotSettings[aMessage.serverID].prefix;
	if (aMessage.startsWith(lcrPrefix + "prefix ")) {
		changePrefix(aMessage.serverID, aMessage.author, aMessage.channelID, aMessage.content.substr(lcrPrefix.size() + changePrefix.name.size() + 1));
	} else if (aMessage.startsWith(lcrPrefix + "hello")) {
		hello(aMessage.serverID, aMessage.author, aMessage.channelID);
	} else if (aMessage.startsWith(lcrPrefix + "echo ")) {
		echo(aMessage.serverID, aMessage.author, aMessage.channelID, aMessage.content.substr(lcrPrefix.size() + echo.name.size() + 1));
	} else if (aMessage.startsWith(lcrPrefix + "dm ")) {
		auto words = split(aMessage.content);
		dmUser(aMessage.serverID, aMessage.author, getSnowflake(words[1]), aMessage.content.substr(lcrPrefix.size() + dmUser.name.size() + 1 + words[1].size() + 1));
	} else if (aMessage.startsWith(lcrPrefix + "mute voice ")) {
		muteVoice(aMessage.serverID, aMessage.author, aMessage.content.substr(lcrPrefix.size() + muteVoice.name.size() + 1));
	} else if (aMessage.startsWith(lcrPrefix + "unmute voice ")) {
		unmuteVoice(aMessage.serverID, aMessage.author, aMessage.content.substr(lcrPrefix.size() + unmuteVoice.name.size() + 1));
	} else if (aMessage.startsWith(lcrPrefix + "mute text ")) {
		muteText(aMessage.serverID, aMessage.author, getSnowflake(aMessage.content.substr(lcrPrefix.size() + muteText.name.size() + 1)));
	} else if (aMessage.startsWith(lcrPrefix + "unmute text ")) {
		unmuteText(aMessage.serverID, aMessage.author, getSnowflake(aMessage.content.substr(lcrPrefix.size() + unmuteText.name.size() + 1)));
	} else if (aMessage.startsWith(lcrPrefix + "kick ")) {
		auto words = split(aMessage.content);
		if(words.size() == 2) {
			kick(aMessage.serverID, aMessage.author, getSnowflake(words[1]), "");
		} else {
			kick(aMessage.serverID, aMessage.author, getSnowflake(words[1]), aMessage.content.substr(lcrPrefix.size() + kick.name.size() + 1+ words[1].size() + 1));
		}
	} else if (aMessage.startsWith(lcrPrefix + "ban ")) {
		auto words = split(aMessage.content);
		if(words.size() == 2) {
			ban(aMessage.serverID, aMessage.author, getSnowflake(words[1]), "", 36500);
		} else if(words.size() == 3) {
			ban(aMessage.serverID, aMessage.author, getSnowflake(words[1]), "", std::stoi(words[2]));
		} else {
			ban(aMessage.serverID, aMessage.author, getSnowflake(words[1]), aMessage.content.substr(lcrPrefix.size() + ban.name.size() + 1 + words[1].size() + 1 + words[2].size() + 1), words[2]);
		}
	} else if (aMessage.startsWith(lcrPrefix + "unban ")) {
		auto words = split(aMessage.content);
		if(words.size() == 2) {
			unban(aMessage.serverID, aMessage.author, aMessage.channelID, words[1], "");
		} else {
			unban(aMessage.serverID, aMessage.author, aMessage.channelID, words[1], aMessage.content.substr(lcrPrefix.size() + unban.name.size() + 1 + words[1].size() + 1));
		}
	} else if (aMessage.startsWith(lcrPrefix + "invite ")) {
		auto words = split(aMessage.content);
		invite(aMessage.serverID, aMessage.author, aMessage.channelID, getSnowflake(words[1]));
	} else if (aMessage.startsWith(lcrPrefix + "bot_admin_role set ")) {
		setBotAdminRole(aMessage.serverID, aMessage.author, getSnowflake(aMessage.content.substr(lcrPrefix.size() + setBotAdminRole.name.size() + 1)));
	} else if (aMessage.startsWith(lcrPrefix + "nologs")) {
		logsDisable(aMessage.serverID, aMessage.author);
	} else if (aMessage.startsWith(lcrPrefix + "logs disable")) {
		logsDisable(aMessage.serverID, aMessage.author);
	} else if (aMessage.startsWith(lcrPrefix + "logs enable")) {
		logsDisable(aMessage.serverID, aMessage.author, false);
	} else if (aMessage.startsWith(lcrPrefix + "logs ")) {
		setLogsChannel(aMessage.serverID, aMessage.author, SleepyDiscord::Snowflake<SleepyDiscord::Channel>(getSnowflake(aMessage.content.substr(lcrPrefix.size() + setLogsChannel.name.size() + 1))));
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
	} else if (aMessage.startsWith(lcrPrefix + "sonar_ping")) {
		int lNumPings;
		try {
			lNumPings = stoi(split(aMessage.content)[2]);
		} catch(const std::out_of_range& e) {
			std::fprintf(stderr, "onMessage(): sonar_ping provided out of range value.\n");
			echo(aMessage.serverID, aMessage.author, aMessage.channelID, "Value is too large, must be less than 2^32");
			lNumPings = 0;
		}
		sonarPing(aMessage.serverID, aMessage.author, aMessage.channelID, getSnowflake(split(aMessage.content)[1]), lNumPings);
	}

	else if(aMessage.startsWith(lcrPrefix)) {
		const std::string lcMessage = "Unknown command.";
		echo(aMessage.serverID, aMessage.author, aMessage.channelID, lcMessage);
	}

	if(isMuted(aMessage.serverID, aMessage.author.ID)) {
		deleteMsg(aMessage.serverID, aMessage.author, aMessage);
	}
}

void MyClientClass::onServer(SleepyDiscord::Server aServer) {
	m_servers[aServer.ID] = aServer;
	m_serverBotSettings[aServer.ID] = ServerBotSettings(); // add server ID to m_serverBotSettings and default-initialize value object
}

void MyClientClass::onBan(SleepyDiscord::Snowflake<SleepyDiscord::Server> aServerID, SleepyDiscord::User aBannedUser) {
	std::mutex mutex;
	std::lock_guard<std::mutex> lock(mutex);
	
	// if user wasn't already added to m_bannedUsers by ban()
		if(m_bannedUsers.find(aBannedUser.ID) == m_bannedUsers.end()) {
		// if user wasn't already added, then they weren't manually banned (set bool value to false)
		m_bannedUsers[aBannedUser.ID] = std::make_pair(aBannedUser, false);
	}
	// client automatically calls onRemoveUser(), which handles the logging
}

void MyClientClass::onRemoveMember(SleepyDiscord::Snowflake<SleepyDiscord::Server> aServerID, SleepyDiscord::User aRemovedUser) {
	std::mutex mutex;
	std::lock_guard<std::mutex> lock(mutex);

	std::time_t lTime = std::time(nullptr);
	std::put_time(std::gmtime(&lTime), "%c"); // get date/time info for log
	std::stringstream lTimeSS;
	lTimeSS << lTime;
	const std::string lcTimeStr = lTimeSS.str(); // hacky way to get std::string from time_t
	std::string lLog;
	
	m_servers.at(aServerID).members.erase(m_servers.at(aServerID).findMember(aRemovedUser.ID)); // remove user from cached server
	// if user was banned, not kicked
	if((m_bannedUsers.find(aRemovedUser.ID) != m_bannedUsers.end()) && (m_kickedUsers.find(aRemovedUser.ID) == m_kickedUsers.end())) {
		// if user was not banned by bot, log ban
		// if user was banned by bot, ban will have already been logged by ban()
		if(m_bannedUsers.at(aRemovedUser.ID).second == false) {
			lLog = "**BANNED USER**\n```User: " + aRemovedUser.username + "#" + aRemovedUser.discriminator + "\nBanned by: Unknown\nReason given:\nOn: " + lcTimeStr +"```";
			logAction(aServerID, aRemovedUser, lLog);
		}
		// erase user if user was previously kicked, and now banned
		m_kickedUsers.erase(m_kickedUsers.find(aRemovedUser.ID));
	}
	// else if user was manually kicked, but not banned
	else if((m_bannedUsers.find(aRemovedUser.ID) == m_bannedUsers.end()) && (m_kickedUsers.find(aRemovedUser.ID) != m_kickedUsers.end())) {
		// same as above
		if(m_kickedUsers.at(aRemovedUser.ID).second == false) {
			lLog = "**KICKED USER**\n```User: " + aRemovedUser.username + "#" + aRemovedUser.discriminator + "\nBanned by: Unknown\nReason given:\nOn: " + lcTimeStr +"```";
			logAction(aServerID, aRemovedUser, lLog);
		}
	}
	// else user was not manually kicked/left on their own 
	// (can't detect difference between non-manual kick and normal leave)
	else {
		lLog = "**KICKED USER/USER LEFT**\n```User: " + aRemovedUser.username + "#" + aRemovedUser.discriminator + "\nOn: " + lcTimeStr +"```";
		logAction(aServerID, aRemovedUser, lLog);
	}
}



void MyClientClass::fn_changePrefix(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const std::string& acrNewPrefix) {
	if(acrNewPrefix.find(" ") != std::string::npos) {
		const std::string lcMessage = "Prefix may not contain whitespace.";
		echo(arServerID, acrUser, acrChannelID, lcMessage);
	}
	m_serverBotSettings.at(arServerID).prefix = acrNewPrefix;
}

void MyClientClass::fn_hello(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID) {
	echo(arServerID, acrUser, acrChannelID, "Hello, " + Mention<SleepyDiscord::User>(acrUser));
}

void MyClientClass::fn_echo(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const std::string& acrMessage) {
	if (m_serverBotSettings.at(arServerID).silent == false) {
		sendMessage(acrChannelID, acrMessage);
	}
}

void MyClientClass::fn_dmUser(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrDMedUserID, const std::string& acrMessage) {
	if(m_userDMchannelIDs.find(acrDMedUserID) == m_userDMchannelIDs.end()) { // if user DM channel was not already created
		m_userDMchannelIDs[acrDMedUserID] = SleepyDiscord::Channel(createDirectMessageChannel(acrDMedUserID)).ID;
	}
	const SleepyDiscord::Snowflake<SleepyDiscord::Channel> lcChannelID = m_userDMchannelIDs[acrDMedUserID];
	sendMessage(lcChannelID, acrMessage);
}

void MyClientClass::fn_muteVoice(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrMutedUserID) {
	muteServerMember(arServerID, acrMutedUserID, true);
}

void MyClientClass::fn_unmuteVoice(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrMutedUserID) {
	muteServerMember(arServerID, acrMutedUserID, false);
}

void MyClientClass::fn_muteText(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrMutedUserID) {
	if(std::count(m_serverBotSettings.at(arServerID).mutedUserIDs.begin(), m_serverBotSettings.at(arServerID).mutedUserIDs.end(), acrMutedUserID) == 0) { // if user is not already text-muted
		m_serverBotSettings.at(arServerID).mutedUserIDs.push_back(acrMutedUserID);
	}
}

void MyClientClass::fn_unmuteText(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrMutedUserID) {
	if(std::count(m_serverBotSettings.at(arServerID).mutedUserIDs.begin(), m_serverBotSettings.at(arServerID).mutedUserIDs.end(), acrMutedUserID) > 0) { // if user is text-muted, remove from mutedUserIDs
		m_serverBotSettings.at(arServerID).mutedUserIDs.erase(std::find(m_serverBotSettings.at(arServerID).mutedUserIDs.begin(), m_serverBotSettings.at(arServerID).mutedUserIDs.end(), acrMutedUserID)); 
	}
}

void MyClientClass::fn_kick(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrKickedUserID, const std::string& acrReason) {
	std::mutex mutex;
	std::lock_guard<std::mutex> lock(mutex);

	SleepyDiscord::User lKickedUser = getUser(acrKickedUserID);
	m_kickedUsers[acrKickedUserID] = std::make_pair(lKickedUser, true); // bool value set to true to indicate kick via bot
	kickMember(arServerID, lKickedUser);
	std::time_t lTime = std::time(nullptr);
	std::put_time(std::gmtime(&lTime), "%c"); // get date/time info for log
	std::stringstream lTimeSS;
	lTimeSS << lTime;
	const std::string lcTimeStr = lTimeSS.str(); // hacky time_t thing again
	std::string lLog;
	if(acrReason == "") {
		lLog = std::string("**KICKED USER**\n```User: " + lKickedUser.username + "#" + lKickedUser.discriminator + "\nBanned by: " + acrUser.username + "#" + acrUser.discriminator + "\nReason given:\nOn: " + lcTimeStr + "```");
	} else {
		lLog = std::string("**KICKED USER**\n```User: " + lKickedUser.username + "#" + lKickedUser.discriminator + "\nBanned by: " + acrUser.username + "#" + acrUser.discriminator + "\nReason given: " + acrReason + "\nOn: " + lcTimeStr + "```");
	}
	logAction(arServerID, acrUser, lLog);
}

void MyClientClass::fn_ban(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrBannedUserID, const std::string& acrReason, int acDeleteMessageDays) {
	std::mutex mutex;
	std::lock_guard<std::mutex> lock(mutex);

	SleepyDiscord::User lBannedUser = getUser(acrBannedUserID);
	m_bannedUsers[acrBannedUserID] = std::make_pair(lBannedUser, true); // bool value set to true to indicate ban via bot
	banMember(arServerID, lBannedUser, acDeleteMessageDays, acrReason);
	std::time_t lTime = std::time(nullptr);
	std::put_time(std::gmtime(&lTime), "%c"); // get time info for log
	std::stringstream lTimeSS;
	lTimeSS << lTime;
	const std::string lcTimeStr = lTimeSS.str(); // hacky time thing yet again
	std::string lLog;
	if(acrReason == "") {
		lLog = std::string("**BANNED USER**\n```User: " + lBannedUser.username + "#" + lBannedUser.discriminator + "\nBanned by: " + acrUser.username + "#" + acrUser.discriminator + "\nReason given:\nOn: " + lcTimeStr + "```");
	} else {
		lLog = std::string("**BANNED USER**\n```User: " + lBannedUser.username + "#" + lBannedUser.discriminator + "\nBanned by: " + acrUser.username + "#" + acrUser.discriminator + "\nReason given: " + acrReason + "\nOn: " + lcTimeStr + "```");
	}
	logAction(arServerID, acrUser, lLog);
}

void MyClientClass::fn_unban(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrBannedUserID, const std::string& acrReason) {
	auto lBannedUsers = getBans(arServerID).vector();
	SleepyDiscord::User lBannedUser;

	for(const auto& lUser : lBannedUsers) {
		if(lBannedUser.ID == acrBannedUserID) {
			lBannedUser = lUser;
		}
	}

	if(lBannedUser.ID == "") {
		const std::string lcLog = "User not found.";
		echo(arServerID, acrUser, acrChannelID, lcLog);
		return;
	} else {
		std::mutex mutex;
		std::lock_guard lock(mutex);

		m_bannedUsers.erase(acrBannedUserID); // remove user from ban list
		unbanMember(arServerID, acrBannedUserID);
		std::time_t lTime = std::time(nullptr);
		std::put_time(std::gmtime(&lTime), "%c");
		std::stringstream lTimeSS;
		lTimeSS << lTime;
		const std::string lcTimeStr = lTimeSS.str(); // once more...
		std::string lLog;
		if(acrReason == "") {
			lLog = std::string("**UNBANNED USER**\n```User: " + lBannedUser.username + "#" + lBannedUser.discriminator + "\nUnbanned by: " + acrUser.username + "#" + acrUser.discriminator + "\nReason given:\nOn: " + lcTimeStr + "```");
		} else {
			lLog = std::string("**UNBANNED USER**\n```User: " + lBannedUser.username + "#" + lBannedUser.discriminator + "\nUnbanned by: " + acrUser.username + "#" + acrUser.discriminator + "\nReason given: " + acrReason + "\nOn: " + lcTimeStr + "```");
		}
		logAction(arServerID, acrUser, lLog);
	}
}

void MyClientClass::fn_invite(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrInvitedUserID) {
	SleepyDiscord::Invite invite = createChannelInvite(acrChannelID, 0, 1, false, false);
	const std::string lcInviteCode = invite.code;
	dmUser(arServerID, acrUser, acrInvitedUserID, "https://discord.gg/" + lcInviteCode);
}

void MyClientClass::fn_setBotAdminRole(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& acrRoleID) {
	m_serverBotSettings.at(arServerID).botAdminRoleID = acrRoleID;
	logAction(arServerID, acrUser, "**BOT ADMIN ROLE SET**\n```Set to: " + acrRoleID.string() + "\nSet by: " + acrUser.username + "#" + acrUser.discriminator + "\n```");
}

void MyClientClass::fn_setLogsChannel(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID) {
	m_serverBotSettings.at(arServerID).logsChannelID = acrChannelID;
	logAction(arServerID, acrUser, "Logs enabled in " + Mention<SleepyDiscord::Snowflake<SleepyDiscord::Channel>>(acrChannelID));
}

void MyClientClass::fn_logsDisable(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, bool b) {
	m_serverBotSettings.at(arServerID).noLogs = b;
}

void MyClientClass::fn_setSilent(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, bool b) {
	m_serverBotSettings.at(arServerID).silent = b;
}

void MyClientClass::fn_deleteMsg(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, SleepyDiscord::Message& arMessage) {
	deleteMsg(arMessage.serverID, arMessage.member, arMessage);
	std::string lLog = "**MESSAGE DELETE:**\n```Message ID: " + arMessage.ID.string() + "\nDeleted by: " + acrUser.username + "#" + acrUser.discriminator + "\nChannel: " + arMessage.channelID.string() + "\nMessage content: " + arMessage.content + "\n```";
	logAction(arServerID, acrUser, lLog);
}

void MyClientClass::fn_logAction(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const std::string& acrString) {
	if (m_serverBotSettings.at(arServerID).noLogs == false) {
		if (m_serverBotSettings.at(arServerID).logsChannelID != SleepyDiscord::Snowflake<SleepyDiscord::Channel>()) {
			echo(arServerID, acrUser, m_serverBotSettings.at(arServerID).logsChannelID, acrString);
		}
	}
}

void MyClientClass::fn_setPermissions(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, COMMAND_PERMISSION aCommandPerm, COMMAND_TYPE aCommandType) {
	if(aCommandType == ROLE_ALL) {
		m_serverBotSettings.at(arServerID).permissions[COMMAND_TYPE::ADMIN] = aCommandPerm;
		m_serverBotSettings.at(arServerID).permissions[COMMAND_TYPE::NON_ADMIN] = aCommandPerm;
	} else {
		m_serverBotSettings.at(arServerID).permissions[aCommandType] = aCommandPerm;
	}

	// used for log
	std::map<COMMAND_PERMISSION, std::string> lPerms = {
		{ COMMAND_PERMISSION::OWNER_ONLY, std::string("owner_only") },
		{ COMMAND_PERMISSION::BOT_ADMIN,  std::string("bot_admin")  },
		{ COMMAND_PERMISSION::CMD_ALL,    std::string("all") 		}
	};
	std::map<COMMAND_TYPE, std::string> lType = {
		{ COMMAND_TYPE::ADMIN, 	   std::string("admin") 	},
		{ COMMAND_TYPE::NON_ADMIN, std::string("non_admin") },
		{ COMMAND_TYPE::ROLE_ALL,  std::string("all") 		}
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

void MyClientClass::fn_sonarPing(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrPingedUserID, unsigned int aCount) {
	if(aCount == 0) {
		return;
	} else {
		std::string lMention = Mention<SleepyDiscord::User>(acrPingedUserID);
		for(int i = 0; i < aCount; i++) {
			echo(arServerID, acrUser, acrChannelID, lMention + " Sonar ping.");
			sleep(500);
			echo(arServerID, acrUser, acrChannelID, lMention + " Sonar pong.");
			sleep(2000);
		}
	}
}


std::vector<std::string> MyClientClass::split(const std::string& acrString) { // split std::string into vector of words delimited by whitespace
	std::vector<std::string> lVec;
	std::string lTemp;
    std::stringstream lSS(acrString);

    while (lSS >> lTemp) {
        lVec.push_back(lTemp);
	}
	return lVec;
}

std::string MyClientClass::getSnowflake(const std::string& acrString) {
	if(acrString.find("<@!") != std::string::npos) { // user mention
		return acrString.substr(3, acrString.size() - 3 - 1);
	}
	else if(acrString.find("<#") != std::string::npos) { // channel mention
		return acrString.substr(2, acrString.size() - 2 - 1);
	}
	else if (acrString.find("<@&") != std::string::npos) { // role mention
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
	if(std::count(m_serverBotSettings.at(acrServerID).mutedUserIDs.begin(), m_serverBotSettings.at(acrServerID).mutedUserIDs.end(), acrUser) >= 1) {
		return true;
	} else {
		return false;
	}
}