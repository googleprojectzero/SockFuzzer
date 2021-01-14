/*
 * System call argument to DTrace register array conversion.
 */
#include <sys/systrace_args.h>
void
systrace_args(int sysnum, void *params, uint64_t *uarg)
{
	int64_t *iarg  = (int64_t *) uarg;
	switch (sysnum) {
	/* nosys */
	case 0: {
		break;
	}
	/* exit */
	case 1: {
		struct exit_args *p = params;
		iarg[0] = (int64_t) p->rval; /* int */
		break;
	}
	/* fork */
	case 2: {
		break;
	}
	/* read */
	case 3: {
		struct read_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->cbuf; /* user_addr_t */
		uarg[2] = (uint64_t) p->nbyte; /* user_size_t */
		break;
	}
	/* write */
	case 4: {
		struct write_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->cbuf; /* user_addr_t */
		uarg[2] = (uint64_t) p->nbyte; /* user_size_t */
		break;
	}
	/* open */
	case 5: {
		struct open_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		iarg[1] = (int64_t) p->flags; /* int */
		iarg[2] = (int64_t) p->mode; /* int */
		break;
	}
	/* sys_close */
	case 6: {
		struct close_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		break;
	}
	/* wait4 */
	case 7: {
		struct wait4_args *p = params;
		iarg[0] = (int64_t) p->pid; /* int */
		uarg[1] = (uint64_t) p->status; /* user_addr_t */
		iarg[2] = (int64_t) p->options; /* int */
		uarg[3] = (uint64_t) p->rusage; /* user_addr_t */
		break;
	}
	/* link */
	case 9: {
		struct link_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		uarg[1] = (uint64_t) p->link; /* user_addr_t */
		break;
	}
	/* unlink */
	case 10: {
		struct unlink_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		break;
	}
	/* chdir */
	case 12: {
		struct chdir_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		break;
	}
	/* fchdir */
	case 13: {
		struct fchdir_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		break;
	}
	/* mknod */
	case 14: {
		struct mknod_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		iarg[1] = (int64_t) p->mode; /* int */
		iarg[2] = (int64_t) p->dev; /* int */
		break;
	}
	/* chmod */
	case 15: {
		struct chmod_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		iarg[1] = (int64_t) p->mode; /* int */
		break;
	}
	/* chown */
	case 16: {
		struct chown_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		iarg[1] = (int64_t) p->uid; /* int */
		iarg[2] = (int64_t) p->gid; /* int */
		break;
	}
	/* getfsstat */
	case 18: {
		struct getfsstat_args *p = params;
		uarg[0] = (uint64_t) p->buf; /* user_addr_t */
		iarg[1] = (int64_t) p->bufsize; /* int */
		iarg[2] = (int64_t) p->flags; /* int */
		break;
	}
	/* getpid */
	case 20: {
		break;
	}
	/* setuid */
	case 23: {
		struct setuid_args *p = params;
		uarg[0] = (uint64_t) p->uid; /* uid_t */
		break;
	}
	/* getuid */
	case 24: {
		break;
	}
	/* geteuid */
	case 25: {
		break;
	}
	/* ptrace */
	case 26: {
		struct ptrace_args *p = params;
		iarg[0] = (int64_t) p->req; /* int */
		iarg[1] = (int64_t) p->pid; /* pid_t */
		uarg[2] = (uint64_t) p->addr; /* caddr_t */
		iarg[3] = (int64_t) p->data; /* int */
		break;
	}
#if SOCKETS
	/* recvmsg */
	case 27: {
		struct recvmsg_args *p = params;
		iarg[0] = (int64_t) p->s; /* int */
		uarg[1] = (uint64_t) p->msg; /* struct msghdr * */
		iarg[2] = (int64_t) p->flags; /* int */
		break;
	}
	/* sendmsg */
	case 28: {
		struct sendmsg_args *p = params;
		iarg[0] = (int64_t) p->s; /* int */
		uarg[1] = (uint64_t) p->msg; /* caddr_t */
		iarg[2] = (int64_t) p->flags; /* int */
		break;
	}
	/* recvfrom */
	case 29: {
		struct recvfrom_args *p = params;
		iarg[0] = (int64_t) p->s; /* int */
		uarg[1] = (uint64_t) p->buf; /* void * */
		uarg[2] = (uint64_t) p->len; /* size_t */
		iarg[3] = (int64_t) p->flags; /* int */
		uarg[4] = (uint64_t) p->from; /* struct sockaddr * */
		uarg[5] = (uint64_t) p->fromlenaddr; /* int * */
		break;
	}
	/* accept */
	case 30: {
		struct accept_args *p = params;
		iarg[0] = (int64_t) p->s; /* int */
		uarg[1] = (uint64_t) p->name; /* caddr_t */
		uarg[2] = (uint64_t) p->anamelen; /* socklen_t * */
		break;
	}
	/* getpeername */
	case 31: {
		struct getpeername_args *p = params;
		iarg[0] = (int64_t) p->fdes; /* int */
		uarg[1] = (uint64_t) p->asa; /* caddr_t */
		uarg[2] = (uint64_t) p->alen; /* socklen_t * */
		break;
	}
	/* getsockname */
	case 32: {
		struct getsockname_args *p = params;
		iarg[0] = (int64_t) p->fdes; /* int */
		uarg[1] = (uint64_t) p->asa; /* caddr_t */
		uarg[2] = (uint64_t) p->alen; /* socklen_t * */
		break;
	}
#else
#endif /* SOCKETS */
	/* access */
	case 33: {
		struct access_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		iarg[1] = (int64_t) p->flags; /* int */
		break;
	}
	/* chflags */
	case 34: {
		struct chflags_args *p = params;
		uarg[0] = (uint64_t) p->path; /* char * */
		iarg[1] = (int64_t) p->flags; /* int */
		break;
	}
	/* fchflags */
	case 35: {
		struct fchflags_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		iarg[1] = (int64_t) p->flags; /* int */
		break;
	}
	/* sync */
	case 36: {
		break;
	}
	/* kill */
	case 37: {
		struct kill_args *p = params;
		iarg[0] = (int64_t) p->pid; /* int */
		iarg[1] = (int64_t) p->signum; /* int */
		iarg[2] = (int64_t) p->posix; /* int */
		break;
	}
	/* getppid */
	case 39: {
		break;
	}
	/* sys_dup */
	case 41: {
		struct dup_args *p = params;
		uarg[0] = (uint64_t) p->fd; /* u_int */
		break;
	}
	/* pipe */
	case 42: {
		break;
	}
	/* getegid */
	case 43: {
		break;
	}
	/* sigaction */
	case 46: {
		struct sigaction_args *p = params;
		iarg[0] = (int64_t) p->signum; /* int */
		uarg[1] = (uint64_t) p->nsa; /* struct __sigaction * */
		uarg[2] = (uint64_t) p->osa; /* struct sigaction * */
		break;
	}
	/* getgid */
	case 47: {
		break;
	}
	/* sigprocmask */
	case 48: {
		struct sigprocmask_args *p = params;
		iarg[0] = (int64_t) p->how; /* int */
		uarg[1] = (uint64_t) p->mask; /* user_addr_t */
		uarg[2] = (uint64_t) p->omask; /* user_addr_t */
		break;
	}
	/* getlogin */
	case 49: {
		struct getlogin_args *p = params;
		uarg[0] = (uint64_t) p->namebuf; /* char * */
		uarg[1] = (uint64_t) p->namelen; /* u_int */
		break;
	}
	/* setlogin */
	case 50: {
		struct setlogin_args *p = params;
		uarg[0] = (uint64_t) p->namebuf; /* char * */
		break;
	}
	/* acct */
	case 51: {
		struct acct_args *p = params;
		uarg[0] = (uint64_t) p->path; /* char * */
		break;
	}
	/* sigpending */
	case 52: {
		struct sigpending_args *p = params;
		uarg[0] = (uint64_t) p->osv; /* struct sigvec * */
		break;
	}
	/* sigaltstack */
	case 53: {
		struct sigaltstack_args *p = params;
		uarg[0] = (uint64_t) p->nss; /* struct sigaltstack * */
		uarg[1] = (uint64_t) p->oss; /* struct sigaltstack * */
		break;
	}
	/* ioctl */
	case 54: {
		struct ioctl_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->com; /* u_long */
		uarg[2] = (uint64_t) p->data; /* caddr_t */
		break;
	}
	/* reboot */
	case 55: {
		struct reboot_args *p = params;
		iarg[0] = (int64_t) p->opt; /* int */
		uarg[1] = (uint64_t) p->msg; /* char * */
		break;
	}
	/* revoke */
	case 56: {
		struct revoke_args *p = params;
		uarg[0] = (uint64_t) p->path; /* char * */
		break;
	}
	/* symlink */
	case 57: {
		struct symlink_args *p = params;
		uarg[0] = (uint64_t) p->path; /* char * */
		uarg[1] = (uint64_t) p->link; /* char * */
		break;
	}
	/* readlink */
	case 58: {
		struct readlink_args *p = params;
		uarg[0] = (uint64_t) p->path; /* char * */
		uarg[1] = (uint64_t) p->buf; /* char * */
		iarg[2] = (int64_t) p->count; /* int */
		break;
	}
	/* execve */
	case 59: {
		struct execve_args *p = params;
		uarg[0] = (uint64_t) p->fname; /* char * */
		uarg[1] = (uint64_t) p->argp; /* char ** */
		uarg[2] = (uint64_t) p->envp; /* char ** */
		break;
	}
	/* umask */
	case 60: {
		struct umask_args *p = params;
		iarg[0] = (int64_t) p->newmask; /* int */
		break;
	}
	/* chroot */
	case 61: {
		struct chroot_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		break;
	}
	/* msync */
	case 65: {
		struct msync_args *p = params;
		uarg[0] = (uint64_t) p->addr; /* caddr_t */
		uarg[1] = (uint64_t) p->len; /* size_t */
		iarg[2] = (int64_t) p->flags; /* int */
		break;
	}
	/* vfork */
	case 66: {
		break;
	}
	/* munmap */
	case 73: {
		struct munmap_args *p = params;
		uarg[0] = (uint64_t) p->addr; /* caddr_t */
		uarg[1] = (uint64_t) p->len; /* size_t */
		break;
	}
	/* mprotect */
	case 74: {
		struct mprotect_args *p = params;
		uarg[0] = (uint64_t) p->addr; /* caddr_t */
		uarg[1] = (uint64_t) p->len; /* size_t */
		iarg[2] = (int64_t) p->prot; /* int */
		break;
	}
	/* madvise */
	case 75: {
		struct madvise_args *p = params;
		uarg[0] = (uint64_t) p->addr; /* caddr_t */
		uarg[1] = (uint64_t) p->len; /* size_t */
		iarg[2] = (int64_t) p->behav; /* int */
		break;
	}
	/* mincore */
	case 78: {
		struct mincore_args *p = params;
		uarg[0] = (uint64_t) p->addr; /* user_addr_t */
		uarg[1] = (uint64_t) p->len; /* user_size_t */
		uarg[2] = (uint64_t) p->vec; /* user_addr_t */
		break;
	}
	/* getgroups */
	case 79: {
		struct getgroups_args *p = params;
		uarg[0] = (uint64_t) p->gidsetsize; /* u_int */
		uarg[1] = (uint64_t) p->gidset; /* gid_t * */
		break;
	}
	/* setgroups */
	case 80: {
		struct setgroups_args *p = params;
		uarg[0] = (uint64_t) p->gidsetsize; /* u_int */
		uarg[1] = (uint64_t) p->gidset; /* gid_t * */
		break;
	}
	/* getpgrp */
	case 81: {
		break;
	}
	/* setpgid */
	case 82: {
		struct setpgid_args *p = params;
		iarg[0] = (int64_t) p->pid; /* int */
		iarg[1] = (int64_t) p->pgid; /* int */
		break;
	}
	/* setitimer */
	case 83: {
		struct setitimer_args *p = params;
		uarg[0] = (uint64_t) p->which; /* u_int */
		uarg[1] = (uint64_t) p->itv; /* struct itimerval * */
		uarg[2] = (uint64_t) p->oitv; /* struct itimerval * */
		break;
	}
	/* swapon */
	case 85: {
		break;
	}
	/* getitimer */
	case 86: {
		struct getitimer_args *p = params;
		uarg[0] = (uint64_t) p->which; /* u_int */
		uarg[1] = (uint64_t) p->itv; /* struct itimerval * */
		break;
	}
	/* sys_getdtablesize */
	case 89: {
		break;
	}
	/* sys_dup2 */
	case 90: {
		struct dup2_args *p = params;
		uarg[0] = (uint64_t) p->from; /* u_int */
		uarg[1] = (uint64_t) p->to; /* u_int */
		break;
	}
	/* sys_fcntl */
	case 92: {
		struct fcntl_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		iarg[1] = (int64_t) p->cmd; /* int */
		iarg[2] = (int64_t) p->arg; /* long */
		break;
	}
	/* select */
	case 93: {
		struct select_args *p = params;
		iarg[0] = (int64_t) p->nd; /* int */
		uarg[1] = (uint64_t) p->in; /* u_int32_t * */
		uarg[2] = (uint64_t) p->ou; /* u_int32_t * */
		uarg[3] = (uint64_t) p->ex; /* u_int32_t * */
		uarg[4] = (uint64_t) p->tv; /* struct timeval * */
		break;
	}
	/* fsync */
	case 95: {
		struct fsync_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		break;
	}
	/* setpriority */
	case 96: {
		struct setpriority_args *p = params;
		iarg[0] = (int64_t) p->which; /* int */
		iarg[1] = (int64_t) p->who; /* id_t */
		iarg[2] = (int64_t) p->prio; /* int */
		break;
	}
#if SOCKETS
	/* socket */
	case 97: {
		struct socket_args *p = params;
		iarg[0] = (int64_t) p->domain; /* int */
		iarg[1] = (int64_t) p->type; /* int */
		iarg[2] = (int64_t) p->protocol; /* int */
		break;
	}
	/* connect */
	case 98: {
		struct connect_args *p = params;
		iarg[0] = (int64_t) p->s; /* int */
		uarg[1] = (uint64_t) p->name; /* caddr_t */
		iarg[2] = (int64_t) p->namelen; /* socklen_t */
		break;
	}
#else
#endif /* SOCKETS */
	/* getpriority */
	case 100: {
		struct getpriority_args *p = params;
		iarg[0] = (int64_t) p->which; /* int */
		iarg[1] = (int64_t) p->who; /* id_t */
		break;
	}
#if SOCKETS
	/* bind */
	case 104: {
		struct bind_args *p = params;
		iarg[0] = (int64_t) p->s; /* int */
		uarg[1] = (uint64_t) p->name; /* caddr_t */
		iarg[2] = (int64_t) p->namelen; /* socklen_t */
		break;
	}
	/* setsockopt */
	case 105: {
		struct setsockopt_args *p = params;
		iarg[0] = (int64_t) p->s; /* int */
		iarg[1] = (int64_t) p->level; /* int */
		iarg[2] = (int64_t) p->name; /* int */
		uarg[3] = (uint64_t) p->val; /* caddr_t */
		iarg[4] = (int64_t) p->valsize; /* socklen_t */
		break;
	}
	/* listen */
	case 106: {
		struct listen_args *p = params;
		iarg[0] = (int64_t) p->s; /* int */
		iarg[1] = (int64_t) p->backlog; /* int */
		break;
	}
#else
#endif /* SOCKETS */
	/* sigsuspend */
	case 111: {
		struct sigsuspend_args *p = params;
		iarg[0] = (int64_t) p->mask; /* sigset_t */
		break;
	}
#if SOCKETS
#else
#endif /* SOCKETS */
	/* gettimeofday */
	case 116: {
		struct gettimeofday_args *p = params;
		uarg[0] = (uint64_t) p->tp; /* struct timeval * */
		uarg[1] = (uint64_t) p->tzp; /* struct timezone * */
		uarg[2] = (uint64_t) p->mach_absolute_time; /* uint64_t * */
		break;
	}
	/* getrusage */
	case 117: {
		struct getrusage_args *p = params;
		iarg[0] = (int64_t) p->who; /* int */
		uarg[1] = (uint64_t) p->rusage; /* struct rusage * */
		break;
	}
#if SOCKETS
	/* getsockopt */
	case 118: {
		struct getsockopt_args *p = params;
		iarg[0] = (int64_t) p->s; /* int */
		iarg[1] = (int64_t) p->level; /* int */
		iarg[2] = (int64_t) p->name; /* int */
		uarg[3] = (uint64_t) p->val; /* caddr_t */
		uarg[4] = (uint64_t) p->avalsize; /* socklen_t * */
		break;
	}
#else
#endif /* SOCKETS */
	/* readv */
	case 120: {
		struct readv_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->iovp; /* struct iovec * */
		uarg[2] = (uint64_t) p->iovcnt; /* u_int */
		break;
	}
	/* writev */
	case 121: {
		struct writev_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->iovp; /* struct iovec * */
		uarg[2] = (uint64_t) p->iovcnt; /* u_int */
		break;
	}
	/* settimeofday */
	case 122: {
		struct settimeofday_args *p = params;
		uarg[0] = (uint64_t) p->tv; /* struct timeval * */
		uarg[1] = (uint64_t) p->tzp; /* struct timezone * */
		break;
	}
	/* fchown */
	case 123: {
		struct fchown_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		iarg[1] = (int64_t) p->uid; /* int */
		iarg[2] = (int64_t) p->gid; /* int */
		break;
	}
	/* fchmod */
	case 124: {
		struct fchmod_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		iarg[1] = (int64_t) p->mode; /* int */
		break;
	}
	/* setreuid */
	case 126: {
		struct setreuid_args *p = params;
		uarg[0] = (uint64_t) p->ruid; /* uid_t */
		uarg[1] = (uint64_t) p->euid; /* uid_t */
		break;
	}
	/* setregid */
	case 127: {
		struct setregid_args *p = params;
		iarg[0] = (int64_t) p->rgid; /* gid_t */
		iarg[1] = (int64_t) p->egid; /* gid_t */
		break;
	}
	/* rename */
	case 128: {
		struct rename_args *p = params;
		uarg[0] = (uint64_t) p->from; /* char * */
		uarg[1] = (uint64_t) p->to; /* char * */
		break;
	}
	/* sys_flock */
	case 131: {
		struct flock_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		iarg[1] = (int64_t) p->how; /* int */
		break;
	}
	/* mkfifo */
	case 132: {
		struct mkfifo_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		iarg[1] = (int64_t) p->mode; /* int */
		break;
	}
#if SOCKETS
	/* sendto */
	case 133: {
		struct sendto_args *p = params;
		iarg[0] = (int64_t) p->s; /* int */
		uarg[1] = (uint64_t) p->buf; /* caddr_t */
		uarg[2] = (uint64_t) p->len; /* size_t */
		iarg[3] = (int64_t) p->flags; /* int */
		uarg[4] = (uint64_t) p->to; /* caddr_t */
		iarg[5] = (int64_t) p->tolen; /* socklen_t */
		break;
	}
	/* shutdown */
	case 134: {
		struct shutdown_args *p = params;
		iarg[0] = (int64_t) p->s; /* int */
		iarg[1] = (int64_t) p->how; /* int */
		break;
	}
	/* socketpair */
	case 135: {
		struct socketpair_args *p = params;
		iarg[0] = (int64_t) p->domain; /* int */
		iarg[1] = (int64_t) p->type; /* int */
		iarg[2] = (int64_t) p->protocol; /* int */
		uarg[3] = (uint64_t) p->rsv; /* int * */
		break;
	}
#else
#endif /* SOCKETS */
	/* mkdir */
	case 136: {
		struct mkdir_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		iarg[1] = (int64_t) p->mode; /* int */
		break;
	}
	/* rmdir */
	case 137: {
		struct rmdir_args *p = params;
		uarg[0] = (uint64_t) p->path; /* char * */
		break;
	}
	/* utimes */
	case 138: {
		struct utimes_args *p = params;
		uarg[0] = (uint64_t) p->path; /* char * */
		uarg[1] = (uint64_t) p->tptr; /* struct timeval * */
		break;
	}
	/* futimes */
	case 139: {
		struct futimes_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->tptr; /* struct timeval * */
		break;
	}
	/* adjtime */
	case 140: {
		struct adjtime_args *p = params;
		uarg[0] = (uint64_t) p->delta; /* struct timeval * */
		uarg[1] = (uint64_t) p->olddelta; /* struct timeval * */
		break;
	}
	/* gethostuuid */
	case 142: {
		struct gethostuuid_args *p = params;
		uarg[0] = (uint64_t) p->uuid_buf; /* unsigned char * */
		uarg[1] = (uint64_t) p->timeoutp; /* const struct timespec * */
		break;
	}
	/* setsid */
	case 147: {
		break;
	}
	/* getpgid */
	case 151: {
		struct getpgid_args *p = params;
		iarg[0] = (int64_t) p->pid; /* pid_t */
		break;
	}
	/* setprivexec */
	case 152: {
		struct setprivexec_args *p = params;
		iarg[0] = (int64_t) p->flag; /* int */
		break;
	}
	/* pread */
	case 153: {
		struct pread_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->buf; /* user_addr_t */
		uarg[2] = (uint64_t) p->nbyte; /* user_size_t */
		iarg[3] = (int64_t) p->offset; /* off_t */
		break;
	}
	/* pwrite */
	case 154: {
		struct pwrite_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->buf; /* user_addr_t */
		uarg[2] = (uint64_t) p->nbyte; /* user_size_t */
		iarg[3] = (int64_t) p->offset; /* off_t */
		break;
	}
#if NFSSERVER	/* XXX */
	/* nfssvc */
	case 155: {
		struct nfssvc_args *p = params;
		iarg[0] = (int64_t) p->flag; /* int */
		uarg[1] = (uint64_t) p->argp; /* caddr_t */
		break;
	}
#else
#endif
	/* statfs */
	case 157: {
		struct statfs_args *p = params;
		uarg[0] = (uint64_t) p->path; /* char * */
		uarg[1] = (uint64_t) p->buf; /* struct statfs * */
		break;
	}
	/* fstatfs */
	case 158: {
		struct fstatfs_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->buf; /* struct statfs * */
		break;
	}
	/* unmount */
	case 159: {
		struct unmount_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		iarg[1] = (int64_t) p->flags; /* int */
		break;
	}
#if NFSSERVER	/* XXX */
	/* getfh */
	case 161: {
		struct getfh_args *p = params;
		uarg[0] = (uint64_t) p->fname; /* char * */
		uarg[1] = (uint64_t) p->fhp; /* fhandle_t * */
		break;
	}
#else
#endif
	/* quotactl */
	case 165: {
		struct quotactl_args *p = params;
		uarg[0] = (uint64_t) p->path; /* const char * */
		iarg[1] = (int64_t) p->cmd; /* int */
		iarg[2] = (int64_t) p->uid; /* int */
		uarg[3] = (uint64_t) p->arg; /* caddr_t */
		break;
	}
	/* mount */
	case 167: {
		struct mount_args *p = params;
		uarg[0] = (uint64_t) p->type; /* char * */
		uarg[1] = (uint64_t) p->path; /* char * */
		iarg[2] = (int64_t) p->flags; /* int */
		uarg[3] = (uint64_t) p->data; /* caddr_t */
		break;
	}
	/* csops */
	case 169: {
		struct csops_args *p = params;
		iarg[0] = (int64_t) p->pid; /* pid_t */
		uarg[1] = (uint64_t) p->ops; /* uint32_t */
		uarg[2] = (uint64_t) p->useraddr; /* user_addr_t */
		uarg[3] = (uint64_t) p->usersize; /* user_size_t */
		break;
	}
	/* csops_audittoken */
	case 170: {
		struct csops_audittoken_args *p = params;
		iarg[0] = (int64_t) p->pid; /* pid_t */
		uarg[1] = (uint64_t) p->ops; /* uint32_t */
		uarg[2] = (uint64_t) p->useraddr; /* user_addr_t */
		uarg[3] = (uint64_t) p->usersize; /* user_size_t */
		uarg[4] = (uint64_t) p->uaudittoken; /* user_addr_t */
		break;
	}
	/* waitid */
	case 173: {
		struct waitid_args *p = params;
		iarg[0] = (int64_t) p->idtype; /* idtype_t */
		iarg[1] = (int64_t) p->id; /* id_t */
		uarg[2] = (uint64_t) p->infop; /* siginfo_t * */
		iarg[3] = (int64_t) p->options; /* int */
		break;
	}
	/* kdebug_typefilter */
	case 177: {
		struct kdebug_typefilter_args *p = params;
		uarg[0] = (uint64_t) p->addr; /* void ** */
		uarg[1] = (uint64_t) p->size; /* size_t * */
		break;
	}
	/* kdebug_trace_string */
	case 178: {
		struct kdebug_trace_string_args *p = params;
		uarg[0] = (uint64_t) p->debugid; /* uint32_t */
		uarg[1] = (uint64_t) p->str_id; /* uint64_t */
		uarg[2] = (uint64_t) p->str; /* const char * */
		break;
	}
	/* kdebug_trace64 */
	case 179: {
		struct kdebug_trace64_args *p = params;
		uarg[0] = (uint64_t) p->code; /* uint32_t */
		uarg[1] = (uint64_t) p->arg1; /* uint64_t */
		uarg[2] = (uint64_t) p->arg2; /* uint64_t */
		uarg[3] = (uint64_t) p->arg3; /* uint64_t */
		uarg[4] = (uint64_t) p->arg4; /* uint64_t */
		break;
	}
	/* kdebug_trace */
	case 180: {
		struct kdebug_trace_args *p = params;
		uarg[0] = (uint64_t) p->code; /* uint32_t */
		uarg[1] = (uint64_t) p->arg1; /* u_long */
		uarg[2] = (uint64_t) p->arg2; /* u_long */
		uarg[3] = (uint64_t) p->arg3; /* u_long */
		uarg[4] = (uint64_t) p->arg4; /* u_long */
		break;
	}
	/* setgid */
	case 181: {
		struct setgid_args *p = params;
		iarg[0] = (int64_t) p->gid; /* gid_t */
		break;
	}
	/* setegid */
	case 182: {
		struct setegid_args *p = params;
		iarg[0] = (int64_t) p->egid; /* gid_t */
		break;
	}
	/* seteuid */
	case 183: {
		struct seteuid_args *p = params;
		uarg[0] = (uint64_t) p->euid; /* uid_t */
		break;
	}
	/* sigreturn */
	case 184: {
		struct sigreturn_args *p = params;
		uarg[0] = (uint64_t) p->uctx; /* struct ucontext * */
		iarg[1] = (int64_t) p->infostyle; /* int */
		uarg[2] = (uint64_t) p->token; /* user_addr_t */
		break;
	}
	/* thread_selfcounts */
	case 186: {
		struct thread_selfcounts_args *p = params;
		iarg[0] = (int64_t) p->type; /* int */
		uarg[1] = (uint64_t) p->buf; /* user_addr_t */
		uarg[2] = (uint64_t) p->nbytes; /* user_size_t */
		break;
	}
	/* fdatasync */
	case 187: {
		struct fdatasync_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		break;
	}
	/* stat */
	case 188: {
		struct stat_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		uarg[1] = (uint64_t) p->ub; /* user_addr_t */
		break;
	}
	/* sys_fstat */
	case 189: {
		struct fstat_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->ub; /* user_addr_t */
		break;
	}
	/* lstat */
	case 190: {
		struct lstat_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		uarg[1] = (uint64_t) p->ub; /* user_addr_t */
		break;
	}
	/* pathconf */
	case 191: {
		struct pathconf_args *p = params;
		uarg[0] = (uint64_t) p->path; /* char * */
		iarg[1] = (int64_t) p->name; /* int */
		break;
	}
	/* sys_fpathconf */
	case 192: {
		struct fpathconf_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		iarg[1] = (int64_t) p->name; /* int */
		break;
	}
	/* getrlimit */
	case 194: {
		struct getrlimit_args *p = params;
		uarg[0] = (uint64_t) p->which; /* u_int */
		uarg[1] = (uint64_t) p->rlp; /* struct rlimit * */
		break;
	}
	/* setrlimit */
	case 195: {
		struct setrlimit_args *p = params;
		uarg[0] = (uint64_t) p->which; /* u_int */
		uarg[1] = (uint64_t) p->rlp; /* struct rlimit * */
		break;
	}
	/* getdirentries */
	case 196: {
		struct getdirentries_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->buf; /* char * */
		uarg[2] = (uint64_t) p->count; /* u_int */
		uarg[3] = (uint64_t) p->basep; /* long * */
		break;
	}
	/* mmap */
	case 197: {
		struct mmap_args *p = params;
		uarg[0] = (uint64_t) p->addr; /* caddr_t */
		uarg[1] = (uint64_t) p->len; /* size_t */
		iarg[2] = (int64_t) p->prot; /* int */
		iarg[3] = (int64_t) p->flags; /* int */
		iarg[4] = (int64_t) p->fd; /* int */
		iarg[5] = (int64_t) p->pos; /* off_t */
		break;
	}
	/* lseek */
	case 199: {
		struct lseek_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		iarg[1] = (int64_t) p->offset; /* off_t */
		iarg[2] = (int64_t) p->whence; /* int */
		break;
	}
	/* truncate */
	case 200: {
		struct truncate_args *p = params;
		uarg[0] = (uint64_t) p->path; /* char * */
		iarg[1] = (int64_t) p->length; /* off_t */
		break;
	}
	/* ftruncate */
	case 201: {
		struct ftruncate_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		iarg[1] = (int64_t) p->length; /* off_t */
		break;
	}
	/* sysctl */
	case 202: {
		struct sysctl_args *p = params;
		uarg[0] = (uint64_t) p->name; /* int * */
		uarg[1] = (uint64_t) p->namelen; /* u_int */
		uarg[2] = (uint64_t) p->old; /* void * */
		uarg[3] = (uint64_t) p->oldlenp; /* size_t * */
		uarg[4] = (uint64_t) p->new; /* void * */
		uarg[5] = (uint64_t) p->newlen; /* size_t */
		break;
	}
	/* mlock */
	case 203: {
		struct mlock_args *p = params;
		uarg[0] = (uint64_t) p->addr; /* caddr_t */
		uarg[1] = (uint64_t) p->len; /* size_t */
		break;
	}
	/* munlock */
	case 204: {
		struct munlock_args *p = params;
		uarg[0] = (uint64_t) p->addr; /* caddr_t */
		uarg[1] = (uint64_t) p->len; /* size_t */
		break;
	}
	/* undelete */
	case 205: {
		struct undelete_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		break;
	}
	/* open_dprotected_np */
	case 216: {
		struct open_dprotected_np_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		iarg[1] = (int64_t) p->flags; /* int */
		iarg[2] = (int64_t) p->class; /* int */
		iarg[3] = (int64_t) p->dpflags; /* int */
		iarg[4] = (int64_t) p->mode; /* int */
		break;
	}
	/* fsgetpath_ext */
	case 217: {
		struct fsgetpath_ext_args *p = params;
		uarg[0] = (uint64_t) p->buf; /* user_addr_t */
		uarg[1] = (uint64_t) p->bufsize; /* size_t */
		uarg[2] = (uint64_t) p->fsid; /* user_addr_t */
		uarg[3] = (uint64_t) p->objid; /* uint64_t */
		uarg[4] = (uint64_t) p->options; /* uint32_t */
		break;
	}
	/* getattrlist */
	case 220: {
		struct getattrlist_args *p = params;
		uarg[0] = (uint64_t) p->path; /* const char * */
		uarg[1] = (uint64_t) p->alist; /* struct attrlist * */
		uarg[2] = (uint64_t) p->attributeBuffer; /* void * */
		uarg[3] = (uint64_t) p->bufferSize; /* size_t */
		uarg[4] = (uint64_t) p->options; /* u_long */
		break;
	}
	/* setattrlist */
	case 221: {
		struct setattrlist_args *p = params;
		uarg[0] = (uint64_t) p->path; /* const char * */
		uarg[1] = (uint64_t) p->alist; /* struct attrlist * */
		uarg[2] = (uint64_t) p->attributeBuffer; /* void * */
		uarg[3] = (uint64_t) p->bufferSize; /* size_t */
		uarg[4] = (uint64_t) p->options; /* u_long */
		break;
	}
	/* getdirentriesattr */
	case 222: {
		struct getdirentriesattr_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->alist; /* struct attrlist * */
		uarg[2] = (uint64_t) p->buffer; /* void * */
		uarg[3] = (uint64_t) p->buffersize; /* size_t */
		uarg[4] = (uint64_t) p->count; /* u_long * */
		uarg[5] = (uint64_t) p->basep; /* u_long * */
		uarg[6] = (uint64_t) p->newstate; /* u_long * */
		uarg[7] = (uint64_t) p->options; /* u_long */
		break;
	}
	/* exchangedata */
	case 223: {
		struct exchangedata_args *p = params;
		uarg[0] = (uint64_t) p->path1; /* const char * */
		uarg[1] = (uint64_t) p->path2; /* const char * */
		uarg[2] = (uint64_t) p->options; /* u_long */
		break;
	}
	/* searchfs */
	case 225: {
		struct searchfs_args *p = params;
		uarg[0] = (uint64_t) p->path; /* const char * */
		uarg[1] = (uint64_t) p->searchblock; /* struct fssearchblock * */
		uarg[2] = (uint64_t) p->nummatches; /* uint32_t * */
		uarg[3] = (uint64_t) p->scriptcode; /* uint32_t */
		uarg[4] = (uint64_t) p->options; /* uint32_t */
		uarg[5] = (uint64_t) p->state; /* struct searchstate * */
		break;
	}
	/* delete */
	case 226: {
		struct delete_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		break;
	}
	/* copyfile */
	case 227: {
		struct copyfile_args *p = params;
		uarg[0] = (uint64_t) p->from; /* char * */
		uarg[1] = (uint64_t) p->to; /* char * */
		iarg[2] = (int64_t) p->mode; /* int */
		iarg[3] = (int64_t) p->flags; /* int */
		break;
	}
	/* fgetattrlist */
	case 228: {
		struct fgetattrlist_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->alist; /* struct attrlist * */
		uarg[2] = (uint64_t) p->attributeBuffer; /* void * */
		uarg[3] = (uint64_t) p->bufferSize; /* size_t */
		uarg[4] = (uint64_t) p->options; /* u_long */
		break;
	}
	/* fsetattrlist */
	case 229: {
		struct fsetattrlist_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->alist; /* struct attrlist * */
		uarg[2] = (uint64_t) p->attributeBuffer; /* void * */
		uarg[3] = (uint64_t) p->bufferSize; /* size_t */
		uarg[4] = (uint64_t) p->options; /* u_long */
		break;
	}
	/* poll */
	case 230: {
		struct poll_args *p = params;
		uarg[0] = (uint64_t) p->fds; /* struct pollfd * */
		uarg[1] = (uint64_t) p->nfds; /* u_int */
		iarg[2] = (int64_t) p->timeout; /* int */
		break;
	}
	/* getxattr */
	case 234: {
		struct getxattr_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		uarg[1] = (uint64_t) p->attrname; /* user_addr_t */
		uarg[2] = (uint64_t) p->value; /* user_addr_t */
		uarg[3] = (uint64_t) p->size; /* size_t */
		uarg[4] = (uint64_t) p->position; /* uint32_t */
		iarg[5] = (int64_t) p->options; /* int */
		break;
	}
	/* fgetxattr */
	case 235: {
		struct fgetxattr_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->attrname; /* user_addr_t */
		uarg[2] = (uint64_t) p->value; /* user_addr_t */
		uarg[3] = (uint64_t) p->size; /* size_t */
		uarg[4] = (uint64_t) p->position; /* uint32_t */
		iarg[5] = (int64_t) p->options; /* int */
		break;
	}
	/* setxattr */
	case 236: {
		struct setxattr_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		uarg[1] = (uint64_t) p->attrname; /* user_addr_t */
		uarg[2] = (uint64_t) p->value; /* user_addr_t */
		uarg[3] = (uint64_t) p->size; /* size_t */
		uarg[4] = (uint64_t) p->position; /* uint32_t */
		iarg[5] = (int64_t) p->options; /* int */
		break;
	}
	/* fsetxattr */
	case 237: {
		struct fsetxattr_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->attrname; /* user_addr_t */
		uarg[2] = (uint64_t) p->value; /* user_addr_t */
		uarg[3] = (uint64_t) p->size; /* size_t */
		uarg[4] = (uint64_t) p->position; /* uint32_t */
		iarg[5] = (int64_t) p->options; /* int */
		break;
	}
	/* removexattr */
	case 238: {
		struct removexattr_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		uarg[1] = (uint64_t) p->attrname; /* user_addr_t */
		iarg[2] = (int64_t) p->options; /* int */
		break;
	}
	/* fremovexattr */
	case 239: {
		struct fremovexattr_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->attrname; /* user_addr_t */
		iarg[2] = (int64_t) p->options; /* int */
		break;
	}
	/* listxattr */
	case 240: {
		struct listxattr_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		uarg[1] = (uint64_t) p->namebuf; /* user_addr_t */
		uarg[2] = (uint64_t) p->bufsize; /* size_t */
		iarg[3] = (int64_t) p->options; /* int */
		break;
	}
	/* flistxattr */
	case 241: {
		struct flistxattr_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->namebuf; /* user_addr_t */
		uarg[2] = (uint64_t) p->bufsize; /* size_t */
		iarg[3] = (int64_t) p->options; /* int */
		break;
	}
	/* fsctl */
	case 242: {
		struct fsctl_args *p = params;
		uarg[0] = (uint64_t) p->path; /* const char * */
		uarg[1] = (uint64_t) p->cmd; /* u_long */
		uarg[2] = (uint64_t) p->data; /* caddr_t */
		uarg[3] = (uint64_t) p->options; /* u_int */
		break;
	}
	/* initgroups */
	case 243: {
		struct initgroups_args *p = params;
		uarg[0] = (uint64_t) p->gidsetsize; /* u_int */
		uarg[1] = (uint64_t) p->gidset; /* gid_t * */
		iarg[2] = (int64_t) p->gmuid; /* int */
		break;
	}
	/* posix_spawn */
	case 244: {
		struct posix_spawn_args *p = params;
		uarg[0] = (uint64_t) p->pid; /* pid_t * */
		uarg[1] = (uint64_t) p->path; /* const char * */
		uarg[2] = (uint64_t) p->adesc; /* const struct _posix_spawn_args_desc * */
		uarg[3] = (uint64_t) p->argv; /* char ** */
		uarg[4] = (uint64_t) p->envp; /* char ** */
		break;
	}
	/* ffsctl */
	case 245: {
		struct ffsctl_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->cmd; /* u_long */
		uarg[2] = (uint64_t) p->data; /* caddr_t */
		uarg[3] = (uint64_t) p->options; /* u_int */
		break;
	}
#if NFSCLIENT	/* XXX */
	/* nfsclnt */
	case 247: {
		struct nfsclnt_args *p = params;
		iarg[0] = (int64_t) p->flag; /* int */
		uarg[1] = (uint64_t) p->argp; /* caddr_t */
		break;
	}
#else
#endif
#if NFSSERVER	/* XXX */
	/* fhopen */
	case 248: {
		struct fhopen_args *p = params;
		uarg[0] = (uint64_t) p->u_fhp; /* const struct fhandle * */
		iarg[1] = (int64_t) p->flags; /* int */
		break;
	}
#else
#endif
	/* minherit */
	case 250: {
		struct minherit_args *p = params;
		uarg[0] = (uint64_t) p->addr; /* void * */
		uarg[1] = (uint64_t) p->len; /* size_t */
		iarg[2] = (int64_t) p->inherit; /* int */
		break;
	}
#if SYSV_SEM
	/* semsys */
	case 251: {
		struct semsys_args *p = params;
		uarg[0] = (uint64_t) p->which; /* u_int */
		iarg[1] = (int64_t) p->a2; /* int */
		iarg[2] = (int64_t) p->a3; /* int */
		iarg[3] = (int64_t) p->a4; /* int */
		iarg[4] = (int64_t) p->a5; /* int */
		break;
	}
#else
#endif
#if SYSV_MSG
	/* msgsys */
	case 252: {
		struct msgsys_args *p = params;
		uarg[0] = (uint64_t) p->which; /* u_int */
		iarg[1] = (int64_t) p->a2; /* int */
		iarg[2] = (int64_t) p->a3; /* int */
		iarg[3] = (int64_t) p->a4; /* int */
		iarg[4] = (int64_t) p->a5; /* int */
		break;
	}
#else
#endif
#if SYSV_SHM
	/* shmsys */
	case 253: {
		struct shmsys_args *p = params;
		uarg[0] = (uint64_t) p->which; /* u_int */
		iarg[1] = (int64_t) p->a2; /* int */
		iarg[2] = (int64_t) p->a3; /* int */
		iarg[3] = (int64_t) p->a4; /* int */
		break;
	}
#else
#endif
#if SYSV_SEM
	/* semctl */
	case 254: {
		struct semctl_args *p = params;
		iarg[0] = (int64_t) p->semid; /* int */
		iarg[1] = (int64_t) p->semnum; /* int */
		iarg[2] = (int64_t) p->cmd; /* int */
		iarg[3] = (int64_t) p->arg; /* semun_t */
		break;
	}
	/* semget */
	case 255: {
		struct semget_args *p = params;
		iarg[0] = (int64_t) p->key; /* key_t */
		iarg[1] = (int64_t) p->nsems; /* int */
		iarg[2] = (int64_t) p->semflg; /* int */
		break;
	}
	/* semop */
	case 256: {
		struct semop_args *p = params;
		iarg[0] = (int64_t) p->semid; /* int */
		uarg[1] = (uint64_t) p->sops; /* struct sembuf * */
		iarg[2] = (int64_t) p->nsops; /* int */
		break;
	}
#else
#endif
#if SYSV_MSG
	/* msgctl */
	case 258: {
		struct msgctl_args *p = params;
		iarg[0] = (int64_t) p->msqid; /* int */
		iarg[1] = (int64_t) p->cmd; /* int */
		uarg[2] = (uint64_t) p->buf; /* struct msqid_ds * */
		break;
	}
	/* msgget */
	case 259: {
		struct msgget_args *p = params;
		iarg[0] = (int64_t) p->key; /* key_t */
		iarg[1] = (int64_t) p->msgflg; /* int */
		break;
	}
	/* msgsnd */
	case 260: {
		struct msgsnd_args *p = params;
		iarg[0] = (int64_t) p->msqid; /* int */
		uarg[1] = (uint64_t) p->msgp; /* void * */
		uarg[2] = (uint64_t) p->msgsz; /* size_t */
		iarg[3] = (int64_t) p->msgflg; /* int */
		break;
	}
	/* msgrcv */
	case 261: {
		struct msgrcv_args *p = params;
		iarg[0] = (int64_t) p->msqid; /* int */
		uarg[1] = (uint64_t) p->msgp; /* void * */
		uarg[2] = (uint64_t) p->msgsz; /* size_t */
		iarg[3] = (int64_t) p->msgtyp; /* long */
		iarg[4] = (int64_t) p->msgflg; /* int */
		break;
	}
#else
#endif
#if SYSV_SHM
	/* shmat */
	case 262: {
		struct shmat_args *p = params;
		iarg[0] = (int64_t) p->shmid; /* int */
		uarg[1] = (uint64_t) p->shmaddr; /* void * */
		iarg[2] = (int64_t) p->shmflg; /* int */
		break;
	}
	/* shmctl */
	case 263: {
		struct shmctl_args *p = params;
		iarg[0] = (int64_t) p->shmid; /* int */
		iarg[1] = (int64_t) p->cmd; /* int */
		uarg[2] = (uint64_t) p->buf; /* struct shmid_ds * */
		break;
	}
	/* shmdt */
	case 264: {
		struct shmdt_args *p = params;
		uarg[0] = (uint64_t) p->shmaddr; /* void * */
		break;
	}
	/* shmget */
	case 265: {
		struct shmget_args *p = params;
		iarg[0] = (int64_t) p->key; /* key_t */
		uarg[1] = (uint64_t) p->size; /* size_t */
		iarg[2] = (int64_t) p->shmflg; /* int */
		break;
	}
#else
#endif
	/* shm_open */
	case 266: {
		struct shm_open_args *p = params;
		uarg[0] = (uint64_t) p->name; /* const char * */
		iarg[1] = (int64_t) p->oflag; /* int */
		iarg[2] = (int64_t) p->mode; /* int */
		break;
	}
	/* shm_unlink */
	case 267: {
		struct shm_unlink_args *p = params;
		uarg[0] = (uint64_t) p->name; /* const char * */
		break;
	}
	/* sem_open */
	case 268: {
		struct sem_open_args *p = params;
		uarg[0] = (uint64_t) p->name; /* const char * */
		iarg[1] = (int64_t) p->oflag; /* int */
		iarg[2] = (int64_t) p->mode; /* int */
		iarg[3] = (int64_t) p->value; /* int */
		break;
	}
	/* sem_close */
	case 269: {
		struct sem_close_args *p = params;
		uarg[0] = (uint64_t) p->sem; /* sem_t * */
		break;
	}
	/* sem_unlink */
	case 270: {
		struct sem_unlink_args *p = params;
		uarg[0] = (uint64_t) p->name; /* const char * */
		break;
	}
	/* sem_wait */
	case 271: {
		struct sem_wait_args *p = params;
		uarg[0] = (uint64_t) p->sem; /* sem_t * */
		break;
	}
	/* sem_trywait */
	case 272: {
		struct sem_trywait_args *p = params;
		uarg[0] = (uint64_t) p->sem; /* sem_t * */
		break;
	}
	/* sem_post */
	case 273: {
		struct sem_post_args *p = params;
		uarg[0] = (uint64_t) p->sem; /* sem_t * */
		break;
	}
	/* sys_sysctlbyname */
	case 274: {
		struct sysctlbyname_args *p = params;
		uarg[0] = (uint64_t) p->name; /* const char * */
		uarg[1] = (uint64_t) p->namelen; /* size_t */
		uarg[2] = (uint64_t) p->old; /* void * */
		uarg[3] = (uint64_t) p->oldlenp; /* size_t * */
		uarg[4] = (uint64_t) p->new; /* void * */
		uarg[5] = (uint64_t) p->newlen; /* size_t */
		break;
	}
	/* open_extended */
	case 277: {
		struct open_extended_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		iarg[1] = (int64_t) p->flags; /* int */
		uarg[2] = (uint64_t) p->uid; /* uid_t */
		iarg[3] = (int64_t) p->gid; /* gid_t */
		iarg[4] = (int64_t) p->mode; /* int */
		uarg[5] = (uint64_t) p->xsecurity; /* user_addr_t */
		break;
	}
	/* umask_extended */
	case 278: {
		struct umask_extended_args *p = params;
		iarg[0] = (int64_t) p->newmask; /* int */
		uarg[1] = (uint64_t) p->xsecurity; /* user_addr_t */
		break;
	}
	/* stat_extended */
	case 279: {
		struct stat_extended_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		uarg[1] = (uint64_t) p->ub; /* user_addr_t */
		uarg[2] = (uint64_t) p->xsecurity; /* user_addr_t */
		uarg[3] = (uint64_t) p->xsecurity_size; /* user_addr_t */
		break;
	}
	/* lstat_extended */
	case 280: {
		struct lstat_extended_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		uarg[1] = (uint64_t) p->ub; /* user_addr_t */
		uarg[2] = (uint64_t) p->xsecurity; /* user_addr_t */
		uarg[3] = (uint64_t) p->xsecurity_size; /* user_addr_t */
		break;
	}
	/* sys_fstat_extended */
	case 281: {
		struct fstat_extended_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->ub; /* user_addr_t */
		uarg[2] = (uint64_t) p->xsecurity; /* user_addr_t */
		uarg[3] = (uint64_t) p->xsecurity_size; /* user_addr_t */
		break;
	}
	/* chmod_extended */
	case 282: {
		struct chmod_extended_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		uarg[1] = (uint64_t) p->uid; /* uid_t */
		iarg[2] = (int64_t) p->gid; /* gid_t */
		iarg[3] = (int64_t) p->mode; /* int */
		uarg[4] = (uint64_t) p->xsecurity; /* user_addr_t */
		break;
	}
	/* fchmod_extended */
	case 283: {
		struct fchmod_extended_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->uid; /* uid_t */
		iarg[2] = (int64_t) p->gid; /* gid_t */
		iarg[3] = (int64_t) p->mode; /* int */
		uarg[4] = (uint64_t) p->xsecurity; /* user_addr_t */
		break;
	}
	/* access_extended */
	case 284: {
		struct access_extended_args *p = params;
		uarg[0] = (uint64_t) p->entries; /* user_addr_t */
		uarg[1] = (uint64_t) p->size; /* size_t */
		uarg[2] = (uint64_t) p->results; /* user_addr_t */
		uarg[3] = (uint64_t) p->uid; /* uid_t */
		break;
	}
	/* settid */
	case 285: {
		struct settid_args *p = params;
		uarg[0] = (uint64_t) p->uid; /* uid_t */
		iarg[1] = (int64_t) p->gid; /* gid_t */
		break;
	}
	/* gettid */
	case 286: {
		struct gettid_args *p = params;
		uarg[0] = (uint64_t) p->uidp; /* uid_t * */
		uarg[1] = (uint64_t) p->gidp; /* gid_t * */
		break;
	}
	/* setsgroups */
	case 287: {
		struct setsgroups_args *p = params;
		iarg[0] = (int64_t) p->setlen; /* int */
		uarg[1] = (uint64_t) p->guidset; /* user_addr_t */
		break;
	}
	/* getsgroups */
	case 288: {
		struct getsgroups_args *p = params;
		uarg[0] = (uint64_t) p->setlen; /* user_addr_t */
		uarg[1] = (uint64_t) p->guidset; /* user_addr_t */
		break;
	}
	/* setwgroups */
	case 289: {
		struct setwgroups_args *p = params;
		iarg[0] = (int64_t) p->setlen; /* int */
		uarg[1] = (uint64_t) p->guidset; /* user_addr_t */
		break;
	}
	/* getwgroups */
	case 290: {
		struct getwgroups_args *p = params;
		uarg[0] = (uint64_t) p->setlen; /* user_addr_t */
		uarg[1] = (uint64_t) p->guidset; /* user_addr_t */
		break;
	}
	/* mkfifo_extended */
	case 291: {
		struct mkfifo_extended_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		uarg[1] = (uint64_t) p->uid; /* uid_t */
		iarg[2] = (int64_t) p->gid; /* gid_t */
		iarg[3] = (int64_t) p->mode; /* int */
		uarg[4] = (uint64_t) p->xsecurity; /* user_addr_t */
		break;
	}
	/* mkdir_extended */
	case 292: {
		struct mkdir_extended_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		uarg[1] = (uint64_t) p->uid; /* uid_t */
		iarg[2] = (int64_t) p->gid; /* gid_t */
		iarg[3] = (int64_t) p->mode; /* int */
		uarg[4] = (uint64_t) p->xsecurity; /* user_addr_t */
		break;
	}
#if CONFIG_EXT_RESOLVER
	/* identitysvc */
	case 293: {
		struct identitysvc_args *p = params;
		iarg[0] = (int64_t) p->opcode; /* int */
		uarg[1] = (uint64_t) p->message; /* user_addr_t */
		break;
	}
#else
#endif
	/* shared_region_check_np */
	case 294: {
		struct shared_region_check_np_args *p = params;
		uarg[0] = (uint64_t) p->start_address; /* uint64_t * */
		break;
	}
	/* vm_pressure_monitor */
	case 296: {
		struct vm_pressure_monitor_args *p = params;
		iarg[0] = (int64_t) p->wait_for_pressure; /* int */
		iarg[1] = (int64_t) p->nsecs_monitored; /* int */
		uarg[2] = (uint64_t) p->pages_reclaimed; /* uint32_t * */
		break;
	}
#if PSYNCH
	/* psynch_rw_longrdlock */
	case 297: {
		struct psynch_rw_longrdlock_args *p = params;
		uarg[0] = (uint64_t) p->rwlock; /* user_addr_t */
		uarg[1] = (uint64_t) p->lgenval; /* uint32_t */
		uarg[2] = (uint64_t) p->ugenval; /* uint32_t */
		uarg[3] = (uint64_t) p->rw_wc; /* uint32_t */
		iarg[4] = (int64_t) p->flags; /* int */
		break;
	}
	/* psynch_rw_yieldwrlock */
	case 298: {
		struct psynch_rw_yieldwrlock_args *p = params;
		uarg[0] = (uint64_t) p->rwlock; /* user_addr_t */
		uarg[1] = (uint64_t) p->lgenval; /* uint32_t */
		uarg[2] = (uint64_t) p->ugenval; /* uint32_t */
		uarg[3] = (uint64_t) p->rw_wc; /* uint32_t */
		iarg[4] = (int64_t) p->flags; /* int */
		break;
	}
	/* psynch_rw_downgrade */
	case 299: {
		struct psynch_rw_downgrade_args *p = params;
		uarg[0] = (uint64_t) p->rwlock; /* user_addr_t */
		uarg[1] = (uint64_t) p->lgenval; /* uint32_t */
		uarg[2] = (uint64_t) p->ugenval; /* uint32_t */
		uarg[3] = (uint64_t) p->rw_wc; /* uint32_t */
		iarg[4] = (int64_t) p->flags; /* int */
		break;
	}
	/* psynch_rw_upgrade */
	case 300: {
		struct psynch_rw_upgrade_args *p = params;
		uarg[0] = (uint64_t) p->rwlock; /* user_addr_t */
		uarg[1] = (uint64_t) p->lgenval; /* uint32_t */
		uarg[2] = (uint64_t) p->ugenval; /* uint32_t */
		uarg[3] = (uint64_t) p->rw_wc; /* uint32_t */
		iarg[4] = (int64_t) p->flags; /* int */
		break;
	}
	/* psynch_mutexwait */
	case 301: {
		struct psynch_mutexwait_args *p = params;
		uarg[0] = (uint64_t) p->mutex; /* user_addr_t */
		uarg[1] = (uint64_t) p->mgen; /* uint32_t */
		uarg[2] = (uint64_t) p->ugen; /* uint32_t */
		uarg[3] = (uint64_t) p->tid; /* uint64_t */
		uarg[4] = (uint64_t) p->flags; /* uint32_t */
		break;
	}
	/* psynch_mutexdrop */
	case 302: {
		struct psynch_mutexdrop_args *p = params;
		uarg[0] = (uint64_t) p->mutex; /* user_addr_t */
		uarg[1] = (uint64_t) p->mgen; /* uint32_t */
		uarg[2] = (uint64_t) p->ugen; /* uint32_t */
		uarg[3] = (uint64_t) p->tid; /* uint64_t */
		uarg[4] = (uint64_t) p->flags; /* uint32_t */
		break;
	}
	/* psynch_cvbroad */
	case 303: {
		struct psynch_cvbroad_args *p = params;
		uarg[0] = (uint64_t) p->cv; /* user_addr_t */
		uarg[1] = (uint64_t) p->cvlsgen; /* uint64_t */
		uarg[2] = (uint64_t) p->cvudgen; /* uint64_t */
		uarg[3] = (uint64_t) p->flags; /* uint32_t */
		uarg[4] = (uint64_t) p->mutex; /* user_addr_t */
		uarg[5] = (uint64_t) p->mugen; /* uint64_t */
		uarg[6] = (uint64_t) p->tid; /* uint64_t */
		break;
	}
	/* psynch_cvsignal */
	case 304: {
		struct psynch_cvsignal_args *p = params;
		uarg[0] = (uint64_t) p->cv; /* user_addr_t */
		uarg[1] = (uint64_t) p->cvlsgen; /* uint64_t */
		uarg[2] = (uint64_t) p->cvugen; /* uint32_t */
		iarg[3] = (int64_t) p->thread_port; /* int */
		uarg[4] = (uint64_t) p->mutex; /* user_addr_t */
		uarg[5] = (uint64_t) p->mugen; /* uint64_t */
		uarg[6] = (uint64_t) p->tid; /* uint64_t */
		uarg[7] = (uint64_t) p->flags; /* uint32_t */
		break;
	}
	/* psynch_cvwait */
	case 305: {
		struct psynch_cvwait_args *p = params;
		uarg[0] = (uint64_t) p->cv; /* user_addr_t */
		uarg[1] = (uint64_t) p->cvlsgen; /* uint64_t */
		uarg[2] = (uint64_t) p->cvugen; /* uint32_t */
		uarg[3] = (uint64_t) p->mutex; /* user_addr_t */
		uarg[4] = (uint64_t) p->mugen; /* uint64_t */
		uarg[5] = (uint64_t) p->flags; /* uint32_t */
		iarg[6] = (int64_t) p->sec; /* int64_t */
		uarg[7] = (uint64_t) p->nsec; /* uint32_t */
		break;
	}
	/* psynch_rw_rdlock */
	case 306: {
		struct psynch_rw_rdlock_args *p = params;
		uarg[0] = (uint64_t) p->rwlock; /* user_addr_t */
		uarg[1] = (uint64_t) p->lgenval; /* uint32_t */
		uarg[2] = (uint64_t) p->ugenval; /* uint32_t */
		uarg[3] = (uint64_t) p->rw_wc; /* uint32_t */
		iarg[4] = (int64_t) p->flags; /* int */
		break;
	}
	/* psynch_rw_wrlock */
	case 307: {
		struct psynch_rw_wrlock_args *p = params;
		uarg[0] = (uint64_t) p->rwlock; /* user_addr_t */
		uarg[1] = (uint64_t) p->lgenval; /* uint32_t */
		uarg[2] = (uint64_t) p->ugenval; /* uint32_t */
		uarg[3] = (uint64_t) p->rw_wc; /* uint32_t */
		iarg[4] = (int64_t) p->flags; /* int */
		break;
	}
	/* psynch_rw_unlock */
	case 308: {
		struct psynch_rw_unlock_args *p = params;
		uarg[0] = (uint64_t) p->rwlock; /* user_addr_t */
		uarg[1] = (uint64_t) p->lgenval; /* uint32_t */
		uarg[2] = (uint64_t) p->ugenval; /* uint32_t */
		uarg[3] = (uint64_t) p->rw_wc; /* uint32_t */
		iarg[4] = (int64_t) p->flags; /* int */
		break;
	}
	/* psynch_rw_unlock2 */
	case 309: {
		struct psynch_rw_unlock2_args *p = params;
		uarg[0] = (uint64_t) p->rwlock; /* user_addr_t */
		uarg[1] = (uint64_t) p->lgenval; /* uint32_t */
		uarg[2] = (uint64_t) p->ugenval; /* uint32_t */
		uarg[3] = (uint64_t) p->rw_wc; /* uint32_t */
		iarg[4] = (int64_t) p->flags; /* int */
		break;
	}
#else
#endif
	/* getsid */
	case 310: {
		struct getsid_args *p = params;
		iarg[0] = (int64_t) p->pid; /* pid_t */
		break;
	}
	/* settid_with_pid */
	case 311: {
		struct settid_with_pid_args *p = params;
		iarg[0] = (int64_t) p->pid; /* pid_t */
		iarg[1] = (int64_t) p->assume; /* int */
		break;
	}
#if PSYNCH
	/* psynch_cvclrprepost */
	case 312: {
		struct psynch_cvclrprepost_args *p = params;
		uarg[0] = (uint64_t) p->cv; /* user_addr_t */
		uarg[1] = (uint64_t) p->cvgen; /* uint32_t */
		uarg[2] = (uint64_t) p->cvugen; /* uint32_t */
		uarg[3] = (uint64_t) p->cvsgen; /* uint32_t */
		uarg[4] = (uint64_t) p->prepocnt; /* uint32_t */
		uarg[5] = (uint64_t) p->preposeq; /* uint32_t */
		uarg[6] = (uint64_t) p->flags; /* uint32_t */
		break;
	}
#else
#endif
	/* aio_fsync */
	case 313: {
		struct aio_fsync_args *p = params;
		iarg[0] = (int64_t) p->op; /* int */
		uarg[1] = (uint64_t) p->aiocbp; /* user_addr_t */
		break;
	}
	/* aio_return */
	case 314: {
		struct aio_return_args *p = params;
		uarg[0] = (uint64_t) p->aiocbp; /* user_addr_t */
		break;
	}
	/* aio_suspend */
	case 315: {
		struct aio_suspend_args *p = params;
		uarg[0] = (uint64_t) p->aiocblist; /* user_addr_t */
		iarg[1] = (int64_t) p->nent; /* int */
		uarg[2] = (uint64_t) p->timeoutp; /* user_addr_t */
		break;
	}
	/* aio_cancel */
	case 316: {
		struct aio_cancel_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->aiocbp; /* user_addr_t */
		break;
	}
	/* aio_error */
	case 317: {
		struct aio_error_args *p = params;
		uarg[0] = (uint64_t) p->aiocbp; /* user_addr_t */
		break;
	}
	/* aio_read */
	case 318: {
		struct aio_read_args *p = params;
		uarg[0] = (uint64_t) p->aiocbp; /* user_addr_t */
		break;
	}
	/* aio_write */
	case 319: {
		struct aio_write_args *p = params;
		uarg[0] = (uint64_t) p->aiocbp; /* user_addr_t */
		break;
	}
	/* lio_listio */
	case 320: {
		struct lio_listio_args *p = params;
		iarg[0] = (int64_t) p->mode; /* int */
		uarg[1] = (uint64_t) p->aiocblist; /* user_addr_t */
		iarg[2] = (int64_t) p->nent; /* int */
		uarg[3] = (uint64_t) p->sigp; /* user_addr_t */
		break;
	}
	/* iopolicysys */
	case 322: {
		struct iopolicysys_args *p = params;
		iarg[0] = (int64_t) p->cmd; /* int */
		uarg[1] = (uint64_t) p->arg; /* void * */
		break;
	}
	/* process_policy */
	case 323: {
		struct process_policy_args *p = params;
		iarg[0] = (int64_t) p->scope; /* int */
		iarg[1] = (int64_t) p->action; /* int */
		iarg[2] = (int64_t) p->policy; /* int */
		iarg[3] = (int64_t) p->policy_subtype; /* int */
		uarg[4] = (uint64_t) p->attrp; /* user_addr_t */
		iarg[5] = (int64_t) p->target_pid; /* pid_t */
		uarg[6] = (uint64_t) p->target_threadid; /* uint64_t */
		break;
	}
	/* mlockall */
	case 324: {
		struct mlockall_args *p = params;
		iarg[0] = (int64_t) p->how; /* int */
		break;
	}
	/* munlockall */
	case 325: {
		struct munlockall_args *p = params;
		iarg[0] = (int64_t) p->how; /* int */
		break;
	}
	/* issetugid */
	case 327: {
		break;
	}
	/* __pthread_kill */
	case 328: {
		struct __pthread_kill_args *p = params;
		iarg[0] = (int64_t) p->thread_port; /* int */
		iarg[1] = (int64_t) p->sig; /* int */
		break;
	}
	/* __pthread_sigmask */
	case 329: {
		struct __pthread_sigmask_args *p = params;
		iarg[0] = (int64_t) p->how; /* int */
		uarg[1] = (uint64_t) p->set; /* user_addr_t */
		uarg[2] = (uint64_t) p->oset; /* user_addr_t */
		break;
	}
	/* __sigwait */
	case 330: {
		struct __sigwait_args *p = params;
		uarg[0] = (uint64_t) p->set; /* user_addr_t */
		uarg[1] = (uint64_t) p->sig; /* user_addr_t */
		break;
	}
	/* __disable_threadsignal */
	case 331: {
		struct __disable_threadsignal_args *p = params;
		iarg[0] = (int64_t) p->value; /* int */
		break;
	}
	/* __pthread_markcancel */
	case 332: {
		struct __pthread_markcancel_args *p = params;
		iarg[0] = (int64_t) p->thread_port; /* int */
		break;
	}
	/* __pthread_canceled */
	case 333: {
		struct __pthread_canceled_args *p = params;
		iarg[0] = (int64_t) p->action; /* int */
		break;
	}
	/* __semwait_signal */
	case 334: {
		struct __semwait_signal_args *p = params;
		iarg[0] = (int64_t) p->cond_sem; /* int */
		iarg[1] = (int64_t) p->mutex_sem; /* int */
		iarg[2] = (int64_t) p->timeout; /* int */
		iarg[3] = (int64_t) p->relative; /* int */
		iarg[4] = (int64_t) p->tv_sec; /* int64_t */
		iarg[5] = (int64_t) p->tv_nsec; /* int32_t */
		break;
	}
	/* proc_info */
	case 336: {
		struct proc_info_args *p = params;
		iarg[0] = (int64_t) p->callnum; /* int32_t */
		iarg[1] = (int64_t) p->pid; /* int32_t */
		uarg[2] = (uint64_t) p->flavor; /* uint32_t */
		uarg[3] = (uint64_t) p->arg; /* uint64_t */
		uarg[4] = (uint64_t) p->buffer; /* user_addr_t */
		iarg[5] = (int64_t) p->buffersize; /* int32_t */
		break;
	}
#if SENDFILE
	/* sendfile */
	case 337: {
		struct sendfile_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		iarg[1] = (int64_t) p->s; /* int */
		iarg[2] = (int64_t) p->offset; /* off_t */
		uarg[3] = (uint64_t) p->nbytes; /* off_t * */
		uarg[4] = (uint64_t) p->hdtr; /* struct sf_hdtr * */
		iarg[5] = (int64_t) p->flags; /* int */
		break;
	}
#else /* !SENDFILE */
#endif /* SENDFILE */
	/* stat64 */
	case 338: {
		struct stat64_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		uarg[1] = (uint64_t) p->ub; /* user_addr_t */
		break;
	}
	/* sys_fstat64 */
	case 339: {
		struct fstat64_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->ub; /* user_addr_t */
		break;
	}
	/* lstat64 */
	case 340: {
		struct lstat64_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		uarg[1] = (uint64_t) p->ub; /* user_addr_t */
		break;
	}
	/* stat64_extended */
	case 341: {
		struct stat64_extended_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		uarg[1] = (uint64_t) p->ub; /* user_addr_t */
		uarg[2] = (uint64_t) p->xsecurity; /* user_addr_t */
		uarg[3] = (uint64_t) p->xsecurity_size; /* user_addr_t */
		break;
	}
	/* lstat64_extended */
	case 342: {
		struct lstat64_extended_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		uarg[1] = (uint64_t) p->ub; /* user_addr_t */
		uarg[2] = (uint64_t) p->xsecurity; /* user_addr_t */
		uarg[3] = (uint64_t) p->xsecurity_size; /* user_addr_t */
		break;
	}
	/* sys_fstat64_extended */
	case 343: {
		struct fstat64_extended_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->ub; /* user_addr_t */
		uarg[2] = (uint64_t) p->xsecurity; /* user_addr_t */
		uarg[3] = (uint64_t) p->xsecurity_size; /* user_addr_t */
		break;
	}
	/* getdirentries64 */
	case 344: {
		struct getdirentries64_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->buf; /* void * */
		uarg[2] = (uint64_t) p->bufsize; /* user_size_t */
		uarg[3] = (uint64_t) p->position; /* off_t * */
		break;
	}
	/* statfs64 */
	case 345: {
		struct statfs64_args *p = params;
		uarg[0] = (uint64_t) p->path; /* char * */
		uarg[1] = (uint64_t) p->buf; /* struct statfs64 * */
		break;
	}
	/* fstatfs64 */
	case 346: {
		struct fstatfs64_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->buf; /* struct statfs64 * */
		break;
	}
	/* getfsstat64 */
	case 347: {
		struct getfsstat64_args *p = params;
		uarg[0] = (uint64_t) p->buf; /* user_addr_t */
		iarg[1] = (int64_t) p->bufsize; /* int */
		iarg[2] = (int64_t) p->flags; /* int */
		break;
	}
	/* __pthread_chdir */
	case 348: {
		struct __pthread_chdir_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		break;
	}
	/* __pthread_fchdir */
	case 349: {
		struct __pthread_fchdir_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		break;
	}
	/* audit */
	case 350: {
		struct audit_args *p = params;
		uarg[0] = (uint64_t) p->record; /* void * */
		iarg[1] = (int64_t) p->length; /* int */
		break;
	}
	/* auditon */
	case 351: {
		struct auditon_args *p = params;
		iarg[0] = (int64_t) p->cmd; /* int */
		uarg[1] = (uint64_t) p->data; /* void * */
		iarg[2] = (int64_t) p->length; /* int */
		break;
	}
	/* getauid */
	case 353: {
		struct getauid_args *p = params;
		uarg[0] = (uint64_t) p->auid; /* au_id_t * */
		break;
	}
	/* setauid */
	case 354: {
		struct setauid_args *p = params;
		uarg[0] = (uint64_t) p->auid; /* au_id_t * */
		break;
	}
	/* getaudit_addr */
	case 357: {
		struct getaudit_addr_args *p = params;
		uarg[0] = (uint64_t) p->auditinfo_addr; /* struct auditinfo_addr * */
		iarg[1] = (int64_t) p->length; /* int */
		break;
	}
	/* setaudit_addr */
	case 358: {
		struct setaudit_addr_args *p = params;
		uarg[0] = (uint64_t) p->auditinfo_addr; /* struct auditinfo_addr * */
		iarg[1] = (int64_t) p->length; /* int */
		break;
	}
	/* auditctl */
	case 359: {
		struct auditctl_args *p = params;
		uarg[0] = (uint64_t) p->path; /* char * */
		break;
	}
#if CONFIG_WORKQUEUE
	/* bsdthread_create */
	case 360: {
		struct bsdthread_create_args *p = params;
		uarg[0] = (uint64_t) p->func; /* user_addr_t */
		uarg[1] = (uint64_t) p->func_arg; /* user_addr_t */
		uarg[2] = (uint64_t) p->stack; /* user_addr_t */
		uarg[3] = (uint64_t) p->pthread; /* user_addr_t */
		uarg[4] = (uint64_t) p->flags; /* uint32_t */
		break;
	}
	/* bsdthread_terminate */
	case 361: {
		struct bsdthread_terminate_args *p = params;
		uarg[0] = (uint64_t) p->stackaddr; /* user_addr_t */
		uarg[1] = (uint64_t) p->freesize; /* size_t */
		uarg[2] = (uint64_t) p->port; /* uint32_t */
		uarg[3] = (uint64_t) p->sem; /* uint32_t */
		break;
	}
#else
#endif /* CONFIG_WORKQUEUE */
	/* kqueue */
	case 362: {
		break;
	}
	/* kevent */
	case 363: {
		struct kevent_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->changelist; /* const struct kevent * */
		iarg[2] = (int64_t) p->nchanges; /* int */
		uarg[3] = (uint64_t) p->eventlist; /* struct kevent * */
		iarg[4] = (int64_t) p->nevents; /* int */
		uarg[5] = (uint64_t) p->timeout; /* const struct timespec * */
		break;
	}
	/* lchown */
	case 364: {
		struct lchown_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		uarg[1] = (uint64_t) p->owner; /* uid_t */
		iarg[2] = (int64_t) p->group; /* gid_t */
		break;
	}
#if CONFIG_WORKQUEUE
	/* bsdthread_register */
	case 366: {
		struct bsdthread_register_args *p = params;
		uarg[0] = (uint64_t) p->threadstart; /* user_addr_t */
		uarg[1] = (uint64_t) p->wqthread; /* user_addr_t */
		uarg[2] = (uint64_t) p->flags; /* uint32_t */
		uarg[3] = (uint64_t) p->stack_addr_hint; /* user_addr_t */
		uarg[4] = (uint64_t) p->targetconc_ptr; /* user_addr_t */
		uarg[5] = (uint64_t) p->dispatchqueue_offset; /* uint32_t */
		uarg[6] = (uint64_t) p->tsd_offset; /* uint32_t */
		break;
	}
	/* workq_open */
	case 367: {
		break;
	}
	/* workq_kernreturn */
	case 368: {
		struct workq_kernreturn_args *p = params;
		iarg[0] = (int64_t) p->options; /* int */
		uarg[1] = (uint64_t) p->item; /* user_addr_t */
		iarg[2] = (int64_t) p->affinity; /* int */
		iarg[3] = (int64_t) p->prio; /* int */
		break;
	}
#else
#endif /* CONFIG_WORKQUEUE */
	/* kevent64 */
	case 369: {
		struct kevent64_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->changelist; /* const struct kevent64_s * */
		iarg[2] = (int64_t) p->nchanges; /* int */
		uarg[3] = (uint64_t) p->eventlist; /* struct kevent64_s * */
		iarg[4] = (int64_t) p->nevents; /* int */
		uarg[5] = (uint64_t) p->flags; /* unsigned int */
		uarg[6] = (uint64_t) p->timeout; /* const struct timespec * */
		break;
	}
#if OLD_SEMWAIT_SIGNAL
	/* __old_semwait_signal */
	case 370: {
		struct __old_semwait_signal_args *p = params;
		iarg[0] = (int64_t) p->cond_sem; /* int */
		iarg[1] = (int64_t) p->mutex_sem; /* int */
		iarg[2] = (int64_t) p->timeout; /* int */
		iarg[3] = (int64_t) p->relative; /* int */
		uarg[4] = (uint64_t) p->ts; /* const struct timespec * */
		break;
	}
	/* __old_semwait_signal_nocancel */
	case 371: {
		struct __old_semwait_signal_nocancel_args *p = params;
		iarg[0] = (int64_t) p->cond_sem; /* int */
		iarg[1] = (int64_t) p->mutex_sem; /* int */
		iarg[2] = (int64_t) p->timeout; /* int */
		iarg[3] = (int64_t) p->relative; /* int */
		uarg[4] = (uint64_t) p->ts; /* const struct timespec * */
		break;
	}
#else
#endif
	/* thread_selfid */
	case 372: {
		break;
	}
	/* ledger */
	case 373: {
		struct ledger_args *p = params;
		iarg[0] = (int64_t) p->cmd; /* int */
		uarg[1] = (uint64_t) p->arg1; /* caddr_t */
		uarg[2] = (uint64_t) p->arg2; /* caddr_t */
		uarg[3] = (uint64_t) p->arg3; /* caddr_t */
		break;
	}
	/* kevent_qos */
	case 374: {
		struct kevent_qos_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->changelist; /* const struct kevent_qos_s * */
		iarg[2] = (int64_t) p->nchanges; /* int */
		uarg[3] = (uint64_t) p->eventlist; /* struct kevent_qos_s * */
		iarg[4] = (int64_t) p->nevents; /* int */
		uarg[5] = (uint64_t) p->data_out; /* void * */
		uarg[6] = (uint64_t) p->data_available; /* size_t * */
		uarg[7] = (uint64_t) p->flags; /* unsigned int */
		break;
	}
	/* kevent_id */
	case 375: {
		struct kevent_id_args *p = params;
		uarg[0] = (uint64_t) p->id; /* uint64_t */
		uarg[1] = (uint64_t) p->changelist; /* const struct kevent_qos_s * */
		iarg[2] = (int64_t) p->nchanges; /* int */
		uarg[3] = (uint64_t) p->eventlist; /* struct kevent_qos_s * */
		iarg[4] = (int64_t) p->nevents; /* int */
		uarg[5] = (uint64_t) p->data_out; /* void * */
		uarg[6] = (uint64_t) p->data_available; /* size_t * */
		uarg[7] = (uint64_t) p->flags; /* unsigned int */
		break;
	}
	/* __mac_execve */
	case 380: {
		struct __mac_execve_args *p = params;
		uarg[0] = (uint64_t) p->fname; /* char * */
		uarg[1] = (uint64_t) p->argp; /* char ** */
		uarg[2] = (uint64_t) p->envp; /* char ** */
		uarg[3] = (uint64_t) p->mac_p; /* struct mac * */
		break;
	}
#if CONFIG_MACF
	/* __mac_syscall */
	case 381: {
		struct __mac_syscall_args *p = params;
		uarg[0] = (uint64_t) p->policy; /* char * */
		iarg[1] = (int64_t) p->call; /* int */
		uarg[2] = (uint64_t) p->arg; /* user_addr_t */
		break;
	}
	/* __mac_get_file */
	case 382: {
		struct __mac_get_file_args *p = params;
		uarg[0] = (uint64_t) p->path_p; /* char * */
		uarg[1] = (uint64_t) p->mac_p; /* struct mac * */
		break;
	}
	/* __mac_set_file */
	case 383: {
		struct __mac_set_file_args *p = params;
		uarg[0] = (uint64_t) p->path_p; /* char * */
		uarg[1] = (uint64_t) p->mac_p; /* struct mac * */
		break;
	}
	/* __mac_get_link */
	case 384: {
		struct __mac_get_link_args *p = params;
		uarg[0] = (uint64_t) p->path_p; /* char * */
		uarg[1] = (uint64_t) p->mac_p; /* struct mac * */
		break;
	}
	/* __mac_set_link */
	case 385: {
		struct __mac_set_link_args *p = params;
		uarg[0] = (uint64_t) p->path_p; /* char * */
		uarg[1] = (uint64_t) p->mac_p; /* struct mac * */
		break;
	}
	/* __mac_get_proc */
	case 386: {
		struct __mac_get_proc_args *p = params;
		uarg[0] = (uint64_t) p->mac_p; /* struct mac * */
		break;
	}
	/* __mac_set_proc */
	case 387: {
		struct __mac_set_proc_args *p = params;
		uarg[0] = (uint64_t) p->mac_p; /* struct mac * */
		break;
	}
	/* __mac_get_fd */
	case 388: {
		struct __mac_get_fd_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->mac_p; /* struct mac * */
		break;
	}
	/* __mac_set_fd */
	case 389: {
		struct __mac_set_fd_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->mac_p; /* struct mac * */
		break;
	}
	/* __mac_get_pid */
	case 390: {
		struct __mac_get_pid_args *p = params;
		iarg[0] = (int64_t) p->pid; /* pid_t */
		uarg[1] = (uint64_t) p->mac_p; /* struct mac * */
		break;
	}
#else
#endif
	/* pselect */
	case 394: {
		struct pselect_args *p = params;
		iarg[0] = (int64_t) p->nd; /* int */
		uarg[1] = (uint64_t) p->in; /* u_int32_t * */
		uarg[2] = (uint64_t) p->ou; /* u_int32_t * */
		uarg[3] = (uint64_t) p->ex; /* u_int32_t * */
		uarg[4] = (uint64_t) p->ts; /* const struct timespec * */
		uarg[5] = (uint64_t) p->mask; /* const struct sigset_t * */
		break;
	}
	/* pselect_nocancel */
	case 395: {
		struct pselect_nocancel_args *p = params;
		iarg[0] = (int64_t) p->nd; /* int */
		uarg[1] = (uint64_t) p->in; /* u_int32_t * */
		uarg[2] = (uint64_t) p->ou; /* u_int32_t * */
		uarg[3] = (uint64_t) p->ex; /* u_int32_t * */
		uarg[4] = (uint64_t) p->ts; /* const struct timespec * */
		uarg[5] = (uint64_t) p->mask; /* const struct sigset_t * */
		break;
	}
	/* read_nocancel */
	case 396: {
		struct read_nocancel_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->cbuf; /* user_addr_t */
		uarg[2] = (uint64_t) p->nbyte; /* user_size_t */
		break;
	}
	/* write_nocancel */
	case 397: {
		struct write_nocancel_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->cbuf; /* user_addr_t */
		uarg[2] = (uint64_t) p->nbyte; /* user_size_t */
		break;
	}
	/* open_nocancel */
	case 398: {
		struct open_nocancel_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		iarg[1] = (int64_t) p->flags; /* int */
		iarg[2] = (int64_t) p->mode; /* int */
		break;
	}
	/* sys_close_nocancel */
	case 399: {
		struct close_nocancel_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		break;
	}
	/* wait4_nocancel */
	case 400: {
		struct wait4_nocancel_args *p = params;
		iarg[0] = (int64_t) p->pid; /* int */
		uarg[1] = (uint64_t) p->status; /* user_addr_t */
		iarg[2] = (int64_t) p->options; /* int */
		uarg[3] = (uint64_t) p->rusage; /* user_addr_t */
		break;
	}
#if SOCKETS
	/* recvmsg_nocancel */
	case 401: {
		struct recvmsg_nocancel_args *p = params;
		iarg[0] = (int64_t) p->s; /* int */
		uarg[1] = (uint64_t) p->msg; /* struct msghdr * */
		iarg[2] = (int64_t) p->flags; /* int */
		break;
	}
	/* sendmsg_nocancel */
	case 402: {
		struct sendmsg_nocancel_args *p = params;
		iarg[0] = (int64_t) p->s; /* int */
		uarg[1] = (uint64_t) p->msg; /* caddr_t */
		iarg[2] = (int64_t) p->flags; /* int */
		break;
	}
	/* recvfrom_nocancel */
	case 403: {
		struct recvfrom_nocancel_args *p = params;
		iarg[0] = (int64_t) p->s; /* int */
		uarg[1] = (uint64_t) p->buf; /* void * */
		uarg[2] = (uint64_t) p->len; /* size_t */
		iarg[3] = (int64_t) p->flags; /* int */
		uarg[4] = (uint64_t) p->from; /* struct sockaddr * */
		uarg[5] = (uint64_t) p->fromlenaddr; /* int * */
		break;
	}
	/* accept_nocancel */
	case 404: {
		struct accept_nocancel_args *p = params;
		iarg[0] = (int64_t) p->s; /* int */
		uarg[1] = (uint64_t) p->name; /* caddr_t */
		uarg[2] = (uint64_t) p->anamelen; /* socklen_t * */
		break;
	}
#else
#endif /* SOCKETS */
	/* msync_nocancel */
	case 405: {
		struct msync_nocancel_args *p = params;
		uarg[0] = (uint64_t) p->addr; /* caddr_t */
		uarg[1] = (uint64_t) p->len; /* size_t */
		iarg[2] = (int64_t) p->flags; /* int */
		break;
	}
	/* sys_fcntl_nocancel */
	case 406: {
		struct fcntl_nocancel_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		iarg[1] = (int64_t) p->cmd; /* int */
		iarg[2] = (int64_t) p->arg; /* long */
		break;
	}
	/* select_nocancel */
	case 407: {
		struct select_nocancel_args *p = params;
		iarg[0] = (int64_t) p->nd; /* int */
		uarg[1] = (uint64_t) p->in; /* u_int32_t * */
		uarg[2] = (uint64_t) p->ou; /* u_int32_t * */
		uarg[3] = (uint64_t) p->ex; /* u_int32_t * */
		uarg[4] = (uint64_t) p->tv; /* struct timeval * */
		break;
	}
	/* fsync_nocancel */
	case 408: {
		struct fsync_nocancel_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		break;
	}
#if SOCKETS
	/* connect_nocancel */
	case 409: {
		struct connect_nocancel_args *p = params;
		iarg[0] = (int64_t) p->s; /* int */
		uarg[1] = (uint64_t) p->name; /* caddr_t */
		iarg[2] = (int64_t) p->namelen; /* socklen_t */
		break;
	}
#else
#endif /* SOCKETS */
	/* sigsuspend_nocancel */
	case 410: {
		struct sigsuspend_nocancel_args *p = params;
		iarg[0] = (int64_t) p->mask; /* sigset_t */
		break;
	}
	/* readv_nocancel */
	case 411: {
		struct readv_nocancel_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->iovp; /* struct iovec * */
		uarg[2] = (uint64_t) p->iovcnt; /* u_int */
		break;
	}
	/* writev_nocancel */
	case 412: {
		struct writev_nocancel_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->iovp; /* struct iovec * */
		uarg[2] = (uint64_t) p->iovcnt; /* u_int */
		break;
	}
#if SOCKETS
	/* sendto_nocancel */
	case 413: {
		struct sendto_nocancel_args *p = params;
		iarg[0] = (int64_t) p->s; /* int */
		uarg[1] = (uint64_t) p->buf; /* caddr_t */
		uarg[2] = (uint64_t) p->len; /* size_t */
		iarg[3] = (int64_t) p->flags; /* int */
		uarg[4] = (uint64_t) p->to; /* caddr_t */
		iarg[5] = (int64_t) p->tolen; /* socklen_t */
		break;
	}
#else
#endif /* SOCKETS */
	/* pread_nocancel */
	case 414: {
		struct pread_nocancel_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->buf; /* user_addr_t */
		uarg[2] = (uint64_t) p->nbyte; /* user_size_t */
		iarg[3] = (int64_t) p->offset; /* off_t */
		break;
	}
	/* pwrite_nocancel */
	case 415: {
		struct pwrite_nocancel_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->buf; /* user_addr_t */
		uarg[2] = (uint64_t) p->nbyte; /* user_size_t */
		iarg[3] = (int64_t) p->offset; /* off_t */
		break;
	}
	/* waitid_nocancel */
	case 416: {
		struct waitid_nocancel_args *p = params;
		iarg[0] = (int64_t) p->idtype; /* idtype_t */
		iarg[1] = (int64_t) p->id; /* id_t */
		uarg[2] = (uint64_t) p->infop; /* siginfo_t * */
		iarg[3] = (int64_t) p->options; /* int */
		break;
	}
	/* poll_nocancel */
	case 417: {
		struct poll_nocancel_args *p = params;
		uarg[0] = (uint64_t) p->fds; /* struct pollfd * */
		uarg[1] = (uint64_t) p->nfds; /* u_int */
		iarg[2] = (int64_t) p->timeout; /* int */
		break;
	}
#if SYSV_MSG
	/* msgsnd_nocancel */
	case 418: {
		struct msgsnd_nocancel_args *p = params;
		iarg[0] = (int64_t) p->msqid; /* int */
		uarg[1] = (uint64_t) p->msgp; /* void * */
		uarg[2] = (uint64_t) p->msgsz; /* size_t */
		iarg[3] = (int64_t) p->msgflg; /* int */
		break;
	}
	/* msgrcv_nocancel */
	case 419: {
		struct msgrcv_nocancel_args *p = params;
		iarg[0] = (int64_t) p->msqid; /* int */
		uarg[1] = (uint64_t) p->msgp; /* void * */
		uarg[2] = (uint64_t) p->msgsz; /* size_t */
		iarg[3] = (int64_t) p->msgtyp; /* long */
		iarg[4] = (int64_t) p->msgflg; /* int */
		break;
	}
#else
#endif
	/* sem_wait_nocancel */
	case 420: {
		struct sem_wait_nocancel_args *p = params;
		uarg[0] = (uint64_t) p->sem; /* sem_t * */
		break;
	}
	/* aio_suspend_nocancel */
	case 421: {
		struct aio_suspend_nocancel_args *p = params;
		uarg[0] = (uint64_t) p->aiocblist; /* user_addr_t */
		iarg[1] = (int64_t) p->nent; /* int */
		uarg[2] = (uint64_t) p->timeoutp; /* user_addr_t */
		break;
	}
	/* __sigwait_nocancel */
	case 422: {
		struct __sigwait_nocancel_args *p = params;
		uarg[0] = (uint64_t) p->set; /* user_addr_t */
		uarg[1] = (uint64_t) p->sig; /* user_addr_t */
		break;
	}
	/* __semwait_signal_nocancel */
	case 423: {
		struct __semwait_signal_nocancel_args *p = params;
		iarg[0] = (int64_t) p->cond_sem; /* int */
		iarg[1] = (int64_t) p->mutex_sem; /* int */
		iarg[2] = (int64_t) p->timeout; /* int */
		iarg[3] = (int64_t) p->relative; /* int */
		iarg[4] = (int64_t) p->tv_sec; /* int64_t */
		iarg[5] = (int64_t) p->tv_nsec; /* int32_t */
		break;
	}
	/* __mac_mount */
	case 424: {
		struct __mac_mount_args *p = params;
		uarg[0] = (uint64_t) p->type; /* char * */
		uarg[1] = (uint64_t) p->path; /* char * */
		iarg[2] = (int64_t) p->flags; /* int */
		uarg[3] = (uint64_t) p->data; /* caddr_t */
		uarg[4] = (uint64_t) p->mac_p; /* struct mac * */
		break;
	}
#if CONFIG_MACF
	/* __mac_get_mount */
	case 425: {
		struct __mac_get_mount_args *p = params;
		uarg[0] = (uint64_t) p->path; /* char * */
		uarg[1] = (uint64_t) p->mac_p; /* struct mac * */
		break;
	}
#else
#endif
	/* __mac_getfsstat */
	case 426: {
		struct __mac_getfsstat_args *p = params;
		uarg[0] = (uint64_t) p->buf; /* user_addr_t */
		iarg[1] = (int64_t) p->bufsize; /* int */
		uarg[2] = (uint64_t) p->mac; /* user_addr_t */
		iarg[3] = (int64_t) p->macsize; /* int */
		iarg[4] = (int64_t) p->flags; /* int */
		break;
	}
	/* fsgetpath */
	case 427: {
		struct fsgetpath_args *p = params;
		uarg[0] = (uint64_t) p->buf; /* user_addr_t */
		uarg[1] = (uint64_t) p->bufsize; /* size_t */
		uarg[2] = (uint64_t) p->fsid; /* user_addr_t */
		uarg[3] = (uint64_t) p->objid; /* uint64_t */
		break;
	}
	/* audit_session_self */
	case 428: {
		break;
	}
	/* audit_session_join */
	case 429: {
		struct audit_session_join_args *p = params;
		iarg[0] = (int64_t) p->port; /* mach_port_name_t */
		break;
	}
	/* sys_fileport_makeport */
	case 430: {
		struct fileport_makeport_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->portnamep; /* user_addr_t */
		break;
	}
	/* sys_fileport_makefd */
	case 431: {
		struct fileport_makefd_args *p = params;
		iarg[0] = (int64_t) p->port; /* mach_port_name_t */
		break;
	}
	/* audit_session_port */
	case 432: {
		struct audit_session_port_args *p = params;
		iarg[0] = (int64_t) p->asid; /* au_asid_t */
		uarg[1] = (uint64_t) p->portnamep; /* user_addr_t */
		break;
	}
	/* pid_suspend */
	case 433: {
		struct pid_suspend_args *p = params;
		iarg[0] = (int64_t) p->pid; /* int */
		break;
	}
	/* pid_resume */
	case 434: {
		struct pid_resume_args *p = params;
		iarg[0] = (int64_t) p->pid; /* int */
		break;
	}
#if CONFIG_EMBEDDED
	/* pid_hibernate */
	case 435: {
		struct pid_hibernate_args *p = params;
		iarg[0] = (int64_t) p->pid; /* int */
		break;
	}
#else
#endif
#if SOCKETS
	/* pid_shutdown_sockets */
	case 436: {
		struct pid_shutdown_sockets_args *p = params;
		iarg[0] = (int64_t) p->pid; /* int */
		iarg[1] = (int64_t) p->level; /* int */
		break;
	}
#else
#endif
	/* shared_region_map_and_slide_np */
	case 438: {
		struct shared_region_map_and_slide_np_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->count; /* uint32_t */
		uarg[2] = (uint64_t) p->mappings; /* const struct shared_file_mapping_np * */
		uarg[3] = (uint64_t) p->slide; /* uint32_t */
		uarg[4] = (uint64_t) p->slide_start; /* uint64_t * */
		uarg[5] = (uint64_t) p->slide_size; /* uint32_t */
		break;
	}
	/* kas_info */
	case 439: {
		struct kas_info_args *p = params;
		iarg[0] = (int64_t) p->selector; /* int */
		uarg[1] = (uint64_t) p->value; /* void * */
		uarg[2] = (uint64_t) p->size; /* size_t * */
		break;
	}
#if CONFIG_MEMORYSTATUS
	/* memorystatus_control */
	case 440: {
		struct memorystatus_control_args *p = params;
		uarg[0] = (uint64_t) p->command; /* uint32_t */
		iarg[1] = (int64_t) p->pid; /* int32_t */
		uarg[2] = (uint64_t) p->flags; /* uint32_t */
		uarg[3] = (uint64_t) p->buffer; /* user_addr_t */
		uarg[4] = (uint64_t) p->buffersize; /* size_t */
		break;
	}
#else
#endif
	/* guarded_open_np */
	case 441: {
		struct guarded_open_np_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		uarg[1] = (uint64_t) p->guard; /* const guardid_t * */
		uarg[2] = (uint64_t) p->guardflags; /* u_int */
		iarg[3] = (int64_t) p->flags; /* int */
		iarg[4] = (int64_t) p->mode; /* int */
		break;
	}
	/* guarded_close_np */
	case 442: {
		struct guarded_close_np_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->guard; /* const guardid_t * */
		break;
	}
	/* guarded_kqueue_np */
	case 443: {
		struct guarded_kqueue_np_args *p = params;
		uarg[0] = (uint64_t) p->guard; /* const guardid_t * */
		uarg[1] = (uint64_t) p->guardflags; /* u_int */
		break;
	}
	/* change_fdguard_np */
	case 444: {
		struct change_fdguard_np_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->guard; /* const guardid_t * */
		uarg[2] = (uint64_t) p->guardflags; /* u_int */
		uarg[3] = (uint64_t) p->nguard; /* const guardid_t * */
		uarg[4] = (uint64_t) p->nguardflags; /* u_int */
		uarg[5] = (uint64_t) p->fdflagsp; /* int * */
		break;
	}
	/* usrctl */
	case 445: {
		struct usrctl_args *p = params;
		uarg[0] = (uint64_t) p->flags; /* uint32_t */
		break;
	}
	/* proc_rlimit_control */
	case 446: {
		struct proc_rlimit_control_args *p = params;
		iarg[0] = (int64_t) p->pid; /* pid_t */
		iarg[1] = (int64_t) p->flavor; /* int */
		uarg[2] = (uint64_t) p->arg; /* void * */
		break;
	}
#if SOCKETS
	/* connectx */
	case 447: {
		struct connectx_args *p = params;
		iarg[0] = (int64_t) p->socket; /* int */
		uarg[1] = (uint64_t) p->endpoints; /* const sa_endpoints_t * */
		iarg[2] = (int64_t) p->associd; /* sae_associd_t */
		uarg[3] = (uint64_t) p->flags; /* unsigned int */
		uarg[4] = (uint64_t) p->iov; /* const struct iovec * */
		uarg[5] = (uint64_t) p->iovcnt; /* unsigned int */
		uarg[6] = (uint64_t) p->len; /* size_t * */
		uarg[7] = (uint64_t) p->connid; /* sae_connid_t * */
		break;
	}
	/* disconnectx */
	case 448: {
		struct disconnectx_args *p = params;
		iarg[0] = (int64_t) p->s; /* int */
		iarg[1] = (int64_t) p->aid; /* sae_associd_t */
		iarg[2] = (int64_t) p->cid; /* sae_connid_t */
		break;
	}
	/* peeloff */
	case 449: {
		struct peeloff_args *p = params;
		iarg[0] = (int64_t) p->s; /* int */
		iarg[1] = (int64_t) p->aid; /* sae_associd_t */
		break;
	}
	/* socket_delegate */
	case 450: {
		struct socket_delegate_args *p = params;
		iarg[0] = (int64_t) p->domain; /* int */
		iarg[1] = (int64_t) p->type; /* int */
		iarg[2] = (int64_t) p->protocol; /* int */
		iarg[3] = (int64_t) p->epid; /* pid_t */
		break;
	}
#else
#endif /* SOCKETS */
	/* telemetry */
	case 451: {
		struct telemetry_args *p = params;
		uarg[0] = (uint64_t) p->cmd; /* uint64_t */
		uarg[1] = (uint64_t) p->deadline; /* uint64_t */
		uarg[2] = (uint64_t) p->interval; /* uint64_t */
		uarg[3] = (uint64_t) p->leeway; /* uint64_t */
		uarg[4] = (uint64_t) p->arg4; /* uint64_t */
		uarg[5] = (uint64_t) p->arg5; /* uint64_t */
		break;
	}
#if CONFIG_PROC_UUID_POLICY
	/* proc_uuid_policy */
	case 452: {
		struct proc_uuid_policy_args *p = params;
		uarg[0] = (uint64_t) p->operation; /* uint32_t */
		uarg[1] = (uint64_t) p->uuid; /* uuid_t */
		uarg[2] = (uint64_t) p->uuidlen; /* size_t */
		uarg[3] = (uint64_t) p->flags; /* uint32_t */
		break;
	}
#else
#endif
#if CONFIG_MEMORYSTATUS
	/* memorystatus_get_level */
	case 453: {
		struct memorystatus_get_level_args *p = params;
		uarg[0] = (uint64_t) p->level; /* user_addr_t */
		break;
	}
#else
#endif
	/* system_override */
	case 454: {
		struct system_override_args *p = params;
		uarg[0] = (uint64_t) p->timeout; /* uint64_t */
		uarg[1] = (uint64_t) p->flags; /* uint64_t */
		break;
	}
	/* vfs_purge */
	case 455: {
		break;
	}
	/* sfi_ctl */
	case 456: {
		struct sfi_ctl_args *p = params;
		uarg[0] = (uint64_t) p->operation; /* uint32_t */
		uarg[1] = (uint64_t) p->sfi_class; /* uint32_t */
		uarg[2] = (uint64_t) p->time; /* uint64_t */
		uarg[3] = (uint64_t) p->out_time; /* uint64_t * */
		break;
	}
	/* sfi_pidctl */
	case 457: {
		struct sfi_pidctl_args *p = params;
		uarg[0] = (uint64_t) p->operation; /* uint32_t */
		iarg[1] = (int64_t) p->pid; /* pid_t */
		uarg[2] = (uint64_t) p->sfi_flags; /* uint32_t */
		uarg[3] = (uint64_t) p->out_sfi_flags; /* uint32_t * */
		break;
	}
#if CONFIG_COALITIONS
	/* coalition */
	case 458: {
		struct coalition_args *p = params;
		uarg[0] = (uint64_t) p->operation; /* uint32_t */
		uarg[1] = (uint64_t) p->cid; /* uint64_t * */
		uarg[2] = (uint64_t) p->flags; /* uint32_t */
		break;
	}
	/* coalition_info */
	case 459: {
		struct coalition_info_args *p = params;
		uarg[0] = (uint64_t) p->flavor; /* uint32_t */
		uarg[1] = (uint64_t) p->cid; /* uint64_t * */
		uarg[2] = (uint64_t) p->buffer; /* void * */
		uarg[3] = (uint64_t) p->bufsize; /* size_t * */
		break;
	}
#else
#endif /* COALITIONS */
#if NECP
	/* necp_match_policy */
	case 460: {
		struct necp_match_policy_args *p = params;
		uarg[0] = (uint64_t) p->parameters; /* uint8_t * */
		uarg[1] = (uint64_t) p->parameters_size; /* size_t */
		uarg[2] = (uint64_t) p->returned_result; /* struct necp_aggregate_result * */
		break;
	}
#else
#endif /* NECP */
	/* getattrlistbulk */
	case 461: {
		struct getattrlistbulk_args *p = params;
		iarg[0] = (int64_t) p->dirfd; /* int */
		uarg[1] = (uint64_t) p->alist; /* struct attrlist * */
		uarg[2] = (uint64_t) p->attributeBuffer; /* void * */
		uarg[3] = (uint64_t) p->bufferSize; /* size_t */
		uarg[4] = (uint64_t) p->options; /* uint64_t */
		break;
	}
	/* clonefileat */
	case 462: {
		struct clonefileat_args *p = params;
		iarg[0] = (int64_t) p->src_dirfd; /* int */
		uarg[1] = (uint64_t) p->src; /* user_addr_t */
		iarg[2] = (int64_t) p->dst_dirfd; /* int */
		uarg[3] = (uint64_t) p->dst; /* user_addr_t */
		uarg[4] = (uint64_t) p->flags; /* uint32_t */
		break;
	}
	/* openat */
	case 463: {
		struct openat_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->path; /* user_addr_t */
		iarg[2] = (int64_t) p->flags; /* int */
		iarg[3] = (int64_t) p->mode; /* int */
		break;
	}
	/* openat_nocancel */
	case 464: {
		struct openat_nocancel_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->path; /* user_addr_t */
		iarg[2] = (int64_t) p->flags; /* int */
		iarg[3] = (int64_t) p->mode; /* int */
		break;
	}
	/* renameat */
	case 465: {
		struct renameat_args *p = params;
		iarg[0] = (int64_t) p->fromfd; /* int */
		uarg[1] = (uint64_t) p->from; /* char * */
		iarg[2] = (int64_t) p->tofd; /* int */
		uarg[3] = (uint64_t) p->to; /* char * */
		break;
	}
	/* faccessat */
	case 466: {
		struct faccessat_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->path; /* user_addr_t */
		iarg[2] = (int64_t) p->amode; /* int */
		iarg[3] = (int64_t) p->flag; /* int */
		break;
	}
	/* fchmodat */
	case 467: {
		struct fchmodat_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->path; /* user_addr_t */
		iarg[2] = (int64_t) p->mode; /* int */
		iarg[3] = (int64_t) p->flag; /* int */
		break;
	}
	/* fchownat */
	case 468: {
		struct fchownat_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->path; /* user_addr_t */
		uarg[2] = (uint64_t) p->uid; /* uid_t */
		iarg[3] = (int64_t) p->gid; /* gid_t */
		iarg[4] = (int64_t) p->flag; /* int */
		break;
	}
	/* fstatat */
	case 469: {
		struct fstatat_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->path; /* user_addr_t */
		uarg[2] = (uint64_t) p->ub; /* user_addr_t */
		iarg[3] = (int64_t) p->flag; /* int */
		break;
	}
	/* fstatat64 */
	case 470: {
		struct fstatat64_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->path; /* user_addr_t */
		uarg[2] = (uint64_t) p->ub; /* user_addr_t */
		iarg[3] = (int64_t) p->flag; /* int */
		break;
	}
	/* linkat */
	case 471: {
		struct linkat_args *p = params;
		iarg[0] = (int64_t) p->fd1; /* int */
		uarg[1] = (uint64_t) p->path; /* user_addr_t */
		iarg[2] = (int64_t) p->fd2; /* int */
		uarg[3] = (uint64_t) p->link; /* user_addr_t */
		iarg[4] = (int64_t) p->flag; /* int */
		break;
	}
	/* unlinkat */
	case 472: {
		struct unlinkat_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->path; /* user_addr_t */
		iarg[2] = (int64_t) p->flag; /* int */
		break;
	}
	/* readlinkat */
	case 473: {
		struct readlinkat_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->path; /* user_addr_t */
		uarg[2] = (uint64_t) p->buf; /* user_addr_t */
		uarg[3] = (uint64_t) p->bufsize; /* size_t */
		break;
	}
	/* symlinkat */
	case 474: {
		struct symlinkat_args *p = params;
		uarg[0] = (uint64_t) p->path1; /* user_addr_t * */
		iarg[1] = (int64_t) p->fd; /* int */
		uarg[2] = (uint64_t) p->path2; /* user_addr_t */
		break;
	}
	/* mkdirat */
	case 475: {
		struct mkdirat_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->path; /* user_addr_t */
		iarg[2] = (int64_t) p->mode; /* int */
		break;
	}
	/* getattrlistat */
	case 476: {
		struct getattrlistat_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->path; /* const char * */
		uarg[2] = (uint64_t) p->alist; /* struct attrlist * */
		uarg[3] = (uint64_t) p->attributeBuffer; /* void * */
		uarg[4] = (uint64_t) p->bufferSize; /* size_t */
		uarg[5] = (uint64_t) p->options; /* u_long */
		break;
	}
	/* proc_trace_log */
	case 477: {
		struct proc_trace_log_args *p = params;
		iarg[0] = (int64_t) p->pid; /* pid_t */
		uarg[1] = (uint64_t) p->uniqueid; /* uint64_t */
		break;
	}
	/* bsdthread_ctl */
	case 478: {
		struct bsdthread_ctl_args *p = params;
		uarg[0] = (uint64_t) p->cmd; /* user_addr_t */
		uarg[1] = (uint64_t) p->arg1; /* user_addr_t */
		uarg[2] = (uint64_t) p->arg2; /* user_addr_t */
		uarg[3] = (uint64_t) p->arg3; /* user_addr_t */
		break;
	}
	/* openbyid_np */
	case 479: {
		struct openbyid_np_args *p = params;
		uarg[0] = (uint64_t) p->fsid; /* user_addr_t */
		uarg[1] = (uint64_t) p->objid; /* user_addr_t */
		iarg[2] = (int64_t) p->oflags; /* int */
		break;
	}
#if SOCKETS
	/* recvmsg_x */
	case 480: {
		struct recvmsg_x_args *p = params;
		iarg[0] = (int64_t) p->s; /* int */
		uarg[1] = (uint64_t) p->msgp; /* struct msghdr_x * */
		uarg[2] = (uint64_t) p->cnt; /* u_int */
		iarg[3] = (int64_t) p->flags; /* int */
		break;
	}
	/* sendmsg_x */
	case 481: {
		struct sendmsg_x_args *p = params;
		iarg[0] = (int64_t) p->s; /* int */
		uarg[1] = (uint64_t) p->msgp; /* struct msghdr_x * */
		uarg[2] = (uint64_t) p->cnt; /* u_int */
		iarg[3] = (int64_t) p->flags; /* int */
		break;
	}
#else
#endif /* SOCKETS */
	/* thread_selfusage */
	case 482: {
		break;
	}
#if CONFIG_CSR
	/* csrctl */
	case 483: {
		struct csrctl_args *p = params;
		uarg[0] = (uint64_t) p->op; /* uint32_t */
		uarg[1] = (uint64_t) p->useraddr; /* user_addr_t */
		uarg[2] = (uint64_t) p->usersize; /* user_addr_t */
		break;
	}
#else
#endif /* CSR */
	/* guarded_open_dprotected_np */
	case 484: {
		struct guarded_open_dprotected_np_args *p = params;
		uarg[0] = (uint64_t) p->path; /* user_addr_t */
		uarg[1] = (uint64_t) p->guard; /* const guardid_t * */
		uarg[2] = (uint64_t) p->guardflags; /* u_int */
		iarg[3] = (int64_t) p->flags; /* int */
		iarg[4] = (int64_t) p->dpclass; /* int */
		iarg[5] = (int64_t) p->dpflags; /* int */
		iarg[6] = (int64_t) p->mode; /* int */
		break;
	}
	/* guarded_write_np */
	case 485: {
		struct guarded_write_np_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->guard; /* const guardid_t * */
		uarg[2] = (uint64_t) p->cbuf; /* user_addr_t */
		uarg[3] = (uint64_t) p->nbyte; /* user_size_t */
		break;
	}
	/* guarded_pwrite_np */
	case 486: {
		struct guarded_pwrite_np_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->guard; /* const guardid_t * */
		uarg[2] = (uint64_t) p->buf; /* user_addr_t */
		uarg[3] = (uint64_t) p->nbyte; /* user_size_t */
		iarg[4] = (int64_t) p->offset; /* off_t */
		break;
	}
	/* guarded_writev_np */
	case 487: {
		struct guarded_writev_np_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->guard; /* const guardid_t * */
		uarg[2] = (uint64_t) p->iovp; /* struct iovec * */
		iarg[3] = (int64_t) p->iovcnt; /* int */
		break;
	}
	/* renameatx_np */
	case 488: {
		struct renameatx_np_args *p = params;
		iarg[0] = (int64_t) p->fromfd; /* int */
		uarg[1] = (uint64_t) p->from; /* char * */
		iarg[2] = (int64_t) p->tofd; /* int */
		uarg[3] = (uint64_t) p->to; /* char * */
		uarg[4] = (uint64_t) p->flags; /* u_int */
		break;
	}
#if CONFIG_CODE_DECRYPTION
	/* mremap_encrypted */
	case 489: {
		struct mremap_encrypted_args *p = params;
		uarg[0] = (uint64_t) p->addr; /* caddr_t */
		uarg[1] = (uint64_t) p->len; /* size_t */
		uarg[2] = (uint64_t) p->cryptid; /* uint32_t */
		uarg[3] = (uint64_t) p->cputype; /* uint32_t */
		uarg[4] = (uint64_t) p->cpusubtype; /* uint32_t */
		break;
	}
#else
#endif
#if NETWORKING
	/* netagent_trigger */
	case 490: {
		struct netagent_trigger_args *p = params;
		uarg[0] = (uint64_t) p->agent_uuid; /* uuid_t */
		uarg[1] = (uint64_t) p->agent_uuidlen; /* size_t */
		break;
	}
#else
#endif /* NETWORKING */
	/* stack_snapshot_with_config */
	case 491: {
		struct stack_snapshot_with_config_args *p = params;
		iarg[0] = (int64_t) p->stackshot_config_version; /* int */
		uarg[1] = (uint64_t) p->stackshot_config; /* user_addr_t */
		uarg[2] = (uint64_t) p->stackshot_config_size; /* size_t */
		break;
	}
#if CONFIG_TELEMETRY
	/* microstackshot */
	case 492: {
		struct microstackshot_args *p = params;
		uarg[0] = (uint64_t) p->tracebuf; /* user_addr_t */
		uarg[1] = (uint64_t) p->tracebuf_size; /* uint32_t */
		uarg[2] = (uint64_t) p->flags; /* uint32_t */
		break;
	}
#else
#endif /* CONFIG_TELEMETRY */
#if PGO
	/* grab_pgo_data */
	case 493: {
		struct grab_pgo_data_args *p = params;
		uarg[0] = (uint64_t) p->uuid; /* user_addr_t */
		iarg[1] = (int64_t) p->flags; /* int */
		uarg[2] = (uint64_t) p->buffer; /* user_addr_t */
		uarg[3] = (uint64_t) p->size; /* user_ssize_t */
		break;
	}
#else
#endif
#if CONFIG_PERSONAS
	/* persona */
	case 494: {
		struct persona_args *p = params;
		uarg[0] = (uint64_t) p->operation; /* uint32_t */
		uarg[1] = (uint64_t) p->flags; /* uint32_t */
		uarg[2] = (uint64_t) p->info; /* struct kpersona_info * */
		uarg[3] = (uint64_t) p->id; /* uid_t * */
		uarg[4] = (uint64_t) p->idlen; /* size_t * */
		uarg[5] = (uint64_t) p->path; /* char * */
		break;
	}
#else
#endif
	/* mach_eventlink_signal */
	case 496: {
		struct mach_eventlink_signal_args *p = params;
		iarg[0] = (int64_t) p->eventlink_port; /* mach_port_name_t */
		uarg[1] = (uint64_t) p->signal_count; /* uint64_t */
		break;
	}
	/* mach_eventlink_wait_until */
	case 497: {
		struct mach_eventlink_wait_until_args *p = params;
		iarg[0] = (int64_t) p->eventlink_port; /* mach_port_name_t */
		uarg[1] = (uint64_t) p->wait_count; /* uint64_t */
		uarg[2] = (uint64_t) p->deadline; /* uint64_t */
		uarg[3] = (uint64_t) p->clock_id; /* uint32_t */
		uarg[4] = (uint64_t) p->option; /* uint32_t */
		break;
	}
	/* mach_eventlink_signal_wait_until */
	case 498: {
		struct mach_eventlink_signal_wait_until_args *p = params;
		iarg[0] = (int64_t) p->eventlink_port; /* mach_port_name_t */
		uarg[1] = (uint64_t) p->wait_count; /* uint64_t */
		uarg[2] = (uint64_t) p->signal_count; /* uint64_t */
		uarg[3] = (uint64_t) p->deadline; /* uint64_t */
		uarg[4] = (uint64_t) p->clock_id; /* uint32_t */
		uarg[5] = (uint64_t) p->option; /* uint32_t */
		break;
	}
	/* work_interval_ctl */
	case 499: {
		struct work_interval_ctl_args *p = params;
		uarg[0] = (uint64_t) p->operation; /* uint32_t */
		uarg[1] = (uint64_t) p->work_interval_id; /* uint64_t */
		uarg[2] = (uint64_t) p->arg; /* void * */
		uarg[3] = (uint64_t) p->len; /* size_t */
		break;
	}
	/* getentropy */
	case 500: {
		struct getentropy_args *p = params;
		uarg[0] = (uint64_t) p->buffer; /* void * */
		uarg[1] = (uint64_t) p->size; /* size_t */
		break;
	}
#if NECP
	/* necp_open */
	case 501: {
		struct necp_open_args *p = params;
		iarg[0] = (int64_t) p->flags; /* int */
		break;
	}
	/* necp_client_action */
	case 502: {
		struct necp_client_action_args *p = params;
		iarg[0] = (int64_t) p->necp_fd; /* int */
		uarg[1] = (uint64_t) p->action; /* uint32_t */
		uarg[2] = (uint64_t) p->client_id; /* uuid_t */
		uarg[3] = (uint64_t) p->client_id_len; /* size_t */
		uarg[4] = (uint64_t) p->buffer; /* uint8_t * */
		uarg[5] = (uint64_t) p->buffer_size; /* size_t */
		break;
	}
#else
#endif /* NECP */
	/* ulock_wait */
	case 515: {
		struct ulock_wait_args *p = params;
		uarg[0] = (uint64_t) p->operation; /* uint32_t */
		uarg[1] = (uint64_t) p->addr; /* void * */
		uarg[2] = (uint64_t) p->value; /* uint64_t */
		uarg[3] = (uint64_t) p->timeout; /* uint32_t */
		break;
	}
	/* ulock_wake */
	case 516: {
		struct ulock_wake_args *p = params;
		uarg[0] = (uint64_t) p->operation; /* uint32_t */
		uarg[1] = (uint64_t) p->addr; /* void * */
		uarg[2] = (uint64_t) p->wake_value; /* uint64_t */
		break;
	}
	/* fclonefileat */
	case 517: {
		struct fclonefileat_args *p = params;
		iarg[0] = (int64_t) p->src_fd; /* int */
		iarg[1] = (int64_t) p->dst_dirfd; /* int */
		uarg[2] = (uint64_t) p->dst; /* user_addr_t */
		uarg[3] = (uint64_t) p->flags; /* uint32_t */
		break;
	}
	/* fs_snapshot */
	case 518: {
		struct fs_snapshot_args *p = params;
		uarg[0] = (uint64_t) p->op; /* uint32_t */
		iarg[1] = (int64_t) p->dirfd; /* int */
		uarg[2] = (uint64_t) p->name1; /* user_addr_t */
		uarg[3] = (uint64_t) p->name2; /* user_addr_t */
		uarg[4] = (uint64_t) p->data; /* user_addr_t */
		uarg[5] = (uint64_t) p->flags; /* uint32_t */
		break;
	}
	/* terminate_with_payload */
	case 520: {
		struct terminate_with_payload_args *p = params;
		iarg[0] = (int64_t) p->pid; /* int */
		uarg[1] = (uint64_t) p->reason_namespace; /* uint32_t */
		uarg[2] = (uint64_t) p->reason_code; /* uint64_t */
		uarg[3] = (uint64_t) p->payload; /* void * */
		uarg[4] = (uint64_t) p->payload_size; /* uint32_t */
		uarg[5] = (uint64_t) p->reason_string; /* const char * */
		uarg[6] = (uint64_t) p->reason_flags; /* uint64_t */
		break;
	}
	/* abort_with_payload */
	case 521: {
		struct abort_with_payload_args *p = params;
		uarg[0] = (uint64_t) p->reason_namespace; /* uint32_t */
		uarg[1] = (uint64_t) p->reason_code; /* uint64_t */
		uarg[2] = (uint64_t) p->payload; /* void * */
		uarg[3] = (uint64_t) p->payload_size; /* uint32_t */
		uarg[4] = (uint64_t) p->reason_string; /* const char * */
		uarg[5] = (uint64_t) p->reason_flags; /* uint64_t */
		break;
	}
#if NECP
	/* necp_session_open */
	case 522: {
		struct necp_session_open_args *p = params;
		iarg[0] = (int64_t) p->flags; /* int */
		break;
	}
	/* necp_session_action */
	case 523: {
		struct necp_session_action_args *p = params;
		iarg[0] = (int64_t) p->necp_fd; /* int */
		uarg[1] = (uint64_t) p->action; /* uint32_t */
		uarg[2] = (uint64_t) p->in_buffer; /* uint8_t * */
		uarg[3] = (uint64_t) p->in_buffer_length; /* size_t */
		uarg[4] = (uint64_t) p->out_buffer; /* uint8_t * */
		uarg[5] = (uint64_t) p->out_buffer_length; /* size_t */
		break;
	}
#else /* NECP */
#endif /* NECP */
	/* setattrlistat */
	case 524: {
		struct setattrlistat_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->path; /* const char * */
		uarg[2] = (uint64_t) p->alist; /* struct attrlist * */
		uarg[3] = (uint64_t) p->attributeBuffer; /* void * */
		uarg[4] = (uint64_t) p->bufferSize; /* size_t */
		uarg[5] = (uint64_t) p->options; /* uint32_t */
		break;
	}
	/* net_qos_guideline */
	case 525: {
		struct net_qos_guideline_args *p = params;
		uarg[0] = (uint64_t) p->param; /* struct net_qos_param * */
		uarg[1] = (uint64_t) p->param_len; /* uint32_t */
		break;
	}
	/* fmount */
	case 526: {
		struct fmount_args *p = params;
		uarg[0] = (uint64_t) p->type; /* const char * */
		iarg[1] = (int64_t) p->fd; /* int */
		iarg[2] = (int64_t) p->flags; /* int */
		uarg[3] = (uint64_t) p->data; /* void * */
		break;
	}
	/* ntp_adjtime */
	case 527: {
		struct ntp_adjtime_args *p = params;
		uarg[0] = (uint64_t) p->tp; /* struct timex * */
		break;
	}
	/* ntp_gettime */
	case 528: {
		struct ntp_gettime_args *p = params;
		uarg[0] = (uint64_t) p->ntvp; /* struct ntptimeval * */
		break;
	}
	/* os_fault_with_payload */
	case 529: {
		struct os_fault_with_payload_args *p = params;
		uarg[0] = (uint64_t) p->reason_namespace; /* uint32_t */
		uarg[1] = (uint64_t) p->reason_code; /* uint64_t */
		uarg[2] = (uint64_t) p->payload; /* void * */
		uarg[3] = (uint64_t) p->payload_size; /* uint32_t */
		uarg[4] = (uint64_t) p->reason_string; /* const char * */
		uarg[5] = (uint64_t) p->reason_flags; /* uint64_t */
		break;
	}
#if CONFIG_WORKQUEUE
	/* kqueue_workloop_ctl */
	case 530: {
		struct kqueue_workloop_ctl_args *p = params;
		uarg[0] = (uint64_t) p->cmd; /* user_addr_t */
		uarg[1] = (uint64_t) p->options; /* uint64_t */
		uarg[2] = (uint64_t) p->addr; /* user_addr_t */
		uarg[3] = (uint64_t) p->sz; /* size_t */
		break;
	}
#else
#endif // CONFIG_WORKQUEUE
	/* __mach_bridge_remote_time */
	case 531: {
		struct __mach_bridge_remote_time_args *p = params;
		uarg[0] = (uint64_t) p->local_timestamp; /* uint64_t */
		break;
	}
#if CONFIG_COALITIONS
	/* coalition_ledger */
	case 532: {
		struct coalition_ledger_args *p = params;
		uarg[0] = (uint64_t) p->operation; /* uint32_t */
		uarg[1] = (uint64_t) p->cid; /* uint64_t * */
		uarg[2] = (uint64_t) p->buffer; /* void * */
		uarg[3] = (uint64_t) p->bufsize; /* size_t * */
		break;
	}
#else
#endif // CONFIG_COALITIONS
	/* log_data */
	case 533: {
		struct log_data_args *p = params;
		uarg[0] = (uint64_t) p->tag; /* unsigned int */
		uarg[1] = (uint64_t) p->flags; /* unsigned int */
		uarg[2] = (uint64_t) p->buffer; /* void * */
		uarg[3] = (uint64_t) p->size; /* unsigned int */
		break;
	}
	/* memorystatus_available_memory */
	case 534: {
		break;
	}
	/* shared_region_map_and_slide_2_np */
	case 536: {
		struct shared_region_map_and_slide_2_np_args *p = params;
		uarg[0] = (uint64_t) p->files_count; /* uint32_t */
		uarg[1] = (uint64_t) p->files; /* const struct shared_file_np * */
		uarg[2] = (uint64_t) p->mappings_count; /* uint32_t */
		uarg[3] = (uint64_t) p->mappings; /* const struct shared_file_mapping_slide_np * */
		break;
	}
	/* pivot_root */
	case 537: {
		struct pivot_root_args *p = params;
		uarg[0] = (uint64_t) p->new_rootfs_path_before; /* const char * */
		uarg[1] = (uint64_t) p->old_rootfs_path_after; /* const char * */
		break;
	}
	/* task_inspect_for_pid */
	case 538: {
		struct task_inspect_for_pid_args *p = params;
		iarg[0] = (int64_t) p->target_tport; /* mach_port_name_t */
		iarg[1] = (int64_t) p->pid; /* int */
		uarg[2] = (uint64_t) p->t; /* mach_port_name_t * */
		break;
	}
	/* task_read_for_pid */
	case 539: {
		struct task_read_for_pid_args *p = params;
		iarg[0] = (int64_t) p->target_tport; /* mach_port_name_t */
		iarg[1] = (int64_t) p->pid; /* int */
		uarg[2] = (uint64_t) p->t; /* mach_port_name_t * */
		break;
	}
	/* sys_preadv */
	case 540: {
		struct preadv_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->iovp; /* struct iovec * */
		iarg[2] = (int64_t) p->iovcnt; /* int */
		iarg[3] = (int64_t) p->offset; /* off_t */
		break;
	}
	/* sys_pwritev */
	case 541: {
		struct pwritev_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->iovp; /* struct iovec * */
		iarg[2] = (int64_t) p->iovcnt; /* int */
		iarg[3] = (int64_t) p->offset; /* off_t */
		break;
	}
	/* sys_preadv_nocancel */
	case 542: {
		struct preadv_nocancel_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->iovp; /* struct iovec * */
		iarg[2] = (int64_t) p->iovcnt; /* int */
		iarg[3] = (int64_t) p->offset; /* off_t */
		break;
	}
	/* sys_pwritev_nocancel */
	case 543: {
		struct pwritev_nocancel_args *p = params;
		iarg[0] = (int64_t) p->fd; /* int */
		uarg[1] = (uint64_t) p->iovp; /* struct iovec * */
		iarg[2] = (int64_t) p->iovcnt; /* int */
		iarg[3] = (int64_t) p->offset; /* off_t */
		break;
	}
	/* ulock_wait2 */
	case 544: {
		struct ulock_wait2_args *p = params;
		uarg[0] = (uint64_t) p->operation; /* uint32_t */
		uarg[1] = (uint64_t) p->addr; /* void * */
		uarg[2] = (uint64_t) p->value; /* uint64_t */
		uarg[3] = (uint64_t) p->timeout; /* uint64_t */
		uarg[4] = (uint64_t) p->value2; /* uint64_t */
		break;
	}
	/* proc_info_extended_id */
	case 545: {
		struct proc_info_extended_id_args *p = params;
		iarg[0] = (int64_t) p->callnum; /* int32_t */
		iarg[1] = (int64_t) p->pid; /* int32_t */
		uarg[2] = (uint64_t) p->flavor; /* uint32_t */
		uarg[3] = (uint64_t) p->flags; /* uint32_t */
		uarg[4] = (uint64_t) p->ext_id; /* uint64_t */
		uarg[5] = (uint64_t) p->arg; /* uint64_t */
		uarg[6] = (uint64_t) p->buffer; /* user_addr_t */
		iarg[7] = (int64_t) p->buffersize; /* int32_t */
		break;
	}
	default:
		break;
	};
}
void
systrace_entry_setargdesc(int sysnum, int ndx, char *desc, size_t descsz)
{
	const char *p = NULL;
	switch (sysnum) {
	/* nosys */
	case 0:
		break;
	/* exit */
	case 1:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* fork */
	case 2:
		break;
	/* read */
	case 3:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "user_size_t";
			break;
		default:
			break;
		};
		break;
	/* write */
	case 4:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "user_size_t";
			break;
		default:
			break;
		};
		break;
	/* open */
	case 5:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* sys_close */
	case 6:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* wait4 */
	case 7:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* link */
	case 9:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* unlink */
	case 10:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* chdir */
	case 12:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* fchdir */
	case 13:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* mknod */
	case 14:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* chmod */
	case 15:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* chown */
	case 16:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* getfsstat */
	case 18:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* getpid */
	case 20:
		break;
	/* setuid */
	case 23:
		switch(ndx) {
		case 0:
			p = "uid_t";
			break;
		default:
			break;
		};
		break;
	/* getuid */
	case 24:
		break;
	/* geteuid */
	case 25:
		break;
	/* ptrace */
	case 26:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "pid_t";
			break;
		case 2:
			p = "caddr_t";
			break;
		case 3:
			p = "int";
			break;
		default:
			break;
		};
		break;
#if SOCKETS
	/* recvmsg */
	case 27:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland struct msghdr *";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* sendmsg */
	case 28:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "caddr_t";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* recvfrom */
	case 29:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland void *";
			break;
		case 2:
			p = "size_t";
			break;
		case 3:
			p = "int";
			break;
		case 4:
			p = "userland struct sockaddr *";
			break;
		case 5:
			p = "userland int *";
			break;
		default:
			break;
		};
		break;
	/* accept */
	case 30:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "caddr_t";
			break;
		case 2:
			p = "userland socklen_t *";
			break;
		default:
			break;
		};
		break;
	/* getpeername */
	case 31:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "caddr_t";
			break;
		case 2:
			p = "userland socklen_t *";
			break;
		default:
			break;
		};
		break;
	/* getsockname */
	case 32:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "caddr_t";
			break;
		case 2:
			p = "userland socklen_t *";
			break;
		default:
			break;
		};
		break;
#else
#endif /* SOCKETS */
	/* access */
	case 33:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* chflags */
	case 34:
		switch(ndx) {
		case 0:
			p = "userland char *";
			break;
		case 1:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* fchflags */
	case 35:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* sync */
	case 36:
		break;
	/* kill */
	case 37:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* getppid */
	case 39:
		break;
	/* sys_dup */
	case 41:
		switch(ndx) {
		case 0:
			p = "u_int";
			break;
		default:
			break;
		};
		break;
	/* pipe */
	case 42:
		break;
	/* getegid */
	case 43:
		break;
	/* sigaction */
	case 46:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland struct __sigaction *";
			break;
		case 2:
			p = "userland struct sigaction *";
			break;
		default:
			break;
		};
		break;
	/* getgid */
	case 47:
		break;
	/* sigprocmask */
	case 48:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* getlogin */
	case 49:
		switch(ndx) {
		case 0:
			p = "userland char *";
			break;
		case 1:
			p = "u_int";
			break;
		default:
			break;
		};
		break;
	/* setlogin */
	case 50:
		switch(ndx) {
		case 0:
			p = "userland char *";
			break;
		default:
			break;
		};
		break;
	/* acct */
	case 51:
		switch(ndx) {
		case 0:
			p = "userland char *";
			break;
		default:
			break;
		};
		break;
	/* sigpending */
	case 52:
		switch(ndx) {
		case 0:
			p = "userland struct sigvec *";
			break;
		default:
			break;
		};
		break;
	/* sigaltstack */
	case 53:
		switch(ndx) {
		case 0:
			p = "userland struct sigaltstack *";
			break;
		case 1:
			p = "userland struct sigaltstack *";
			break;
		default:
			break;
		};
		break;
	/* ioctl */
	case 54:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "u_long";
			break;
		case 2:
			p = "caddr_t";
			break;
		default:
			break;
		};
		break;
	/* reboot */
	case 55:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland char *";
			break;
		default:
			break;
		};
		break;
	/* revoke */
	case 56:
		switch(ndx) {
		case 0:
			p = "userland char *";
			break;
		default:
			break;
		};
		break;
	/* symlink */
	case 57:
		switch(ndx) {
		case 0:
			p = "userland char *";
			break;
		case 1:
			p = "userland char *";
			break;
		default:
			break;
		};
		break;
	/* readlink */
	case 58:
		switch(ndx) {
		case 0:
			p = "userland char *";
			break;
		case 1:
			p = "userland char *";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* execve */
	case 59:
		switch(ndx) {
		case 0:
			p = "userland char *";
			break;
		case 1:
			p = "userland char **";
			break;
		case 2:
			p = "userland char **";
			break;
		default:
			break;
		};
		break;
	/* umask */
	case 60:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* chroot */
	case 61:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* msync */
	case 65:
		switch(ndx) {
		case 0:
			p = "caddr_t";
			break;
		case 1:
			p = "size_t";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* vfork */
	case 66:
		break;
	/* munmap */
	case 73:
		switch(ndx) {
		case 0:
			p = "caddr_t";
			break;
		case 1:
			p = "size_t";
			break;
		default:
			break;
		};
		break;
	/* mprotect */
	case 74:
		switch(ndx) {
		case 0:
			p = "caddr_t";
			break;
		case 1:
			p = "size_t";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* madvise */
	case 75:
		switch(ndx) {
		case 0:
			p = "caddr_t";
			break;
		case 1:
			p = "size_t";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* mincore */
	case 78:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "user_size_t";
			break;
		case 2:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* getgroups */
	case 79:
		switch(ndx) {
		case 0:
			p = "u_int";
			break;
		case 1:
			p = "userland gid_t *";
			break;
		default:
			break;
		};
		break;
	/* setgroups */
	case 80:
		switch(ndx) {
		case 0:
			p = "u_int";
			break;
		case 1:
			p = "userland gid_t *";
			break;
		default:
			break;
		};
		break;
	/* getpgrp */
	case 81:
		break;
	/* setpgid */
	case 82:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* setitimer */
	case 83:
		switch(ndx) {
		case 0:
			p = "u_int";
			break;
		case 1:
			p = "userland struct itimerval *";
			break;
		case 2:
			p = "userland struct itimerval *";
			break;
		default:
			break;
		};
		break;
	/* swapon */
	case 85:
		break;
	/* getitimer */
	case 86:
		switch(ndx) {
		case 0:
			p = "u_int";
			break;
		case 1:
			p = "userland struct itimerval *";
			break;
		default:
			break;
		};
		break;
	/* sys_getdtablesize */
	case 89:
		break;
	/* sys_dup2 */
	case 90:
		switch(ndx) {
		case 0:
			p = "u_int";
			break;
		case 1:
			p = "u_int";
			break;
		default:
			break;
		};
		break;
	/* sys_fcntl */
	case 92:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "long";
			break;
		default:
			break;
		};
		break;
	/* select */
	case 93:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland u_int32_t *";
			break;
		case 2:
			p = "userland u_int32_t *";
			break;
		case 3:
			p = "userland u_int32_t *";
			break;
		case 4:
			p = "userland struct timeval *";
			break;
		default:
			break;
		};
		break;
	/* fsync */
	case 95:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* setpriority */
	case 96:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "id_t";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
#if SOCKETS
	/* socket */
	case 97:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* connect */
	case 98:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "caddr_t";
			break;
		case 2:
			p = "socklen_t";
			break;
		default:
			break;
		};
		break;
#else
#endif /* SOCKETS */
	/* getpriority */
	case 100:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "id_t";
			break;
		default:
			break;
		};
		break;
#if SOCKETS
	/* bind */
	case 104:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "caddr_t";
			break;
		case 2:
			p = "socklen_t";
			break;
		default:
			break;
		};
		break;
	/* setsockopt */
	case 105:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "caddr_t";
			break;
		case 4:
			p = "socklen_t";
			break;
		default:
			break;
		};
		break;
	/* listen */
	case 106:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "int";
			break;
		default:
			break;
		};
		break;
#else
#endif /* SOCKETS */
	/* sigsuspend */
	case 111:
		switch(ndx) {
		case 0:
			p = "sigset_t";
			break;
		default:
			break;
		};
		break;
#if SOCKETS
#else
#endif /* SOCKETS */
	/* gettimeofday */
	case 116:
		switch(ndx) {
		case 0:
			p = "userland struct timeval *";
			break;
		case 1:
			p = "userland struct timezone *";
			break;
		case 2:
			p = "userland uint64_t *";
			break;
		default:
			break;
		};
		break;
	/* getrusage */
	case 117:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland struct rusage *";
			break;
		default:
			break;
		};
		break;
#if SOCKETS
	/* getsockopt */
	case 118:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "caddr_t";
			break;
		case 4:
			p = "userland socklen_t *";
			break;
		default:
			break;
		};
		break;
#else
#endif /* SOCKETS */
	/* readv */
	case 120:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland struct iovec *";
			break;
		case 2:
			p = "u_int";
			break;
		default:
			break;
		};
		break;
	/* writev */
	case 121:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland struct iovec *";
			break;
		case 2:
			p = "u_int";
			break;
		default:
			break;
		};
		break;
	/* settimeofday */
	case 122:
		switch(ndx) {
		case 0:
			p = "userland struct timeval *";
			break;
		case 1:
			p = "userland struct timezone *";
			break;
		default:
			break;
		};
		break;
	/* fchown */
	case 123:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* fchmod */
	case 124:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* setreuid */
	case 126:
		switch(ndx) {
		case 0:
			p = "uid_t";
			break;
		case 1:
			p = "uid_t";
			break;
		default:
			break;
		};
		break;
	/* setregid */
	case 127:
		switch(ndx) {
		case 0:
			p = "gid_t";
			break;
		case 1:
			p = "gid_t";
			break;
		default:
			break;
		};
		break;
	/* rename */
	case 128:
		switch(ndx) {
		case 0:
			p = "userland char *";
			break;
		case 1:
			p = "userland char *";
			break;
		default:
			break;
		};
		break;
	/* sys_flock */
	case 131:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* mkfifo */
	case 132:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "int";
			break;
		default:
			break;
		};
		break;
#if SOCKETS
	/* sendto */
	case 133:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "caddr_t";
			break;
		case 2:
			p = "size_t";
			break;
		case 3:
			p = "int";
			break;
		case 4:
			p = "caddr_t";
			break;
		case 5:
			p = "socklen_t";
			break;
		default:
			break;
		};
		break;
	/* shutdown */
	case 134:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* socketpair */
	case 135:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "userland int *";
			break;
		default:
			break;
		};
		break;
#else
#endif /* SOCKETS */
	/* mkdir */
	case 136:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* rmdir */
	case 137:
		switch(ndx) {
		case 0:
			p = "userland char *";
			break;
		default:
			break;
		};
		break;
	/* utimes */
	case 138:
		switch(ndx) {
		case 0:
			p = "userland char *";
			break;
		case 1:
			p = "userland struct timeval *";
			break;
		default:
			break;
		};
		break;
	/* futimes */
	case 139:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland struct timeval *";
			break;
		default:
			break;
		};
		break;
	/* adjtime */
	case 140:
		switch(ndx) {
		case 0:
			p = "userland struct timeval *";
			break;
		case 1:
			p = "userland struct timeval *";
			break;
		default:
			break;
		};
		break;
	/* gethostuuid */
	case 142:
		switch(ndx) {
		case 0:
			p = "userland unsigned char *";
			break;
		case 1:
			p = "userland const struct timespec *";
			break;
		default:
			break;
		};
		break;
	/* setsid */
	case 147:
		break;
	/* getpgid */
	case 151:
		switch(ndx) {
		case 0:
			p = "pid_t";
			break;
		default:
			break;
		};
		break;
	/* setprivexec */
	case 152:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* pread */
	case 153:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "user_size_t";
			break;
		case 3:
			p = "off_t";
			break;
		default:
			break;
		};
		break;
	/* pwrite */
	case 154:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "user_size_t";
			break;
		case 3:
			p = "off_t";
			break;
		default:
			break;
		};
		break;
#if NFSSERVER	/* XXX */
	/* nfssvc */
	case 155:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "caddr_t";
			break;
		default:
			break;
		};
		break;
#else
#endif
	/* statfs */
	case 157:
		switch(ndx) {
		case 0:
			p = "userland char *";
			break;
		case 1:
			p = "userland struct statfs *";
			break;
		default:
			break;
		};
		break;
	/* fstatfs */
	case 158:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland struct statfs *";
			break;
		default:
			break;
		};
		break;
	/* unmount */
	case 159:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "int";
			break;
		default:
			break;
		};
		break;
#if NFSSERVER	/* XXX */
	/* getfh */
	case 161:
		switch(ndx) {
		case 0:
			p = "userland char *";
			break;
		case 1:
			p = "userland fhandle_t *";
			break;
		default:
			break;
		};
		break;
#else
#endif
	/* quotactl */
	case 165:
		switch(ndx) {
		case 0:
			p = "userland const char *";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "caddr_t";
			break;
		default:
			break;
		};
		break;
	/* mount */
	case 167:
		switch(ndx) {
		case 0:
			p = "userland char *";
			break;
		case 1:
			p = "userland char *";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "caddr_t";
			break;
		default:
			break;
		};
		break;
	/* csops */
	case 169:
		switch(ndx) {
		case 0:
			p = "pid_t";
			break;
		case 1:
			p = "uint32_t";
			break;
		case 2:
			p = "user_addr_t";
			break;
		case 3:
			p = "user_size_t";
			break;
		default:
			break;
		};
		break;
	/* csops_audittoken */
	case 170:
		switch(ndx) {
		case 0:
			p = "pid_t";
			break;
		case 1:
			p = "uint32_t";
			break;
		case 2:
			p = "user_addr_t";
			break;
		case 3:
			p = "user_size_t";
			break;
		case 4:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* waitid */
	case 173:
		switch(ndx) {
		case 0:
			p = "idtype_t";
			break;
		case 1:
			p = "id_t";
			break;
		case 2:
			p = "userland siginfo_t *";
			break;
		case 3:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* kdebug_typefilter */
	case 177:
		switch(ndx) {
		case 0:
			p = "userland void **";
			break;
		case 1:
			p = "userland size_t *";
			break;
		default:
			break;
		};
		break;
	/* kdebug_trace_string */
	case 178:
		switch(ndx) {
		case 0:
			p = "uint32_t";
			break;
		case 1:
			p = "uint64_t";
			break;
		case 2:
			p = "userland const char *";
			break;
		default:
			break;
		};
		break;
	/* kdebug_trace64 */
	case 179:
		switch(ndx) {
		case 0:
			p = "uint32_t";
			break;
		case 1:
			p = "uint64_t";
			break;
		case 2:
			p = "uint64_t";
			break;
		case 3:
			p = "uint64_t";
			break;
		case 4:
			p = "uint64_t";
			break;
		default:
			break;
		};
		break;
	/* kdebug_trace */
	case 180:
		switch(ndx) {
		case 0:
			p = "uint32_t";
			break;
		case 1:
			p = "u_long";
			break;
		case 2:
			p = "u_long";
			break;
		case 3:
			p = "u_long";
			break;
		case 4:
			p = "u_long";
			break;
		default:
			break;
		};
		break;
	/* setgid */
	case 181:
		switch(ndx) {
		case 0:
			p = "gid_t";
			break;
		default:
			break;
		};
		break;
	/* setegid */
	case 182:
		switch(ndx) {
		case 0:
			p = "gid_t";
			break;
		default:
			break;
		};
		break;
	/* seteuid */
	case 183:
		switch(ndx) {
		case 0:
			p = "uid_t";
			break;
		default:
			break;
		};
		break;
	/* sigreturn */
	case 184:
		switch(ndx) {
		case 0:
			p = "userland struct ucontext *";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* thread_selfcounts */
	case 186:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "user_size_t";
			break;
		default:
			break;
		};
		break;
	/* fdatasync */
	case 187:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* stat */
	case 188:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* sys_fstat */
	case 189:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* lstat */
	case 190:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* pathconf */
	case 191:
		switch(ndx) {
		case 0:
			p = "userland char *";
			break;
		case 1:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* sys_fpathconf */
	case 192:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* getrlimit */
	case 194:
		switch(ndx) {
		case 0:
			p = "u_int";
			break;
		case 1:
			p = "userland struct rlimit *";
			break;
		default:
			break;
		};
		break;
	/* setrlimit */
	case 195:
		switch(ndx) {
		case 0:
			p = "u_int";
			break;
		case 1:
			p = "userland struct rlimit *";
			break;
		default:
			break;
		};
		break;
	/* getdirentries */
	case 196:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland char *";
			break;
		case 2:
			p = "u_int";
			break;
		case 3:
			p = "userland long *";
			break;
		default:
			break;
		};
		break;
	/* mmap */
	case 197:
		switch(ndx) {
		case 0:
			p = "caddr_t";
			break;
		case 1:
			p = "size_t";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "int";
			break;
		case 4:
			p = "int";
			break;
		case 5:
			p = "off_t";
			break;
		default:
			break;
		};
		break;
	/* lseek */
	case 199:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "off_t";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* truncate */
	case 200:
		switch(ndx) {
		case 0:
			p = "userland char *";
			break;
		case 1:
			p = "off_t";
			break;
		default:
			break;
		};
		break;
	/* ftruncate */
	case 201:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "off_t";
			break;
		default:
			break;
		};
		break;
	/* sysctl */
	case 202:
		switch(ndx) {
		case 0:
			p = "userland int *";
			break;
		case 1:
			p = "u_int";
			break;
		case 2:
			p = "userland void *";
			break;
		case 3:
			p = "userland size_t *";
			break;
		case 4:
			p = "userland void *";
			break;
		case 5:
			p = "size_t";
			break;
		default:
			break;
		};
		break;
	/* mlock */
	case 203:
		switch(ndx) {
		case 0:
			p = "caddr_t";
			break;
		case 1:
			p = "size_t";
			break;
		default:
			break;
		};
		break;
	/* munlock */
	case 204:
		switch(ndx) {
		case 0:
			p = "caddr_t";
			break;
		case 1:
			p = "size_t";
			break;
		default:
			break;
		};
		break;
	/* undelete */
	case 205:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* open_dprotected_np */
	case 216:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "int";
			break;
		case 4:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* fsgetpath_ext */
	case 217:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "size_t";
			break;
		case 2:
			p = "user_addr_t";
			break;
		case 3:
			p = "uint64_t";
			break;
		case 4:
			p = "uint32_t";
			break;
		default:
			break;
		};
		break;
	/* getattrlist */
	case 220:
		switch(ndx) {
		case 0:
			p = "userland const char *";
			break;
		case 1:
			p = "userland struct attrlist *";
			break;
		case 2:
			p = "userland void *";
			break;
		case 3:
			p = "size_t";
			break;
		case 4:
			p = "u_long";
			break;
		default:
			break;
		};
		break;
	/* setattrlist */
	case 221:
		switch(ndx) {
		case 0:
			p = "userland const char *";
			break;
		case 1:
			p = "userland struct attrlist *";
			break;
		case 2:
			p = "userland void *";
			break;
		case 3:
			p = "size_t";
			break;
		case 4:
			p = "u_long";
			break;
		default:
			break;
		};
		break;
	/* getdirentriesattr */
	case 222:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland struct attrlist *";
			break;
		case 2:
			p = "userland void *";
			break;
		case 3:
			p = "size_t";
			break;
		case 4:
			p = "userland u_long *";
			break;
		case 5:
			p = "userland u_long *";
			break;
		case 6:
			p = "userland u_long *";
			break;
		case 7:
			p = "u_long";
			break;
		default:
			break;
		};
		break;
	/* exchangedata */
	case 223:
		switch(ndx) {
		case 0:
			p = "userland const char *";
			break;
		case 1:
			p = "userland const char *";
			break;
		case 2:
			p = "u_long";
			break;
		default:
			break;
		};
		break;
	/* searchfs */
	case 225:
		switch(ndx) {
		case 0:
			p = "userland const char *";
			break;
		case 1:
			p = "userland struct fssearchblock *";
			break;
		case 2:
			p = "userland uint32_t *";
			break;
		case 3:
			p = "uint32_t";
			break;
		case 4:
			p = "uint32_t";
			break;
		case 5:
			p = "userland struct searchstate *";
			break;
		default:
			break;
		};
		break;
	/* delete */
	case 226:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* copyfile */
	case 227:
		switch(ndx) {
		case 0:
			p = "userland char *";
			break;
		case 1:
			p = "userland char *";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* fgetattrlist */
	case 228:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland struct attrlist *";
			break;
		case 2:
			p = "userland void *";
			break;
		case 3:
			p = "size_t";
			break;
		case 4:
			p = "u_long";
			break;
		default:
			break;
		};
		break;
	/* fsetattrlist */
	case 229:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland struct attrlist *";
			break;
		case 2:
			p = "userland void *";
			break;
		case 3:
			p = "size_t";
			break;
		case 4:
			p = "u_long";
			break;
		default:
			break;
		};
		break;
	/* poll */
	case 230:
		switch(ndx) {
		case 0:
			p = "userland struct pollfd *";
			break;
		case 1:
			p = "u_int";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* getxattr */
	case 234:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "user_addr_t";
			break;
		case 3:
			p = "size_t";
			break;
		case 4:
			p = "uint32_t";
			break;
		case 5:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* fgetxattr */
	case 235:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "user_addr_t";
			break;
		case 3:
			p = "size_t";
			break;
		case 4:
			p = "uint32_t";
			break;
		case 5:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* setxattr */
	case 236:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "user_addr_t";
			break;
		case 3:
			p = "size_t";
			break;
		case 4:
			p = "uint32_t";
			break;
		case 5:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* fsetxattr */
	case 237:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "user_addr_t";
			break;
		case 3:
			p = "size_t";
			break;
		case 4:
			p = "uint32_t";
			break;
		case 5:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* removexattr */
	case 238:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* fremovexattr */
	case 239:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* listxattr */
	case 240:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "size_t";
			break;
		case 3:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* flistxattr */
	case 241:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "size_t";
			break;
		case 3:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* fsctl */
	case 242:
		switch(ndx) {
		case 0:
			p = "userland const char *";
			break;
		case 1:
			p = "u_long";
			break;
		case 2:
			p = "caddr_t";
			break;
		case 3:
			p = "u_int";
			break;
		default:
			break;
		};
		break;
	/* initgroups */
	case 243:
		switch(ndx) {
		case 0:
			p = "u_int";
			break;
		case 1:
			p = "userland gid_t *";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* posix_spawn */
	case 244:
		switch(ndx) {
		case 0:
			p = "userland pid_t *";
			break;
		case 1:
			p = "userland const char *";
			break;
		case 2:
			p = "userland const struct _posix_spawn_args_desc *";
			break;
		case 3:
			p = "userland char **";
			break;
		case 4:
			p = "userland char **";
			break;
		default:
			break;
		};
		break;
	/* ffsctl */
	case 245:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "u_long";
			break;
		case 2:
			p = "caddr_t";
			break;
		case 3:
			p = "u_int";
			break;
		default:
			break;
		};
		break;
#if NFSCLIENT	/* XXX */
	/* nfsclnt */
	case 247:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "caddr_t";
			break;
		default:
			break;
		};
		break;
#else
#endif
#if NFSSERVER	/* XXX */
	/* fhopen */
	case 248:
		switch(ndx) {
		case 0:
			p = "userland const struct fhandle *";
			break;
		case 1:
			p = "int";
			break;
		default:
			break;
		};
		break;
#else
#endif
	/* minherit */
	case 250:
		switch(ndx) {
		case 0:
			p = "userland void *";
			break;
		case 1:
			p = "size_t";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
#if SYSV_SEM
	/* semsys */
	case 251:
		switch(ndx) {
		case 0:
			p = "u_int";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "int";
			break;
		case 4:
			p = "int";
			break;
		default:
			break;
		};
		break;
#else
#endif
#if SYSV_MSG
	/* msgsys */
	case 252:
		switch(ndx) {
		case 0:
			p = "u_int";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "int";
			break;
		case 4:
			p = "int";
			break;
		default:
			break;
		};
		break;
#else
#endif
#if SYSV_SHM
	/* shmsys */
	case 253:
		switch(ndx) {
		case 0:
			p = "u_int";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "int";
			break;
		default:
			break;
		};
		break;
#else
#endif
#if SYSV_SEM
	/* semctl */
	case 254:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "semun_t";
			break;
		default:
			break;
		};
		break;
	/* semget */
	case 255:
		switch(ndx) {
		case 0:
			p = "key_t";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* semop */
	case 256:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland struct sembuf *";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
#else
#endif
#if SYSV_MSG
	/* msgctl */
	case 258:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "userland struct msqid_ds *";
			break;
		default:
			break;
		};
		break;
	/* msgget */
	case 259:
		switch(ndx) {
		case 0:
			p = "key_t";
			break;
		case 1:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* msgsnd */
	case 260:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland void *";
			break;
		case 2:
			p = "size_t";
			break;
		case 3:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* msgrcv */
	case 261:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland void *";
			break;
		case 2:
			p = "size_t";
			break;
		case 3:
			p = "long";
			break;
		case 4:
			p = "int";
			break;
		default:
			break;
		};
		break;
#else
#endif
#if SYSV_SHM
	/* shmat */
	case 262:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland void *";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* shmctl */
	case 263:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "userland struct shmid_ds *";
			break;
		default:
			break;
		};
		break;
	/* shmdt */
	case 264:
		switch(ndx) {
		case 0:
			p = "userland void *";
			break;
		default:
			break;
		};
		break;
	/* shmget */
	case 265:
		switch(ndx) {
		case 0:
			p = "key_t";
			break;
		case 1:
			p = "size_t";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
#else
#endif
	/* shm_open */
	case 266:
		switch(ndx) {
		case 0:
			p = "userland const char *";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* shm_unlink */
	case 267:
		switch(ndx) {
		case 0:
			p = "userland const char *";
			break;
		default:
			break;
		};
		break;
	/* sem_open */
	case 268:
		switch(ndx) {
		case 0:
			p = "userland const char *";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* sem_close */
	case 269:
		switch(ndx) {
		case 0:
			p = "userland sem_t *";
			break;
		default:
			break;
		};
		break;
	/* sem_unlink */
	case 270:
		switch(ndx) {
		case 0:
			p = "userland const char *";
			break;
		default:
			break;
		};
		break;
	/* sem_wait */
	case 271:
		switch(ndx) {
		case 0:
			p = "userland sem_t *";
			break;
		default:
			break;
		};
		break;
	/* sem_trywait */
	case 272:
		switch(ndx) {
		case 0:
			p = "userland sem_t *";
			break;
		default:
			break;
		};
		break;
	/* sem_post */
	case 273:
		switch(ndx) {
		case 0:
			p = "userland sem_t *";
			break;
		default:
			break;
		};
		break;
	/* sys_sysctlbyname */
	case 274:
		switch(ndx) {
		case 0:
			p = "userland const char *";
			break;
		case 1:
			p = "size_t";
			break;
		case 2:
			p = "userland void *";
			break;
		case 3:
			p = "userland size_t *";
			break;
		case 4:
			p = "userland void *";
			break;
		case 5:
			p = "size_t";
			break;
		default:
			break;
		};
		break;
	/* open_extended */
	case 277:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "uid_t";
			break;
		case 3:
			p = "gid_t";
			break;
		case 4:
			p = "int";
			break;
		case 5:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* umask_extended */
	case 278:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* stat_extended */
	case 279:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "user_addr_t";
			break;
		case 3:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* lstat_extended */
	case 280:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "user_addr_t";
			break;
		case 3:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* sys_fstat_extended */
	case 281:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "user_addr_t";
			break;
		case 3:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* chmod_extended */
	case 282:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "uid_t";
			break;
		case 2:
			p = "gid_t";
			break;
		case 3:
			p = "int";
			break;
		case 4:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* fchmod_extended */
	case 283:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "uid_t";
			break;
		case 2:
			p = "gid_t";
			break;
		case 3:
			p = "int";
			break;
		case 4:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* access_extended */
	case 284:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "size_t";
			break;
		case 2:
			p = "user_addr_t";
			break;
		case 3:
			p = "uid_t";
			break;
		default:
			break;
		};
		break;
	/* settid */
	case 285:
		switch(ndx) {
		case 0:
			p = "uid_t";
			break;
		case 1:
			p = "gid_t";
			break;
		default:
			break;
		};
		break;
	/* gettid */
	case 286:
		switch(ndx) {
		case 0:
			p = "userland uid_t *";
			break;
		case 1:
			p = "userland gid_t *";
			break;
		default:
			break;
		};
		break;
	/* setsgroups */
	case 287:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* getsgroups */
	case 288:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* setwgroups */
	case 289:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* getwgroups */
	case 290:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* mkfifo_extended */
	case 291:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "uid_t";
			break;
		case 2:
			p = "gid_t";
			break;
		case 3:
			p = "int";
			break;
		case 4:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* mkdir_extended */
	case 292:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "uid_t";
			break;
		case 2:
			p = "gid_t";
			break;
		case 3:
			p = "int";
			break;
		case 4:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
#if CONFIG_EXT_RESOLVER
	/* identitysvc */
	case 293:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
#else
#endif
	/* shared_region_check_np */
	case 294:
		switch(ndx) {
		case 0:
			p = "userland uint64_t *";
			break;
		default:
			break;
		};
		break;
	/* vm_pressure_monitor */
	case 296:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "userland uint32_t *";
			break;
		default:
			break;
		};
		break;
#if PSYNCH
	/* psynch_rw_longrdlock */
	case 297:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "uint32_t";
			break;
		case 2:
			p = "uint32_t";
			break;
		case 3:
			p = "uint32_t";
			break;
		case 4:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* psynch_rw_yieldwrlock */
	case 298:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "uint32_t";
			break;
		case 2:
			p = "uint32_t";
			break;
		case 3:
			p = "uint32_t";
			break;
		case 4:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* psynch_rw_downgrade */
	case 299:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "uint32_t";
			break;
		case 2:
			p = "uint32_t";
			break;
		case 3:
			p = "uint32_t";
			break;
		case 4:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* psynch_rw_upgrade */
	case 300:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "uint32_t";
			break;
		case 2:
			p = "uint32_t";
			break;
		case 3:
			p = "uint32_t";
			break;
		case 4:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* psynch_mutexwait */
	case 301:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "uint32_t";
			break;
		case 2:
			p = "uint32_t";
			break;
		case 3:
			p = "uint64_t";
			break;
		case 4:
			p = "uint32_t";
			break;
		default:
			break;
		};
		break;
	/* psynch_mutexdrop */
	case 302:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "uint32_t";
			break;
		case 2:
			p = "uint32_t";
			break;
		case 3:
			p = "uint64_t";
			break;
		case 4:
			p = "uint32_t";
			break;
		default:
			break;
		};
		break;
	/* psynch_cvbroad */
	case 303:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "uint64_t";
			break;
		case 2:
			p = "uint64_t";
			break;
		case 3:
			p = "uint32_t";
			break;
		case 4:
			p = "user_addr_t";
			break;
		case 5:
			p = "uint64_t";
			break;
		case 6:
			p = "uint64_t";
			break;
		default:
			break;
		};
		break;
	/* psynch_cvsignal */
	case 304:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "uint64_t";
			break;
		case 2:
			p = "uint32_t";
			break;
		case 3:
			p = "int";
			break;
		case 4:
			p = "user_addr_t";
			break;
		case 5:
			p = "uint64_t";
			break;
		case 6:
			p = "uint64_t";
			break;
		case 7:
			p = "uint32_t";
			break;
		default:
			break;
		};
		break;
	/* psynch_cvwait */
	case 305:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "uint64_t";
			break;
		case 2:
			p = "uint32_t";
			break;
		case 3:
			p = "user_addr_t";
			break;
		case 4:
			p = "uint64_t";
			break;
		case 5:
			p = "uint32_t";
			break;
		case 6:
			p = "int64_t";
			break;
		case 7:
			p = "uint32_t";
			break;
		default:
			break;
		};
		break;
	/* psynch_rw_rdlock */
	case 306:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "uint32_t";
			break;
		case 2:
			p = "uint32_t";
			break;
		case 3:
			p = "uint32_t";
			break;
		case 4:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* psynch_rw_wrlock */
	case 307:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "uint32_t";
			break;
		case 2:
			p = "uint32_t";
			break;
		case 3:
			p = "uint32_t";
			break;
		case 4:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* psynch_rw_unlock */
	case 308:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "uint32_t";
			break;
		case 2:
			p = "uint32_t";
			break;
		case 3:
			p = "uint32_t";
			break;
		case 4:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* psynch_rw_unlock2 */
	case 309:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "uint32_t";
			break;
		case 2:
			p = "uint32_t";
			break;
		case 3:
			p = "uint32_t";
			break;
		case 4:
			p = "int";
			break;
		default:
			break;
		};
		break;
#else
#endif
	/* getsid */
	case 310:
		switch(ndx) {
		case 0:
			p = "pid_t";
			break;
		default:
			break;
		};
		break;
	/* settid_with_pid */
	case 311:
		switch(ndx) {
		case 0:
			p = "pid_t";
			break;
		case 1:
			p = "int";
			break;
		default:
			break;
		};
		break;
#if PSYNCH
	/* psynch_cvclrprepost */
	case 312:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "uint32_t";
			break;
		case 2:
			p = "uint32_t";
			break;
		case 3:
			p = "uint32_t";
			break;
		case 4:
			p = "uint32_t";
			break;
		case 5:
			p = "uint32_t";
			break;
		case 6:
			p = "uint32_t";
			break;
		default:
			break;
		};
		break;
#else
#endif
	/* aio_fsync */
	case 313:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* aio_return */
	case 314:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* aio_suspend */
	case 315:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* aio_cancel */
	case 316:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* aio_error */
	case 317:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* aio_read */
	case 318:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* aio_write */
	case 319:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* lio_listio */
	case 320:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* iopolicysys */
	case 322:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland void *";
			break;
		default:
			break;
		};
		break;
	/* process_policy */
	case 323:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "int";
			break;
		case 4:
			p = "user_addr_t";
			break;
		case 5:
			p = "pid_t";
			break;
		case 6:
			p = "uint64_t";
			break;
		default:
			break;
		};
		break;
	/* mlockall */
	case 324:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* munlockall */
	case 325:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* issetugid */
	case 327:
		break;
	/* __pthread_kill */
	case 328:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* __pthread_sigmask */
	case 329:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* __sigwait */
	case 330:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* __disable_threadsignal */
	case 331:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* __pthread_markcancel */
	case 332:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* __pthread_canceled */
	case 333:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* __semwait_signal */
	case 334:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "int";
			break;
		case 4:
			p = "int64_t";
			break;
		case 5:
			p = "int32_t";
			break;
		default:
			break;
		};
		break;
	/* proc_info */
	case 336:
		switch(ndx) {
		case 0:
			p = "int32_t";
			break;
		case 1:
			p = "int32_t";
			break;
		case 2:
			p = "uint32_t";
			break;
		case 3:
			p = "uint64_t";
			break;
		case 4:
			p = "user_addr_t";
			break;
		case 5:
			p = "int32_t";
			break;
		default:
			break;
		};
		break;
#if SENDFILE
	/* sendfile */
	case 337:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "off_t";
			break;
		case 3:
			p = "userland off_t *";
			break;
		case 4:
			p = "userland struct sf_hdtr *";
			break;
		case 5:
			p = "int";
			break;
		default:
			break;
		};
		break;
#else /* !SENDFILE */
#endif /* SENDFILE */
	/* stat64 */
	case 338:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* sys_fstat64 */
	case 339:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* lstat64 */
	case 340:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* stat64_extended */
	case 341:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "user_addr_t";
			break;
		case 3:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* lstat64_extended */
	case 342:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "user_addr_t";
			break;
		case 3:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* sys_fstat64_extended */
	case 343:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "user_addr_t";
			break;
		case 3:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* getdirentries64 */
	case 344:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland void *";
			break;
		case 2:
			p = "user_size_t";
			break;
		case 3:
			p = "userland off_t *";
			break;
		default:
			break;
		};
		break;
	/* statfs64 */
	case 345:
		switch(ndx) {
		case 0:
			p = "userland char *";
			break;
		case 1:
			p = "userland struct statfs64 *";
			break;
		default:
			break;
		};
		break;
	/* fstatfs64 */
	case 346:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland struct statfs64 *";
			break;
		default:
			break;
		};
		break;
	/* getfsstat64 */
	case 347:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* __pthread_chdir */
	case 348:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* __pthread_fchdir */
	case 349:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* audit */
	case 350:
		switch(ndx) {
		case 0:
			p = "userland void *";
			break;
		case 1:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* auditon */
	case 351:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland void *";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* getauid */
	case 353:
		switch(ndx) {
		case 0:
			p = "userland au_id_t *";
			break;
		default:
			break;
		};
		break;
	/* setauid */
	case 354:
		switch(ndx) {
		case 0:
			p = "userland au_id_t *";
			break;
		default:
			break;
		};
		break;
	/* getaudit_addr */
	case 357:
		switch(ndx) {
		case 0:
			p = "userland struct auditinfo_addr *";
			break;
		case 1:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* setaudit_addr */
	case 358:
		switch(ndx) {
		case 0:
			p = "userland struct auditinfo_addr *";
			break;
		case 1:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* auditctl */
	case 359:
		switch(ndx) {
		case 0:
			p = "userland char *";
			break;
		default:
			break;
		};
		break;
#if CONFIG_WORKQUEUE
	/* bsdthread_create */
	case 360:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "user_addr_t";
			break;
		case 3:
			p = "user_addr_t";
			break;
		case 4:
			p = "uint32_t";
			break;
		default:
			break;
		};
		break;
	/* bsdthread_terminate */
	case 361:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "size_t";
			break;
		case 2:
			p = "uint32_t";
			break;
		case 3:
			p = "uint32_t";
			break;
		default:
			break;
		};
		break;
#else
#endif /* CONFIG_WORKQUEUE */
	/* kqueue */
	case 362:
		break;
	/* kevent */
	case 363:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland const struct kevent *";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "userland struct kevent *";
			break;
		case 4:
			p = "int";
			break;
		case 5:
			p = "userland const struct timespec *";
			break;
		default:
			break;
		};
		break;
	/* lchown */
	case 364:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "uid_t";
			break;
		case 2:
			p = "gid_t";
			break;
		default:
			break;
		};
		break;
#if CONFIG_WORKQUEUE
	/* bsdthread_register */
	case 366:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "uint32_t";
			break;
		case 3:
			p = "user_addr_t";
			break;
		case 4:
			p = "user_addr_t";
			break;
		case 5:
			p = "uint32_t";
			break;
		case 6:
			p = "uint32_t";
			break;
		default:
			break;
		};
		break;
	/* workq_open */
	case 367:
		break;
	/* workq_kernreturn */
	case 368:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "int";
			break;
		default:
			break;
		};
		break;
#else
#endif /* CONFIG_WORKQUEUE */
	/* kevent64 */
	case 369:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland const struct kevent64_s *";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "userland struct kevent64_s *";
			break;
		case 4:
			p = "int";
			break;
		case 5:
			p = "unsigned int";
			break;
		case 6:
			p = "userland const struct timespec *";
			break;
		default:
			break;
		};
		break;
#if OLD_SEMWAIT_SIGNAL
	/* __old_semwait_signal */
	case 370:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "int";
			break;
		case 4:
			p = "userland const struct timespec *";
			break;
		default:
			break;
		};
		break;
	/* __old_semwait_signal_nocancel */
	case 371:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "int";
			break;
		case 4:
			p = "userland const struct timespec *";
			break;
		default:
			break;
		};
		break;
#else
#endif
	/* thread_selfid */
	case 372:
		break;
	/* ledger */
	case 373:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "caddr_t";
			break;
		case 2:
			p = "caddr_t";
			break;
		case 3:
			p = "caddr_t";
			break;
		default:
			break;
		};
		break;
	/* kevent_qos */
	case 374:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland const struct kevent_qos_s *";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "userland struct kevent_qos_s *";
			break;
		case 4:
			p = "int";
			break;
		case 5:
			p = "userland void *";
			break;
		case 6:
			p = "userland size_t *";
			break;
		case 7:
			p = "unsigned int";
			break;
		default:
			break;
		};
		break;
	/* kevent_id */
	case 375:
		switch(ndx) {
		case 0:
			p = "uint64_t";
			break;
		case 1:
			p = "userland const struct kevent_qos_s *";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "userland struct kevent_qos_s *";
			break;
		case 4:
			p = "int";
			break;
		case 5:
			p = "userland void *";
			break;
		case 6:
			p = "userland size_t *";
			break;
		case 7:
			p = "unsigned int";
			break;
		default:
			break;
		};
		break;
	/* __mac_execve */
	case 380:
		switch(ndx) {
		case 0:
			p = "userland char *";
			break;
		case 1:
			p = "userland char **";
			break;
		case 2:
			p = "userland char **";
			break;
		case 3:
			p = "userland struct mac *";
			break;
		default:
			break;
		};
		break;
#if CONFIG_MACF
	/* __mac_syscall */
	case 381:
		switch(ndx) {
		case 0:
			p = "userland char *";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* __mac_get_file */
	case 382:
		switch(ndx) {
		case 0:
			p = "userland char *";
			break;
		case 1:
			p = "userland struct mac *";
			break;
		default:
			break;
		};
		break;
	/* __mac_set_file */
	case 383:
		switch(ndx) {
		case 0:
			p = "userland char *";
			break;
		case 1:
			p = "userland struct mac *";
			break;
		default:
			break;
		};
		break;
	/* __mac_get_link */
	case 384:
		switch(ndx) {
		case 0:
			p = "userland char *";
			break;
		case 1:
			p = "userland struct mac *";
			break;
		default:
			break;
		};
		break;
	/* __mac_set_link */
	case 385:
		switch(ndx) {
		case 0:
			p = "userland char *";
			break;
		case 1:
			p = "userland struct mac *";
			break;
		default:
			break;
		};
		break;
	/* __mac_get_proc */
	case 386:
		switch(ndx) {
		case 0:
			p = "userland struct mac *";
			break;
		default:
			break;
		};
		break;
	/* __mac_set_proc */
	case 387:
		switch(ndx) {
		case 0:
			p = "userland struct mac *";
			break;
		default:
			break;
		};
		break;
	/* __mac_get_fd */
	case 388:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland struct mac *";
			break;
		default:
			break;
		};
		break;
	/* __mac_set_fd */
	case 389:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland struct mac *";
			break;
		default:
			break;
		};
		break;
	/* __mac_get_pid */
	case 390:
		switch(ndx) {
		case 0:
			p = "pid_t";
			break;
		case 1:
			p = "userland struct mac *";
			break;
		default:
			break;
		};
		break;
#else
#endif
	/* pselect */
	case 394:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland u_int32_t *";
			break;
		case 2:
			p = "userland u_int32_t *";
			break;
		case 3:
			p = "userland u_int32_t *";
			break;
		case 4:
			p = "userland const struct timespec *";
			break;
		case 5:
			p = "userland const struct sigset_t *";
			break;
		default:
			break;
		};
		break;
	/* pselect_nocancel */
	case 395:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland u_int32_t *";
			break;
		case 2:
			p = "userland u_int32_t *";
			break;
		case 3:
			p = "userland u_int32_t *";
			break;
		case 4:
			p = "userland const struct timespec *";
			break;
		case 5:
			p = "userland const struct sigset_t *";
			break;
		default:
			break;
		};
		break;
	/* read_nocancel */
	case 396:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "user_size_t";
			break;
		default:
			break;
		};
		break;
	/* write_nocancel */
	case 397:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "user_size_t";
			break;
		default:
			break;
		};
		break;
	/* open_nocancel */
	case 398:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* sys_close_nocancel */
	case 399:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* wait4_nocancel */
	case 400:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
#if SOCKETS
	/* recvmsg_nocancel */
	case 401:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland struct msghdr *";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* sendmsg_nocancel */
	case 402:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "caddr_t";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* recvfrom_nocancel */
	case 403:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland void *";
			break;
		case 2:
			p = "size_t";
			break;
		case 3:
			p = "int";
			break;
		case 4:
			p = "userland struct sockaddr *";
			break;
		case 5:
			p = "userland int *";
			break;
		default:
			break;
		};
		break;
	/* accept_nocancel */
	case 404:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "caddr_t";
			break;
		case 2:
			p = "userland socklen_t *";
			break;
		default:
			break;
		};
		break;
#else
#endif /* SOCKETS */
	/* msync_nocancel */
	case 405:
		switch(ndx) {
		case 0:
			p = "caddr_t";
			break;
		case 1:
			p = "size_t";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* sys_fcntl_nocancel */
	case 406:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "long";
			break;
		default:
			break;
		};
		break;
	/* select_nocancel */
	case 407:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland u_int32_t *";
			break;
		case 2:
			p = "userland u_int32_t *";
			break;
		case 3:
			p = "userland u_int32_t *";
			break;
		case 4:
			p = "userland struct timeval *";
			break;
		default:
			break;
		};
		break;
	/* fsync_nocancel */
	case 408:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		default:
			break;
		};
		break;
#if SOCKETS
	/* connect_nocancel */
	case 409:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "caddr_t";
			break;
		case 2:
			p = "socklen_t";
			break;
		default:
			break;
		};
		break;
#else
#endif /* SOCKETS */
	/* sigsuspend_nocancel */
	case 410:
		switch(ndx) {
		case 0:
			p = "sigset_t";
			break;
		default:
			break;
		};
		break;
	/* readv_nocancel */
	case 411:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland struct iovec *";
			break;
		case 2:
			p = "u_int";
			break;
		default:
			break;
		};
		break;
	/* writev_nocancel */
	case 412:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland struct iovec *";
			break;
		case 2:
			p = "u_int";
			break;
		default:
			break;
		};
		break;
#if SOCKETS
	/* sendto_nocancel */
	case 413:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "caddr_t";
			break;
		case 2:
			p = "size_t";
			break;
		case 3:
			p = "int";
			break;
		case 4:
			p = "caddr_t";
			break;
		case 5:
			p = "socklen_t";
			break;
		default:
			break;
		};
		break;
#else
#endif /* SOCKETS */
	/* pread_nocancel */
	case 414:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "user_size_t";
			break;
		case 3:
			p = "off_t";
			break;
		default:
			break;
		};
		break;
	/* pwrite_nocancel */
	case 415:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "user_size_t";
			break;
		case 3:
			p = "off_t";
			break;
		default:
			break;
		};
		break;
	/* waitid_nocancel */
	case 416:
		switch(ndx) {
		case 0:
			p = "idtype_t";
			break;
		case 1:
			p = "id_t";
			break;
		case 2:
			p = "userland siginfo_t *";
			break;
		case 3:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* poll_nocancel */
	case 417:
		switch(ndx) {
		case 0:
			p = "userland struct pollfd *";
			break;
		case 1:
			p = "u_int";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
#if SYSV_MSG
	/* msgsnd_nocancel */
	case 418:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland void *";
			break;
		case 2:
			p = "size_t";
			break;
		case 3:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* msgrcv_nocancel */
	case 419:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland void *";
			break;
		case 2:
			p = "size_t";
			break;
		case 3:
			p = "long";
			break;
		case 4:
			p = "int";
			break;
		default:
			break;
		};
		break;
#else
#endif
	/* sem_wait_nocancel */
	case 420:
		switch(ndx) {
		case 0:
			p = "userland sem_t *";
			break;
		default:
			break;
		};
		break;
	/* aio_suspend_nocancel */
	case 421:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* __sigwait_nocancel */
	case 422:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* __semwait_signal_nocancel */
	case 423:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "int";
			break;
		case 4:
			p = "int64_t";
			break;
		case 5:
			p = "int32_t";
			break;
		default:
			break;
		};
		break;
	/* __mac_mount */
	case 424:
		switch(ndx) {
		case 0:
			p = "userland char *";
			break;
		case 1:
			p = "userland char *";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "caddr_t";
			break;
		case 4:
			p = "userland struct mac *";
			break;
		default:
			break;
		};
		break;
#if CONFIG_MACF
	/* __mac_get_mount */
	case 425:
		switch(ndx) {
		case 0:
			p = "userland char *";
			break;
		case 1:
			p = "userland struct mac *";
			break;
		default:
			break;
		};
		break;
#else
#endif
	/* __mac_getfsstat */
	case 426:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "user_addr_t";
			break;
		case 3:
			p = "int";
			break;
		case 4:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* fsgetpath */
	case 427:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "size_t";
			break;
		case 2:
			p = "user_addr_t";
			break;
		case 3:
			p = "uint64_t";
			break;
		default:
			break;
		};
		break;
	/* audit_session_self */
	case 428:
		break;
	/* audit_session_join */
	case 429:
		switch(ndx) {
		case 0:
			p = "mach_port_name_t";
			break;
		default:
			break;
		};
		break;
	/* sys_fileport_makeport */
	case 430:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* sys_fileport_makefd */
	case 431:
		switch(ndx) {
		case 0:
			p = "mach_port_name_t";
			break;
		default:
			break;
		};
		break;
	/* audit_session_port */
	case 432:
		switch(ndx) {
		case 0:
			p = "au_asid_t";
			break;
		case 1:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* pid_suspend */
	case 433:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* pid_resume */
	case 434:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		default:
			break;
		};
		break;
#if CONFIG_EMBEDDED
	/* pid_hibernate */
	case 435:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		default:
			break;
		};
		break;
#else
#endif
#if SOCKETS
	/* pid_shutdown_sockets */
	case 436:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "int";
			break;
		default:
			break;
		};
		break;
#else
#endif
	/* shared_region_map_and_slide_np */
	case 438:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "uint32_t";
			break;
		case 2:
			p = "userland const struct shared_file_mapping_np *";
			break;
		case 3:
			p = "uint32_t";
			break;
		case 4:
			p = "userland uint64_t *";
			break;
		case 5:
			p = "uint32_t";
			break;
		default:
			break;
		};
		break;
	/* kas_info */
	case 439:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland void *";
			break;
		case 2:
			p = "userland size_t *";
			break;
		default:
			break;
		};
		break;
#if CONFIG_MEMORYSTATUS
	/* memorystatus_control */
	case 440:
		switch(ndx) {
		case 0:
			p = "uint32_t";
			break;
		case 1:
			p = "int32_t";
			break;
		case 2:
			p = "uint32_t";
			break;
		case 3:
			p = "user_addr_t";
			break;
		case 4:
			p = "size_t";
			break;
		default:
			break;
		};
		break;
#else
#endif
	/* guarded_open_np */
	case 441:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "userland const guardid_t *";
			break;
		case 2:
			p = "u_int";
			break;
		case 3:
			p = "int";
			break;
		case 4:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* guarded_close_np */
	case 442:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland const guardid_t *";
			break;
		default:
			break;
		};
		break;
	/* guarded_kqueue_np */
	case 443:
		switch(ndx) {
		case 0:
			p = "userland const guardid_t *";
			break;
		case 1:
			p = "u_int";
			break;
		default:
			break;
		};
		break;
	/* change_fdguard_np */
	case 444:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland const guardid_t *";
			break;
		case 2:
			p = "u_int";
			break;
		case 3:
			p = "userland const guardid_t *";
			break;
		case 4:
			p = "u_int";
			break;
		case 5:
			p = "userland int *";
			break;
		default:
			break;
		};
		break;
	/* usrctl */
	case 445:
		switch(ndx) {
		case 0:
			p = "uint32_t";
			break;
		default:
			break;
		};
		break;
	/* proc_rlimit_control */
	case 446:
		switch(ndx) {
		case 0:
			p = "pid_t";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "userland void *";
			break;
		default:
			break;
		};
		break;
#if SOCKETS
	/* connectx */
	case 447:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland const sa_endpoints_t *";
			break;
		case 2:
			p = "sae_associd_t";
			break;
		case 3:
			p = "unsigned int";
			break;
		case 4:
			p = "userland const struct iovec *";
			break;
		case 5:
			p = "unsigned int";
			break;
		case 6:
			p = "userland size_t *";
			break;
		case 7:
			p = "userland sae_connid_t *";
			break;
		default:
			break;
		};
		break;
	/* disconnectx */
	case 448:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "sae_associd_t";
			break;
		case 2:
			p = "sae_connid_t";
			break;
		default:
			break;
		};
		break;
	/* peeloff */
	case 449:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "sae_associd_t";
			break;
		default:
			break;
		};
		break;
	/* socket_delegate */
	case 450:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "pid_t";
			break;
		default:
			break;
		};
		break;
#else
#endif /* SOCKETS */
	/* telemetry */
	case 451:
		switch(ndx) {
		case 0:
			p = "uint64_t";
			break;
		case 1:
			p = "uint64_t";
			break;
		case 2:
			p = "uint64_t";
			break;
		case 3:
			p = "uint64_t";
			break;
		case 4:
			p = "uint64_t";
			break;
		case 5:
			p = "uint64_t";
			break;
		default:
			break;
		};
		break;
#if CONFIG_PROC_UUID_POLICY
	/* proc_uuid_policy */
	case 452:
		switch(ndx) {
		case 0:
			p = "uint32_t";
			break;
		case 1:
			p = "uuid_t";
			break;
		case 2:
			p = "size_t";
			break;
		case 3:
			p = "uint32_t";
			break;
		default:
			break;
		};
		break;
#else
#endif
#if CONFIG_MEMORYSTATUS
	/* memorystatus_get_level */
	case 453:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
#else
#endif
	/* system_override */
	case 454:
		switch(ndx) {
		case 0:
			p = "uint64_t";
			break;
		case 1:
			p = "uint64_t";
			break;
		default:
			break;
		};
		break;
	/* vfs_purge */
	case 455:
		break;
	/* sfi_ctl */
	case 456:
		switch(ndx) {
		case 0:
			p = "uint32_t";
			break;
		case 1:
			p = "uint32_t";
			break;
		case 2:
			p = "uint64_t";
			break;
		case 3:
			p = "userland uint64_t *";
			break;
		default:
			break;
		};
		break;
	/* sfi_pidctl */
	case 457:
		switch(ndx) {
		case 0:
			p = "uint32_t";
			break;
		case 1:
			p = "pid_t";
			break;
		case 2:
			p = "uint32_t";
			break;
		case 3:
			p = "userland uint32_t *";
			break;
		default:
			break;
		};
		break;
#if CONFIG_COALITIONS
	/* coalition */
	case 458:
		switch(ndx) {
		case 0:
			p = "uint32_t";
			break;
		case 1:
			p = "userland uint64_t *";
			break;
		case 2:
			p = "uint32_t";
			break;
		default:
			break;
		};
		break;
	/* coalition_info */
	case 459:
		switch(ndx) {
		case 0:
			p = "uint32_t";
			break;
		case 1:
			p = "userland uint64_t *";
			break;
		case 2:
			p = "userland void *";
			break;
		case 3:
			p = "userland size_t *";
			break;
		default:
			break;
		};
		break;
#else
#endif /* COALITIONS */
#if NECP
	/* necp_match_policy */
	case 460:
		switch(ndx) {
		case 0:
			p = "userland uint8_t *";
			break;
		case 1:
			p = "size_t";
			break;
		case 2:
			p = "userland struct necp_aggregate_result *";
			break;
		default:
			break;
		};
		break;
#else
#endif /* NECP */
	/* getattrlistbulk */
	case 461:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland struct attrlist *";
			break;
		case 2:
			p = "userland void *";
			break;
		case 3:
			p = "size_t";
			break;
		case 4:
			p = "uint64_t";
			break;
		default:
			break;
		};
		break;
	/* clonefileat */
	case 462:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "user_addr_t";
			break;
		case 4:
			p = "uint32_t";
			break;
		default:
			break;
		};
		break;
	/* openat */
	case 463:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* openat_nocancel */
	case 464:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* renameat */
	case 465:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland char *";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "userland char *";
			break;
		default:
			break;
		};
		break;
	/* faccessat */
	case 466:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* fchmodat */
	case 467:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* fchownat */
	case 468:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "uid_t";
			break;
		case 3:
			p = "gid_t";
			break;
		case 4:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* fstatat */
	case 469:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "user_addr_t";
			break;
		case 3:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* fstatat64 */
	case 470:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "user_addr_t";
			break;
		case 3:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* linkat */
	case 471:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "user_addr_t";
			break;
		case 4:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* unlinkat */
	case 472:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* readlinkat */
	case 473:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "user_addr_t";
			break;
		case 3:
			p = "size_t";
			break;
		default:
			break;
		};
		break;
	/* symlinkat */
	case 474:
		switch(ndx) {
		case 0:
			p = "userland user_addr_t *";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* mkdirat */
	case 475:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* getattrlistat */
	case 476:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland const char *";
			break;
		case 2:
			p = "userland struct attrlist *";
			break;
		case 3:
			p = "userland void *";
			break;
		case 4:
			p = "size_t";
			break;
		case 5:
			p = "u_long";
			break;
		default:
			break;
		};
		break;
	/* proc_trace_log */
	case 477:
		switch(ndx) {
		case 0:
			p = "pid_t";
			break;
		case 1:
			p = "uint64_t";
			break;
		default:
			break;
		};
		break;
	/* bsdthread_ctl */
	case 478:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "user_addr_t";
			break;
		case 3:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
	/* openbyid_np */
	case 479:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "int";
			break;
		default:
			break;
		};
		break;
#if SOCKETS
	/* recvmsg_x */
	case 480:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland struct msghdr_x *";
			break;
		case 2:
			p = "u_int";
			break;
		case 3:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* sendmsg_x */
	case 481:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland struct msghdr_x *";
			break;
		case 2:
			p = "u_int";
			break;
		case 3:
			p = "int";
			break;
		default:
			break;
		};
		break;
#else
#endif /* SOCKETS */
	/* thread_selfusage */
	case 482:
		break;
#if CONFIG_CSR
	/* csrctl */
	case 483:
		switch(ndx) {
		case 0:
			p = "uint32_t";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "user_addr_t";
			break;
		default:
			break;
		};
		break;
#else
#endif /* CSR */
	/* guarded_open_dprotected_np */
	case 484:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "userland const guardid_t *";
			break;
		case 2:
			p = "u_int";
			break;
		case 3:
			p = "int";
			break;
		case 4:
			p = "int";
			break;
		case 5:
			p = "int";
			break;
		case 6:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* guarded_write_np */
	case 485:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland const guardid_t *";
			break;
		case 2:
			p = "user_addr_t";
			break;
		case 3:
			p = "user_size_t";
			break;
		default:
			break;
		};
		break;
	/* guarded_pwrite_np */
	case 486:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland const guardid_t *";
			break;
		case 2:
			p = "user_addr_t";
			break;
		case 3:
			p = "user_size_t";
			break;
		case 4:
			p = "off_t";
			break;
		default:
			break;
		};
		break;
	/* guarded_writev_np */
	case 487:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland const guardid_t *";
			break;
		case 2:
			p = "userland struct iovec *";
			break;
		case 3:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* renameatx_np */
	case 488:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland char *";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "userland char *";
			break;
		case 4:
			p = "u_int";
			break;
		default:
			break;
		};
		break;
#if CONFIG_CODE_DECRYPTION
	/* mremap_encrypted */
	case 489:
		switch(ndx) {
		case 0:
			p = "caddr_t";
			break;
		case 1:
			p = "size_t";
			break;
		case 2:
			p = "uint32_t";
			break;
		case 3:
			p = "uint32_t";
			break;
		case 4:
			p = "uint32_t";
			break;
		default:
			break;
		};
		break;
#else
#endif
#if NETWORKING
	/* netagent_trigger */
	case 490:
		switch(ndx) {
		case 0:
			p = "uuid_t";
			break;
		case 1:
			p = "size_t";
			break;
		default:
			break;
		};
		break;
#else
#endif /* NETWORKING */
	/* stack_snapshot_with_config */
	case 491:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "user_addr_t";
			break;
		case 2:
			p = "size_t";
			break;
		default:
			break;
		};
		break;
#if CONFIG_TELEMETRY
	/* microstackshot */
	case 492:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "uint32_t";
			break;
		case 2:
			p = "uint32_t";
			break;
		default:
			break;
		};
		break;
#else
#endif /* CONFIG_TELEMETRY */
#if PGO
	/* grab_pgo_data */
	case 493:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "user_addr_t";
			break;
		case 3:
			p = "user_ssize_t";
			break;
		default:
			break;
		};
		break;
#else
#endif
#if CONFIG_PERSONAS
	/* persona */
	case 494:
		switch(ndx) {
		case 0:
			p = "uint32_t";
			break;
		case 1:
			p = "uint32_t";
			break;
		case 2:
			p = "userland struct kpersona_info *";
			break;
		case 3:
			p = "userland uid_t *";
			break;
		case 4:
			p = "userland size_t *";
			break;
		case 5:
			p = "userland char *";
			break;
		default:
			break;
		};
		break;
#else
#endif
	/* mach_eventlink_signal */
	case 496:
		switch(ndx) {
		case 0:
			p = "mach_port_name_t";
			break;
		case 1:
			p = "uint64_t";
			break;
		default:
			break;
		};
		break;
	/* mach_eventlink_wait_until */
	case 497:
		switch(ndx) {
		case 0:
			p = "mach_port_name_t";
			break;
		case 1:
			p = "uint64_t";
			break;
		case 2:
			p = "uint64_t";
			break;
		case 3:
			p = "uint32_t";
			break;
		case 4:
			p = "uint32_t";
			break;
		default:
			break;
		};
		break;
	/* mach_eventlink_signal_wait_until */
	case 498:
		switch(ndx) {
		case 0:
			p = "mach_port_name_t";
			break;
		case 1:
			p = "uint64_t";
			break;
		case 2:
			p = "uint64_t";
			break;
		case 3:
			p = "uint64_t";
			break;
		case 4:
			p = "uint32_t";
			break;
		case 5:
			p = "uint32_t";
			break;
		default:
			break;
		};
		break;
	/* work_interval_ctl */
	case 499:
		switch(ndx) {
		case 0:
			p = "uint32_t";
			break;
		case 1:
			p = "uint64_t";
			break;
		case 2:
			p = "userland void *";
			break;
		case 3:
			p = "size_t";
			break;
		default:
			break;
		};
		break;
	/* getentropy */
	case 500:
		switch(ndx) {
		case 0:
			p = "userland void *";
			break;
		case 1:
			p = "size_t";
			break;
		default:
			break;
		};
		break;
#if NECP
	/* necp_open */
	case 501:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* necp_client_action */
	case 502:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "uint32_t";
			break;
		case 2:
			p = "uuid_t";
			break;
		case 3:
			p = "size_t";
			break;
		case 4:
			p = "userland uint8_t *";
			break;
		case 5:
			p = "size_t";
			break;
		default:
			break;
		};
		break;
#else
#endif /* NECP */
	/* ulock_wait */
	case 515:
		switch(ndx) {
		case 0:
			p = "uint32_t";
			break;
		case 1:
			p = "userland void *";
			break;
		case 2:
			p = "uint64_t";
			break;
		case 3:
			p = "uint32_t";
			break;
		default:
			break;
		};
		break;
	/* ulock_wake */
	case 516:
		switch(ndx) {
		case 0:
			p = "uint32_t";
			break;
		case 1:
			p = "userland void *";
			break;
		case 2:
			p = "uint64_t";
			break;
		default:
			break;
		};
		break;
	/* fclonefileat */
	case 517:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "user_addr_t";
			break;
		case 3:
			p = "uint32_t";
			break;
		default:
			break;
		};
		break;
	/* fs_snapshot */
	case 518:
		switch(ndx) {
		case 0:
			p = "uint32_t";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "user_addr_t";
			break;
		case 3:
			p = "user_addr_t";
			break;
		case 4:
			p = "user_addr_t";
			break;
		case 5:
			p = "uint32_t";
			break;
		default:
			break;
		};
		break;
	/* terminate_with_payload */
	case 520:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "uint32_t";
			break;
		case 2:
			p = "uint64_t";
			break;
		case 3:
			p = "userland void *";
			break;
		case 4:
			p = "uint32_t";
			break;
		case 5:
			p = "userland const char *";
			break;
		case 6:
			p = "uint64_t";
			break;
		default:
			break;
		};
		break;
	/* abort_with_payload */
	case 521:
		switch(ndx) {
		case 0:
			p = "uint32_t";
			break;
		case 1:
			p = "uint64_t";
			break;
		case 2:
			p = "userland void *";
			break;
		case 3:
			p = "uint32_t";
			break;
		case 4:
			p = "userland const char *";
			break;
		case 5:
			p = "uint64_t";
			break;
		default:
			break;
		};
		break;
#if NECP
	/* necp_session_open */
	case 522:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		default:
			break;
		};
		break;
	/* necp_session_action */
	case 523:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "uint32_t";
			break;
		case 2:
			p = "userland uint8_t *";
			break;
		case 3:
			p = "size_t";
			break;
		case 4:
			p = "userland uint8_t *";
			break;
		case 5:
			p = "size_t";
			break;
		default:
			break;
		};
		break;
#else /* NECP */
#endif /* NECP */
	/* setattrlistat */
	case 524:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland const char *";
			break;
		case 2:
			p = "userland struct attrlist *";
			break;
		case 3:
			p = "userland void *";
			break;
		case 4:
			p = "size_t";
			break;
		case 5:
			p = "uint32_t";
			break;
		default:
			break;
		};
		break;
	/* net_qos_guideline */
	case 525:
		switch(ndx) {
		case 0:
			p = "userland struct net_qos_param *";
			break;
		case 1:
			p = "uint32_t";
			break;
		default:
			break;
		};
		break;
	/* fmount */
	case 526:
		switch(ndx) {
		case 0:
			p = "userland const char *";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "userland void *";
			break;
		default:
			break;
		};
		break;
	/* ntp_adjtime */
	case 527:
		switch(ndx) {
		case 0:
			p = "userland struct timex *";
			break;
		default:
			break;
		};
		break;
	/* ntp_gettime */
	case 528:
		switch(ndx) {
		case 0:
			p = "userland struct ntptimeval *";
			break;
		default:
			break;
		};
		break;
	/* os_fault_with_payload */
	case 529:
		switch(ndx) {
		case 0:
			p = "uint32_t";
			break;
		case 1:
			p = "uint64_t";
			break;
		case 2:
			p = "userland void *";
			break;
		case 3:
			p = "uint32_t";
			break;
		case 4:
			p = "userland const char *";
			break;
		case 5:
			p = "uint64_t";
			break;
		default:
			break;
		};
		break;
#if CONFIG_WORKQUEUE
	/* kqueue_workloop_ctl */
	case 530:
		switch(ndx) {
		case 0:
			p = "user_addr_t";
			break;
		case 1:
			p = "uint64_t";
			break;
		case 2:
			p = "user_addr_t";
			break;
		case 3:
			p = "size_t";
			break;
		default:
			break;
		};
		break;
#else
#endif // CONFIG_WORKQUEUE
	/* __mach_bridge_remote_time */
	case 531:
		switch(ndx) {
		case 0:
			p = "uint64_t";
			break;
		default:
			break;
		};
		break;
#if CONFIG_COALITIONS
	/* coalition_ledger */
	case 532:
		switch(ndx) {
		case 0:
			p = "uint32_t";
			break;
		case 1:
			p = "userland uint64_t *";
			break;
		case 2:
			p = "userland void *";
			break;
		case 3:
			p = "userland size_t *";
			break;
		default:
			break;
		};
		break;
#else
#endif // CONFIG_COALITIONS
	/* log_data */
	case 533:
		switch(ndx) {
		case 0:
			p = "unsigned int";
			break;
		case 1:
			p = "unsigned int";
			break;
		case 2:
			p = "userland void *";
			break;
		case 3:
			p = "unsigned int";
			break;
		default:
			break;
		};
		break;
	/* memorystatus_available_memory */
	case 534:
		break;
	/* shared_region_map_and_slide_2_np */
	case 536:
		switch(ndx) {
		case 0:
			p = "uint32_t";
			break;
		case 1:
			p = "userland const struct shared_file_np *";
			break;
		case 2:
			p = "uint32_t";
			break;
		case 3:
			p = "userland const struct shared_file_mapping_slide_np *";
			break;
		default:
			break;
		};
		break;
	/* pivot_root */
	case 537:
		switch(ndx) {
		case 0:
			p = "userland const char *";
			break;
		case 1:
			p = "userland const char *";
			break;
		default:
			break;
		};
		break;
	/* task_inspect_for_pid */
	case 538:
		switch(ndx) {
		case 0:
			p = "mach_port_name_t";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "userland mach_port_name_t *";
			break;
		default:
			break;
		};
		break;
	/* task_read_for_pid */
	case 539:
		switch(ndx) {
		case 0:
			p = "mach_port_name_t";
			break;
		case 1:
			p = "int";
			break;
		case 2:
			p = "userland mach_port_name_t *";
			break;
		default:
			break;
		};
		break;
	/* sys_preadv */
	case 540:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland struct iovec *";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "off_t";
			break;
		default:
			break;
		};
		break;
	/* sys_pwritev */
	case 541:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland struct iovec *";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "off_t";
			break;
		default:
			break;
		};
		break;
	/* sys_preadv_nocancel */
	case 542:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland struct iovec *";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "off_t";
			break;
		default:
			break;
		};
		break;
	/* sys_pwritev_nocancel */
	case 543:
		switch(ndx) {
		case 0:
			p = "int";
			break;
		case 1:
			p = "userland struct iovec *";
			break;
		case 2:
			p = "int";
			break;
		case 3:
			p = "off_t";
			break;
		default:
			break;
		};
		break;
	/* ulock_wait2 */
	case 544:
		switch(ndx) {
		case 0:
			p = "uint32_t";
			break;
		case 1:
			p = "userland void *";
			break;
		case 2:
			p = "uint64_t";
			break;
		case 3:
			p = "uint64_t";
			break;
		case 4:
			p = "uint64_t";
			break;
		default:
			break;
		};
		break;
	/* proc_info_extended_id */
	case 545:
		switch(ndx) {
		case 0:
			p = "int32_t";
			break;
		case 1:
			p = "int32_t";
			break;
		case 2:
			p = "uint32_t";
			break;
		case 3:
			p = "uint32_t";
			break;
		case 4:
			p = "uint64_t";
			break;
		case 5:
			p = "uint64_t";
			break;
		case 6:
			p = "user_addr_t";
			break;
		case 7:
			p = "int32_t";
			break;
		default:
			break;
		};
		break;
	default:
		break;
	};
	if (p != NULL)
		strlcpy(desc, p, descsz);
}
void
systrace_return_setargdesc(int sysnum, int ndx, char *desc, size_t descsz)
{
	const char *p = NULL;
	switch (sysnum) {
	/* nosys */
	case 0:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* exit */
	case 1:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* fork */
	case 2:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* read */
	case 3:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
	/* write */
	case 4:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
	/* open */
	case 5:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sys_close */
	case 6:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* wait4 */
	case 7:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* link */
	case 9:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* unlink */
	case 10:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* chdir */
	case 12:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* fchdir */
	case 13:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* mknod */
	case 14:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* chmod */
	case 15:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* chown */
	case 16:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* getfsstat */
	case 18:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* getpid */
	case 20:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* setuid */
	case 23:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* getuid */
	case 24:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* geteuid */
	case 25:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* ptrace */
	case 26:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#if SOCKETS
	/* recvmsg */
	case 27:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sendmsg */
	case 28:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* recvfrom */
	case 29:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* accept */
	case 30:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* getpeername */
	case 31:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* getsockname */
	case 32:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif /* SOCKETS */
	/* access */
	case 33:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* chflags */
	case 34:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* fchflags */
	case 35:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sync */
	case 36:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* kill */
	case 37:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* getppid */
	case 39:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sys_dup */
	case 41:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* pipe */
	case 42:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* getegid */
	case 43:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sigaction */
	case 46:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* getgid */
	case 47:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sigprocmask */
	case 48:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* getlogin */
	case 49:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* setlogin */
	case 50:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* acct */
	case 51:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sigpending */
	case 52:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sigaltstack */
	case 53:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* ioctl */
	case 54:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* reboot */
	case 55:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* revoke */
	case 56:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* symlink */
	case 57:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* readlink */
	case 58:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* execve */
	case 59:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* umask */
	case 60:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* chroot */
	case 61:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* msync */
	case 65:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* vfork */
	case 66:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* munmap */
	case 73:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* mprotect */
	case 74:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* madvise */
	case 75:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* mincore */
	case 78:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* getgroups */
	case 79:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* setgroups */
	case 80:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* getpgrp */
	case 81:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* setpgid */
	case 82:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* setitimer */
	case 83:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* swapon */
	case 85:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* getitimer */
	case 86:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sys_getdtablesize */
	case 89:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sys_dup2 */
	case 90:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sys_fcntl */
	case 92:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* select */
	case 93:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* fsync */
	case 95:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* setpriority */
	case 96:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#if SOCKETS
	/* socket */
	case 97:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* connect */
	case 98:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif /* SOCKETS */
	/* getpriority */
	case 100:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#if SOCKETS
	/* bind */
	case 104:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* setsockopt */
	case 105:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* listen */
	case 106:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif /* SOCKETS */
	/* sigsuspend */
	case 111:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#if SOCKETS
#else
#endif /* SOCKETS */
	/* gettimeofday */
	case 116:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* getrusage */
	case 117:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#if SOCKETS
	/* getsockopt */
	case 118:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif /* SOCKETS */
	/* readv */
	case 120:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
	/* writev */
	case 121:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
	/* settimeofday */
	case 122:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* fchown */
	case 123:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* fchmod */
	case 124:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* setreuid */
	case 126:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* setregid */
	case 127:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* rename */
	case 128:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sys_flock */
	case 131:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* mkfifo */
	case 132:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#if SOCKETS
	/* sendto */
	case 133:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* shutdown */
	case 134:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* socketpair */
	case 135:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif /* SOCKETS */
	/* mkdir */
	case 136:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* rmdir */
	case 137:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* utimes */
	case 138:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* futimes */
	case 139:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* adjtime */
	case 140:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* gethostuuid */
	case 142:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* setsid */
	case 147:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* getpgid */
	case 151:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* setprivexec */
	case 152:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* pread */
	case 153:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
	/* pwrite */
	case 154:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
#if NFSSERVER	/* XXX */
	/* nfssvc */
	case 155:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif
	/* statfs */
	case 157:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* fstatfs */
	case 158:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* unmount */
	case 159:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#if NFSSERVER	/* XXX */
	/* getfh */
	case 161:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif
	/* quotactl */
	case 165:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* mount */
	case 167:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* csops */
	case 169:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* csops_audittoken */
	case 170:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* waitid */
	case 173:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* kdebug_typefilter */
	case 177:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* kdebug_trace_string */
	case 178:
		if (ndx == 0 || ndx == 1)
			p = "uint64_t";
		break;
	/* kdebug_trace64 */
	case 179:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* kdebug_trace */
	case 180:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* setgid */
	case 181:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* setegid */
	case 182:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* seteuid */
	case 183:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sigreturn */
	case 184:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* thread_selfcounts */
	case 186:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* fdatasync */
	case 187:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* stat */
	case 188:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sys_fstat */
	case 189:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* lstat */
	case 190:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* pathconf */
	case 191:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sys_fpathconf */
	case 192:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* getrlimit */
	case 194:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* setrlimit */
	case 195:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* getdirentries */
	case 196:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* mmap */
	case 197:
		if (ndx == 0 || ndx == 1)
			p = "user_addr_t";
		break;
	/* lseek */
	case 199:
		if (ndx == 0 || ndx == 1)
			p = "off_t";
		break;
	/* truncate */
	case 200:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* ftruncate */
	case 201:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sysctl */
	case 202:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* mlock */
	case 203:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* munlock */
	case 204:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* undelete */
	case 205:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* open_dprotected_np */
	case 216:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* fsgetpath_ext */
	case 217:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
	/* getattrlist */
	case 220:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* setattrlist */
	case 221:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* getdirentriesattr */
	case 222:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* exchangedata */
	case 223:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* searchfs */
	case 225:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* delete */
	case 226:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* copyfile */
	case 227:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* fgetattrlist */
	case 228:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* fsetattrlist */
	case 229:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* poll */
	case 230:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* getxattr */
	case 234:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
	/* fgetxattr */
	case 235:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
	/* setxattr */
	case 236:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* fsetxattr */
	case 237:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* removexattr */
	case 238:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* fremovexattr */
	case 239:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* listxattr */
	case 240:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
	/* flistxattr */
	case 241:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
	/* fsctl */
	case 242:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* initgroups */
	case 243:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* posix_spawn */
	case 244:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* ffsctl */
	case 245:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#if NFSCLIENT	/* XXX */
	/* nfsclnt */
	case 247:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif
#if NFSSERVER	/* XXX */
	/* fhopen */
	case 248:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif
	/* minherit */
	case 250:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#if SYSV_SEM
	/* semsys */
	case 251:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif
#if SYSV_MSG
	/* msgsys */
	case 252:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif
#if SYSV_SHM
	/* shmsys */
	case 253:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif
#if SYSV_SEM
	/* semctl */
	case 254:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* semget */
	case 255:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* semop */
	case 256:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif
#if SYSV_MSG
	/* msgctl */
	case 258:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* msgget */
	case 259:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* msgsnd */
	case 260:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* msgrcv */
	case 261:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
#else
#endif
#if SYSV_SHM
	/* shmat */
	case 262:
		if (ndx == 0 || ndx == 1)
			p = "user_addr_t";
		break;
	/* shmctl */
	case 263:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* shmdt */
	case 264:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* shmget */
	case 265:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif
	/* shm_open */
	case 266:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* shm_unlink */
	case 267:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sem_open */
	case 268:
		if (ndx == 0 || ndx == 1)
			p = "user_addr_t";
		break;
	/* sem_close */
	case 269:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sem_unlink */
	case 270:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sem_wait */
	case 271:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sem_trywait */
	case 272:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sem_post */
	case 273:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sys_sysctlbyname */
	case 274:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* open_extended */
	case 277:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* umask_extended */
	case 278:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* stat_extended */
	case 279:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* lstat_extended */
	case 280:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sys_fstat_extended */
	case 281:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* chmod_extended */
	case 282:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* fchmod_extended */
	case 283:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* access_extended */
	case 284:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* settid */
	case 285:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* gettid */
	case 286:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* setsgroups */
	case 287:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* getsgroups */
	case 288:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* setwgroups */
	case 289:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* getwgroups */
	case 290:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* mkfifo_extended */
	case 291:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* mkdir_extended */
	case 292:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#if CONFIG_EXT_RESOLVER
	/* identitysvc */
	case 293:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif
	/* shared_region_check_np */
	case 294:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* vm_pressure_monitor */
	case 296:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#if PSYNCH
	/* psynch_rw_longrdlock */
	case 297:
		if (ndx == 0 || ndx == 1)
			p = "uint32_t";
		break;
	/* psynch_rw_yieldwrlock */
	case 298:
		if (ndx == 0 || ndx == 1)
			p = "uint32_t";
		break;
	/* psynch_rw_downgrade */
	case 299:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* psynch_rw_upgrade */
	case 300:
		if (ndx == 0 || ndx == 1)
			p = "uint32_t";
		break;
	/* psynch_mutexwait */
	case 301:
		if (ndx == 0 || ndx == 1)
			p = "uint32_t";
		break;
	/* psynch_mutexdrop */
	case 302:
		if (ndx == 0 || ndx == 1)
			p = "uint32_t";
		break;
	/* psynch_cvbroad */
	case 303:
		if (ndx == 0 || ndx == 1)
			p = "uint32_t";
		break;
	/* psynch_cvsignal */
	case 304:
		if (ndx == 0 || ndx == 1)
			p = "uint32_t";
		break;
	/* psynch_cvwait */
	case 305:
		if (ndx == 0 || ndx == 1)
			p = "uint32_t";
		break;
	/* psynch_rw_rdlock */
	case 306:
		if (ndx == 0 || ndx == 1)
			p = "uint32_t";
		break;
	/* psynch_rw_wrlock */
	case 307:
		if (ndx == 0 || ndx == 1)
			p = "uint32_t";
		break;
	/* psynch_rw_unlock */
	case 308:
		if (ndx == 0 || ndx == 1)
			p = "uint32_t";
		break;
	/* psynch_rw_unlock2 */
	case 309:
		if (ndx == 0 || ndx == 1)
			p = "uint32_t";
		break;
#else
#endif
	/* getsid */
	case 310:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* settid_with_pid */
	case 311:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#if PSYNCH
	/* psynch_cvclrprepost */
	case 312:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif
	/* aio_fsync */
	case 313:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* aio_return */
	case 314:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
	/* aio_suspend */
	case 315:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* aio_cancel */
	case 316:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* aio_error */
	case 317:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* aio_read */
	case 318:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* aio_write */
	case 319:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* lio_listio */
	case 320:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* iopolicysys */
	case 322:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* process_policy */
	case 323:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* mlockall */
	case 324:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* munlockall */
	case 325:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* issetugid */
	case 327:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* __pthread_kill */
	case 328:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* __pthread_sigmask */
	case 329:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* __sigwait */
	case 330:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* __disable_threadsignal */
	case 331:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* __pthread_markcancel */
	case 332:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* __pthread_canceled */
	case 333:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* __semwait_signal */
	case 334:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* proc_info */
	case 336:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#if SENDFILE
	/* sendfile */
	case 337:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else /* !SENDFILE */
#endif /* SENDFILE */
	/* stat64 */
	case 338:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sys_fstat64 */
	case 339:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* lstat64 */
	case 340:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* stat64_extended */
	case 341:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* lstat64_extended */
	case 342:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sys_fstat64_extended */
	case 343:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* getdirentries64 */
	case 344:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
	/* statfs64 */
	case 345:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* fstatfs64 */
	case 346:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* getfsstat64 */
	case 347:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* __pthread_chdir */
	case 348:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* __pthread_fchdir */
	case 349:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* audit */
	case 350:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* auditon */
	case 351:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* getauid */
	case 353:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* setauid */
	case 354:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* getaudit_addr */
	case 357:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* setaudit_addr */
	case 358:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* auditctl */
	case 359:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#if CONFIG_WORKQUEUE
	/* bsdthread_create */
	case 360:
		if (ndx == 0 || ndx == 1)
			p = "user_addr_t";
		break;
	/* bsdthread_terminate */
	case 361:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif /* CONFIG_WORKQUEUE */
	/* kqueue */
	case 362:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* kevent */
	case 363:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* lchown */
	case 364:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#if CONFIG_WORKQUEUE
	/* bsdthread_register */
	case 366:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* workq_open */
	case 367:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* workq_kernreturn */
	case 368:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif /* CONFIG_WORKQUEUE */
	/* kevent64 */
	case 369:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#if OLD_SEMWAIT_SIGNAL
	/* __old_semwait_signal */
	case 370:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* __old_semwait_signal_nocancel */
	case 371:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif
	/* thread_selfid */
	case 372:
		if (ndx == 0 || ndx == 1)
			p = "uint64_t";
		break;
	/* ledger */
	case 373:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* kevent_qos */
	case 374:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* kevent_id */
	case 375:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* __mac_execve */
	case 380:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#if CONFIG_MACF
	/* __mac_syscall */
	case 381:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* __mac_get_file */
	case 382:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* __mac_set_file */
	case 383:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* __mac_get_link */
	case 384:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* __mac_set_link */
	case 385:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* __mac_get_proc */
	case 386:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* __mac_set_proc */
	case 387:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* __mac_get_fd */
	case 388:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* __mac_set_fd */
	case 389:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* __mac_get_pid */
	case 390:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif
	/* pselect */
	case 394:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* pselect_nocancel */
	case 395:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* read_nocancel */
	case 396:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
	/* write_nocancel */
	case 397:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
	/* open_nocancel */
	case 398:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sys_close_nocancel */
	case 399:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* wait4_nocancel */
	case 400:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#if SOCKETS
	/* recvmsg_nocancel */
	case 401:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sendmsg_nocancel */
	case 402:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* recvfrom_nocancel */
	case 403:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* accept_nocancel */
	case 404:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif /* SOCKETS */
	/* msync_nocancel */
	case 405:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sys_fcntl_nocancel */
	case 406:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* select_nocancel */
	case 407:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* fsync_nocancel */
	case 408:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#if SOCKETS
	/* connect_nocancel */
	case 409:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif /* SOCKETS */
	/* sigsuspend_nocancel */
	case 410:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* readv_nocancel */
	case 411:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
	/* writev_nocancel */
	case 412:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
#if SOCKETS
	/* sendto_nocancel */
	case 413:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif /* SOCKETS */
	/* pread_nocancel */
	case 414:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
	/* pwrite_nocancel */
	case 415:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
	/* waitid_nocancel */
	case 416:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* poll_nocancel */
	case 417:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#if SYSV_MSG
	/* msgsnd_nocancel */
	case 418:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* msgrcv_nocancel */
	case 419:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
#else
#endif
	/* sem_wait_nocancel */
	case 420:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* aio_suspend_nocancel */
	case 421:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* __sigwait_nocancel */
	case 422:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* __semwait_signal_nocancel */
	case 423:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* __mac_mount */
	case 424:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#if CONFIG_MACF
	/* __mac_get_mount */
	case 425:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif
	/* __mac_getfsstat */
	case 426:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* fsgetpath */
	case 427:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
	/* audit_session_self */
	case 428:
		if (ndx == 0 || ndx == 1)
			p = "mach_port_name_t";
		break;
	/* audit_session_join */
	case 429:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sys_fileport_makeport */
	case 430:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sys_fileport_makefd */
	case 431:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* audit_session_port */
	case 432:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* pid_suspend */
	case 433:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* pid_resume */
	case 434:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#if CONFIG_EMBEDDED
	/* pid_hibernate */
	case 435:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif
#if SOCKETS
	/* pid_shutdown_sockets */
	case 436:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif
	/* shared_region_map_and_slide_np */
	case 438:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* kas_info */
	case 439:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#if CONFIG_MEMORYSTATUS
	/* memorystatus_control */
	case 440:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif
	/* guarded_open_np */
	case 441:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* guarded_close_np */
	case 442:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* guarded_kqueue_np */
	case 443:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* change_fdguard_np */
	case 444:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* usrctl */
	case 445:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* proc_rlimit_control */
	case 446:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#if SOCKETS
	/* connectx */
	case 447:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* disconnectx */
	case 448:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* peeloff */
	case 449:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* socket_delegate */
	case 450:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif /* SOCKETS */
	/* telemetry */
	case 451:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#if CONFIG_PROC_UUID_POLICY
	/* proc_uuid_policy */
	case 452:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif
#if CONFIG_MEMORYSTATUS
	/* memorystatus_get_level */
	case 453:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif
	/* system_override */
	case 454:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* vfs_purge */
	case 455:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sfi_ctl */
	case 456:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sfi_pidctl */
	case 457:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#if CONFIG_COALITIONS
	/* coalition */
	case 458:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* coalition_info */
	case 459:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif /* COALITIONS */
#if NECP
	/* necp_match_policy */
	case 460:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif /* NECP */
	/* getattrlistbulk */
	case 461:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* clonefileat */
	case 462:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* openat */
	case 463:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* openat_nocancel */
	case 464:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* renameat */
	case 465:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* faccessat */
	case 466:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* fchmodat */
	case 467:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* fchownat */
	case 468:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* fstatat */
	case 469:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* fstatat64 */
	case 470:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* linkat */
	case 471:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* unlinkat */
	case 472:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* readlinkat */
	case 473:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* symlinkat */
	case 474:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* mkdirat */
	case 475:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* getattrlistat */
	case 476:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* proc_trace_log */
	case 477:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* bsdthread_ctl */
	case 478:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* openbyid_np */
	case 479:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#if SOCKETS
	/* recvmsg_x */
	case 480:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
	/* sendmsg_x */
	case 481:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
#else
#endif /* SOCKETS */
	/* thread_selfusage */
	case 482:
		if (ndx == 0 || ndx == 1)
			p = "uint64_t";
		break;
#if CONFIG_CSR
	/* csrctl */
	case 483:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif /* CSR */
	/* guarded_open_dprotected_np */
	case 484:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* guarded_write_np */
	case 485:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
	/* guarded_pwrite_np */
	case 486:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
	/* guarded_writev_np */
	case 487:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
	/* renameatx_np */
	case 488:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#if CONFIG_CODE_DECRYPTION
	/* mremap_encrypted */
	case 489:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif
#if NETWORKING
	/* netagent_trigger */
	case 490:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif /* NETWORKING */
	/* stack_snapshot_with_config */
	case 491:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#if CONFIG_TELEMETRY
	/* microstackshot */
	case 492:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif /* CONFIG_TELEMETRY */
#if PGO
	/* grab_pgo_data */
	case 493:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
#else
#endif
#if CONFIG_PERSONAS
	/* persona */
	case 494:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif
	/* mach_eventlink_signal */
	case 496:
		if (ndx == 0 || ndx == 1)
			p = "uint64_t";
		break;
	/* mach_eventlink_wait_until */
	case 497:
		if (ndx == 0 || ndx == 1)
			p = "uint64_t";
		break;
	/* mach_eventlink_signal_wait_until */
	case 498:
		if (ndx == 0 || ndx == 1)
			p = "uint64_t";
		break;
	/* work_interval_ctl */
	case 499:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* getentropy */
	case 500:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#if NECP
	/* necp_open */
	case 501:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* necp_client_action */
	case 502:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif /* NECP */
	/* ulock_wait */
	case 515:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* ulock_wake */
	case 516:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* fclonefileat */
	case 517:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* fs_snapshot */
	case 518:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* terminate_with_payload */
	case 520:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* abort_with_payload */
	case 521:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
#if NECP
	/* necp_session_open */
	case 522:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* necp_session_action */
	case 523:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else /* NECP */
#endif /* NECP */
	/* setattrlistat */
	case 524:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* net_qos_guideline */
	case 525:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* fmount */
	case 526:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* ntp_adjtime */
	case 527:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* ntp_gettime */
	case 528:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* os_fault_with_payload */
	case 529:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#if CONFIG_WORKQUEUE
	/* kqueue_workloop_ctl */
	case 530:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif // CONFIG_WORKQUEUE
	/* __mach_bridge_remote_time */
	case 531:
		if (ndx == 0 || ndx == 1)
			p = "uint64_t";
		break;
#if CONFIG_COALITIONS
	/* coalition_ledger */
	case 532:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
#else
#endif // CONFIG_COALITIONS
	/* log_data */
	case 533:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* memorystatus_available_memory */
	case 534:
		if (ndx == 0 || ndx == 1)
			p = "uint64_t";
		break;
	/* shared_region_map_and_slide_2_np */
	case 536:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* pivot_root */
	case 537:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* task_inspect_for_pid */
	case 538:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* task_read_for_pid */
	case 539:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* sys_preadv */
	case 540:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
	/* sys_pwritev */
	case 541:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
	/* sys_preadv_nocancel */
	case 542:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
	/* sys_pwritev_nocancel */
	case 543:
		if (ndx == 0 || ndx == 1)
			p = "user_ssize_t";
		break;
	/* ulock_wait2 */
	case 544:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	/* proc_info_extended_id */
	case 545:
		if (ndx == 0 || ndx == 1)
			p = "int";
		break;
	default:
		break;
	};
	if (p != NULL)
		strlcpy(desc, p, descsz);
}
