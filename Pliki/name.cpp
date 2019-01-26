#include "name.h"
#include "step.h"
#include "ui_name.h"
#include "mainwindow.h"
#include <QDebug>


Name::Name(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Name)
{
    ui->setupUi(this);
    
    QSqlQuery query("SELECT * FROM Uklady");
    while(query.next())
    {
        QString name = query.value(1).toString();
        if (names.size() == 0 )
        {
            names.append(name);
            ui->comboBox->addItem(name);
        }
        else
        {
            qint32 iii = 0;
            for(int i=0;i<=names.size()-1;i++)
            {
                if(names[i]==name)
                {
                    iii=1;
                    break;
                }
            }
            if(iii==0)
            {
                names.append(name);
                ui->comboBox->addItem(name);
            }
        }

    }


}

Name::~Name()
{
    delete ui;
}

void Name::on_gobtn_clicked()
{
    QString nazwa ;

    //nazwa nowego ukladu
    nazwa = ui->nownazwa->text();
    if (nazwa == "")
    {
        nazwa = ui->comboBox->currentText();
    }

    Step* step = new Step();
    MainWindow* window = new MainWindow();
    connect(this, SIGNAL(wyslijnazwe(QString)),step ,SLOT(odbierznazwa(QString)));
    connect(this, SIGNAL(wyslijnazwe(QString)),window ,SLOT(namesystem(QString)));
    emit wyslijnazwe(nazwa);
    this->close();
}



