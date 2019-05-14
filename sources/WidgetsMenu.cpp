//
// Created by skan on 16.04.19.
//

#include "WidgetsMenu.hpp"
#include <iostream>
//                                       widgets:                                             |           boxes:            |
//0: single     1:multi     2: settings     3: quit     4: loginwindow      5: settingsWindow |  0: username    1: password |
//---------------------------------------------------------------------------------------------------------------------------

WidgetsMenu widgetsMenu;

void WidgetsMenu::add_widget(const tgui::Widget::Ptr &widget) {
    widgetsMenu.widgets.push_back(widget);
}

void WidgetsMenu::add_box(const tgui::EditBox::Ptr &box) {
    widgetsMenu.boxes.push_back(box);
}

void WidgetsMenu::widget_remove() {
    widgetsMenu.widgets.clear();
}

void WidgetsMenu::change_ava(int sysok) {
    switch (sysok) {
        case 1: {                                           //pressed multiButton
            for (auto i = 0; i < 4; i++)
                widgetsMenu.widgets[i]->setEnabled(false);
            widgetsMenu.widgets[5]->setEnabled(false);
            widgetsMenu.widgets[4]->setVisible(true);
            break;
        }
        case 0: {                                           //pressed buttonCancel
            for (auto i = 0; i < 4; i++)
                widgetsMenu.widgets[i]->setEnabled(true);
            widgetsMenu.widgets[5]->setEnabled(true);
            widgetsMenu.widgets[4]->setVisible(false);
            break;
        }
        case 2: {                                           //pressed settingsButton
            for (auto i = 0; i < 5; i++)
                widgetsMenu.widgets[i]->setEnabled(false);
            widgetsMenu.widgets[5]->setVisible(true);
            break;
        }
        case 3: {                                           //pressed settingsCancel or settingsAccept
            for (auto i = 0; i < 5; i++)
                widgetsMenu.widgets[i]->setEnabled(true);
            widgetsMenu.widgets[5]->setVisible(false);
            break;
        }
        default: {
            break;
        }
    }
}

std::pair<std::string, std::string> WidgetsMenu::login() {
    if (widgetsMenu.boxes[0]->getText().isEmpty() || widgetsMenu.boxes[1]->getText().isEmpty()) {
        if (widgetsMenu.boxes[0]->getText().isEmpty()) {
            widgetsMenu.boxes[0]->setDefaultText("Enter the username");
        }
        if (widgetsMenu.boxes[1]->getText().isEmpty()) {
            widgetsMenu.boxes[1]->setDefaultText("Enter the password");
        }
        return std::make_pair("", "");
    }
    else {
        WidgetsMenu::change_ava(0);
        return std::make_pair(widgetsMenu.boxes[0]->getText().toAnsiString(), widgetsMenu.boxes[1]->getText().toAnsiString());
    }
}


