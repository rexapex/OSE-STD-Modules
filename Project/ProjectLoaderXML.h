#pragma once
#include "OSE-V2-STD-Modules/EngineDependencies/rapidxml-1.13/rapidxml.hpp"
#include "OSE-Core/Project/ProjectLoader.h"
#include "OSE-Core/Resources/FileHandlingUtil.h"
#include "OSE-Core/Game/Scene.h"
#include "OSE-Core/Game/Tag.h"
#include "OSE-Core/Game/IDManager.h"
#include "OSE-Core/Entity/Component.h"
#include "OSE-Core/Entity/MeshFilter.h"
#include "OSE-Core/Entity/MeshRenderer.h"
#include "OSE-Core/Entity/Material.h"
#include <functional>

namespace ose::project
{
	using namespace ose::game;

	//Loads projects from xml text files
	class ProjectLoaderXML : public ProjectLoader
	{
	public:
		ProjectLoaderXML();
		~ProjectLoaderXML() noexcept;

		std::unique_ptr<Project> loadProject(const std::string & project_name);
		std::unique_ptr<ProjectInfo> loadProjectManifest(const std::string & project_path);
		std::unique_ptr<std::map<std::string, std::string>> loadSceneDeclerations(const std::string & project_path);
		std::unique_ptr<Tag> loadTagDefinitions(const std::string & project_path);
		void loadProjectSettings(const std::string & project_path);
		void loadInputSettings(const std::string & project_path);
		std::unique_ptr<Scene> loadScene(const Project & project, const std::string & scene_name);
		std::unique_ptr<Entity> loadEntityPrefab(const std::string & prefab_path, const Project & project);

	private:
		//Parse the XML file at 'path' and store the contents in 'content'
		//NOTE - contents must remain in memory while accessing doc as it used in-place parsing
		//@returns {std::unique_ptr<rapidxml::xml_document<>>} Pointer to the parsed document
		std::unique_ptr<rapidxml::xml_document<>> loadXMLFile(const std::string & path, std::string & contents);

		std::unique_ptr<Entity> parseEntity(rapidxml::xml_node<> * entity_node,
				std::unordered_map<std::string, std::string> & aliases, const Project & project);
		
		void parseTag(std::vector<Tag> & tags, rapidxml::xml_node<> * tag_node);
		void parseResources(rapidxml::xml_node<> * resources_node, std::unordered_map<std::string, std::string> & aliases, const Project & project);

		const std::string file_extension = ".xml";
	};
}

