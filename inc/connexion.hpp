/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connexion.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:41:28 by diroyer           #+#    #+#             */
/*   Updated: 2023/09/27 16:53:13 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNEXION_HPP
# define CONNEXION_HPP

# include <iostream>
# include <string>
# include <sys/socket.h>
# include <sstream>
# include <map>

# include "notification.hpp"
# include "utils.hpp"
# include "sharedfd.hpp"
# include "parser.hpp"
# include "types.hpp"

# include "command_factory.hpp"

class Connexion : public notification {
	public:
		Connexion();
		Connexion(int fd, std::map<int, Connexion> &ref);
		~Connexion();
		Connexion(const Connexion &copy);
		Connexion&operator=(const Connexion &copy);

		void						notify(void);
		int							getFd(void);
		void						setFd(int fd);
		void						disconnect(void);

	private:
		Shared_fd					sock_fd;
		std::string					buffer;
		std::map<int, Connexion>	*m_ptr;

		void						readInput(void);
		l_str						checkCrlf(void);
};


#endif
