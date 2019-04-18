//
// Created by skan on 16.04.19.
//

#include "WidgetsMenu.hpp"
#include <iostream>
//                          widgets:                              |           boxes:            |
//0: single     1:multi     2: settings     3: quit     4: window |  0: username    1: password |
//-----------------------------------------------------------------------------------------------

WidgetsMenu widgetsMenu;

void WidgetsMenu::add_widget(const tgui::Widget::Ptr &widget) {
    widgetsMenu.widgets.push_back(widget);
}

void WidgetsMenu::add_box(const tgui::EditBox::Ptr &box) {
    widgetsMenu.boxes.push_back(box);
}

//void WidgetsMenu::add_widget(const tgui::Widget::Ptr &widgetPtr, const sf::String &widgetName){
//    widgetsMenu.widgets.push_back(widgetPtr);
//}

//void WidgetsMenu::get_widget() {
//    for (auto i = 0; i < widgetsMenu.widgets.size(); i++)
//        std::cout << i+1 << "-й виджет: " << widgetsMenu.widgets[i] << " is " << widgetsMenu.available[i] << std::endl;
//}

void WidgetsMenu::widget_remove() {
    widgetsMenu.widgets.clear();
}

void WidgetsMenu::change_ava(int sysok) {
    switch (sysok) {
        case 1: {
            for (auto i = 0; i < 4; i++)
                widgetsMenu.widgets[i]->setEnabled(false);
            widgetsMenu.widgets[4]->setVisible(true);
            break;
        }
        case 0: {
            for (auto i = 0; i < 4; i++)
                widgetsMenu.widgets[i]->setEnabled(true);
            widgetsMenu.widgets[4]->setVisible(false);
            break;
        }
        default: {
            break;
        }
    }
}

bool WidgetsMenu::login() {
    if (widgetsMenu.boxes[0]->getText().isEmpty() || widgetsMenu.boxes[1]->getText().isEmpty()) {
        if (widgetsMenu.boxes[0]->getText().isEmpty()) {
            widgetsMenu.boxes[0]->setDefaultText("Enter the username");
        }
        if (widgetsMenu.boxes[1]->getText().isEmpty()) {
            widgetsMenu.boxes[1]->setDefaultText("Enter the password");
        }
        return false;
    }
    else {
        std::cout << "Username: " << widgetsMenu.boxes[0]->getText().toAnsiString() << std::endl;
        std::cout << "Password: " << widgetsMenu.boxes[1]->getText().toAnsiString() << std::endl;
        ///@todo сформировать http-запрос
        std::string message("Authorization...");

        WidgetsMenu::change_ava(0);
        return true;
    }
}


