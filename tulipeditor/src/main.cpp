#include <entrypoint\entrypoint.h>

#include "application\editorApplication.h"

tulip::Ref<tulip::Application> getApp() {

	return tulip::createRef<tulip::EditorApplication>();

}
