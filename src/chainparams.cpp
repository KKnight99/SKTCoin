// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The SKT developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "assert.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

//
// Main network
//

unsigned int pnSeed[] =
{
0x05C4BE52, 0x68EEBC2C, 0x55D6444B, 0x5B996D95, 0x9B5E9244, 0x4FACD744, 0x2D20B813, 0x5D9ED890, 0x6DF82145, 0xD4186F38, 0xD4651074, 0x0219B535, 0x25028591, 0x55D62C10, 0xC62CBE25, 0x461B5D07,0x40E76915, 0x05E7EB35,
};
// //sktdev 04-2015   New Seeds

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xd2;    //sktdev 04-2015   mainc.pp 3072    ggf testnet wert = falshc
        pchMessageStart[1] = 0xc3;    ///sktdev 04-2015
        pchMessageStart[2] = 0xc2;    //sktdev 04-2015
        pchMessageStart[3] = 0xf9;    //sktdev 04-2015
        
  //    name, networkVersion, privateKeyPrefix, WIF_Start, CWIF_Start, donate
  // ("SKT",  0x66, 0xcc, "7",    "X"    , "  ")
  
        vAlertPubKey = ParseHex("048240a8748a80a286b270ba126705ced4f2ce5a7847b3610ea3c06513150dade2a8512ed5ea86320824683fc0818f0ac019214973e677acd1244f6d0571fc5103"); //sktdev 04-2015   ist bei allen gleich
        nDefaultPort = 19683;
        nRPCPort = 10086;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);  // SKT starting difficulty is 1 / 2^12    //sktdev 04-2015   main.cpp 36
        nSubsidyHalvingInterval = 210000; //sktdev 04-2015   UNBEKANNT FUNKTION

        // Genesis block            Sprungmarke AAAAB
        const char* pszTimestamp = "14/07/2017 respn to trump the Castro gov said Trump's US is in no condition to lecture us";
        CTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 100 * COIN; //sktdev 04-2015
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("123484710fa689ad5023690c80f3a49c8f13f8d45b8c857fbcbc8bc4a8e4d3eb4b10f4d4604fa08dce601aaf0f470216fe1b51850b4acf21b179c45070ac7b03a9") << OP_CHECKSIG;   //skt
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1500016822;   //sktdev 04-2015
        genesis.nBits    = 0x1e0ffff0;  //sktdev 04-2015
        genesis.nNonce   = 3099112;  //sktdev 04-2015

        hashGenesisBlock = genesis.GetHash();
        //begin
        if (true && genesis.GetHash() != uint256("0x00000164b60a3a75ece03ffba4920631842014e9e694d28db5461b7231e9c070"))
        {
            printf("Searching for genesis block...\n");
            // This will figure out a valid hash and Nonce if you're
            // creating a different genesis block:
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            
            //arith_uint256 hashTarget;
            //bool fNegative;
            //bool fOverflow;
            //hashTarget.SetCompact(genesis.nBits, &fNegative, &fOverflow);
            
            uint256 thash;
            //char scratchpad[SCRYPT_SCRATCHPAD_SIZE];

            while (true)
            {
                //scrypt_1024_1_1_256_sp(BEGIN(block.nVersion), BEGIN(thash), scratchpad);
                //genesis.GetHash();
                if (genesis.GetHash() <= hashTarget)
                    break;
                if ((genesis.nNonce & 0xFFF) == 0)
                {
                    genesis.print();
                }
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    printf("NONCE WRAPPED, incrementing time\n");
                    ++genesis.nTime;
                }
            }
            printf("block.nTime = %u \n", genesis.nTime);
            printf("block.nNonce = %u \n", genesis.nNonce);
            printf("block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
            printf("block.hashMerkleRoot = %s\n", genesis.hashMerkleRoot.ToString().c_str());
        }
        //end
        assert(hashGenesisBlock == uint256("0x00000164b60a3a75ece03ffba4920631842014e9e694d28db5461b7231e9c070"));   //skt   
        assert(genesis.hashMerkleRoot == uint256("0x09f3d3def8872ffe75671bcd167acc1e3660f3af738aafede60ac9b5a3ae56bb"));   //checkpoint 38
   
		vSeeds.push_back(CDNSSeedData("www.superskynet.org", "47.52.45.101"));
		
        base58Prefixes[PUBKEY_ADDRESS] = list_of( 102);                    //sktdev 04-2015   addresses start with 'i'
        base58Prefixes[SCRIPT_ADDRESS] = list_of( 5);                    //sktdev 04-2015   script addresses start with '7'
        base58Prefixes[SECRET_KEY] =     list_of(204);                    //sktdev 04-2015  Pubkey +128 sktdev
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E); //sktdev 04-2015  'xpub '
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4); //sktdev 04-2015  'xpriv'
        base58Prefixes[EXT_COIN_TYPE]  = list_of(0x80000005);             // SKT BIP44 coin type is '5'

        // Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time' of between one and two
            // weeks ago.
            const int64_t nOneWeek = 7*24*60*60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
            vFixedSeeds.push_back(addr);
        }
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
// Testnet (v3)
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xd2;   //sktdev 04-2015
        pchMessageStart[1] = 0xc3;   //sktdev 04-2015
        pchMessageStart[2] = 0xc2;   //sktdev 04-2015
        pchMessageStart[3] = 0xf9;   //sktdev 04-2015   Testnet

        vAlertPubKey = ParseHex("04517d8a699cb43d3938d7b24faaff7cda448ca4ea267723ba614784de661949bf632d6304316b244646dea079735b9a6fc4af804efb4752075b9fe2245e14e412");
        nDefaultPort = 19683;
        nRPCPort = 10087;
        strDataDir = "testnet3";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1500016822;   //sktdev 04-2015 main.cpp 3127
        genesis.nNonce = 3099112;   //sktdev 04-2015 main.cpp 3128

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000164b60a3a75ece03ffba4920631842014e9e694d28db5461b7231e9c070"));  //sktdev 04-2015  Fehler

        vFixedSeeds.clear();
        vSeeds.clear();
        /*vSeeds.push_back(CDNSSeedData("5.56.209.255", "5.56.209.255"));   //sktdev 04-2015
        vSeeds.push_back(CDNSSeedData("", ""));       //sktdev 04-2015 vSeeds.push_back(CDNSSeedData("skt.qa", "testnet-seed.skt.qa"));
        *///legacy seeders
        vSeeds.push_back(CDNSSeedData("www.superskynet.org", "47.52.45.101"));      //sktdev 04-2015

        base58Prefixes[PUBKEY_ADDRESS] = list_of(111);                    //sktdev 04-2015   Testnet vorher 139 skt addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = list_of( 196);                    //sktdev 04-2015   Testnet vorher 19 skt script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY]     = list_of(211);                    ///sktdev 04-2015   Testnet vorher 239  private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF); //sktdev 04-2015   tpub
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94); //sktdev 04-2015  tprv
        base58Prefixes[EXT_COIN_TYPE]  = list_of(0x80000001);             // Testnet skt BIP44 coin type is '5' (All coin's testnet default)
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
      // Alle Parameter hier unverändert
        pchMessageStart[0] = 0xd2;          // SKTdev 04-2015 old    0xfc
        pchMessageStart[1] = 0xc3;          // SKTdev 04-2015 old    0xc1
        pchMessageStart[2] = 0xc2;         // SKTdev 04-2015 old     0xb7
        pchMessageStart[3] = 0xf9;          // SKTdev 04-2015 old    0xdc
        nSubsidyHalvingInterval = 150;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1500016822;       // SKTdev 04-2015 old   1417713337  Testnet
        genesis.nBits = 0x1e0ffff0;        // SKTdev 04-2015 old    0x207fffff  Zeile 60
        genesis.nNonce = 3099112;         // SKTdev 04-2015 old   1096447    Testnet
        nDefaultPort = 19994;             // SKTdev 04-2015 old   19994
        strDataDir = "regtest";

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000164b60a3a75ece03ffba4920631842014e9e694d28db5461b7231e9c070"));   // SKTdev 04-2015 old      0x000008ca1832a4baf228eb1553c03d3a2c8e02399550dd6ea8d65cec3ef23d2e

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

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
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
