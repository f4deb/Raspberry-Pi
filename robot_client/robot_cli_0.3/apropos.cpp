#include "apropos.h"
#include "setup.h"

void MainWindow::aPropos(void){
    QMessageBox::information(this, "A Propos", revision);
}
