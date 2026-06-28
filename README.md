# POSIX DAEMONISATION

This is an implementation of a classic Unix daemonisation pattern. It's based on Kerrisk's *The Linux Programming Interface* daemon implementation.

For modern Linux systems with systemd, this functionality is a simple foreground process and systemd handles daemonisation, but the goal of this exercise was to understand the double-fork pattern, setsid(), and file descriptor management. See the systemd documentation for the modern approach: https://0pointer.de/public/systemd-man/daemon.html#New-Style%20Daemons

## HOW IT WORKS:
1. First `fork()`. The parent process exits and the child continues running in the background.
2. `setsid()` creates a new session.
3. Second `fork()` to make sure the process doesn't accidentally get a terminal again.
4. Apply settings:
	- Reset file permissions mask (umask).
	- Change working directory to `/`.
	- Close open file descriptors.
5. Redirect standard input/output.

## STATUS CODES:
`start_daemon()` returns 0 on success or a negative error code on failure:

	DAEMON_ERROR_FORK     // fork() failed.
	DAEMON_ERROR_SETSID   // setsid() failed.
	DAEMON_ERROR_CHDIR    // chdir(/) failed.
	DAEMON_ERROR_DEVNULL  // failed to open /dev/null.
	DAEMON_ERROR_STDOUT   // failed to redirect stdout.
	DAEMON_ERROR_STDERR   // failed to redirect stderr.
	
## FLAGS:
Flags are bitmasks and can be combined with the | operator:

	NO_UMASK0  			  // don't reset file creation mask.
	NO_CHDIR 			  // don't change working directory to /.
	NO_CLOSE_FILES 		  // don't close all open file descriptors.
	NO_REOPEN_SFDS 		  // don't redirect stdout/stderr to /dev/null.
