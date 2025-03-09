#include "Application.h"
#include "MainWindow.h"

int main(int argc, char** argv) {
    Application app(argc, argv);
    app.setStyle("Fusion");

    MainWindow window;
    window.show();

    return app.exec();
}
