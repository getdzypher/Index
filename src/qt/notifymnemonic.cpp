#include "notifymnemonic.h"
#include "ui_notifymnemonic.h"

#include "guiutil.h"

#include "util.h"

#ifdef ENABLE_WALLET
#include "walletmodel.h"
#endif

#include <QFileDialog>
#include <QSettings>
#include <QMessageBox>

NotifyMnemonic::NotifyMnemonic(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::NotifyMnemonic)
{
    ui->setupUi(this);
}

NotifyMnemonic::~NotifyMnemonic()
{
    delete ui;
}

void NotifyMnemonic::notify()
{
#ifdef ENABLE_WALLET
    SecureString mnemonic;
    pwalletMain->GetMnemonicContainer().GetMnemonic(mnemonic);
    NotifyMnemonic notify;
    notify.setWindowIcon(QIcon(":icons/zcoin"));
    notify.ui->mnemonic->setText(mnemonic.c_str());
    while(true)
    {
        if(notify.exec())
        {
            std::string inputMnememonic = notify.ui->words->text().toStdString();
            std::string strMnemonic(mnemonic.begin(), mnemonic.end());
            if(inputMnememonic != strMnemonic) {
                notify.ui->errorMessage->setText("<font color='red'>Mnemonics don't match.</font>");
                continue;
            }
            break;
        }
    }
#endif
}