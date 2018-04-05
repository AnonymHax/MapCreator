#include "GoToWidget.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QDialogButtonBox>

GoToWidget::GoToWidget(MapManager *mapManager, QSize *position, QWidget *parent)
    : QDialog(parent)
    , m_position(position)
    , m_mapManager(mapManager)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("Aller à la case");
    buildGUI();
}

void GoToWidget::buildGUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel* xLabel = new QLabel ("X", this);
    QLabel* yLabel = new QLabel ("Y", this);

    if(m_mapManager == NULL)
        return;

    QSpinBox* xBox = new QSpinBox (this);
    connect(xBox, SIGNAL(valueChanged(int)), this, SLOT(xChanged(int)));
    xBox->setMinimum(0);
    xBox->setMaximum(m_mapManager->mapSize().x-1);
    xBox->setValue(0);

    QSpinBox* yBox = new QSpinBox (this);
    connect(yBox, SIGNAL(valueChanged(int)), this, SLOT(yChanged(int)));
    yBox->setMinimum(0);
    yBox->setMaximum(m_mapManager->mapSize().y-1);
    yBox->setValue(0);

    QHBoxLayout *xLayout = new QHBoxLayout;
    xLayout->addWidget(xLabel);
    xLayout->addWidget(xBox);

    QHBoxLayout *yLayout = new QHBoxLayout;
    yLayout->addWidget(yLabel);
    yLayout->addWidget(yBox);

    QDialogButtonBox *buttons = new QDialogButtonBox(this);
    buttons->addButton(QDialogButtonBox::Ok);
    connect(buttons, SIGNAL(accepted()), this, SLOT(accept()));

    mainLayout->addLayout(xLayout);
    mainLayout->addLayout(yLayout);
    mainLayout->addWidget(buttons);
}

void GoToWidget::xChanged(int value)
{
   m_position->setWidth(value);
}

void GoToWidget::yChanged(int value)
{
    m_position->setHeight(value);
}
