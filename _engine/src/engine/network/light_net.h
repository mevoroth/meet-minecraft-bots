/**	\file light_net.h
	*	Communication reseau bas niveau
	*	
	*	Communication reseau bas niveau	(UDP) entre	deux entites, a	niveau de 
	*	priorite egale (peer to	peer)
	*			
	*	\author	Guillaume Levieux
	*	\date 2005
	*/

#ifndef	__NY_LIGHT_NET__
#define	__NY_LIGHT_NET__

#include <winsock2.h> //!!! Attention, a inclure avant windows.h sinon erreur de compil
#include <stdio.h>
#include "engine/utils/types.h"
#include "engine/utils/ny_utils.h"
#include "net.h"

#include <string>
using namespace std;

/** Composants de gestion bas niveau du réseau, en mode non connecté : UDP
	*/
class NYLightNet : public NYNet
{

private:

	///	Le port	d'écoute
	uint16 _Port;		 
		
	///	Le nombre d'octets recus
	uint32 _NbOctetsRecus; 

	///Adresse de la machine distante vers laquelle sont emises les trames
	SOCKADDR_IN	_RemoteHost;

	///Adresse de la machine a l'origine du dernier message recu
	SOCKADDR_IN _RemoteHostReceived;

public:
	/**	Constructeur de	la classe
	  *
		* \param taille la taille du buffer de reception
	  */
	NYLightNet::NYLightNet(uint16 taille) : NYNet(taille)
	{
		//Init
		this->_NbOctetsRecus =	0;
		memset(&_RemoteHost,0x00,sizeof(SOCKADDR_IN));
		memset(&_RemoteHostReceived,0x00,sizeof(SOCKADDR_IN));

		//Le port n'est pas initialise
		this->_Port =	-1; 
	}

	/** Destructeur
	  */
	NYLightNet::~NYLightNet(void)
	{
		this->setOffline();
	}

	/** Permet de choisir le remote host
	  *
	  * \param ip l'ip de destination 
	  * \param port le port de destination
	  */
	void setRemoteHost(string & ip, uint16 port);

	/** Permet d'effacer le remote host
	  *
		* \note
		*		Implementé pour conformité avec l'interface net mais 
		*		sans interet pour composant sans connexion
	  */
	void resetRemoteHost(void);

	/** Permet de connaitre le remote host
	  *
	  * \param ip l'ip de destination
	  * \param port le port de destination
	  */
	void getRemoteHost(string & ip, uint16 * port);
	
	/** Permet de connaitre le denrier couple ip/port qui a nous envoye un message
	  *
	  * \param ip l'ip de la machine a l'origine du dernier message recu
	  * \param port le port de cette meme machine
	  */
	void getWhoTalkedToMe(string & ip, uint16 * port);

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
		*
		* \return
		*		-  0: pas d'erreur
		*   - -1: erreur WSA
		*   - -2: pas de port libre
	  */
	sint8 setOnline(uint32 timeout, uint16 port, uint16 portFinPlage = 0);

	/** Deconnecte le composant
		*/
	void setOffline(void);
	
	/**	Permet de relancer la connexion
	  *
		* \param timeout timeout pour la connexion au restart
		*
		* \warning 
		*		ne fonctionnne que si le composant a deja été mis une fois en ligne
		*   (sinon le port n'est pas definit)
	  */
	sint8 restart(uint32 timeout);
	
	/** Permet d'envoyer un	paquet au remote host
	  *
	  * \param datas les datas a envoyer
	  * \param taille la taille de ces datas
		*
		* \return
		*		-  0: pas d'erreur
		*   - -1: erreur WSA
		*   - -2: pas de port libre
	  */
	sint8 send(uint8 * datas,  uint32	taille);
		
	/**	Permet de recevoir les datas arrivés sur le socket et de les stoquer dans
		*	le buffer du composant
		*
		*	\return	
		*	  -	 0:	aucun carac	recus
		*	  -	-1:	erreur WSA
		*	  -	>0:	nombre d'octets	recus
		*/
	sint16 receive(void);
			
};

#endif