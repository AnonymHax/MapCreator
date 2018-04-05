#include "TileEditor.h"
#include "ui_TileEditor.h"
#include "MANAGERS/TileManager.h"

#include <QFile>

TileEditor::TileEditor(BaseEngine *engine, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TileEditor),
    m_tile(NULL)
    //m_cube(NULL)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    m_animationsModel = new QStandardItemModel;
    ui->animation_manager->setModel(m_animationsModel);
    ui->animation_manager->setHeaderHidden(true);

    connect (ui->animation_manager, SIGNAL(entered(QModelIndex)), this, SLOT(itemSelected(QModelIndex)));
    connect (ui->animation_manager, SIGNAL(pressed(QModelIndex)), this, SLOT(itemSelected(QModelIndex)));

    m_currentFrame = 0;

    m_tileAnimationData = NULL;
    m_tileAnimationFrameData = NULL;

    m_mapSize.x = 1;
    m_mapSize.y = 1;

    m_tileName = "";

    m_actualEngine = engine;

    m_render = new Render (this, QPoint(ui->frame->mapToGlobal(QPoint(0,0)).rx(), ui->frame->mapToGlobal(QPoint(0,0)).ry()+55), QSize(ui->frame->width(), ui->frame->height()));
    m_map = new MapManager ();
    m_mapRender = new MapRender (m_map, sf::Vector2i(ui->frame->width(), ui->frame->height()));

    m_render->add(m_mapRender);

    m_mapRender->showGrid(false);

    m_map->addLayer(-1, "X", true, true);
    m_map->addLayer(0,"Couche Principale");

    on_newTile_triggered();
    m_added = false;
}


TileEditor::~TileEditor()
{
    delete ui;
    delete m_mapRender;
    delete m_render;
    delete m_map;

    if (m_tile != NULL && !m_added)
        TileManagerSingleton::getInstance()->remove(m_tile->getId());
}


void TileEditor::keyPressEvent ( QKeyEvent * event )
{
    event->accept();

    // Zoomer et Dezoomer
    if(event->key() == Qt::Key_Plus)
        m_mapRender->setZoom (m_mapRender->getZoom()+POSITIVE_ZOOM,ZOOM_TIME);
    if(event->key() == Qt::Key_Minus)
        m_mapRender->setZoom (m_mapRender->getZoom()+NEGATIVE_ZOOM,ZOOM_TIME);
}

void TileEditor::wheelEvent(QWheelEvent * event)
{
    event->accept();
    if(event->delta() > -1)
        m_mapRender->setZoom (m_mapRender->getZoom()+POSITIVE_ZOOM);
    else
        m_mapRender->setZoom (m_mapRender->getZoom()+NEGATIVE_ZOOM);
}

bool TileEditor::loadTiles(QString animation_name, QStringList textures_paths)
{
    if(m_tile == NULL)
        return false;

    m_tile->addAnimation(animation_name);
    m_tileAnimationData = m_tile->getAnimation(animation_name);
    if(m_tileAnimationData == NULL)
        return false;


    foreach (QString texture_path, textures_paths)
    {
        sf::Texture *texture = new sf::Texture();
        texture->loadFromFile(texture_path.toStdString());

        m_tileAnimationData->addFrame(texture);
    }

    if (ui->tile_name->text() == "")
    {
        QString temp;
        bool foundExtension = false;

        for (int i = textures_paths.first().size()-1; i != -1; i--)
        {
            if (textures_paths.first().at(i).toAscii() == '\\')
                break;

            if (textures_paths.first().at(i).toAscii() == '.')
                foundExtension = true;

            else if (foundExtension)
                temp += textures_paths.first().at(i);
        }


        m_tileName.clear();
        for (int i = temp.size()-1; i != -1 ; i--)
            m_tileName += temp.at(i).toAscii();

        ui->tile_name->setText(m_tileName);
    }

    m_tileAnimationFrameData = m_tileAnimationData->getFrame(m_currentFrame);
    return true;
}


void TileEditor::on_tile_secondFloor_valueChanged (int secondFloor)
{
    //TileAnimationFrameData* tafd = m_tile->getAnimationFrame(m_currentAnimation, m_currentFrame);
    if(m_tileAnimationFrameData == NULL)
        return;

    m_tileAnimationFrameData->setPosition(sf::Vector2i(secondFloor, m_tileAnimationFrameData->getPosition().y));
    m_map->getCell(0,0)->cell(0)->update();
}

void TileEditor::on_tile_secondSide_valueChanged (int secondSide)
{
    //TileAnimationFrameData* tafd = m_tile->getAnimationFrame(m_currentAnimation, m_currentFrame);
    if(m_tileAnimationFrameData == NULL)
        return;

    m_tileAnimationFrameData->setPosition(sf::Vector2i(m_tileAnimationFrameData->getPosition().x, secondSide));
    m_map->getCell(0,0)->cell(0)->update();
}

void TileEditor::on_tile_add_clicked ()
{
    if (ui->tile_name->text() != "")
    {
        m_tile->setName(m_tileName);
        emit tileAdded ();
        m_added = true;
        close();
    }

    else
    {
        QMessageBox::critical(this, "Nom invalide","Veuillez nommer le tile, le nom de doit pas etre deja utulisé");
        ui->tile_name->setText(m_tileName);
        ui->tile_name->setFocus();
        ui->tile_name->selectAll();
    }
}


void TileEditor::on_tile_scalex_valueChanged (double x)
{
    //TileAnimationFrameData* tafd = m_tile->getAnimationFrame(m_currentAnimation, m_currentFrame);
    if(m_tileAnimationFrameData == NULL)
        return;

    m_tileAnimationFrameData->setScale(sf::Vector2f(x, m_tileAnimationFrameData->getScale().y));
    m_map->getCell(0,0)->cell(0)->update();
}

void TileEditor::on_tile_scaley_valueChanged (double y)
{
    //TileAnimationFrameData* tafd = m_tile->getAnimationFrame(m_currentAnimation, m_currentFrame);
    if(m_tileAnimationFrameData == NULL)
        return;

    m_tileAnimationFrameData->setScale(sf::Vector2f(m_tileAnimationFrameData->getScale().x, y));
    m_map->getCell(0,0)->cell(0)->update();
}

void TileEditor::on_frame_previous_clicked ()
{
    //TileAnimationData *tad = m_tile->getAnimation(m_currentAnimation);
    if(m_tileAnimationData ==NULL)
        return;

    if (ui->frame_number->value()-1 > 0)
    {
        m_currentFrame -= 1;
        ui->frame_number->display( ui->frame_number->value()-1);
    }

    else
    {
        m_currentFrame = m_tileAnimationData->getNbFrame()-1;
        ui->frame_number->display(m_currentFrame+1);
    }

    m_tileAnimationFrameData = m_tileAnimationData->getFrame(m_currentFrame);
    if(m_tileAnimationFrameData == NULL)
        return;

    m_map->getCell(0,0)->cell(0)->setFrame(m_currentFrame);

    ui->tile_scalex->setValue(m_tileAnimationFrameData->getScale().x);
    ui->tile_scaley->setValue(m_tileAnimationFrameData->getScale().y);
    ui->tile_secondFloor->setValue(m_tileAnimationFrameData->getPosition().x);
    ui->tile_secondSide->setValue(m_tileAnimationFrameData->getPosition().y);
    ui->frame_interval->setValue(m_tileAnimationFrameData->getFrameInterval());
    ui->frame_restart->setValue(m_tileAnimationData->getFrameRestart());

    m_map->getCell(0,0)->cell(0)->update();
}

void TileEditor::on_frame_next_clicked ()
{
    if(m_tileAnimationData ==NULL)
        return;

    if (ui->frame_number->value()+1 <= m_tileAnimationData->getNbFrame())
    {
        m_currentFrame += 1;
        ui->frame_number->display( ui->frame_number->value()+1);
    }

    else
    {
        m_currentFrame = 0;
        ui->frame_number->display(1);
    }

    m_tileAnimationFrameData = m_tileAnimationData->getFrame(m_currentFrame);

    m_map->getCell(0,0)->cell(0)->setFrame(m_currentFrame);

    if(m_tileAnimationFrameData == NULL)
        return;

    ui->tile_scalex->setValue(m_tileAnimationFrameData->getScale().x);
    ui->tile_scaley->setValue(m_tileAnimationFrameData->getScale().y);
    ui->tile_secondFloor->setValue(m_tileAnimationFrameData->getPosition().x);
    ui->tile_secondSide->setValue(m_tileAnimationFrameData->getPosition().y);
    ui->frame_interval->setValue(m_tileAnimationFrameData->getFrameInterval());
    ui->frame_restart->setValue(m_tileAnimationData->getFrameRestart());

    m_map->getCell(0,0)->cell(0)->update();
}

void TileEditor::on_tile_play_clicked ()

{
    if (ui->tile_play->text() == "Rendu")
    {
        ui->frame_box->setEnabled(false);
        ui->tile_infos->setEnabled(false);
        ui->animation_manager->setEnabled(false);
        if (ui->cube_show->isChecked())
        {ui->cube_show->setChecked(false); on_cube_show_clicked();}
        ui->cube_box->setEnabled(false);
        ui->tile_play->setText("Stop");
        GameLayer* layer = m_map->getLayer(-1);
        if(layer == NULL)
        {
            qDebug() << __FILE__ << __LINE__ << ", Layer -1 n'existe pas.";
            return;
        }
        layer->setVisible(false);


        m_map->getCell(0,0)->cell(0)->setFrame(0);
        m_map->getCell(0,0)->cell(0)->startAnimation();


    }

    else
    {
        ui->frame_box->setEnabled(true);
        ui->tile_infos->setEnabled(true);
        ui->tile_play->setText("Rendu");
        ui->animation_manager->setEnabled(true);
        ui->cube_box->setEnabled(true);

        GameLayer* layer = m_map->getLayer(-1);
        if(layer == NULL)
            qDebug() << __FILE__ << __LINE__ << ", Layer -1 n'existe pas.";
        else
            layer->setVisible(true);

        m_map->getCell(0,0)->cell(0)->setFrame(m_currentAnimation, m_currentFrame);
    }
}

void TileEditor::on_frame_interval_valueChanged (int frameInterval)
{
    //TileAnimationFrameData *tafd = m_tile->getAnimationFrame(m_currentAnimation, m_currentFrame);
    if(m_tileAnimationFrameData == NULL)
        return;

    m_tileAnimationFrameData->setFrameInterval(frameInterval);
}

void TileEditor::on_frame_restart_valueChanged (int frameRestart)
{
    //TileAnimationData *tad = m_tile->getAnimation(m_currentAnimation);
    if(m_tileAnimationData == NULL)
        return;

    m_tileAnimationData->setFrameRestart(frameRestart);
}

void TileEditor::on_check_restart_stateChanged (int checked)
{
    if (checked == Qt::Checked)
    {
        on_frame_restart_valueChanged (ui->frame_restart->value());
        ui->frame_restart->setEnabled(true);
    }

    else if (checked == Qt::Unchecked)

    {
        on_frame_restart_valueChanged (NO_RESTART);
        ui->frame_restart->setEnabled(false);
    }
}

void TileEditor::on_newTile_triggered()
{
    m_animationsModel->clear();
    m_currentFrame = 0;
    m_currentAnimation = DEFAULT_ANIMATION;

    if (m_tile != NULL && !m_added)
        TileManagerSingleton::getInstance()->remove(m_tile->getId());

    m_tile = TileManagerSingleton::getInstance()->create();

    disableUi();

    m_map->createMap(m_mapSize);

    Cell* cell = m_map->getCell(0,0)->cell(0);
    cell->addEffect(EffectManagerSingleton::getInstance()->create(Effect::CUBE)->getId());

    m_tileAnimationData = m_tile->getAnimation(m_currentAnimation);
    if(m_tileAnimationData == NULL)
        return;
    m_tileAnimationFrameData = m_tileAnimationData->getFrame(m_currentFrame);
}

void TileEditor::resetUi()

{
    ui->tile_infos->setEnabled(true);
    activateUi();

    ui->frame_interval->setValue(10);
    ui->frame_number->display(1);
    ui->frame_restart->setValue(0);
    ui->tile_name->setText("");
    ui->tile_scalex->setValue(1);
    ui->tile_scaley->setValue(1);
    ui->check_restart->setChecked(true);
    ui->tile_secondFloor->setValue(0);
    ui->tile_secondSide->setValue(0);
}

void TileEditor::disableUi()

{
    ui->tile_infos->setEnabled(false);
    ui->frame_box->setEnabled(false);
    ui->tile_play->setEnabled(false);
    ui->tile_add->setEnabled(false);
}

void TileEditor::activateUi()

{
    ui->tile_infos->setEnabled(true);
    ui->frame_box->setEnabled(true);

    ui->tile_play->setEnabled(true);
    ui->tile_add->setEnabled(true);
}

void TileEditor::on_newAnimation_triggered()
{
    QStringList paths = QFileDialog::getOpenFileNames(this,"Selectionez les images", "", IMAGE_FORMATS);

    if (!paths.isEmpty())
    {
        m_toAddPaths = paths;
        QDialog *createAnimation = new QDialog(this);
        createAnimation->setWindowTitle("Definir le nom de l'animation");
        QVBoxLayout *layout = new QVBoxLayout();


        QLabel *label_name = new QLabel ("Nom de l'animation");
        QLineEdit *line_name = new QLineEdit (DEFAULT_ANIMATION);
        m_toAddName = line_name->text();


        QPushButton *button_confirm = new QPushButton ("Ok");


        layout->addWidget(label_name,0,Qt::AlignCenter);
        layout->addWidget(line_name);
        layout->addSpacing(15);
        layout->addWidget(button_confirm);

        createAnimation->setLayout(layout);
        createAnimation->show();

        connect (line_name, SIGNAL(textChanged(QString)), this, SLOT(setAnimName(QString)));
        connect (button_confirm, SIGNAL(clicked()), this, SLOT (animationConfirm()));
        connect (button_confirm, SIGNAL(clicked()), createAnimation, SLOT(close()));
    }
}


void TileEditor::addAnimation (const QString &name, const QStringList &paths)
{
    bool alreadyExist = false;

    for (int i = 0; i != m_animationsModel->rowCount(); i++)
    {
        if (name ==  m_animationsModel->index(i,0).data().toString())
            alreadyExist = true;
    }

    if (!alreadyExist)
    {
        QStandardItem *item = new QStandardItem(name);
        item->setData(name,1);
        m_currentAnimation = name;
        m_animationsModel->appendRow(item);

        for (int i = 0; i != paths.size();i++)
        {
            QStandardItem *item2 = new QStandardItem("image_"+toString(i+1));
            item2->setEditable(false);
            item->appendRow(item2);
        }

        resetUi();
        loadTiles(name, paths);
        m_map->getCell(0,0)->cell(0)->setId(m_tile->getId(),false);
    }
}

void TileEditor::setAnimName (QString name)
{
    m_toAddName = name;
}

void TileEditor::animationConfirm ()
{
    addAnimation(m_toAddName,m_toAddPaths);
    m_map->getCell(0,0)->cell(0)->update();
}

void TileEditor::itemSelected(const QModelIndex &index)
{
    if (index.internalId() != m_animationsModel->index(0,0).internalId())
    {
        m_currentAnimation = index.parent().data(1).toString();
        m_currentFrame = index.row();

        ui->frame_number->display(m_currentFrame+1);

        m_map->getCell(0,0)->cell(0)->setFrame(m_currentAnimation, m_currentFrame,true);

        TileAnimationData *tad = m_tile->getAnimation(m_currentAnimation);
        if(tad == NULL)
            return;

        TileAnimationFrameData *tafd = tad->getFrame(m_currentFrame);
        if(tafd == NULL)
            return;

        ui->tile_scalex->setValue(tafd->getScale().x);
        ui->tile_scaley->setValue(tafd->getScale().y);
        ui->tile_secondFloor->setValue(tafd->getPosition().x);
        ui->tile_secondSide->setValue(tafd->getPosition().y);
        ui->frame_interval->setValue(tafd->getFrameInterval());
        ui->frame_restart->setValue(tad->getFrameRestart());

        m_map->getCell(0,0)->cell(0)->update();
    }

    else
        m_currentAnimation = index.data().toString();

    m_tileAnimationData = m_tile->getAnimation(m_currentAnimation);
    m_tileAnimationFrameData = m_tileAnimationData->getFrame(m_currentFrame);
}


void TileEditor::on_cube_show_clicked()
{
    m_map->getCell(0,0)->cell(0)->setVisibleEffect(ui->cube_show->checkState());
}

void TileEditor::on_cube_inverse_clicked()
{
    if (ui->cube_inverse->checkState())
    {
        m_map->getLayerSystem()->moveDown(-1);
    }

    else
    {
        m_map->getLayerSystem()->moveUp(-1);
    }
}

