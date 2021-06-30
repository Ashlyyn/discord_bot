#include "server_cache.hpp"
#include "server_bot_settings.hpp"

void ServerCache::addServer(const SleepyDiscord::Server& acrServer, const std::vector<SleepyDiscord::User>& acrBannedUsers) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        m_servers.at(acrServer.ID);
    }
    catch (const std::out_of_range& e) {
        m_servers[acrServer.ID] = acrServer;
        std::vector<std::pair<SleepyDiscord::Snowflake<SleepyDiscord::User>, bool>> lBannedUserIDs;
        for (const auto& lBannedUser : acrBannedUsers) {
            lBannedUserIDs.push_back(std::make_pair(lBannedUser.ID, false));
        }
        m_bannedUserIDs[acrServer.ID] = lBannedUserIDs;
        return;
    }
    throw std::runtime_error("addServer(): server already present");
}

void ServerCache::editServer(const SleepyDiscord::Server& acrServer) {
    std::mutex mutex;
    std::lock_guard lock(mutex);
    
    try {
        m_servers.at(acrServer.ID) = acrServer;
    }
    catch (const std::out_of_range& e) {
        throw std::runtime_error("editServer(): server not found");
    }
}
    
void ServerCache::removeServer(const SleepyDiscord::UnavailableServer& acrRemovedServer) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        m_servers.at(acrRemovedServer.ID);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("removeServer(): server not found");
    }

    m_servers.erase(acrRemovedServer.ID);
    m_bannedUserIDs.erase(acrRemovedServer.ID);
}

void ServerCache::addMember(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::ServerMember& acrMember) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        m_servers.at(acrServerID);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("addMember(): server not found");
    }

    if (std::find(m_servers.at(acrServerID).members.begin(), m_servers.at(acrServerID).members.end(), acrMember) == m_servers.at(acrServerID).members.end()) {
        m_servers.at(acrServerID).members.push_back(acrMember);
    }
    else {
        throw std::runtime_error("addMember(): member already present");
    }
}

void ServerCache::editMember(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::User& acrUser, const std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Role>>& acrRoles, const std::string& acrNickname) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        m_servers.at(acrServerID);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("editMember(): server not found");
    }

    if (m_servers.at(acrServerID).findMember(acrUser.ID) == m_servers.at(acrServerID).members.end()) {
        throw std::out_of_range("editMember(): member not found");
    }

    if (acrNickname.find_first_not_of("\t\n ") == std::string::npos) {
        throw std::out_of_range("editMember(): nickname string contains only whitespace");
    }

    // TODO - check if server has all roles passed to function

    SleepyDiscord::ServerMember& lMember = *m_servers.at(acrServerID).findMember(acrUser.ID);
    lMember.user = acrUser;
    lMember.roles = acrRoles;
    lMember.nick = acrNickname;
}

void ServerCache::removeMember(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::User& acrUser) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        m_servers.at(acrServerID);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("removeMember(): server not found");
    }

    for (auto& lMember : m_servers.at(acrServerID).members) {
        if (lMember.user.ID == acrUser.ID) {
            m_servers.at(acrServerID).members.erase(std::find(m_servers.at(acrServerID).members.begin(), m_servers.at(acrServerID).members.end(), lMember));
            return;
        }
    }
    throw std::out_of_range("removeMember(): member not found");
}

void ServerCache::addRole(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Role& acrRole) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        m_servers.at(acrServerID).roles.push_back(acrRole);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("editMember(): server not found");
    }
}

void ServerCache::editRole(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Role& acrRole) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        m_servers.at(acrServerID);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("editRole(): server not found");
    }

    for (auto& lRole : m_servers.at(acrServerID).roles) {
        if (lRole.ID == acrRole.ID) {
            lRole = acrRole;
            return;
        }
    }
    throw std::out_of_range("editRole(): role not found");
}

// TODO - fix compile error and add exception handling
void ServerCache::removeRole(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& acrRoleID) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    for (auto& lRole : m_servers.at(acrServerID).roles) {
        if (lRole.ID == acrRoleID) {
            //m_servers.at(acrServerID).roles.erase(std::find(m_servers.at(acrServerID).roles.begin(), m_servers.at(acrServerID).roles.end(), lRole));
            break;
        }
    }
}

/*
void ServerCache::editEmojis(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const std::vector<SleepyDiscord::Emoji>& acrEmojis) {
    // TODO
}
*/

void ServerCache::addChannel(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Channel& acrChannel) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        m_servers.at(acrServerID);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("addChannel(): server not found");
    }

    for (auto& lChannel : m_servers.at(acrServerID).channels) {     // if channel already exists
        if (lChannel.ID == acrChannel.ID) {
            throw std::runtime_error("addChannel(): channel already exists");
        }
    }
    m_servers.at(acrServerID).channels.push_back(acrChannel);
}

void ServerCache::editChannel(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Channel& acrChannel) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        m_servers.at(acrServerID);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("editRole(): server not found");
    }

    for (auto& lChannel : m_servers.at(acrServerID).channels) {
        if (lChannel.ID == acrChannel.ID) {
            lChannel = acrChannel;
            return;
        }
    }
    throw std::out_of_range("editChannel(): channel not found");
}

void ServerCache::deleteChannel(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        m_servers.at(acrServerID);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("deleteChannel(): server not found");
    }

    for (auto& lChannel : m_servers.at(acrServerID).channels) {
        if (lChannel.ID == acrChannelID) {
            m_servers.at(acrServerID).channels.remove(lChannel);
            break;
        }
    }
    throw std::out_of_range("deleteChannel(): channel not found");
}

void ServerCache::addUser(const SleepyDiscord::User& acrUser) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        m_users.at(acrUser.ID);
    }
    catch (const std::out_of_range& e) {
        m_users[acrUser.ID] = acrUser;
        return;
    }
    throw std::runtime_error("addUser(): user already present");
}

void ServerCache::editUser(const SleepyDiscord::User& acrUser) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    bool b = false;

    for (auto& lUser : m_users) {
        if (lUser.second.ID == acrUser.ID) {
            m_users.at(acrUser.ID) = acrUser;
            b = true;
            break;
        }
    }

    if (b == false) {
        throw std::out_of_range("editUser(): user not found");
    }

    for (auto& lServer : m_servers) {
        for (auto& lMember : lServer.second.members) {
            if (lMember.user.ID == acrUser.ID) {
                lMember.user = acrUser;
            }
            break;
        }
    }
}

void ServerCache::addKickedUserID(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, bool b) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        m_servers.at(acrServerID);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("addKickedUserID(): server not found");
    }

    if ((std::find(m_kickedUserIDs[acrServerID].begin(), m_kickedUserIDs[acrServerID].end(), std::make_pair(acrUserID, false)) != m_kickedUserIDs[acrServerID].end()) ||
        (std::find(m_kickedUserIDs[acrServerID].begin(), m_kickedUserIDs[acrServerID].end(), std::make_pair(acrUserID, true))  != m_kickedUserIDs[acrServerID].end()) 
    ) {
        throw std::runtime_error("addKickedUserID(): user ID already present");
    }

    m_kickedUserIDs[acrServerID].push_back(std::make_pair(acrUserID, b));
}

void ServerCache::removeKickedUserID(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        m_servers.at(acrServerID);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("removeKickedUserID(): server not found");
    }

    if (std::find(m_kickedUserIDs[acrServerID].begin(), m_kickedUserIDs[acrServerID].end(), std::make_pair(acrUserID, false)) != m_kickedUserIDs[acrServerID].end()) {
        m_kickedUserIDs[acrServerID].erase(std::find(m_kickedUserIDs[acrServerID].begin(), m_kickedUserIDs[acrServerID].end(), std::make_pair(acrUserID, false)));
    }
    else if (std::find(m_kickedUserIDs[acrServerID].begin(), m_kickedUserIDs[acrServerID].end(), std::make_pair(acrUserID, true)) != m_kickedUserIDs[acrServerID].end()) {
        m_kickedUserIDs[acrServerID].erase(std::find(m_kickedUserIDs[acrServerID].begin(), m_kickedUserIDs[acrServerID].end(), std::make_pair(acrUserID, true)));
    }
    else {
        throw std::out_of_range("removeKickedUserID(): user ID not found");
    }
}

void ServerCache::addBannedUserID(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, bool b) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        m_servers.at(acrServerID);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("addBannedUserID(): server not found");
    }

    if ((std::find(m_bannedUserIDs[acrServerID].begin(), m_bannedUserIDs[acrServerID].end(), std::make_pair(acrUserID, false)) != m_bannedUserIDs[acrServerID].end()) ||
        (std::find(m_bannedUserIDs[acrServerID].begin(), m_bannedUserIDs[acrServerID].end(), std::make_pair(acrUserID, true)) != m_bannedUserIDs[acrServerID].end())
    ) {
        throw std::runtime_error("addBannedUserID(): user ID already present");
    }

    m_bannedUserIDs[acrServerID].push_back(std::make_pair(acrUserID, b));
}

void ServerCache::removeBannedUserID(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        m_servers.at(acrServerID);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("removeBannedUserID(): server not found");
    }

    if (std::find(m_bannedUserIDs[acrServerID].begin(), m_bannedUserIDs[acrServerID].end(), std::make_pair(acrUserID, false)) != m_bannedUserIDs[acrServerID].end()) {
        m_bannedUserIDs[acrServerID].erase(std::find(m_bannedUserIDs[acrServerID].begin(), m_bannedUserIDs[acrServerID].end(), std::make_pair(acrUserID, false)));
    }
    else if (std::find(m_bannedUserIDs[acrServerID].begin(), m_bannedUserIDs[acrServerID].end(), std::make_pair(acrUserID, true)) != m_bannedUserIDs[acrServerID].end()) {
        m_bannedUserIDs[acrServerID].erase(std::find(m_bannedUserIDs[acrServerID].begin(), m_bannedUserIDs[acrServerID].end(), std::make_pair(acrUserID, true)));
    }
    else {
        throw std::out_of_range("removeBannedUserID(): user ID not found");
    }
}

void ServerCache::addUserDMchannelID(const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        m_userDMchannelIDs.at(acrUserID);
    }
    catch (const std::out_of_range& e) {
        m_userDMchannelIDs[acrUserID] = acrChannelID;
        return;
    }
    throw std::runtime_error("addUserDMchannelID(): channel ID already present");
}

void ServerCache::addServerBotSettings(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        m_servers.at(acrServerID);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("addServerBotSettings(): server not found");
    }

    try {
        m_serverBotSettings.at(acrServerID);
    }
    catch (const std::out_of_range& e) {
        m_serverBotSettings[acrServerID] = ServerBotSettings();
        return;
    }
    throw std::runtime_error("addServerBotSettings(): entry already present");
}

const SleepyDiscord::Server& ServerCache::getServer(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID) {
    std::mutex mutex;
    std::lock_guard lock(mutex);
    
    try {
        return m_servers.at(acrServerID);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("getServer(): server not found");
    }
}

const SleepyDiscord::Channel& ServerCache::getChannel(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        m_servers.at(acrServerID);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("getChannel(): server not found");
    }

    return *m_servers.at(acrServerID).findChannel(acrChannelID);
}

const SleepyDiscord::Role& ServerCache::getRole(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& acrRoleID) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        m_servers.at(acrServerID);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("getRole(): server not found");
    }

    return *m_servers.at(acrServerID).findRole(acrRoleID);
}


const SleepyDiscord::User& ServerCache::getUser(const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        return m_users.at(acrUserID);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("getUser(): user not found");
    }

    
}

const SleepyDiscord::ServerMember& ServerCache::getMember(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        m_servers.at(acrServerID);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("getMember(): server not found");
    }

    return *m_servers.at(acrServerID).findMember(acrUserID);
}

ServerBotSettings& ServerCache::getServerBotSettings(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        m_servers.at(acrServerID);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("getServerBotSettings(): server not found");
    }

    try {
        return m_serverBotSettings.at(acrServerID);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("getServerBotSettings(): entry not found");
    }
}

const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& ServerCache::getUserDMchannelID(const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        return m_userDMchannelIDs.at(acrUserID);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("getUserDMchannelID(): entry not found");
    }
    
}

std::vector<SleepyDiscord::Server> ServerCache::getServers() {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    std::vector<SleepyDiscord::Server> lServers;
    for(const auto& lVal : m_servers) {
        lServers.push_back(lVal.second);
    }
    return lServers;
}

const std::unordered_map<SleepyDiscord::Snowflake<SleepyDiscord::User>, SleepyDiscord::User, UserIDHash>& ServerCache::getUsers() {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    return m_users;
}

const std::list<SleepyDiscord::Channel>& ServerCache::getServerChannels(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        m_servers.at(acrServerID);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("getServerChannels(): server not found");
    }

    return m_servers.at(acrServerID).channels;
}

const std::list<SleepyDiscord::ServerMember>& ServerCache::getServerMembers(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        m_servers.at(acrServerID);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("getServerMembers(): server not found");
    }

    return m_servers.at(acrServerID).members;
}

const std::list<SleepyDiscord::Role>& ServerCache::getRoles(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        m_servers.at(acrServerID);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("getRoles(): server not found");
    }

    return m_servers.at(acrServerID).roles;
}

std::vector<SleepyDiscord::User> ServerCache::getKickedUsers(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        m_servers.at(acrServerID);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("getKickedUsers(): server not found");
    }

    std::vector<SleepyDiscord::User> lVec;
    for (const auto& lUserID : m_kickedUserIDs.at(acrServerID)) {
        lVec.push_back(getUser(lUserID.first));
    }
    return lVec;
}

std::vector<SleepyDiscord::User> ServerCache::getBannedUsers(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        m_servers.at(acrServerID);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("getBannedUsers(): server not found");
    }

    std::vector<SleepyDiscord::User> lVec;
    for (const auto& lUserID : m_bannedUserIDs.at(acrServerID)) {
        lVec.push_back(getUser(lUserID.first));
    }
    return lVec;
}

std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Server>> ServerCache::getServerIDs() {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Server>> lServerIDs;
    for(const auto lVal : m_servers) {
        lServerIDs.push_back(lVal.second.ID);
    }
    return lServerIDs;
}

std::unordered_map<SleepyDiscord::Snowflake<SleepyDiscord::Server>, ServerBotSettings, ServerIDHash>& ServerCache::getAllServerBotSettings() {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    return m_serverBotSettings;
}

const std::unordered_map<SleepyDiscord::Snowflake<SleepyDiscord::User>, SleepyDiscord::Snowflake<SleepyDiscord::Channel>, UserIDHash>& ServerCache::getUserDMchannelIDs() {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    return m_userDMchannelIDs;
}

std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Channel>> ServerCache::getServerChannelIDs(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        m_servers.at(acrServerID);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("getServerChannelIDs(): server not found");
    }

    std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Channel>> lChannelIDs;
    for (const auto& lChannel : m_servers.at(acrServerID).channels) {
        lChannelIDs.push_back(lChannel.ID);
    }
    return lChannelIDs;
}

std::vector<SleepyDiscord::Snowflake<SleepyDiscord::ServerMember>> ServerCache::getServerMemberIDs(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        m_servers.at(acrServerID);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("getServerMemberIDs(): server not found");
    }

    std::vector<SleepyDiscord::Snowflake<SleepyDiscord::ServerMember>> lServerMemberIDs;
    for (const auto& lMember : getServer(acrServerID).members) {
        lServerMemberIDs.push_back(SleepyDiscord::Snowflake<SleepyDiscord::ServerMember>(lMember.ID));
    }
    return lServerMemberIDs;
}

std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Role>> ServerCache::getRoleIDs(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        m_servers.at(acrServerID);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("getRoleIDs(): server not found");
    }

    std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Role>> lRoleIDs;
    for(const auto& lRole : m_servers.at(acrServerID).roles) {
        lRoleIDs.push_back(lRole.ID);
    }
    return lRoleIDs;
}

const std::vector<std::pair<SleepyDiscord::Snowflake<SleepyDiscord::User>, bool>>& ServerCache::getKickedUserIDs(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        m_servers.at(acrServerID);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("getKickedUserIDs(): server not found");
    }

    return m_kickedUserIDs.at(acrServerID);
}

const std::vector<std::pair<SleepyDiscord::Snowflake<SleepyDiscord::User>, bool>>& ServerCache::getBannedUserIDs(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID) {
    std::mutex mutex;
    std::lock_guard lock(mutex);

    try {
        m_servers.at(acrServerID);
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("getBannedUserIDs(): server not found");
    }

    return m_bannedUserIDs.at(acrServerID);
}