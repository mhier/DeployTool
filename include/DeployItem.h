/*
 * WtTimeTrack - Web-based time tracker
 *
 * Copyright (C) 2017 Martin Hierholzer, Hamburg, Germany
 *
 * This program is released under the GNU GENERAL PUBLIC LICENSE v3.0
 * See the LICENSE file for terms of use.
 */

#ifndef INCLUDE_DEPLOY_ITEM_H_
#define INCLUDE_DEPLOY_ITEM_H_

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/WtSqlTraits.h>

class User;

class DeployItem {
  public:
    DeployItem() {}

    enum class SourceType {
      APT, FILESYSTEM
    };

    std::string name;
    SourceType sourceType;
    std::string sourcePath;
    std::string installCommand;

    template<class Action>
    void persist ( Action& a ) {
        Wt::Dbo::field ( a, name, "name" );
        Wt::Dbo::field ( a, sourceType, "sourceType" );
        Wt::Dbo::field ( a, sourcePath, "sourcePath" );
        Wt::Dbo::field ( a, installCommand, "installCommand" );
    }

};

#endif /* INCLUDE_DEPLOY_ITEM_H_ */
