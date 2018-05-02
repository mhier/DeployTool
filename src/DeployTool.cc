/*
 * WtTimeTrack - Web-based time tracker
 *
 * Copyright (C) 2017 Martin Hierholzer, Hamburg, Germany
 *
 * This program is released under the GNU GENERAL PUBLIC LICENSE v3.0
 * See the LICENSE file for terms of use.
 */

#include <Wt/WApplication.h>
#include <Wt/Auth/AuthWidget.h>
#include <Wt/Auth/RegistrationModel.h>
#include <Wt/WText.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WCalendar.h>
#include <Wt/WPushButton.h>
#include <Wt/Auth/Dbo/AuthInfo.h>
#include <Wt/Auth/Dbo/UserDatabase.h>

#include "Session.h"
#include "DeployTool.h"
#include "DeployItemList.h"

DeployTool::DeployTool() {
    session_.login().changed().connect(this, &DeployTool::onAuthEvent);

    auto authModel = std::make_unique<Auth::AuthModel>(Session::auth(), session_.users());
    authModel->addPasswordAuth(&Session::passwordAuth());

    auto authWidget = std::make_unique<Auth::AuthWidget>(session_.login());
    authWidget->setModel(std::move(authModel));
    authWidget->setRegistrationEnabled(false);

    std::unique_ptr<WText> title(std::make_unique<WText>("<h1>Deployment Tool</h1>"));
    addWidget(std::move(title));

    authWidgetPtr = addWidget(std::move(authWidget));

    mainStack_ = new WStackedWidget();
    mainStack_->setHeight("100vH");
    addWidget(std::unique_ptr<WStackedWidget>(mainStack_));

    WApplication::instance()->internalPathChanged().connect(this, &DeployTool::handleInternalPath);

    authWidgetPtr->processEnvironment();
}

void DeployTool::onAuthEvent() {
    if(session_.login().loggedIn()) {
      createMenu();
      handleInternalPath(WApplication::instance()->internalPath());
    }
    else {
      mainStack_->clear();
      WApplication::instance()->setInternalPath("/",  true);
    }
}

void DeployTool::handleInternalPath(const std::string &internalPath) {
    Wt::Dbo::Transaction transaction(session_.session_);
    if(session_.login().loggedIn()) {
      contentStack_->clear();
      if (internalPath == "/search") {
        //contentStack_->addWidget( std::make_unique<SearchView>(session_) );
      }
      else if (internalPath == "/deployItemList") {
        contentStack_->addWidget( std::make_unique<DeployItemList>(session_) );
      }
      else if (internalPath == "/password") {
        //contentStack_->addWidget(std::make_unique<Wt::Auth::UpdatePasswordWidget>(session_.user(), ));
        auto authUser = session_.users_->find(session_.user()->authInfos.front());
        authWidgetPtr->letUpdatePassword(authUser, true);
      }
      else {
        WApplication::instance()->setInternalPath("/search",  true);
      }
    }
    else {
      WApplication::instance()->setInternalPath("/",  true);
    }
}

void DeployTool::createMenu() {
    Wt::Dbo::Transaction transaction(session_.session_);

    auto pane = std::make_unique<Wt::WContainerWidget>();
    auto pane_ = pane.get();
    mainStack_->addWidget(std::move(pane));
    auto hLayout = pane_->setLayout(std::make_unique<Wt::WHBoxLayout>());
    hLayout->setPreferredImplementation(Wt::LayoutImplementation::JavaScript);

    auto contentStack = std::make_unique<Wt::WStackedWidget>();
    contentStack_ = contentStack.get();
    contentStack_->addStyleClass("contents");
    contentStack_->setOverflow(Wt::Overflow::Auto);

    auto menu = std::make_unique<Wt::WMenu>(contentStack_);
    auto menu_ = menu.get();
    menu_->addStyleClass("nav nav-pills nav-stacked");
    menu_->setWidth(200);

    hLayout->addWidget(std::move(menu));
    hLayout->addWidget(std::move(contentStack),1);

    menu_->setInternalPathEnabled();
    menu_->setInternalBasePath("/");

    menu_->addItem("Search")->setPathComponent("search");
    menu_->addItem("Deploy Items")->setPathComponent("deployItemList");
    menu_->addItem("Change password")->setPathComponent("password");

}
