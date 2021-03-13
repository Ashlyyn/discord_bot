#include <sleepy_discord/sleepy_discord.h>

class MyClientClass : public SleepyDiscord::DiscordClient {
public:
	using SleepyDiscord::DiscordClient::DiscordClient;
	void onMessage(SleepyDiscord::Message message) override {
		if (message.startsWith(prefix + "prefix ")) {
			changePrefix(message.content.substr(prefix.size() + strlen("prefix ")));
		}
		else if (message.startsWith(prefix + "hello")) {
			hello(message.channelID, message.author);
		}

		else if (message.startsWith(prefix + "echo ")) {
			echo(message.channelID, message.content.substr(prefix.size() + strlen("echo ")));
		}

		else if (message.startsWith(prefix + "logs ")) {
			setLogsChannel(SleepyDiscord::Snowflake<SleepyDiscord::Channel>(std::string(message.content.substr(prefix.size() + strlen("logs ")))));
			logAction("Logs enabled in " + message.content.substr(prefix.size() + strlen("logs ")));
		}

		else if (message.startsWith(prefix + "delete ")) {
			std::string log;
			std::vector<std::string> words = split(message.content);
			if (words.size() > 2) {
				log = "**MESSAGE DELETE:**\n```Message ID: " + words[2] + "\nDeleted by: " + message.author.username + "\nChannel: " + words[1] + "\nMessage content: " + message.content + "\n```";
				deleteMessage(SleepyDiscord::Snowflake<SleepyDiscord::Channel>(words[1]), SleepyDiscord::Snowflake<SleepyDiscord::Message>(words[2]));
			}
			else {
				log = "**MESSAGE DELETE:**\n```Message ID: " + words[1] + "\nDeleted by: " + message.author.username + "\nChannel: " + message.channelID.string() + "\nMessage content: " + message.content +"\n```";
				deleteMessage(message.channelID, SleepyDiscord::Snowflake<SleepyDiscord::Message>(words[1]));
			}
			logAction(log);
		}

		else if (message.startsWith(prefix + "die")) {
			die(message.channelID);
		}
	}

private:
	std::string prefix = "F!";
	SleepyDiscord::Snowflake<SleepyDiscord::Channel> logsChannel;

	void changePrefix(const std::string& newPrefix) {
		prefix = newPrefix;
	}

	void hello(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channel, const SleepyDiscord::User& user) {
		sendMessage(channel, "Hello, " + user.username);
	}

	void echo(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channel, const std::string& message) {
		sendMessage(channel, message);
	}

	void setLogsChannel(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channel) {
		logsChannel = channel;
	}

	void logAction(const std::string& str) {
		sendMessage(logsChannel, str);
	}

	void die(const SleepyDiscord::Snowflake<SleepyDiscord::Channel> channel) {
		sendMessage(channel, "Okay.");
		exit(0);
	}

	std::vector<std::string> split(std::string string) {
		std::vector<std::string> vec;
		int pos = 0;
		while (1) {
			int temp = pos;
			pos = string.find(" ", pos);
			std::string word = string.substr(temp, pos - temp);
			if (pos < temp) {
				std::string word = string.substr(temp);
				if (word.find_first_not_of(' ') != std::string::npos) {
					vec.push_back(word);
				}
				break;
			}

			if (word.find_first_not_of(' ') != std::string::npos) {
				vec.push_back(word);
			}
			pos++;
		}
		return vec;
	}
};

int main() {
	MyClientClass client("NzgzMTc3ODExOTUwOTYwNjcw.X8W9LQ.E3Kusm_bV5g8KbDzTymcQjobPVM", SleepyDiscord::USER_CONTROLED_THREADS);
	client.run();
}
