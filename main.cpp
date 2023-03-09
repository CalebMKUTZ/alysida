#include <iostream>
#include <glog/logging.h>
#include "src/block.h"
#include "src/db/database.h"
#include "src/transaction.h"
#include "src/private_key.h"
#include "src/wallet.h"

int main()
{
    CDatabase db("./tmp/alysidadb");

    CWallet wallet1("Caleb");
    CWallet wallet2("Jane");

    wallet1.Send(wallet1.GetWalletAddress(), wallet2.GetWalletAddress(), 10);

    // CBlock block("genesis", {"hello", "world"});
    // block.RunPoW(db);

    return 0;
}