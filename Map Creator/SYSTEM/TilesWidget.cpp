#include "TilesWidget.h"

#include <QListWidget>
#include <QListWidgetItem>
#include "MANAGERS/TileManager.h"
#include "SYSTEM/Public.h"

TilesWidget::TilesWidget(QWidget *parent)
    : QWidget(parent)
    , m_list(NULL)
{
    setAttribute(Qt::WA_DeleteOnClose);
    buildGUI();
}

void TilesWidget::buildGUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    m_list = new QListWidget(this);
    m_list->setMinimumWidth(150);
    mainLayout->addWidget(m_list);
    m_list->setViewMode(QListView::IconMode);
    connect(m_list, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(currentItemChanged(QListWidgetItem*)));

    populate();

    setLayout(mainLayout);
}

void TilesWidget::update()
{
    populate();
}

void TilesWidget::populate()
{
    m_list->clear();
    foreach (const Tile *tile,*TileManagerSingleton::getInstance()->data())
    {
        if(tile == NULL)
            continue;

        QListWidgetItem* item = new QListWidgetItem();

        const TileAnimationFrameData *tafd = tile->getAnimationFrame(DEFAULT_ANIMATION, 0);
        if(tafd != NULL)
        {
            sf::Image img = tafd->getTexture()->copyToImage();

            const unsigned char *data = img.getPixelsPtr();
            int width = tafd->getTexture()->getSize().x;
            int height = tafd->getTexture()->getSize().y;
            int length = width*height*4;

            int x = 0;
            int y = 0;

            QImage image(width, height, QImage::Format_ARGB32 );
            assert( length % 4 == 0 );
            for ( int i = 0; i < length / 4; ++i )
            {
                int index = i * 4;
                QRgb argb = qRgba( data[index],       //rouge
                                   data[index + 1],   //vert
                                   data[index + 2],   //bleu
                                   data[index + 3] ); //alpha
                image.setPixel(x, y, argb );

                if (x == width-1)
                {
                    x = 0;
                    y++;
                }

                else
                    x++;
            }
            item->setIcon(QIcon(QPixmap::fromImage(image)));
        }

        item->setText(tile->getName());
        item->setData(Qt::UserRole, tile->getId());

        m_list->addItem(item);
    }
}

void TilesWidget::currentItemChanged(QListWidgetItem* item)
{
    if(item == NULL)
        return;
    else
        emit tileSelected(item->data(Qt::UserRole).toInt());
}
