#include <dev/busvar.h>


extern int pty_init(int);
extern int ptmx_init(int);
extern int vndevice_init(int);
extern int mdevinit(int);
extern int bpf_init(int);
extern int fsevents_init(int);
extern int random_init(int);
extern int dtrace_init(int);
extern int helper_init(int);
extern int lockstat_init(int);
extern int lockprof_init(int);
extern int sdt_init(int);
extern int systrace_init(int);
extern int fbt_init(int);
extern int profile_init(int);

struct pseudo_init pseudo_inits[] = {
	{128,	pty_init},
	{1,	ptmx_init},
	{4,	vndevice_init},
	{1,	mdevinit},
	{4,	bpf_init},
	{1,	fsevents_init},
	{1,	random_init},
	{1,	dtrace_init},
	{1,	helper_init},
	{1,	lockstat_init},
	{1,	lockprof_init},
	{1,	sdt_init},
	{1,	systrace_init},
	{1,	fbt_init},
	{1,	profile_init},
	{0,	0},
};
