#pragma once

#include <vector>
#include "UdsQuery.h"

class UdsQueryManager
{
public:
    void loop(const uint32_t time_ms);
    void addQuery(const UdsQuery &query);

private:
    void checkRx(const uint32_t time_ms);
    void checkTx(const uint32_t time_ms);

private:
    std::vector<UdsQuery> queries;
};
