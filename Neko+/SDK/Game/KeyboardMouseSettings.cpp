#include "KeyboardMouseSettings.h"
#include <string>
#include "../../Utils/OffsetManager.h"

int KeyboardMouseSettings::operator[](const std::string& key)
{
    for (auto& bind : mKeyTypeA) {
        if (bind.mBindName == key)
            return bind.mBindKey[0];
    }
    return -1;
}

KeyboardMouseSettings* ClientInputMappingFactory::getKeyboardMouseSettings()
{
    return hat::member_at<KeyboardMouseSettings*>(this, OffsetProvider::ClientInputMappingFactory_mKeyboardMouseSettings);
}

ClientInputMappingFactory* ClientInputHandler::getMappingFactory()
{
    return hat::member_at<ClientInputMappingFactory*>(this, OffsetProvider::ClientInputHandler_mMappingFactory);
}
