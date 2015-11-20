/*
 *
 * Copyright Matthieu Patou <mat@matws.net> 2014
 * License is public domain so that it can be linked with any kind of code
 */
#include <dlfcn.h>
#include <sys/utsname.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef int type_uname(struct utsname *buf);
static type_uname * func = NULL;
void install_interceptor(void) __attribute__ ((constructor));
static int32_t installed = 0;
static int32_t intercepted = 0;
static struct utsname fake;

const char SYSNAME[] = "sysname";
const char MACHINE[] = "machine";
const char RELEASE[] = "release";
const char VERSION[] = "version";
const char NODENAME[] = "nodename";
#ifdef _GNU_SOURCE
const char DOMAINNAME[] = "domainname";
#endif

//#define UNAME_PRELOAD_DEBUG
#ifdef UNAME_PRELOAD_DEBUG
#define debug_print(...) do { fprintf(stderr, __VA_ARGS__); } while (0)
#else
#define debug_print(...)
#endif

void install_interceptor(void)
{
	if (installed) {
		return;
	}
	char buf[4096];
	ssize_t size;
	char* current;
	char* tmp;
	int fd;
	const char *path = getenv("PRELOAD_UNAME_CONF");
	if (!path) {
		path = "/etc/preload_uname.conf";
	}
	fd = open(path, 0);

	/* Set all strings to NULL so that only overrided values are set */
	memset(&fake, 0, sizeof(fake));
	memset(buf, 0, sizeof(buf));

	func = (type_uname*) dlsym(RTLD_NEXT, "uname");
	if (fd == -1) {
		/* Nothing to load */
		return;
	}
	size = read(fd, buf, sizeof(buf) - 1);
	if (size == -1) {
		debug_print("Error while reading %s\n", path);
		close(fd);
		return;
	}
	if (size == sizeof(buf)) {
		/* 4K is more than enough, so if we need more something is wrong */
		debug_print("File %s is more than 4K long that's not normal, ignoring interposition\n", path);
		close(fd);
		return;
	}
	current = buf;
	while ((tmp = strchr(current, ':')) && ((current - buf) <= size)) {
		debug_print("delta = %d\n", (int)(current - buf));
		char *field = NULL;
		size_t size_field = 0;
		/* Found a key */
		*tmp = '\0';
		if (strncmp(current, SYSNAME, sizeof(SYSNAME)) == 0) {
			field = fake.sysname;
			size_field = sizeof(fake.sysname);
		}
		if (strncmp(current, NODENAME, sizeof(NODENAME)) == 0) {
			field = fake.nodename;
			size_field = sizeof(fake.nodename);
		}
		if (strncmp(current, RELEASE, sizeof(RELEASE)) == 0) {
			field = fake.release;
			size_field = sizeof(fake.release);
		}
		if (strncmp(current, VERSION, sizeof(VERSION)) == 0) {
			field = fake.sysname;
			size_field = sizeof(fake.sysname);
		}
		if (strncmp(current, MACHINE, sizeof(MACHINE)) == 0) {
			field = fake.machine;
			size_field = sizeof(fake.machine);
		}
#ifdef _GNU_SOURCE
		if (strncmp(current, DOMAINNAME, sizeof(DOMAINNAME)) == 0) {
			field = fake.domainname;
			size_field = sizeof(fake.domainname);
		}
#endif
		debug_print("key = %s size = %lu\n", current, size_field);
		current = tmp + 1;
		tmp = strchr(current, '\n');
		if (tmp && ((tmp - buf) > size)) {
			break;
		}

		if (tmp) {
			*tmp = '\0';
		}
		strncpy(field, current, size_field - 1);
		if ((size_field - 1) > strlen(current)) {
			field[strlen(current)] = '\0';
		} else {
			field[size_field - 1] = '\0';
			debug_print("Value %s too long, truncated to %s", current, field);
		}
		debug_print("value = %s\n", current);
		if (tmp) {
			current = tmp + 1;
		}
	}
	installed = 1;
}

int uname(struct utsname *buf)
{
	int ret = 0;
	debug_print("my uname called\n");
	if (!intercepted) {
		func = (type_uname*) dlsym(RTLD_NEXT, "uname");
	}
	if (!func) {
		debug_print("No real uname\n");
		return -1;
	}
	ret = func(buf);
	if (!installed) {
		return ret;
	}
	debug_print("interposing\n");
	if (fake.sysname[0]) {
		strcpy(buf->sysname, fake.sysname);
	}
	if (fake.nodename[0]) {
		strcpy(buf->nodename, fake.nodename);
	}
	if (fake.release[0]) {
		strcpy(buf->release, fake.release);
	}
	if (fake.version[0]) {
		strcpy(buf->version, fake.version);
	}
	if (fake.machine[0]) {
		strcpy(buf->machine, fake.machine);
	}
#ifdef _GNU_SOURCE
	if (fake.domainname[0]) {
		strcpy(buf->domainname, fake.domainname);
	}
#endif
	return ret;
}
