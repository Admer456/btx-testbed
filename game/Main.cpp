
#include "Precompiled.hpp"

CVar testCvar( "test_cvar", "0", CVarFlags::ReadOnly, "Some test CVar" );

class Application : public IApplication
{
public:
	bool Init( const EngineAPI& api ) override
	{
		Core = api.core;
		Animation = api.animation;
		Collision = api.collision;
		Console = api.console;
		FileSystem = api.fileSystem;
		MaterialManager = api.materialManager;
		ModelManager = api.modelManager;
		Network = api.network;
		Physics = api.physics;
		PluginSystem = api.pluginSystem;

		Audio = api.audio;
		Input = api.input;
		Renderer = api.renderer;

		// Initialise in-game systems here
		Console->Print( "Application::Init: Game initialised" );

		return true;
	}

	void Shutdown() override
	{
		// Shut down in-game systems here
		Console->Print( "Application::Shutdown: Shutting down..." );

		Core = nullptr;
		Animation = nullptr;
		Collision = nullptr;
		Console = nullptr;
		FileSystem = nullptr;
		MaterialManager = nullptr;
		ModelManager = nullptr;
		Network = nullptr;
		Physics = nullptr;
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

ADM_API PluginRegistry* GetPluginRegistry()
{
	static auto& registry = PluginRegistry( EngineVersion )
		.Register<Application>();

	return &registry;
}
