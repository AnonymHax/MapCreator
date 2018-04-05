#include "LightWidget.h"

#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QPushButton>
#include <QColorDialog>
#include <QVBoxLayout>
#include <QLabel>

LightWidget:: LightWidget(QWidget *parent)
    : QWidget(parent)
    , m_rayon(NULL)
    , m_intensite(NULL)
    , m_qualite(NULL)
    , m_angle(NULL)
    , m_angleOuverture(NULL)
    , m_colorButton(NULL)
    , m_color(Qt::white)
{
    setAttribute(Qt::WA_DeleteOnClose);

    BuildGUI();
}

void LightWidget::BuildGUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    // rayon
    QLabel *rayonLabel = new QLabel("Rayon");
    rayonLabel->setAlignment(Qt::AlignCenter);
    m_rayon = new QSpinBox(this);
    m_rayon->setRange(0,500);
    m_rayon->setSingleStep(1);
    m_rayon->setValue(200);
    connect(m_rayon, SIGNAL(valueChanged(int)), this, SIGNAL(lightChanged()));
    m_rayon->setMinimumWidth(203);

    mainLayout->addWidget(rayonLabel);
    mainLayout->addWidget(m_rayon);

    //intensite
    QLabel *intensiteLabel = new QLabel("Intensité");
    intensiteLabel->setAlignment(Qt::AlignCenter);
    m_intensite = new QSpinBox(this);
    m_intensite->setRange(0,500);
    m_intensite->setSingleStep(1);
    m_intensite->setValue(150);
    connect(m_intensite, SIGNAL(valueChanged(int)), this, SIGNAL(lightChanged()));
    m_intensite->setMinimumWidth(203);

    mainLayout->addWidget(intensiteLabel);
    mainLayout->addWidget(m_intensite);

    //qualite
    QLabel *qualiteLabel = new QLabel("Qualité");
    qualiteLabel->setAlignment(Qt::AlignCenter);
    m_qualite = new QSpinBox(this);
    m_qualite->setRange(0,250);
    m_qualite->setSingleStep(1);
    m_qualite->setValue(30);
    connect(m_qualite, SIGNAL(valueChanged(int)), this, SIGNAL(lightChanged()));
    m_qualite->setMinimumWidth(203);

    mainLayout->addWidget(qualiteLabel);
    mainLayout->addWidget(m_qualite);

    //angle
    QLabel *angleLabel = new QLabel("Angle");
    angleLabel->setAlignment(Qt::AlignCenter);
    m_angle = new QDoubleSpinBox(this);
    m_angle->setRange(0,360);
    m_angle->setSingleStep(1);
    m_angle->setValue(360);
    connect(m_angle, SIGNAL(valueChanged(double)), this, SIGNAL(lightChanged()));
    m_angle->setDecimals(2);
    m_angle->setMinimumWidth(203);

    mainLayout->addWidget(angleLabel);
    mainLayout->addWidget(m_angle);

    //angleOuverture
    QLabel *angleOuvertureLabel = new QLabel("Angle d'ouverture");
    angleOuvertureLabel->setAlignment(Qt::AlignCenter);
    m_angleOuverture = new QDoubleSpinBox(this);
    m_angleOuverture->setRange(0,360);
    m_angleOuverture->setSingleStep(1);
    m_angleOuverture->setValue(180);
    connect(m_angleOuverture, SIGNAL(valueChanged(double)), this, SIGNAL(lightChanged()));
    m_angleOuverture->setDecimals(2);
    m_angleOuverture->setMinimumWidth(203);

    mainLayout->addWidget(angleOuvertureLabel);
    mainLayout->addWidget(m_angleOuverture);

    //couleur
    QLabel *couleurLabel = new QLabel("Couleur");
    couleurLabel->setAlignment(Qt::AlignCenter);
    m_colorButton = new QPushButton(this);
    connect(m_colorButton, SIGNAL(clicked()), this, SLOT(choiceColor()));
    m_colorButton->setMinimumWidth(203);
    updateColorButton();

    mainLayout->addWidget(couleurLabel);
    mainLayout->addWidget(m_colorButton);

    setLayout(mainLayout);
}

void LightWidget::setRayon(int rayon)
{
    m_rayon->setValue(rayon);
    emit lightChanged();
}

void LightWidget::setIntensite(int intensite)
{
    m_intensite->setValue(intensite);
    emit lightChanged();
}

void LightWidget::setQualite(int qualite)
{
    m_qualite->setValue(qualite);
    emit lightChanged();
}

void LightWidget::setAngle(double angle)
{
    m_angle->setValue(angle);
    emit lightChanged();
}

void LightWidget::setAngleOuverture(double angleOuverture)
{
    m_angleOuverture->setValue(angleOuverture);
    emit lightChanged();
}

void LightWidget::setColor(QColor color)
{
    m_color = color;
    updateColorButton();
}

int LightWidget::getRayon() const
{
    return m_rayon->value();
}

int LightWidget::getIntensite() const
{
    return m_intensite->value();
}

int LightWidget::getQualite() const
{
    return m_qualite->value();
}

double LightWidget::getAngle() const
{
    return m_angle->value();
}

double LightWidget::getAngleOuverture() const
{
    return m_angleOuverture->value();
}

QColor LightWidget::getColor() const
{
    return m_color;
}

void LightWidget::updateColorButton()
{
    m_colorButton->setStyleSheet("QPushButton { background : rgb( "+ QString::number(m_color.red())+","+ QString::number(m_color.green())+ ","+ QString::number(m_color.blue())+ ") }");
}

void LightWidget::choiceColor()
{
    m_color = QColorDialog::getColor(m_color, this);
    emit lightChanged();
    updateColorButton();
}

