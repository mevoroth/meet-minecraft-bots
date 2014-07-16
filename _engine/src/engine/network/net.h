/**	\file net.h
	*	Interface pour les composants de gestion bas niveau du réseau
	*			
	*	\author	Guillaume Levieux
	*	\date 2005
	*/

#ifndef	__NY_NET__
#define	__NY_NET__

#include <winsock2.h>
#include "engine/utils/types.h"
#include "engine/utils/ny_utils.h"
#include "engine/log/log.h"

#include <string>
using namespace std;

/** Interface pour les composants de gestion bas niveau du réseau
	*/
class NYNet	
{
protected:
	///	Buffer de reception
	uint8 * _ReceiveBuffer;

	/// Taille du buffer de reception
	uint16 _ReceiveBufferSize;

	///	Le socket utilisé pour la connexion
	SOCKET _Socket;	  

	///Si le composant est online
	bool _IsOnline;

public:	

	/**	Constructeur de la classe
		*
	  * \param ReceiveBufferSize la taille de ce buffer
	  */
	NYNet(uint16 ReceiveBufferSize)
	{
		this->_ReceiveBuffer = new uint8[ReceiveBufferSize];
		this->_ReceiveBufferSize = ReceiveBufferSize;
		_IsOnline = false;
		this->_Socket = (SOCKET)0;
	}

	/**	Destructeur de la classe
	  */
	~NYNet()
	{
		SAFEDELETE(this->_ReceiveBuffer);
	}

	/** Initialisation WSA
		*/
	void init(void)
	{
		//initialisation winsocks
		WORD SockVersion = MAKEWORD(2,2); 
		WSADATA	wsaData;
		WSACleanup();
		WSAStartup(SockVersion,&wsaData);
	}

	/**	A utiliser pour obtenir un pointeur sur le buffer de reception du composant
	  * et recuperer les mesages recus
	  */
	uint8 * getBufferReception(void)
	{
		return this->_ReceiveBuffer;
	}
	
	/**	Permet de choisir la machine avec laquelle on veut communiquer
		*
	  * \param ip l'ip de cette machine sous la forme "xxx.xxx.xxx.xxx"
	  * \param port le port distant 
	  */
	virtual void setRemoteHost(string & ip, uint16 port) = 0;

	/**	Permet de connaitre la machine avec laquelle on vient
		*	de communiquer
		*
	  * \param ip l'ip de destination
	  * \param port le port de destination
	  */
	virtual void getRemoteHost(string & ip, uint16 * port) = 0;

	/** Permet de connaitre le dernier couple ip/port qui nous envoye un message
	  *
	  * \param ip l'ip de la machine distante
	  * \param port le port distant
	  */
	virtual void getWhoTalkedToMe(string & ip, uint16 * port) = 0;

	/** Permet mettre en ligne le composant. 
	  * Si on a definit aucun remote host, le composant se declare serveur, ouvre une connexion
		* et attend qu'on s'y connecte pendant la duree du timeout
		* Si on a definit un remote host, le client essaie de s'y connecter
		* Le composant utilise le port passe en argument pour se connecter localement.
		* Si portFinPlage est definit, le composant utilise le premier port libre de la plage
	  * comprise entre port et portFinPlage.
		*
	  * \param timeout le temps laisse pour se connecter ou attendre une connexion
	  * \param port le port distant ou le debut d'une plage de ports
		* \param portFinPlage si definit, la fin de la plage de port
	  */
	virtual sint8 setOnline(uint32 timeout, uint16 port, uint16 portFinPlage = 0) = 0;

	/** Deconnecte le composant
		*/
	virtual void setOffline(void) = 0;

	/** Pour savoir si le composant est online
		*/
	bool isOnline(void)
	{
		return this->_IsOnline;
	}

	/**	Permet de relancer la connexion
	  *
		* \warning 
		*		ne fonctionnne que si le composant a deja été mis une fois en ligne
		*   (sinon le port n'est pas definit)
	  */
	virtual sint8 restart(uint32 timeout) = 0;

	/** 
		* Permet d'envoyer un	paquet au remote host actuel
	  * 
	  * \param datas les datas a envoyer
	  * \param taille la taille de ces datas
		*
		* \warning 
		*		l'emission se fait en mode bloquant 
	  */
	virtual sint8 send(uint8 * datas,  uint32	taille) = 0;
			
	/**	
		*	Permet de verifier si des datas on été recus. 
		*	Si c'est le cas, il seront automatiquement copiés dans 	
		*	le buffer passé au contructeur de l'objet
		*
		*	\return	
		*	  -	 0:	aucun carac	recus
		*	  -	-1:	erreur WSA (appeler	WSAGetLastError)
		*	  -	>0:	nombre d'octets	recus
		*
		*/
	virtual sint16 receive(void) = 0;
	
	/**	
		*	Verification de l'etat de la connexion
		*
		*	\return	
		*	  -	 0:	connexion ok
		*	  -	-1:	impossible de lire sur la connexion
		*	  -	-2:	impossible d'ecrire sur la connexion
		*   -	-3:	erreurs sur la connexion
		*
		* \warning
		*		Cette fonction demande jusqu'a 3 secondes pour effectuer les 3 types de test
		*   (lecture,ecriture,erreur)
		*/
	sint8 checkConnexion(void)
	{
		TIMEVAL timeout;
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;

		//Tableau de sockets a checker (que celui du composant pour nous)
		fd_set sockSet;
		sockSet.fd_array[0] = this->_Socket;
		sockSet.fd_count = 1;

		//Test en lecture
		sint32 ret = select(0,&sockSet, NULL, NULL, &timeout);
		
		if(ret == SOCKET_ERROR)
		{
			string message;
			
			Log::log(Log::ENGINE_ERROR,(string("NYNet: Erreur check connexion (read) ") + toString(WSAGetLastError())).c_str());
			WSACleanup();
			return -1;
		}
		
		sockSet.fd_array[0] = this->_Socket;
		sockSet.fd_count = 1;

		//Test en ecriture
		ret = select(0,NULL, &sockSet, NULL, &timeout);

		if(ret == SOCKET_ERROR)
		{
			Log::log(Log::ENGINE_ERROR,(string("NYNet: Erreur check connexion (send) ") + toString(WSAGetLastError())).c_str());
			WSACleanup();
			return -2;
			
		}
		
		sockSet.fd_array[0] = this->_Socket;
		sockSet.fd_count = 1;

		//Test d'erreurs sur la connexion
		ret = select(0,NULL, NULL, &sockSet, &timeout);

		if(ret == SOCKET_ERROR)
		{
			Log::log(Log::ENGINE_ERROR,(string("NYNet: Erreur check connexion (errors) ") + toString(WSAGetLastError())).c_str());
			WSACleanup();
			return -3;	
		}

		return 0;
	}

	/**	
		*	Recupère l'ip a partir d'un nom
		*
		*	\param name le nom du serveur
		*	\param ip l'ip si on la trouve
		*
		*	\warning 
		*		doit deja avoir initialise WsaStartup();
		*/
	sint8 getIpFromName(string & name, string & ip)
	{
		struct  hostent *h; 
		DWORD   adress; 

		h = (hostent *) gethostbyname(name.c_str()); 
    
		if(h == NULL)
			return -1;

		memcpy(&adress,h->h_addr_list[0],sizeof(DWORD)); 
		if (adress == INADDR_NONE)   
			return -1; 

		struct in_addr tAddr; 
		memcpy(&tAddr,&adress,sizeof(DWORD)); 

		char *pAdr = inet_ntoa(tAddr); 
		if(!pAdr) 
			return -1;

		ip = string(pAdr);
		
		return 0; 
	}
};

#endif