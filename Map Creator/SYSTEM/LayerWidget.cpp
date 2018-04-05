#include "LayerWidget.h"

#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QVBoxLayout>

#define BUTTON_WIDTH 60

LayerWidget::LayerWidget(QWidget *parent)
    : m_list(NULL)
    , m_new(NULL)
    , m_del(NULL)
    , m_up(NULL)
    , m_down(NULL)
    , m_manager(NULL)
{
    buildGUI();
}

void LayerWidget::buildGUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->setSpacing(0);

    m_new = new QPushButton("Nouveau", this);
    m_new->setMaximumWidth(BUTTON_WIDTH);
    connect(m_new, SIGNAL(clicked()), this, SLOT(newLayer()));
    hLayout->addWidget(m_new);

    m_del = new QPushButton("Supprimer", this);
    m_del->setMaximumWidth(BUTTON_WIDTH);
    connect(m_del, SIGNAL(clicked()), this, SLOT(delLayer()));
    hLayout->addWidget(m_del);

    m_up = new QPushButton("Monter", this);
    m_up->setMaximumWidth(BUTTON_WIDTH);
    connect(m_up, SIGNAL(clicked()), this, SLOT(upLayer()));
    hLayout->addWidget(m_up);

    m_down = new QPushButton("Descendre", this);
    m_down->setMaximumWidth(BUTTON_WIDTH);
    connect(m_down, SIGNAL(clicked()), this, SLOT(downLayer()));
    hLayout->addWidget(m_down);

    m_list = new QListWidget(this);
    m_list->setMaximumSize(240,125);
    connect(m_list, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(layerChanged(QListWidgetItem*)));
    mainLayout->addLayout(hLayout);
    mainLayout->setAlignment(hLayout, Qt::AlignTop);
    mainLayout->addWidget(m_list,1,Qt::AlignTop);

    setLayout(mainLayout);
}

void LayerWidget::setMapManager(MapManager *mapManager)
{
    m_manager = mapManager;
    populate();
}

void LayerWidget::populate()
{
    m_list->clear();

    const QList<GameLayer*>* layers = m_manager->getLayersOrder();
    QList<GameLayer*>::const_iterator it = layers->begin();
    QList<GameLayer*>::const_iterator itEnd = layers->end();
    do
    {
        itEnd--;
        GameLayer *layer = *itEnd;
        QListWidgetItem *item = new QListWidgetItem(layer->getName());
        item->setData( Qt::UserRole, layer->getId());
        if(layer->isSystem())
            item->setToolTip("COUCHE SYSTEME");
        else
            item->setToolTip("NORMAL");

        item->setCheckState(layer->isVisible() ? Qt::Checked : Qt::Unchecked);
        m_list->addItem(item);
    } while(itEnd != it);
}

void LayerWidget::newLayer()
{
    if(m_manager == NULL)
        return;

    if(!m_manager->mapExist())
        return;

    int number_id = m_list->count() -1;

    bool alreadyExist;

    do{
        alreadyExist = false;

        for (int i = 0; i < m_list->count(); i++) {
            QListWidgetItem *item = m_list->item(i);
            if(item == NULL)
                return;
            if (item->data(Qt::UserRole).toInt() == number_id)
                alreadyExist = true;
        }
        if (alreadyExist)
            number_id ++;
    }
    while (alreadyExist);

    GameLayer *temp = m_manager->addLayer(number_id, "Couche n°"+toString(number_id), true, false);
    if(temp == NULL)
    {
        qDebug() << "Impossible d'ajouter le layer " << number_id << "dans "<<__FILE__<<__LINE__;
        exit(0);
    }

    populate();
    setCurrentLayer(temp->getId());
}

void LayerWidget::delLayer()
{
    if(m_manager == NULL)
        return;

    QListWidgetItem *item = m_list->currentItem();
    if(item == NULL)
        return;

    if (item->toolTip() != "COUCHE SYSTEME")
    {
        int id = item->data(Qt::UserRole).toInt();
        m_manager->removeLayer(static_cast<ID>(id));
    }

    populate();
    m_list->setCurrentRow(0);
}

void LayerWidget::upLayer()
{
    if(m_manager == NULL)
        return;

    QListWidgetItem *item = m_list->currentItem();
    if(item == NULL)
        return;

    int id = item->data(Qt::UserRole).toInt();
    m_manager->getLayerSystem()->moveUp(id);

    populate();
    setCurrentLayer(id);
}

void LayerWidget::downLayer()
{
    if(m_manager == NULL)
        return;

    QListWidgetItem *item = m_list->currentItem();
    if(item == NULL)
        return;

    int id = item->data(Qt::UserRole).toInt();
    m_manager->getLayerSystem()->moveDown(id);

    populate();
    setCurrentLayer(id);
}

void LayerWidget::setCurrentLayer(int idLayer)
{
    size_t count = m_list->count();
    for(size_t i = 0 ; i < count ; ++i)
    {
        QListWidgetItem *item = m_list->item(i);
        if(item == NULL)
            continue;
        if(item->data(Qt::UserRole).toInt() == idLayer)
        {
            m_list->setCurrentRow(i);
            emit layerSelected(item->data(Qt::UserRole).toInt(), item->checkState() == Qt::Checked);
            return;
        }
    }

}

void LayerWidget::layerChanged(int row)
{
    QListWidgetItem *item = m_list->item(row);
    if(item == NULL)
        return;

    layerChanged(item);
}

void LayerWidget::layerChanged(QListWidgetItem *item)
{
    if(item == NULL)
        return;

    int id = item->data(Qt::UserRole).toInt();
    int checkState = item->checkState();
    emit layerSelected(id, checkState == Qt::Checked);
}
