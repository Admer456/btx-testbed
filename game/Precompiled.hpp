// SPDX-FileCopyrightText: 2022 Admer Šuko
// SPDX-License-Identifier: MIT

#pragma once

#include "common/Precompiled.hpp"

inline EngineAPI* Engine = nullptr;

// Copy pasted from EngineAPI as a convenience layer, less typing
// 
// Shared stuff
// Both the server & client game use these
inline ICore* Core = nullptr;                       // system info, timing...
inline IConsole* Console = nullptr;                 // printing, console vars, console commands...
inline IFileSystem* FileSystem = nullptr;           // files, directories
inline IMaterialManager* MaterialManager = nullptr; // textures, surface properties
inline IModelManager* ModelManager = nullptr;       // model mesh data, metadata
inline IPluginSystem* PluginSystem = nullptr;       // plugin libraries

// Client-specific stuff
// The serverside should never use these
inline IAudio* Audio = nullptr;           // sound sources, music, filters, reverb
inline IInput* Input = nullptr;           // keyboard & mouse input
inline IRenderFrontend* Renderer = nullptr; // rendering of 3D models, 2D surfs, text etc.

using CVar = CVarTemplate<Console>;
