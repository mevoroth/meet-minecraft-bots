/**	\file connected_net.h
	*	Communication reseau bas niveau
	*	
	*	Communication reseau bas niveau	en mode connecte (TCP)
	*			
	*	\author	Guillaume Levieux
	*	\date 2005
	*/

#ifndef	__NY_CONNECTED_NET__
#define	__NY_CONNECTED_NET__

#include <winsock2.h>
#include "engine/utils/types.h"
#include "engine/utils/ny_utils.h"
#include "net.h"

#include <string>  
using namespace std;

#include <process.h>

///	Gestion	bas	niveau de la com reseau
class NYConnectedNet : public NYNet
{

private: 
	
	///	Le port	d'écoute
	uint16 _Port;

	///	Le nombre d'octets recus
	uint32 _NbOctetsRecus;

	///Le remote host
	SOCKADDR_IN	_RemoteHost;

	///Si on a choisit un remote host
	bool _RemoteHostOK;

	///Si on naggle de TCP (buffering auto sur le socket)
	bool _UseNaggle;
	
	///Evenement de fermeture
	WSAEVENT _CloseEvent;

private:
	
	/**Permet de creer le socket et d'initialiserla connexion
	  */
	sint8 create(void);

public:
	/**	Constructeur de	la classe
	  *
		* \param taille la taille du buffer de reception
	  */
	NYConnectedNet::NYConnectedNet(uint16 taille) : NYNet(taille)
	{
		memset(&_RemoteHost,0x00,sizeof(SOCKADDR_IN));
		_RemoteHostOK = false;
		_NbOctetsRecus = 0;
		_Port = -1;
		_UseNaggle = false; //par defaut, pas naggle
	}

	/** Destructeur
	  */
	NYConnectedNet::~NYConnectedNet(void)
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
		* Permet d'etre sur, lors de la connexion , de se connecter en mode serveur,
		* car si un remote host est definit, le composant cherche a se connecter
		* à se remote host en mode client.
	  */
	void resetRemoteHost(void);

	/** Permet de connaitre le remote host definit
	  *
	  * \param ip l'ip de destination 
	  * \param port le port de destination
	  */
	void getRemoteHost(string & ip, uint16 * port);

	/** Permet de connaitre le denrnier couple ip/port qui nous envoye un message
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
		*		-  0: Pas d'erreur
		*		- -1: Erreur WSA
		*   - -2: Plus de port libre pour attacher le socket en local
		*   - -3: (mode serveur) Timeout, aucun client ne s'est connecte
	  */
	sint8 setOnline(uint32 timeout, uint16 port, uint16 portFinPlage = 0);

	/** Cree un socket en ecoute.
		* Cette fonction n'est a utiliser que si on souhaite utiliser le composant en mode
		* serveur et décompser les phases de connexion, par exemple pour pouvoir NYnuler
		* avant la fin du timeout.
		* Cette fonction est appelee de facon transparente si on utilise setOnline
		* Cette fonction trouve elle même un port libre dans la plage de port passee
		* en argument, bornes comprises
		*
		* \param port Le port sur lequel on ouvre cette connexion en ecoute
		* \param portFinPlage Si definit, la fin de la plage de port
		*
		* \return
		*		-  0: Pas d'erreur
		*		- -1: Erreur WSA
		*   - -2: Plus de port libre pour attacher le socket en local
	  */
	sint8 createListeningConnexion(uint16 port, uint16 portFinPlage = 0);

	/** Verifie si un client essaie de se connecter et si oui l'accepte
		* Il faut tout d'abord creer une connexion en ecoute pour pouvoir utiliser cette 
		* fonction, en utilisant createListeningConnexion
		* Cette fonction n'est a utiliser que si on souhaite utiliser le composant en mode
		* serveur et décompser les phases de connexion, par exemple pour pouvoir NYnuler
		* avant la fin du timeout.
		* Cette fonction est appelee de facon transparente si on utilise setOnline
		*
	  * \param timeout le temps pendant lequel on ecoute sur le socket
		*
		* \return
		*		-  0: Pas d'erreur
		*		- -1: Erreur WSA
		*   - -2: Timeout, aucun client ne s'est connecte
	  */
	sint8 waitClient(uint32 timeout);

	/** Permet de passer le composant hors ligne
		*/
	void setOffline(void);
	
	/** Permet de deconnecter et reconnecter le composant
		*
		* \param timeout le temps qu'on laisse au composant pour se connecter
		*
		* \return
		*		-  0: Pas d'erreur
		*		- -1: Erreur WSA
		*   - -2: Plus de port libre pour attacher le socket en local
		*   - -3: (mode serveur) Timeout, aucun client ne s'est connecte
		*/
	sint8 restart(uint32 timeout);
	
	/** Permet d'envoyer un	paquet au remote host
	  *
	  * \param datas les datas a envoyer
	  * \param taille la taille de ces datas
		*
		* \return
		*		-  0: Pas d'erreur
		*		- -1: Erreur WSA 
	  */
	sint8 send(uint8 * datas,  uint32	taille);
		
	/**	Permet de verifier si des datas sont en attente dans le socket et de les recuperer
		*	
		*	\return	
		*	  -	 0:	aucun carac	recus
		*	  -	-1:	erreur WSA (appeler	WSAGetLastError)
		*	  -	>0:	nombre d'octets	recus
		*/
	sint16 receive(void);

	/**	Permet d'activer ou non l'algo de Nagle qui bufferise des datas avant d'envoyer 
		* pour les grouper dans le meme message. Quand cet algo est disabled, chaque send 
		* provoque l'emission d'une trame
		*	
		*	\return	
		*	  -	 0:	aucun carac	recus
		*	  -	-1:	erreur WSA (appeler	WSAGetLastError)
		*/
	sint8 enableBuffering(bool enable)
	{
		_UseNaggle = enable;
		enable = !enable;
		if(setsockopt(this->_Socket,IPPROTO_TCP,TCP_NODELAY,(char*)&enable,sizeof(bool)) == SOCKET_ERROR)
		{
			Log::log(Log::ENGINE_ERROR,(string("NYConnectedNet::enableBuffering Error enable TCP_NODELAY ") + toString(WSAGetLastError())).c_str());	
			return -1;
		}
		return 0;
	}
		

};

#endif