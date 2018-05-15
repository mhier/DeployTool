/*
 * WtTimeTrack - Web-based time tracker
 *
 * Copyright (C) 2017 Martin Hierholzer, Hamburg, Germany
 *
 * This program is released under the GNU GENERAL PUBLIC LICENSE v3.0
 * See the LICENSE file for terms of use.
 */

#ifndef VERSIONS_LIST_H_
#define VERSIONS_LIST_H_

#include "Item.h"
#include "Session.h"
#include "Updateable.h"
#include "GroupVersionDialog.h"

#include <Wt/Dbo/Dbo.h>
#include <Wt/WContainerWidget.h>

using namespace Wt;

class VersionsList : public WContainerWidget, public Updateable {
  public:
    VersionsList(Session &session);

    void update() override;

  private:
    Session &session_;
    std::unique_ptr<GroupVersionDialog> groupVersionDialog_;
};

#endif // VERSIONS_LIST_H_
