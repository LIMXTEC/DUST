// global Dust Protocol header file
// globals consts (DEFINEs for now) should be here
//
// for now (?) class declarations go here -- work in progress; probably will get pulled out into a separate file, note: some declarations are still in the .cpp file

#ifndef _DUST
#define _DUST 1

#include "netbase.h"
#include "protocol.h"

#include "tinyformat.h"

#define DISABLE_METADEX

#define LOG_FILENAME    "dust.log"
#define INFO_FILENAME   "dust_crowdsales.log"
#define OWNERS_FILENAME "dust_owners.log"

int const MAX_STATE_HISTORY = 50;

#define TEST_ECO_PROPERTY_1 (0x80000003UL)

// could probably also use: int64_t maxInt64 = std::numeric_limits<int64_t>::max();
// maximum numeric values from the spec:
#define MAX_INT_8_BYTES (9223372036854775807UL)

// what should've been in the Exodus address for this block if none were spent
#define DEV_MSC_BLOCK_290629 (1743358325718)

#define SP_STRING_FIELD_LEN 256

// in Dust Satoshis (Willetts)
#define TRANSFER_FEE_PER_OWNER  (1)

// some boost formats
#define FORMAT_BOOST_TXINDEXKEY "index-tx-%s"
#define FORMAT_BOOST_SPKEY      "sp-%d"

// Dust Protocol Transaction (Packet) Version
#define MP_TX_PKT_V0  0
#define MP_TX_PKT_V1  1

// Maximum outputs per BTC Transaction
#define MAX_BTC_OUTPUTS 16

#define MAX_SHA256_OBFUSCATION_TIMES  255

#define PACKET_SIZE_CLASS_A 19
#define PACKET_SIZE         31
#define MAX_PACKETS         64

// Transaction types, from the spec
enum TransactionType {
  MSC_TYPE_SIMPLE_SEND              =  0,
  MSC_TYPE_RESTRICTED_SEND          =  2,
  MSC_TYPE_SEND_TO_OWNERS           =  3,
  MSC_TYPE_SAVINGS_MARK             = 10,
  MSC_TYPE_SAVINGS_COMPROMISED      = 11,
  MSC_TYPE_RATELIMITED_MARK         = 12,
  MSC_TYPE_AUTOMATIC_DISPENSARY     = 15,
  MSC_TYPE_TRADE_OFFER              = 20,
  MSC_TYPE_METADEX                  = 21,
  MSC_TYPE_ACCEPT_OFFER_BTC         = 22,
  MSC_TYPE_NOTIFICATION             = 31,
  MSC_TYPE_OFFER_ACCEPT_A_BET       = 40,
  MSC_TYPE_CREATE_PROPERTY_FIXED    = 50,
  MSC_TYPE_CREATE_PROPERTY_VARIABLE = 51,
  MSC_TYPE_PROMOTE_PROPERTY         = 52,
  MSC_TYPE_CLOSE_CROWDSALE          = 53,
  MSC_TYPE_CREATE_PROPERTY_MANUAL   = 54,
  MSC_TYPE_GRANT_PROPERTY_TOKENS    = 55,
  MSC_TYPE_REVOKE_PROPERTY_TOKENS   = 56,
  MSC_TYPE_CHANGE_ISSUER_ADDRESS    = 70,
  DUST_MESSAGE_TYPE_ALERT     = 65535
};

#define MSC_PROPERTY_TYPE_INDIVISIBLE             1
#define MSC_PROPERTY_TYPE_DIVISIBLE               2
#define MSC_PROPERTY_TYPE_INDIVISIBLE_REPLACING   65
#define MSC_PROPERTY_TYPE_DIVISIBLE_REPLACING     66
#define MSC_PROPERTY_TYPE_INDIVISIBLE_APPENDING   129
#define MSC_PROPERTY_TYPE_DIVISIBLE_APPENDING     130

// block height (MainNet) with which the corresponding transaction is considered valid, per spec
enum BLOCKHEIGHTRESTRICTIONS {
// starting block for parsing on TestNet
  START_TESTNET_BLOCK=263000,
  START_REGTEST_BLOCK=5,
  MONEYMAN_REGTEST_BLOCK= 101, // new address to assign MSC & TMSC on RegTest
  MONEYMAN_TESTNET_BLOCK= 270775, // new address to assign MSC & TMSC on TestNet
  POST_EXODUS_BLOCK = 255366,
  MSC_DEX_BLOCK     = 290630,
  MSC_SP_BLOCK      = 297110,
  GENESIS_BLOCK     = 249498,
  LAST_EXODUS_BLOCK = 255365,
  MSC_STO_BLOCK     = 342650,
  MSC_METADEX_BLOCK = 999999,
  MSC_BET_BLOCK     = 999999,
  MSC_MANUALSP_BLOCK= 323230,
  P2SH_BLOCK        = 322000,
};

enum FILETYPES {
  FILETYPE_BALANCES = 0,
  FILETYPE_OFFERS,
  FILETYPE_ACCEPTS,
  FILETYPE_GLOBALS,
  FILETYPE_CROWDSALES,
  NUM_FILETYPES
};

#define PKT_RETURNED_OBJECT    (1000)

#define PKT_ERROR             ( -9000)
#define DEX_ERROR_SELLOFFER   (-10000)
#define DEX_ERROR_ACCEPT      (-20000)
#define DEX_ERROR_PAYMENT     (-30000)
// Smart Properties
#define PKT_ERROR_SP          (-40000)
// Send To Owners
#define PKT_ERROR_STO         (-50000)
#define PKT_ERROR_SEND        (-60000)
#define PKT_ERROR_TRADEOFFER  (-70000)
#define PKT_ERROR_METADEX     (-80000)
#define METADEX_ERROR         (-81000)
#define PKT_ERROR_TOKENS      (-82000)

#define DUST_PROPERTY_BTC   0
#define DUST_PROPERTY_MSC   1
#define DUST_PROPERTY_TMSC  2

#include <boost/multiprecision/cpp_dec_float.hpp>
using boost::multiprecision::cpp_dec_float_100;
typedef cpp_dec_float_100 XDOUBLE;

int mp_LogPrintStr(const std::string &str);

/* When we switch to C++11, this can be switched to variadic templates instead
 * of this macro-based construction (see tinyformat.h).
 */
#define MP_MAKE_ERROR_AND_LOG_FUNC(n)                                        \
    /*   Print to debug.log if -debug=category switch is given OR category is NULL. */ \
    template<TINYFORMAT_ARGTYPES(n)>                                          \
    static inline int mp_category_log(const char* category, const char* format, TINYFORMAT_VARARGS(n))  \
    {                                                                         \
        if(!LogAcceptCategory(category)) return 0;                            \
        return mp_LogPrintStr(tfm::format(format, TINYFORMAT_PASSARGS(n))); \
    }                                                                         \
    template<TINYFORMAT_ARGTYPES(n)>                                          \
    static inline int mp_log(TINYFORMAT_VARARGS(n))  \
    {                                                                         \
        return mp_LogPrintStr(tfm::format("%s", TINYFORMAT_PASSARGS(n))); \
    }                                                                         \
    template<TINYFORMAT_ARGTYPES(n)>                                          \
    static inline int mp_log(const char* format, TINYFORMAT_VARARGS(n))  \
    {                                                                         \
        return mp_LogPrintStr(tfm::format(format, TINYFORMAT_PASSARGS(n))); \
    }                                                                         \
    template<TINYFORMAT_ARGTYPES(n)>                                          \
    static inline int file_log(const char* format, TINYFORMAT_VARARGS(n))  \
    {                                                                         \
        return mp_LogPrintStr(tfm::format(format, TINYFORMAT_PASSARGS(n))); \
    }                                                                         \
    template<TINYFORMAT_ARGTYPES(n)>                                          \
    static inline int file_log(TINYFORMAT_VARARGS(n))  \
    {                                                                         \
        return mp_LogPrintStr(tfm::format("%s", TINYFORMAT_PASSARGS(n))); \
    }                                                                         \
    /*   Log error and return false */                                        \
    template<TINYFORMAT_ARGTYPES(n)>                                          \
    static inline bool mp_error(const char* format, TINYFORMAT_VARARGS(n))                     \
    {                                                                         \
        mp_LogPrintStr("ERROR: " + tfm::format(format, TINYFORMAT_PASSARGS(n)) + "\n"); \
        return false;                                                         \
    }

TINYFORMAT_FOREACH_ARGNUM(MP_MAKE_ERROR_AND_LOG_FUNC)
//--- CUT HERE ---

// forward declarations
std::string FormatPriceMP(double n);
std::string FormatDivisibleMP(int64_t n, bool fSign = false);
std::string FormatDivisibleShortMP(int64_t);
std::string FormatMP(unsigned int, int64_t n, bool fSign = false);
uint256 send_MP(const string &FromAddress, const string &ToAddress, const string &RedeemAddress, unsigned int PropertyID, uint64_t Amount);
int64_t feeCheck(const string &address);

const std::string ExodusAddress();

extern int msc_debug_ui;

extern CCriticalSection cs_tally;

extern const int msc_debug_dex;

enum TallyType { BALANCE = 0, SELLOFFER_RESERVE = 1, ACCEPT_RESERVE = 2, PENDING = 3, METADEX_RESERVE = 4, TALLY_TYPE_COUNT };

class CMPTally
{
private:
typedef struct
{
  int64_t balance[TALLY_TYPE_COUNT];
} BalanceRecord;

  typedef std::map<unsigned int, BalanceRecord> TokenMap;
  TokenMap mp_token;
  TokenMap::iterator my_it;

  bool propertyExists(unsigned int which_property) const
  {
  const TokenMap::const_iterator it = mp_token.find(which_property);

    return (it != mp_token.end());
  }

public:

  unsigned int init()
  {
  unsigned int ret = 0;

    my_it = mp_token.begin();
    if (my_it != mp_token.end()) ret = my_it->first;

    return ret;
  }

  unsigned int next()
  {
  unsigned int ret;

    if (my_it == mp_token.end()) return 0;

    ret = my_it->first;

    ++my_it;

    return ret;
  }

  bool updateMoney(unsigned int which_property, int64_t amount, TallyType ttype)
  {
  bool bRet = false;
  int64_t now64;

    if (TALLY_TYPE_COUNT <= ttype) return false;

    LOCK(cs_tally);

    now64 = mp_token[which_property].balance[ttype];

    if ((PENDING != ttype) && (0>(now64 + amount)))
    {
    }
    else
    {
      now64 += amount;
      mp_token[which_property].balance[ttype] = now64;

      bRet = true;
    }

    return bRet;
  }

  // the constructor -- create an empty tally for an address
  CMPTally()
  {
    my_it = mp_token.begin();
  }

  int64_t print(int which_property = DUST_PROPERTY_MSC, bool bDivisible = true)
  {
  int64_t money = 0;
  int64_t so_r = 0;
  int64_t a_r = 0;
  int64_t pending = 0;

    if (propertyExists(which_property))
    {
      money = mp_token[which_property].balance[BALANCE];
      so_r = mp_token[which_property].balance[SELLOFFER_RESERVE];
      a_r = mp_token[which_property].balance[ACCEPT_RESERVE];
      pending = mp_token[which_property].balance[PENDING];
    }

    if (bDivisible)
    {
      printf("%22s [SO_RESERVE= %22s , ACCEPT_RESERVE= %22s ] %22s\n",
       FormatDivisibleMP(money, true).c_str(), FormatDivisibleMP(so_r, true).c_str(), FormatDivisibleMP(a_r, true).c_str(), FormatDivisibleMP(pending, true).c_str());
    }
    else
    {
      printf("%14lu [SO_RESERVE= %14lu , ACCEPT_RESERVE= %14lu ] %14ld\n", money, so_r, a_r, pending);
    }

    return (money + so_r + a_r);
  }

  int64_t getMoney(unsigned int which_property, TallyType ttype)
  {
  int64_t ret64 = 0;

    if (TALLY_TYPE_COUNT <= ttype) return 0;

    LOCK(cs_tally);

    if (propertyExists(which_property)) ret64 = mp_token[which_property].balance[ttype];

    return ret64;
  }
};

/* leveldb-based storage for sto recipients */
class CMPSTOList
{
    protected:
    // datebase options reused from MPTxList
    leveldb::Options options;
    leveldb::ReadOptions readoptions;
    leveldb::ReadOptions iteroptions;
    leveldb::WriteOptions writeoptions;
    leveldb::WriteOptions syncoptions;
    leveldb::DB *sdb;
    // statistics
    unsigned int sWritten;
    unsigned int sRead;

public:
    CMPSTOList(const boost::filesystem::path &path, size_t nCacheSize, bool fMemory, bool fWipe):sWritten(0),sRead(0)
    {
      options.paranoid_checks = true;
      options.create_if_missing = true;
      readoptions.verify_checksums = true;
      iteroptions.verify_checksums = true;
      iteroptions.fill_cache = false;
      syncoptions.sync = true;
      leveldb::Status status = leveldb::DB::Open(options, path.string(), &sdb);
      printf("%s(): %s, line %d, file: %s\n", __FUNCTION__, status.ToString().c_str(), __LINE__, __FILE__);
    }

    ~CMPSTOList()
    {
      delete sdb;
      sdb = NULL;
    }

    void getRecipients(const uint256 txid, string filterAddress, Array *recipientArray, uint64_t *total, uint64_t *stoFee);
    std::string getMySTOReceipts(string filterAddress);
    int deleteAboveBlock(int blockNum);
    void printStats();
    void printAll();
    bool exists(string address);
    void recordSTOReceive(std::string, const uint256&, int, unsigned int, uint64_t);
};

/* leveldb-based storage for trade history - trades will be listed here atomically with key txid1:txid2 */
class CMPTradeList
{
protected:
    // datebase options reused from MPTxList
    leveldb::Options options;
    leveldb::ReadOptions readoptions;
    leveldb::ReadOptions iteroptions;
    leveldb::WriteOptions writeoptions;
    leveldb::WriteOptions syncoptions;
    leveldb::DB *tdb;
    // statistics
    unsigned int tWritten;
    unsigned int tRead;

public:
    CMPTradeList(const boost::filesystem::path &path, size_t nCacheSize, bool fMemory, bool fWipe):tWritten(0),tRead(0)
    {
      options.paranoid_checks = true;
      options.create_if_missing = true;
      readoptions.verify_checksums = true;
      iteroptions.verify_checksums = true;
      iteroptions.fill_cache = false;
      syncoptions.sync = true;
      leveldb::Status status = leveldb::DB::Open(options, path.string(), &tdb);
      printf("%s(): %s, line %d, file: %s\n", __FUNCTION__, status.ToString().c_str(), __LINE__, __FILE__);
    }

    ~CMPTradeList()
    {
      delete tdb;
      tdb = NULL;
    }

    void recordTrade(const uint256 txid1, const uint256 txid2, string address1, string address2, unsigned int prop1, unsigned int prop2, uint64_t amount1, uint64_t amount2, int blockNum);
    int deleteAboveBlock(int blockNum);
    bool exists(const uint256 &txid);
    void printStats();
    void printAll();
    bool getMatchingTrades(const uint256 txid, unsigned int propertyId, Array *tradeArray, uint64_t *totalSold, uint64_t *totalBought);
    int getMPTradeCountTotal();
};

/* leveldb-based storage for the list of ALL Dust Protocol TXIDs (key) with validity bit & other misc data as value */
class CMPTxList
{
protected:
    // database options used
    leveldb::Options options;

    // options used when reading from the database
    leveldb::ReadOptions readoptions;

    // options used when iterating over values of the database
    leveldb::ReadOptions iteroptions;

    // options used when writing to the database
    leveldb::WriteOptions writeoptions;

    // options used when sync writing to the database
    leveldb::WriteOptions syncoptions;

    // the database itself
    leveldb::DB *pdb;

    // statistics
    unsigned int nWritten;
    unsigned int nRead;

public:
    CMPTxList(const boost::filesystem::path &path, size_t nCacheSize, bool fMemory, bool fWipe):nWritten(0),nRead(0)
    {
      options.paranoid_checks = true;
      options.create_if_missing = true;

      readoptions.verify_checksums = true;
      iteroptions.verify_checksums = true;
      iteroptions.fill_cache = false;
      syncoptions.sync = true;

      leveldb::Status status = leveldb::DB::Open(options, path.string(), &pdb);

      printf("%s(): %s, line %d, file: %s\n", __FUNCTION__, status.ToString().c_str(), __LINE__, __FILE__);
    }

    ~CMPTxList()
    {
      delete pdb;
      pdb = NULL;
    }

    void recordTX(const uint256 &txid, bool fValid, int nBlock, unsigned int type, uint64_t nValue);
    void recordPaymentTX(const uint256 &txid, bool fValid, int nBlock, unsigned int vout, unsigned int propertyId, uint64_t nValue, string buyer, string seller);
    void recordMetaDExCancelTX(const uint256 &txidDust, const uint256 &txidSub, bool fValid, int nBlock, unsigned int propertyId, uint64_t nValue);

    string getKeyValue(string key);
    uint256 findMetaDExCancel(const uint256 txid);
    int getNumberOfPurchases(const uint256 txid);
    int getNumberOfMetaDExCancels(const uint256 txid);
    bool getPurchaseDetails(const uint256 txid, int purchaseNumber, string *buyer, string *seller, uint64_t *vout, uint64_t *propertyId, uint64_t *nValue);
    int getMPTransactionCountTotal();
    int getMPTransactionCountBlock(int block);

    bool exists(const uint256 &txid);
    bool getTX(const uint256 &txid, string &value);

    int setLastAlert(int blockHeight);

    void printStats();
    void printAll();

    bool isMPinBlockRange(int, int, bool);
};

class CMPPending
{
public:
  string src; // the FromAddress
  unsigned int prop;
  int64_t amount;
  int64_t type;
  string desc; // the description

  void print(uint256 txid) const
  {
    printf("%s : %s %d %ld %ld %s\n", txid.GetHex().c_str(), src.c_str(), prop, amount, type, desc.c_str());
  }
 
};

//temp - only supporting 100,000 properties per eco here, research best way to expand array
//these 4 arrays use about 3MB total memory with 100K properties limit (100000*8*4 bytes)
extern uint64_t global_metadex_market;
extern uint64_t global_balance_money_maineco[100000];
extern uint64_t global_balance_reserved_maineco[100000];
extern uint64_t global_balance_money_testeco[100000];
extern uint64_t global_balance_reserved_testeco[100000];

int dust_init(void);

int64_t getMPbalance(const string &Address, unsigned int property, TallyType ttype);
int64_t getUserAvailableMPbalance(const string &Address, unsigned int property);
bool IsMyAddress(const std::string &address);

string getLabel(const string &address);

int dust_handler_disc_begin(int nBlockNow, CBlockIndex const * pBlockIndex);
int dust_handler_disc_end(int nBlockNow, CBlockIndex const * pBlockIndex);
int dust_handler_block_begin(int nBlockNow, CBlockIndex const * pBlockIndex);
int dust_handler_block_end(int nBlockNow, CBlockIndex const * pBlockIndex, unsigned int);
int dust_handler_tx(const CTransaction &tx, int nBlock, unsigned int idx, CBlockIndex const *pBlockIndex );
int dust_save_state( CBlockIndex const *pBlockIndex );

namespace dust
{
extern std::map<string, CMPTally> mp_tally_map;
extern CMPTxList *p_txlistdb;
extern CMPTradeList *t_tradelistdb;
extern CMPSTOList *s_stolistdb;

typedef std::map<uint256, CMPPending> PendingMap;
extern PendingMap my_pending;
string strMPProperty(unsigned int i);

int GetHeight(void);
uint32_t GetLatestBlockTime(void);
bool isPropertyDivisible(unsigned int propertyId);
string getPropertyName(unsigned int propertyId);
bool isCrowdsaleActive(unsigned int propertyId);
bool isCrowdsalePurchase(uint256 txid, string address, int64_t *propertyId = NULL, int64_t *userTokens = NULL, int64_t *issuerTokens = NULL);
bool isMPinBlockRange(int starting_block, int ending_block, bool bDeleteFound);
std::string FormatIndivisibleMP(int64_t n);

int ClassB_send(const string &senderAddress, const string &receiverAddress, const string &redemptionAddress, const vector<unsigned char> &data, uint256 & txid, int64_t additional = 0);

uint256 send_INTERNAL_1packet(const string &FromAddress, const string &ToAddress, const string &RedeemAddress, unsigned int PropertyID, uint64_t Amount,
 unsigned int PropertyID_2, uint64_t Amount_2, unsigned int TransactionType, int64_t additional, int *error_code = NULL);

bool isTestEcosystemProperty(unsigned int property);
bool isMainEcosystemProperty(unsigned int property);

CMPTally *getTally(const string & address);

bool isMetaDExOfferActive(const uint256 txid, unsigned int propertyId);
int64_t getTotalTokens(unsigned int propertyId, int64_t *n_owners_total = NULL);
bool checkExpiredAlerts(unsigned int curBlock, uint64_t curTime);
int set_wallet_totals();

char *c_strDustProtocolTXType(int i);

bool isTransactionTypeAllowed(int txBlock, unsigned int txProperty, unsigned int txType, unsigned short version, bool bAllowNullProperty = false);

bool getValidMPTX(const uint256 &txid, int *block = NULL, unsigned int *type = NULL, uint64_t *nAmended = NULL);

bool update_tally_map(string who, unsigned int which_currency, int64_t amount, TallyType ttype);
std::string getDustAlertString();
std::string getDustAlertTextOnly();
bool parseAlertMessage(std::string rawAlertStr, int32_t *alertType, uint64_t *expiryValue, uint32_t *typeCheck, uint32_t *verCheck, std::string *alertMessage);
std::string getTokenLabel(unsigned int propertyId);
}

#endif

