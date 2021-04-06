#include "sleepy_discord/sleepy_discord.h"
#include "bot_client.hpp"

int main() {
	MyClientClass client("NzgzMTc3ODExOTUwOTYwNjcw.X8W9LQ.E3Kusm_bV5g8KbDzTymcQjobPVM", SleepyDiscord::USER_CONTROLED_THREADS);
	try{
		client.run();
	} catch(std::runtime_error& e) {
		std::fprintf(stderr, "%s\n", e.what());
		return 1;
	}
}
