/*
 * WtTimeTrack - Web-based time tracker
 *
 * Copyright (C) 2017 Martin Hierholzer, Hamburg, Germany
 *
 * This program is released under the GNU GENERAL PUBLIC LICENSE v3.0
 * See the LICENSE file for terms of use.
 */

#include <cmath>

#include "DeployItemInstanceDialog.h"

#include <Wt/WPushButton.h>
#include <Wt/WGridLayout.h>
#include <Wt/Dbo/WtSqlTraits.h>
#include <Wt/WComboBox.h>
#include <Wt/WTable.h>

DeployItemInstanceDialog::DeployItemInstanceDialog(Updateable *owner, Session &session, Wt::Dbo::ptr<DeployItemInstance> instance)
: Wt::WDialog("Deploy Item Instance"), owner_(owner), session_(session), instance_(instance)
{
    contents()->addStyleClass("form-group");

    Dbo::Transaction transaction(session_.session_);
    auto user = session_.user();

    bool createNew = false;
    if(instance_.get() == nullptr) {
      createNew = true;
      instace_ = Wt::Dbo::ptr<DeployItem>(std::make_unique<DeployItemInstance>());
    }

    auto grid = contents()->setLayout(std::make_unique<Wt::WGridLayout>());
    grid->setColumnStretch(0,0);
    grid->setColumnStretch(1,1);

    grid->addWidget(std::make_unique<Wt::WText>("Deploy item: "), 0, 0);
    auto w_item = grid->addWidget(std::make_unique<Wt::WComboBox>(), 0, 1);
    auto items = session_.session_.find<DeployItem>().resultList();
    size_t index = 0;
    for(auto item : items) {
      w_item->addItem(item->name);
      if(instance_->deployItemInstane == item) w_item.setCurrentIndex(index);
      index++;
    }
    w_item->changed().connect( [=] {

    } );

    auto table = grid->addWidget(std::make_unique<WTable>(), 3,1);
    table->setHeaderCount(1);
    table->setWidth(WLength("100%"));
    table->elementAt(0, 0)->addWidget(std::make_unique<WText>("Parameter name"));
    table->elementAt(0, 1)->addWidget(std::make_unique<WText>("Parameter value"));

    auto &parameters = instance_->deployItemInstance->parameters;
    for(const auto &p : parameters) {
      size_t row = v_paramNames.size()+1;
      v_paramNames.push_back(table->elementAt(row, 0)->addWidget(std::make_unique<Wt::WLineEdit>()));
      v_paramValues.push_back(table->elementAt(row, 1)->addWidget(std::make_unique<Wt::WLineEdit>()));
      v_paramNames.back()->setText(p->key);
      v_paramValues.back()->setText(p->value);
    }

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
      item_.modify()->sourcePattern = w_srcpat->text().toUTF8();
      item_.modify()->installCommand = w_instcmd->text().toUTF8();
      size_t ip = 0;
      size_t np = v_paramNames.size();
      auto &parameters = item_.modify()->parameters;
      for(auto &p : parameters) {
        if(ip < np) {
          p.modify()->key = v_paramNames[ip]->text().toUTF8();
          p.modify()->value = v_paramValues[ip]->text().toUTF8();
        }
        else {
          //parameters.erase(p);
        }
        ++ip;
      }
      for(; ip < np; ++ip) {
        Wt::Dbo::ptr<KeyValue<DeployItem>> p(std::make_unique<KeyValue<DeployItem>>());
        p.modify()->key = v_paramNames[ip]->text().toUTF8();
        p.modify()->value = v_paramValues[ip]->text().toUTF8();
        parameters.insert(p);
      }

      if(createNew) {   // create new?
        session_.session_.add(item_);
      }
      owner_->update();
      hide();
    } );

    auto cancel = footer()->addWidget(std::make_unique<Wt::WPushButton>("Cancel"));
    cancel->clicked().connect(this, [=] {hide();} );

}
