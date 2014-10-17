#include "customgraph.h"
#include <QPainter>
#include <QFont>
#include <QTimer>
#include <QTime>

CustomGraph::CustomGraph(QWidget *parent)
    : QWidget(parent)
{

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);

    title = "CustomGraph";

    setWindowTitle(tr("CustomGraph"));
    //resize(200,200);

    //fill the Graph data list with default values...
    amount_data = 100;
    max_data = 0.0;
    for(int i = 0; i < amount_data; i++){
        data_list.append(0.0);
    }
}

void CustomGraph::setTitle(QString title){
    this->title = title;
}

void CustomGraph::addData(double data){
    data_list.pop_front();
    data_list.append(data);

    if(max_data < data){
        max_data = data;
    }
    update();
}

void CustomGraph::paintEvent(QPaintEvent *)
{

    QColor colorText(40, 255, 40, 240);
    QColor colorBars(40, 180, 40, 225);

    QColor colorBackground(40,40,40, 255);

    int w = width();
    int h = height();

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    painter.translate(0, 0);

    //Background
    painter.setPen(Qt::NoPen);
    painter.setBrush(colorBackground);
    painter.drawRect(0,0,w,h);







    //draw the bars...
    if(max_data!=0.0){

        painter.save();
        double bar_width = (double)w / (double)amount_data;
        double scale_factor = (double)h / max_data;

        painter.setPen(colorBars);
        painter.setBrush(colorBars);
        painter.translate(0, h);

        double avg = 0.0;


        //paint all the lines to make a graph
        for(int i=0; i < amount_data-1; i++){
            //calculate the vertical position of the data...

            int v_pos1 = data_list.at(i) * scale_factor;
            int v_pos2 = data_list.at(i+1) * scale_factor;
            avg += data_list.at(i);

            painter.drawLine(i*bar_width,-v_pos1,(i+1)*bar_width,-v_pos2);
            //painter.drawLine(0 + i*bar_width, -v_pos, 0 + i*bar_width,v_pos);
        }
        painter.restore();


        //paint the average bar...
        painter.setPen(colorText);
        painter.setBrush(colorText);

        avg = avg/amount_data;

        painter.drawLine(0,h-avg * scale_factor,w, h-avg * scale_factor);

    }


    //TEXT
    painter.setBrush(colorBackground);
    painter.setPen(colorBackground);

    QString text_value;
    text_value.sprintf("%0.1f", data_list.last());
    painter.setFont(QFont("Courir",9,1,false));
    painter.drawText(6, 6 + 9,title + ": " + text_value);

    painter.setBrush(colorText);
    painter.setPen(colorText);

    painter.setFont(QFont("Courir",9,1,false));
    painter.drawText(5, 5 + 9,title + ": " + text_value);
}
