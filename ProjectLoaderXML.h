#pragma once
#include "../ProjectLoader.h"
#include "EngineDependencies/rapidxml-1.13/rapidxml.hpp"
#include "../FileHandlingUtil.h"
#include "../Scene.h"
#include "../Tag.h"
#include "../IDManager.h"
#include "../Component.h"
#include "../MeshFilter.h"
#include "../MeshRenderer.h"
#include "../Material.h"

namespace origami_sheep_engine
{
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
		void loadEntityPrefab(std::map<std::string, Entity> & prefab_names_to_object, const std::string & prefab_name,
													const std::string & prefab_path, const Project & project);

	private:
		//Parse the XML file at 'path' and store the contents in 'content'
		//NOTE - contents must remain in memory while accessing doc as it used in-place parsing
		//@returns {std::unique_ptr<rapidxml::xml_document<>>} Pointer to the parsed document
		std::unique_ptr<rapidxml::xml_document<>> loadXMLFile(const std::string & path, std::string & contents);

		void parseEntity(std::vector<Entity> & entities, rapidxml::xml_node<> * entity_node, std::map<std::string, Entity> & prefab_names_to_object, const Project & project);
		void parseTag(std::vector<Tag> & tags, rapidxml::xml_node<> * tag_node);
		void parseResources(rapidxml::xml_node<> * resources_node, std::map<std::string, Entity> & prefab_names_to_object, const Project & project);

		const std::string file_extension = ".xml";
	};
}

