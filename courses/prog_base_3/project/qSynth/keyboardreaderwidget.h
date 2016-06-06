#ifndef QSYNTH_KEYBOARDREADERWIDGET_H
#define QSYNTH_KEYBOARDREADERWIDGET_H

#define QSYNTH_KEYBOARDREADERWIGHET_MIN_HEIGHT (80)

#include <igenericinput.h>
#include <vector>
#include <QLabel>
#include <QWidget>

namespace qSynth {

class KeyboardReaderWidget : public QWidget, public IGenericInput
{
    Q_OBJECT
public:
    explicit KeyboardReaderWidget(QWidget *parent = 0);
    std::vector<Action> poll_input();
private:
    void setupLabel();

    void keyPressEvent(QKeyEvent* e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
    std::vector<Action> action_queue;

    QLabel* label;
};

} // namespace qSynth

#endif // QSYNTH_KEYBOARDREADERWIDGET_H
