#include <cbehave/cbehave.h>

#include <utils.h>

#include <SDL_joystick.h>

#include <sys_config.h>

// Stubs
extern DECLSPEC const char * SDLCALL SDL_JoystickName(int device_index)
{
	UNUSED(device_index);
	return "";
}

FEATURE(1, "Path functions")
	SCENARIO("Relative path")
	{
		GIVEN("a relative path")
			char to[CDOGS_PATH_MAX];
			strcpy(to, "/a/path/to");
		GIVEN_END

		WHEN("I get the relative path from another path")
			char from[CDOGS_PATH_MAX];
			strcpy(from, "/a/path/from");
		WHEN_END

		THEN("the result should be a relative path from one to the other");
			char rel[CDOGS_PATH_MAX];
			RelPath(rel, to, from);
			SHOULD_STR_EQUAL(rel, "../to");
		THEN_END
	}
	SCENARIO_END
	SCENARIO("Relative path from different path separators")
	{
		GIVEN("a relative path with forward slashes")
			char to[CDOGS_PATH_MAX];
			strcpy(to, "/a/path/to");
		GIVEN_END

		WHEN("I get the relative path from another path with back slashes")
			char from[CDOGS_PATH_MAX];
			strcpy(from, "\\a\\path\\from");
		WHEN_END

		THEN("the result should be a relative path from one to the other");
			char rel[CDOGS_PATH_MAX];
			RelPath(rel, to, from);
			SHOULD_STR_EQUAL(rel, "../to");
		THEN_END
	}
	SCENARIO_END
FEATURE_END

int main(void)
{
	cbehave_feature features[] =
	{
		{feature_idx(1)}
	};
	
	return cbehave_runner("Utils features are:", features);
}