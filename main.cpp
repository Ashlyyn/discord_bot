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

		else if (message.startsWith(prefix + "mute voice ")) {
			muteVoice(message.serverID, message.content.substr(prefix.size() + strlen("mute voice ")));
		}

		else if (message.startsWith(prefix + "unmute voice")) {
			unmuteVoice(message.serverID, message.content.substr(prefix.size() + strlen("unmute voice ")));
		}

		else if (message.startsWith(prefix + "mute text ")) {
			muteText(message.serverID, getSnowflake(message.content.substr(prefix.size() + strlen("mute text "))));
		}

		else if (message.startsWith(prefix + "unmute text ")) {
			unmuteText(message.serverID, getSnowflake(message.content.substr(prefix.size() + strlen("unmute text "))));
		}

		else if (message.startsWith(prefix + "logs ")) {
			setLogsChannel(SleepyDiscord::Snowflake<SleepyDiscord::Channel>(getSnowflake(message.content.substr(prefix.size() + strlen("logs ")))));
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

		else if (message.startsWith(prefix + "permissions set ")) {
			auto words = split(message.content);
			std::map<std::string, COMMAND_PERMISSION> perms = {
				{ std::string("owner_only"), COMMAND_PERMISSION::OWNER_ONLY },
				{ std::string("no_owner"), COMMAND_PERMISSION::NO_OWNER },
				{ std::string("bot_admin"), COMMAND_PERMISSION::BOT_ADMIN },
				{ std::string("all"), COMMAND_PERMISSION::CMD_ALL }
			};
			std::map<std::string, COMMAND_TYPE> type = {
				{ std::string("admin"), COMMAND_TYPE::ADMIN },
				{ std::string("non_admin"), COMMAND_TYPE::NON_ADMIN },
				{ std::string("all"), COMMAND_TYPE::ROLE_ALL }
			};
			setPermissions(perms[words[2]], type[words[3]]);
			logAction("**PERMISSIONS CHANGE:**\n```Type: " + words[3] + "\nSet to: " + words[2] + "\nSet by: " + message.author.username + "#" + message.author.discriminator + "```\n");
		}

		else if (message.startsWith(prefix + "die")) {
			if(checkPermissions(message.author, ADMIN) == true) {
				die(message.channelID);
			}
		}

		else if(message.startsWith(prefix)) {
			sendMessage(message.channelID, "Unknown command.");
		}

		if(isMuted(message.author.ID)) {
			deleteMessage(message.channelID, message.ID);
		}
	}

protected:
	std::string prefix = "F!";
	SleepyDiscord::Snowflake<SleepyDiscord::Channel> logsChannel;
	std::vector<SleepyDiscord::Snowflake<SleepyDiscord::User> > mutedUsers;

	enum COMMAND_PERMISSION {
		OWNER_ONLY,
		NO_OWNER,
		BOT_ADMIN,
		CMD_ALL
	};

	enum COMMAND_TYPE {
		ADMIN,
		NON_ADMIN,
		ROLE_ALL
	};

	std::array<int, 2> permissions;

	void changePrefix(const std::string& newPrefix) {
		prefix = newPrefix;
	}

	void hello(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channel, const SleepyDiscord::User& user) {
		sendMessage(channel, "Hello, " + user.username);
	}

	void echo(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channel, const std::string& message) {
		sendMessage(channel, message);
	}

	void muteVoice(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::User>& user) {
		muteServerMember(server, user, true);
	}

	void unmuteVoice(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::User>& user) {
		muteServerMember(server, user, false);
	}

	void muteText(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::User> user) {
		if(std::count(mutedUsers.begin(), mutedUsers.end(), user) == 0) {
			mutedUsers.push_back(user);
		}
	}

	void unmuteText(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& server, const SleepyDiscord::Snowflake<SleepyDiscord::User> user) {
		if(std::count(mutedUsers.begin(), mutedUsers.end(), user) > 0) {
			mutedUsers.erase(std::find(mutedUsers.begin(), mutedUsers.end(), user));
		}
	}

	void setLogsChannel(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channel) {
		logsChannel = channel;
	}

	void logAction(const std::string& str) {
		sendMessage(logsChannel, str);
	}

	void setPermissions(COMMAND_PERMISSION commandPerm, COMMAND_TYPE commandType) {
		if(commandType == ROLE_ALL) {
			permissions[COMMAND_TYPE::ADMIN] = commandPerm;
			permissions[COMMAND_TYPE::NON_ADMIN] = commandPerm;
		} else {
			permissions[commandType] = commandPerm;
		}
	}

	void die(const SleepyDiscord::Snowflake<SleepyDiscord::Channel> channel) {
		sendMessage(channel, "Okay.");
		exit(0);
	}


private:
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

	std::string getSnowflake(const std::string str) {
		if(str.find("<@!") != std::string::npos) {
			return str.substr(3, str.size() - 3 - 1);
		}
		else if(str.find("<#") != std::string::npos) {
			return str.substr(2, str.size() - 2 - 1);
		}
		else throw std::runtime_error("getSnowflake: string is not a server or channel mention.");
	}

	bool isMuted(const SleepyDiscord::Snowflake<SleepyDiscord::User>& user) {
		if(std::count(mutedUsers.begin(), mutedUsers.end(), user) >= 1) {
			return true;
		} else {
			return false;
		}
	}

	bool checkPermissions(SleepyDiscord::Snowflake<SleepyDiscord::User>& user, COMMAND_TYPE commandType) {
		if(permissions[commandType] == OWNER_ONLY && user != 518216114665291786) {
			return false;
		} 
		else if(permissions[commandType] == NO_OWNER && user == 518216114665291786) {
			return false;
		}
		else {
			return true;
		}
	}
};

int main() {
	MyClientClass client("NzgzMTc3ODExOTUwOTYwNjcw.X8W9LQ.E3Kusm_bV5g8KbDzTymcQjobPVM", SleepyDiscord::USER_CONTROLED_THREADS);
	try{
		client.run();
	} catch(std::runtime_error& e) {
		std::fprintf(stderr, "%s\n", e.what());
		return 1;
	}
}
