// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin developers
// Copyright (c) 2017 Empinel/The Bitcoin Developers
// Copyright (c) 2017 CEVAP Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"
#include "amount.h"
#include "globals.h"
#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, const uint64_t nTime, const uint32_t nNonce, const uint32_t nBits, const int32_t nVersion, const CAmount& genesisReward)
{
	std::vector<CTxIn> vin;
	vin.resize(1);
	vin[0].scriptSig = CScript() << nTime << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
	std::vector<CTxOut> vout;
	vout.resize(1);
	vout[0].nValue = genesisReward;
	vout[0].scriptPubKey = genesisOutputScript;
	CTransaction txNew(1, nTime, vin, vout, 0);
		
    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = genesis.BuildMerkleTree();

    return genesis;
}

static CBlock CreateGenesisBlock(uint64_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
	const char* pszTimestamp = "The SuperCellCoin was started at 2018/2/3,based on a new idea of super-cell masternodes.";
    const CScript genesisOutputScript = CScript() << ParseHex("045622582bdfad9366cdff9652d35a562af17ea4e3462d32cd988b32919ba2ff4bc806485be5228185ad3f75445039b6e744819c4a63304277ca8d20c99a6acec8") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xc2;
        pchMessageStart[1] = 0xe3;
        pchMessageStart[2] = 0xd6;
        pchMessageStart[3] = 0xc8;
        vAlertPubKey = ParseHex("040fd972dba056779d9f998cba8d5866e47fb875fd8cb9c4d36baf88db738a6ffbc581e0fad7f2f129c7f814d81baeda567a3735aaf0bfbc339f40359d4a52b4bf");
        nDefaultPort = DEFAULT_PORT;
        nRPCPort = DEFAULT_RPCPORT;
        nProofOfWorkLimit = uint256S("000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        nProofOfStakeLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        nTargetSpacing = TARGET_SPACKING;
        nTargetTimespan = 7 * 24 * 60 * 60; // one week

	genesis = CreateGenesisBlock(GENESIS_BLOCK_TIME, 224490, 0x1e00ffff, 1, (0 * COIN));
	hashGenesisBlock = genesis.GetHash();
/*
	for(int ii = 0 ;ii<1000000;ii++) {
		genesis = CreateGenesisBlock(GENESIS_BLOCK_TIME, ii, 0x1e00ffff,1, 0 * COIN);
		printf("nNonce = %9u,hash=",ii);
		const std::string &str = genesis.GetHash().GetHex();
		fwrite(str.data(), 1, str.size(), stdout);
		printf(",root=");
		const std::string &str2 = genesis.hashMerkleRoot.GetHex();
		fwrite(str2.data(), 1, str2.size(), stdout);
		printf("\n");
	}
*/
//
	
        assert(hashGenesisBlock == uint256("0x0000070cef98194093249b1571925396d8fe5944498e669540cb40f8aa9ea190"));
        assert(genesis.hashMerkleRoot == uint256("0xcc196acbef54cee12253a4247c76e28291fe2f3c81ae5535a01013b792bae203"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,125);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,90);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,163);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,40);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

	vSeeds.push_back(CDNSSeedData("23.91.97.27", "23.91.97.27"));
	vSeeds.push_back(CDNSSeedData("106.75.99.86", "106.75.99.86"));
	vSeeds.push_back(CDNSSeedData("23.248.162.212","23.248.162.212"));
        
        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

	nPoolMaxTransactions = 3;
        strStashedsendPoolDummyAddress = STASHED_DUMMY_ADDRESS; 
        nLastPOWBlock 	= LAST_POW_BLOCK; 
        
        //nFork1Height = 176500;
        //nFork1Time = 1497541280;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xdb;
        pchMessageStart[1] = 0x86;
        pchMessageStart[2] = 0xfc;
        pchMessageStart[3] = 0x69;
        vAlertPubKey = ParseHex("");
        nDefaultPort = 27170;
        nRPCPort = 27175;
        strDataDir = "testnet";
   
        nProofOfWorkLimit = uint256S("000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        nProofOfStakeLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        nTargetSpacing = 64;
        nTargetTimespan = 7 * 24 * 60 * 60; // one week

	genesis = CreateGenesisBlock(1491737471, 1603027, 0x1e00ffff, 1, (1 * COIN));
        
	hashGenesisBlock = genesis.GetHash();
	
	//assert(hashGenesisBlock == uint256("0x0000002bed128b6b2a62bd8edd4e6f8a414eac38e256aa0194adb8c93fe18132"));		
	//assert(genesis.hashMerkleRoot == uint256("0x24c7b9bada3984f99ec9072672d3f7180af711b5eed5b82b321848b973b4a41e"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,97);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,239);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,40);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds.clear();
        vSeeds.clear();
	vSeeds.push_back(CDNSSeedData("seeder.baseserv.com", "testnet.seeder.baseserv.com"));
        vSeeds.push_back(CDNSSeedData("seeder.uksafedns.net", "testnet.seeder.uksafedns.net"));
        
        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

	nPoolMaxTransactions = 3;
        strStashedsendPoolDummyAddress = "gCJDCcmcVZcfnwAZdEt7dg5s5jjAbDp9dZdhXAmP5NM";
        nLastPOWBlock 	= 300;
        
        nFork1Height = 75000;
        nFork1Time = 1497209344;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;

};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    
    bool fTestNet = GetBoolArg("-testnet", false);
    
    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
