/*
 *  Command: PRIVMSG
Parameters: <receiver>{,<receiver>} <text to be sent>

PRIVMSG is used to send private messages between users.  <receiver>
is the nickname of the receiver of the message.  <receiver> can also
be a list of names or channels separated with commas.

The <receiver> parameter may also me a host mask  (#mask)  or  server
mask  ($mask).   In  both cases the server will only send the PRIVMSG
to those who have a server or host matching the mask.  The mask  must
have at  least  1  (one)  "."  in it and no wildcards following the
last ".".  This requirement exists to prevent people sending messages
to  "#*"  or "$*",  which  would  broadcast  to  all  users; from
experience, this is abused more than used responsibly and properly.
Wildcards are  the  '*' and  '?'   characters.   This  extension  to
the PRIVMSG command is only available to Operators.

Numeric Replies:

ERR_NORECIPIENT                 ERR_NOTEXTTOSEND
ERR_CANNOTSENDTOCHAN            ERR_NOTOPLEVEL
ERR_WILDTOPLEVEL                ERR_TOOMANYTARGETS
ERR_NOSUCHNICK
RPL_AWAY

Examples:

:Angel PRIVMSG Wiz :Hello are you receiving this message ?
; Message from Angel to Wiz.

PRIVMSG Angel :yes I'm receiving it !receiving it !'u>(768u+1n) .br ;
Message to Angel.

PRIVMSG jto@tolsun.oulu.fi :Hello !
; Message to a client on server
*/

#include "privmsg.hpp"
#include "server.hpp"

Privmsg::Privmsg(Connexion& conn, Message& msg)
	: Command(conn, msg) {}

	Privmsg::~Privmsg(void) {}

	Command::ret_type	 Privmsg::execute(void) {

		if (not _msg.has_params()) {
			_conn.enqueue(RPL::no_recipient(_conn.info(), _msg.command()));
			return 0;
		}
		else if (not _msg.has_trailing() && not _msg.has_dcc()) {
			_conn.enqueue(RPL::no_text_to_send(_conn.info()));
			return 0;
		}

		if (_msg.params_first()[0] == '#') {
			Logger::debug("PRIVMSG: channel" + _msg.params_first());
			if ( not _server.channel_exist(_msg.params_first())) {
				_conn.enqueue(RPL::no_such_channel(_conn.info(), _msg.params_first()));
				return 0;
			}
			Channel& channel = _server.get_channel(_msg.params_first());
			Logger::debug("PRIVMSG: trailing");
			channel.broadcast(gen_reply(_msg.trailing()), _conn);
		}
		else {
			Logger::debug("PRIVMSG: user");
			if (not _server.nick_exist(_msg.params_first())) {
				_conn.enqueue(RPL::no_such_nick(_conn.info(), _msg.params_first()));
				return 0;
			}
			Connexion& user = _server.get_conn(_msg.params_first());
			if (_msg.has_dcc()) {
				user.enqueue(gen_reply(_msg.full_dcc()));
				return 0;
			}
			user.enqueue(gen_reply(_msg.trailing()));
			// handle_user
		}
		//		Logger::debug(msg);
		return 0;
	}

Command* Privmsg::create(Connexion& conn, Message& msg) {
	return new Privmsg(conn, msg);
}
