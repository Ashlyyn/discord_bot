#ifndef _MENTION_H_
#define _MENTION_H_

template<class T> class Mention {
public:
    Mention(const std::string& snowflake);
    Mention(const T& type);
    Mention(const SleepyDiscord::Snowflake<T>& snowflake);
    
    inline void operator=(const T& a);
    
    bool operator==(const T& a) const {
        return a == m_mention;
    }

    operator const std::string&() const {
        return m_prefix + m_mention + ">";
    }

    std::string string() const {
        return m_prefix + m_mention + ">";
    }

private:
    std::string m_prefix;
    std::string m_mention;
};

template<class T> std::string operator+ (const std::string& string, const Mention<T>& mention) {
    return string + mention.string();
}
#endif