/**	\file connected_net.cpp
	*  Communication reseau bas niveau	
	*	
	*	 \author Guillaume Levieux
	*	 \date 2005
	*/

#include <stdio.h>
#include "connected_net.h"
#include "engine/timer.h"

/*******************************************************************************/
/*CREATE*/
/*******************************************************************************/
sint8 NYConnectedNet::create(void)
{	
	//Si socket deja créé
	if(this->_Socket)
		closesocket(this->_Socket);

	//Creation du socket
	this->_Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(this->_Socket==INVALID_SOCKET)
	{
		Log::log(Log::ENGINE_ERROR,(string("NYConnectedNet::create Impossible de	créer un socket ") + toString(WSAGetLastError())).c_str());
		WSACleanup();
		return -1;
	}

	return 0;
}

/*******************************************************************************/
/*SETONLINE*/
/*******************************************************************************/
sint8 NYConnectedNet::setOnline(uint32 timeout, uint16 port, uint16 portFinPlage)
{	
	int	nret; //retour
	sint8 retS8; 

	//Affecte le port 
	this->_Port = port;

	//On se deconnecte au cas ou deja connecte
	this->setOffline();

	//On est en TCP. Si on a definit un remote Host: on essaie de se connecter a lui
	if(_RemoteHostOK)
	{	
		//Creation de la connexion
		retS8 = this->create();
		if(retS8 < 0)
		{
			Log::log(Log::ENGINE_ERROR,(string("NYConnectedNet::setOnline Impossible de	créer un socket ") + toString(WSAGetLastError())).c_str());
			return -1;
		}

		//bind du socket en local pour fixer le port (si firewall, plus simple)
		if(!portFinPlage)
			portFinPlage = port;

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
					Log::log(Log::ENGINE_ERROR,(string("NYConnectedNet::setOnline Erreur d'attache du socket ") + toString(WSAGetLastError())).c_str());
					WSACleanup();
					return -1;
				}
			}
			else
			{
				break;
			}
		}

		//Si pas trouve de port libre
		if(port > portFinPlage)
		{
			Log::log(Log::ENGINE_ERROR,(string("NYConnectedNet::setOnline Plus de port libre ") + toString(portFinPlage)).c_str());
			WSACleanup();
			return -2;
		}
		
		//On sera client, on essaie de se connecter au remote host pendant le timeout
		NYTimer timer;
		timer.start();
		while(timer.getElapsedMs() < timeout)
		{
			nret = connect(this->_Socket,(SOCKADDR*) &_RemoteHost,	sizeof(_RemoteHost));	
			if (nret==0)
				break;
		}

		if(nret < 0)
		{ 
			Log::log(Log::ENGINE_ERROR,(string("NYConnectedNet::setOnline Impossible de se connecter au serveur ") + toString(WSAGetLastError())).c_str());
			WSACleanup();
			return -1;
		}

		//non blocking
		uint32 mode = 1;
		int nret = ioctlsocket(this->_Socket, FIONBIO,	(unsigned long*)(&mode));
		if(nret==SOCKET_ERROR)
		{
			Log::log(Log::ENGINE_ERROR,(string("NYConnectedNet::setOnline Erreur passage ensocket non bloquant ") + toString(WSAGetLastError())).c_str());
			WSACleanup();
			return -1;
		}
	}
	else //Si pas de remote host definit
	{
		//On cree une connexion en attente
		retS8 = createListeningConnexion(port,portFinPlage);
		
		//Si erreur
		if (retS8 < 0)
		{
			this->setOffline();
			
			//Si plus de ports libres, retourne meme erreur
			if(retS8 == -2)
				return -2;
			
			return -1;
		}
		
		//On veut recevoir l'evt de fermeture
		/*_CloseEvent = WSACreateEvent();
		if(WSAEventSelect( this->_Socket, _CloseEvent, FD_CLOSE) == SOCKET_ERROR)
		{
			Log::log(Log::ENGINE_ERROR,(string("NYConnectedNet::setOnline Impossible de demander l'evenement de fermeture ") + toString(WSAGetLastError())).c_str());
			this->setOffline();
			return -1;	
		}*/
		
		//On attend une connexion du client pendant ce timeout
		retS8 = this->waitClient(timeout);
		
		if (retS8 < 0)
		{
			this->setOffline();
			
			//Si timeout, retourne timeout
			if (retS8 == -2)
			{
				return -3;
			}
			return -1;
		}
	}

	//On autorise ou non le buffering
	if(enableBuffering(_UseNaggle) < 0)
	{
		this->setOffline();
		return -1;
	}

	//Fermeture violente quand closesocket
	//(sinon erreur a la reconnexion quand relance exe, car socket mal ferme)
	LINGER linger;
	linger.l_onoff = 1;
	linger.l_linger = 0;
	if(setsockopt(_Socket,SOL_SOCKET,SO_LINGER,(char*)&linger,sizeof(LINGER)) == SOCKET_ERROR)
	{
		Log::log(Log::ENGINE_ERROR,(string("NYConnectedNet::setOnline Peut pas mettre fermeture violente ") + toString(WSAGetLastError())).c_str());
		return -1;
	}
	
	//On est online
	_IsOnline = true;

	return 0;
}

/*******************************************************************************/
/*SETOFFLINE*/
/*******************************************************************************/
void NYConnectedNet::setOffline(void)
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
sint8 NYConnectedNet::restart(uint32 timeout)
{
	this->setOffline();
	return this->setOnline(timeout, this->_Port);
}


/*******************************************************************************/
/*CREATE LISTENING CONNEXION*/
/*******************************************************************************/
sint8 NYConnectedNet::createListeningConnexion(uint16 port, uint16 plageFin)
{
	int	nret; //retour
	sint8 retS8;

	//Creation de la connexion
	retS8 = this->create();
	if(retS8 < 0)
	{
		Log::log(Log::ENGINE_ERROR,(string("NYConnectedNet::createListeningConnexion Impossible de creer le socket ") + toString(WSAGetLastError())).c_str());
		return -1;
	}
	
	if (plageFin == 0)
		plageFin = port;
		
	//On cherche le bon port
	while (port <= plageFin)
	{
		//bind en receive all, on sera serveur
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
				Log::log(Log::ENGINE_ERROR,(string("NYConnectedNet::createListeningConnexion Erreur d'attache du socket ") + toString(WSAGetLastError())).c_str());
				WSACleanup();
				return -1;
			}
		}
		else
		{
			//On sauve le port
			_Port = port;
			break;
		}
	}

	//Si pas trouve de port libre
	if(port > plageFin)
	{
		Log::log(Log::ENGINE_ERROR,(string("NYConnectedNet::createListeningConnexion Plus de port libres ") + toString(plageFin)).c_str());
		WSACleanup();
		return -2;
	}

	//On affecte le port
	this->_Port = port;

	//On demande a ecouter les connexions entrantes sur ce socket
	if(listen(this->_Socket,1) == SOCKET_ERROR)
	{
		Log::log(Log::ENGINE_ERROR,(string("NYConnectedNet::createListeningConnexion Impossible d'ecouter sur le socket ") + toString(WSAGetLastError())).c_str());
		WSACleanup();
		return -1;
	}
	
	//Passage en mode non bloquant
	uint32 mode = 1;
	nret = ioctlsocket(this->_Socket, FIONBIO,	(unsigned long*)(&mode));
	if(nret==SOCKET_ERROR)
	{
		Log::log(Log::ENGINE_ERROR,(string("NYConnectedNet::createListeningConnexion Erreur passage en	socket non bloquant ") + toString(WSAGetLastError())).c_str());
		WSACleanup();
		return -1;
	}

	return 0;
}



/*******************************************************************************/
/*WAITCLIENT*/
/*******************************************************************************/
sint8 NYConnectedNet::waitClient(uint32 timeout)
{
	//On attend une connexion
	NYTimer timer;
	timer.start();
	SOCKET sockAccept = INVALID_SOCKET;
	while(sockAccept == INVALID_SOCKET &&
		    (timer.getElapsedMs() <= timeout))
	{
		sint32 taille = sizeof(SOCKADDR);
		sockAccept = accept(this->_Socket,(SOCKADDR*)&this->_RemoteHost,(int*)&taille);

		if (sockAccept == INVALID_SOCKET && WSAGetLastError() != WSAEWOULDBLOCK)
		{
			this->setOffline();
			Log::log(Log::ENGINE_ERROR,(string("NYConnectedNet::waitClient Erreur accept du client ") + toString(WSAGetLastError())).c_str());
			WSACleanup();
			return -1;
		}
	}

	//Si toujours invalide,  le timeout s'est ecoule
	if(sockAccept == INVALID_SOCKET)
	{
		return -2;
	}
	
	//Sinon on affecte le socket connecte au socket principal
	closesocket(this->_Socket);
	this->_Socket = sockAccept;

	//On est online
	this->_IsOnline = true;

	return 0;
}

/*******************************************************************************/
/*SETREMOTEHOST*/
/*******************************************************************************/
void NYConnectedNet::setRemoteHost(string & ip, uint16 port)
{
	_RemoteHostOK = true;

	_RemoteHost.sin_family	= AF_INET;
	_RemoteHost.sin_port =	htons(port);
	_RemoteHost.sin_addr.s_addr = inet_addr(ip.c_str());
}

/*******************************************************************************/
/*RESETREMOTEHOST*/
/*******************************************************************************/
void NYConnectedNet::resetRemoteHost(void)
{
	_RemoteHostOK = false;
	memset(&_RemoteHost,0x00,sizeof(SOCKADDR_IN));
}

/*******************************************************************************/
/*GETREMOTEHOST*/
/*******************************************************************************/
void NYConnectedNet::getRemoteHost(string & ip, uint16 * port)
{
	*port =	ntohs(_RemoteHost.sin_port);
  ip = inet_ntoa(_RemoteHost.sin_addr);
}

/*******************************************************************************/
/*GETWHOTALKEDTOME*/
/*******************************************************************************/
void NYConnectedNet::getWhoTalkedToMe(string & ip, uint16 * port)
{
	*port =	ntohs(_RemoteHost.sin_port);
  ip = inet_ntoa(_RemoteHost.sin_addr);
}


/*******************************************************************************/
/*SEND*/
/*******************************************************************************/
sint8 NYConnectedNet::send(uint8 * datas,  uint32 taille)
{
	int	nret;
	bool sentOk = false;

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
					Log::log(Log::ENGINE_ERROR,(string("NYConnectedNet::send Impossible d'emettre ") + toString(WSAGetLastError())).c_str());
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
sint16 NYConnectedNet::receive(void)
{
	sint16	nb_cars;
	int	taille_addr	= sizeof(struct	sockaddr);
	
	nb_cars	= recvfrom(this->_Socket,(char*)this->_ReceiveBuffer,this->_ReceiveBufferSize-2,0,(LPSOCKADDR)&(_RemoteHost),&taille_addr);

	if(nb_cars == SOCKET_ERROR)
	{
		//si c juste pas de	datas
		uint16 error = WSAGetLastError();
		if (error == WSAEWOULDBLOCK)
			return 0;
		
		Log::log(Log::ENGINE_ERROR,(string("NYConnectedNet::receive Impossible de	recevoir ") + toString(WSAGetLastError())).c_str());	
		return -1;
	}
	
	if(nb_cars)
	{
		this->_ReceiveBuffer[nb_cars] = 0;
		this->_NbOctetsRecus =	nb_cars;
	}

	return nb_cars;
}

