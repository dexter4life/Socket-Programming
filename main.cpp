
#ifdef WIN32
#include <winsock2.h>         // For socket(), connect(), send(), and recv()
#include <ws2ipdef.h>
typedef int socklen_t;
typedef char raw_type;       // Type used for raw data on this platform
#else
#include <sys/types.h>       // For data types
#include <sys/socket.h>      // For socket(), connect(), send(), and recv()
#include <netdb.h>           // For gethostbyname()
#include <arpa/inet.h>       // For inet_addr()
#include <unistd.h>          // For close()
#include <netinet/in.h>      // For sockaddr_in
typedef void raw_type;       // Type used for raw data on this platform
#endif

typedef uint32_t ip_addr;

ip_addr get_local_ip()
{
#if WIN32
	WSADATA wsaData;

	if (WSAStartup(0x202, &wsaData)) {
		fprintf(stderr, "WSAStartup init fail");
		exit(1);
	}
#endif
	struct in_addr local_ip;
	//local_ip.s_addr = inet_addr("");

	char hostname[255];
	struct hostent *he;

	if (gethostname(hostname, sizeof(hostname)) != 0) {
		printf("cannot retrieve local hostname\n");
		return 0;
	}
	he = gethostbyname(hostname);
	if (!he) {
		printf("cannot retrieve local ip address\n");
		return 0;
	}
	local_ip = *(struct in_addr *)*he->h_addr_list;
#ifdef WIN32
	WSACleanup();
#endif
	return local_ip.s_addr;// .S_addr;
}

int main()
{
  in_addr addr;
	addr.s_addr = get_local_ip();

	printf("System IP is: %s\n",inet_ntoa(addr));
  
  return 0;
}
