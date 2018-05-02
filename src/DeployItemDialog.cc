/*
 * WtTimeTrack - Web-based time tracker
 *
 * Copyright (C) 2017 Martin Hierholzer, Hamburg, Germany
 *
 * This program is released under the GNU GENERAL PUBLIC LICENSE v3.0
 * See the LICENSE file for terms of use.
 */

#include <cmath>

#include "DeployItemDialog.h"

#include <Wt/WPushButton.h>
#include <Wt/WGridLayout.h>
#include <Wt/Dbo/WtSqlTraits.h>
#include <Wt/WComboBox.h>

DeployItemDialog::DeployItemDialog(Updateable *owner, Session &session, Wt::Dbo::ptr<DeployItem> item)
: Wt::WDialog("Deploy Item"), owner_(owner), session_(session), item_(item)
{
    contents()->addStyleClass("form-group");

    Dbo::Transaction transaction(session_.session_);
    auto user = session_.user();

    bool createNew = false;
    if(item_.get() == nullptr) {
      createNew = true;
      item_ = Wt::Dbo::ptr<DeployItem>(std::make_unique<DeployItem>());
    }

    auto grid = contents()->setLayout(std::make_unique<Wt::WGridLayout>());
    grid->setColumnStretch(0,0);
    grid->setColumnStretch(1,1);

    grid->addWidget(std::make_unique<Wt::WText>("Name: "), 0, 0);
    auto w_name = grid->addWidget(std::make_unique<Wt::WLineEdit>(), 0, 1);
    w_name->setText(item_->name);

    errorMessage = grid->addWidget(std::make_unique<Wt::WText>(), 8, 1);
    errorMessage->hide();

    if(!createNew) {   // existing item might be deleted
      Wt::WPushButton *del = footer()->addWidget(std::make_unique<Wt::WPushButton>("Delete"));
      del->clicked().connect(this, [=] {
        dbo::Transaction transaction(session_.session_);
        item_.remove();
        owner_->update();
        hide();
      } );
    }

    auto ok = footer()->addWidget(std::make_unique<Wt::WPushButton>("Save"));
    ok->setDefault(true);
    ok->clicked().connect(this, [=] {
      dbo::Transaction transaction(session_.session_);

      // update the database object
      item_.modify()->name = w_name->text().toUTF8();
      if(createNew) {   // create new?
        session_.session_.add(item_);
      }
      owner_->update();
      hide();
    } );

    auto cancel = footer()->addWidget(std::make_unique<Wt::WPushButton>("Cancel"));
    cancel->clicked().connect(this, [=] {hide();} );

}

