/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notification.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 20:07:08 by diroyer           #+#    #+#             */
/*   Updated: 2023/08/21 10:13:41 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NOTIFICATION_HPP
# define NOTIFICATION_HPP

class notification {
	public:
		inline virtual ~notification() {} ;
		virtual void	notify(void) = 0;
		virtual int		getFd(void) = 0;
		virtual void	disconnect(void) = 0;
	private:
};

#endif
