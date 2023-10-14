#include "pass.hpp"
#include "numerics.hpp"
#include "server.hpp"
#include "crypt.hpp"

Pass::Pass(Connexion& conn, Message& msg)
: Command(conn, msg) {}

Pass::~Pass(void) {}

int		Pass::check_password(const std::string& password) {
#if defined CRYPT
	static std::string salt = extractSalt(Server::shared().password());

	if (encryptPassword(_msg.params_first(), salt.c_str()) != Server::shared().password()) {

		_conn.enqueue(RPL::passwd_mismatch(_conn.info()));
		return -1;
	}
#else
	if (_msg.params_first() != Server::shared().password()) {

		_conn.enqueue(RPL::passwd_mismatch(_conn.info()));
		return -1;
	}
#endif
	return 0;
}

Command::ret_type Pass::execute(void) {
	if (_conn.registered()) {
		_conn.enqueue(RPL::already_registered(_conn.info()));
		return 0;
	}

	if (not _msg.has_params()) {
		_conn.enqueue(RPL::need_more_params(_conn.info(), _msg.params_first()));
		return -1;
	}

	if (check_password(_msg.params_first()) == -1) {
		_server.add_rm_list(_conn);
	}

	_conn.tracker(PASS);
	return 0;
}

Command* Pass::create(Connexion& conn, Message& msg) {
	return new Pass(conn, msg);
}
