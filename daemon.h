#ifndef DAEMON_H
#define DAEMON_H

// Flags
#define NO_UMASK0            0x01
#define NO_CHDIR             0x02
#define NO_CLOSE_FILES       0x04
#define NO_REOPEN_SFDS	     0x08
#define MAX_CLOSE            0x2000

// Daemon statuses
typedef enum {
	DAEMON_SUCCESS = 0,
	DAEMON_ERROR_FORK = -1,
	DAEMON_ERROR_SETSID = -2,
	DAEMON_ERROR_CHDIR = -3,
	DAEMON_ERROR_DEVNULL = -4,
	DAEMON_ERROR_STDOUT = -5,
	DAEMON_ERROR_STDERR = -6
} daemon_status;

int start_daemon(int flags);

#endif
