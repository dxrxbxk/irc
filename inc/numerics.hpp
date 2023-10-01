/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numerics.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:12:48 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/01 23:48:54 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERICS_HPP
# define NUMERICS_HPP

# include <string>
# include <sstream>

struct ClientInfo;

class RPL {

	private:
		typedef std::string			ret_type;
		typedef const ClientInfo&	arg_type;

	public:
		static ret_type	welcome(arg_type info);
		static ret_type	end_of_motd(arg_type info);
};

class ERR {
	private:
		typedef std::string			ret_type;
		typedef const ClientInfo&	arg_type;
	
	public:
		static ret_type	u_mod_unknown_flag(arg_type info);
};

#endif
