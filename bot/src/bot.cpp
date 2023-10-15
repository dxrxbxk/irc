#include "bot.hpp"
#include "utils.hpp"

Bot::Bot(const std::string &port, const std::string &pass) :
	_sfd(-1),
	_epoll_fd(-1),
	_buffer_in(),
	_buffer_out(),
	_wait_out(false),  
	_nickname("bot"),
	_username("Mikey"), 
	_hostname("bot.42.fr"),
	_servername("irc.42.fr"),
	_running(false),
	_pass(pass)
{
	create_socket("localhost", port.c_str());
	_epoll_fd = epoll_create(1);
	if (_epoll_fd == -1) {
		throw std::runtime_error(handleSysError("epoll_create"));
	}
	add_event();
}

Bot::~Bot() {}

/*------------------------ name accessors ----------------------*/

const std::string Bot::fullname(void)  const {
		return (nickname() + "!" + username() + "@" + hostname());
}

const std::string& Bot::nickname(void) const {
	return _nickname;
}

const std::string& Bot::username(void) const {
	return _username;
}

const std::string& Bot::hostname(void) const {
	return _hostname;
}

void	Bot::read_input(void) {
	ssize_t		readed;
	char		buffer[BUFFER_SIZE];

	readed = ::recv(_sfd, buffer, BUFFER_SIZE, 0);
	if (readed == -1)
		throw::std::runtime_error(handleSysError("recv"));
	else {
		_buffer_in.append(buffer, readed);
	}
}

Bot::vec_str	Bot::check_crlf(void) {
	std::string::size_type	pos;
	vec_str					l_msg;
	while ((pos = _buffer_in.find("\r\n")) != std::string::npos) {
		l_msg.push_back(_buffer_in.substr(0, pos + 2));
		_buffer_in.erase(0, pos + 2);
	}
	return l_msg;
}

bool	is_numerics(const std::string& str) {
	for (std::string::const_iterator i = str.begin(); i != str.end(); ++i) {
		if (!std::isdigit(*i))
			return false;
	}
	return true;
}


void Bot::read(void) {
	read_input();

	const vec_str l_msg = check_crlf();

	for (vec_str::const_iterator i = l_msg.begin(); i != l_msg.end(); ++i) {

//		PRINT("message recu: " << *i);

		try {
			// parse raw message
			Message msg = Parser::parse(*i);

			msg.print();

			if (not is_numerics(msg.command())) {
				Command* cmd = CommandFactory::create(*this, msg);

			if (cmd == NULL) {
				//Logger::info(msg.command() + " command not found");
				ERROR(msg.trailing() + " command not found");
			}
			else {
				cmd->execute();
				delete cmd;
			}
			}
		} catch (const std::exception& e) {
			ERROR(e.what());
		}
	}
}

void	Bot::enqueue(const std::string &msg) {
	_buffer_out.append(msg);
	if (not _wait_out) {
		mod_event(EPOLLOUT);
		_wait_out = true;
	}
}

void Bot::write(void) {
	PRINT("message envoye: " << _buffer_out);
	if (::send(_sfd, _buffer_out.c_str(), _buffer_out.size(), 0) == -1) {
		throw std::runtime_error(handleSysError("send"));
	}
	_buffer_out.clear();
	mod_event(EPOLLIN);
	_wait_out = false;

}

void	Bot::ddos(const std::string& msg) {
	if (::send(_sfd, msg.c_str(), msg.size(), 0) == -1) {
		throw std::runtime_error(handleSysError("send"));
	}
}

int Bot::fd(void) const {
	return _sfd;
}

void	Bot::stop(void) {
	_running = false;
}

void Bot::disconnect(void) {
	std::cout << "disconnect" << std::endl;
	close(_sfd);
	close(_epoll_fd);
	stop();
}

void	Bot::add_event(void) {
	struct epoll_event ev;
	memset(&ev, 0, sizeof(struct epoll_event));
	ev.events = EPOLLOUT | EPOLL_ERRORS;
	ev.data.fd = _sfd;
	if (epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, _sfd, &ev) == -1) {
		throw std::runtime_error(handleSysError("epoll_ctl: add"));
	}
}

void	Bot::mod_event(int flag) {
	struct epoll_event ev;
	memset(&ev, 0, sizeof(struct epoll_event));
	ev.events = flag | EPOLL_ERRORS;
	ev.data.fd = _sfd;
	if (epoll_ctl(_epoll_fd, EPOLL_CTL_MOD, _sfd, &ev) == -1) {
		throw std::runtime_error(handleSysError("epoll_ctl: mod"));
	}
}

void	Bot::del_event(void) {
	if (epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, _sfd, NULL) == -1) {
		throw std::runtime_error(handleSysError("epoll_ctl: del"));
	}
}

void	Bot::login(void) {
	enqueue("PASS " + _pass + "\r\n");
	enqueue("NICK " + nickname() + "\r\n");
	enqueue("USER " + username() + " 0 * :" + hostname() + "\r\n");
}

void	Bot::run(void) {
	login();
	_running = true;
	while (_running) {
		poller();
	}
}

#define MAX_EVENTS 100

void	Bot::poller(void) {
	struct epoll_event ev[MAX_EVENTS];

	int nfds = epoll_wait(_epoll_fd, ev, 1, -1);

	if (nfds == -1) {
		throw std::runtime_error(handleSysError("epoll_wait"));
	}

	for (int i = 0; i < nfds; ++i) {

		if (ev[i].events & EPOLL_ERRORS) {
			disconnect();
		}
		else if (ev[i].events & EPOLLIN) {
			read();
		}
		else if (ev[i].events & EPOLLOUT) {
			write();
		}
	}
}

void	Bot::create_socket(const char *host, const char *port)
{
	int              sfd, s;
	struct addrinfo  hints;
	struct addrinfo  *result, *rp;


	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
	hints.ai_flags = 0;
	hints.ai_protocol = 0;          /* Any protocol */

	s = getaddrinfo(host, port, &hints, &result);
	if (s != 0) {
		throw std::runtime_error(handleGaiError(s));
	}

	for (rp = result; rp != NULL; rp = rp->ai_next) {
		sfd = socket(rp->ai_family, rp->ai_socktype,
				rp->ai_protocol);
		if (sfd == -1)
			continue;

		if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
			break;                  /* Success */

		close(sfd);
	}

	freeaddrinfo(result);           /* No longer needed */

	if (rp == NULL) {               /* No address succeeded */
		throw std::runtime_error(handleSysError("Could not connect"));
	}
	_sfd = sfd;
}
