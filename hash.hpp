#ifndef _HASH_H_
#define _HASH_H_

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

#endif