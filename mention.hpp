#ifndef _MENTION_H_
#define _MENTION_H_

template<class T> class Mention {
public:
    Mention(const std::string& snowflake);
    Mention(const T& type);
    Mention(const SleepyDiscord::Snowflake<T>& snowflake);
    inline void operator=(const T& a);
    
    bool operator==(const T& a) const {
        return a == mention;
    }

    operator const std::string&() const {
        return prefix + mention + ">";
    }

    std::string string() const {
        return prefix + mention + ">";
    }

private:
    std::string prefix;
    std::string mention;
};

template<class T> std::string operator+ (const std::string& string, const Mention<T>& mention) {
    return string + mention.string();
}
#endif