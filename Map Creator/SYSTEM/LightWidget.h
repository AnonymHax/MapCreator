#ifndef LIGHTWIDGET_H
#define LIGHTWIDGET_H

#include <QWidget>

class QDoubleSpinBox;
class QSpinBox;
class QPushButton;

class LightWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LightWidget(QWidget *parent = 0);

    void setRayon(int rayon);
    void setIntensite(int intensite);
    void setQualite(int qualite);
    void setAngle(double angle);
    void setAngleOuverture(double angleOuverture);
    void setColor(QColor color);
    
    int getRayon() const;
    int getIntensite() const;
    int getQualite() const;
    double getAngle() const;
    double getAngleOuverture() const;
    QColor getColor() const;

protected:
    void BuildGUI();
    void updateColorButton();

private slots:
    void choiceColor();

signals:
    void lightChanged();


private:
    QSpinBox *m_rayon;
    QSpinBox *m_intensite;
    QSpinBox *m_qualite;
    QDoubleSpinBox *m_angle;
    QDoubleSpinBox *m_angleOuverture;
    QPushButton *m_colorButton;
    QColor m_color;
};

#endif // LIGHTWIDGET_H
