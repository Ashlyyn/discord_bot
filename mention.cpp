#include "sleepy_discord/sleepy_discord.h"

#include "mention.hpp"

// templates specialized since user, channel, and role all have a different prefix

template<> Mention<SleepyDiscord::User>::Mention(const std::string& snowflake) {
    m_prefix = "<@!";
    m_mention = snowflake;
}

template<> Mention<SleepyDiscord::ServerMember>::Mention(const std::string& snowflake) {
    m_prefix = "<@!";
    m_mention = snowflake;
}

template<> Mention<SleepyDiscord::Channel>::Mention(const std::string& snowflake) {
    m_prefix = "<#";
    m_mention = snowflake;
}

template<> Mention<SleepyDiscord::Role>::Mention(const std::string& snowflake) {
    m_prefix = "<@&";
    m_mention = snowflake;
}

template<> Mention<SleepyDiscord::User>::Mention(const SleepyDiscord::User& user) {
    SleepyDiscord::Snowflake<SleepyDiscord::User> snowflake = user;
    m_prefix = "<@!";
    m_mention = snowflake;
}

template<> Mention<SleepyDiscord::ServerMember>::Mention(const SleepyDiscord::ServerMember& member) {
    SleepyDiscord::Snowflake<SleepyDiscord::ServerMember> snowflake = member;
    m_prefix = "<@!";
    m_mention = snowflake;
}

template<> Mention<SleepyDiscord::Channel>::Mention(const SleepyDiscord::Channel& channel) {
    SleepyDiscord::Snowflake<SleepyDiscord::Channel> snowflake = channel;
    m_prefix = "<@!";
    m_mention = snowflake;
}

template<> Mention<SleepyDiscord::Role>::Mention(const SleepyDiscord::Role& role) {
    SleepyDiscord::Snowflake<SleepyDiscord::Role> snowflake = role;
    m_prefix = "<#";
    m_mention = snowflake;
}

template<> Mention<SleepyDiscord::User>::Mention(const SleepyDiscord::Snowflake<SleepyDiscord::User>& snowflake) {
    m_prefix = "<@!";
    m_mention = snowflake;
}

template<> Mention<SleepyDiscord::ServerMember>::Mention(const SleepyDiscord::Snowflake<SleepyDiscord::ServerMember>& snowflake) {
    m_prefix = "<@!";
    m_mention = snowflake;
}

template<> Mention<SleepyDiscord::Channel>::Mention(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& snowflake) {
    m_prefix = "<#";
    m_mention = snowflake;
}

template<> Mention<SleepyDiscord::Role>::Mention(const SleepyDiscord::Snowflake<SleepyDiscord::Role>& snowflake) {
    m_prefix = "<@&";
    m_mention = snowflake;
}

template<> Mention<SleepyDiscord::Snowflake<SleepyDiscord::User>>::Mention(const SleepyDiscord::Snowflake<SleepyDiscord::User>& snowflake) {
    m_prefix = "<@!";
    m_mention = snowflake;
}

template<> Mention<SleepyDiscord::Snowflake<SleepyDiscord::ServerMember>>::Mention(const SleepyDiscord::Snowflake<SleepyDiscord::ServerMember>& snowflake) {
    m_prefix = "<@!";
    m_mention = snowflake;
}

template<> Mention<SleepyDiscord::Snowflake<SleepyDiscord::Channel>>::Mention(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& snowflake) {
    m_prefix = "<#";
    m_mention = snowflake;
}

template<> Mention<SleepyDiscord::Snowflake<SleepyDiscord::Role>>::Mention(const SleepyDiscord::Snowflake<SleepyDiscord::Role>& snowflake) {
    m_prefix = "<@&";
    m_mention = snowflake;
}

template<> void Mention<SleepyDiscord::User>::operator=(const SleepyDiscord::User& user) {
    SleepyDiscord::Snowflake<SleepyDiscord::User> snowflake = user;
    m_prefix = "<@!";
    m_mention = snowflake;
}

template<> void Mention<SleepyDiscord::ServerMember>::operator=(const SleepyDiscord::ServerMember& member) {
    SleepyDiscord::Snowflake<SleepyDiscord::ServerMember> snowflake = member;
    m_prefix = "<@!";
    m_mention = snowflake;
}

template<> void Mention<SleepyDiscord::Channel>::operator=(const SleepyDiscord::Channel& channel) {
    SleepyDiscord::Snowflake<SleepyDiscord::Channel> snowflake = channel;
    m_prefix = "<#";
    m_mention = snowflake;
}

template<> void Mention<SleepyDiscord::Role>::operator=(const SleepyDiscord::Role& role) {
    SleepyDiscord::Snowflake<SleepyDiscord::Role> snowflake = role;
    m_prefix = "<@&";
    m_mention = snowflake;
}

template<> void Mention<SleepyDiscord::Snowflake<SleepyDiscord::User>>::operator=(const SleepyDiscord::Snowflake<SleepyDiscord::User>& snowflake) {
    m_prefix = "<@!";
    m_mention = snowflake;
}

template<> void Mention<SleepyDiscord::Snowflake<SleepyDiscord::ServerMember>>::operator=(const SleepyDiscord::Snowflake<SleepyDiscord::ServerMember>& snowflake) {
    m_prefix = "<@!";
    m_mention = snowflake;
}

template<> void Mention<SleepyDiscord::Snowflake<SleepyDiscord::Channel>>::operator=(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& snowflake) {
    m_prefix = "<#";
    m_mention = snowflake;
}

template<> void Mention<SleepyDiscord::Snowflake<SleepyDiscord::Role>>::operator=(const SleepyDiscord::Snowflake<SleepyDiscord::Role>& snowflake) {
    m_prefix = "<@&";
    m_mention = snowflake;
}