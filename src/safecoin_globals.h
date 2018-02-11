/******************************************************************************
 * Copyright © 2014-2017 The SuperNET Developers.                             *
 *                                                                            *
 * See the AUTHORS, DEVELOPER-AGREEMENT and LICENSE files at                  *
 * the top-level directory of this distribution for the individual copyright  *
 * holder information and the developer policies on copyright and licensing.  *
 *                                                                            *
 * Unless otherwise agreed in a custom licensing agreement, no part of the    *
 * SuperNET software, including this file may be copied, modified, propagated *
 * or distributed except according to the terms contained in the LICENSE file *
 *                                                                            *
 * Removal or modification of this copyright notice is prohibited.            *
 *                                                                            *
 ******************************************************************************/

#include "safecoin_defs.h"

void safecoin_stateupdate(int32_t height,uint8_t notarypubs[][33],uint8_t numnotaries,uint8_t notaryid,uint256 txhash,uint64_t voutmask,uint8_t numvouts,uint32_t *pvals,uint8_t numpvals,int32_t kheight,uint32_t ktime,uint64_t opretvalue,uint8_t *opretbuf,uint16_t opretlen,uint16_t vout);
void safecoin_init(int32_t height);
int32_t safecoin_notarizeddata(int32_t nHeight,uint256 *notarized_hashp,uint256 *notarized_desttxidp);
char *safecoin_issuemethod(char *userpass,char *method,char *params,uint16_t port);
void safecoin_init(int32_t height);
void safecoin_assetchain_pubkeys(char *jsonstr);
int32_t safecoin_chosennotary(int32_t *notaryidp,int32_t height,uint8_t *pubkey33);
int32_t safecoin_isrealtime(int32_t *SAFEheightp);
uint64_t safecoin_paxtotal();
int32_t safecoin_longestchain();
uint64_t safecoin_maxallowed(int32_t baseid);
int32_t safecoin_bannedset(int32_t *indallvoutsp,uint256 *array,int32_t max);

pthread_mutex_t safecoin_mutex;

#define SAFECOIN_ELECTION_GAP 2000    //((ASSETCHAINS_SYMBOL[0] == 0) ? 2000 : 100)
#define IGUANA_MAXSCRIPTSIZE 10001
#define SAFECOIN_ASSETCHAIN_MAXLEN 65

struct pax_transaction *PAX;
int32_t NUM_PRICES; uint32_t *PVALS;
struct knotaries_entry *Pubkeys;

struct safecoin_state SAFECOIN_STATES[34];

#define _COINBASE_MATURITY 100
int COINBASE_MATURITY = _COINBASE_MATURITY;//100;

int32_t IS_SAFECOIN_NOTARY,USE_EXTERNAL_PUBKEY,SAFECOIN_CHOSEN_ONE,ASSETCHAINS_SEED,SAFECOIN_ON_DEMAND,SAFECOIN_EXTERNAL_NOTARIES,SAFECOIN_PASSPORT_INITDONE,SAFECOIN_PAX,SAFECOIN_EXCHANGEWALLET,SAFECOIN_REWIND;
int32_t SAFECOIN_LASTMINED,prevSAFECOIN_LASTMINED,JUMBLR_PAUSE;
std::string NOTARY_PUBKEY,ASSETCHAINS_NOTARIES;
uint8_t NOTARY_PUBKEY33[33];

char ASSETCHAINS_SYMBOL[SAFECOIN_ASSETCHAIN_MAXLEN];
uint16_t ASSETCHAINS_PORT;
uint32_t ASSETCHAIN_INIT;
uint32_t ASSETCHAINS_MAGIC = 2387029918;
uint64_t ASSETCHAINS_SUPPLY = 10;

uint32_t SAFECOIN_INITDONE;
char SAFEUSERPASS[4096],BTCUSERPASS[4096]; uint16_t SAFE_PORT = 8771,BITCOIND_PORT = 8771;
uint64_t PENDING_SAFECOIN_TX;

struct safecoin_kv *SAFECOIN_KV;
pthread_mutex_t SAFECOIN_KV_mutex;
