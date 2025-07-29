//
// Created by vastrakai on 6/24/2024.
//

#include "SigManager.h"

#include <iostream>
#include <chrono>
#include <omp.h>
#include <libhat.hpp>

#define NOW std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()

hat::scan_result SigManager::scanSig(hat::signature_view sig, const std::string& name, int offset)
{
    mSigScanCount++;

    auto minecraft = hat::process::get_process_module();
    auto result = hat::find_pattern(sig, ".text", minecraft);

    if (!result.has_result()) {
        mSigs[name] = 0;
        return {};
    }

    if (offset == 0) mSigs[name] = reinterpret_cast<uintptr_t>(result.get());
    else mSigs[name] = reinterpret_cast<uintptr_t>(result.rel(offset));

    return result;
}

void SigManager::initialize()
{
    int64_t start = NOW;
#pragma omp parallel for
    for (int i = 0; i < mSigInitializers.size(); i++) {
        mSigInitializers[i]();
    }
    int64_t end = NOW;
    int64_t diff = end - start;

    mIsInitialized = true;
}

void SigManager::deinitialize()
{
    mSigInitializers.clear();
    mSigs.clear();

    mIsInitialized = false;
}
