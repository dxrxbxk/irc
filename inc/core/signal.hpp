/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 20:56:00 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/03 00:50:38 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HPP
# define SIGNAL_HPP

# include <exception>
# include <iostream>
# include <csignal>

# include "utils.hpp"
# include "io_event.hpp"


class Signal : public IOEvent {

	public:
		// -- public IOEvent interface ----------------------------------------

		int			fd(void) const;
		void		read(void);
		void		disconnect(void);
		void		write(void);

		// -- public static methods -------------------------------------------

		/* get instance */
		static Signal& shared(void);

		static void signal_manager(void);
		static void signal_ignore(void);
		static void signal_default(void);
		static void	signal_nopipe_manager(void);

	private:

		// -- private constructors --------------------------------------------

		Signal(void);
		~Signal(void);

		// -- private members -------------------------------------------------

		int _pipe[2];

		// -- private static methods ------------------------------------------

		static void signal_handler(int);
		static void signal_no_pipe(int);

};

#endif
