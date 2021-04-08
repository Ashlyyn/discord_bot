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
        m_name = std::string();
        m_client = nullptr;
        m_fpRun = nullptr;
        m_commandType = COMMAND_TYPE::NON_ADMIN;
        m_numParams = -1;
    }

    template<typename ...Args> Command(const std::string& acrName, MyClientClass* apClient, COMMAND_TYPE aCommandType, void(MyClientClass::*fpFnptr)(SleepyDiscord::Snowflake<SleepyDiscord::Server>&, const SleepyDiscord::User&, Args...)) {
        m_name = acrName;
        m_client = apClient;
        m_fpRun = (void(MyClientClass::*)()) fpFnptr;
        m_commandType = aCommandType;
        m_numParams = sizeof...(Args);

    }

    template<typename ...Args> void operator()(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, Args... args) {
        if(checkPermissions(arServerID, acrUser) == true) {
            (m_client->*(void(MyClientClass::*)(SleepyDiscord::Snowflake<SleepyDiscord::Server>&, const SleepyDiscord::User&, Args...))m_fpRun)(arServerID, acrUser, args...);
        }
    }

private:
    std::string m_name;
    MyClientClass* m_client;
    void (MyClientClass::*m_fpRun)();
    COMMAND_TYPE m_commandType;
    int m_numParams;

    std::map<SleepyDiscord::Snowflake<SleepyDiscord::Server>, COMMAND_TYPE, ServerBotSettingsComparator> m_permissions;

    static bool isOwner(const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID);
    static bool hasRole(SleepyDiscord::Server& arServer, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& acrRoleID);
    bool checkPermissions(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::User& acrUser) const;
};


#endif