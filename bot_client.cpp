#include "bot_client.hpp"
#include "mention.hpp"

void MyClientClass::init() {
	
}

void MyClientClass::onMessage(SleepyDiscord::Message aMessage) {
	const std::string& lcrPrefix = m_serverBotSettings[aMessage.serverID].prefix;
	const auto lcWords = split(aMessage.content);
	if (aMessage.startsWith(lcrPrefix + "prefix ")) {
		changePrefix(aMessage.serverID, aMessage.author, aMessage.channelID, aMessage.content.substr(lcrPrefix.size() + changePrefix.name.size() + 1));
	} else if (aMessage.startsWith(lcrPrefix + "hello")) {
		hello(aMessage.serverID, aMessage.author, aMessage.channelID);
	} else if (aMessage.startsWith(lcrPrefix + "echo ")) {
		echo(aMessage.serverID, aMessage.author, aMessage.channelID, aMessage.content.substr(lcrPrefix.size() + echo.name.size() + 1));
	} else if (aMessage.startsWith(lcrPrefix + "dm ")) {
		std::string lSnowflake;
		try {
			lSnowflake = getSnowflake(lcWords[1]);
		} catch(std::runtime_error& e) {
			fprintf(stderr, "onMessage(): dm: %s\n", e.what());
			return;
		}
		dmUser(aMessage.serverID, aMessage.author, lSnowflake, aMessage.content.substr(lcrPrefix.size() + dmUser.name.size() + 1 + lcWords[1].size() + 1));
	} else if (aMessage.startsWith(lcrPrefix + "mute voice ")) {
		muteVoice(aMessage.serverID, aMessage.author, aMessage.content.substr(lcrPrefix.size() + muteVoice.name.size() + 1));
	} else if (aMessage.startsWith(lcrPrefix + "unmute voice ")) {
		unmuteVoice(aMessage.serverID, aMessage.author, aMessage.content.substr(lcrPrefix.size() + unmuteVoice.name.size() + 1));
	} else if (aMessage.startsWith(lcrPrefix + "mute text ")) {
		std::string lSnowflake;
		try {
			lSnowflake = getSnowflake(lcWords[2]);
		} catch(std::runtime_error& e) {
			fprintf(stderr, "onMessage(): mute text: %s\n", e.what());
			return;
		}
		muteText(aMessage.serverID, aMessage.author, getSnowflake(aMessage.content.substr(lcrPrefix.size() + muteText.name.size() + 1)));
	} else if (aMessage.startsWith(lcrPrefix + "unmute text ")) {
		std::string lSnowflake;
		try {
			lSnowflake = getSnowflake(lcWords[2]);
		} catch(std::runtime_error& e) {
			fprintf(stderr, "onMessage(): unmute text: %s\n", e.what());
			return;
		}
		unmuteText(aMessage.serverID, aMessage.author, getSnowflake(aMessage.content.substr(lcrPrefix.size() + unmuteText.name.size() + 1)));
	} else if (aMessage.startsWith(lcrPrefix + "kick ")) {
		std::string lSnowflake;
		try {
			lSnowflake = getSnowflake(lcWords[1]);
		} catch(std::runtime_error& e) {
			fprintf(stderr, "onMessage(): kick: %s\n", e.what());
			return;
		}
		if(lcWords.size() == 2) {
			kick(aMessage.serverID, aMessage.author, lSnowflake, "");
		} else {
			kick(aMessage.serverID, aMessage.author, lSnowflake, aMessage.content.substr(lcrPrefix.size() + kick.name.size() + 1 + lcWords[1].size() + 1));
		}
	} else if (aMessage.startsWith(lcrPrefix + "ban ")) {
		std::string lSnowflake;
		try {
			lSnowflake = getSnowflake(lcWords[1]);
		} catch(std::runtime_error& e) {
			fprintf(stderr, "onMessage(): ban: %s\n", e.what());
			return;
		}
		if(lcWords.size() == 2) {
			ban(aMessage.serverID, aMessage.author, lSnowflake, "", 36500);
		} else if(lcWords.size() == 3) {
			ban(aMessage.serverID, aMessage.author, lSnowflake, "", std::stoi(lcWords[2]));
		} else {
			ban(aMessage.serverID, aMessage.author, lSnowflake, aMessage.content.substr(lcrPrefix.size() + ban.name.size() + 1 + lcWords[1].size() + 1 + lcWords[2].size() + 1), lcWords[2]);
		}
	} else if (aMessage.startsWith(lcrPrefix + "unban ")) {
		if(lcWords.size() == 2) {
			unban(aMessage.serverID, aMessage.author, aMessage.channelID, lcWords[1], "");
		} else {
			unban(aMessage.serverID, aMessage.author, aMessage.channelID, lcWords[1], aMessage.content.substr(lcrPrefix.size() + unban.name.size() + 1 + lcWords[1].size() + 1));
		}
	} else if (aMessage.startsWith(lcrPrefix + "invite send ")) {
		std::string lSnowflake;
		try {
			lSnowflake = getSnowflake(lcWords[2]);
		} catch(std::runtime_error& e) {
			fprintf(stderr, "onMessage(): invite send: %s\n", e.what());
			return;
		}
		invite(aMessage.serverID, aMessage.author, aMessage.channelID, lSnowflake);
	} else if (aMessage.startsWith(lcrPrefix + "bot_admin_role set ")) {
		std::string lSnowflake;
		try {
			lSnowflake = getSnowflake(lcWords[2]);
		} catch(std::runtime_error& e) {
			fprintf(stderr, "onMessage(): bot_admin_role set: %s\n", e.what());
			return;
		}
		setBotAdminRole(aMessage.serverID, aMessage.author, lSnowflake);
	} else if (aMessage.startsWith(lcrPrefix + "nologs")) {
		logsDisable(aMessage.serverID, aMessage.author);
	} else if (aMessage.startsWith(lcrPrefix + "logs disable")) {
		logsDisable(aMessage.serverID, aMessage.author);
	} else if (aMessage.startsWith(lcrPrefix + "logs enable")) {
		logsDisable(aMessage.serverID, aMessage.author, false);
	} else if (aMessage.startsWith(lcrPrefix + "logs ")) {
		std::string lSnowflake;
		try {
			lSnowflake = getSnowflake(lcWords[1]);
		} catch(std::runtime_error& e) {
			fprintf(stderr, "onMessage(): logs: %s\n", e.what());
			return;
		}
		setLogsChannel(aMessage.serverID, aMessage.author, SleepyDiscord::Snowflake<SleepyDiscord::Channel>(lSnowflake));
	} else if (aMessage.startsWith(lcrPrefix + "silent")) {
		setSilent(aMessage.serverID, aMessage.author);
	} else if (aMessage.startsWith(lcrPrefix + "nosilent")) {
		setSilent(aMessage.serverID, aMessage.author, false);
	} else if (aMessage.startsWith(lcrPrefix + "delete ")) {
		deleteMsg(aMessage.serverID, aMessage.author, aMessage);
	} else if (aMessage.startsWith(lcrPrefix + "permissions set ")) {
		setPermissions(aMessage.serverID, aMessage.author, toCommandPerm(split(aMessage.content)[3]), toCommandType(split(aMessage.content)[2]));
	} else if (aMessage.startsWith(lcrPrefix + "channel rename ")) {
		std::string lSnowflake;
		try {
			lSnowflake = getSnowflake(lcWords[2]);
		} catch(std::runtime_error& e) {
			fprintf(stderr, "onMessage(): channel rename: %s\n", e.what());
			return;
		}
		renameChannel(aMessage.serverID, aMessage.author, lSnowflake, lcWords[3]);
	} else if (aMessage.startsWith(lcrPrefix + "channel topic set ")) {
		std::string lSnowflake;
		try {
			lSnowflake = getSnowflake(lcWords[3]);
		} catch(std::runtime_error& e) {
			fprintf(stderr, "onMessage(): channel topic set: %s\n", e.what());
			return;
		}
		setChannelTopic(aMessage.serverID, aMessage.author, lSnowflake, aMessage.content.substr(lcrPrefix.size() + setChannelTopic.name.size() + 1 + lcWords[3].size() + 1));
	} else if (aMessage.startsWith(lcrPrefix + "channel delete ")) {
		
		std::string lSnowflake;
		try {
			lSnowflake = getSnowflake(lcWords[2]);
		} catch(std::runtime_error& e) {
			fprintf(stderr, "onMessage(): channel delete: %s\n", e.what());
			return;
		}
		removeChannel(aMessage.serverID, aMessage.author, lSnowflake);
	} else if (aMessage.startsWith(lcrPrefix + "pin ")) { // http error
		//pin(aMessage.serverID, aMessage.author, aMessage.channelID, split(aMessage.content)[1]);
	} else if (aMessage.startsWith(lcrPrefix + "unpin ")) { // http error
		//unpin(aMessage.serverID, aMessage.author, aMessage.channelID, split(aMessage.content)[1]);
	} else if (aMessage.startsWith(lcrPrefix + "nickname ")) { // discord permissions error on changing other users' nicknames
		std::string lSnowflake;
		try {
			lSnowflake = getSnowflake(lcWords[1]);
		} catch(std::runtime_error& e) {
			fprintf(stderr, "onMessage(): nickname: %s\n", e.what());
			return;
		}
		changeNickname(aMessage.serverID, aMessage.author, lSnowflake, aMessage.content.substr(lcrPrefix.size() + changeNickname.name.size() + 1 + lcWords[1].size() + 1));
	} else if (aMessage.startsWith(lcrPrefix + "role revoke ")) {
		
		std::string lSnowflake1;
		std::string lSnowflake2;
		try {
			lSnowflake1 = getSnowflake(lcWords[2]);
			lSnowflake2 = getSnowflake(lcWords[3]);
		} catch(std::runtime_error& e) {
			fprintf(stderr, "onMessage(): role revoke: %s\n", e.what());
			return;
		}
		revokeRole(aMessage.serverID, aMessage.author, lSnowflake1, lSnowflake2);
	} else if (aMessage.startsWith(lcrPrefix + "role delete ")) {
		std::string lSnowflake;
		try {
			lSnowflake = getSnowflake(lcWords[2]);
		} catch(std::runtime_error& e) {
			fprintf(stderr, "onMessage(): mute text: %s\n", e.what());
			return;
		}
		rmRole(aMessage.serverID, aMessage.author, lSnowflake);
	} else if (aMessage.startsWith(lcrPrefix + "prune ")) {
		int lNumDays;
		try {
			lNumDays = std::stoi(split(aMessage.content)[1]);
		} catch(std::out_of_range& e) {
			fprintf(stderr, "onMessage(): prune provided with out of range value.\n");
			lNumDays = 0;
		}
		revokeRole(aMessage.serverID, aMessage.author, lNumDays);
	} else if (aMessage.startsWith(lcrPrefix + "invite delete ")) {
		deleteInviteCode(aMessage.serverID, aMessage.author, split(aMessage.content)[2]);
	} else if (aMessage.startsWith(lcrPrefix + "channel invites delete ")) {
		std::string lSnowflake;
		try {
			lSnowflake = getSnowflake(lcWords[3]);
		} catch(std::runtime_error& e) {
			fprintf(stderr, "onMessage(): channel invites delete: %s\n", e.what());
			return;
		}
		deleteChannelInvites(aMessage.serverID, aMessage.author, lSnowflake);
	} else if (aMessage.startsWith(lcrPrefix + "invites delete all")) {
		deleteServerInvites(aMessage.serverID, aMessage.author);
	} else if (aMessage.startsWith(lcrPrefix + "leave")) { // not verified working
		leave(aMessage.serverID, aMessage.author);
	} else if (aMessage.startsWith(lcrPrefix + "status ")) { // not verified working
		if(lcWords.size() == 1) {
			fprintf(stderr, "onMessage(): status: provided with no arguments.\n");
			return;
		} else {
			const std::string& lcrActivity = lcWords[1];
			SleepyDiscord::Status lStatus = SleepyDiscord::Status::online;
			bool lbAFK = false;
			int lIdleTime = 0;
			if(lcWords.size() > 2) {
				lStatus = toStatus(lcWords[2]);
			} 
			if(lcWords.size() > 3) {
				if(lcWords[3] == "1" || lcWords[3] == "true") {
					lbAFK = true;
				} else if (lcWords[3] == "0" || lcWords[3] == "false") {
					lbAFK = false;
				} else {
					throw std::runtime_error("onMessage(): status: provided with invalid value for bool value.\n");
				}
			}
			if(lcWords.size() > 4) {
				try {
					lIdleTime = std::stoi(lcWords[4]);
				} catch(std::out_of_range& e) {
					std::fprintf(stderr, "onMessage(): status: provided with out of range value for lIdleTime.\n");
					return;
				}
			}
			status(aMessage.serverID, aMessage.author, lcrActivity, lStatus, lbAFK, lIdleTime);
		}
	} else if (aMessage.startsWith(lcrPrefix + "bot activity set")) {
		setBotActivity(aMessage.serverID, aMessage.author, aMessage.content.substr(setBotActivity.name.size() + 1));
	} else if (aMessage.startsWith(lcrPrefix + "bot idle set")) {
		uint64_t lIdleTime;
		try {
			lIdleTime = std::stoi(lcWords[3]);
		} catch(const std::exception& e) {
			std::fprintf(stderr, "onMessage(): bot idle set: provided with out of range value for lIdleTime.\n");
			return;
		}
		setBotIdle(aMessage.serverID, aMessage.author, lIdleTime);
	} else if (aMessage.startsWith(lcrPrefix + "bot status set")) {
		setBotStatus(aMessage.serverID, aMessage.author, toStatus(lcWords[3]));
	} else if (aMessage.startsWith(lcrPrefix + "bot afk set")) {
		bool b;
		if(lcWords[3] == "1" || lcWords[3] == "true") {
			b = true;
		} else if(lcWords[3] == "0" || lcWords[3] == "false") {
			b = false;
		}
		else {
			std::fprintf(stderr, "onMessage(): bot afk set: provided with invalid bool value.\n");
			return;
		}
		setBotAFK(aMessage.serverID, aMessage.author, b);
	}
	
	else if (aMessage.startsWith(lcrPrefix + "die")) {
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
		std::string lSnowflake;
		try {
			lSnowflake = getSnowflake(lcWords[1]);
		} catch(std::runtime_error& e) {
			fprintf(stderr, "onMessage(): sonar_ping: %s\n", e.what());
			return;
		}
		sonarPing(aMessage.serverID, aMessage.author, aMessage.channelID, lSnowflake, lNumPings);
	} else if (aMessage.startsWith(lcrPrefix + "fuckoff")) { // not verified working
		fuckoff(aMessage.serverID, aMessage.author);
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

void MyClientClass::fn_setChannelName(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const std::string& acrName) {
	editChannelName(acrChannelID, acrName);
}

void MyClientClass::fn_setChannelTopic	(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const std::string& acrTopic) {
	editChannelTopic(acrChannelID, acrTopic);
}

void MyClientClass::fn_deleteChannel(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID) {
	deleteChannel(acrChannelID);
}

void MyClientClass::fn_pinMessage(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const SleepyDiscord::Snowflake<SleepyDiscord::Message>& acrMessageID) {
	if(std::find(getPinnedMessages(acrChannelID).vector().begin(), getPinnedMessages(acrChannelID).vector().end(), acrMessageID) == getPinnedMessages(acrChannelID).vector().end()) {
		pinMessage(acrChannelID, acrMessageID);
	} else {
		std::fprintf(stderr, "pinMessage(): message was already pinned.");
	}
}

void MyClientClass::fn_unpinMessage(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const SleepyDiscord::Snowflake<SleepyDiscord::Message>& acrMessageID) {
	if(std::find(getPinnedMessages(acrChannelID).vector().begin(), getPinnedMessages(acrChannelID).vector().end(), acrMessageID) != getPinnedMessages(acrChannelID).vector().end()) {
		unpinMessage(acrChannelID, acrMessageID);
	} else {
		std::fprintf(stderr, "unpinMessage(): message was not pinned.");
	}
}

void MyClientClass::fn_changeNickname(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrNicknamedUserID, const std::string& acrNickname) {
	if(isBot(acrNicknamedUserID)) {
		editNickname(arServerID, acrNickname);
	} else {
		// throws discord permissions error
		//editMember(arServerID, acrNicknamedUserID, acrNickname);
	}
}

void MyClientClass::fn_removeRole(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrRemovedUserID, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& acrRoleID) {
	removeRole(arServerID, acrRemovedUserID, acrRoleID);
}

void MyClientClass::fn_deleteRole(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& acrRoleID) {
	deleteRole(arServerID, acrRoleID);
}

void MyClientClass::fn_pruneUsers(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, int aNumDays) {
	pruneMembers(arServerID, aNumDays);
}

void MyClientClass::fn_deleteInvite(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const std::string& acrInvite) {
	std::string lInviteCode;
	if(acrInvite.find("https://discord.gg/") != std::string::npos) {
		lInviteCode = acrInvite.substr(strlen("https://discord.gg/"));
	} else if(acrInvite.find("discord.gg/") != std::string::npos) {
		lInviteCode = acrInvite.substr(strlen("discord.gg/"));
	} else {
		lInviteCode = acrInvite;
	}
	deleteInvite(lInviteCode);
}

void MyClientClass::fn_deleteChannelInvites(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID) {
	auto lVec = getChannelInvites(acrChannelID).vector();
	for(auto lInvite : lVec) {
		deleteInvite(lInvite.code);
	}
}

void MyClientClass::fn_deleteAllInvites(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser) {
	auto lVec = getServerInvites(arServerID).vector();
	for(auto lInvite : lVec) {
		deleteInvite(lInvite.code);
	}
}

void MyClientClass::fn_leaveServer(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser) {
	leaveServer(arServerID);
}

void MyClientClass::fn_setStatus(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const std::string& acrActivityName, const SleepyDiscord::Status acStatus, bool abAFK, int aIdleTime) {
	updateStatus(acrActivityName, aIdleTime, acStatus, abAFK);
}

void MyClientClass::fn_setBotActivity(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const std::string& acrActivityName) {
	botStatus.activity = acrActivityName;
	updateStatus(botStatus.activity, botStatus.idleSince, botStatus.status, botStatus.AFK);
}

void MyClientClass::fn_setBotIdle(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, int aIdleTime) {
	botStatus.idleSince = aIdleTime;
	updateStatus(botStatus.activity, botStatus.idleSince, botStatus.status, botStatus.AFK);
}

void MyClientClass::fn_setBotStatus(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Status acStatus) {
	botStatus.status = acStatus;
	updateStatus(botStatus.activity, botStatus.idleSince, botStatus.status, botStatus.AFK);
}
	
void MyClientClass::fn_setBotAFK(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, bool abAFK) {
	botStatus.AFK = abAFK;
	updateStatus(botStatus.activity, botStatus.idleSince, botStatus.status, botStatus.AFK);
}

void MyClientClass::fn_die(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID) {
	const std::string lcMessage = "Okay.";
	echo(arServerID, acrUser, acrChannelID, lcMessage);
	quit();
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

SleepyDiscord::Status MyClientClass::toStatus(const std::string& acrString) {
	std::map<std::string, SleepyDiscord::Status> lStatuses = {
		{ "online", 		SleepyDiscord::Status::online },
		{ "dnd", 			SleepyDiscord::Status::doNotDisturb },
		{ "do_not_disturb", SleepyDiscord::Status::doNotDisturb },
		{ "afk",			SleepyDiscord::Status::idle },
		{ "idle",			SleepyDiscord::Status::idle },
		{ "invisible",		SleepyDiscord::Status::invisible },
		{ "offline",		SleepyDiscord::Status::offline }
	};

	return lStatuses.at(acrString);
}

bool MyClientClass::isBot(const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID) {
	return acrUserID == botID;
}

bool MyClientClass::isMuted(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUser) const {
	if(std::count(m_serverBotSettings.at(acrServerID).mutedUserIDs.begin(), m_serverBotSettings.at(acrServerID).mutedUserIDs.end(), acrUser) > 0) {
		return true;
	} else {
		return false;
	}
}