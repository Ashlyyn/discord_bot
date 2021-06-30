#include "server_cache.hpp"
#include "server_bot_settings.hpp"

void ServerCache::addServer(const SleepyDiscord::Server& acrServer, const std::vector<SleepyDiscord::User>& acrBannedUsers) {
    m_servers[acrServer.ID] = acrServer;
    std::vector<std::pair<SleepyDiscord::Snowflake<SleepyDiscord::User>, bool>> lBannedUserIDs;
    for(const auto& lBannedUser : acrBannedUsers) {
        lBannedUserIDs.push_back(std::make_pair(lBannedUser.ID, false));
    }
    m_bannedUserIDs[acrServer.ID] = lBannedUserIDs;
}

void ServerCache::editServer(const SleepyDiscord::Server& acrServer) {
    m_servers.at(acrServer.ID) = acrServer;
}
    
void ServerCache::removeServer(const SleepyDiscord::UnavailableServer& acrRemovedServer) {
    m_servers.erase(acrRemovedServer.ID);
    m_bannedUserIDs.erase(acrRemovedServer.ID);
}

void ServerCache::addMember(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::ServerMember& acrMember) {
    if (std::find(m_servers.at(acrServerID).members.begin(), m_servers.at(acrServerID).members.end(), acrMember) == m_servers.at(acrServerID).members.end()) {
        m_servers.at(acrServerID).members.push_back(acrMember);
    }
}

void ServerCache::editMember(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::User& acrUser, const std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Role>>& acrRoles, const std::string& acrNickname) {
    for (auto& lMember : m_servers.at(acrServerID).members) {
        if (lMember.user.ID == acrUser.ID) {
            lMember.user = acrUser;
            lMember.roles = acrRoles;
            lMember.nick = acrNickname;
            break;
        }
    }
}

void ServerCache::removeMember(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::User& acrUser) {
    for (auto& lMember : m_servers.at(acrServerID).members) {
        if (lMember.user.ID == acrUser.ID) {
            m_servers.at(acrServerID).members.erase(std::find(m_servers.at(acrServerID).members.begin(), m_servers.at(acrServerID).members.end(), lMember));
        }
    }
}

void ServerCache::addRole(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Role& acrRole) {
    m_servers.at(acrServerID).roles.push_back(acrRole);
}

void ServerCache::editRole(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Role& acrRole) {
    for (auto& lRole : m_servers.at(acrServerID).roles) {
        if (lRole.ID == acrRole.ID) {
            lRole = acrRole;
            break;
        }
    }
}

void ServerCache::removeRole(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& acrRoleID) {
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
    for (auto& lChannel : m_servers.at(acrServerID).channels) {     // if channel already exists
        if (lChannel.ID == acrChannel.ID) {
            lChannel = acrChannel;
            return;
        }
    }
    m_servers.at(acrServerID).channels.push_back(acrChannel);
}

void ServerCache::editChannel(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Channel& acrChannel) {
    for (auto& lChannel : m_servers.at(acrServerID).channels) {
        if (lChannel.ID == acrChannel.ID) {
            lChannel = acrChannel;
            break;
        }
    }
}

void ServerCache::deleteChannel(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID) {
    for (auto& lChannel : m_servers.at(acrServerID).channels) {
        if (lChannel.ID == acrChannelID) {
            m_servers.at(acrServerID).channels.remove(lChannel);
            break;
        }
    }
}

void ServerCache::addUser(const SleepyDiscord::User& acrUser) {
    m_users[acrUser.ID] = acrUser;
}

void ServerCache::editUser(const SleepyDiscord::User& acrUser) {
    for (auto& lUser : m_users) {
        if (lUser.second.ID == acrUser.ID) {
            m_users.at(acrUser.ID) = acrUser;
            break;
        }
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
    m_kickedUserIDs[acrServerID].push_back(std::make_pair(acrUserID, b));
}

void ServerCache::removeKickedUserID(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID) {
    if (std::find(m_kickedUserIDs[acrServerID].begin(), m_kickedUserIDs[acrServerID].end(), std::make_pair(acrUserID, false)) != m_kickedUserIDs[acrServerID].end()) {
        m_kickedUserIDs[acrServerID].erase(std::find(m_kickedUserIDs[acrServerID].begin(), m_kickedUserIDs[acrServerID].end(), std::make_pair(acrUserID, false)));
    }
    else if (std::find(m_kickedUserIDs[acrServerID].begin(), m_kickedUserIDs[acrServerID].end(), std::make_pair(acrUserID, true)) != m_kickedUserIDs[acrServerID].end()) {
        m_kickedUserIDs[acrServerID].erase(std::find(m_kickedUserIDs[acrServerID].begin(), m_kickedUserIDs[acrServerID].end(), std::make_pair(acrUserID, true)));
    }
}

void ServerCache::addBannedUserID(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, bool b) {
    m_bannedUserIDs[acrServerID].push_back(std::make_pair(acrUserID, b));
}

void ServerCache::removeBannedUserID(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID) {
    if (std::find(m_bannedUserIDs[acrServerID].begin(), m_bannedUserIDs[acrServerID].end(), std::make_pair(acrUserID, false)) != m_bannedUserIDs[acrServerID].end()) {
        m_bannedUserIDs[acrServerID].erase(std::find(m_bannedUserIDs[acrServerID].begin(), m_bannedUserIDs[acrServerID].end(), std::make_pair(acrUserID, false)));
    }
    else if (std::find(m_bannedUserIDs[acrServerID].begin(), m_bannedUserIDs[acrServerID].end(), std::make_pair(acrUserID, true)) != m_bannedUserIDs[acrServerID].end()) {
        m_bannedUserIDs[acrServerID].erase(std::find(m_bannedUserIDs[acrServerID].begin(), m_bannedUserIDs[acrServerID].end(), std::make_pair(acrUserID, true)));
    }
}

void ServerCache::addUserDMchannelID(const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID) {
    m_userDMchannelIDs[acrUserID] = acrChannelID;
}

void ServerCache::addServerBotSettings(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID) {
    m_serverBotSettings[acrServerID] = ServerBotSettings();
}

/*
SleepyDiscord::Invite ServerCache::getInvite(const std::string& acrInviteCode) {

}
*/

const SleepyDiscord::Server& ServerCache::getServer(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID) {
    return m_servers.at(acrServerID);
}

/*
SleepyDiscord::Invite ServerCache::getInvite(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const std::string& acrInviteCode) {
    SleepyDiscord::Invite lReturnVal;
    try {
        SleepyDiscord::Server lServer = m_servers.at(acrServerID);
        try {
            lServer.findChannel(acrInviteCode);
        } catch(const std::exception& e) {
            throw std::out_of_range("getInvite(): invite not found in server");
        }
    } catch(const std::out_of_range& e) {
        throw std::out_of_range(std::string("getInvite(): ") + e.what());
        return SleepyDiscord::Invite();
    }
    return lReturnVal;
}
*/

const SleepyDiscord::Channel& ServerCache::getChannel(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID) {
        return *m_servers.at(acrServerID).findChannel(acrChannelID);
}

/*
SleepyDiscord::Message ServerCache::getMessage(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrChannelID, const SleepyDiscord::Snowflake<SleepyDiscord::Message>& acrMessageID) {
    SleepyDiscord::Message lReturnVal;
    try {
        SleepyDiscord::Server lServer = m_servers.at(acrServerID);
        try {
            lServer.findChannel(acrChannelID).findMessage(acrMessageID);
        } catch(const std::exception& e) {
            throw std::out_of_range("getMessage(): message not found in server");
        }
    } catch(const std::out_of_range& e) {
        throw std::out_of_range(std::string("getMessage(): ") + e.what());
        return SleepyDiscord::Message();
    }
    return lReturnVal;
}
*/

const SleepyDiscord::Role& ServerCache::getRole(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& acrRoleID) {
    return *m_servers.at(acrServerID).findRole(acrRoleID);
}


const SleepyDiscord::User& ServerCache::getUser(const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID) {
    return m_users.at(acrUserID);
}

const SleepyDiscord::ServerMember& ServerCache::getMember(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID) {
    return *m_servers.at(acrServerID).findMember(acrUserID);
}

ServerBotSettings& ServerCache::getServerBotSettings(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID) {
    return m_serverBotSettings.at(acrServerID);
}

const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& ServerCache::getUserDMchannelID(const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrUserID) {
    return m_userDMchannelIDs.at(acrUserID);
}

std::vector<SleepyDiscord::Server> ServerCache::getServers() {
    std::vector<SleepyDiscord::Server> lServers;
    for(const auto& lVal : m_servers) {
        lServers.push_back(lVal.second);
    }
    return lServers;
}

const std::unordered_map<SleepyDiscord::Snowflake<SleepyDiscord::User>, SleepyDiscord::User, UserIDHash>& ServerCache::getUsers() {
    return m_users;
}

const std::list<SleepyDiscord::Channel>& ServerCache::getServerChannels(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID) {
    return m_servers.at(acrServerID).channels;
}

const std::list<SleepyDiscord::ServerMember>& ServerCache::getServerMembers(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID) {
    return m_servers.at(acrServerID).members;
}

const std::list<SleepyDiscord::Role>& ServerCache::getRoles(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID) {
    return m_servers.at(acrServerID).roles;
}

std::vector<SleepyDiscord::User> ServerCache::getKickedUsers(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID) {
    std::vector<SleepyDiscord::User> lVec;
    for (const auto& lUserID : m_kickedUserIDs.at(acrServerID)) {
        lVec.push_back(getUser(lUserID.first));
    }
    return lVec;
}

std::vector<SleepyDiscord::User> ServerCache::getBannedUsers(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID) {
    std::vector<SleepyDiscord::User> lVec;
    for (const auto& lUserID : m_bannedUserIDs.at(acrServerID)) {
        lVec.push_back(getUser(lUserID.first));
    }
    return lVec;
}

std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Server>> ServerCache::getServerIDs() {
    std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Server>> lServerIDs;
    for(const auto lVal : m_servers) {
        lServerIDs.push_back(lVal.second.ID);
    }
    return lServerIDs;
}

std::unordered_map<SleepyDiscord::Snowflake<SleepyDiscord::Server>, ServerBotSettings, ServerIDHash>& ServerCache::getAllServerBotSettings() {
    return m_serverBotSettings;
}

const std::unordered_map<SleepyDiscord::Snowflake<SleepyDiscord::User>, SleepyDiscord::Snowflake<SleepyDiscord::Channel>, UserIDHash>& ServerCache::getUserDMchannelIDs() {
    return m_userDMchannelIDs;
}

std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Channel>> ServerCache::getServerChannelIDs(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID) {
    std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Channel>> lChannelIDs;
    for (const auto& lChannel : m_servers.at(acrServerID).channels) {
        lChannelIDs.push_back(lChannel.ID);
    }
    return lChannelIDs;
}

std::vector<SleepyDiscord::Snowflake<SleepyDiscord::ServerMember>> ServerCache::getServerMemberIDs(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID) {
    std::vector<SleepyDiscord::Snowflake<SleepyDiscord::ServerMember>> lServerMemberIDs;
    for (const auto& lMember : getServer(acrServerID).members) {
        lServerMemberIDs.push_back(SleepyDiscord::Snowflake<SleepyDiscord::ServerMember>(lMember.ID));
    }
    return lServerMemberIDs;
}

std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Role>> ServerCache::getRoleIDs(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID) {
    std::vector<SleepyDiscord::Snowflake<SleepyDiscord::Role>> lRoleIDs;
    for(const auto& lRole : m_servers.at(acrServerID).roles) {
        lRoleIDs.push_back(lRole.ID);
    }
    return lRoleIDs;
}

const std::vector<std::pair<SleepyDiscord::Snowflake<SleepyDiscord::User>, bool>>& ServerCache::getKickedUserIDs(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID) {
    return m_kickedUserIDs.at(acrServerID);
}

const std::vector<std::pair<SleepyDiscord::Snowflake<SleepyDiscord::User>, bool>>& ServerCache::getBannedUserIDs(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& acrServerID) {
    return m_bannedUserIDs.at(acrServerID);
}