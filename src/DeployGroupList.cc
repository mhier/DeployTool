/*
 * WtTimeTrack - Web-based time tracker
 *
 * Copyright (C) 2017 Martin Hierholzer, Hamburg, Germany
 *
 * This program is released under the GNU GENERAL PUBLIC LICENSE v3.0
 * See the LICENSE file for terms of use.
 */

#include "DeployGroupList.h"
#include "DeployGroupDialog.h"

#include <Wt/WText.h>
#include <Wt/WTable.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WDate.h>
#include <Wt/WPushButton.h>

DeployGroupList::DeployGroupList(Session &session)
: session_(session), Updateable(nullptr)
{
    update();
}

void DeployGroupList::update() {
    clear();

    auto user = session_.user();

    dbo::Transaction transaction(session_.session_);

    addWidget(std::make_unique<WText>("<h2>List of deploy groups</h2>"));

    auto table = std::make_unique<WTable>();
    table->setHeaderCount(1);
    table->setWidth(WLength("100%"));
    table->addStyleClass("table form-inline table-hover");

    table->elementAt(0, 0)->addWidget(std::make_unique<WText>("#"));
    table->elementAt(0, 1)->addWidget(std::make_unique<WText>("Name"));

    auto items = session_.session_.find<DeployGroup>().resultList();
    int row = 0;
    for(auto item : items) {
      row++;

      table->elementAt(row, 0)->addWidget(std::make_unique<WText>(WString("{1}").arg(row)));
      table->elementAt(row, 1)->addWidget(std::make_unique<WText>(item->name));
      table->elementAt(row, 2)->addWidget(std::make_unique<WText>(item->hostname));

      for(int i=0; i<2; ++i) {
        table->elementAt(row,i)->clicked().connect(this, [=] {
          groupDialog_ = std::make_unique<DeployGroupDialog>(this, session_, item);
          groupDialog_->show();
        });
      }

    }

    addWidget(std::move(table));

    auto newGroup = addWidget(std::make_unique<Wt::WPushButton>("Create group..."));
    newGroup->clicked().connect(this, [=] {
      groupDialog_ = std::make_unique<DeployGroupDialog>(this, session_, nullptr);
      groupDialog_->show();
    } );

}
