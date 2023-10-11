/* **************************************************************************
 
      Command: INVITE
   Parameters: <nickname> <channel>

   The INVITE message is used to invite users to a channel.  The
   parameter <nickname> is the nickname of the person to be invited to
   the target channel <channel>.  There is no requirement that the
   channel the target user is being invited to must exist or be a valid
   channel.  To invite a user to a channel which is invite only (MODE
   +i), the client sending the invite must be recognised as being a
   channel operator on the given channel.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_NOSUCHNICK
           ERR_NOTONCHANNEL                ERR_USERONCHANNEL
           ERR_CHANOPRIVSNEEDED
           RPL_INVITING                    RPL_AWAY

   Examples:

   :Angel INVITE Wiz #Dust         ; User Angel inviting WiZ to channel
                                   #Dust

   INVITE Wiz #Twilight_Zone       ; Command to invite WiZ to
                                   #Twilight_zone

************************************************************* */

#include "invite.hpp"
#include "mode.hpp"
#include "server.hpp"
#include "utils.hpp"

Invite::Invite(Connexion& c, Message& m) : Command(c, m) {}

Invite::~Invite(void) {}

Command::ret_type	Invite::execute(void) {
	std::string nickname = _msg.params(0);
	std::string channel_name = _msg.params(1);
	Logger::debug("channel name : " + channel_name);
	Logger::debug("nickname : " + nickname);

	if (_msg.params_size() < 2) {
		_conn.enqueue(RPL::need_more_params(_conn.info(), _msg.command()));
		return 0;
	}
	Channel& channel = _server.channel(channel_name);

	if (not _server.nick_exist(nickname)) {
		_conn.enqueue(RPL::no_such_nick(_conn.info(), nickname));
		return 0;
	}
//	else if (not channel.user_in(_conn.nickname())) {
//		_conn.enqueue(RPL::not_on_channel(_conn.info(), channel_name));
//		return 0;
//	}
	else if (not channel.is_op(_conn.nickname())) {
		_conn.enqueue(RPL::chano_privs_needed(_conn.info(), channel_name));
		return 0;
	}
	else if (channel.user_in(nickname)) {
		_conn.enqueue(RPL::user_on_channel(_conn.info(), nickname, channel_name));
		return 0;
	}
	Connexion& target = _server.get_conn(nickname);
	Logger::debug(target.nickname());
	target.enqueue(RPL::inviting(_conn.info(), nickname, channel_name));
	channel.invite(target.nickname());


//	Connexion& target = _server.get_conn(nickname);

	return 0;
}

Command* Invite::create(Connexion& c, Message& m) {
	return new Invite(c, m);
}
