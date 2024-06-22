#pragma once

#include "PacketPriority.h"
#include "NetworkTypes.h"
#include "Export.h"

namespace RakNet
{

/// On failed directed sends, RakNet can call an alternative send function to use.
class RAK_DLL_EXPORT RouterInterface
{
public:
	virtual bool Send( const char *data, unsigned bitLength, PacketPriority priority, PacketReliability reliability, char orderingChannel, PlayerID playerId )=0;
};

} // namespace RakNet
