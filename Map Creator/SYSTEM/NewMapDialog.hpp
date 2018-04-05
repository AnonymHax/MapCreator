#ifndef NEWMAPDIALOG_HPP
#define NEWMAPDIALOG_HPP

#include <QDialog>

class NewMapDialog : public QDialog
{
    Q_OBJECT
public:
    explicit NewMapDialog(QSize *size,QString *name, QWidget *parent = 0);
    
    void buildGUI();

public slots:
    void xChanged(int);
    void yChanged(int);
    void nameChanged(QString);

private:
    QSize *m_size;
    QString *m_name;
    
};

#endif // NEWMAPDIALOG_HPP
