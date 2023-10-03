/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_info.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 00:22:07 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/03 02:59:45 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEND_INFO_HPP
# define SEND_INFO_HPP

# include "numerics.hpp"

struct SendInfo {
	std::string			rpl;
	std::string			buffer;
	
	SendInfo() : rpl(), buffer() {};
	~SendInfo() {};
};

#endif
