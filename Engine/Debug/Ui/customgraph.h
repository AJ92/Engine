#ifndef CUSTOMGRAPH_H
#define CUSTOMGRAPH_H


#include <QWidget>
#include <QString>
#include <QList>

class CustomGraph : public QWidget
{
    Q_OBJECT

public:
    CustomGraph(QWidget *parent = 0);

    void setTitle(QString title);

    void addData(double data);

protected:
    void paintEvent(QPaintEvent *event);
    QString title;

    int amount_data;
    double max_data;
    QList<double> data_list;
};

#endif // CUSTOMGRAPH_H
