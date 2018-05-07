/*
 * DeployTool - Web-based software/firmware deployment tool
 *
 * Copyright (C) 2018 Martin Hierholzer, Deutsches Elektronen-Synchrotron DESY Hamburg, Germany
 *
 * This program is released under the GNU GENERAL PUBLIC LICENSE v3.0
 * See the LICENSE file for terms of use.
 */

#ifndef INCLUDE_DEPLOY_GROUP_H_
#define INCLUDE_DEPLOY_GROUP_H_

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/WtSqlTraits.h>

#include "DeployItemInstance.h"

class DeployGroup {
  public:
    DeployGroup() {}

    std::string name;
    std::string hostname;
    Wt::Dbo::collection< Wt::Dbo::ptr<DeployItemInstance> > deployItemInstances;

    template<class Action>
    void persist ( Action& a ) {
        Wt::Dbo::field ( a, name, "name" );
        Wt::Dbo::field ( a, hostname, "hostname" );
        Wt::Dbo::hasMany ( a, deployItemInstances, Wt::Dbo::ManyToOne, "groupInstances" );
    }

};

#endif /* INCLUDE_DEPLOY_GROUP_H_ */
