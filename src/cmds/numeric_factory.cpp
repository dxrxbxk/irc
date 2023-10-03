/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric_factory.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 20:26:44 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/03 03:29:14 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "numeric_factory.hpp"

// NumericFactory::NumericFactory(void)
// : fmap(init()) {}
//
// NumericFactory::~NumericFactory(void) {}
//
// NumericFactory& NumericFactory::shared(void) {
// 		static NumericFactory instance;
// 		return instance;
// }
//
// std::string	NumericFactory::handle_numeric(Reply::code code, ClientInfo& cinfo) {
// 	if (shared().fmap[code] == NULL)
// 		throw std::runtime_error("map error access");
// 	return shared().fmap[code](cinfo);
// }
//
//
// NumericFactory::map_t NumericFactory::init(void) {
// 	map_t fmap;
//
// 	using namespace Reply;
//
// 	fmap[RplNone        	 ] = NULL;
// 	fmap[RplWelcome          ] = &welcome;
// 	fmap[RplYourHost         ] = NULL;
// 	fmap[RplCreated          ] = NULL;
// 	fmap[RplMyInfo           ] = NULL;
// 	fmap[RplMap              ] = NULL;
// 	fmap[RplEndOfMap         ] = NULL;
// 	fmap[RplMotdStart        ] = NULL;
// 	fmap[RplMotd             ] = NULL;
// 	fmap[RplMotdAlt          ] = NULL;
// 	fmap[RplMotdAlt2         ] = NULL;
// 	fmap[RplMotdEnd          ] = &end_of_motd;
// 	fmap[RplUModeIs          ] = NULL;
// 	fmap[RplUserHost         ] = NULL;
// 	fmap[RplIsOn             ] = NULL;
// 	fmap[RplAway             ] = NULL;
// 	fmap[RplUnAway           ] = NULL;
// 	fmap[RplNowAway          ] = NULL;
// 	fmap[RplWhoisHelper      ] = NULL;
// 	fmap[RplWhoIsUser        ] = NULL;
// 	fmap[RplWhoIsServer      ] = NULL;
// 	fmap[RplWhoIsOperator    ] = NULL;
// 	fmap[RplWhoIsIdle        ] = NULL;
// 	fmap[RplEndOfWhois       ] = NULL;
// 	fmap[RplWhoIsChannels    ] = NULL;
// 	fmap[RplWhoWasUser       ] = NULL;
// 	fmap[RplEndOfWhoWas      ] = NULL;
// 	fmap[RplWhoReply         ] = NULL;
// 	fmap[RplEndOfWho         ] = NULL;
// 	fmap[RplUserIPs          ] = NULL;
// 	fmap[RplUserIP           ] = NULL;
// 	fmap[RplListStart        ] = NULL;
// 	fmap[RplList             ] = NULL;
// 	fmap[RplListEnd          ] = NULL;
// 	fmap[RplLinks            ] = NULL;
// 	fmap[RplEndOfLinks       ] = NULL;
// 	fmap[RplUniqOpIs         ] = NULL;
// 	fmap[RplChannelModeIs    ] = NULL;
// 	fmap[RplChannelUrl       ] = NULL;
// 	fmap[RplChannelCreated   ] = NULL;
// 	fmap[RplNoTopic          ] = NULL;
// 	fmap[RplTopic            ] = NULL;
// 	fmap[RplTopicSetBy       ] = NULL;
// 	fmap[RplNamReply         ] = NULL;
// 	fmap[RplEndOfNames       ] = NULL;
// 	fmap[RplInviting         ] = NULL;
// 	fmap[RplSummoning        ] = NULL;
// 	fmap[RplInviteList       ] = NULL;
// 	fmap[RplEndOfInviteList  ] = NULL;
// 	fmap[RplExceptList       ] = NULL;
// 	fmap[RplEndOfExceptList  ] = NULL;
// 	fmap[RplBanList          ] = NULL;
// 	fmap[RplEndOfBanList     ] = NULL;
// 	fmap[RplVersion          ] = NULL;
// 	fmap[RplInfo             ] = NULL;
// 	fmap[RplEndOfInfo        ] = NULL;
// 	fmap[RplYoureOper        ] = NULL;
// 	fmap[RplRehashing        ] = NULL;
// 	fmap[RplYoureService     ] = NULL;
// 	fmap[RplTime             ] = NULL;
// 	fmap[RplUsersStart       ] = NULL;
// 	fmap[RplUsers            ] = NULL;
// 	fmap[RplEndOfUsers       ] = NULL;
// 	fmap[RplNoUsers          ] = NULL;
// 	fmap[RplServList         ] = NULL;
// 	fmap[RplServListEnd      ] = NULL;
// 	fmap[RplAdminMe          ] = NULL;
// 	fmap[RplAdminLoc1        ] = NULL;
// 	fmap[RplAdminLoc2        ] = NULL;
// 	fmap[RplAdminEMail       ] = NULL;
// 	fmap[RplTryAgain         ] = NULL;
// 	fmap[RplTraceLink        ] = NULL;
// 	fmap[RplTraceConnecting  ] = NULL;
// 	fmap[RplTraceHandshake   ] = NULL;
// 	fmap[RplTraceUnknown     ] = NULL;
// 	fmap[RplTraceOperator    ] = NULL;
// 	fmap[RplTraceUser        ] = NULL;
// 	fmap[RplTraceServer      ] = NULL;
// 	fmap[RplTraceService     ] = NULL;
// 	fmap[RplTraceNewType     ] = NULL;
// 	fmap[RplTraceClass       ] = NULL;
// 	fmap[RplTraceReconnect   ] = NULL;
// 	fmap[RplTraceLog         ] = NULL;
// 	fmap[RplTraceEnd         ] = NULL;
// 	fmap[RplStatsLinkInfo    ] = NULL;
// 	fmap[RplStatsCommands    ] = NULL;
// 	fmap[RplStatsCLine       ] = NULL;
// 	fmap[RplStatsNLine       ] = NULL;
// 	fmap[RplStatsILine       ] = NULL;
// 	fmap[RplStatsKLine       ] = NULL;
// 	fmap[RplStatsPLine       ] = NULL;
// 	fmap[RplStatsQLine       ] = NULL;
// 	fmap[RplStatsELine       ] = NULL;
// 	fmap[RplStatsDLine       ] = NULL;
// 	fmap[RplStatsLLine       ] = NULL;
// 	fmap[RplStatsuLine       ] = NULL;
// 	fmap[RplStatsoLine       ] = NULL;
// 	fmap[RplStatsHLine       ] = NULL;
// 	fmap[RplStatsGLine       ] = NULL;
// 	fmap[RplStatsULine       ] = NULL;
// 	fmap[RplStatsZLine       ] = NULL;
// 	fmap[RplStatsYLine       ] = NULL;
// 	fmap[RplEndOfStats       ] = NULL;
// 	fmap[RplStatsUptime      ] = NULL;
// 	fmap[RplGLineList        ] = NULL;
// 	fmap[RplEndOfGLineList   ] = NULL;
// 	fmap[RplSilenceList      ] = NULL;
// 	fmap[RplEndOfSilenceList ] = NULL;
// 	fmap[RplLUserClient      ] = NULL;
// 	fmap[RplLUserOp          ] = NULL;
// 	fmap[RplLUserUnknown     ] = NULL;
// 	fmap[RplLUserChannels    ] = NULL;
// 	fmap[RplLUserMe          ] = NULL;
// 	fmap[RplLUserLocalUser   ] = NULL;
// 	fmap[RplLUserGlobalUser  ] = NULL;
// 	fmap[ErrNoSuchNick       ] = NULL;
// 	fmap[ErrNoSuchServer     ] = NULL;
// 	fmap[ErrNoSuchChannel    ] = NULL;
// 	fmap[ErrCannotSendToChan ] = NULL;
// 	fmap[ErrTooManyChannels  ] = NULL;
// 	fmap[ErrWasNoSuchNick    ] = NULL;
// 	fmap[ErrTooManyTargets   ] = NULL;
// 	fmap[ErrNoColors         ] = NULL;
// 	fmap[ErrNoOrigin         ] = NULL;
// 	fmap[ErrNoRecipient      ] = NULL;
// 	fmap[ErrNoTextToSend     ] = NULL;
// 	fmap[ErrNoTopLevel       ] = NULL;
// 	fmap[ErrWildTopLevel     ] = NULL;
// 	fmap[ErrBadMask          ] = NULL;
// 	fmap[ErrTooMuchInfo      ] = NULL;
// 	fmap[ErrUnknownCommand   ] = NULL;
// 	fmap[ErrNoMotd           ] = NULL;
// 	fmap[ErrNoAdminInfo      ] = NULL;
// 	fmap[ErrFileError        ] = NULL;
// 	fmap[ErrNoNicknameGiven  ] = NULL;
// 	fmap[ErrErroneusNickname ] = NULL;
// 	fmap[ErrNickNameInUse    ] = NULL;
// 	fmap[ErrNickCollision    ] = NULL;
// 	fmap[ErrUnAvailResource  ] = NULL;
// 	fmap[ErrNickTooFast      ] = NULL;
// 	fmap[ErrTargetTooFast    ] = NULL;
// 	fmap[ErrUserNotInChannel ] = NULL;
// 	fmap[ErrNotOnChannel     ] = NULL;
// 	fmap[ErrUserOnChannel    ] = NULL;
// 	fmap[ErrNoLogin          ] = NULL;
// 	fmap[ErrSummonDisabled   ] = NULL;
// 	fmap[ErrUsersDisabled    ] = NULL;
// 	fmap[ErrNotRegistered    ] = NULL;
// 	fmap[ErrNeedMoreParams   ] = NULL;
// 	fmap[ErrAlreadyRegistered] = NULL;
// 	fmap[ErrNoPermForHost    ] = NULL;
// 	fmap[ErrPasswdMistmatch  ] = NULL;
// 	fmap[ErrYoureBannedCreep ] = NULL;
// 	fmap[ErrYouWillBeBanned  ] = NULL;
// 	fmap[ErrKeySet           ] = NULL;
// 	fmap[ErrServerCanChange  ] = NULL;
// 	fmap[ErrChannelIsFull    ] = NULL;
// 	fmap[ErrUnknownMode      ] = NULL;
// 	fmap[ErrInviteOnlyChan   ] = NULL;
// 	fmap[ErrBannedFromChan   ] = NULL;
// 	fmap[ErrBadChannelKey    ] = NULL;
// 	fmap[ErrBadChanMask      ] = NULL;
// 	fmap[ErrNickNotRegistered] = NULL;
// 	fmap[ErrBanListFull      ] = NULL;
// 	fmap[ErrNoPrivileges     ] = NULL;
// 	fmap[ErrChanOPrivsNeeded ] = NULL;
// 	fmap[ErrCantKillServer   ] = NULL;
// 	fmap[ErrRestricted       ] = NULL;
// 	fmap[ErrUniqOPrivsNeeded ] = NULL;
// 	fmap[ErrNoOperHost       ] = NULL;
// 	fmap[ErrUModeUnknownFlag ] = &u_mod_unknown_flag;
// 	fmap[ErrUsersDontMatch   ] = NULL;
// 	fmap[ErrSilenceListFull  ] = NULL;
//
// 	return fmap;
// }
