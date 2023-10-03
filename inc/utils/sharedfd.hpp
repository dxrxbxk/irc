/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sharedfd.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 19:48:31 by diroyer           #+#    #+#             */
/*   Updated: 2023/08/21 20:08:10 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_FD
# define SHARED_FD

# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <iostream>

class Shared_fd {

	public:

		Shared_fd(void);
		Shared_fd(const int);
		Shared_fd(const Shared_fd&);

		operator int(void) const;

		Shared_fd& operator=(const Shared_fd&);


		~Shared_fd(void);

	private:

		int _fd;
		int* _count;
};

#endif
