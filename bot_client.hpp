#ifndef _BOT_CLIENT_H_
#define _BOT_CLIENT_H_

#include <array>
#include <vector>

#include "sleepy_discord/sleepy_discord.h"

class MyClientClass : public SleepyDiscord::DiscordClient {
public:
	using SleepyDiscord::DiscordClient::DiscordClient;

	void onMessage(SleepyDiscord::Message message) override;
    void onServer(SleepyDiscord::Server server) override;

protected:
    struct ServerBotSettings {
        bool silent = false;
	    bool noLogs = false;
	    std::string prefix = "F!";
	    SleepyDiscord::Snowflake<SleepyDiscord::Channel> logsChannel;
	    SleepyDiscord::Snowflake<SleepyDiscord::Role> botAdminRole;
	    std::vector<SleepyDiscord::Snowflake<SleepyDiscord::User> > mutedUsers;
    };

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

    std::map<SleepyDiscord::Snowflake<SleepyDiscord::Server>, ServerBotSettings> m_serverBotSettings;

	std::array<int, 2> m_permissions = {
		COMMAND_PERMISSION::CMD_ALL, COMMAND_PERMISSION::CMD_ALL
	};

	void changePrefix(const std::string& newPrefix);
	void hello(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channel, const SleepyDiscord::User& user);
	void echo(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channel, const std::string& message);
	void muteVoice(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::User>& user);
	void unmuteVoice(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::User>& user);
	void muteText(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::User> user);
	void unmuteText(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::User> user);
	void setBotAdminRole(const SleepyDiscord::Snowflake<SleepyDiscord::Role>& role);
	void setLogsChannel(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channel);
	void logsDisable(bool b = true);
	void setSilent(bool b = true);
	void logAction(const std::string& str);
	void setPermissions(COMMAND_PERMISSION commandPerm, COMMAND_TYPE commandType);
	void die(const SleepyDiscord::Snowflake<SleepyDiscord::Channel> channel);


private:
	static std::vector<std::string> split(std::string string);
	static std::string getSnowflake(const std::string str);
	bool isMuted(const SleepyDiscord::Snowflake<SleepyDiscord::User>& user);
	static bool hasRole(const SleepyDiscord::ServerMember& member, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& role);
	static bool isOwner(const SleepyDiscord::Snowflake<SleepyDiscord::User>& user);
	bool checkPermissions(const SleepyDiscord::ServerMember& member, COMMAND_TYPE commandType);
};

#endif