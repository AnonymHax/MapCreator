#include "Interface.h"
#include "ui_interface.h"
#include "MANAGERS/TileManager.h"
#include "GAME_ELEMENTS/Effect.h"
#include "SYSTEM/TileEditorDialog.h"

#include <QStandardItem>

Interface::Interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Interface)
{
    m_editor = NULL;
    m_lastChoice = 0;
    m_lightColor = Qt::white;

    ui->setupUi(this);

    m_filesModel = new QFileSystemModel(this);
    m_filesModel->setNameFilterDisables(false);
    m_filesModel->setRootPath(QDir::currentPath());
    m_filesModel->setNameFilters(QStringList(TILES_FORMAT));
    m_filesModel->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);

    ui->tile_list->setModel(m_filesModel);
    ui->tile_list->setRootIndex(m_filesModel->index(QDir::currentPath()));
    ui->tile_list->header()->hide();
    ui->tile_list->setColumnHidden(1,true);
    ui->tile_list->setColumnHidden(2,true);
    ui->tile_list->setColumnHidden(3,true);

    m_tilesModel = new QStandardItemModel(this);

    ui->tile_view->setModel(m_tilesModel);
    ui->tile_view->setIconSize(QSize(100,50));
    ui->tile_view->setViewMode(QListView::IconMode);
    //  ui->tile_view->setUniformItemSizes(true);
    ui->tile_view->setSelectionRectVisible(true);
    ui->tile_view->setMovement(QListView::Static);
    ui->tile_view->setSelectionMode(QListView::SingleSelection);
    ui->tile_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->tile_view,SIGNAL(clicked(QModelIndex)), this,SLOT(tileSelected(QModelIndex)));

    connect (ui->tile_list, SIGNAL(pressed(QModelIndex)), this, SLOT(openTile(QModelIndex)));

    ui->saveMap->setEnabled(false);
    ui->sendMap->setEnabled(false);

    m_layersModel = new QStandardItemModel(this);
    connect(m_layersModel, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(ItemLayerChanged(QStandardItem*)));

    m_slayersModel = new QItemSelectionModel(m_layersModel);
    ui->layer_manager->setModel(m_layersModel);
    ui->layer_manager->setSelectionModel(m_slayersModel);
    ui->layer_manager->setHeaderHidden(true);
    connect (ui->layer_manager, SIGNAL(entered(QModelIndex)), this, SLOT(layerSelected(QModelIndex)));
    connect (ui->layer_manager, SIGNAL(pressed(QModelIndex)), this, SLOT(layerSelected(QModelIndex)));

    ui->version->setText("Map Creator - Alpha - Revision "+ toString(REVISION));

    connect (ui->light_color, SIGNAL(clicked()), this, SLOT(update_Light_Color ()));
    connect (ui->light_radius, SIGNAL(valueChanged(int)), this, SLOT (sendLightParameters()));
    connect (ui->light_intensity, SIGNAL(valueChanged(int)), this, SLOT (sendLightParameters()));
    connect (ui->light_opening_angle, SIGNAL(valueChanged(double)), this, SLOT (sendLightParameters()));
    connect (ui->light_angle, SIGNAL(valueChanged(double)), this, SLOT (sendLightParameters()));
    connect (ui->light_quality, SIGNAL(valueChanged(int)), this, SLOT (sendLightParameters()));
    connect (ui->light_color, SIGNAL(clicked()), this, SLOT (sendLightParameters()));

    m_engine = new BaseEngine (this, QPoint(ui->frame->mapToGlobal(QPoint(0,0)).rx(), ui->frame->mapToGlobal(QPoint(0,0)).ry()+55), QSize(ui->frame->width(), ui->frame->height()));
    connect(m_engine, SIGNAL(mapMoved()), this, SLOT(mapMoved()));

    //m_tiles = m_engine->getManager()->getTiles ();

    //m_engine->getManager()->loadTiles(QCoreApplication::applicationDirPath() + "/datas/packs/angelis.tile", true);
    showTiles();

    ui->statusbar->addWidget(&m_statusPosition);
    connect (&m_engine->getSelector(), SIGNAL(selectorMoved(sf::Vector2i)), this, SLOT(status_bar_position(sf::Vector2i)));
}


Interface::~Interface()

{delete ui;}

void Interface::update_Light_Color ()

{
    m_lightColor = QColorDialog::getColor(m_lightColor, this);
    QPalette palette;
    palette.setColor(QPalette::ButtonText, m_lightColor);
    ui->light_color->setStyleSheet("QPushButton { background : rgb( "+ toString(m_lightColor.red())+","+ toString(m_lightColor.green())+ ","+ toString(m_lightColor.blue())+ ") }");
}

void Interface::sendLightParameters ()

{
    m_engine->setLight(ui->light_radius->value(),ui->light_quality->value(),ui->light_intensity->value(),m_lightColor, ui->light_opening_angle->value(), ui->light_angle->value());
    ui->tool_light->setChecked(true);
    m_engine->setTool(TOOL_LIGHT);
}

void Interface::on_createMap_triggered()
{
    QDialog* confirmCreateMap = new QDialog (this);
    confirmCreateMap->setModal(true);
    confirmCreateMap->setFixedSize(300, 150);
    confirmCreateMap->setWindowTitle("Creer une nouvelle carte");

    QLabel* nameLabel = new QLabel ("Nom de la carte", confirmCreateMap);
    nameLabel->move(100,10);

    QLineEdit* nameEdit = new QLineEdit ("Nom",confirmCreateMap);
    nameEdit->move (75, 30);
    nameEdit->selectAll();

    QLabel* xLabel = new QLabel ("Largeur", confirmCreateMap);
    xLabel->move(50, 60);

    QLabel* yLabel = new QLabel ("Hauteur", confirmCreateMap);
    yLabel->move (200, 60);

    QSpinBox* xBox = new QSpinBox (confirmCreateMap);
    xBox->move(50, 80);
    xBox->setMinimum(1);
    xBox->setMaximum(100000);
    xBox->setValue(100);
    m_mapSize.x = 100;  //Je met 100 car si l'utulisateur ne change pas la valeur, m_mapSize restera a 0.

    QSpinBox* yBox = new QSpinBox (confirmCreateMap);
    yBox->move(200, 80);
    yBox->setMinimum(1);
    yBox->setMaximum(100000);
    yBox->setValue(100);
    m_mapSize.y = 100;

    QPushButton* confirmButton = new QPushButton  ("Confirmer", confirmCreateMap);
    confirmButton->move(115, 120);
    confirmCreateMap->show();

    setMapName("Pas de Nom");
    connect(nameEdit, SIGNAL(textChanged(QString)), this, SLOT(setMapName(QString)));
    connect(xBox, SIGNAL(valueChanged(int)), this, SLOT(setMapSizeX(int)));
    connect(yBox, SIGNAL(valueChanged(int)), this, SLOT(setMapSizeY(int)));
    connect(confirmButton, SIGNAL(clicked()), this, SLOT(newMap()));
    connect(confirmButton, SIGNAL(clicked()), confirmCreateMap, SLOT(close()));
}

void Interface::setMapSizeX (int x)

{m_mapSize.x = x;}

void Interface::setMapSizeY (int y)

{m_mapSize.y = y;}

void Interface::newMap()
{
    setWindowTitle("Map Creator - [ "+m_mapName+" ]");

    m_mapPath.clear();
    m_engine->resetEngine();
    m_engine->getManager()->createMap(m_mapSize);
    m_engine->getManager()->setName(m_mapName);

    ui->VBar->setMaximum(m_engine->getManager()->mapSize().x * SCROLL_PRECISION);
    ui->HBar->setMaximum(m_engine->getManager()->mapSize().y * SCROLL_PRECISION);

    ui->VBar->setValue(0);
    QObject::disconnect(ui->HBar, SIGNAL(valueChanged(int)), this, SLOT(on_HBar_valueChanged(int)));
    ui->HBar->setValue((m_engine->getManager()->mapSize().y * SCROLL_PRECISION)/2);
    QObject::connect(ui->HBar, SIGNAL(valueChanged(int)), this, SLOT(on_HBar_valueChanged(int)));

    m_engine->getRender()->updateScrollBox();

    ui->saveMap->setEnabled(true);

    m_layersModel->clear();
    m_engine->getManager()->removeAllLayers();

    GameLayer* selector_layer = m_engine->getManager()->addLayer(-2, "Selecteur", true, true);
    if(selector_layer == NULL)
    {
        qDebug() << "Impossible de creer le layer -2 dans " << __FILE__ << __LINE__;
        exit(0);
    }

    GameLayer* collision_layer = m_engine->getManager()->addLayer(-1, "Couche SYSTEM", false, true);
    if(collision_layer == NULL)
    {
        qDebug() << "Impossible de creer le layer -1 dans " << __FILE__ << __LINE__;
        exit(0);
    }

    populateLayerModel();

    on_layer_add_clicked();

    m_engine->setLayerFocus(1);
}

void Interface::populateLayerModel()
{
    m_layersModel->clear();

    const QList<GameLayer*>* layers = m_engine->getManager()->getLayersOrder();
    QList<GameLayer*>::const_iterator it = layers->begin();
    QList<GameLayer*>::const_iterator itEnd = layers->end();
    //foreach(GameLayer* layer, *layers)
    do
    {
        itEnd--;
        GameLayer *layer = *itEnd;
        QStandardItem *item = new QStandardItem(layer->getName());
        item->setData(layer->getId(), Qt::UserRole);
        if(layer->isSystem())
            item->setToolTip("SYSTEME");
        else
            item->setToolTip("NORMAL");
        item->setCheckable(true);
        item->setCheckState(layer->isVisible() ? Qt::Checked : Qt::Unchecked);
        item->setEditable(false);
        m_layersModel->appendRow(item);
    } while(itEnd != it);
}

void Interface::keyPressEvent ( QKeyEvent * event )
{
    event->accept();
    // Se deplacer
    if(event->key() == Qt::Key_Right)
        ui->HBar->setValue(ui->HBar->value()+1);
    if(event->key() == Qt::Key_Left)
        ui->HBar->setValue(ui->HBar->value()-1);
    if(event->key() == Qt::Key_Up)
        ui->VBar->setValue(ui->VBar->value()-1);
    if(event->key() == Qt::Key_Down)
        ui->VBar->setValue(ui->VBar->value()+1);

    // Selection
    if(event->key() == Qt::Key_Return)
    {ui->tool_place->setChecked(true);
        m_engine->setTool (TOOL_PLACE);
        m_engine->selection();
        m_engine->selection();}
    if(event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace )
    {  ui->tool_delete->setChecked(true);
        m_engine->setTool(TOOL_DELETE);
        m_engine->selection();}

}

void Interface::on_VBar_valueChanged(int value)

{
    int x = ((float(ui->HBar->value())/float(ui->HBar->maximum()))-0.5)*m_mapSize.x*CELL_SIZE_X;
    int y = (float(value)/float(ui->VBar->maximum()))*m_mapSize.y*CELL_SIZE_Y;

    m_engine->getRender()->setViewPosition(sf::Vector2f(x,y));
}

void Interface::on_HBar_valueChanged(int value)
{
    int x = ((float(value)/float(ui->HBar->maximum()))-0.5)*m_mapSize.x*CELL_SIZE_X;
    int y = (float(ui->VBar->value())/float(ui->VBar->maximum()))*m_mapSize.y*CELL_SIZE_Y;

    m_engine->getRender()->setViewPosition(sf::Vector2f(x,y));
}

void Interface::mapMoved()
{
    sf::Vector2f position = m_engine->getRender()->getViewPosition();

    float hvalue = ((position.x / (CELL_SIZE_X*m_mapSize.x))+0.5)*ui->HBar->maximum();
    float vvalue = (position.y / (CELL_SIZE_Y*m_mapSize.y))*ui->VBar->maximum();

    ui->HBar->blockSignals(true);
    ui->HBar->setValue(hvalue);
    ui->HBar->blockSignals(false);

    ui->VBar->blockSignals(true);
    ui->VBar->setValue(vvalue);
    ui->VBar->blockSignals(false);
}

void Interface::on_tool_delete_clicked(bool checked)

{m_engine->setTool (TOOL_DELETE);}

void Interface::on_tool_place_clicked (bool checked)

{
    ui->tab_selector->setCurrentIndex(m_lastChoice);
    m_engine->setTool (TOOL_PLACE);
}

void Interface::on_tool_collision_clicked(bool checked)

{m_engine->setTool(TOOL_COLLISION);}

void Interface::on_tool_move_clicked(bool checked)

{m_engine->setTool(TOOL_MOVE);}

void Interface::on_tool_place_clicked()

{
    ui->tool_place->setChecked(true);
    ui->tool_collision->setChecked(false);
    ui->tool_delete->setChecked(false);
    ui->tool_height->setChecked(false);
    ui->tool_light->setChecked(false);
    ui->tool_move->setChecked(false);
}

void Interface::on_tool_delete_clicked()

{
    ui->tool_place->setChecked(false);
    ui->tool_collision->setChecked(false);
    ui->tool_delete->setChecked(true);
    ui->tool_height->setChecked(false);
    ui->tool_light->setChecked(false);
    ui->tool_move->setChecked(false);
}

void Interface::on_tool_height_clicked()

{
    ui->tool_place->setChecked(false);
    ui->tool_collision->setChecked(false);
    ui->tool_delete->setChecked(false);
    ui->tool_height->setChecked(true);
    ui->tool_light->setChecked(false);
    ui->tool_move->setChecked(false);
}

void Interface::on_tool_light_clicked()

{
    ui->tool_place->setChecked(false);
    ui->tool_collision->setChecked(false);
    ui->tool_delete->setChecked(false);
    ui->tool_height->setChecked(false);
    ui->tool_light->setChecked(true);
    ui->tool_move->setChecked(false);
}

void Interface::on_tool_collision_clicked()

{
    ui->tool_place->setChecked(false);
    ui->tool_collision->setChecked(true);
    ui->tool_delete->setChecked(false);
    ui->tool_height->setChecked(false);
    ui->tool_light->setChecked(false);
    ui->tool_move->setChecked(false);
}

void Interface::on_tool_move_clicked()
{
    ui->tool_place->setChecked(false);
    ui->tool_collision->setChecked(false);
    ui->tool_delete->setChecked(false);
    ui->tool_height->setChecked(false);
    ui->tool_light->setChecked(false);
    ui->tool_move->setChecked(true);
}

void Interface::showTiles ()
{
    m_tilesModel->clear();
    foreach (const Tile *tile,*TileManagerSingleton::getInstance()->data())
    {
        if(tile == NULL)
            continue;

        QStandardItem* item = new QStandardItem();

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
        item->setData(tile->getId(),Qt::UserRole);
        m_tilesModel->appendRow(item);
    }
}


void Interface::tileSelected (int id)
{
    m_engine->setTileChoice(id);
    m_engine->setTool(TOOL_PLACE);
    ui->tool_place->setChecked(true);

    ui->tool_collision->setChecked(false);
    ui->tool_delete->setChecked(false);
    ui->tool_height->setChecked(false);
    ui->tool_light->setChecked(false);
    ui->tool_move->setChecked(false);

    emit tileSelection (id);
}

void Interface::tileSelected(const QModelIndex &tile)
{
    tileSelected(tile.data(Qt::UserRole).toInt());
}

void Interface::on_saveMap_triggered()

{
    if (m_engine->getManager()->mapExist())
    {
        if (m_mapPath.isEmpty() || m_mapPath == "")
            m_mapPath = QFileDialog::getSaveFileName(this, "Enregistrer la carte", m_mapName, "Fichier MAP (*.map)");


        if (m_mapPath != "")
        { setCursor(Qt::WaitCursor);

            if (!m_engine->getManager()->saveMap (m_mapPath))
                QMessageBox::critical(this, "Erreur", "Erreur lors de la sauvegarde");

            setCursor(Qt::ArrowCursor);
        }


    }

    else
        QMessageBox::information (this, "Action Impossible", "Aucune carte n'est chargée");
}

void Interface::on_loadMap_triggered()

{
    QString path = QFileDialog::getOpenFileName(this, "Charger une carte", "", MAPS_FORMAT);
    if (path != "")
    {

        setCursor(Qt::WaitCursor);

        if (m_engine->getManager()->loadMap (path))
        {
            ui->saveMap->setEnabled(true);
            m_mapPath=path;
            showTiles();
            ui->VBar->setMaximum(m_engine->getManager()->mapSize().x * SCROLL_PRECISION);
            ui->HBar->setMaximum(m_engine->getManager()->mapSize().y * SCROLL_PRECISION);


            ui->VBar->setValue(0);
            QObject::disconnect(ui->HBar, SIGNAL(valueChanged(int)), this, SLOT(on_HBar_valueChanged(int)));
            ui->HBar->setValue((m_engine->getManager()->mapSize().y * SCROLL_PRECISION)/2);
            m_engine->resetEngine();
            QObject::connect(ui->HBar, SIGNAL(valueChanged(int)), this, SLOT(on_HBar_valueChanged(int)));

            m_engine->getRender()->updateScrollBox();}
        else
            QMessageBox::critical(this, "Erreur", "Erreur lors du chargement");

        setCursor(Qt::ArrowCursor);
    }

}

void Interface::on_sendMap_triggered()

{QMessageBox::information (this, "Indisponible", "En cours de developpement");}

void Interface::on_tool_height_clicked(bool checked)

{m_engine->setTool (TOOL_HEIGHT);}

void Interface::on_tool_light_clicked(bool checked)

{
    ui->tab_selector->setCurrentIndex(3);
    m_engine->setTool (TOOL_LIGHT);
}

void Interface::on_version_triggered ()

{
    QDialog* version = new QDialog ();
    version->setModal(true);
    version->setWindowTitle("Version");
    QVBoxLayout *layout = new QVBoxLayout (version);

    QLabel* Label = new QLabel ("Map Creator est developpé dans le cardre d'un jeu MMORPG");
    QLabel* Label2 = new QLabel ("Revision "+ toString(REVISION) +" - Alpha");
    QLabel* Label3 = new QLabel ("Si vous etes un graphiste, et voulez joindre le projet, vous pouvez me contacter sur le site du zero : <a href=\"www.siteduzero.com/membres-294-291282.html\">Pti'Zero</a>");
    Label3->setOpenExternalLinks(true);

    layout->addWidget(Label, 0, Qt::AlignHCenter);
    layout->addWidget(Label2, 0, Qt::AlignHCenter);
    layout->addWidget(Label3, 0, Qt::AlignHCenter);

    version->show();
}

void Interface::on_addTile_triggered ()

{
    int ret = QMessageBox::question(this, "TileEditor", "veut tu voir la version de ptitminus ^^ ?", QMessageBox::Yes, QMessageBox::No);
    if(ret == QMessageBox::No)
    {
        m_editor = new TileEditor (m_engine, this);
        connect (m_editor, SIGNAL (tileAdded ()), this, SLOT (showTiles ()));
        m_editor->show();
    }
    else
    {
        TileEditorDialog *d = new TileEditorDialog(this);
        connect(d, SIGNAL(tileAdded()), this, SLOT(showTiles()));
        d->show();
    }
}

void Interface::on_loadTiles_triggered ()

{
    QString formats;
    QString tiles_path = QFileDialog::getOpenFileName(this, "Charger des tiles",  QDir::currentPath()+"/datas/packs", QString(FORMATS) ,&formats);

    if (tiles_path != "")
    { setCursor(Qt::WaitCursor);

        if (formats == TILES_FORMAT)
            m_tilesPath = tiles_path;

        m_engine->getManager()->loadTiles(tiles_path);
        showTiles();
        setCursor(Qt::ArrowCursor);}
}

void Interface::on_saveTiles_triggered ()

{
    if (m_tilesPath.isEmpty() || m_tilesPath == "")
        m_tilesPath = QFileDialog::getSaveFileName(this, "Enregistrer les Tiles", "*.tile", "Fichier TILE (*.tile)");

    if (m_tilesPath != "")
    {

        setCursor(Qt::WaitCursor);

        if (!m_engine->getManager()->saveTiles(m_tilesPath))
            QMessageBox::critical(this, "Echec", "Erreur durant l'enregistrement");

        setCursor(Qt::ArrowCursor);
    }

}

void Interface::on_deleteTiles_triggered ()

{
    QMessageBox::information(this, "Information", "Toute cellule utulisant un tile supprimé sera elle aussi effacée \n\n Cliquer sur un tile dans le menu pour le decharger");
    QPushButton *stop = new QPushButton ("Arreter la suppression",this);
    stop->setGeometry(ui->tool_box->x(),ui->tool_box->y()+55, ui->tool_box->width(), ui->tool_box->height());

    connect (stop, SIGNAL (clicked()), this, SLOT(deleteTile_disconnect()));
    connect (stop, SIGNAL(clicked()), stop, SLOT(close()));

    ui->menubar->setEnabled(false);
    ui->menuCarte->setEnabled(false);
    ui->infos->setEnabled(false);

    m_engine->setTool(TOOL_NOTHING);
    m_engine->setTileChoice(-1);

    stop->show();

    connect (this, SIGNAL(tileSelection(int)), this, SLOT (deleteTile(int)));
}

void Interface::deleteTile(int id)

{
    m_engine->getManager()->removeTile(id);
    m_engine->setTool(TOOL_NOTHING);
    m_engine->setTileChoice(-1);
    showTiles();
}


void Interface::deleteTile_disconnect()

{
    disconnect(this, SIGNAL(tileSelection(int)), this, SLOT (deleteTile(int)));

    ui->menubar->setEnabled(true);
    ui->menuCarte->setEnabled(true);
    ui->infos->setEnabled(true);
}

void Interface::status_bar_position (sf::Vector2i position)

{
    QString _text;
    _text = "Case courante: "+toString(position.x)+", "+toString(position.y);

    if (!m_engine->getManager()->inProportions(position))
        _text+= " - Hors Carte";

    m_statusPosition.setText(_text);
}

void Interface::on_save_asMap_triggered()
{
    m_mapPath.clear();
    on_saveMap_triggered();
}

void Interface::on_save_asTiles_triggered()
{
    m_tilesPath.clear();
    on_saveTiles_triggered();
}

void Interface::on_getBack_triggered()

{m_engine->loadLastCell();}

void Interface::on_getForward_triggered()

{m_engine->loadNextCell();}

void Interface::on_enableGrid_triggered()

{m_engine->getRender()->showGrid (ui->enableGrid->isChecked());}

void Interface::on_zoomIn_triggered()

{m_engine->getRender()->setZoom (m_engine->getRender()->getZoom()+POSITIVE_ZOOM,ZOOM_TIME);}

void Interface::on_zoomOut_triggered()

{m_engine->getRender()->setZoom (m_engine->getRender()->getZoom()+NEGATIVE_ZOOM,ZOOM_TIME);}

void Interface::on_goto_cell_triggered()

{
    QDialog* confirmPosition = new QDialog (this);
    confirmPosition->setModal(true);
    confirmPosition->setFixedSize(300, 90);
    confirmPosition->setWindowTitle("Aller à la case");

    QLabel* xLabel = new QLabel ("X", confirmPosition);
    xLabel->move(50, 10);

    QLabel* yLabel = new QLabel ("Y", confirmPosition);
    yLabel->move (200, 10);

    QSpinBox* xBox = new QSpinBox (confirmPosition);
    xBox->move(50, 30);
    xBox->setMinimum(0);
    xBox->setMaximum(m_engine->getManager()->mapSize().x-1);
    xBox->setValue(0);
    m_destinationCell.x = 0;

    QSpinBox* yBox = new QSpinBox (confirmPosition);
    yBox->move(200, 30);
    yBox->setMinimum(0);
    yBox->setMaximum(m_engine->getManager()->mapSize().y-1);
    yBox->setValue(0);
    m_destinationCell.y = 0;

    QPushButton* confirmButton = new QPushButton  ("Confirmer", confirmPosition);
    confirmButton->move(105, 50);
    confirmPosition->show();

    connect(xBox, SIGNAL(valueChanged(int)), this, SLOT(setDestinationX(int)));
    connect(yBox, SIGNAL(valueChanged(int)), this, SLOT(setDestinationY(int)));
    connect(confirmButton, SIGNAL(clicked()), this, SLOT(goToCell()));
    connect(confirmButton, SIGNAL(clicked()), confirmPosition, SLOT(close()));
}

void Interface::setDestinationX (int x)

{m_destinationCell.x = x;}

void Interface::setDestinationY (int y)

{m_destinationCell.y = y;}

void Interface::goToCell()

{m_engine->getRender()->setViewVPosition(m_destinationCell,5000);}

void Interface::on_tab_selector_currentChanged(int index)
{
    if (index != 3)
        m_lastChoice = index;
}

void Interface::setMapName(QString name)

{m_mapName = name;}

void Interface::on_layer_add_clicked()
{
    if(!m_engine->getManager()->mapExist())
        return;
    int number_id = m_layersModel->rowCount()-1;
    bool alreadyExist;

    do{
        alreadyExist = false;

        for (int i = 0; i < m_layersModel->rowCount(); i++) {
            if (m_layersModel->itemFromIndex(m_layersModel->index(i,0))->data(Qt::UserRole).toInt() == number_id)
                alreadyExist = true;
        }
        if (alreadyExist)
            number_id ++;
    }
    while (alreadyExist);

    GameLayer *temp = m_engine->getManager()->addLayer(number_id, "Couche n°"+toString(number_id), true, false);
    if(temp == NULL)
    {
        qDebug() << "Impossible d'ajouter le layer " << number_id << "dans "<<__FILE__<<__LINE__;
        exit(0);
    }

    populateLayerModel();

    m_engine->setLayerFocus(number_id);
    m_slayersModel->clear();
    m_slayersModel->select(m_layersModel->index(m_layersModel->rowCount()-1,0),QItemSelectionModel::Select);
}

void Interface::on_layer_delete_clicked()
{
    QModelIndexList list = m_slayersModel->selectedRows();
    if(list.size() == 1)
    {
        QStandardItem* item = m_layersModel->itemFromIndex(list[0]);
        int id = item->data(Qt::UserRole).toInt();
        m_engine->getManager()->removeLayer(static_cast<ID>(id));

        populateLayerModel();

        m_slayersModel->clear();
        m_slayersModel->select(m_layersModel->index(m_layersModel->rowCount()-1,0),QItemSelectionModel::Select);
    } 
}

void Interface::on_layer_up_clicked()
{
    QModelIndexList list = m_slayersModel->selectedRows();
    if(list.size() != 1)
        return;

    QStandardItem *item =  m_layersModel->itemFromIndex(list[0]);
    QString text = item->text();
    ID id = item->data(Qt::UserRole).toInt();
    m_engine->getManager()->getLayerSystem()->moveUp(id);

    populateLayerModel();

    QModelIndex index = m_layersModel->findItems(text)[0]->index();

    m_slayersModel->select(index,QItemSelectionModel::Select);
}

void Interface::on_layer_down_clicked()
{
    QModelIndexList list = m_slayersModel->selectedRows();
    if(list.size() != 1)
        return;

    QStandardItem *item =  m_layersModel->itemFromIndex(list[0]);
    QString text = item->text();
    ID id = item->data(Qt::UserRole).toInt();

    m_engine->getManager()->getLayerSystem()->moveDown(id);

    populateLayerModel();

    QModelIndex index = m_layersModel->findItems(text)[0]->index();

    m_slayersModel->select(index,QItemSelectionModel::Select);
}

void Interface::layerSelected(const QModelIndex &index)
{
    m_engine->setLayerFocus(m_layersModel->itemFromIndex(index)->data(Qt::UserRole).toInt());
}

void Interface::openTile(QModelIndex index)

{
    //Fonction a ecrire

    QString file_name = m_filesModel->filePath(index);
    if (file_name.contains(".tile"))
        qDebug()<<file_name;
}


void Interface::closeEvent(QCloseEvent *event)
{
    TileManagerSingleton::clear();
    EffectManagerSingleton::clear();
    event->accept();
}

void Interface::ItemLayerChanged(QStandardItem* item)
{
    int id = item->data(Qt::UserRole).toInt();
    GameLayer *layer = m_engine->getManager()->getLayer(static_cast<ID>(id));

    layer->setVisible(item->checkState() == Qt::Checked);
}
