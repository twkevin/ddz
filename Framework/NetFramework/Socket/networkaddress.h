#ifndef  _NETWORK_ADDRESS_
#define  _NETWORK_ADDRESS_
#include "mutex.h"
#include <iostream>
#include <string>

#if !defined WIN32
#include <netinet/in.h>
#endif

#if defined WIN32
#define _WINSOCKAPI_
#include <Windows.h>
#include <WinSock2.h>
#endif

#define IPV4_LENGTH 4

class NetworkAddress
{
public:

	NetworkAddress();
	
	NetworkAddress( const std::string& hostName, unsigned short port = 0 );
	
	void setHostName( const std::string& theAddress );

	void setIp4Addr( unsigned int addr, unsigned short port=0 );
	
	void setPort( unsigned short port );
	
	std::string getHostName() const;
	
	/// get IP address as a string in the form "192.168.4.5"
	std::string getIpName() const;

	std::string getPortName() const;

	std::string getIpPortName() const;
	
	/** return the IP4 address packed as an unsigned int, in
	* network byte order. */
	unsigned int getIp4Address() const;

	/* return networkmask in network byte order */
	static unsigned int getNetmask();

	static std::string getNetmaskName();

	static unsigned int m_netmask;
	
	/** return the address in a sockaddr.  This value is assigned
	* @param socka    returned address */
	void getSockAddr( struct sockaddr & socka ) const;
	
	unsigned short getPort() const;
	

	friend bool operator < ( const NetworkAddress & xAddress, const NetworkAddress & yAddress );

	friend bool operator == ( const NetworkAddress & xAddress, const NetworkAddress & yAddress );	
	
	friend bool operator!=( const NetworkAddress & xAddress, const NetworkAddress & yAddress );
	
	friend std::ostream & operator<< ( std::ostream & xStream, const NetworkAddress& rxObj );
	
	NetworkAddress& operator=( const NetworkAddress& x );
	
	std::ostream & print( std::ostream & xStr ) const;

	bool isSameNetwork( const NetworkAddress& dtIp );
	
	static bool is_valid_ip_addr( const std::string& ip_addr, char* retaddr = NULL );

	bool isValid();

private:

	void initIpAddress() const;
	mutable char ipAddress[ IPV4_LENGTH ];  // it's in network byte order
	unsigned short aPort;
	std::string rawHostName;
	mutable bool ipAddressSet;
};


inline std::ostream &
operator<< ( std::ostream & xStream, const NetworkAddress& rxObj )
{
    return rxObj.print ( xStream );
}

#endif //_NETWORK_ADDRESS_

