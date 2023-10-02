/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:04:15 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/02 00:04:04 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MODE_HPP
# define MODE_HPP

#include "command.hpp"

class Mode : public Command {

	public:

		Mode(Connexion&, Message&);
		~Mode(void);

		bool evaluate(void);
		void execute(void);

		static Command* create(Connexion&, Message&);

	private:
	
		void	user_mode(void);
		bool	valid_mode(char c);

};

#endif
