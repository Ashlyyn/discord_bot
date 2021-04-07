#ifndef _BOT_CLIENT_H_
#define _BOT_CLIENT_H_

#include <array>
#include <map>
#include <vector>

#include "sleepy_discord/sleepy_discord.h"

class MyClientClass : public SleepyDiscord::DiscordClient {
public:
	using SleepyDiscord::DiscordClient::DiscordClient;

	void onMessage(SleepyDiscord::Message message) override;
    void onServer(SleepyDiscord::Server server) override;

protected:
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

    struct ServerBotSettings {
        bool silent = false;
	    bool noLogs = false;
	    std::string prefix = "F!";
	    SleepyDiscord::Snowflake<SleepyDiscord::Channel> logsChannel;
	    SleepyDiscord::Snowflake<SleepyDiscord::Role> botAdminRole;
	    std::vector<SleepyDiscord::Snowflake<SleepyDiscord::ServerMember> > mutedUsers;
        std::array<int, 2> permissions = {
		    COMMAND_PERMISSION::CMD_ALL, COMMAND_PERMISSION::CMD_ALL
	    };

		ServerBotSettings() {
			logsChannel = SleepyDiscord::Snowflake<SleepyDiscord::Channel>();
			SleepyDiscord::Snowflake<SleepyDiscord::Role>();
			std::vector<SleepyDiscord::Snowflake<SleepyDiscord::User> >();
		}

		bool operator==(const ServerBotSettings& rhs) const {
			if((silent == rhs.silent) && (noLogs == rhs.noLogs) && (prefix == rhs.prefix) 
				&& (logsChannel == rhs.logsChannel) && (botAdminRole == rhs.botAdminRole)
				&& (mutedUsers == rhs.mutedUsers) && (permissions == rhs.permissions)
			) {
				return true;
			}
			else {
				return false;
			}
		}

		bool operator!=(const ServerBotSettings& rhs) const {
			if(!operator==(rhs)) {
				return true;
			}
			else {
				return false;
			}
		}
    };

	struct ServerBotSettingsComparator {
		bool operator()(const ServerBotSettings& lhs, const ServerBotSettings& rhs) const {
			if(lhs == ServerBotSettings() && rhs != ServerBotSettings()) {
				return 0;
			}
			else {
				return 1;
			}
		}

		bool operator()(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& lhs, const SleepyDiscord::Snowflake<SleepyDiscord::Server>& rhs) const {
			if(lhs == SleepyDiscord::Snowflake<SleepyDiscord::Server>() && rhs != SleepyDiscord::Snowflake<SleepyDiscord::Server>()) {
				return 0;
			}
			else {
				return 1;
			}
		}
	};

    std::map<SleepyDiscord::Snowflake<SleepyDiscord::Server>, ServerBotSettings, ServerBotSettingsComparator> m_serverBotSettings;

	void changePrefix(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const std::string& newPrefix);
	void hello(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channel, const SleepyDiscord::User& user);
	void echo(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channel, const std::string& message);
	void muteVoice(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::User>& user);
	void unmuteVoice(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::User>& user);
	void muteText(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::ServerMember>& member);
	void unmuteText(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::ServerMember>& member);
	void setBotAdminRole(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& role);
	void setLogsChannel(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channel);
	void logsDisable(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, bool b = true);
	void setSilent(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, bool b = true);
	void logAction(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const std::string& str);
	void setPermissions(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, COMMAND_PERMISSION commandPerm, COMMAND_TYPE commandType);
	void die(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::Channel> channel);


private:
	static std::vector<std::string> split(const std::string& string);
	static std::string getSnowflake(const std::string& str);
	bool isMuted(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::ServerMember>& member);
	static bool hasRole(const SleepyDiscord::ServerMember& member, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& role);
	static bool isOwner(const SleepyDiscord::Snowflake<SleepyDiscord::User>& user);
	bool checkPermissions(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::ServerMember& member, COMMAND_TYPE commandType);
};

#endif