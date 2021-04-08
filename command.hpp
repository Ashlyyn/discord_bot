#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <map>
#include <vector>
#include <functional>

#include "sleepy_discord/sleepy_discord.h"

#include "server_bot_settings.hpp"

class MyClientClass;

class Command {
public:
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

    Command() {
        m_client = nullptr;
        m_run = nullptr;
        m_commandType = COMMAND_TYPE::NON_ADMIN;
    }

    template<typename ...Args> Command(MyClientClass* _client, COMMAND_TYPE commandType, void(MyClientClass::*fnptr)(SleepyDiscord::Snowflake<SleepyDiscord::Server>&, Args...)) {
        m_client = _client;
        m_run = (void(MyClientClass::*)()) fnptr;
        m_commandType = commandType;

    }

    template<typename ...Args> void operator()(SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::ServerMember& member, Args... args) {
        if(checkPermissions(server, member) == true) {
            (m_client->*(void(MyClientClass::*)(SleepyDiscord::Snowflake<SleepyDiscord::Server>&, Args...))m_run)(server, args...);
        }
    }

private:
    MyClientClass* m_client;
    void (MyClientClass::*m_run)();
    COMMAND_TYPE m_commandType;

    std::map<SleepyDiscord::Snowflake<SleepyDiscord::Server>, COMMAND_TYPE, ServerBotSettingsComparator> permissions;

    static bool isOwner(const SleepyDiscord::Snowflake<SleepyDiscord::User>& user);
    static bool hasRole(const SleepyDiscord::ServerMember& member, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& role);
    bool checkPermissions(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::ServerMember& member) const;
};


#endif