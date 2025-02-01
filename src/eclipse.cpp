#include "eclipse.eclipse-menu/include/components.hpp"
#include <eclipse.eclipse-menu/include/eclipse.hpp>
#include <Geode/Geode.hpp>
#include <Geode/ui/GeodeUI.hpp>

$execute {
        using namespace geode::prelude;
        auto menuTab = eclipse::MenuTab::find("Lucas11Settings");
        menuTab.addLabel("Hello world.");
        menuTab.addLabel("Read the README for using this mod.");
        menuTab.addButton("Open Geode settings.", []() {
            geode::openSettingsPopup(Mod::get());
        });
}