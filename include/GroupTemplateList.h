/*
 * WtTimeTrack - Web-based time tracker
 *
 * Copyright (C) 2017 Martin Hierholzer, Hamburg, Germany
 *
 * This program is released under the GNU GENERAL PUBLIC LICENSE v3.0
 * See the LICENSE file for terms of use.
 */

#ifndef DEPLOY_GROUP_LIST_H_
#define DEPLOY_GROUP_LIST_H_

#include "DeployItem.h"
#include "Session.h"
#include "Updateable.h"
#include "GroupTemplateDialog.h"

#include <Wt/Dbo/Dbo.h>
#include <Wt/WContainerWidget.h>

using namespace Wt;

class GroupTemplateList : public WContainerWidget, public Updateable {
  public:
    GroupTemplateList(Session &session);

    void update() override;

  private:
    Session &session_;
    std::unique_ptr<GroupTemplateDialog> groupDialog_;
};

#endif // DEPLOY_GROUP_LIST_H_
