#define EV_TEST_NO_LUA_SETUP
#include "test.lua.h"

#define TMPFILE_PATH    "364ff706-a89b-4ad0-8819-c3896b2e302a"

TEST_FIXTURE_SETUP(lua)
{
    ev_fs_remove_sync(TMPFILE_PATH, 1);
    test_lua_setup();
}

TEST_FIXTURE_TEARDOWN(lua)
{
    test_lua_teardown();
    ev_fs_remove_sync(TMPFILE_PATH, 1);
}

TEST_F(lua, fs_file)
{
    static const char* script =
"local loop = ev.loop()\n"
"loop:co(function()\n"
"    local _, file = loop:fs_file(test.sample_file, ev.EV_FS_O_CREAT | ev.EV_FS_O_RDWR)\n"
"    assert(file ~= nil)\n"
"    file:write(\"hello world\")\n"
"    file:seek(ev.EV_FS_SEEK_BEG, 0)\n"
"    local _, data = file:read()\n"
"    assert(data == \"hello world\")\n"
"end)\n"
"loop:run()\n";

    test_lua_set_test_string("sample_file", TMPFILE_PATH);

    ASSERT_EQ_INT(test_lua_dostring(g_test_lua.L, script), LUA_OK,
        "%s", lua_tostring(g_test_lua.L, -1));
}