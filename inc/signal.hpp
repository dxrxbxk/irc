/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 20:56:00 by diroyer           #+#    #+#             */
/*   Updated: 2023/08/21 10:24:42 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HPP
# define SIGNAL_HPP

# include <exception>
# include <iostream>
# include <csignal>

# include "utils.hpp"
# include "notification.hpp"

extern int g_signalPipe[2];

class Signal : public notification {
	public:
		Signal();
		~Signal();

		int		getFd(void);
		void	notify(void);
		void	disconnect(void);
	private:
};

void				readSignalPipe(void);
void				signalManager(void);
void				signalHandler(int signum);
void				signalIgnore(void);


#endif 
