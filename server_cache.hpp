#include <vector>
#include <map>
#include <unordered_set>

#include "sleepy_discord/sleepy_discord.h"

#include "server_bot_settings.hpp"

struct UserIDHash {
    std::size_t operator()(const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID) const {
        return std::hash<std::string>()(acrUserID);
    }
};

struct UserHash {
    std::size_t operator()(const SleepyDiscord::User& acrUser) const {
        return std::hash<std::string>()(acrUser.ID);
    }
};

struct ServerIDHash {
    std::size_t operator()(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID) const {
        return std::hash<std::string>()(acrServerID);
    }
};

struct ServerHash {
    std::size_t operator()(const SleepyDiscord::Server& acrServer) const {
        return std::hash<std::string>()(acrServer.ID);
    }
};

class ServerCache {
public:
    // acrBannedUserIDs passed to function since getBans() is a member function of client
    void addServer              (const SleepyDiscord::Server& acrServer, const std::vector<SleepyDiscord::User>& acrBannedUsers); 
    void editServer             (const SleepyDiscord::Server& acrServer);
    void removeServer           (const SleepyDiscord::UnavailableServer& acrRemovedServer);
    void addMember              (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::ServerMember& acrMember);
    void editMember             (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::User& acrUser, const std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Role>>& acrRoles, const std::string& acrNickname);
    void removeMember           (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::User& acrUser);
    void addRole                (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Role& acrRole);
    void editRole               (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Role& acrRole);
    void removeRole             (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& acrRoleID);
    //void editEmojis   (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const std::vector<SleepyDiscord::Emoji>& acrEmojis);   // TODO
    void addChannel             (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Channel& acrChannel);
    void editChannel            (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Channel& acrChannel);
    void deleteChannel          (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID);
    void addUser                (const SleepyDiscord::User& acrUser);
    void editUser               (const SleepyDiscord::User& acrUser);
    void addKickedUserID        (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, bool b);
    void removeKickedUserID     (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID);
    void addBannedUserID        (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, bool b);
    void removeBannedUserID     (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID);
    void addUserDMchannelID     (const SleepyDiscord::Snowflake<SleepyDiscord::User>&   acrUserID,   const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID);
    void addServerBotSettings   (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID);



    const SleepyDiscord::Server&        getServer           (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID);
    //SleepyDiscord::Invite             getInvite           (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const std::string& acrInviteCode);
    const SleepyDiscord::Channel&       getChannel          (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID);
    //SleepyDiscord::Message            getMessage          (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const SleepyDiscord::Snowflake<SleepyDiscord::Message>& acrMessageID);
    const SleepyDiscord::Role&          getRole             (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& acrRoleID);
    const SleepyDiscord::User&          getUser             (const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID);
    const SleepyDiscord::ServerMember&  getMember           (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID);
    ServerBotSettings&                  getServerBotSettings(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID);
    
    const SleepyDiscord::Snowflake<SleepyDiscord::Channel>&    getUserDMchannelID(const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID);

    std::vector<SleepyDiscord::Server>                          getServers          ();
    const std::unordered_map<SleepyDiscord::Snowflake<SleepyDiscord::User>, SleepyDiscord::User, UserIDHash>& getUsers            ();
    //std::vector<SleepyDiscord::Connection>  getUserConnetions   ();
    const std::list<SleepyDiscord::Channel>&                    getServerChannels   (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID);
    const std::list<SleepyDiscord::ServerMember>&               getServerMembers    (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID);
    const std::list<SleepyDiscord::Role>&                       getRoles            (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID);
    std::vector<SleepyDiscord::User>                            getKickedUsers      (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID);
    std::vector<SleepyDiscord::User>                            getBannedUsers      (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID);
    //std::vector<SleepyDiscord::Webhook>     getServerWebhooks   (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID);
    //std::vector<SleepyDiscord::Webhook>     getChannelWebhooks  (const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID);
    //std::vector<SleepyDiscord::Invite>      getServerInvites    (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID);
    //std::vector<SleepyDiscord::Invite>      getChannelInvites   (const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID);
    //std::vector<SleepyDiscord::Message>     getPinnedMessages   (const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID);
    //std::vector<SleepyDiscord::User>        getReactions        (const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const SleepyDiscord::Snowflake<SleepyDiscord::Message> acrMessageID, const std::string& acrEmoji);
    
    std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Server>>                                getServerIDs           ();
    std::unordered_map<SleepyDiscord::Snowflake<SleepyDiscord::Server>, ServerBotSettings, ServerIDHash>&                                    getAllServerBotSettings();
    const std::unordered_map<SleepyDiscord::Snowflake<SleepyDiscord::User>,   SleepyDiscord::Snowflake<SleepyDiscord::Channel>, UserIDHash>& getUserDMchannelIDs    ();
    //std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Message>> getPinnedMessageIDs   (const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID);
    std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Channel>>                               getServerChannelIDs    (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID);
    std::vector<SleepyDiscord::Snowflake<SleepyDiscord::ServerMember>>                          getServerMemberIDs     (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID);
    std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Role>>                                  getRoleIDs             (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID);
    const std::vector<std::pair<SleepyDiscord::Snowflake<SleepyDiscord::User>, bool>>&          getKickedUserIDs       (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID);
    const std::vector<std::pair<SleepyDiscord::Snowflake<SleepyDiscord::User>, bool>>&          getBannedUserIDs       (const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID);

private:
    // std::string used in place of SleepyDiscord::Snowflake to prevent needing to supply a hash
    std::unordered_map<SleepyDiscord::Snowflake<SleepyDiscord::User>,   SleepyDiscord::User,                                                         UserIDHash>   m_users;
    std::unordered_map<SleepyDiscord::Snowflake<SleepyDiscord::User>,   SleepyDiscord::Snowflake<SleepyDiscord::Channel>,                            UserIDHash>   m_userDMchannelIDs; // map server IDs to DM channel IDs
    std::unordered_map<SleepyDiscord::Snowflake<SleepyDiscord::Server>, SleepyDiscord::Server,                                                       ServerIDHash> m_servers;
    std::unordered_map<SleepyDiscord::Snowflake<SleepyDiscord::Server>, std::vector<std::pair<SleepyDiscord::Snowflake<SleepyDiscord::User>, bool>>, ServerIDHash> m_bannedUserIDs;
    std::unordered_map<SleepyDiscord::Snowflake<SleepyDiscord::Server>, ServerBotSettings,                                                           ServerIDHash> m_serverBotSettings; // map server IDs to their respective settings struct
    std::unordered_map<SleepyDiscord::Snowflake<SleepyDiscord::Server>, std::vector<std::pair<SleepyDiscord::Snowflake<SleepyDiscord::User>, bool>>, ServerIDHash> m_kickedUserIDs; // map server IDs to users kicked from the server

};