#ifndef _MENTION_H_
#define _MENTION_H_

template<class T> class Mention {
public:
    Mention(const std::string& acrSnowflake);
    Mention(const T& acrType);
    Mention(const SleepyDiscord::Snowflake<T>& acrSnowflake);
    
    inline void operator=(const T& acrRhs);
    
    bool operator==(const T& acrRhs) const {
        return acrRhs == m_mention;
    }

    operator const std::string&() const {
        return m_prefix + m_mention + ">";
    }

    std::string string() const {
        return m_prefix + m_mention + ">";
    }

private:
    std::string m_prefix; // prefix for mentions - <@! for users, <# for channels, <@& for roles
    std::string m_mention; // user/channel/role ID
};

// allow for concatenation with std::string
template<class T> std::string operator+ (const std::string& acrString, const Mention<T>& acrMention) {
    return acrString + acrMention.string();
}
#endif