//
// Created by skan on 16.04.19.
//

#ifndef TANCHIKI_WIDGETSMENU_HPP
#define TANCHIKI_WIDGETSMENU_HPP

#include <TGUI/TGUI.hpp>


class WidgetsMenu {

private:

    std::vector <tgui::Widget::Ptr> widgets;

    std::vector <tgui::EditBox::Ptr> boxes;

public:

    static void add_widget(const tgui::Widget::Ptr &widget);

    static void add_box(const tgui::EditBox::Ptr &box);

    static void widget_remove();

    static void change_ava(int sysok);

    static bool login();

};


#endif //TANCHIKI_WIDGETSMENU_HPP
