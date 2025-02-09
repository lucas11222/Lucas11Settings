/**
 * Credits to Prevter for using this for the base.
 * Sorry for the bad code :(
 */

/**
 * Custom Keybinds mod provides a way to bind custom key combinations to actions in the game.
 * We will use it to bind open/close button for out ImGui interface.
 */
#include <imgui-cocos.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include <Geode/Geode.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include <gdutilsdevs.gdutils/include/RateEvent.hpp>
#include <gdutilsdevs.gdutils/include/Types.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/LevelSearchLayer.hpp>
#include <eclipse.eclipse-menu/include/eclipse.hpp>
#include <eclipse.eclipse-menu/include/components.hpp>
#include <Geode/binding/GameLevelManager.hpp>
#include <Geode/binding/FMODAudioEngine.hpp> // sound engine
#include "SpotifyHeader.h"					 // Contents of add.h copied here
#include <iostream>
using namespace geode::prelude;
void setup()
{
	/**
	 * This function should be used for things like setting up ImGui style, loading fonts, etc.
	 * For this example, we will set up a custom font (which is stored in our mod resources).
	 */

	auto &io = ImGui::GetIO();
	auto fontPath = geode::Mod::get()->getResourcesDir() / "ProggyClean.ttf";
	// auto fontPath2 = geode::Mod::get()->getResourcesDir() / "Roboto-Regular.ttf";
	io.Fonts->AddFontFromFileTTF(fontPath.string().c_str(), 20.5f);
	// auto font2 = io.Fonts->AddFontFromFileTTF(fontPath2.string().c_str(), 25.0f);
	// ImGui::PushStyleColor(ImGuiCol_Border, (ImVec4(210.0f,100.0f,80.0f)));
	ImGuiStyle &style = ImGui::GetStyle();
	style.WindowRounding = 6.0f;
	style.FrameRounding = 2.3f;
	style.ScrollbarRounding = 0;

	style.Colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 0.90f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.09f, 0.09f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.85f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.70f, 0.70f, 0.70f, 0.65f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.01f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.90f, 0.80f, 0.80f, 0.40f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.90f, 0.65f, 0.65f, 1.5f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.83f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.40f, 0.40f, 0.80f, 0.20f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.87f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.01f, 0.01f, 0.02f, 0.80f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.55f, 0.53f, 0.55f, 0.51f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.56f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.91f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.83f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.70f, 0.70f, 0.70f, 0.62f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.30f, 0.30f, 0.30f, 0.84f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.48f, 0.72f, 0.89f, 0.49f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.50f, 0.69f, 0.99f, 0.68f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.30f, 0.69f, 1.00f, 0.53f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.44f, 0.61f, 0.86f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.38f, 0.62f, 0.83f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.85f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
	style.WindowMinSize = ImVec2(20.0f,40.0f);
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	// https://github.com/ocornut/imgui/issues/707#issuecomment-252413954
	// thank you for the theme
}

void draw()
{
	/**
	 * This function should be used for drawing ImGui widgets.
	 * You can put any ImGui code here, and it will be rendered on the screen.
	 */
	float volume = 100.0f;
	bool muted = false;
	bool automatic = false;
	ImGui::Begin("Lucas11Settings");
	ImGui::Text("%s", "Hello world!");
	if (ImGui::Button("Close"))
	{
		/* This will hide our ImGui interface. */
		ImGuiCocos::get().toggle();
	}
	ImGui::SameLine();
	if (ImGui::Button("Open Geode settings."))
	{
		/* This will hide our ImGui interface. */
		ImGuiCocos::get().toggle();
		geode::openSettingsPopup(Mod::get());
	}
	ImGui::End();
	// ImGui::PushFont(font2);
	if (PlayLayer::get())
	{
		ImGui::Begin("Info");
		ImGui::Text("%s", "Percent");
		ImGui::Text("%s", "-------");
		if (PlayLayer::PlayLayer::get()->m_hasCompletedLevel == true)
		{
			ImGui::Text("%s", "GG! 100%");
		}
		else
		{
			ImGui::Text("%s", std::to_string(PlayLayer::get()->getCurrentPercent()).c_str());
		}
		ImGui::Text("%s", "ID Level: ");
		ImGui::SameLine();
		ImGui::Text("%s", std::to_string(GJBaseGameLayer::get()->m_level->m_levelID).c_str());
		ImGui::Text("%s", "Level Name: ");
		ImGui::SameLine();
		ImGui::Text("%s", GJBaseGameLayer::get()->m_level->m_levelName.c_str());
		ImGui::Text("%s", "Attempts: ");
		ImGui::SameLine();
		ImGui::Text("%s", std::to_string(GJBaseGameLayer::get()->m_level->m_attempts).c_str());
		ImGui::Text("%s", "gonna add more (i suck at adding things)");
		ImGui::End();
	}
	ImGui::Begin("Song Request time! (dosent work)");
	ImGui::End();

	ImGui::Begin("Sound Control");
	ImGui::Text("volume slider is buged please dont use it");
	if ((ImGui::SliderFloat("Volume", &volume, 0.0f, 100.0f)))
	{
		toggleSpotifyVolume(automatic, volume);
	}
	if (ImGui::Button("Mute"))
	{
		toggleSpotifyMute(automatic, muted);
	}
	if (ImGui::Button("a"))
	{
		toggleSpotifyVolume(automatic, 1.0f);
	}
	ImGui::End();
	ImGui::Begin("Credits");
	ImGui::Text("%s", "Created by Lucas11.");
	ImGui::Text("%s", "Spotify code by Fire (check GDUtills!)");
	ImGui::Text("%s", "Thank to all the persons that help me at #help.");
	ImGui::Text("%s", "And you too for using this mod!");
	ImGui::End();
}

$on_mod(Loaded)
{
	ImGuiCocos::get()
		.setup(setup)
		.draw(draw)
		.setVisible(false); /* We don't want our ImGui interface to be visible by default. */
}

/**
 * $execute is a special macro that allows us to execute code when our mod first loads.
 * Then we will use Custom Keybinds API to register a new keybind for opening/closing our ImGui interface.
 */
$execute
{
	/**
	 * Bringing some namespaces into scope for easier access to classes and functions.
	 */
	using namespace geode::prelude;	
	using namespace keybinds;
	auto menuTab = eclipse::MenuTab::find("Lucas11Settings");
	auto menuTab2 = eclipse::MenuTab::find("Lucas11Settings: Credits");
	menuTab.addLabel("Hello world!");
	menuTab.addButton("Open Geode settings.", []()
					  { geode::openSettingsPopup(Mod::get()); });
	menuTab2.addLabel("Created by Lucas11.");
	menuTab2.addLabel("Spotify code by Fire (check GDUtills!)");
	menuTab2.addLabel("Thank to all the persons that help me at #help.");
	menuTab2.addLabel("And you too for using this mod!");
	BindManager::get()
		->registerBindable({
			"open-imgui"_spr,					  /* Keybind ID */
			"Open Interface",					  /* Keybind name */
			"Open or close the ImGui interface.", /* Keybind description */
			{Keybind::create(cocos2d::enumKeyCodes::KEY_L)},
			"Lucas11Settings" /* Category name (usually the name of your mod) */
		});
	new EventListener([=](InvokeBindEvent *event)
					  {
        if (event->isDown()) {
			auto aolsounds = Mod::get()->getSettingValue<bool>("aol-sounds");
			auto portal2sounds = Mod::get()->getSettingValue<bool>("torret-portal-sounds");
			//auto customsound = Mod::get()->getSettingValue<std::filesystem::path>("custom-sound-file");
			//auto customsoundenabled = Mod::get()->getSettingValue<bool>("customs-sounds");
			if (aolsounds == true) {
            	FMODAudioEngine::sharedEngine()->playEffect("open_menu-aol.ogg"_spr);
			}
			if (portal2sounds == true) {
				FMODAudioEngine::sharedEngine()->playEffect("open_portal_2.ogg"_spr);
			}
			//if (customsoundenabled == true) {
			//	FMODAudioEngine::sharedEngine()->playEffect(customsound);
			//}
			ImGuiCocos::get().toggle();
			//FMODAudioEngine::get()->playEffect(geode::Mod::get()->getResourcesDir() / "open_menu.mp3");
			if (!Mod::get()->setSavedValue("shown-upload-guidelines", true)) {
			EventData data = {
			false,
			2,
			6,
			1,
    		EventType::NA, // type of notification
    		"Hi!", // notification title
    		"sliderthumbsel.png", // sprite (MUST BE VALID OR WILL CRASH!)
    		"Please read the description before using this mod. Bye!", // level name
    		"Lucas11", // level creator
			0,
			false,	
			false,	
		};
		GDUtils::Events::RateEvent::emit(data);
		geode::openInfoPopup(Mod::get());
	}
		}
        return ListenerResult::Propagate; }, InvokeBindFilter(nullptr, "open-imgui"_spr));
};
#include <Geode/modify/MenuLayer.hpp>
class $modify(MyMenuLayer, MenuLayer)
{
	/**
	 * Typically classes in GD are initialized using the `init` function, (though not always!),
	 * so here we use it to add our own button to the bottom menu.
	 *
	 * Note that for all hooks, your signature has to *match exactly*,
	 * `void init()` would not place a hook!
	 */
	bool init()
	{
		/**
		 * We call the original init function so that the
		 * original class is properly initialized.
		 */
		if (!MenuLayer::init())
		{
			return false;
		}

		/**
		 * You can use methods from the `geode::log` namespace to log messages to the console,
		 * being useful for debugging and such. See this page for more info about logging:
		 * https://docs.geode-sdk.org/tutorials/logging
		 */
		log::debug("Hello from my MenuLayer::init hook! This layer has {} children.", this->getChildrenCount());

		/**
		 * See this page for more info about buttons
		 * https://docs.geode-sdk.org/tutorials/buttons
		 */
		auto myButton = CCMenuItemSpriteExtra::create(
			CCSprite::createWithSpriteFrameName("GJ_epicCoin3_001.png"),
			this,
			/**
			 * Here we use the name we set earlier for our modify class.
			 */
			menu_selector(MyMenuLayer::onMyButton));

		/**
		 * Here we access the `bottom-menu` node by its ID, and add our button to it.
		 * Node IDs are a Geode feature, see this page for more info about it:
		 * https://docs.geode-sdk.org/tutorials/nodetree
		 */
		auto menu = this->getChildByID("bottom-menu");
		menu->addChild(myButton);

		/**
		 * The `_spr` string literal operator just prefixes the string with
		 * your mod id followed by a slash. This is good practice for setting your own node ids.
		 */
		myButton->setID("my-button"_spr);

		/**
		 * We update the layout of the menu to ensure that our button is properly placed.
		 * This is yet another Geode feature, see this page for more info about it:
		 * https://docs.geode-sdk.org/tutorials/layouts
		 */
		menu->updateLayout();

		/**
		 * We return `true` to indicate that the class was properly initialized.
		 */
		return true;
	}

	/**
	 * This is the callback function for the button we created earlier.
	 * The signature for button callbacks must always be the same,
	 * return type `void` and taking a `CCObject*`.
	 */
	void onMyButton(CCObject *)
	{
		if (!Mod::get()->setSavedValue("shown-upload-guidelines", true))
		{
			EventData data = {
				false,
				2,
				6,
				1,
				EventType::NA,											   // type of notification
				"Hi!",													   // notification title
				"sliderthumbsel.png",									   // sprite (MUST BE VALID OR WILL CRASH!)
				"Please read the description before using this mod. Bye!", // level name
				"Lucas11",												   // level creator
				0,
				false,
				false,
			};
			GDUtils::Events::RateEvent::emit(data);
			geode::openInfoPopup(Mod::get());
		}
		auto aolsounds = Mod::get()->getSettingValue<bool>("aol-sounds");
		auto portal2sounds = Mod::get()->getSettingValue<bool>("torret-portal-sounds");
		if (aolsounds == true)
		{
			FMODAudioEngine::sharedEngine()->playEffect("open_menu-aol.ogg"_spr);
		}
		if (portal2sounds == true)
		{
			FMODAudioEngine::sharedEngine()->playEffect("open_portal_2.ogg"_spr);
		}
		ImGuiCocos::get().toggle();
	}
};
