#ifndef GOTOWIDGET_H
#define GOTOWIDGET_H

#include <QDialog>
#include "MANAGERS/MapManager.h"

class GoToWidget : public QDialog
{
    Q_OBJECT
public:
    GoToWidget(MapManager *mapManager, QSize *position, QWidget *parent);

protected:
    void buildGUI();

private slots:
    void xChanged(int);
    void yChanged(int);

private:
    QSize *m_position;
    MapManager *m_mapManager;
};

#endif // GOTOWIDGET_H
