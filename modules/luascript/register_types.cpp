/*************************************************/
/*  register_script_types.cpp                    */
/*************************************************/
/*            This file is part of:              */
/*                GODOT ENGINE                   */
/*************************************************/
/*       Source code within this file is:        */
/*  (c) 2007-2010 Juan Linietsky, Ariel Manzur   */
/*             All Rights Reserved.              */
/*************************************************/

#include "register_types.h"

#include "lua_script.h"
#include "io/resource_loader.h"
#include "os/file_access.h"


LuaScriptLanguage *script_language_lua=NULL;
ResourceFormatLoaderLuaScript *resource_loader_lua=NULL;
ResourceFormatSaverLuaScript *resource_saver_lua=NULL;

#ifdef TOOLS_ENABLED

#include "tools/editor/editor_import_export.h"
//#include "gd_tokenizer.h"
#include "tools/editor/editor_node.h"

class EditorExportLuaScript : public EditorExportPlugin {

	OBJ_TYPE(EditorExportLuaScript,EditorExportPlugin);

public:

	virtual Vector<uint8_t> custom_export(String& p_path,const Ref<EditorExportPlatform> &p_platform) {
		//compile lua script to bytecode
		if (p_path.ends_with(".lua")) {
//			Vector<uint8_t> file = FileAccess::get_file_as_array(p_path);
//			if (file.empty())
//				return file;
//			String txt;
//			txt.parse_utf8((const char*)file.ptr(),file.size());
//			file = GDTokenizerBuffer::parse_code_string(txt);
//			if (!file.empty()) {
//				print_line("PREV: "+p_path);
//				p_path=p_path.basename()+".gdc";
//				print_line("NOW: "+p_path);
//				return file;
//			}
//
		}

		return Vector<uint8_t>();
	}


	EditorExportLuaScript(){}

};

static void register_editor_plugin() {

	Ref<EditorExportLuaScript> elua = memnew( EditorExportLuaScript );
	EditorImportExport::get_singleton()->add_export_plugin(elua);
}


#endif

void register_luascript_types() {

	script_language_lua=memnew( LuaScriptLanguage );
	script_language_lua->init();
	ScriptServer::register_language(script_language_lua);
	ObjectTypeDB::register_type<LuaScript>();
	resource_loader_lua=memnew( ResourceFormatLoaderLuaScript );
	ResourceLoader::add_resource_format_loader(resource_loader_lua);
	resource_saver_lua=memnew( ResourceFormatSaverLuaScript );
	ResourceSaver::add_resource_format_saver(resource_saver_lua);

#ifdef TOOLS_ENABLED

	EditorNode::add_init_callback(register_editor_plugin);
#endif

}
void unregister_luascript_types() {
	if (script_language_lua)
		memdelete( script_language_lua );
	if (resource_loader_lua)
		memdelete( resource_loader_lua );
	if (resource_saver_lua)
		memdelete( resource_saver_lua );
}
