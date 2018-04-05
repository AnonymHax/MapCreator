#include "ToolWidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include "SYSTEM/Public.h"

#define LAYOUT_SPACING 5

ToolWidget::ToolWidget(QWidget *parent)
    : QWidget(parent)
    , m_group(NULL)
    , m_move(NULL)
    , m_place(NULL)
    , m_delete(NULL)
    , m_light(NULL)
    , m_height(NULL)
    , m_wall(NULL)
    , m_mainLayout(NULL)
    , m_currentLayout(NULL)
    , m_row(0)
    , m_datas()
{
    setAttribute(Qt::WA_DeleteOnClose);
    buildGUI();
}

void ToolWidget::buildGUI()
{
    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setSpacing(LAYOUT_SPACING);

    QWidget *widget = new QWidget(this);
    widget->setLayout(m_mainLayout);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(widget, 0, Qt::AlignTop);

    m_group = new QButtonGroup(this);

    m_move = new QToolButton(this);
    m_move->setIcon(QIcon(":/icons/move.png"));
    connect(m_move, SIGNAL(clicked()), this, SLOT(move()));
    addButton(m_move, TOOL_MOVE);

    m_place = new QToolButton(this);
    m_place->setIcon(QIcon(":/icons/icon_place.png"));
    connect(m_place, SIGNAL(clicked()), this, SLOT(place()));
    addButton(m_place, TOOL_PLACE);

    m_delete = new QToolButton(this);
    m_delete->setIcon(QIcon(":/icons/icon_delete.png"));
    connect(m_delete, SIGNAL(clicked()), this, SLOT(del()));
    addButton(m_delete, TOOL_DELETE);

    m_light = new QToolButton(this);
    m_light->setIcon(QIcon(":/icons/icon_light.png"));
    connect(m_light, SIGNAL(clicked()), this, SLOT(light()));
    addButton(m_light, TOOL_LIGHT);

    m_height = new QToolButton(this);
    m_height->setIcon(QIcon(":/icons/icon_height.png"));
    connect(m_height, SIGNAL(clicked()), this, SLOT(height()));
    addButton(m_height, TOOL_HEIGHT);

    m_wall = new QToolButton(this);
    m_wall->setIcon(QIcon(":/icons/icon_collision.png"));
    connect(m_wall, SIGNAL(clicked()), this, SLOT(wall()));
    addButton(m_wall, TOOL_COLLISION);

    m_layer = new QToolButton(this);
    m_layer->setIcon(QIcon(":/icons/icon_layer.png"));
    connect(m_layer, SIGNAL(clicked()), this, SLOT(layer()));
    addButton(m_layer, TOOL_LAYER);

    m_currentLayout->addStretch();

    setLayout(layout);
}

void ToolWidget::addButton(QToolButton *button, TOOL tool)
{
    if(m_group->buttons().count()%3 == 0)
    {
        if(m_currentLayout != NULL)
            m_currentLayout->addStretch();
        m_currentLayout = new QHBoxLayout;
        m_currentLayout->setSpacing(LAYOUT_SPACING);
        m_mainLayout->addLayout(m_currentLayout);
        m_row++;
    }
    button->setMinimumSize(50,50);
    button->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    button->setIconSize(QSize(35,35));
    button->setCheckable(true);
    m_datas.insert(tool, button);
    m_group->addButton(button);
    m_currentLayout->addWidget(button, 0, Qt::AlignLeft);
}


void ToolWidget::move()
{
    emit toolSelected(TOOL_MOVE);
}

void ToolWidget::place()
{
    emit toolSelected(TOOL_PLACE);
}

void ToolWidget::del()
{
    emit toolSelected(TOOL_DELETE);
}

void ToolWidget::light()
{
    emit toolSelected(TOOL_LIGHT);
}

void ToolWidget::height()
{
    emit toolSelected(TOOL_HEIGHT);
}

void ToolWidget::wall()
{
    emit toolSelected(TOOL_COLLISION);
}

void ToolWidget::layer()
{
    emit toolSelected(TOOL_LAYER);
}

void ToolWidget::selectButton(TOOL tool)
{
    if(m_datas.contains(tool))
    {
        QToolButton *b = m_datas[tool];
        b->setChecked(true);
        emit toolSelected(tool);
    }
}
