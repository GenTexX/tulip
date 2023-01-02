#pragma once

#include <application\application.h>
#include <graphicsapi\gAPI.h>
#include <logging\logger.h>

#include <engine.h>

#include <GL\glew.h>

extern tulip::Ref<tulip::Application> getApp();

int main(int argc, char* argv[]) {

	tulip::ScriptEngine::init();

	tulip::Logger::init();
	TULIP_CORE_TRACE("Initialized Tulip-Logger!");
	auto app =  getApp();
	app->genWindow();
	tulip::GraphicsAPI::init();
	app->init();
	TULIP_CORE_TRACE("Application initialized!");
	app->postInit();
	
	TULIP_CORE_TRACE("Starting Application now...");
	app->run();
	TULIP_CORE_TRACE("Application finished!");

	return 0;

}