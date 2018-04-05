#include "NewMapDialog.hpp"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QDialogButtonBox>

NewMapDialog::NewMapDialog(QSize *size, QString *name, QWidget *parent) :
    QDialog(parent)
  , m_size(size)
  , m_name(name)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("Creer une nouvelle carte");
    buildGUI();
}

void NewMapDialog::buildGUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QLabel* nameLabel = new QLabel ("Nom de la carte", this);
    QLineEdit* nameEdit = new QLineEdit ("Nom",this);
    nameEdit->selectAll();
    connect(nameEdit, SIGNAL(textChanged(QString)), this, SLOT(nameChanged(QString)));

    QLabel* xLabel = new QLabel ("Largeur", this);
    QLabel* yLabel = new QLabel ("Hauteur", this);

    QSpinBox* xBox = new QSpinBox(this);
    xBox->setMinimum(1);
    xBox->setMaximum(100000);
    connect(xBox, SIGNAL(valueChanged(int)), this, SLOT(xChanged(int)));
    xBox->setValue(100);

    QSpinBox* yBox = new QSpinBox(this);
    yBox->setMinimum(1);
    yBox->setMaximum(100000);
    connect(yBox, SIGNAL(valueChanged(int)), this, SLOT(yChanged(int)));
    yBox->setValue(100);

    QDialogButtonBox *buttons = new QDialogButtonBox(this);
    buttons->addButton(QDialogButtonBox::Ok);
    buttons->addButton(QDialogButtonBox::Cancel);
    connect(buttons, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttons, SIGNAL(rejected()), this, SLOT(reject()));

    QHBoxLayout *nameLayout = new QHBoxLayout;
    QHBoxLayout *sizeLayout = new QHBoxLayout;

    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(nameEdit);
    sizeLayout->addWidget(xLabel);
    sizeLayout->addWidget(xBox);
    sizeLayout->addSpacing(100);
    sizeLayout->addWidget(yLabel);
    sizeLayout->addWidget(yBox);

    mainLayout->addLayout(nameLayout);
    mainLayout->addLayout(sizeLayout);
    mainLayout->addWidget(buttons);

    setLayout(mainLayout);
}

void NewMapDialog::xChanged(int value)
{
    m_size->setWidth(value);
}

void NewMapDialog::yChanged(int value)
{
    m_size->setHeight(value);
}

void NewMapDialog::nameChanged(QString value)
{
    m_name->append(value);
}
