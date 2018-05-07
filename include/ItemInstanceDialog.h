/*
 * WtTimeTrack - Web-based time tracker
 *
 * Copyright (C) 2017 Martin Hierholzer, Hamburg, Germany
 *
 * This program is released under the GNU GENERAL PUBLIC LICENSE v3.0
 * See the LICENSE file for terms of use.
 */

#ifndef DEPLOY_ITEM_INSTANCE_DIALOG_H_
#define DEPLOY_ITEM_INSTANCE_DIALOG_H_

#include "Session.h"
#include "Updateable.h"
#include "ItemInstance.h"

#include <Wt/WDialog.h>
#include <Wt/WDateEdit.h>
#include <Wt/WText.h>

using namespace Wt;

class ItemInstanceDialog : public WDialog {
  public:
    ItemInstanceDialog(Updateable *owner, Session &session, Wt::Dbo::ptr<ItemInstance> instance);

    Session &session_;
    Updateable *owner_;
    Wt::WComboBox *w_item;
    Wt::WTable *parameterTable_;

    Wt::Dbo::ptr<ItemInstance> instance_;

    std::vector<Wt::WLineEdit*> v_paramNames;
    std::vector<Wt::WLineEdit*> v_paramValues;

};

#endif //DEPLOY_ITEM_INSTANCE_DIALOG_H_
