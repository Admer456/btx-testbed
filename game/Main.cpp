// SPDX-FileCopyrightText: 2022 Admer Šuko
// SPDX-License-Identifier: MIT

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
		Renderer = api.renderFrontend;

		CVar::RegisterAll();

		Console->Print( "Application::Init: Game initialised" );
		return true;
	}

	// Initialise in-game systems here
	void Start() override
	{
		adm::DateTime date = adm::DateTime::Now();
		Console->Print( adm::format( "The date is: %i/%i/%i %i:%i:%i",
			date.GetYear(), date.GetMonth(), date.GetDay(),
			date.GetHour(), date.GetMinute(), date.GetSecond() ) );

		Console->Print( "Available video modes:" );
		auto videoModes = Core->GetWindows()[0]->GetAvailableVideoModes();
		for ( const auto& videoMode : videoModes )
		{
			if ( videoMode.refreshRate >= 60 )
			{
				Console->Print( adm::format( "  * %ix%i, %i Hz", videoMode.width, videoMode.height, videoMode.refreshRate ) );
			}
		}

		SetupRenderingData();
	}

	void Shutdown() override
	{
		// Shut down in-game systems here
		Console->Print( "Application::Shutdown: Shutting down..." );

		if ( nullptr != mainView )
		{
			Renderer->DestroyView( mainView );
			mainView = nullptr;	
		}

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
		if ( Renderer )
		{
			Renderer->RenderView( mainView );
		}
	}

	inline static const Vector<Render::Data::Vertex> PentagonVertexData
	{
		Render::Data::VertexPos( { 0.0f, 0.5f, 0.0f } ),
		Render::Data::VertexPos( { 0.5f, 0.2f, 0.0f } ),
		Render::Data::VertexPos( { 0.3f, -0.4f, 0.0f } ),
		Render::Data::VertexPos( { -0.3f, -0.4f, 0.0f } ),
		Render::Data::VertexPos( { -0.5f, 0.2f, 0.0f } ),
	};

	inline static const Vector<uint32_t> PentagonVertexIndices
	{
		0, 1, 2,
		0, 2, 3,
		0, 3, 4
	};

	void SetupRenderingData()
	{
		// Models can be either programmatically generated like this,
		// or in the future, loaded from a file
		Render::ModelDesc modelDesc;
		// Names are optional but good for debugging
		modelDesc.modelData.name = "test_5gon_model";
		// First you start off with a mesh
		auto& mesh = modelDesc.modelData.meshes.emplace_back();
		mesh.name = "Mesh001";
		// Then you add a sur*face* to that mesh
		auto& face = mesh.faces.emplace_back();
		// And finally here, you add the actual geometry data and stuff
		face.vertexData = PentagonVertexData;
		face.vertexIndices = PentagonVertexIndices;
		// And then send it to the model manager to actually create the model for you
		showcaseModel = ModelManager->CreateModel( modelDesc );
		
		if ( nullptr != Renderer )
		{
			// A view is basically a camera. You can position it, rotate it,
			// change the FOV and stuff like that
			Render::ViewDesc mainViewDesc;
			mainViewDesc.viewMatrix = Mat4::Identity;
			mainViewDesc.projectionMatrix = Mat4::Identity;
			mainViewDesc.viewportSize = Vec2( -1.0f );
			mainView = Renderer->CreateView( mainViewDesc );

			// Now that we have a model, we need an object that will display that model
			// That is basically a render entity
			Render::EntityDesc entityDesc;
			entityDesc.model = showcaseModel;
			entityDesc.transform = Mat4::Identity;
			renderEntity = Renderer->CreateEntity( entityDesc );
		}
		else
		{
			Console->Warning( "Renderer doesn't exist, there will be no video" );
		}
	}

	const char* GetPluginName() const override
	{
		return "BTX Test Game";
	}

private:
	Render::IView* mainView{ nullptr };
	Render::IModel* showcaseModel{ nullptr };
	Render::IEntity* renderEntity{ nullptr };
};

static PluginRegistry Registry( EngineVersion );

ADM_API PluginRegistry* GetPluginRegistry()
{
	return &Registry.Register<Application>();
}
