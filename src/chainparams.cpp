// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The SPON developers
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
     boost::assign::map_list_of
    (0, uint256("0x001"));
    //(0, uint256("0x00000b3181281c11162930fa5e3fe52a82d456815a3256adb7bbedcac419795a")) //gen block
    //(259201, uint256("1c9121bf9329a6234bfd1ea2d91515f19cd96990725265253f4b164283ade5dd")); 
    //(2, uint256("0x00000d46e354372609f5f6c0cf40c46a2c174899d7eeec64514fa16909ef64c9"))
    //(3, uint256("0x0000010f6728ecde4e59649bbc9f24f6eeac182c0b42e5b53b508647f4f30611"))
    //(167, uint256("0x00000012ba3beedd544c6bc63a98a1f496a64c2817e56fd8547534c93cc891c6"))
    //(254, uint256("0x0000001468b048b5f3801f107475691e87a546cdb8a2313391ef54979850d8df"))
    //(428, uint256("0x00000040da892adf5afdf02e732e2fa20632947b9a26d994bfc9214a11b56539"))
    //(499, uint256("0x00000030e323683107f1c34f6ce4886cf0dd49d7d5df7de525e061a6bb1da0fb"))
    //(500, uint256("0x0000007e0194c4abd5692f4264825ac9a6a72f0d38d232faec5eecb0c7f72b9a"))
    //(501, uint256("0x6f6f05badd2d9b824749cbee6a732ab46338c563c16162501853a1a2f952f29d"))
    //(1587, uint256("0x24a7001a82608901f47dbd693e0e3e72ba5588c4a476d053ffcb8294a9f32ceb"))
    //(2342, uint256("0x06b972caff65d145d6714d7e9184f03a4e134f46f2dc599ceaa6fc4b293bf85f"))
    //(3110, uint256("0xcc230f6ec71671418af9e75aeed4a9d2671f0a262564b261e013c5e57b34153d"))
    //(209000, uint256("0xc46f338ff967b992f4a5b68ddac9b5f30ab2c883e37d71a7b8c1ec97acccdd57"));
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1543204778, // * UNIX timestamp of last checkpoint block
    0,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    500        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1543204778,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1543204778,
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
        pchMessageStart[0] = 0xa5;
        pchMessageStart[1] = 0x6b;
        pchMessageStart[2] = 0xc7;
        pchMessageStart[3] = 0x8d;
        vAlertPubKey = ParseHex("0000098d3ba6ba6e7423fa5cbd6a89e0a9a5348f88d332b44a5cb1a8b7ed2c1eaa335fc8dc4f012cb8241cc0bdafd6ca70c5f5448916e4e6f511bcd746ed57dc50");
        nDefaultPort = 39811;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // SPON starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // SPON: 1 day
        nTargetSpacing = 1 * 60;  // SPON: 1 minute
        nLastPOWBlock = 259200;
        nMaturity = 100;
        nMasternodeCountDrift = 20;
        nModifierUpdateBlock = 615800;

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "South Korea beat Germany 2:0 at the World Cup in Russia on June 17, 2018.";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 250 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04c6b049e5a40b71781ab6e436a60b6f6796a0301fd37dbacb23a0425125130a4234969532decb60a1cd7512e03b9120e058e272a231c931e9299cddef6e67eb36") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1543204778;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 4558422;

        hashGenesisBlock = genesis.GetHash();
/*
	if(genesis.GetHash() != uint256("0x"))
        {
        printf("MSearching for genesis block...\n");
        uint256 hashTarget;
        hashTarget.SetCompact(genesis.nBits);
        while(uint256(genesis.GetHash()) > uint256(hashTarget))
        {
            ++genesis.nNonce;
            if (genesis.nNonce == 0)
            {
                printf("Mainnet NONCE WRAPPED, incrementing time");
                std::cout << std::string("Mainnet NONCE WRAPPED, incrementing time:\n");
                ++genesis.nTime;
            }
            if (genesis.nNonce % 10000 == 0)
            {
               printf("Mainnet: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
            }
        }
        printf("Mainnet block.nTime = %u \n", genesis.nTime);
        printf("Mainnet block.nNonce = %u \n", genesis.nNonce);
        printf("Mainnet block.hashMerkleRoot: %s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("Mainnet block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        }
*/
        assert(hashGenesisBlock == uint256("0x000009807ce709d207452960487373ffb1a79bcb6e059e89593a68a2f2b10bca"));
        assert(genesis.hashMerkleRoot == uint256("0x991dc3c6cdde776d85ad31efd341afc63919f4b58b743de9a6de2bf669005880"));

        //vSeeds.push_back(CDNSSeedData("fuzzbawls.pw", "spon.seed.fuzzbawls.pw"));     // Primary DNS Seeder from Fuzzbawls
        //vSeeds.push_back(CDNSSeedData("fuzzbawls.pw", "spon.seed2.fuzzbawls.pw"));    // Secondary DNS Seeder from Fuzzbawls
        //vSeeds.push_back(CDNSSeedData("coin-server.com", "coin-server.com"));         // Single node address
        //vSeeds.push_back(CDNSSeedData("s3v3nh4cks.ddns.net", "s3v3nh4cks.ddns.net")); // Single node address
        vSeeds.push_back(CDNSSeedData("117.52.87.33", "117.52.87.33"));           // Single node address

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 63);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 5);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is 'TBD'
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x13)(0x00)(0x00)(0x80).convert_to_container<std::vector<unsigned char> >();

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
        strSporkKey = "0484698d3ba6ba6e7423fa5cbd6a89e0a9a5348f88d332b44a5cb1a8b7ed2c1eaa335fc8dc4f012cb8241cc0bdafd6ca70c5f5448916e4e6f511bcd746ed57dc50";
        //strSporkKey = "04B433E6598390C992F4F022F20D3B4CBBE691652EE7C48243B81701CBDB7CC7D7BF0EE09E154E6FCBF2043D65AF4E9E97B89B5DBAF830D83B9B7F469A6C45A717";
        strObfuscationPoolDummyAddress = "S87q2gC9j6nNrnzCsg4aY6bHMLsT9nUhEw";
        nStartMasternodePayments = 1558761897; //Wed, 25 Jun 2014 20:36:16 GMT
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
        pchMessageStart[0] = 0xc4;
        pchMessageStart[1] = 0x5d;
        pchMessageStart[2] = 0xe6;
        pchMessageStart[3] = 0xf7;
        vAlertPubKey = ParseHex("000010e83b2703ccf322f7dbd62dd5855ac7c10bd055814ce121ba32607d573b8810c02c0582aed05b4deb9c4b77b26d92428c61256cd42774babea0a073b2ed0c9");
        nDefaultPort = 39813;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // SPON: 1 day
        nTargetSpacing = 1 * 60;  // SPON: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 15;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1543204778;
        genesis.nNonce = 4558422;

        hashGenesisBlock = genesis.GetHash();
/*
	if(genesis.GetHash() != uint256("0x"))
        {
        printf("MSearching for genesis block...\n");
        uint256 hashTarget;
        hashTarget.SetCompact(genesis.nBits);
        while(uint256(genesis.GetHash()) > uint256(hashTarget))
        {
            ++genesis.nNonce;
            if (genesis.nNonce == 0)
            {
                printf("Mainnet NONCE WRAPPED, incrementing time");
                std::cout << std::string("Mainnet NONCE WRAPPED, incrementing time:\n");
                ++genesis.nTime;
            }
            if (genesis.nNonce % 10000 == 0)
            {
               printf("Mainnet: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
            }
        }
        printf("Mainnet block.nTime = %u \n", genesis.nTime);
        printf("Mainnet block.nNonce = %u \n", genesis.nNonce);
        printf("Mainnet block.hashMerkleRoot: %s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("Mainnet block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        }
*/
        assert(hashGenesisBlock == uint256("0x000009807ce709d207452960487373ffb1a79bcb6e059e89593a68a2f2b10bca"));

        vFixedSeeds.clear();
        vSeeds.clear();
        //vSeeds.push_back(CDNSSeedData("fuzzbawls.pw", "spon-testnet.seed.fuzzbawls.pw"));
        //vSeeds.push_back(CDNSSeedData("fuzzbawls.pw", "spon-testnet.seed2.fuzzbawls.pw"));
        //vSeeds.push_back(CDNSSeedData("s3v3nh4cks.ddns.net", "s3v3nh4cks.ddns.net"));
        vSeeds.push_back(CDNSSeedData("117.52.87.33", "117.52.87.33"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 125); // Testnet spon addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 3);  // Testnet spon script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet spon BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet spon BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet spon BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x01)(0x00)(0x00)(0x80).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04348C2F50F90267E64FACC65BFDC9D0EB147D090872FB97ABAE92E9A36E6CA60983E28E741F8E7277B11A7479B626AC115BA31463AC48178A5075C5A9319D4A38";
        strObfuscationPoolDummyAddress = "s57cqfGRkekRyDRNeJiLtYVEbvhXrNbmox";
        nStartMasternodePayments = 1558761897; //Fri, 09 Jan 2015 21:05:58 GMT
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
        pchMessageStart[0] = 0x5a;
        pchMessageStart[1] = 0xe5;
        pchMessageStart[2] = 0x9c;
        pchMessageStart[3] = 0x3d;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Spon: 1 day
        nTargetSpacing = 1 * 60;        // Spon: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1543204778;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 12347;

        hashGenesisBlock = genesis.GetHash();
/*
	if(genesis.GetHash() != uint256("0x"))
        {
        printf("MSearching for genesis block...\n");
        uint256 hashTarget;
        hashTarget.SetCompact(genesis.nBits);
        while(uint256(genesis.GetHash()) > uint256(hashTarget))
        {
            ++genesis.nNonce;
            if (genesis.nNonce == 0)
            {
                printf("Mainnet NONCE WRAPPED, incrementing time");
                std::cout << std::string("Mainnet NONCE WRAPPED, incrementing time:\n");
                ++genesis.nTime;
            }
            if (genesis.nNonce % 10000 == 0)
            {
               printf("Mainnet: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
            }
        }
        printf("Mainnet block.nTime = %u \n", genesis.nTime);
        printf("Mainnet block.nNonce = %u \n", genesis.nNonce);
        printf("Mainnet block.hashMerkleRoot: %s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("Mainnet block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        }
*/
        nDefaultPort = 51476;
        assert(hashGenesisBlock == uint256("0x247eea85fda85dc0479aec633689a5dd4abb372c99cdc42f5faeb1c05fb26ddd"));

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
        nDefaultPort = 51478;
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