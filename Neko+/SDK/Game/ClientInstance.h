#pragma once
#include "../../Utils/MemUtils.h"
#include "../../Utils/Math.h"
#include "KeyboardMouseSettings.h"

class ClientInstance {
public:
    CLASS_FIELD(uintptr_t**, vtable, 0x0);
    static ClientInstance* get();

    class MinecraftSim* getMinecraftSim();
    class LevelRenderer* getLevelRenderer();
    class LoopbackPacketSender* getPacketSender();
    class GuiData* getGuiData();
    class bgfx_context* getBGFX();
    glm::vec2 getFov();

    class ClientInputHandler* getInputHandler();
    class KeyboardMouseSettings* getKeyboardSettings();
    class MinecraftGame* getMinecraftGame();
    class Actor* getLocalPlayer();
    class BlockSource* getBlockSource();
    class Options* getOptions();
    std::string getScreenName();
    void setDisableInput(bool disable);
    bool getMouseGrabbed();
    void grabMouse();
    void releaseMouse();
    void playUi(const std::string& soundName, float volume, float pitch);
    std::string lawl();
};