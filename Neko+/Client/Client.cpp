#include "Client.h"
#include "../Utils/OffsetManager.h"
#include "../Utils/SigManager.h"

Client* Client::s_instance = nullptr;

Client& Client::getInstance() {
    if (!s_instance) {
        s_instance = new Client();
    }
    return *s_instance;
}

Client::Client() {}

Client::~Client() {
    shutdown();
}

bool Client::initialize() {
    if (m_initialized) return true;
    SigManager::initialize();
    OffsetProvider::initialize();
    if (!SigManager::mIsInitialized || !OffsetProvider::mIsInitialized) {
        shutdown();
        return false;
    }
    m_initialized = true;
    return true;
}

void Client::shutdown() {
    if (!m_initialized) return;
    OffsetProvider::deinitialize();
    SigManager::deinitialize();
    m_initialized = false;
}