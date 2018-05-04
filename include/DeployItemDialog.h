/*
 * WtTimeTrack - Web-based time tracker
 *
 * Copyright (C) 2017 Martin Hierholzer, Hamburg, Germany
 *
 * This program is released under the GNU GENERAL PUBLIC LICENSE v3.0
 * See the LICENSE file for terms of use.
 */

#ifndef DEPLOY_ITEM_DIALOG_H_
#define DEPLOY_ITEM_DIALOG_H_

#include "Session.h"
#include "Updateable.h"
#include "DeployItem.h"

#include <Wt/WDialog.h>
#include <Wt/WDateEdit.h>
#include <Wt/WText.h>

using namespace Wt;

class DeployItemDialog : public WDialog {
  public:
    DeployItemDialog(Updateable *owner, Session &session, Wt::Dbo::ptr<DeployItem> item);

    Session &session_;
    Updateable *owner_;

    Wt::Dbo::ptr<DeployItem> item_;

    std::vector<Wt::WLineEdit*> v_paramNames;
    std::vector<Wt::WLineEdit*> v_paramValues;

};

#endif //DEPLOY_ITEM_DIALOG_H_
