#pragma once
//
// Created by vastrakai on 6/24/2024.
//

#include <cstdint>
#include <future>
#include "../Libs/libhat/libhat.hpp"
#include "XorStr.h"

enum class SigType {
    Sig,
    RefSig
};

#define DEFINE_SIG(name, str, sig_type, offset) \
public: \
static inline uintptr_t name; \
private: \
static void name##_initializer() { \
    auto result = scanSig(hat::compile_signature<str>(), xorstr_(#name), offset); \
    if (!result.has_result()) { \
        name = 0; \
        return; \
    } \
    if (sig_type == SigType::Sig) name = reinterpret_cast<uintptr_t>(result.get()); \
    else name = reinterpret_cast<uintptr_t>(result.rel(offset)); \
} \
static inline std::function<void()> name##_function = (mSigInitializers.emplace_back(name##_initializer), std::function<void()>()); \
public:



class SigManager {
    static hat::scan_result scanSig(hat::signature_view sig, const std::string& name, int offset = 0);

    static inline std::vector<std::function<void()>> mSigInitializers;
    static inline int mSigScanCount;
public:
    static inline bool mIsInitialized = false;
    static inline std::unordered_map<std::string, uintptr_t> mSigs;

    DEFINE_SIG(Actor_setPosition, "48 89 5C 24 ? 57 48 83 EC ? 48 8B 59 ? 48 8B FA 48 8B 8B ? ? ? ? 48 85 C9", SigType::Sig, 0);
    DEFINE_SIG(Actor_getNameTag, "48 83 EC ? 48 8B 81 ? ? ? ? 48 85 C0 74 ? 48 89 5C 24 ? B9 ? ? ? ? 48 8B 18 48 8B 40 ? 48 2B C3 48 C1 F8 ? 66 3B C8 73 ? 48 8B 5B ? 48 85 DB 74 ? 48 8B 03 48 8B CB 48 8B 40 ? FF 15 ? ? ? ? 3C ? 48 8D 43", SigType::Sig, 0); // 1.21.70
    DEFINE_SIG(Actor_setNameTag, "E8 ? ? ? ? 4C 8D ? ? ? ? ? 8B D3 48 8B ? E8 ? ? ? ? E9", SigType::RefSig, 1);
    DEFINE_SIG(ClientInstance_getScreenName, "48 89 ? ? ? 48 89 ? ? ? 48 89 ? ? ? 57 48 83 EC ? 48 8B ? 48 8B ? 48 8D ? ? ? 48 8B ? ? ? ? ? FF 15 ? ? ? ? 48 8B ? 48 8B ? 48 85 ? 0F 84 ? ? ? ? 80 38 ? 0F 84 ? ? ? ? 48 8B ? ? 48 85 ? 74 ? F0 FF ? ? 48 8B ? 48 89 ? ? ? 48 8B ? ? 48 89 ? ? ? 48 8B ? ? 48 89 ? ? ? 48 8B ? ? 48 39 ? ? 74 ? 48 8B ? ? 48 85 ? 74 ? 48 8B ? 48 8B ? 48 8B ? ? ? ? ? FF 15 ? ? ? ? EB ? 48 8D ? ? ? ? ? 48 8B ? E8 ? ? ? ? 90 BF ? ? ? ? 48 85 ? 74 ? 8B C7 F0 0F ? ? ? 83 F8 ? 75 ? 48 8B ? 48 8B ? 48 8B ? FF 15 ? ? ? ? 8B C7 F0 0F ? ? ? 83 F8 ? 75 ? 48 8B ? 48 8B ? 48 8B ? ? FF 15 ? ? ? ? 90 48 C7 44 24 28 ? ? ? ? 48 8B ? ? ? 33 DB 48 89 ? ? ? 48 85 ? 74 ? 8B C7 F0 0F ? ? ? 83 F8 ? 75 ? 48 8B ? 48 8B ? 48 8B ? FF 15 ? ? ? ? 8B C7 F0 0F ? ? ? 83 F8 ? 75 ? 48 8B ? 48 8B ? 48 8B ? ? FF 15 ? ? ? ? 48 8B ? ? ? 48 C7 44 24 38 ? ? ? ? 48 85 ? 74 ? 8B C7 F0 0F ? ? ? 83 F8 ? 75 ? 48 8B ? 48 8B ? 48 8B ? FF 15 ? ? ? ? F0 0F ? ? ? 83 FF ? 75 ? 48 8B ? 48 8B ? 48 8B ? ? FF 15 ? ? ? ? 48 8B ? 48 8B ? ? ? 48 8B ? ? ? 48 8B ? ? ? ? ? ? 48 83 C4 ? 5F C3 E8 ? ? ? ? 90 CC 48 89", SigType::Sig, 0);
    DEFINE_SIG(ActorRenderDispatcher_render, "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 0F 29 B4 24 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 F7 4C 89 4C 24 ?", SigType::Sig, 0); // 1.21.51
    DEFINE_SIG(ClientInstance_mBgfx, "48 8B ? ? ? ? ? 48 8D ? ? ? ? ? FF 15 ? ? ? ? 0F B7", SigType::RefSig, 3);
    DEFINE_SIG(ClientInstance_grabMouse, "40 ? 48 83 EC ? 48 8B ? 48 8B ? 48 8B ? ? ? ? ? FF 15 ? ? ? ? 84 C0 74 ? 48 8B ? ? ? ? ? 48 8B ? 48 8B ? ? ? ? ? 48 83 C4 ? 5B 48 FF ? ? ? ? ? 48 83 C4 ? 5B C3 40", SigType::Sig, 0); // 1.21.51
    DEFINE_SIG(ClientInstance_releaseMouse, "40 ? 48 83 EC ? 48 8B ? 48 8B ? 48 8B ? ? ? ? ? FF 15 ? ? ? ? 84 C0 74 ? 48 8B ? ? ? ? ? 48 8B ? 48 8B ? ? ? ? ? 48 83 C4 ? 5B 48 FF ? ? ? ? ? 48 83 C4 ? 5B C3 48 89", SigType::Sig, 0); // 1.21.51
    DEFINE_SIG(ContainerScreenController_tick, "E8 ? ? ? ? 48 8B ? ? ? ? ? 48 8D ? ? ? ? ? 41 B8 ? ? ? ? 8B F8", SigType::RefSig, 1); // 1.21.51
    DEFINE_SIG(ContainerScreenController_handleAutoPlace, "E8 ? ? ? ? 66 ? ? ? ? ? ? ? 0F 8C", SigType::RefSig, 1); // 1.21.51
    DEFINE_SIG(ComplexInventoryTransaction_vtable, "48 8D 05 ? ? ? ? 48 8B F9 48 89 01 8B DA 48 83 C1 ? E8 ? ? ? ? F6 C3 ? 74 ? BA ? ? ? ? 48 8B CF E8 ? ? ? ? 48 8B 5C 24 ? 48 8B C7 48 83 C4 ? 5F C3 CC CC CC CC CC CC CC CC CC CC CC CC CC CC 48 89 5C 24 ? 48 89 74 24 ? 57 41 56", SigType::RefSig, 3); //8 toolong wtfffffffffffff
    DEFINE_SIG(EnchantUtils_getEnchantLevel, "48 89 ? ? ? 48 89 ? ? ? 57 48 81 EC ? ? ? ? 48 8B ? 0F B6 ? 33 FF", SigType::Sig, 0); // 1.21.51
    DEFINE_SIG(GameMode_getDestroyRate, "E8 ? ? ? ? 0F 28 ? 49 8B ? ? E8", SigType::RefSig, 1); // 1.21.51
    DEFINE_SIG(HoverTextRenderer_render, "48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 57 48 81 EC ? ? ? ? 0F 29 70 E8 0F 29 78 D8 44 0F 29 40 ? 49 8B D9 49 8B F8 48 8B F1 48 8B 6A 10", SigType::Sig, 0); // 1.21.51
    DEFINE_SIG(GameMode_baseUseItem, "E8 ? ? ? ? 84 C0 74 ? 48 8B ? 48 8B ? 48 8B ? ? ? ? ? FF 15 ? ? ? ? 48 85", SigType::RefSig, 1); // 1.21.51
    DEFINE_SIG(GuiData_displayClientMessage, "40 55 53 56 57 41 56 48 8D AC 24 A0 FE FF FF 48 81 EC 60 02 00 00 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 50 01 00 00 41", SigType::Sig, 0); // 1.21.51
    DEFINE_SIG(InventoryTransaction_addAction, "e8 ? ? ? ? 48 81 c3 ? ? ? ? 48 3b de 75 ? bb", SigType::RefSig, 1);
    DEFINE_SIG(ItemStack_vTable, "48 8D 05 ? ? ? ? 48 89 05 ? ? ? ? C7 05 ? ? ? ? ? ? ? ? C6 05 ? ? ? ? ? 48 8D 0D", SigType::RefSig, 3);
    DEFINE_SIG(ItemStack_getCustomName, "48 89 ? ? ? 57 48 83 EC ? 48 8B ? 48 8B ? E8 ? ? ? ? 84 C0 74 ? 48 8B ? 48 8B ? E8 ? ? ? ? 48 8B", SigType::Sig, 0); // 1.21.51
    DEFINE_SIG(ItemUseInventoryTransaction_vtable, "48 8D ? ? ? ? ? 48 89 ? 8B 46 ? 89 47 ? 0F B6 ? ? 88 47 ? 8B 56", SigType::RefSig, 3);
    DEFINE_SIG(ItemUseOnActorInventoryTransaction_vtable, "48 8d 05 ? ? ? ? 48 89 03 48 89 6b ? 89 6b ? c7 43", SigType::RefSig, 3);
    DEFINE_SIG(ItemReleaseInventoryTransaction_vtable, "48 8d 05 ? ? ? ? 48 89 43 ? c6 83 ? ? ? ? ? 89 ab ? ? ? ? c6 83 ? ? ? ? ? 89 ab ? ? ? ? 0f 57 c0 0f 11 83 ? ? ? ? 48 89 ab ? ? ? ? 48 c7 83 ? ? ? ? ? ? ? ? c6 83 ? ? ? ? ? 48 89 ab ? ? ? ? 89 ab", SigType::RefSig, 3); // "gamePlayEmote" -> couple of refs -> this 
    DEFINE_SIG(Keyboard_feed, "E8 ? ? ? ? E9 ? ? ? ? 41 0F ? ? ? 45 0F ? ? ? 45 0F", SigType::RefSig, 1);
    DEFINE_SIG(MainView_instance, "48 8B 05 ? ? ? ? C6 40 ? ? 0F 95 C0", SigType::RefSig, 3);
    DEFINE_SIG(MinecraftPackets_createPacket, "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 48 8B D9 48 89 4C 24 ? 33 F6", SigType::Sig, 0); // 1.21.70
    DEFINE_SIG(Mob_getJumpControlComponent, "E8 ? ? ? ? 48 85 C0 74 ? C6 40 ? ? 48 83 C4 ? 5B", SigType::RefSig, 1);
    DEFINE_SIG(Mob_getCurrentSwingDuration, "48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 56 48 83 EC 30 8B 41 18 48 8D", SigType::Sig, 0); // 1.21.51
    DEFINE_SIG(MouseDevice_feed, "E8 ? ? ? ? 40 88 ? ? ? EB ? 40 84", SigType::RefSig, 1);
    DEFINE_SIG(NetworkStackItemDescriptor_ctor, "E8 ? ? ? ? 90 48 8B ? 48 8D ? ? ? ? ? E8 ? ? ? ? 4C 8D ? ? ? ? ? 4C 89 ? ? ? ? ? 48 8D", SigType::RefSig, 1);
    //DEFINE_SIG(PlayerMovement_clearInputStateInlined, "75 ? 48 8B ? ? ? ? ? ? 48 8D ? ? ? ? ? ? 48 89 ? ? ? 4D 8B", SigType::Sig, 0);
    //DEFINE_SIG(PlayerMovement_clearInputStateInlined2, "0F 84 ? ? ? ? 48 8B ? ? 48 89 ? ? ? ? ? ? 48 89 ? ? ? ? ? ? 4C 89 ? ? ? ? ? ? 0F 10", SigType::Sig, 0);

    DEFINE_SIG(RakNet_RakPeer_runUpdateCycle, "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 0F 29 B4 24 ? ? ? ? 0F 29 BC 24 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B EA 48 89 54 24 ? 48 8B D9", SigType::Sig, 0);
    DEFINE_SIG(RakNet_RakPeer_sendImmediate, "40 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 48 8D 6C 24 ? 48 89 9D ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C5 48 89 85 ? ? ? ? 4C 8B 95 ? ? ? ? 40 32 FF", SigType::Sig, 0);
    DEFINE_SIG(ScreenView_setupAndRender, "48 8B C4 48 89 58 18 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 98 FD", SigType::Sig, 0); // 1.21.51
    DEFINE_SIG(SimulatedPlayer_simulateJump, "40 53 48 83 EC ? 48 8B 01 48 8B D9 48 8B 80 ? ? ? ? FF 15 ? ? ? ? 84 C0 0F 84 ? ? ? ? 4C 8B 53", SigType::Sig, 0);
    DEFINE_SIG(ItemInHandRenderer_render_bytepatch, "F3 0F ? ? ? ? ? ? 48 8B ? F3 41 ? ? ? 0F 57", SigType::Sig, 0);
    DEFINE_SIG(SneakMovementSystem_tickSneakMovementSystem, "32 C0 41 88 41 ? 84 C0", SigType::Sig, 0);
    DEFINE_SIG(ConnectionRequest_create, "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 49 8B D9 41 8B F0", SigType::Sig, 0);
    DEFINE_SIG(CameraDirectLookSystemUtil_handleLookInput, "40 53 48 83 EC ? F3 41 0F 10 49", SigType::Sig, 0);
    DEFINE_SIG(ItemRenderer_render, "48 8B ? 48 89 ? ? 55 56 57 41 ? 41 ? 41 ? 41 ? 48 81 EC ? ? ? ? 0F 29 ? ? 0F 29 ? ? 44 0F ? ? ? 44 0F ? ? ? 49 8B", SigType::Sig, 0);
    //DEFINE_SIG(ItemPositionConst, "F3 0F ? ? ? ? ? ? F3 0F ? ? F3 0F ? ? F3 0F ? ? ? ? ? ? F3 0F ? ? 0F B7", SigType::Sig, 0);
    /*DEFINE_SIG(glm_rotate, "40 53 48 83 EC ? F3 0F 59 0D ? ? ? ? 4C 8D 4C 24", SigType::Sig, 0);
    DEFINE_SIG(glm_rotateRef, "E8 ? ? ? ? 0F 28 ? ? ? ? ? 48 8B ? C6 40 38", SigType::Sig, 0);
    DEFINE_SIG(glm_translateRef, "E8 ? ? ? ? E9 ? ? ? ? 40 84 ? 0F 84 ? ? ? ? 83 FF", SigType::Sig, 0);
    DEFINE_SIG(glm_translateRef2, "E8 ? ? ? ? C6 46 ? ? F3 0F 11 74 24 ? F3 0F 10 1D", SigType::Sig, 0);*/
    DEFINE_SIG(BlockSource_fireBlockChanged, "4C 8B ? 45 89 ? ? 49 89 ? ? 53", SigType::Sig, 0);
    DEFINE_SIG(ActorAnimationControllerPlayer_applyToPose, "40 53 55 56 57 41 54 41 56 41 57 48 81 EC ? ? ? ? 48 63 AC 24", SigType::Sig, 0); // 1.21.80
    DEFINE_SIG(JSON_parse, "E8 ? ? ? ? 0F B6 D8 48 8D 8D ? ? ? ? E8 ? ? ? ? 90 48 8D 8D ? ? ? ? E8 ? ? ? ? 84 DB 0F 84 ? ? ? ? C6 44 24", SigType::RefSig, 1);
    DEFINE_SIG(Actor_getStatusFlag, "E8 ? ? ? ? 84 C0 75 ? 48 8B CF E8 ? ? ? ? 48 8B C8", SigType::RefSig, 1); // 8
    DEFINE_SIG(Level_getRuntimeActorList, "48 89 ? ? ? 55 56 57 48 83 EC ? 48 8B ? 48 89 ? ? ? 33 D2", SigType::Sig, 0); // 1.21.51
    DEFINE_SIG(ConcreteBlockLegacy_getCollisionShapeForCamera, "48 89 5C 24 ? 55 56 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 49 8B B0", SigType::Sig, 0); //8
    DEFINE_SIG(WaterBlockLegacy_getCollisionShapeForCamera, "0F 10 ? ? ? ? ? 48 8B ? F2 0F ? ? ? ? ? ? 0F 11 ? F2 0F ? ? ? C3 CC", SigType::Sig, 0);
    DEFINE_SIG(mce_framebuilder_RenderItemInHandDescription_ctor, "48 89 ? ? ? 48 89 ? ? ? 55 56 57 41 ? 41 ? 41 ? 41 ? 48 83 EC ? 4D 8B ? 4D 8B ? 4C 8B ? 48 8B ? 45 33", SigType::Sig, 0);

    DEFINE_SIG(ResourcePackManager_composeFullStackBp, "74 ? 4C 8D 0D ? ? ? ? 41 B8 ? ? ? ? E8 ? ? ? ? E9 ? ? ? ? 48 8D 8D", SigType::Sig, 0);
    DEFINE_SIG(ClientInstance_isPreGame, "48 83 EC ? 48 8B ? 48 8B ? ? ? ? ? FF 15 ? ? ? ? 48 85 ? 0F 94", SigType::Sig, 0);
    DEFINE_SIG(tickEntity_ItemUseSlowdownModifierComponent, "48 89 ? ? ? 48 89 ? ? ? 57 48 83 EC ? 49 8B ? 4D 85", SigType::Sig, 0); // ?tickEntity@?$Impl@U?$type_list@AEBUItemInUseComponent@@V?$EntityModifier@UItemUseSlowdownModifierComponent@@@@@entt@@U?$type_list@U?$type_list@U?$Include@V?$FlagComponent@UActorMovementTickNeededFlag@@@@UPlayerInputRequestComponent@@@@U?$Exclude@UPassengerComponent@@@@@entt@@AEBVStrictEntityContext@@AEBUItemInUseComponent@@V?$EntityModifier@UItemUseSlowdownModifierComponent@@@@@2@U?$type_list@V?$EntityModifier@UItemUseSlowdownModifierComponent@@@@@2@@?$CandidateAdapter@$MP6AXU?$type_list@U?$Include@V?$FlagComponent@UActorMovementTickNeededFlag@@@@UPlayerInputRequestComponent@@@@U?$Exclude@UPassengerComponent@@@@@entt@@AEBVStrictEntityContext@@AEBUItemInUseComponent@@V?$EntityModifier@UItemUseSlowdownModifierComponent@@@@@Z1?doItemUseSlowdownSystem@ItemUseSlowdownSystemImpl@@YAX0123@Z@details@@SAXAEBVStrictEntityContext@@AEBUItemInUseComponent@@V?$EntityModifier@UItemUseSlowdownModifierComponent@@@@@Z
    DEFINE_SIG(checkBlocks, "48 8D 05 ? ? ? ? 4D 8B CE 48 89 44 24 ? 4C 8D 44 24", SigType::Sig, 0);
    //DEFINE_SIG(JSON_toStyledString, "E8 ? ? ? ? 90 0F B7 ? ? ? ? ? 66 89 ? ? ? ? ? 48 8D ? ? ? ? ? 48 8D ? ? ? ? ? E8 ? ? ? ? 0F 57 ? 0F 11 ? ? ? ? ? 48 8D ? ? ? ? ? 48 89 ? ? ? ? ? 8B 85 ? ? ? ? 89 85 ? ? ? ? 4C 8B ? ? ? ? ? 49 8B ? 48 8D ? ? ? ? ? E8 ? ? ? ? 48 8B ? ? ? ? ? 48 8D ? ? ? ? ? E8 ? ? ? ? 48 8B ? 48 8D ? ? ? ? ? E8 ? ? ? ? 90 48 8D ? ? ? ? ? 48 8D ? ? ? ? ? E8 ? ? ? ? 90 0F 57 ? 33 C0 0F 11 ? ? ? ? ? 48 89 ? ? ? ? ? 48 8D ? ? ? ? ? E8 ? ? ? ? 90 48 8D", SigType::RefSig, 1);

    // TODO: Identify proper function names for these and refactor them accordingly

    DEFINE_SIG(Unknown_renderBlockOverlay, "40 55 53 56 57 41 54 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 49 8B D9 49 8B F0", SigType::Sig, 0);
    DEFINE_SIG(FastEat, "45 0F B6 F4 48 8D 4F", SigType::Sig, 0); //8
    DEFINE_SIG(Unknown_renderNametag, "48 8B ? 55 53 56 57 41 ? 41 ? 41 ? 48 8D ? ? 48 81 EC ? ? ? ? 0F 29 ? ? 0F 29 ? ? 48 8B ? ? ? ? ? 48 33 ? 48 89 ? ? 4C 89", SigType::Sig, 0);
    DEFINE_SIG(Reach, "74 ? F3 44 ? ? ? ? ? ? ? EB ? F3 0F", SigType::Sig, 0);
    DEFINE_SIG(BlockReach, "F3 0F ? ? ? ? ? ? 48 8B ? ? ? 48 83 C4 ? 5F C3 83 C0", SigType::Sig, 0);
    DEFINE_SIG(GetSpeedInAirWithSprint, "41 C7 40 ? ? ? ? ? F6 02", SigType::Sig, 0);
    DEFINE_SIG(ConnectionRequest_create_DeviceModel, "48 8B 11 48 83 C2 ? EB", SigType::Sig, 0);
    DEFINE_SIG(ConnectionRequest_create_DeviceOS, "BA ? ? ? ? 0F 44 ? C3 CC CC CC CC CC CC CC CC CC", SigType::Sig, 0);
    DEFINE_SIG(ConnectionRequest_create_DefaultInputMode, "48 8D 4C 24 ? E8 ? ? ? ? 90 48 8D 15 ? ? ? ? 48 8D 4D ? E8 ? ? ? ? 48 8B C8 48 8D 54 24 ? E8 ? ? ? ? 90 48 8D 4C 24 ? E8 ? ? ? ? 8B 54 24 ? 48 8D 4C 24 ? E8 ? ? ? ? 90 48 8D 15 ? ? ? ? 48 8D 4D ? E8 ? ? ? ? 48 8B C8 48 8D 54 24 ? E8 ? ? ? ? 90 48 8D 4C 24 ? E8 ? ? ? ? 8B 95", SigType::Sig, 0); // this shit is so fat
    DEFINE_SIG(ConnectionRequest_create_CurrentInputMode, "8B 54 24 ? 48 8D 4C 24 ? E8 ? ? ? ? 90 48 8D 15 ? ? ? ? 48 8D 4D ? E8 ? ? ? ? 48 8B C8 48 8D 54 24 ? E8 ? ? ? ? 90 48 8D 4C 24 ? E8 ? ? ? ? 8B 95", SigType::Sig, 0); // this shit is so fat
    DEFINE_SIG(InputModeBypass, "8b d7 48 8b ce 48 8b 80 ? ? ? ? ff 15 ? ? ? ? 49 8b 07", SigType::Sig, 0);
    DEFINE_SIG(InputModeBypassFix, "49 8b 07 8b d7 49 8b cf 48 8b 80 ? ? ? ? ff 15 ? ? ? ? 49 8b 07", SigType::Sig, 0); // fixes gui bugs, withot it ur inv will works like on mobile
    DEFINE_SIG(TapSwingAnim, "F3 44 ? ? ? ? ? ? ? 4C 8D ? ? ? 48 8B ? 48 C7 44 24 30 ? ? ? ? c7 44 24 ? ? ? ? ? 8b 08", SigType::RefSig, 5);
    DEFINE_SIG(Unknown_updatePlayerFromCamera, "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 41 8B 58", SigType::Sig, 0);

    DEFINE_SIG(FluxSwing, "E8 ? ? ? ? 48 8B ? F3 0F ? ? ? ? ? ? F3 0F ? ? ? ? ? ? F3 0F ? ? ? ? ? ? C6 40 38 ? 48 8B ? EB", SigType::Sig, 0);
    DEFINE_SIG(BobHurt, "48 89 5C 24 ? 57 48 81 EC ? ? ? ? 0F 29 B4 24 ? ? ? ? 48 81 C1", SigType::Sig, 0); // 1.21.51
    DEFINE_SIG(CameraComponent_applyRotation, "66 0F ? ? 0F 5B ? 0F 2F ? 76 ? F3 0F ? ? F3 0F", SigType::Sig, 0); // Guessed func name
    DEFINE_SIG(Actor_canSee, "E8 ? ? ? ? 84 C0 74 ? 48 8B ? ? 48 8B ? 48 8B ? 48 8B ? ? ? ? ? FF 15 ? ? ? ? E9", SigType::RefSig, 1);

    DEFINE_SIG(BaseAttributeMap_getInstance, "4C 8B C9 89 54 24 ? 48 B9 ? ? ? ? ? ? ? ? 44 0F B6 C2 48 B8 ? ? ? ? ? ? ? ? 4C 33 C0 0F B6 44 24 ? 4C 0F AF C1 4C 33 C0 0F B6 44 24 ? 4C 0F AF C1 4C 33 C0 0F B6 44 24 ? 4C 0F AF C1 4C 33 C0 4C 0F AF C1 49 8B 49 ? 49 23 C8 4D 8B 41 ? 48 C1 E1 ? 49 03 49 ? 48 8B 41 ? 49 3B C0 74 ? 48 8B 09 3B 50 ? 74 ? 66 90 48 3B C1 74 ? 48 8B 40 ? 3B 50 ? 75 ? EB ? 33 C0 48 85 C0 48 8D 15 ? ? ? ? 49 0F 44 C0 49 3B C0 48 8D 48 ? 48 0F 45 D1 48 8B C2 C3 CC 48 89 5C 24", SigType::Sig, 0);

    //DEFINE_SIG(ItemInHandRenderer_renderItem_bytepatch, "F3 0F ? ? ? ? ? ? 0F 57 ? F3 0F ? ? ? ? ? ? F3 0F ? ? 0F 2F ? 73 ? F3 41", SigType::Sig, 0);
    DEFINE_SIG(ItemInHandRenderer_renderItem_bytepatch2, "8B 52 ? 48 8B 40 ? FF 15 ? ? ? ? 48 8B F8 EB ? 48 8D 3D ? ? ? ? 48 8B 8B", SigType::Sig, 0); //8
    DEFINE_SIG(GammaSig, "48 83 EC ? 80 B9 ? ? ? ? ? 48 8D 54 24 ? 48 8B 01 48 8B 40 ? 74 ? 41 B8 ? ? ? ? FF 15 ? ? ? ? 48 8B 10 48 85 D2 74 ? 48 8B 42 ? 48 8B 88 ? ? ? ? 48 85 C9 74 ? E8 ? ? ? ? 48 83 C4 ? C3 F3 0F 10 42 ? 48 83 C4 ? C3 41 B8 ? ? ? ? FF 15 ? ? ? ? 48 8B 10 48 85 D2 75 ? E8 ? ? ? ? CC E8 ? ? ? ? CC CC CC CC CC CC CC CC CC CC CC CC CC CC CC CC 48 89 5C 24", SigType::Sig, 0); //8
    DEFINE_SIG(ZoomSig, "48 8B C4 48 89 58 ? 48 89 70 ? 57 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 44 0F 29 40 ? 44 0F 29 48 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 41 0F B6 F0", SigType::Sig, 0); //8
    DEFINE_SIG(Fistpr, "48 83 EC 28 48 8B 01 48 8D 54 24 30 41 B8 03 00 00 00", SigType::Sig, 0); //its super long i usaing no wl sig
    DEFINE_SIG(FovHk, "48 8b c4 48 89 58 ? 48 89 70 ? 57 48 81 ec ? ? ? ? 0f 29 70 ? 0f 29 78 ? 44 0f 29 40 ? 44 0f 29 48 ? 48 8b 05 ? ? ? ? 48 33 c4 48 89 44 24 ? 41 0f b6 f0", SigType::Sig, 0);


    static void initialize();
    static void deinitialize();
};

