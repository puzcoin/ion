// Copyright (c) 2009-2017 The Bitcoin developers
// Copyright (c) 2017 CEVAP Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "proofs.h"
#include "txdb.h"
#include "main.h"
#include "uint256.h"

static const int nCheckpointSpan = 5000;

namespace Checkpoints
{
	typedef std::map<int, uint256> MapCheckpoints;
    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (       0,	Params().HashGenesisBlock())
//        (       1,	uint256("0x000000ed2f68cd6c7935831cc1d473da7c6decdb87e8b5dba0afff0b00002690") ) // Premine
//        (      10,	uint256("0x00000032f5a96d31d74b380c0336445baccb73a01bdbedec868283019bad7016") ) // Confirmation of Premine
//	    (    1000,	uint256("0x0000000144b22b0af9bced65256d5eccc4e3f112a89bdb0f08ab8dc2a6145b56") ) // Last POW Block
//        (  10000,  uint256("0x96dbe12ebd92b4df5d1d182e30417899801f01724345c968057d12af38b4eb90") ) // 2.1.6.3
;

    static MapCheckpoints mapCheckpointsTestnet =
	boost::assign::map_list_of
	(       0,      Params().HashGenesisBlock())
	(       1,      uint256("0x000000b86fdd7f2ae9e9973e73790492989113075a2d5c581495ab7bb2ad5711") ) // First block 
	(      10,      uint256("0x0000008c29a7d680710d1cc821d79f33ba0159bc26d9e233bccfabd668b0430e") ) // Confirmation of first block
	(     300,      uint256("0x000000125e3e3d005aa72281e02b4ebaabc2fa9aed817b9365a8d29bb7901c10") ) // Last POW Block
	(   75000,      uint256("0x20faec3994dac57fb88748e29139974522c91036e1bf8ff204c769a90fab5a12") ) // Fork June 2017
	(   85000,      uint256("0x43ee28cd1f804dafe05ef120569726e50e9e6f2b634746925742cbd9f738c201") ) // Fork June 2017
	(   88800,      uint256("0x2807b46cbfa28a2d4854215b40f4db64b62fc71a1d010844d67d7c03888ce692") ) // Fork June 2017
;   

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        if (checkpoints.empty())
            return 0;
        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }

    // Automatically select a suitable sync-checkpoint 
    const CBlockIndex* AutoSelectSyncCheckpoint()
    {
        const CBlockIndex *pindex = pindexBest;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
            pindex = pindex->pprev;
        return pindex;
    }

    // Check against synchronized checkpoint
    bool CheckSync(int nHeight)
    {
        const CBlockIndex* pindexSync = AutoSelectSyncCheckpoint();
        if (nHeight <= pindexSync->nHeight){
            return false;
        }
        return true;
    }
}
