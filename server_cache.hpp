#include <vector>
#include <map>
#include <unordered_set>

#include "sleepy_discord/sleepy_discord.h"

#include "server_bot_settings.hpp"

struct UserHash {
    std::size_t operator()(const SleepyDiscord::User& acrUser) const {
        return std::hash<std::string>()(acrUser.ID);
    }
};

class ServerCache {
public:
    // acrBannedUserIDs passed to function since getBans() is a member function of client
    void addServer    (const SleepyDiscord::Server& acrServer, const std::vector<SleepyDiscord::User>& acrBannedUsers); 
    void removeServer (const SleepyDiscord::UnavailableServer& acrRemovedServer);

    SleepyDiscord::Server&                  getServer           (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID);
    //SleepyDiscord::Invite                   getInvite           (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const std::string& acrInviteCode);
    SleepyDiscord::Channel                  getChannel          (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID);
    //SleepyDiscord::Message                  getMessage          (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const SleepyDiscord::Snowflake<SleepyDiscord::Message>& acrMessageID);
    SleepyDiscord::User                     getRole             (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& acrRoleID);
    SleepyDiscord::ServerMember             getMember           (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID);
    SleepyDiscord::User                     getUser             (const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID);
    ServerBotSettings&                      getServerBotSettings(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID);
    
    SleepyDiscord::Snowflake<SleepyDiscord::Channel>    getUserDMchannelID(const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID);

    std::vector<SleepyDiscord::Server>                  getServers          ();
    std::unordered_set<SleepyDiscord::User, UserHash>&  getUsers            ();
    //std::vector<SleepyDiscord::Connection>  getUserConnetions   ();
    std::list<SleepyDiscord::Channel>&                  getServerChannels   (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID);
    std::list<SleepyDiscord::ServerMember>&             getServerMembers    (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID);
    std::list<SleepyDiscord::Role>&                     getRoles            (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID);
    std::vector<SleepyDiscord::User>                    getKickedUsers      (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID);
    std::vector<SleepyDiscord::User>                    getBannedUsers      (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID);
    //std::vector<SleepyDiscord::Webhool>     getServerWebhooks   (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID);
    //std::vector<SleepyDiscord::Webhool>     getChannelWebhooks  (const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID);
    //std::vector<SleepyDiscord::Invite>      getServerInvites    (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID);
    //std::vector<SleepyDiscord::Invite>      getChannelInvites   (const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID);
    //std::vector<SleepyDiscord::Message>     getPinnedMessages   (const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID);
    //std::vector<SleepyDiscord::User>        getReactions        (const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const SleepyDiscord::Snowflake<SleepyDiscord::Message> acrMessageID, const std::string& acrEmoji);
    void                                                addKickedUser       (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, bool b);
    
    std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Server>>                        getServerIDs           ();
    std::unordered_map<std::string, ServerBotSettings>&                                 getAllServerBotSettings();
    std::unordered_map<std::string, SleepyDiscord::Snowflake<SleepyDiscord::Channel>>&  getUserDMchannelIDs    ();
    //std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Message>> getPinnedMessageIDs   (const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID);
    std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Channel>>                       getServerChannelIDs    (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID);
    std::vector<SleepyDiscord::Snowflake<SleepyDiscord::ServerMember>>                  getServerMemberIDs     (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID);
    std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Role>>                          getRoleIDs             (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID);
    std::vector<std::pair<SleepyDiscord::Snowflake<SleepyDiscord::User>, bool>>&        getKickedUserIDs       (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID);
    std::vector<std::pair<SleepyDiscord::Snowflake<SleepyDiscord::User>, bool>>&        getBannedUserIDs       (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID);
    void                                                                                addServerBotSettings   (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID);

private:
    // std::string used in place of SleepyDiscord::Snowflake to prevent needing to supply a hash
    std::unordered_set<SleepyDiscord::User, UserHash> m_users;
    std::unordered_map<std::string, SleepyDiscord::Server> m_servers;
    std::unordered_map<std::string, std::vector<std::pair<SleepyDiscord::Snowflake<SleepyDiscord::User>, bool>>> m_bannedUserIDs;
    std::unordered_map<std::string, SleepyDiscord::Snowflake<SleepyDiscord::Channel>> m_userDMchannelIDs; // map server IDs to DM channel IDs
    std::unordered_map<std::string, ServerBotSettings> m_serverBotSettings; // map server IDs to their respective settings struct
    std::unordered_map<std::string, std::vector<std::pair<SleepyDiscord::Snowflake<SleepyDiscord::User>, bool>>> m_kickedUserIDs; // map server IDs to users kicked from the server
                                                                                                                                  // same thing with the bool

};