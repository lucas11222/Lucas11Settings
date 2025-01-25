/**
 * Include the Geode headers.
 */
#include <Geode/Geode.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include <gdutilsdevs.gdutils/include/RateEvent.hpp>
#include <gdutilsdevs.gdutils/include/Types.hpp>
#include <imgui-cocos.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>
/**
 * Brings cocos2d and all Geode namespaces to the current scope.
 */
using namespace geode::prelude;

/**
 * `$modify` lets you extend and modify GD's classes.
 * To hook a function in Geode, simply $modify the class
 * and write a new function definition with the signature of
 * the function you want to hook.
 *
 * Here we use the overloaded `$modify` macro to set our own class name,
 * so that we can use it for button callbacks.
 *
 * Notice the header being included, you *must* include the header for
 * the class you are modifying, or you will get a compile error.
 *
 * Another way you could do this is like this:
 *
 * struct MyMenuLayer : Modify<MyMenuLayer, MenuLayer> {};
 */
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

		
        if (!MenuLayer::init()) return false;
          static bool initialized = false;
        if (!initialized) {
              ImGuiCocos::get()
                  .setup(setup).draw(draw)
                  .setVisible(false);
              initialized = true;
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
		auto& io = ImGui::GetIO();
    	auto fontPath = geode::Mod::get()->getResourcesDir() / "Roboto-Regular.ttf";
    	io.Fonts->AddFontFromFileTTF(fontPath.string().c_str(), 16.0f);
		return true;
	}
	void draw() {
    /**
     * This function should be used for drawing ImGui widgets.
     * You can put any ImGui code here, and it will be rendered on the screen.
     */
    	ImGui::Begin("Hello, ImGui!");

    	ImGui::Text("This is a simple ImGui window.");
    	ImGui::Text("You can put any ImGui widgets here.");

    	if (ImGui::Button("Close")) {
        	/* This will hide our ImGui interface. */
        	ImGuiCocos::get().toggle();
    }

    ImGui::End();
	}	
	/**
	 * This is the callback function for the button we created earlier.
	 * The signature for button callbacks must always be the same,
	 * return type `void` and taking a `CCObject*`.
	*/
	$execute {
    /**
     * Bringing some namespaces into scope for easier access to classes and functions.
     */
    	using namespace geode::prelude;
    	using namespace keybinds;

    	BindManager::get()->registerBindable({
        	"open-menu-settings"_spr, /* Keybind ID */
        	"Open Interface", /* Keybind name */
        	"Open or close the ImGui interface.", /* Keybind description */
        	{ Keybind::create(cocos2d::enumKeyCodes::KEY_S, Modifier::Alt) },
        	"Lucas11Settings" /* Category name (usually the name of your mod) */
    	});
    	new EventListener([=](InvokeBindEvent* event) {
        	if (event->isDown()) ImGuiCocos::get().toggle();
        	return ListenerResult::Propagate;
    	}, InvokeBindFilter(nullptr, "open-menu-settings"_spr));
	}
	void onMyButton(CCObject*) {
		geode::openSettingsPopup(Mod::get());
		if (!Mod::get()->setSavedValue("shown-upload-guidelines", true)) {
    		FLAlertLayer::create(
        	"Lucas11",
        	"Hello! Please read the README or the description of the mod.",
        	"OK"
			
    	)->show();
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

	}
};