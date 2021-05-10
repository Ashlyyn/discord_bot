#ifndef _MENTION_H_
#define _MENTION_H_

#include <string>

// creates mention from snowflake
// operator const std::string() and operator+() overloaded to allow ease of use with std::string
template<class T> class Mention {
public:
    Mention(const std::string& acrSnowflake);
    Mention(const T& acrType);
    Mention(const SleepyDiscord::Snowflake<T>& acrSnowflake);
    
    inline void operator=(const T& acrRhs);

    inline bool operator==(const T& acrRhs) const {
        return acrRhs == m_mention;
    }

    inline operator const std::string() const {
        return m_prefix + m_mention + ">";
    }

    inline const std::string string() const {
        return m_prefix + m_mention + ">";
    }

private:
    std::string m_prefix; // prefix for mentions - <@! for users, <# for channels, <@& for roles
    std::string m_mention; // user/channel/role ID
};

// allow for concatenation with std::string
template<class T> std::string operator+(const std::string& acrString, const Mention<T>& acrMention) {
    return acrString + acrMention.string();
}
#endif