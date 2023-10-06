/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 01:37:54 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/03 03:59:14 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NICK_HPP
# define NICK_HPP

#include "command.hpp"

class Nick : public Command {

	public:

		Nick(Connexion&, Message&);

		~Nick(void);

		ret_type execute(void);

		static Command* create(Connexion&, Message&);

	private:

};

#endif
