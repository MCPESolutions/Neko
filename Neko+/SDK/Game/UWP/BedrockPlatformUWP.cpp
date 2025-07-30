#include "BedrockPlatformUWP.h"
#include "../../Utils/OffsetManager.h"

MinecraftGame* BedrockPlatformUWP::getMinecraftGame()
{
    return hat::member_at<MinecraftGame*>(this, OffsetProvider::BedrockPlatformUWP_mcGame);
}
