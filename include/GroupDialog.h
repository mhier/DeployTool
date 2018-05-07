/*
 * WtTimeTrack - Web-based time tracker
 *
 * Copyright (C) 2017 Martin Hierholzer, Hamburg, Germany
 *
 * This program is released under the GNU GENERAL PUBLIC LICENSE v3.0
 * See the LICENSE file for terms of use.
 */

#ifndef GROUP_DIALOG_H_
#define GROUP_DIALOG_H_

#include "Session.h"
#include "Updateable.h"
#include "Group.h"
#include "ItemInstanceDialog.h"

#include <Wt/WDialog.h>
#include <Wt/WDateEdit.h>
#include <Wt/WText.h>

using namespace Wt;

class GroupDialog : public WDialog, public Updateable {
  public:
    GroupDialog(Updateable *owner, Session &session, Wt::Dbo::ptr<Group> group);

    void update() override;

    Session &session_;
    Updateable *owner_;

    Wt::Dbo::ptr<Group> group_;

};

#endif // GROUP_DIALOG_H_
