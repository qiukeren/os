#include <gtest/gtest.h>
#include "x.h"
using namespace std;

// TEST(x_flag, test_flag) {
//     char* url_exp = "3aa3";
//     int argc = 7;
//     const char* argv[] = {"test_prog", "--requests", "1",   "--concurrency",
//                           "2",         "--url",      "3aa3"};
//     int requests = 5000;
//     int concurrency = 10;
//     const char* url = ":3000";

//     x_flag_int(&requests, "requests", "Number of total requests");
//     x_flag_int(&concurrency, "concurrency", "Number of concurrent requests");
//     x_flag_str(&url, "url", "Target url");
//     x_flag_parse(argc, argv, "1.0.0");

//     // puts("");
//     // printf("     requests: %d\n", requests);
//     // printf("  concurrency: %d\n", concurrency);
//     // printf("          url: %s\n", url);
//     // puts("");

//     EXPECT_EQ(requests, 1);
//     EXPECT_EQ(concurrency, 2);
//     EXPECT_STREQ(url, url_exp);
// }
