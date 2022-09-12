
#include "Precompiled.hpp"

CVar testCvar( "test_cvar", "0", CVarFlags::ReadOnly, "Some test CVar" );

class Application : public IApplication
{
public:
	bool Init( const EngineAPI& api ) override
	{
		Core = api.core;
		Console = api.console;
		FileSystem = api.fileSystem;
		MaterialManager = api.materialManager;
		ModelManager = api.modelManager;
		PluginSystem = api.pluginSystem;

		Audio = api.audio;
		Input = api.input;
		Renderer = api.renderer;

		CVar::RegisterAll();

		// Initialise in-game systems here
		Console->Print( "Application::Init: Game initialised" );

		return true;
	}

	void Shutdown() override
	{
		// Shut down in-game systems here
		Console->Print( "Application::Shutdown: Shutting down..." );

		CVar::UnregisterAll();

		Core = nullptr;
		Console = nullptr;
		FileSystem = nullptr;
		MaterialManager = nullptr;
		ModelManager = nullptr;
		PluginSystem = nullptr;

		Audio = nullptr;
		Input = nullptr;
		Renderer = nullptr;
	}

	void Update() override
	{
		// Update game systems here
	}

	const char* GetPluginName() const override
	{
		return "BTX Test Game";
	}
};

static PluginRegistry Registry( EngineVersion );

ADM_API PluginRegistry* GetPluginRegistry()
{
	Registry.Register<Application>();
	return &Registry;
}
