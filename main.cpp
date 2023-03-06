#include <iostream>
#include "src/block.h"
#include "src/db/database.h"
#include "src/transaction.h"

int main()
{
    CDatabase db;
    CBlock b1("genesis", {"hello", "world"});
    b1.RunPoW(db);

    std::cout << "---------------------------------------------\n";

    std::string bJSON = db.GetBlockByHash(b1.GetHash());

    std::cout << bJSON << "\n";

    return 0;
}