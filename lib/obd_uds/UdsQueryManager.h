#pragma once

#include <vector>
#include "UdsQuery.h"
#include <memory>

class UdsQueryManager
{
public:
    void loop(const uint32_t time_ms);
    void addQuery(std::unique_ptr<UdsQuery> &&query);

private:
    void checkRx(const uint32_t time_ms);
    void checkTx(const uint32_t time_ms);

private:
    std::vector<std::unique_ptr<UdsQuery>> queries;
};
