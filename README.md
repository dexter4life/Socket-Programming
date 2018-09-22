# Socket-Programming-gethostbyname-
How to Obtain the IP Address of the Local Machine on the Network  Socket Programming gethostbyname: How to Obtain the IP Address of the Local Machine on the Network

A method to obtain the correct IP address of the local machine rather than just the localhost 127.0.0.1 address.

Read more at Suite101: Socket Programming gethostbyname: How to Obtain the IP Address of the Local Machine on the Network 

Introduction
This article covers an operating system-independent way to obtain the local IP address using sockets programming. The original process was developed using the Windows Sockets 1.1 (WinSock) API, but it should be portable to other Windows (CygWin, Wine etc.) and non-Windows environments (Linux, etc.).

Should this not be the case, feel free to open a discussion below.

The Problem : Finding the Local IP Address
Often it is helpful to know the local IP address. Looking at the documentation for sockets programming, it would seem that the following function call might work:

gethostbyname("localhost");
This works, after a fashion, returning:

127.0.0.1
This is the local IP address, as opposed to the IP address that is assigned to the actual machine on the network. The local IP address is present in order to be able to test, use, and install networking applications where the adapter might be installed, but where no network is behind.

However, this IP address is of no use in communicating with the outside world. For that, we need our local network address. Be aware, however, that due to network address translation between the internet and the local network, this address may not be the one exposed to the world at large. Getting that IP address is a different challenge.

The Solution : Using gethostname & gethostbyname
The solution is simple enough. We need to be able to identify the local machine by name, and then we can call gethostbyname with that name to get the true IP address.

The two functions, gethostname and gethostbyname, are both available in implementations of the sockets communication API, on platforms including:

Linux
Windows
PHP
Perl
This makes this method the most portable solution to this problem.

The Code : WinSock Specific Code Sample
Our coded solution is very easy. All we need to do is:

Start up WinSock
Get the local host name
Get the address from the name
Convert the address to a string
Shut down WinSock
The WinSock start up is easy enough:

// Init WinSock
WSADATA wsa_Data;
int wsa_ReturnCode = WSAStartup(0x202,&wsa_Data);
We have selected WinSock 2.2, in this case (specified by the 0x101), as the minimum required library available.

Next, to get the local host name:

// Get the local hostname
char szHostName[255];
gethostname(szHostName, 255);
With this step complete, all that remains is to populate a host entry structure which will contain all the IP related information for this machine:

struct hostent *host_entry;
host_entry=gethostbyname(szHostName);
The hostent structure is not immediately useful, however. It contains a list of all the adapters in a member called h_addr_list, which is a null terminated list of addresses. We assume that the one we want is in h_addr_list[0], for the sake of clarity. This value can be converted to a string by using the inet_ntoa function:

char * szLocalIP;
szLocalIP = inet_ntoa (*(struct in_addr *)*host_entry->h_addr_list);
Having obtained the information we need, we can now shut down the WinSock library:

WSACleanup();
That is really all there is to it - a safe, portable, reliable method to obtain the local IP address of the host system.

(A complete discussion of the WinSock start up and shut down routines, as well as some pointers on decoding the various complex types that the library uses can be found here.)

Summary
There are other solutions to this problem, depending on the platform and technology. For Windows, there are three other alternatives:

Use DNS lookup
Use the WMI
Use a Registry lookup
For those using the .NET framework, the easiest of these is to use DNS, which is a mapping of the WinSock solution presented here, using Dns.GetHostName() and Dns.GetHostByName. Apple MacOS programmers have a similar solution available through the sockets API provided by most standard development tools.

