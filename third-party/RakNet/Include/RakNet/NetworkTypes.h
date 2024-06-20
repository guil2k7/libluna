/// \file
/// \brief Types used by RakNet, most of which involve user code.
///
/// This file is part of RakNet Copyright 2003 Kevin Jenkins.
///
/// Usage of RakNet is subject to the appropriate license agreement.
/// Creative Commons Licensees are subject to the
/// license found at
/// http://creativecommons.org/licenses/by-nc/2.5/
/// Single application licensees are subject to the license found at
/// http://www.rakkarsoft.com/SingleApplicationLicense.html
/// Custom license users are subject to the terms therein.
/// GPL license users are subject to the GNU General Public
/// License as published by the Free
/// Software Foundation; either version 2 of the License, or (at your
/// option) any later version.

#pragma once

#include "RakNetDefines.h"
#include "Export.h"

/// Forward declaration
namespace RakNet
{
class BitStream;

/// Given a number of bits, return how many bytes are needed to represent that.
#define BITS_TO_BYTES(x) (((x)+7)>>3)
#define BYTES_TO_BITS(x) ((x)<<3)

/// \sa NetworkIDGenerator.h
typedef unsigned char UniqueIDType;
typedef unsigned short PlayerIndex;
typedef unsigned char RPCID;

/// First byte of a network message
typedef unsigned char MessageID;

// Define __GET_TIME_64BIT if you want to use large types for GetTime (takes more bandwidth when you transmit time though!)
// You would want to do this if your system is going to run long enough to overflow the millisecond counter (over a month)
#ifdef __GET_TIME_64BIT
typedef long long RakNetTime;
typedef long long RakNetTimeNS;
#else
typedef unsigned int RakNetTime;
typedef long long RakNetTimeNS;
#endif

/// \brief Unique identifier for a system.
/// Corresponds to a network address
struct RAK_DLL_EXPORT PlayerID
{
	///The peer address from inet_addr.
	unsigned int binaryAddress;
	///The port number
	unsigned short port;

	// Return the playerID as a string in the format <IP>:<Port>
	// Note - returns a static string.  Not thread-safe or safe for multiple calls per line.
	char *ToString(bool writePort=true) const;

	// Sets the binary address part from a string.  Doesn't set the port
	void SetBinaryAddress(const char *str);

	PlayerID& operator = ( const PlayerID& input )
	{
		binaryAddress = input.binaryAddress;
		port = input.port;
		return *this;
	}

	bool operator==( const PlayerID& right ) const;
	bool operator!=( const PlayerID& right ) const;
	bool operator > ( const PlayerID& right ) const;
	bool operator < ( const PlayerID& right ) const;
};

struct RAK_DLL_EXPORT NetworkID
{
	// Set this to true to use peer to peer mode for NetworkIDs.
	// Obviously the value of this must match on all systems.
	// True, and this will write the playerId portion with network sends.  Takes more bandwidth, but NetworkIDs can be locally generated
	// False, and only localSystemId is used.
	static bool peerToPeerMode;

	// In peer to peer, we use both playerId and localSystemId
	// In client / server, we only use localSystemId
	PlayerID playerId;
	unsigned short localSystemId;

	NetworkID& operator = ( const NetworkID& input );

	static bool IsPeerToPeerMode(void);
	static void SetPeerToPeerMode(bool isPeerToPeer);
	bool operator==( const NetworkID& right ) const;
	bool operator!=( const NetworkID& right ) const;
	bool operator > ( const NetworkID& right ) const;
	bool operator < ( const NetworkID& right ) const;
};

/// Size of PlayerID data
constexpr int PlayerID_Size = 6;

/// This represents a user message from another system.
struct Packet
{
	/// Server only - this is the index into the player array that this playerId maps to
	PlayerIndex playerIndex;

	/// The system that send this packet.
	PlayerID playerId;

	/// The length of the data in bits
	unsigned int bitSize;

	/// The data from the sender
	unsigned char* data;

	/// @internal
	/// Indicates whether to delete the data, or to simply delete the packet.
	bool deleteData;
};

class RakPeerInterface;

///  Index of an unassigned player
const PlayerIndex UNASSIGNED_PLAYER_INDEX = 0xFFFF;

/// Index of an invalid PlayerID
const PlayerID UNASSIGNED_PLAYER_ID =
{
	0xFFFFFFFF, 0xFFFF
};

/// Unassigned object ID
const NetworkID UNASSIGNED_NETWORK_ID =
{
	{0xFFFFFFFF, 0xFFFF}, 65535
};

const int PING_TIMES_ARRAY_SIZE = 5;
} // namespace RakNet

