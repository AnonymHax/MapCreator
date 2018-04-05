#ifndef TILESWIDGET_H
#define TILESWIDGET_H

#include <QWidget>

class QListWidget;
class QModelIndex;
class QListWidgetItem;

class TilesWidget : public QWidget
{
    Q_OBJECT
public:
    TilesWidget(QWidget *parent = 0);

public slots:
    void update();

private slots:
    void currentItemChanged(QListWidgetItem*);

signals:
    void tileSelected(int);

protected:
    void buildGUI();

    void populate();

private:
    QListWidget *m_list;
};

#endif // TILESWIDGET_H
