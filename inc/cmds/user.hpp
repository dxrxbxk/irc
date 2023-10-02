/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 01:54:34 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/01 19:43:19 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

#include "command.hpp"
#include <sstream>

class User : public Command {

	public:

		User(Connexion&, Message&);

		~User(void);

		bool evaluate(void);

		void execute(void);

		static Command* create(Connexion&, Message&);

	private:
		void		add_user(void);

		enum	Index {
			USERNAME,
			HOSTNAME,
			SERVERNAME
		};

};

#endif
