/*
 * DeployTool - Web-based software/firmware deployment tool
 *
 * Copyright (C) 2018 Martin Hierholzer, Deutsches Elektronen-Synchrotron DESY Hamburg, Germany
 *
 * This program is released under the GNU GENERAL PUBLIC LICENSE v3.0
 * See the LICENSE file for terms of use.
 */

#ifndef INCLUDE_DEPLOY_ITEM_INSTANCE_H_
#define INCLUDE_DEPLOY_ITEM_INSTANCE_H_

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/WtSqlTraits.h>

#include "DeployItem.h"
#include "KeyValue.h"

class GroupTemplate;

class DeployItemInstance {
  public:
    DeployItemInstance() {}

    Wt::Dbo::ptr<GroupTemplate> deployGroup;
    Wt::Dbo::ptr<DeployItem> deployItem;
    Wt::Dbo::collection< Wt::Dbo::ptr<KeyValue<DeployItemInstance>> > parameters;

    template<class Action>
    void persist ( Action& a ) {
        Wt::Dbo::belongsTo ( a, deployGroup, "groupInstances" );
        Wt::Dbo::belongsTo ( a, deployItem, "itemInstances" );
        Wt::Dbo::hasMany ( a, parameters, Wt::Dbo::ManyToMany, KeyValue<DeployItemInstance>::name );
    }

};

#endif /* INCLUDE_DEPLOY_ITEM_INSTANCE_H_ */
