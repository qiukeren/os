#include "x_cflag.h"

int main(int argc, char** argv) {
    int requests = 5000;
    int concurrency = 10;
    bool verbose = false;
    const char* url = "https://perezdecastro.org";

    const struct cflag options[] = {
        CFLAG(int, "requests", 'r', &requests, "Number of total requests"),
        CFLAG(int, "concurrency", 0 /* no short option */, &concurrency,
              "Number of concurrent requests"),
        CFLAG(bool, "verbose" /* no long option */, 'v', &verbose,
              "Verbosely show progress"),
        CFLAG(string, "url", 'U', &url, "Target URL"),
        CFLAG_HELP,
        CFLAG_END};

    cflag_apply(options, "[options] --url URL", &argc, &argv);

    printf("requests:%d\n", requests);
    printf("concurrency:%d\n", concurrency);
    printf("verbose:%d\n", verbose);
    printf("url:%s\n", url);

    return 0;
}
