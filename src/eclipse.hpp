#include "eclipse.eclipse-menu/include/components.hpp"
#include <eclipse.eclipse-menu/include/eclipse.hpp>
#include <Geode/Geode.hpp>
#include <Geode/ui/GeodeUI.hpp>
using namespace geode::prelude;

$execute {
    auto menuTab = eclipse::MenuTab::find("Lucas11Settings");
    menuTab.addLabel("Hello world.");
    menuTab.addLabel("Read the README for using this mod.");
    menuTab.addButton("Open Geode settings.", []() {
        geode::openSettingsPopup(Mod::get());
    });
    menuTab.addToggle("readme-check", "README", {
        
    });
    menuTab.addLabel
}