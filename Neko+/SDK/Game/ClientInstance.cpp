#include "ClientInstance.h"
#include <libhat/Access.hpp>
#include "../../Utils/OffsetManager.h"
#include "../../Utils/SigManager.h"
#include "MinecraftGame.h"

ClientInstance* ClientInstance::get()
{
    static MinecraftGame* game = MinecraftGame::getInstance();
    if (game == nullptr)
    {
        game = MinecraftGame::getInstance();
        return nullptr;
    }
    static ClientInstance* instance = game->getPrimaryClientInstance();
    if (instance == nullptr) instance = game->getPrimaryClientInstance();
    return instance;
}

glm::vec2 ClientInstance::getFov()
{
    float x = hat::member_at<float>(this, OffsetProvider::ClientInstance_mFovX); // 0x6F0
    float y = hat::member_at<float>(this, OffsetProvider::ClientInstance_mFovY); // 0x704
    return { x, y };
}

MinecraftSim* ClientInstance::getMinecraftSim()
{
    return hat::member_at<MinecraftSim*>(this, OffsetProvider::ClientInstance_mMinecraftSim);
}

LevelRenderer* ClientInstance::getLevelRenderer()
{
    return hat::member_at<LevelRenderer*>(this, OffsetProvider::ClientInstance_mLevelRenderer);
}

LoopbackPacketSender* ClientInstance::getPacketSender()
{
    return hat::member_at<LoopbackPacketSender*>(this, OffsetProvider::ClientInstance_mPacketSender);
}

GuiData* ClientInstance::getGuiData()
{
    return hat::member_at<GuiData*>(this, OffsetProvider::ClientInstance_mGuiData);
}

bgfx_context* ClientInstance::getBGFX()
{
    return *reinterpret_cast<bgfx_context**>(SigManager::ClientInstance_mBgfx);
}

ClientInputHandler* ClientInstance::getInputHandler()
{
    return MemUtils::callVirtualFunc<ClientInputHandler*>(OffsetProvider::ClientInstance_getInputHandler, this);
}

KeyboardMouseSettings* ClientInstance::getKeyboardSettings()
{
    return getInputHandler()->getMappingFactory()->getKeyboardMouseSettings();
}

MinecraftGame* ClientInstance::getMinecraftGame()
{
    return MinecraftGame::getInstance();

}

Actor* ClientInstance::getLocalPlayer()
{
    return MemUtils::callVirtualFunc<Actor*>(OffsetProvider::ClientInstance_getLocalPlayer, this);
}

BlockSource* ClientInstance::getBlockSource()
{
    return MemUtils::callVirtualFunc<BlockSource*>(OffsetProvider::ClientInstance_getBlockSource, this);
}

Options* ClientInstance::getOptions()
{
    return MemUtils::callVirtualFunc<Options*>(OffsetProvider::ClientInstance_getOptions, this);
}

std::string ClientInstance::getScreenName()
{
    std::string screen = "no_screen";
    static auto sig = SigManager::ClientInstance_getScreenName;
    auto fn = reinterpret_cast<std::string & (__thiscall*)(ClientInstance*, std::string&)>(sig);
    screen = fn(this, screen);
    return screen;
}

std::string ClientInstance::lawl()
{
    std::string screen = "no_screen";
    MemUtils::callVirtualFunc<std::string&>(271, this, screen);
    return screen;
}

void ClientInstance::setDisableInput(bool disable)
{
    MemUtils::callVirtualFunc<void>(OffsetProvider::ClientInstance_setDisableInput, this, disable);
}

bool ClientInstance::getMouseGrabbed()
{
    return !getMinecraftGame()->getMouseGrabbed();
}

void ClientInstance::grabMouse()
{
    static uintptr_t func = SigManager::ClientInstance_grabMouse;
    MemUtils::callFastcall<void>(func, this);

}

void ClientInstance::releaseMouse()
{
    static uintptr_t func = SigManager::ClientInstance_releaseMouse;
    MemUtils::callFastcall<void>(func, this);
    getMinecraftGame()->setMouseGrabbed(false);
}

void ClientInstance::playUi(const std::string& soundName, float volume, float pitch) {
    getMinecraftGame()->playUi(soundName, volume, pitch);
}
