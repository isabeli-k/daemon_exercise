#ifndef DAEMON_H
#define DAEMON_H

// Flags
#define BD_NO_UMASK0            0x01
#define BD_NO_CHDIR             0x02
#define BD_NO_CLOSE_FILES       0x04
#define BD_NO_REOPEN_STD_FDS    0x08
#define BD_MAX_CLOSE            8192

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
