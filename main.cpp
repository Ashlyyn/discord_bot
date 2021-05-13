#include "sleepy_discord/sleepy_discord.h"
#include "bot_client.hpp"

int main() {
	std::ifstream lConfigFile("../config.json");
	std::string lContent(std::istreambuf_iterator<char>(lConfigFile), (std::istreambuf_iterator<char>()));
	rapidjson::Document lDoc;
	lDoc.Parse(lContent.c_str());
	rapidjson::Value& lTokenVal = lDoc["token"];
	rapidjson::Value& lOwnerIDVal = lDoc["ownerID"];
	try {
		if(lTokenVal.IsNull()) {
			throw std::runtime_error("config.json token field null, exiting");
		} else if(!lTokenVal.IsString()) {
			throw std::runtime_error("config.json token field invalid data, exiting");
		}

		if(lOwnerIDVal.IsNull()) {
			throw std::runtime_error("config.json ownerID field null, exiting");
		} else if(!lOwnerIDVal.IsString()) {
			throw std::runtime_error("config.json ownerID field invalid data, exiting");
		}
	} catch(const std::runtime_error& e) {
		std::fprintf(stderr, "main(): error reading config info: %s\n", e.what());
		return 3;
	}

	try {
		MyClientClass::s_ownerID = std::string(lOwnerIDVal.GetString());
		MyClientClass client(lTokenVal.GetString(), SleepyDiscord::USER_CONTROLED_THREADS);
		try {
			client.init();
			client.run();
		} catch (std::runtime_error& e) {
			std::fprintf(stderr, "main(): uncaught exception: %s\n", e.what());
			return 1;
		}
	} catch (...) {
		std::fprintf(stderr, "main(): error running bot: %s\n", lTokenVal.GetString());
		return 2;
	}
}