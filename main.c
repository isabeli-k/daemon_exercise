#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>
#include "daemon.h"

int main(int argc, char *argv[]) {
	int ret;
	const char *LOGNAME = "DAEMON_EXAMPLE";

	ret = start_daemon(0);

	if(ret) {
		syslog(LOG_USER | LOG_ERR, "error starting");
		closelog();
		return EXIT_FAILURE;
	}

	openlog(LOGNAME, LOG_PID, LOG_USER);
	syslog(LOG_USER | LOG_INFO, "starting");

	while(1) {
		sleep(60);
		syslog(LOG_USER | LOG_INFO, "running");
	}

	return EXIT_SUCCESS;
}
