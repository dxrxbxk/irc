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


class Signal {

	public:
		// -- public static methods -------------------------------------------

		/* get instance */
		static Signal& shared(void);

		static void signal_ignore(void);
		static void signal_default(void);
		static void	signal_nopipe_manager(void);

	private:

		// -- private constructors --------------------------------------------

		Signal(void);
		~Signal(void);

		static void signal_no_pipe(int);

};

#endif
