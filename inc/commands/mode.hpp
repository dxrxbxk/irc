/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:04:15 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/03 04:00:52 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MODE_HPP
# define MODE_HPP

#include "command.hpp"

class Mode : public Command {

	public:

		Mode(Connexion&, Message&);
		~Mode(void);

		void execute(void);

		static Command* create(Connexion&, Message&);

	private:

		bool	valid_mode(char c);

};

#endif
