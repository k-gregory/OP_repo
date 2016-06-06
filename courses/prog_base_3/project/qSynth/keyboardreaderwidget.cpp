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
    GenericInputAction new_action;
    if(e->isAutoRepeat()) return;
    new_action.type = GenericInputAction::KeyPress;
    new_action.key = e->key();
    new_action.specialInfo[0] = e->modifiers();
    new_action.specialInfo[1] = e->text()[0].toLatin1();
    qDebug()<<"Pressed: "<<new_action.key;
    action_queue.push_back(new_action);
}

void KeyboardReaderWidget::keyReleaseEvent(QKeyEvent *e){
    GenericInputAction new_action;
    if(e->isAutoRepeat()) return;
    new_action.type = GenericInputAction::KeyRelease;
    new_action.key = e->key();
    new_action.specialInfo[0] = e->modifiers();
    action_queue.push_back(new_action);
}

bool KeyboardReaderWidget::hasInput(){
    return action_queue.size() != 0;
}

std::vector<GenericInputAction> KeyboardReaderWidget::pollInput(){
    std::vector<GenericInputAction> ret = std::vector<GenericInputAction>(action_queue);
    action_queue.clear();
    return ret;
}

} // namespace qSynth

