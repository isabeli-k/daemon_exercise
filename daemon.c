#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "daemon.h"

static int process_fork() {
	pid_t pid = fork();
	
	if(pid < 0)
		return -1;
	
	if(pid > 0)
		_exit(EXIT_SUCCESS);
	
	return 0;
}

int start_daemon(int flags) {
	
	// First fork to detach from original parent
	if(process_fork() == -1)
		return DAEMON_ERROR_FORK;

	if(setsid() == -1)
		return DAEMON_ERROR_SETSID;

	// Second fork
	if(process_fork() == -1)
		return DAEMON_ERROR_FORK;

	if(!(flags & BD_NO_UMASK0))
		umask(0);
	
	if(!(flags & BD_NO_CHDIR)) {
		if (chdir("/") == -1)
			return DAEMON_ERROR_CHDIR;
	}
	
	long max_open_files;
	int fd;
	
	if(!(flags & BD_NO_CLOSE_FILES)) {
		max_open_files = sysconf(_SC_OPEN_MAX);
		
		if(max_open_files == -1)
			max_open_files = BD_MAX_CLOSE;
		
		for(fd = 0; fd < max_open_files; fd++)
			close(fd);
	}

	if(!(flags & BD_NO_REOPEN_STD_FDS)) {
		fd = open("/dev/null", O_RDWR);
		
		if(fd != STDIN_FILENO)
			return DAEMON_ERROR_DEVNULL;
		
		if(dup2(STDIN_FILENO, STDOUT_FILENO) != STDOUT_FILENO)
			return DAEMON_ERROR_STDOUT;
		
		if(dup2(STDIN_FILENO, STDERR_FILENO) != STDERR_FILENO)
			return DAEMON_ERROR_STDERR;
	}

	return DAEMON_SUCCESS;
}
