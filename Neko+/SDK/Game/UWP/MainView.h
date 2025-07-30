#pragma once

class MainView {
public:
    class BedrockPlatformUWP* getBedrockPlatform();
    static MainView* getInstance();
};