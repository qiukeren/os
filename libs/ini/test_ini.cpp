#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ini.h"
#include "gtest/gtest.h"

using namespace std;


typedef struct {
    int version;
    const char* name;
    const char* email;
} configuration;

static int handler(void* user,
                   const char* section,
                   const char* name,
                   const char* value) {
    configuration* pconfig = (configuration*)user;

#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
    if (MATCH("protocol", "version")) {
        pconfig->version = atoi(value);
    } else if (MATCH("user", "name")) {
        pconfig->name = strdup(value);
    } else if (MATCH("user", "email")) {
        pconfig->email = strdup(value);
    } else {
        return 0; /* unknown section/name, error */
    }
    return 1;
}


TEST(test_ini, check_basic_parse) {
    string n = "Bob Smith";
    string m = "bob@smith.com";
    int v = 6;
    
    configuration config;
    config.version = 0; /* set defaults */
    config.name = NULL;
    config.email = NULL;

    ASSERT_TRUE(ini_parse("test_files/test.ini", handler, &config) > 0);

    printf("Config loaded from 'test.ini': version=%d, name=%s, email=%s\n",
           config.version, config.name, config.email);

    EXPECT_STREQ(config.name, n.c_str());
    EXPECT_STREQ(config.email, m.c_str());
    EXPECT_EQ(config.version, v);
}
