/*
 * WtTimeTrack - Web-based time tracker
 *
 * Copyright (C) 2017 Martin Hierholzer, Hamburg, Germany
 *
 * This program is released under the GNU GENERAL PUBLIC LICENSE v3.0
 * See the LICENSE file for terms of use.
 */

#ifndef INCLUDE_GROUP_VERSION_DIALOG_H_
#define INCLUDE_GROUP_VERSION_DIALOG_H_

#include "Session.h"
#include "Updateable.h"
#include "Group.h"
#include "ItemInstanceDialog.h"

#include <Wt/WDialog.h>
#include <Wt/WDateEdit.h>
#include <Wt/WText.h>

using namespace Wt;

class GroupVersionDialog : public WDialog, public Updateable {
  public:
    GroupVersionDialog(Updateable *owner, Session &session, Wt::Dbo::ptr<GroupVersion> groupVersion);

    void update() override;

    Session &session_;
    Updateable *owner_;

    Wt::Dbo::ptr<GroupVersion> groupVersion_;

    std::vector<WLineEdit*> versions_;

};

#endif // INCLUDE_GROUP_VERSION_DIALOG_H_
