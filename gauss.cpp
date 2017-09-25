#include "gauss.h"
#include "ui_gauss.h"
#include <QTableWidget> // Library for allow the use of items from a table widget.

Gauss::Gauss(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gauss)
{
    ui->setupUi(this); // connect the slots to the push button signals
    connect(ui->Inicio,SIGNAL(clicked()),this,SLOT(ejecutar()));
    connect(ui->Reanudar,SIGNAL(clicked()),this,SLOT(reiniciar()));
    connect(ui->Agregar,SIGNAL(clicked()),this,SLOT(agrega()));
    ui->Inicio->setDisabled(true);// the "start" push button is deactivated
    ui->Reanudar->setDisabled(true);// the "resume" push button is deactivated
    i=0;
}
void Gauss::agrega(){ // With this slot the user will add items from spinboxes to the table.
    ui->Reanudar->setDisabled(false); //the "resume" push button is activated
    // All the spinboxes collects the equations variables and saves it in a 4x4 matrix.
    matriz[i][0]=ui->va1->value();
    matriz[i][1]=ui->va2->value();
    matriz[i][2]=ui->va3->value();
    matriz[i][3]=ui->va4->value();
    indep[i][0]=ui->vaigual->value();
    // The introduced values shows at his respective table position.
    ui->tabla->setItem(i,0,new QTableWidgetItem(ui->va1->text()));
    ui->tabla->setItem(i,1,new QTableWidgetItem(ui->va2->text()));
    ui->tabla->setItem(i,2,new QTableWidgetItem(ui->va3->text()));
    ui->tabla->setItem(i,3,new QTableWidgetItem(ui->va4->text()));
    ui->tabla->setItem(i,4,new QTableWidgetItem(ui->vaigual->text()));
    i++;// Sums one number for the row counter.
    if(i==4){ //If the row counter reaches this limit:
        ui->Agregar->setDisabled(true);//The start button enables.
        ui->Inicio->setDisabled(false);//the "start" push button is activated
    }
}
void Gauss:: ejecutar(){ //slot that will execute the method when you press start
    for(i=4;i>=0;i--){// This cycle analyzes if the first row of the main matrix have zeros.
      if(matriz[0][i]==0){//If it haves zeros:
          // Exchanges row positions for the independent variables.
         ind1=indep[0][0];// A temporal variable takes the value of first independent variable.
         ind2=indep[i+1][0];// Another temporal variable takes the value of the next independent variable.
         for(j=0;j<4;j++){// This cycle exchanges row positions for the x variables.
         tempo[0][j]=matriz[0][j];// A temporal matrix saves the first row.
         tempo2[0][j]=matriz[i+1][j];// Another temporal matrix saves the next row.
         matriz[i+1][j]=tempo[0][j];// Puts the first row on the next row.
         matriz[0][j]=tempo2[0][j];// Puts the next row on the first row.
         indep[i+1][0]=ind1;// Puts the first independent variable on next row.
         indep[0][0]=ind2;// Puts the next variable on previous row.
                    }
                }
            }
     // The method starts.
    for(i=0;i<4;i++){//This cycle analyzes rows.
        for(j=0;j<i;j++){//This cycle analyzes columns.
             // This line turns zero the matrix position.
            matriz[i][j]=(matriz[i][j]-(matriz[0][j]*(matriz[i][j]/matriz[0][j])));
        }
    }
       x4=(indep[3][0]/matriz[3][3]);//Finds the x4 value.
       x3=(indep[2][0]-(matriz[2][3]*x4))/(matriz[2][2]);//Finds the x3 value, with the previos variable.
       //Finds the x2 variable, with the two previous variables.
       x2=(indep[1][0]-(matriz[1][2]*x3)-(matriz[1][3]*x4))/(matriz[1][1]);
       //Finds the x1 value, with the three previous variables.
       x1=(indep[0][0]-(matriz[0][1]*x2)-(matriz[0][2]*x3)-(matriz[0][3]*x4))/(matriz[0][0]);
        //Show all the found values, on a independent LCD number.
       ui->p1->display(x1);
       ui->p2->display(x2);
       ui->p3->display(x3);
       ui->p4->display(x4);
}
void Gauss:: reiniciar(){ //slot that will restart the method to add new values to the array
     //Clears all spinboxes
    ui->va1->setValue(0.0);
    ui->va2->setValue(0.0);
    ui->va3->setValue(0.0);
    ui->va4->setValue(0.0);
    ui->vaigual->setValue(0.0);
    //matriz[4][4]={0};
    //indep[4][1]={0};
    ui->tabla->clearContents();// Clears the table widget contents.
     // Clears all the LCD numbers.
    ui->p1->display(0.0);
    ui->p2->display(0.0);
    ui->p3->display(0.0);
    ui->p4->display(0.0);
    ui->Inicio->setDisabled(true);//the "start" push button is deactivated
    ui->Reanudar->setDisabled(false);//the "resume" push button is activated
    i=0;// The row counter goes to zero, for start over the data introduction.
}
Gauss::~Gauss()
{
    delete ui;
}
