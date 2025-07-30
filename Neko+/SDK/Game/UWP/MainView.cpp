#include "MainView.h"
#include "../../Utils/OffsetManager.h"
#include "../../Utils/SigManager.h"

class BedrockPlatformUWP* MainView::getBedrockPlatform()
{
    return hat::member_at<BedrockPlatformUWP*>(this, OffsetProvider::MainView_bedrockPlatform);
}

MainView* MainView::getInstance()
{
    static auto mainView = reinterpret_cast<MainView**>(SigManager::MainView_instance);
    return *mainView;
}