#include <iostream>
#include "src/block.h"
#include "src/db/database.h"
#include "src/transaction.h"
#include "src/private_key.h"

int main()
{
    CPrivateKey priv_key;
    CTransaction tx1("example_sender1", "example_rec2", 10);
    tx1.Sign(priv_key);

    std::string tx_json = tx1.ToJSON();
    std::cout << tx_json << "\n";
    return 0;
}