// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2015-2017 The Keyco developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>


using namespace std;
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
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions

static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of(0, uint256("0x0000042b3b3d829bd8cc5163c9616fc8d9c203812adfadc754282f3aeebcff92"));
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1519732800, // * UNIX timestamp of last checkpoint block
    0,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x0000042b3b3d829bd8cc5163c9616fc8d9c203812adfadc754282f3aeebcff92"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1519732800,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0xd7dc899d1b0cce20c3e139ce942b6ac255aa40404ed897081dd006172f6db1ef"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1454124731,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xf8;
        pchMessageStart[1] = 0x7a;
        pchMessageStart[2] = 0xda;
        pchMessageStart[3] = 0x1f;
        vAlertPubKey = ParseHex("0497dfcea626dca270cfe2eebf1160733b07352af966926e30058ca53dae05bbc71d64dbaa0c66e373211e324a23b361fc33e1e2dece1fb90afcefc707643a28f5");
        nDefaultPort = 12183;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // Keyco starting difficulty is 1 / 2^12  //20
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 86400; // Keyco: 1 day
        nTargetSpacing = 2 * 60;  // Keyco: 1 minute
        nLastPOWBlock = 400000;
        nMaturity = 100;
        nMasternodeCountDrift = 20;
		nMasternodeColleteralLimxDev = 1000; //Params().MasternodeColleteralLimxDev()
        nModifierUpdateBlock = 1; // we use the version 2 for dmd
        nMaxMoneyOut = 18000000 * COIN;

        const char* pszTimestamp = "27 Feb 2018 - Keyco coin";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("040fbf75ea45bf7eb65f9075e8342b7520d077b66f964e9b1963c96cefd9a2c52e93d0def918e0cd3c91f42821f429b2be4505552dede31c96f95f0d843da0beae") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1519732800;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 2862503;
		
        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x0000042b3b3d829bd8cc5163c9616fc8d9c203812adfadc754282f3aeebcff92"));
        assert(genesis.hashMerkleRoot == uint256("0x5d9883a01af1f056bae49c6072a99b5009298edab44cc5e1a5f2bfa5bb94dd19"));

        //vSeeds.push_back(CDNSSeedData("127.0.0.1", "127.0.0.1"));
        
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,46);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,16);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1,204);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0xFE)(0x52)(0xF8).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0xFE)(0x52)(0xCC).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md 109 	0x8000006d
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x05).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;


        nPoolMaxTransactions = 3;
        strSporkKey = "043fa953688a6e007a7f4dfd3f854a96efadbe5d2db5d13982248b55c4b0b3e20d6c5c2ab4e035de8013aa578bc88440a44ad55d770d98b5504f9887613480c0b4";
        strDarksendPoolDummyAddress = "KTvQSv8DbYHEN9jVzwtk8tqS3pJc3PyYma";
        nStartMasternodePayments = 1510272000; //11/10/2017 @ 12:00am (UTC)
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
       pchMessageStart[0] = 0x1f;
        pchMessageStart[1] = 0xbc;
        pchMessageStart[2] = 0xc7;
        pchMessageStart[3] = 0x4c;
        vAlertPubKey = ParseHex("0451e7e310524bc9d686f334fd3abd5ddf17f8c4c39b412a51b42cdbd08d377ec448aa54ced7aa009ec0575949751b107ec37d42b9384a8d51d4028501d4abba41");;
        nDefaultPort = 22183;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 86400; // Keyco: 1 day
        nTargetSpacing = 2 * 60;  // Keyco: 1 minute
        nLastPOWBlock = 400000;
        nMaturity = 15;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 18000000 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1519732800;
        genesis.nNonce = 2367988;


        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0xd7dc899d1b0cce20c3e139ce942b6ac255aa40404ed897081dd006172f6db1ef"));

        vFixedSeeds.clear();
        vSeeds.clear();

	//vSeeds.push_back(CDNSSeedData("127.0.0.1", "127.0.0.1"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(46);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(16);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(204);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0xFE)(0x52)(0xF8).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0xFE)(0x52)(0xCC).convert_to_container<std::vector<unsigned char> >();
        //  BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md 109   0x8000006d
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x05).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));


        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;



        nPoolMaxTransactions = 2;
        strSporkKey = "04f940e5f2fbea61db2dc678753f68e7d5f0fa0640c0438cae730903541a8da0249a7698f041be1831b7a700dca5a5ae28031e11ef5a6e5a828765cacc4f3438d2";
        strDarksendPoolDummyAddress = "DTvQSv8DbYHEN9jVzwtk8tqS3pJc3PyYma";
        nStartMasternodePayments = 1510272000;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xdc;
        pchMessageStart[1] = 0xc3;
        pchMessageStart[2] = 0xb3;
        pchMessageStart[3] = 0x4c;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Keyco: 1 day
        nTargetSpacing = 2 * 60;        // Keyco: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1519732800;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 129915;
		
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 20455;
        //assert(hashGenesisBlock == uint256("0x00000fea76c2e8523777b3dce649c363b4c5e0234605cae551f8d822d17fcc16"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 19448;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
