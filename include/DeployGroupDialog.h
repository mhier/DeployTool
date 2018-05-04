/*
 * WtTimeTrack - Web-based time tracker
 *
 * Copyright (C) 2017 Martin Hierholzer, Hamburg, Germany
 *
 * This program is released under the GNU GENERAL PUBLIC LICENSE v3.0
 * See the LICENSE file for terms of use.
 */

#ifndef DEPLOY_GROUP_DIALOG_H_
#define DEPLOY_GROUP_DIALOG_H_

#include "Session.h"
#include "Updateable.h"
#include "DeployGroup.h"

#include <Wt/WDialog.h>
#include <Wt/WDateEdit.h>
#include <Wt/WText.h>

using namespace Wt;

class DeployGroupDialog : public WDialog {
  public:
    DeployGroupDialog(Updateable *owner, Session &session, Wt::Dbo::ptr<DeployGroup> group);

    Session &session_;
    Updateable *owner_;

    Wt::Dbo::ptr<DeployGroup> group_;

};

#endif // DEPLOY_GROUP_DIALOG_H_
