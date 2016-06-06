#include "keyboardreaderwidget.h"
#include <QKeyEvent>
#include <QDebug>

namespace qSynth {

KeyboardReaderWidget::KeyboardReaderWidget(QWidget *parent) : QWidget(parent)
{
    setMinimumHeight(QSYNTH_KEYBOARDREADERWIGHET_MIN_HEIGHT);
    setMinimumWidth(50);
    setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    setFocusPolicy(Qt::StrongFocus);
    setupLabel();
}

void KeyboardReaderWidget::setupLabel(){
   label = new QLabel("This widget reads keyboard input, it must be in focus",this);
}

void KeyboardReaderWidget::keyPressEvent(QKeyEvent *e){
    Action new_action;
    if(e->isAutoRepeat()) return;
    new_action.type = Action::KeyPress;
    new_action.key = e->key();
    new_action.specialInfo[0] = e->modifiers();
    qDebug()<<"Pressed: "<<new_action.key;
    action_queue.push_back(new_action);
}

void KeyboardReaderWidget::keyReleaseEvent(QKeyEvent *e){
    Action new_action;
    new_action.type = Action::KeyRelease;
    new_action.key = e->key();
    new_action.specialInfo[0] = e->modifiers();
    action_queue.push_back(new_action);
}

std::vector<Action> KeyboardReaderWidget::poll_input(){
    std::vector<Action> ret = std::vector<Action>(action_queue);
    action_queue.clear();
    return ret;
}

} // namespace qSynth

