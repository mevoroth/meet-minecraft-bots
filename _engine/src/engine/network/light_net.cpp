/**	\file light_net.cpp
	* Communication reseau bas niveau
	*	
	*	Communication reseau bas niveau	(UDP) entre	deux entites, a	niveau de 
	*	priorite egale (peer to	peer)
	*			
	*	 \author Guillaume Levieux
	*	 \date 2005
	*/

#include "light_net.h"

/*******************************************************************************/
/*SETONLINE*/
/*******************************************************************************/
sint8 NYLightNet::setOnline(uint32 timeout, uint16 port, uint16 portFinPlage)
{	
	int	nret; //retour

	//Sauvegarde
	_Port = port;
			
	//initialisation winsocks (version 2)
	WORD SockVersion = MAKEWORD(2,2); 
	WSADATA	wsaData;
	WSAStartup(SockVersion,&wsaData);
	
	//Si socket deja créé
	if(this->_Socket)
		closesocket(this->_Socket);
	
	//Creation du socket
	this->_Socket = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if(this->_Socket == INVALID_SOCKET)
	{
		Log::log(Log::ENGINE_ERROR,(string("NYLightNet::setOnline Impossible de créer un socket ") + toString(WSAGetLastError())).c_str());	
		WSACleanup();
		return -1;
	}

	//Mode non bloquant
	uint32 mode = 1;
	nret = ioctlsocket(this->_Socket, FIONBIO,	(unsigned long*)(&mode));
	if(nret==SOCKET_ERROR)
	{
		Log::log(Log::ENGINE_ERROR,(string("NYLightNet::setOnline Erreur passage en socket non bloquant ") + toString(WSAGetLastError())).c_str());	
		WSACleanup();
		return -1;
	}
	
	//Si on a pas definit de fin de plage, on limite la plage a 1 seul port
	if(!portFinPlage)
		portFinPlage = port;

	//Attache du socket en local: recherche d'un port de libre
	while(port <= portFinPlage)
	{
		SOCKADDR_IN	RecvAddr;
		RecvAddr.sin_family	= AF_INET;
		RecvAddr.sin_port =	htons(port);
		RecvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
			
		nret = bind(this->_Socket,	(SOCKADDR *) &RecvAddr,	sizeof(RecvAddr));
			
		if(nret==SOCKET_ERROR)
		{
			int error = WSAGetLastError();
			
			if(error == WSAEADDRINUSE)
			  port++;
			else
			{
				Log::log(Log::ENGINE_ERROR,(string("NYLightNet::setOnline Erreur d'attache du socket ") + toString(WSAGetLastError())).c_str());	
				WSACleanup();
				return -1;
			}
		}
		else
		{
			//On sauve le port choisi
			_Port = port;
			break;
		}
	}

	//Si pas trouve de port libre
	if(port > portFinPlage)
	{
		Log::log(Log::ENGINE_ERROR,(string("NYLightNet::setOnline Plus de port libres ") + toString(portFinPlage)).c_str());	
		WSACleanup();
		return -2;
	}
		
	//On est online
	_IsOnline = true;

	return 0;
}

/*******************************************************************************/
/*SETOFFLINE*/
/*******************************************************************************/
void NYLightNet::setOffline(void)
{
	//On est plus online
	_IsOnline = false;
	
	if(this->_Socket != 0)
	{
		//shutdown(this->_Socket,SD_BOTH);
		closesocket(this->_Socket);
	}
}

/*******************************************************************************/
/*RESTART*/
/*******************************************************************************/
sint8 NYLightNet::restart(uint32 timeout)
{
	if(this->_Port == -1)
	{
		Log::log(Log::ENGINE_ERROR,(string("NYLightNet::restart Impossible de restarter, jamais mis online ")).c_str());	
		return -1;
	}
	
	this->setOffline();
	return this->setOnline(timeout, _Port);
}

/*******************************************************************************/
/*SETREMOTEHOST*/
/*******************************************************************************/
void NYLightNet::setRemoteHost(string & ip, uint16 port)
{
	_RemoteHost.sin_family	= AF_INET;
	_RemoteHost.sin_port =	htons(port);
	_RemoteHost.sin_addr.s_addr = inet_addr(ip.c_str());
}

/*******************************************************************************/
/*RESETREMOTEHOST*/
/*******************************************************************************/
void NYLightNet::resetRemoteHost(void)
{
	//Ca ne sert a rien pour le composant UDP
	memset(&_RemoteHost,0x00,sizeof(SOCKADDR_IN));
}

/*******************************************************************************/
/*GETREMOTEHOST*/
/*******************************************************************************/
void NYLightNet::getRemoteHost(string & ip, uint16 * port)
{
	*port =	ntohs(_RemoteHost.sin_port);
	ip = inet_ntoa(_RemoteHost.sin_addr);
}

/*******************************************************************************/
/*GETWHOTALKEDTOME*/
/*******************************************************************************/
void NYLightNet::getWhoTalkedToMe(string & ip, uint16 * port)
{
	*port =	ntohs(_RemoteHostReceived.sin_port);
  ip = inet_ntoa(_RemoteHostReceived.sin_addr);
}


/*******************************************************************************/
/*SEND*/
/*******************************************************************************/
sint8 NYLightNet::send(uint8 * datas,  uint32 taille)
{
	int	nret;
	bool sentOk = false;

	if(this->_IsOnline == false)
	{
		Log::log(Log::ENGINE_ERROR,(string("NYLightNet::send Impossible d'emettre, composant offline ")).c_str());	
		return -1;
	}

	//On emet tant que l'on a l'erreur WSAEWOULDBLOCK
	//En fait on se comporte ici comme si le socket etait bloquant
	//mais c moin mal que de le repasser en mode bloquant a chaque emission
	while(sentOk == false)
	{
		nret = sendto(this->_Socket,(char *)datas, taille,0,(LPSOCKADDR)&(this->_RemoteHost),sizeof(struct	sockaddr));

		sentOk = true;
		if(nret==SOCKET_ERROR)
		{
			uint16 error = WSAGetLastError();
			switch(error)
			{
				case WSAEWOULDBLOCK:
					sentOk = false;
					break;
				default:
					Log::log(Log::ENGINE_ERROR,(string("NYLightNet::send Impossible d'emettre ") + toString(error)).c_str());	
					WSACleanup();
					return -1;
			}
		}
	}

	return 0;
}

/*******************************************************************************/
/*RECEIVE*/
/*******************************************************************************/
sint16 NYLightNet::receive(void)
{
	sint16	nb_cars;
	int	taille_addr	= sizeof(SOCKADDR_IN);

	if(this->_IsOnline == false)
	{
		Log::log(Log::ENGINE_ERROR,(string("NYLightNet::receive Impossible de recevoir, composant offline ")).c_str());	
		return -1;
	}
	
	//On le reprepare en NYY
	_RemoteHostReceived.sin_family = AF_INET;
	_RemoteHostReceived.sin_port = htons(this->_Port);
	_RemoteHostReceived.sin_addr.s_addr =	htonl(INADDR_ANY);

	//reception
	nb_cars	= recvfrom(this->_Socket,
										 (char*)this->_ReceiveBuffer,
										 this->_ReceiveBufferSize-2,
										 0,
										 (LPSOCKADDR)&(_RemoteHostReceived),
										 &taille_addr);

	//Si on a recu
	if(nb_cars)
	{
		if(nb_cars == SOCKET_ERROR)
		{
			uint16 error = WSAGetLastError();

			//si c juste pas de	datas
			if (error == WSAEWOULDBLOCK)
				return 0;
			
			Log::log(Log::ENGINE_ERROR,(string("NYLightNet::receive Impossible de recevoir ") + toString(WSAGetLastError())).c_str());	
			return -1;
		}

		this->_ReceiveBuffer[nb_cars] = 0;
		this->_NbOctetsRecus =	nb_cars;
	}
	return nb_cars;
}
