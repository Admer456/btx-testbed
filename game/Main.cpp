
#include "Precompiled.hpp"
#include "client/ClientGame.hpp"
#include "server/ServerGame.hpp"

// The CVar system needs this for auto-registration
namespace detail
{
	CVarList GameCVarList = CVarList();
}

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

		clientGame.Init();
		serverGame.Init();
	
		return true;
	}

	void Shutdown() override
	{
		Core = nullptr;
		Animation = nullptr;
		Collision = nullptr;
		Console = nullptr;
		FileSystem = nullptr;
		MaterialManager = nullptr;
		ModelManager = nullptr;
		Network = nullptr;
		Physics = nullptr;

		clientGame.Shutdown();
		serverGame.Shutdown();
	}

	void Update() override
	{
		clientGame.Update();
		serverGame.Update();
	}

	const char* GetPluginName() const override
	{
		return "BTX Test Game";
	}

private:
	ClientGame clientGame;
	ServerGame serverGame;
};

ADM_API PluginRegistry* GetPluginRegistry()
{
	static auto& registry = PluginRegistry( EngineVersion )
		.Register<Application>();

	return &registry;
}
