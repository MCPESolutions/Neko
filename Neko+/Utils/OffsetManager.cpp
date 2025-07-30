#include "OffsetManager.h"
#include <libhat.hpp>

#define NOW std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()

hat::scan_result OffsetProvider::scanSig(hat::signature_view sig, const std::string& name, int offset)
{
    mSigScanCount++;
    auto minecraft = hat::process::get_process_module();
    auto result = hat::find_pattern(sig, ".text", minecraft);

    if (!result.has_result()) {
        mSigs[name] = 0;
        return {};
    }

    mSigs[name] = reinterpret_cast<uintptr_t>(result.get()) + offset;
    return result;
}

void OffsetProvider::initialize()
{
    int64_t start = NOW;
#pragma omp parallel for
    for (int i = 0; i < mSigInitializers.size(); i++)
    {
        mSigInitializers[i]();
    }
    uint64_t end = NOW;
    mIsInitialized = true;
}

void OffsetProvider::deinitialize()
{

    mSigInitializers.clear();
    mSigs.clear();

    mIsInitialized = false;
}

