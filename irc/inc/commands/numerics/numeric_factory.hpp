/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric_factory.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 20:27:38 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/03 03:18:27 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERIC_FACTORY_HPP
# define NUMERIC_FACTORY_HPP

# include <map>
# include <string>

# include "numerics.hpp"

class Connexion;

// class NumericFactory {
//
// 	public:
//
// 		typedef Reply::ret_type (*fptr_t)(Reply::arg_type);
//
// 		typedef std::map<Reply::code, fptr_t> map_t;
//
// 		static std::string	handle_numeric(Reply::code, ClientInfo&);
//
// 	private:
//
// 		static NumericFactory& shared(void);
//
// 		NumericFactory(void);
// 		~NumericFactory(void);
//
// 		static map_t init(void);
//
// 		map_t fmap;
//
// };


#endif
