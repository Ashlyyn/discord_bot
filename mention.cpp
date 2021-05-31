#include "sleepy_discord/sleepy_discord.h"

#include "mention.hpp"

#include <string>

// templates specialized since user, channel, and role all have a different prefix

template<> Mention<SleepyDiscord::User>::Mention(const std::string& acrSnowflake) {
    m_prefix = "<@";
    m_mention = acrSnowflake;
}

template<> Mention<SleepyDiscord::ServerMember>::Mention(const std::string& acrSnowflake) {
    m_prefix = "<@!";
    m_mention = acrSnowflake;
}

template<> Mention<SleepyDiscord::Channel>::Mention(const std::string& acrSnowflake) {
    m_prefix = "<#";
    m_mention = acrSnowflake;
}

template<> Mention<SleepyDiscord::Role>::Mention(const std::string& acrSnowflake) {
    m_prefix = "<@&";
    m_mention = acrSnowflake;
}

template<> Mention<SleepyDiscord::User>::Mention(const SleepyDiscord::User& acrUser) {
    SleepyDiscord::Snowflake<SleepyDiscord::User> acrSnowflake = acrUser;
    m_prefix = "<@";
    m_mention = acrSnowflake;
}

template<> Mention<SleepyDiscord::ServerMember>::Mention(const SleepyDiscord::ServerMember& acrMember) {
    SleepyDiscord::Snowflake<SleepyDiscord::ServerMember> acrSnowflake = acrMember;
    m_prefix = "<@!";
    m_mention = acrSnowflake;
}

template<> Mention<SleepyDiscord::Channel>::Mention(const SleepyDiscord::Channel& acrChannel) {
    SleepyDiscord::Snowflake<SleepyDiscord::Channel> acrSnowflake = acrChannel;
    m_prefix = "<@!";
    m_mention = acrSnowflake;
}

template<> Mention<SleepyDiscord::Role>::Mention(const SleepyDiscord::Role& acrRole) {
    SleepyDiscord::Snowflake<SleepyDiscord::Role> acrSnowflake = acrRole;
    m_prefix = "<#";
    m_mention = acrSnowflake;
}

template<> Mention<SleepyDiscord::User>::Mention(const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrSnowflake) {
    m_prefix = "<@";
    m_mention = acrSnowflake;
}

template<> Mention<SleepyDiscord::ServerMember>::Mention(const SleepyDiscord::Snowflake<SleepyDiscord::ServerMember>& acrSnowflake) {
    m_prefix = "<@!";
    m_mention = acrSnowflake;
}

template<> Mention<SleepyDiscord::Channel>::Mention(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrSnowflake) {
    m_prefix = "<#";
    m_mention = acrSnowflake;
}

template<> Mention<SleepyDiscord::Role>::Mention(const SleepyDiscord::Snowflake<SleepyDiscord::Role>& acrSnowflake) {
    m_prefix = "<@&";
    m_mention = acrSnowflake;
}

template<> Mention<SleepyDiscord::Snowflake<SleepyDiscord::User>>::Mention(const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrSnowflake) {
    m_prefix = "<@";
    m_mention = acrSnowflake;
}

template<> Mention<SleepyDiscord::Snowflake<SleepyDiscord::ServerMember>>::Mention(const SleepyDiscord::Snowflake<SleepyDiscord::ServerMember>& acrSnowflake) {
    m_prefix = "<@!";
    m_mention = acrSnowflake;
}

template<> Mention<SleepyDiscord::Snowflake<SleepyDiscord::Channel>>::Mention(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrSnowflake) {
    m_prefix = "<#";
    m_mention = acrSnowflake;
}

template<> Mention<SleepyDiscord::Snowflake<SleepyDiscord::Role>>::Mention(const SleepyDiscord::Snowflake<SleepyDiscord::Role>& acrSnowflake) {
    m_prefix = "<@&";
    m_mention = acrSnowflake;
}

template<> void Mention<SleepyDiscord::User>::operator=(const SleepyDiscord::User& acrUser) {
    SleepyDiscord::Snowflake<SleepyDiscord::User> acrSnowflake = acrUser;
    m_prefix = "<@";
    m_mention = acrSnowflake;
}

template<> void Mention<SleepyDiscord::ServerMember>::operator=(const SleepyDiscord::ServerMember& acrMember) {
    SleepyDiscord::Snowflake<SleepyDiscord::ServerMember> acrSnowflake = acrMember;
    m_prefix = "<@!";
    m_mention = acrSnowflake;
}

template<> void Mention<SleepyDiscord::Channel>::operator=(const SleepyDiscord::Channel& acrChannel) {
    SleepyDiscord::Snowflake<SleepyDiscord::Channel> acrSnowflake = acrChannel;
    m_prefix = "<#";
    m_mention = acrSnowflake;
}

template<> void Mention<SleepyDiscord::Role>::operator=(const SleepyDiscord::Role& acrRole) {
    SleepyDiscord::Snowflake<SleepyDiscord::Role> acrSnowflake = acrRole;
    m_prefix = "<@&";
    m_mention = acrSnowflake;
}

template<> void Mention<SleepyDiscord::Snowflake<SleepyDiscord::User>>::operator=(const SleepyDiscord::Snowflake<SleepyDiscord::User>& acrSnowflake) {
    m_prefix = "<@";
    m_mention = acrSnowflake;
}

template<> void Mention<SleepyDiscord::Snowflake<SleepyDiscord::ServerMember>>::operator=(const SleepyDiscord::Snowflake<SleepyDiscord::ServerMember>& acrSnowflake) {
    m_prefix = "<@!";
    m_mention = acrSnowflake;
}

template<> void Mention<SleepyDiscord::Snowflake<SleepyDiscord::Channel>>::operator=(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& acrSnowflake) {
    m_prefix = "<#";
    m_mention = acrSnowflake;
}

template<> void Mention<SleepyDiscord::Snowflake<SleepyDiscord::Role>>::operator=(const SleepyDiscord::Snowflake<SleepyDiscord::Role>& acrSnowflake) {
    m_prefix = "<@&";
    m_mention = acrSnowflake;
}