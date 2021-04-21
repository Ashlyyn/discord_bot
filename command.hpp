#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <map>
#include <vector>
#include <functional>

#include "sleepy_discord/sleepy_discord.h"

#include "server_bot_settings.hpp"

#define ASIO_NO_EXCEPTIONS

class MyClientClass; // forward declaration for declaration of Command::m_client

// creates command for bot

// operator() overloaded to allow for automatic permission checking
// instead of doing it in every function
class Command {
public:
    enum COMMAND_PERMISSION {
		OWNER_ONLY, // only owner can execute
		BOT_ADMIN,  // only users with admin role can execute
		CMD_ALL     // everyone can execute
	};

	enum COMMAND_TYPE {
		ADMIN,
		NON_ADMIN,
		ROLE_ALL
	};

    std::string name; // name of command as used by bot

    // set members to defaults
    Command() {
        name = std::string();
        m_client = nullptr;
        m_fpRun = nullptr;
        m_commandType = COMMAND_TYPE::NON_ADMIN;
        m_noOwner = false;
        m_numParams = -1;
    }

    
    template<typename ...Args> Command(const std::string& acrName, MyClientClass* apClient, COMMAND_TYPE aCommandType, void(MyClientClass::*fpFnptr)(SleepyDiscord::Snowflake<SleepyDiscord::Server>&, const SleepyDiscord::User&, Args...), bool b = false) {
        name = acrName;
        m_client = apClient;
        m_fpRun = (void(MyClientClass::*)(void)) fpFnptr; // cast to void(*)(void) to allow assignment to m_fpRun
        m_commandType = aCommandType;
        m_noOwner = b;
        m_numParams = sizeof...(Args);
    }

    template<typename ...Args> void operator()(SleepyDiscord::Snowflake<SleepyDiscord::Server>& arServerID, const SleepyDiscord::User& acrUser, Args... args) {
        if(arServerID == SleepyDiscord::Snowflake<SleepyDiscord::Server>()) {
            throw std::runtime_error("Command::operator(): Null server passed to function.");
        }
        else if (acrUser == SleepyDiscord::User()) {
            throw std::runtime_error("Command::operator(): Null user passed to function.");
        }
        
        else {
            // check if user is owner and command has m_noOwner set
            if(((m_noOwner == true) && (isOwner(acrUser.ID))) || (m_noOwner == false)) {
                // check if user is allowed to execute command; logAction() is excepted, since no user will ever call it
                if((checkPermissions(arServerID, acrUser) == true) || (name == "log_action")) {
                    // server and user must be passed to all functions, even those that do not use them directly
                    // to allow for permission checking
                    (m_client->*(void(MyClientClass::*)(SleepyDiscord::Snowflake<SleepyDiscord::Server>&, const SleepyDiscord::User&, Args...))m_fpRun)(arServerID, acrUser, args...);
                }
            }
        }
    }

private:
    MyClientClass* m_client;
    void (MyClientClass::*m_fpRun)();
    COMMAND_TYPE m_commandType;
    int m_numParams;
    bool m_noOwner; // set to true if command shouldn't be able to affect owner - i.e., ban, kick, etc.

    // permissions for each server
    std::unordered_map<std::string, COMMAND_TYPE> m_permissions;

    static bool isOwner(const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID);
    static bool hasRole(SleepyDiscord::Server& arServer, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& acrRoleID);
    bool checkPermissions(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::User& acrUser) const;
};


#endif