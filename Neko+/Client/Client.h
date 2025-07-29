#pragma once
#include <cstdint>
#include <functional>
#include <vector>
#include <unordered_map>
#include <string>
#include <libhat/Scanner.hpp>

class Client {
public:
    static Client& getInstance();
    bool initialize();
    void shutdown();
    bool isInitialized() const { return m_initialized; }

private:
    Client();
    ~Client();

    static Client* s_instance;
    bool m_initialized = false;
};