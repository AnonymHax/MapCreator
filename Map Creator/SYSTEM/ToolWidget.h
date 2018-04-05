#ifndef TOOLWIDGET_H
#define TOOLWIDGET_H

#include <QWidget>
#include <QButtonGroup>
#include <QGroupBox>
#include <QToolButton>
#include <QHBoxLayout>
#include "SYSTEM/Public.h"

class ToolWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ToolWidget(QWidget *parent = 0);
    
    void buildGUI();

    void selectButton(TOOL tool);

private:
    void addButton(QToolButton* button, TOOL tool);

private slots:
    void move();
    void place();
    void del();
    void light();
    void height();
    void wall();
    void layer();

signals:
    void toolSelected(int);

private:
    QGroupBox *m_box;
    QButtonGroup *m_group;

    QToolButton *m_move;
    QToolButton *m_place;
    QToolButton *m_delete;
    QToolButton *m_light;
    QToolButton *m_height;
    QToolButton *m_wall;
    QToolButton *m_layer;

    QVBoxLayout *m_mainLayout;
    QHBoxLayout *m_currentLayout;

    int m_row;

    QHash<TOOL, QToolButton*> m_datas;
};

#endif // TOOLWIDGET_H
