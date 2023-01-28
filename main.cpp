#include <QApplication>
#include <QFile>
#include <QString>
#include "View/MainWindow.h"
#include "Team/Team.h"

int main(int argc, char* argv[]) {
    srand(time(nullptr));

    Team ally_team;
    Team enemy_team;

    QFile file("style.qss");
    file.open(QFile::ReadOnly);
    QString style=file.readAll();

    QApplication app(argc, argv);
    app.setStyleSheet(style);

    MainWindow main_window(ally_team, enemy_team);
    main_window.resize(1020, 680);
    main_window.show();
    return app.exec();
}