#include "stdafx.h"
#include "ProjectLoaderXML.h"

namespace ose::project
{
	ProjectLoaderXML::ProjectLoaderXML() : ProjectLoader()
	{

	}


	ProjectLoaderXML::~ProjectLoaderXML() noexcept
	{

	}


	std::unique_ptr<rapidxml::xml_document<>> ProjectLoaderXML::loadXMLFile(const std::string & path, std::string & contents)
	{
		//load the xml string
		try
		{
			FileHandlingUtil::loadTextFile(path, contents);
		}
		catch(const std::exception & e)
		{
			//error occurred, therefore, return an empty project info stub
			LOG("FileHandlingUtil::load_text_file -> " << e.what());
			throw e;
		}

		//load the xml dom tree
		using namespace rapidxml;
		std::unique_ptr<xml_document<>> doc = std::make_unique<xml_document<>>();
		char * c_str = const_cast<char *>(contents.c_str());
		doc->parse<0>(c_str);

		return doc;
	}


	std::unique_ptr<Project> ProjectLoaderXML::loadProject(const std::string & project_name)
	{
		std::string home_dir;
		FileHandlingUtil::getHomeDirectory(home_dir);

		//TODO - FIND DOCUMENT DIRECTORY FOR MAC & LINUX - DONE - NEEDS TESTING
		//TODO - CREATE DIRECTORIES IF THEY DON'T EXIST  - DONE - NEEDS TESTING
		std::string project_path = home_dir + "/Origami_Sheep_Engine/Projects/" + project_name;
		FileHandlingUtil::createDirs(project_path);
		LOG("Loading Project Directory: " << project_path << std::endl);

		//first, load the manifest
		std::unique_ptr<ProjectInfo> manifest = loadProjectManifest(project_path);

		//then, load the scene declerations
		std::unique_ptr<std::map<std::string, std::string>> scene_declerations = loadSceneDeclerations(project_path);

		//then, load the tag definitions
		std::unique_ptr<Tag> root_tag = loadTagDefinitions(project_path);

		//finally, construct a new project instance
		std::unique_ptr<Project> proj = std::make_unique<Project>(project_path, *manifest, *scene_declerations);

		return proj;
	}


	std::unique_ptr<ProjectInfo> ProjectLoaderXML::loadProjectManifest(const std::string & project_path)
	{
		using namespace rapidxml;

		std::unique_ptr<xml_document<>> doc;
		std::string contents;

		try
		{
			doc = loadXMLFile(project_path + "/info.xml", contents);
		}
		catch(const std::exception & e)
		{
			ERROR_LOG(e.what());
			return std::make_unique<ProjectInfo>(std::move(ProjectInfo {"UNKNOWN", "UNKNOWN", "UNKNOWN", "UNKNOWN", "UNKNOWN"}));
		}

		DEBUG_LOG("**********  Project Manifest  **********");

		//parse the xml
		//valid project manifest file should contain: name, version, date_created, date_modified
		xml_node<> * name_node = doc->first_node("name");
		std::string name = (name_node ? name_node->value() : "UNKNOWN");
		DEBUG_LOG("name: " << name);

		xml_node<> * engine_version_node = doc->first_node("engine_version");
		std::string engine_version = (engine_version_node ? engine_version_node->value() : "UNKNOWN");
		DEBUG_LOG("engine_version: " << engine_version);

		xml_node<> * game_version_node = doc->first_node("game_version");
		std::string game_version = (game_version_node ? game_version_node->value() : "UNKNOWN");
		DEBUG_LOG("game_version: " << game_version);

		xml_node<> * date_created_node = doc->first_node("date_created");
		std::string date_created = (date_created_node ? date_created_node->value() : "UNKNOWN");
		DEBUG_LOG("date_created: " << date_created);

		xml_node<> * date_modified_node = doc->first_node("date_modified");
		std::string date_modified = (date_modified_node ? date_modified_node->value() : "UNKNOWN");
		DEBUG_LOG("date_modified: " << date_modified);

		DEBUG_LOG("");

		//construct and return a new ProjectInfo instance
		return std::make_unique<ProjectInfo>(std::move(ProjectInfo {name, engine_version, game_version, date_created, date_modified}));
	}



	std::unique_ptr<std::map<std::string, std::string>> ProjectLoaderXML::loadSceneDeclerations(const std::string & project_path)
	{
		using namespace rapidxml;

		std::unique_ptr<std::map<std::string, std::string>> name_to_path_map = std::make_unique<std::map<std::string, std::string>>();
		std::unique_ptr<xml_document<>> doc;
		std::string contents;
		
		try
		{
			doc = loadXMLFile(project_path + "/scene_declerations.xml", contents);
		}
		catch(const std::exception & e)
		{
			ERROR_LOG(e.what());
			return name_to_path_map;
		}

		DEBUG_LOG("**********  Scene Declerations  **********");

		for(xml_node<> * scene_node = doc->first_node("scene"); scene_node; scene_node = scene_node->next_sibling("scene"))
		{
			//for each scene decleration, add an entry to the map
			xml_attribute<> * name_attrib = scene_node->first_attribute("name");
			xml_attribute<> * path_attrib = scene_node->first_attribute("path");

			if(name_attrib && path_attrib)
			{
				//map name to path
				name_to_path_map->insert({name_attrib->value(), path_attrib->value()});
				DEBUG_LOG("Scene {name: " << name_attrib->value() << ", path: " << path_attrib->value() << "}");
			}
		}

		DEBUG_LOG("");

		return name_to_path_map;
	}


	std::unique_ptr<Tag> ProjectLoaderXML::loadTagDefinitions(const std::string & project_path)
	{
		using namespace rapidxml;

		std::unique_ptr<xml_document<>> doc;
		std::string contents;

		try
		{
			doc = loadXMLFile(project_path + "/tags.xml", contents);
		}
		catch(const std::exception & e)
		{
			ERROR_LOG(e.what());
			return nullptr;
		}

		DEBUG_LOG("**********  Tag Definitions  **********");

		auto root_tag_node = doc->first_node("tag");
		auto root_tag_name_attrib = (root_tag_node ? root_tag_node->first_attribute("name") : nullptr);

		//every tag hierarchy should be contained in a root_tag with name ""
		std::unique_ptr<Tag> root_tag = std::make_unique<Tag>(root_tag_name_attrib ? root_tag_name_attrib->value() : "");

		for(auto tag_node = doc->first_node("tag"); tag_node; tag_node = tag_node->next_sibling("tag"))
		{
			parseTag(root_tag->get_sub_tags(), tag_node);
		}

		DEBUG_LOG("");

		return root_tag;
	}


	void ProjectLoaderXML::parseTag(std::vector<Tag> & tags, rapidxml::xml_node<> * tag_node)
	{
		using namespace rapidxml;

		auto name_attrib = tag_node->first_attribute("name");
		const std::string & name = (name_attrib ? name_attrib->value() : "");

		DEBUG_LOG("tag -> name: " << name);

		//add the tags to the tags list
		tags.emplace_back(name);
		auto & new_tag = tags.back();
		auto & sub_list = new_tag.get_sub_tags();

		//parse any sub-tags
		for(auto sub_tag_node = tag_node->first_node("tag"); sub_tag_node; sub_tag_node = sub_tag_node->next_sibling("tag"))
		{
			parseTag(sub_list, sub_tag_node);
		}
	}


	void ProjectLoaderXML::loadProjectSettings(const std::string & project_path)
	{
		//TODO
	}


	void ProjectLoaderXML::loadInputSettings(const std::string & project_path)
	{
		//TODO
	}


	std::unique_ptr<Scene> ProjectLoaderXML::loadScene(const Project & project, const std::string & scene_name)
	{
		using namespace rapidxml;

		std::unique_ptr<xml_document<>> doc;
		std::string contents;
		std::string scene_path;

		// Game ensures scene exists therefore do not need to check here
		auto map = project.get_scene_names_to_path_map();
		auto pos = map.find(scene_name);
		scene_path = project.get_project_path() + "/" + pos->second + ".xml";

		try
		{
			doc = loadXMLFile(scene_path, contents);
		}
		catch(const std::exception & e)
		{
			ERROR_LOG(e.what());
			return nullptr;
		}

		auto scene_node = doc->first_node("scene");
		auto scene_name_attrib = (scene_node ? scene_node->first_attribute("name") : nullptr);
		///auto aliases_node = scene_node->first_node("aliases");
		auto entities_node = scene_node->first_node("entities");
		auto resources_node = scene_node->first_node("resources");
		///auto cached_prefabs_node = scene_node->first_node("cached_prefabs");

		std::unique_ptr<Scene> scene = std::make_unique<Scene>(scene_name_attrib ? scene_name_attrib->value() : scene_name);

		// map of aliases (lhs = alias, rhs = replacement), only applicable to current file
		std::unordered_map<std::string, std::string> aliases;
		parseResources(resources_node, aliases, project);
		
		// load the scene's entities
		if(entities_node != nullptr) {
			for(auto entity_node = entities_node->first_node("entity"); entity_node; entity_node = entity_node->next_sibling("entity"))
			{
				// create the entity then move it's pointer to the scene
				auto entity = parseEntity(entity_node, aliases, project);
				if(entity != nullptr) {
					scene->entities().add(std::move(entity));
				}
			}
		}

		// remove the temporary prefabs since they were only needed for scene loading
		project.get_prefab_manager().clearTempPrefabs();

		return scene;
	}


	std::unique_ptr<Entity> ProjectLoaderXML::loadEntityPrefab(const std::string & prefab_path, const Project & project)
	{
		using namespace rapidxml;

		std::unique_ptr<xml_document<>> doc;
		std::string contents;

		try
		{
			//load the prefab from its xml file
			doc = loadXMLFile(project.get_project_path() + "/" + prefab_path + file_extension, contents);
		}
		catch(const std::exception & e)
		{
			ERROR_LOG(e.what());
			return nullptr;
		}

		auto resources_node = doc->first_node("resources");
		auto entity_node = doc->first_node("entity");

		// map of aliases (lhs = alias, rhs = replacement), only applicable to current file
		std::unordered_map<std::string, std::string> prefab_aliases;
		parseResources(resources_node, prefab_aliases, project);

		// load the prefab entity as an Entity object
		auto output_entity = parseEntity(entity_node, prefab_aliases, project);

		// check the entity was successfully loaded and that the name is unique
		if(output_entity && !project.get_prefab_manager().doesPrefabExist(prefab_path)) {
			return std::move(output_entity);
		}

		return nullptr;
	}


	// returns: Entity object created
	std::unique_ptr<Entity> ProjectLoaderXML::parseEntity(rapidxml::xml_node<> * entity_node,
			std::unordered_map<std::string, std::string> & aliases, const Project & project)
	{
		using namespace rapidxml;

		auto name_attrib = entity_node->first_attribute("name");
		const std::string & name = (name_attrib ? name_attrib->value() : "");

		auto tag_attrib = entity_node->first_attribute("tag");
		const std::string & tag = (tag_attrib ? tag_attrib->value() : "");

		auto prefab_attrib = entity_node->first_attribute("prefab");
		const std::string & prefab_text = (prefab_attrib ? prefab_attrib->value(): "");

		// if the prefab is an alias, find it's replacement text, else use the file text
		const auto prefab_text_alias_pos = aliases.find(prefab_text);
		const std::string & prefab = prefab_text_alias_pos == aliases.end() ? prefab_text : prefab_text_alias_pos->second;

		// reference to the newly created entity (not yet created)
		std::unique_ptr<Entity> new_entity = nullptr;

		if(prefab == "")
		{
			// if no prefab is specified, then create a new entity object
			new_entity = std::make_unique<Entity>(name, tag, prefab);
		}
		else
		{
			// else, use the existing prefab object as a template
			if(project.get_prefab_manager().doesPrefabExist(prefab))
			{
				const auto & prefab_object = project.get_prefab_manager().getPrefab(prefab);
				DEBUG_LOG("Entity " << name << " extends " << prefab_object.get_name() << std::endl);
				new_entity = std::make_unique<Entity>(prefab_object);	// create object from copy of prefab
				new_entity->set_name(name);
				new_entity->set_tag(tag);
			} else {
				DEBUG_LOG("Prefab " << prefab << " does not exist");
			}
		}

		if(new_entity == nullptr) {
			LOG("ERROR: new_entity is null");
			return nullptr;
		}

		// parse the components of the new entity
		for(auto component_node = entity_node->first_node("sprite_renderer"); component_node; component_node = component_node->next_sibling("sprite_renderer"))
		{
			// has name & texture attributes
			auto name_attrib	= component_node->first_attribute("name");
			auto texture_attrib = component_node->first_attribute("texture");
			std::string name { (name_attrib ? name_attrib->value() : "") };

			// if texture is an alias, find it's replacement text, else use the file text
			std::string texture_text { (texture_attrib ? texture_attrib->value() : "") };
			const auto texture_text_alias_pos { aliases.find(texture_text) };
			const std::string & texture { texture_text_alias_pos == aliases.end() ? texture_text : texture_text_alias_pos->second };

			const Texture * tex = project.get_resource_manager().getTexture(texture);
			if(tex != nullptr) {
				new_entity->addComponent<SpriteRenderer>(name, *tex);
			} else {
				ERROR_LOG("Error: texture " << texture << " has not been loaded");
			}
		}

		// mesh components
		for(auto component_node = entity_node->first_node("mesh_filter"); component_node; component_node = component_node->next_sibling("mesh_filter"))
		{
			// has name & path attributes
			auto name_attrib = component_node->first_attribute("name");
			auto path_attrib = component_node->first_attribute("path");
		//	new_entity.get_components().emplace_back(std::make_unique<MeshFilter>((name_attrib ? name_attrib->value() : ""), (path_attrib ? path_attrib->value() : "")));
		}

		for(auto component_node = entity_node->first_node("mesh_renderer"); component_node; component_node = component_node->next_sibling("mesh_renderer"))
		{
			// has name & path attributes
			auto name_attrib = component_node->first_attribute("name");
			auto path_attrib = component_node->first_attribute("path");
		//	new_entity.get_components().emplace_back(std::make_unique<MeshRenderer>(name_attrib ? name_attrib->value() : ""));
		}

		// parse any sub-entities
		for(auto sub_entity_node = entity_node->first_node("entity"); sub_entity_node; sub_entity_node = sub_entity_node->next_sibling("entity"))
		{
			// create the sub entity then move it's pointer to the new_entity
			auto sub_entity = parseEntity(sub_entity_node, aliases, project);
			new_entity->sub_entities().add(std::move(sub_entity));
		}

		return std::move(new_entity);
	}

	void ProjectLoaderXML::parseResources(rapidxml::xml_node<> * resources_node, std::unordered_map<std::string, std::string> & aliases, const Project & project)
	{
		// parse texture nodes
		for(auto texture_node { resources_node->first_node("texture") }; texture_node; texture_node = texture_node->next_sibling("texture"))
		{
			auto const tex_alias_attrib { texture_node->first_attribute("alias") };
			auto const tex_path_attrib  { texture_node->first_attribute("path") };

			if(tex_path_attrib)
			{
				auto const tex_path { tex_path_attrib->value() };

				// if there is an alias provided, add it to the list of aliases for this file
				if(tex_alias_attrib) {
					auto const tex_alias { tex_alias_attrib->value() };
					aliases.insert({ tex_alias, tex_path });
				}

				project.get_resource_manager().addTexture(tex_path, "");	// TODO - remove name_ field from texture class
			}
		}

		// parse prefab nodes
		for(auto prefab_node { resources_node->first_node("prefab") }; prefab_node; prefab_node = prefab_node->next_sibling("prefab"))
		{
			auto const prefab_alias_attrib { prefab_node->first_attribute("alias") };
			auto const prefab_path_attrib  { prefab_node->first_attribute("path") };
			auto const prefab_is_cached	   { prefab_node->first_attribute("cached") };
			
			if(prefab_path_attrib)
			{
				auto const prefab_path  { prefab_path_attrib->value() };

				// if there is an alias provided, add it to the list of aliases for this file
				if(prefab_alias_attrib) {
					auto const prefab_alias { prefab_alias_attrib->value() };
					aliases.insert({ prefab_alias, prefab_path });
				}

				// and if so, then load the corresponding prefab file and add it to the map
				// NOTE - currently only check existence of attribute rather than whether it's value is true or false
				if(prefab_is_cached) {
					project.get_prefab_manager().addCachedPrefab(std::move(loadEntityPrefab(prefab_path, project)), prefab_path);
				} else {
					project.get_prefab_manager().addTempPrefab(std::move(loadEntityPrefab(prefab_path, project)), prefab_path);
				}
			}
		}
	}
}
