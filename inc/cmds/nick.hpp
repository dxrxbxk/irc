/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 01:37:54 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/03 00:10:58 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NICK_HPP
# define NICK_HPP

#include "command.hpp"

class Nick : public Command {

	public:

		Nick(Connexion&, Message&);

		~Nick(void);

		SendInfo execute(void);

		static Command* create(Connexion&, Message&);

	private:
		void	add_nick(void);

};

#endif
