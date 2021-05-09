#include "sleepy_discord/sleepy_discord.h"
#include "bot_client.hpp"

int main() {
	std::ifstream lConfigFile("../config.json");
	std::string lContent(std::istreambuf_iterator<char>(lConfigFile), (std::istreambuf_iterator<char>()));
	rapidjson::Document lDoc;
	lDoc.Parse(lContent.c_str());
	rapidjson::Value& lToken = lDoc["token"];

	try {
		MyClientClass client(lToken.GetString(), SleepyDiscord::USER_CONTROLED_THREADS);
		try {
			client.init();
			client.run();
		}
		catch (std::runtime_error& e) {
			std::fprintf(stderr, "%s\n", e.what());
			return 1;
		}
	}
	catch (...) {
		std::fprintf(stderr, "%s\n", lToken.GetString());
	}
}