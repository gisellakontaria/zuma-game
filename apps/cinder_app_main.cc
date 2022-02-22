//
// Created by Gisella Kontaria on 20/04/21.
//

#include "graphics/zuma_simulation_app.h"

using zuma::ZumaApp;

void prepareSettings(ZumaApp::Settings* settings) {
    settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(ZumaApp, ci::app::RendererGl, prepareSettings);
