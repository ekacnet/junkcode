#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <dlfcn.h>


typedef int type_getaddrinfo(const char *node, const char *service,
							 const struct addrinfo *hints,
							 struct addrinfo **res);
void *mylibchandle;
static type_getaddrinfo* libcgetaddrinfo;

void install_interceptor(void) __attribute__ ((constructor));
void install_interceptor(void)
{
	mylibchandle = dlopen ("libc.so.6", RTLD_NOW);
	libcgetaddrinfo = (type_getaddrinfo*) dlsym(mylibchandle, "getaddrinfo");
}

int getaddrinfo(const char *node, const char *service,
				  const struct addrinfo *hints,
				  struct addrinfo **res)
{
	return libcgetaddrinfo(node, service, hints, res);
}
