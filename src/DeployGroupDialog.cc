/*
 * WtTimeTrack - Web-based time tracker
 *
 * Copyright (C) 2017 Martin Hierholzer, Hamburg, Germany
 *
 * This program is released under the GNU GENERAL PUBLIC LICENSE v3.0
 * See the LICENSE file for terms of use.
 */

#include <cmath>

#include "DeployGroupDialog.h"

#include <Wt/WPushButton.h>
#include <Wt/WGridLayout.h>
#include <Wt/Dbo/WtSqlTraits.h>
#include <Wt/WComboBox.h>
#include <Wt/WTable.h>

DeployGroupDialog::DeployGroupDialog(Updateable *owner, Session &session, Wt::Dbo::ptr<DeployGroup> group)
: Wt::WDialog("Deploy Group"), owner_(owner), session_(session), group_(group)
{
    contents()->addStyleClass("form-group");

    Dbo::Transaction transaction(session_.session_);
    auto user = session_.user();

    bool createNew = false;
    if(group_.get() == nullptr) {
      createNew = true;
      group_ = Wt::Dbo::ptr<DeployGroup>(std::make_unique<DeployGroup>());
    }

    auto grid = contents()->setLayout(std::make_unique<Wt::WGridLayout>());
    grid->setColumnStretch(0,0);
    grid->setColumnStretch(1,1);

    grid->addWidget(std::make_unique<Wt::WText>("Name: "), 0, 0);
    auto w_name = grid->addWidget(std::make_unique<Wt::WLineEdit>(), 0, 1);
    w_name->setText(group_->name);

    grid->addWidget(std::make_unique<Wt::WText>("Host name: "), 1, 0);
    auto w_host = grid->addWidget(std::make_unique<Wt::WLineEdit>(), 1, 1);
    w_host->setText(group_->hostname);

    grid->addWidget(std::make_unique<Wt::WText>("Deploy Item Instances: "), 3, 0);

    auto table = grid->addWidget(std::make_unique<WTable>(), 3,1);
    table->setHeaderCount(1);
    table->setWidth(WLength("100%"));
    table->elementAt(0, 0)->addWidget(std::make_unique<WText>("Item name"));
    table->elementAt(0, 1)->addWidget(std::make_unique<WText>("Parameters"));

    auto &instances = group_->deployItemInstances;
    size_t row=1;
    for(const auto &i : instances) {
      table->elementAt(row,0)->addWidget(std::make_unique<WText>(i->deployItems->name));
      std::string params;
      for(const auto &p : i->parameters) {
        params += p->key + "=" + p->value + "; ";
      }
      table->elementAt(row,0)->addWidget(std::make_unique<WText>(params));
    }

    auto w_addparam = grid->addWidget(std::make_unique<Wt::WPushButton>("Add deploy item instance"), 4, 1);
    w_addparam->clicked().connect(this, [=] {
    } );

    if(!createNew) {   // existing item might be deleted
      Wt::WPushButton *del = footer()->addWidget(std::make_unique<Wt::WPushButton>("Delete"));
      del->clicked().connect(this, [=] {
        dbo::Transaction transaction(session_.session_);
        group_.remove();
        owner_->update();
        hide();
      } );
    }

    auto ok = footer()->addWidget(std::make_unique<Wt::WPushButton>("Save"));
    ok->setDefault(true);
    ok->clicked().connect(this, [=] {
      dbo::Transaction transaction(session_.session_);

      // update the database object
      group_.modify()->name = w_name->text().toUTF8();
      group_.modify()->hostname = w_host->text().toUTF8();

      if(createNew) {   // create new?
        session_.session_.add(group_);
      }
      owner_->update();
      hide();
    } );

    auto cancel = footer()->addWidget(std::make_unique<Wt::WPushButton>("Cancel"));
    cancel->clicked().connect(this, [=] {hide();} );

}
