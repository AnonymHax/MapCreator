#ifndef LAYERWIDGET_H
#define LAYERWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include "MANAGERS/MapManager.h"

class LayerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LayerWidget(QWidget *parent = 0);
    
    void setMapManager(MapManager *mapManager);
    void setCurrentLayer(int idLayer);

    void populate();

protected:
    void buildGUI();

public slots:
    void newLayer();
    void delLayer();
    void upLayer();
    void downLayer();
    void layerChanged(QListWidgetItem *item);
    void layerChanged(int row);

signals:
    void layerSelected(int, bool);

private:
    QListWidget *m_list;

    QPushButton *m_new;
    QPushButton *m_del;
    QPushButton *m_up;
    QPushButton *m_down;

    MapManager *m_manager;
    
};

#endif // LAYERWIDGET_H
