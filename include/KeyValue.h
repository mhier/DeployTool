/*
 * DeployTool - Web-based software/firmware deployment tool
 *
 * Copyright (C) 2018 Martin Hierholzer, Deutsches Elektronen-Synchrotron DESY Hamburg, Germany
 *
 * This program is released under the GNU GENERAL PUBLIC LICENSE v3.0
 * See the LICENSE file for terms of use.
 */

#ifndef KEYVALUE_H
#define KEYVALUE_H

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/WtSqlTraits.h>

template<typename OWNER>
class KeyValue {
  public:
    KeyValue() {}

    Wt::Dbo::collection<Wt::Dbo::ptr<OWNER>> owner;
    std::string key;
    std::string value;

    const static std::string name;

    template<class Action>
    void persist ( Action& a ) {
        Wt::Dbo::hasMany ( a, owner, Wt::Dbo::ManyToMany, name );
        Wt::Dbo::field ( a, key, "key" );
        Wt::Dbo::field ( a, value, "value" );
    }

};

template<typename OWNER>
const std::string KeyValue<OWNER>::name = std::string("parameters_") + typeid(OWNER).name();

#endif // KEYVALUE_H
