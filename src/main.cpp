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
using namespace geode::prelude;
void setup() {
    /**
     * This function should be used for things like setting up ImGui style, loading fonts, etc.
     * For this example, we will set up a custom font (which is stored in our mod resources).
     */

    auto& io = ImGui::GetIO();
    auto fontPath = geode::Mod::get()->getResourcesDir() / "ProggyClean.ttf";
	auto fontPath2 = geode::Mod::get()->getResourcesDir() / "Roboto-Regular.ttf";
    io.Fonts->AddFontFromFileTTF(fontPath.string().c_str(), 20.5f);
	// auto font2 = io.Fonts->AddFontFromFileTTF(fontPath2.string().c_str(), 25.0f);
}

void draw() {
    /**
     * This function should be used for drawing ImGui widgets.
     * You can put any ImGui code here, and it will be rendered on the screen.
     */
	// extern auto font2;
    ImGui::Begin("Lucas11Settings");
    ImGui::Text("Hello world.");
    ImGui::Text("Read the README for using this mod.");
    if (ImGui::Button("Close")) {
        /* This will hide our ImGui interface. */
        ImGuiCocos::get().toggle();
    }
	if (ImGui::Button("Open Geode settings.")) {
        /* This will hide our ImGui interface. */
        ImGuiCocos::get().toggle();
		geode::openSettingsPopup(Mod::get());
    }
	ImGui::End();
	//ImGui::PushFont(font2);
	if (PlayLayer::get()) {
		auto percent = PlayLayer::get()->getCurrentPercent();
     	ImGui::Begin("Info");
		ImGui::Text("Percent:" ,std::to_string(percent).c_str());
		ImGui::Text("gonna add more (i suck at adding things)");
		ImGui::End();
	}
	//if (LevelSearchLayer::) {
		ImGui::Begin("Song Request time!");
		ImGui::Text("Lucas11 - ");
		ImGui::End();
	//}

	
	
}

$on_mod(Loaded) {
    ImGuiCocos::get()
        .setup(setup).draw(draw)
        .setVisible(false); /* We don't want our ImGui interface to be visible by default. */
}

/**
 * $execute is a special macro that allows us to execute code when our mod first loads.
 * Then we will use Custom Keybinds API to register a new keybind for opening/closing our ImGui interface.
 */
$execute {
    /**
     * Bringing some namespaces into scope for easier access to classes and functions.
     */
    using namespace geode::prelude;
    using namespace keybinds;

    BindManager::get()->registerBindable({
        "open-imgui"_spr, /* Keybind ID */
        "Open Interface", /* Keybind name */
        "Open or close the ImGui interface.", /* Keybind description */
        { Keybind::create(cocos2d::enumKeyCodes::KEY_L) },
        "Lucas11Settings" /* Category name (usually the name of your mod) */
    });
    new EventListener([=](InvokeBindEvent* event) {
        if (event->isDown()) {
			ImGuiCocos::get().toggle();
			if (!Mod::get()->setSavedValue("shown-upload-guidelines", true)) {
    			FLAlertLayer::create(
        			"Lucas11",
        			"Hello! Please read the description of the mod.",
        			"OK!"
    			)->show();
			
		geode::openInfoPopup(Mod::get());
	}
		}
        return ListenerResult::Propagate;
    }, InvokeBindFilter(nullptr, "open-imgui"_spr));
}
#include <Geode/modify/MenuLayer.hpp>
class $modify(MyMenuLayer, MenuLayer) {
	/**
	 * Typically classes in GD are initialized using the `init` function, (though not always!),
	 * so here we use it to add our own button to the bottom menu.
	 *
	 * Note that for all hooks, your signature has to *match exactly*,
	 * `void init()` would not place a hook!
	*/
	bool init() {
		/**
		 * We call the original init function so that the
		 * original class is properly initialized.
		 */
		if (!MenuLayer::init()) {
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
			menu_selector(MyMenuLayer::onMyButton)
		);

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
	void onMyButton(CCObject*) {
		if (!Mod::get()->setSavedValue("shown-upload-guidelines", true)) {
    		FLAlertLayer::create(
        		"Lucas11",
        		"Hello! Please read the description of the mod.",
        		"OK!"
    	)->show();
		geode::openInfoPopup(Mod::get());
	}
		ImGuiCocos::get().toggle();
		EventData data = {
			true,
			2,
			6,
			1,
    		EventType::smallChest, // type of notification
    		"hello world", // notification title
    		"GJ_editBtn_001.png", // sprite (MUST BE VALID OR WILL CRASH!)
    		"hi by mod", // level name
    		"by lucas11", // level creator
			0,
			false,	
			false,	
		};
		GDUtils::Events::RateEvent::emit(data);
	}
};
